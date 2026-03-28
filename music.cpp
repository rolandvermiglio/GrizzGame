#include "music.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

Mix_Music* music = nullptr;
Uint32 musicStartTime = 0; // ms timestamp when music starts

// Start music
bool startAudio(const char* filename) {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << "\n";
        return false;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "Mix_OpenAudio Error: " << Mix_GetError() << "\n";
        return false;
    }

    music = Mix_LoadMUS(filename);
    if (!music) {
        std::cerr << "Mix_LoadMUS Error: " << Mix_GetError() << "\n";
        return false;
    }

    if (Mix_PlayMusic(music, 0) < 0) {
        std::cerr << "Mix_PlayMusic Error: " << Mix_GetError() << "\n";
        return false;
    }

    musicStartTime = SDL_GetTicks(); // record start time for precise tracking
    return true;
}

// Pause / resume
void pauseAudio() {
    Mix_PauseMusic();
}

void resumeAudio() {
    Mix_ResumeMusic();
}

// Stop and cleanup
void stopAudio() {
    Mix_HaltMusic();
    if (music) Mix_FreeMusic(music);
    Mix_CloseAudio();
    SDL_Quit();
}

//returns variance between expected and actual beat timing
int beatVariance(const bool* chart, size_t chartLength, Uint32 chartBegin) {
    Uint32 elapsedMs = getMusicTime();
    if (elapsedMs == 0) return -1;

    // Convert ms to beats (240 BPM → 1 beat = 250 ms)
    double beats = elapsedMs / 250.0;
    int beatIndex = static_cast<int>(round(beats));

    if (beatIndex < 0 || beatIndex >= chartLength) return -1;
    if (!chart[beatIndex]) return -1;

    // Return absolute variance in ms between expected beat and actual elapsed time
    int expectedMs = beatIndex * 250;
    return static_cast<int>(abs(static_cast<int>(elapsedMs) - expectedMs));
}

// Get elapsed music time in milliseconds
Uint32 getMusicTime() {
    if (Mix_PlayingMusic()) {
        return SDL_GetTicks() - musicStartTime;
    }
    return 0;
}
#ifndef MUSIC_H
#define MUSIC_H

//remember to install SDL2
//sudo apt-get install libsdl2-dev
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

//starts the audio player, music starts playing automaticly
bool startAudio(const char* filename)

//take a wild guess
void pauseAudio();
void resumeAudio();
void stopAudio();

//returns variance between expected and actual beat timing
int beatVariance(const bool* chart, size_t chartLength, Uint32 chartBegin)

//returns time in ms since start of song
Uint32 getMusicTime()

#endif
/* 
 * File:   SoundManager.cpp
 * Author: jernej
 * 
 * Created on February 11, 2010, 4:55 PM
 */

#include "SoundManager.h"
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <map>

SoundManager::SoundManager() {

    // initialization
    audio_rate = 22050;			//Frequency of audio playback
    audio_format = AUDIO_S16SYS; 	//Format of the audio we're playing
    audio_channels = 2;			//2 channels = stereo
    audio_buffers = 4096;		//Size of the audio buffers in memory

    //Initialize SDL audio
    if (SDL_Init(SDL_INIT_AUDIO) != 0) { // todo: prestavi ta sdl_init k prvemu sdl initu
            printf("Unable to initialize SDL: %s\n", SDL_GetError());
            // todo: nekak pohendlaj napako
    }

    //Initialize SDL_mixer with our chosen audio settings
    if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) {
            printf("Unable to initialize audio: %s\n", Mix_GetError());
            //exit(1); todo: handling napake
    }

}

SoundManager::SoundManager(const SoundManager& orig) {
}

SoundManager::~SoundManager() {
    //Release the memory allocated to our sounds
    map<string,Mix_Chunk*>::iterator it;
    Mix_Chunk* sound = NULL;

    for (it = effects.begin(); it != effects.end(); it++)
    {
        sound = effects[(*it).first];
        Mix_FreeChunk(sound);
    }

    Mix_CloseAudio();
}

void SoundManager::loadEffect(string name, string path) {
    //Load our WAV file from disk
    Mix_Chunk* sound = Mix_LoadWAV(path.c_str());
    if(sound == NULL) {
        printf("Unable to load WAV file: %s\n", Mix_GetError());
    }

    effects.insert(pair<string,Mix_Chunk*>(name,sound));
}

void SoundManager::playEffect(string name) {

    Mix_Chunk* sound = NULL;
    map<string,Mix_Chunk*>::iterator it;
    it=effects.find(name);

    if (it != effects.end())
    {
        sound = effects[name];
        channel0 = Mix_PlayChannel(-1, sound, 0);
        if(channel0 == -1) {
                printf("Unable to play WAV file: %s\n", Mix_GetError());
        }
    }
    else
    {
        printf("Error: effect with this name does not exist!");
    }
}

void SoundManager::loadMusic(string name, string path) {
}

void SoundManager::playMusic() {

}

void SoundManager::stopMusic() {

}


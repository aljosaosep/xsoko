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
#include <iostream>
#include <stdexcept>

using namespace std;

SoundManager::SoundManager() {

    // initialization
    audio_rate = 22050;			//Frequency of audio playback
    audio_format = AUDIO_S16SYS; 	//Format of the audio we're playing
    audio_channels = 2;			//2 channels = stereo
    audio_buffers = 4096;		//Size of the audio buffers in memory

    //Initialize SDL_mixer with our chosen audio settings
    if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) {
            printf("Unable to initialize audio: %s\n", Mix_GetError());
            //exit(1); todo: handling napake
    }

    Mix_VolumeMusic(MIX_MAX_VOLUME/2.5);  // set music volume
    musicStatus = false;                  // music status initialization
    currentMusic = "";
}

SoundManager::SoundManager(const SoundManager& orig) {
}

SoundManager::~SoundManager() {
    //Release the memory allocated to our musics and sounds
    map<string,Mix_Chunk*>::iterator it;
    Mix_Chunk* sound = NULL;

    for (it = effects.begin(); it != effects.end(); it++)
    {
        sound = effects[(*it).first];
        Mix_FreeChunk(sound);
    }

    map<string,Mix_Music*>::iterator it2;
    Mix_Music* music = NULL;

    for (it2 = musics.begin(); it2 != musics.end(); it2++)
    {
        music = musics[(*it2).first];
        Mix_FreeMusic(music);
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
    Mix_Music *music = Mix_LoadMUS(path.c_str());
    if(music == NULL) {
        printf("Unable to load music file: %s\n", Mix_GetError());
    }
    
    musics.insert(pair<string,Mix_Music *>(name,music));
}

void SoundManager::playMusic(string name) {
    Mix_Music* music = NULL;
    map<string,Mix_Music*>::iterator it;
    it=musics.find(name);

    if (it != musics.end())
    {
        music = musics[name];
        if(!Mix_PlayingMusic())
        {
            Mix_PlayMusic(music, 0);
            musicStatus = true;
            currentMusic = name;
        } else {
            cout << "Music is already playing!" << endl;
        }
    }
    else
    {
        printf("Error: effect with this name does not exist!");
    }
}

void SoundManager::playMusic() {
    // if there is no music set to be played, start from the beginning
    if (currentMusic == "")
    {
        if (musics.size() > 0) {
            playMusic((*musics.begin()).first);
        } else {
            printf("Error: there is no music to play!");
        }
    }
    else
    {
        playMusic(currentMusic);
    }
}

void SoundManager::stopMusic() {
    if (Mix_PlayingMusic()) {
        Mix_HaltMusic();// stop
        musicStatus = false;
    }
}

bool SoundManager::getMusicStatus() {
    return musicStatus;
}

void SoundManager::playNextMusic() {

    if (currentMusic != "") {
        map<string,Mix_Music*>::iterator it;
        it=musics.find(currentMusic);
        
        cout << "Current Iterator: " << (*it).first << endl;

        it++; // fixme: tu je neki bug

        cout << "Iterator: " << (*it).first << endl;
        stopMusic();
        playMusic((*it).first);
    } else {
        // todo: handle this - there was no music played
    }
}

void SoundManager::playPreviousMusic() {

    if (currentMusic != "") {
        map<string,Mix_Music*>::iterator it;
        it=musics.find(currentMusic);
        cout << "Current Iterator: " << (*it).first << endl;

        it--;

        cout << "New Iterator: " << (*it).first << endl;
        stopMusic();
        playMusic((*it).first);
    } else {
        // todo: handle this - there was no music played
    }
}


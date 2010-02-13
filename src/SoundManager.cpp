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
#include "messages.h"

using namespace PacGame;

namespace PacGame
{
    namespace GameClasses
    {

        SoundManager::SoundManager() {

            // initialization
            audio_rate = 22050;			//Frequency of audio playback
            audio_format = AUDIO_S16SYS; 	//Format of the audio we're playing
            audio_channels = 2;			//2 channels = stereo
            audio_buffers = 4096;		//Size of the audio buffers in memory

            //Initialize SDL_mixer with our chosen audio settings
            if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) {
                Messages::errorMessage("unable to initialize audio");
                //exit(1); todo: handling napake
            } else {
                Mix_VolumeMusic(MIX_MAX_VOLUME/2.5);  // set music volume
                musicStatus = false;                  // music status initialization
                lastMusic = "";
                Messages::initMessage("sound manager",true);
            }
        }

        SoundManager::SoundManager(const SoundManager& orig) {
            this->audio_buffers  = orig.audio_buffers;
            this->audio_channels = orig.audio_channels;
            this->audio_format   = orig.audio_format;
            this->audio_rate     = orig.audio_rate;
            this->channel0       = orig.channel0;
            this->effects        = orig.effects;
            this->lastMusic      = orig.lastMusic;
            this->musicStatus    = orig.musicStatus;
            this->musics         = orig.musics;
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

            map<string,Mix_Chunk*>::iterator it;
            it=effects.find(name);

            if (it == effects.end()) {
                Mix_Chunk* sound = Mix_LoadWAV(path.c_str());
                if(sound == NULL) {
                    Messages::errorMessage("unable to load effect file '" + path + "'");
                } else {
                    effects.insert(pair<string,Mix_Chunk*>(name,sound));
                    Messages::infoMessage("sound effect '"+name+"' loaded successfully");
                }
            } else {
                Messages::errorMessage("sound effect with name '"+name+"' already exist");
            }
        }

        void SoundManager::unloadEffect(string name) {
            map<string,Mix_Chunk*>::iterator it;
            it=effects.find(name);

            if (it != effects.end()) {
                Mix_Chunk* sound = effects[(*it).first];
                Mix_FreeChunk(sound);
                effects.erase(it);
                Messages::infoMessage("sound effect '"+name+"' deleted successfully");
            } else {
                Messages::errorMessage("sound effect with name '"+name+"' doesn't exist");
            }
        }

        void SoundManager::playEffect(string name) {

            Mix_Chunk* sound = NULL;
            map<string,Mix_Chunk*>::iterator it;
            it=effects.find(name);

            if (it != effects.end()) {
                sound = effects[name];
                channel0 = Mix_PlayChannel(-1, sound, 0);
                if(channel0 == -1) {
                    Messages::errorMessage("unable to play effect '" + name + "'");
                }
            }
            else {
                Messages::errorMessage("effect with name '"+name+"' does not exist");
            }
        }

        void SoundManager::loadMusic(string name, string path) {

            map<string,Mix_Music*>::iterator it;
            it=musics.find(name);

            if (it == musics.end()) {
                Mix_Music *music = Mix_LoadMUS(path.c_str());

                if(music == NULL) {
                    Messages::errorMessage("unable to load music file '" + path + "'");
                } else {
                    musics.insert(pair<string,Mix_Music *>(name,music));
                    Messages::infoMessage("music '"+name+"' loaded successfully");
                }
            } else {
                Messages::errorMessage("music with name '"+name+"' already exist");
            }
        }

        void SoundManager::unloadMusic(string name) {
            map<string,Mix_Music*>::iterator it;
            it=musics.find(name);

            if (it != musics.end()) {
                Mix_Music* music = musics[(*it).first];
                Mix_FreeMusic(music);
                musics.erase(it);
                Messages::infoMessage("music '"+name+"' deleted successfully");
            } else {
                Messages::errorMessage("music with name '"+name+"' does not exist");
            }
        }

        void SoundManager::playMusic(string name) {
            Mix_Music* music = NULL;
            map<string,Mix_Music*>::iterator it;
            it=musics.find(name);

            if (it != musics.end()) {
                music = musics[name];

                if(Mix_PlayingMusic()) {
                    stopMusic();
                }
                
                Mix_PlayMusic(music, 0);
                musicStatus = true;
                lastMusic = name;
            }
            else {
                Messages::errorMessage("music with this name does not exist");
            }
        }

        void SoundManager::playMusic() {
            // if there is no music set to be played, start from the beginning
            if (lastMusic == "") {
                if (musics.size() > 0) {
                    playMusic((*musics.begin()).first);
                } else {
                    Messages::errorMessage("there is no music to play");
                }
            }
            else {
                playMusic(lastMusic);
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
            if (musicStatus) {
                map<string,Mix_Music*>::iterator it;
                it=musics.find(lastMusic);

                it++;

                if (it == musics.end())
                {
                    it = musics.begin();
                }

                stopMusic();
                playMusic((*it).first);

            } else {
                Messages::errorMessage("start playing music first");
            }
        }

        void SoundManager::playPreviousMusic() {
            if (musicStatus) {
                map<string,Mix_Music*>::iterator it;
                it=musics.find(lastMusic);

                if (it == musics.begin()) {
                    it = musics.end();
                }

                it--;

                stopMusic();
                playMusic((*it).first);
            } else {
                Messages::errorMessage("start playing music first");
            }
        }
    }
}


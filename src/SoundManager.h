/* 
 * File:   SoundManager.h
 * Author: jernej
 *
 * Created on February 11, 2010, 4:55 PM
 */

#ifndef _SOUNDMANAGER_H
#define	_SOUNDMANAGER_H

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <map>
#include <string>
using namespace std;

class SoundManager {
    
    int channel0;           //effects channel
    int channel1;           //music channel
    int audio_rate;         //Frequency of audio playback
    Uint16 audio_format;    //Format of the audio we're playing
    int audio_channels;     //2 channels = stereo
    int audio_buffers;      //Size of the audio buffers in memory

    map<string,Mix_Chunk*> effects;
    map<string,Mix_Music*> musics;

    bool musicStatus;       // true - music is playing, false - no backgound music
    string currentMusic;    // name of currently playing music

public:
    SoundManager();
    SoundManager(const SoundManager& orig);
    virtual ~SoundManager();
    void loadEffect(string name, string path);
    void playEffect(string name);
    void loadMusic(string name, string path);
    void playMusic(string name);
    void playMusic();
    void stopMusic();
    bool getMusicStatus();
    void playNextMusic();
    void playPreviousMusic();
};

#endif	/* _SOUNDMANAGER_H */


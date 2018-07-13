#ifndef _SoundMixer_
#define _SoundMixer_

#include "SDL2/SDL_mixer.h"

#include <map>
#include <string>
#include <iostream>
#include <vector>

enum soundType
{
  SOUND_MUSIC = 0,
  SOUND_SFX = 1
};

class SoundMixer {

private:
  static SoundMixer* s_pInstance;

  //maps holding a string reference to an audio file. Split into music and soundSFX maps
  std::map<std::string, Mix_Chunk*> m_sfxs;
  std::map<std::string, Mix_Music*> m_music;


  //the queue of gene sounds to play, with the next to play in 0th position
  std::vector<unsigned> genotypePlayQueue;
  
public:

  SoundMixer(); //constructor
  ~SoundMixer(); //destr

  //singleton instance
  static SoundMixer* Instance();

  //the file name is found within the assets/Audio folder, and has a string id associated with it so it can be
  //referred to via a name. The sound is given a type (music/soundSFX) which will determine which audio channel
  //the sound is played on
  bool load(std::string fileName, std::string id, soundType type);

  //void playMusic (std::string id, int loop);

  //plays the audio file mapped to the given string id for int loop times
  void playSound (std::string id, int loop);

  //if a microbe has been selected for its genes to be played then each frame this method will be run and play
  //the appropriate sound for each gene
  void playQueuedGenotypes();

  //upon selecting a new microbe it is checked if there is currently a microbe's genes playing, and if so they
  //are removed from the queue and stopped. The new genes are copied into the queue and the first gene played
  void loadToQueuedGenotypes(const std::vector<unsigned>& genotypesToQueue);

  //used when a microbe is deselected, or dies. The current genes queued up to play will be removed, and any
  //currently playing sounds will fade out
  void stopPlayingGenotypes();
};

typedef SoundMixer TheSoundMixer;

#endif

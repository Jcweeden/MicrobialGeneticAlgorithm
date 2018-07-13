#include "SoundMixer.h"
//#include "SDL/SDL_mixer.h"
#include <unistd.h>


SoundMixer* SoundMixer::s_pInstance = 0;


SoundMixer* SoundMixer::Instance()
{
  if(s_pInstance == 0)
  {
    s_pInstance = new SoundMixer();
    return s_pInstance;
  }
  return s_pInstance;
}


SoundMixer::SoundMixer()
{
  Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, (4096));

  std::vector<std::string> genotypePlayQueue;
}

SoundMixer::~SoundMixer()
{
  Mix_CloseAudio();
}

bool SoundMixer::load(std::string fileName, std::string id, soundType type)
{
   if(type == SOUND_MUSIC)
    {
        Mix_Music* pMusic = Mix_LoadMUS(fileName.c_str());
        if(pMusic == 0)
        {
            std::cout << "Could not load music: ERROR - " << Mix_GetError() << std::endl;
            return false;
        }
        
        m_music[id] = pMusic;
        return true;
    }
    else if(type == SOUND_SFX)
    {
        Mix_Chunk* pChunk = Mix_LoadWAV(fileName.c_str());
        if(pChunk == 0)
        {
            std::cout << "Could not load SFX: ERROR - " << Mix_GetError() << std::endl;
            return false;
        }
        
        m_sfxs[id] = pChunk;
        return true;
    }
    return false;
}

/* //unused in this project
void SoundMixer::playMusic(std::string id, int loop)
{
  Mix_PlayMusic(m_music[id], loop);
}
*/

void SoundMixer::playSound(std::string id, int loop)
{
  Mix_PlayChannel(2, m_sfxs[id], loop);
}

void SoundMixer::playQueuedGenotypes()
{
  //if something is queued
  if ( genotypePlayQueue.size() > 0)
  {
    //if not already playing a genotype
    if (!Mix_Playing(2))
    {
      //play the next genotype in the queue
      playSound(std::to_string(genotypePlayQueue[0]), 0);
      //and remove it from the queue
      genotypePlayQueue.erase(genotypePlayQueue.begin()+0);
    }
  }
}

void SoundMixer::loadToQueuedGenotypes(const std::vector<unsigned>& genotypesToQueue)
{
  //stop the current gene playing
  Mix_HaltChannel(2);
  
  //clear the current queue
  genotypePlayQueue.clear();
  
  //add new genotypes to queue
  for (size_t i = 0; i < genotypesToQueue.size(); ++i)
    genotypePlayQueue.push_back(genotypesToQueue[i]);
  
  //call to play this
  playQueuedGenotypes();
}

void SoundMixer::stopPlayingGenotypes()
{
  //empty the queue
  genotypePlayQueue.clear();

  //and fade out and stop the current gene playing (should one be playing)
  Mix_FadeOutChannel(2, 100);
}

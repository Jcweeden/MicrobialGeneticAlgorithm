#ifndef _MicrobialGA_
#define _MicrobialGA_
#include "SDL2/SDL.h"
#include <vector>


class MicrobialGA
{
public:

  std::vector<unsigned> genotypes;

  std::vector<unsigned> targetGenotypes; //const
 

  
public:

  MicrobialGA(); //constructor

  unsigned getFitness();

  void assignNewRandomGenotypes();
  void setGenotype(unsigned geneIndex, unsigned geneValue);
};

#endif

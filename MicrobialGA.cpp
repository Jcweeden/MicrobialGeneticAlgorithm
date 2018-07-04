#include "MicrobialGA.h"

MicrobialGA::MicrobialGA()
{

  //setup target array
  targetGenotypes = {0,1,2,1};

  //setup genes array
  genotypes = { };

}

void MicrobialGA::assignNewRandomGenotypes()
{
  for (size_t i = 0; i < 4; i++) {
    setGenotype(i, rand() % 4);
  }
}

void MicrobialGA::setGenotype(unsigned geneIndex, unsigned geneValue)
{
  genotypes[geneIndex] = geneValue;
}

unsigned MicrobialGA::getFitness() {
  unsigned fitnessCounter = 0;
  for (size_t i = 0; i < 4; i++) {             //for each genotype (musical note)
    if ( genotypes[i] == targetGenotypes[i]) { //if the letter in the genotype matches that of the target array
      fitnessCounter++;                        //add one to the counter
    }
  }
  return fitnessCounter;
}

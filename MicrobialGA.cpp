#include "MicrobialGA.h"

MicrobialGA::MicrobialGA()
{

  //setup target array
  targetGenotypes = {0,1,2,1};

  //setup genes array
  genotypes = {0,0,0,0};

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

 char MicrobialGA::getGenotypeLetter(const size_t index)
 {
   switch (getGenotype(index))
   {
     case 0:
       return 'C';
     case 1:
       return 'D';
     case 2:
       return 'E';
     case 3:
       return 'F';
     default:
       return false;
   }
 }


bool MicrobialGA::isGenotypeCorrect(const size_t index)
{
  if (genotypes[index] == targetGenotypes[index]) return true;
  else return false;
}

void MicrobialGA::mutateGenotype()
{
  genotypes[rand() % 4] = rand() % 4;
}

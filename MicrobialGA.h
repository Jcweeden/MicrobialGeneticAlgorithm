#ifndef _MicrobialGA_
#define _MicrobialGA_
#include "SDL2/SDL.h"
#include <vector>


class MicrobialGA
{
public:
  //the set of four genes associated to the microbe. values range from 0 to 2 inclusive
  std::vector<unsigned> genotypes;

  //the set of genes that produce the tune of frere jacques. The genotypes must match this to be at 100% fitness
  const std::vector<unsigned> targetGenotypes {0,1,2,0};
   
public:

  MicrobialGA(); //constructor

  //compares the genotypes to targetGenotypes and returns an unsigned val of +1 for each matching gene
  unsigned getFitness();

  //sets each gene to randomly to a new value (0 to 2 inclusive)
  void assignNewRandomGenotypes();

  //sets the gene at geneIndex in genotypes to the specified geneValue
  void setGenotype(unsigned geneIndex, unsigned geneValue);

  //returns the gene number at the geneIndex passed in
  const unsigned getGenotype(const size_t index) { return genotypes[index];}

  //returns the gene musical note at the geneIndex passed in
  char getGenotypeLetter(const size_t index);

  //returns true if the gene at the index passed in matches that in the targetGenotypes
  bool isGenotypeCorrect(const size_t index);
  
  //randomly selects a gene and sets it randomly to a new value (0 to 2 inclusive)
  void mutateGenotype();
};

#endif

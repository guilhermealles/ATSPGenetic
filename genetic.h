#ifndef GENETIC_H
#define GENETIC_H

void initializeRandomGenerator();
unsigned int calculateCost(unsigned int solution_index);
int validSolution (unsigned int solution_index);
void stepGeneration();
int notChosen(unsigned int node, int *solution);
unsigned int getFirstNotChosenNode (int *solution);
int* crossover (unsigned int parent1_index, unsigned int parent2_index);
void printSolution(int *solution);
float getSolutionsAverageCost();
int numberOfCopiesForSolution(int solution_index);
void createMatrixFromData();
void printPopulation(int **population_matriz);

#endif

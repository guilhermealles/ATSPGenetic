#ifndef GENETIC_H
#define GENETIC_H

void initializeRandomGenerator();
double getTime();
unsigned int calculateCost(unsigned int solution_index);
int validSolution (unsigned int solution_index);
void stepGeneration();
int notChosen(unsigned int node, int *solution);
unsigned int getFirstNotChosenNode (int *solution);
int* crossover (unsigned int parent1_index, unsigned int parent2_index);
void printSolution(int *solution);
void calculateFitness();
void createMatrixFromData(char *filename);
void printSolutionInPopulation(int solution_index);

#endif

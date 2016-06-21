#ifndef GENETIC_H
#define GENETIC_H

void initGenetic(char *instance_filename);
void stepGeneration();
int* crossover (unsigned int parent1_index, unsigned int parent2_index);
void mutate(int *solution);
void calculateFitness_alles();
void calculateFitness_valer();
unsigned int selectSolutionFromFitness_alles(int restriction);
unsigned int selectSolutionFromFitness_valer(int restriction);
unsigned int calculateCost(unsigned int solution_index);
double getTime();
void initializeRandomGenerator();
float getSolutionsAverageCost();
int validSolution (unsigned int solution_index);
int notChosen(unsigned int node, int *solution);
unsigned int getFirstNotChosenNode (int *solution);
unsigned int getNotChosenNodeFromIndex (int *solution, unsigned int node_to_search);
unsigned int selectLeastFit();
unsigned int bestSolutionFromPopulation();
void printSolution(int *solution);
void printSolutionInPopulation(int solution_index);
void createMatrixFromData(char *filename);


#endif

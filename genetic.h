#ifndef GENETIC_H
#define GENETIC_H

void initGenetic(char *instance_filename, unsigned int pop_size, unsigned int children_per_gen);
void stepGeneration();
int* crossover (unsigned int parent1_index, unsigned int parent2_index);
int* crossover_2 (unsigned int parent1_index, unsigned int parent2_index);
void mutate(int *solution);
void calculateFitness();
unsigned int selectSolutionFromFitness(int restriction);
unsigned int calculateCost(unsigned int solution_index);
double getTime();
void initializeRandomGenerator();
int validSolution (unsigned int solution_index);
int notChosen(unsigned int node, int *solution);
unsigned int getFirstNotChosenNode (int *solution);
unsigned int getNotChosenNodeFromIndex (int *solution, unsigned int node_to_search);
unsigned int selectLeastFit();
unsigned int bestSolutionFromPopulation();
void printSolutionInPopulation(int solution_index);
void createMatrixFromData(char *filename);


#endif

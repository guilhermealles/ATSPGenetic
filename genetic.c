/*
 * Guilherme Alles e Rafael Valer
 *
 * An instance of the ATSP is represented by a NxN matrix
 * containing the costs from node i to node j.
 * Each possible solution is an array with N elements,
 * representing the order in which the nodes are visited.
 * Each node must appear exactly once in a valid solution.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Solutions population
#define POPULATION_COUNT 10

const int instance_size = 5;
const int instance[5][5] = {
    {999999, 3, 2, 6, 4},
    {3, 999999, 8, 999999, 6},
    {10, 3, 999999, 7, 6},
    {3, 999999, 6, 999999, 2},
    {6, 4, 999999, 8, 999999}
};

const int population[POPULATION_COUNT][5] = {
    {0, 1, 2, 3, 4},
    {1, 2, 3, 4, 0},
    {2, 3, 4, 0, 1},
    {3, 4, 0, 1, 2},
    {4, 0, 1, 2, 3},
    {1, 0, 2, 3, 4},
    {1, 2, 0, 3, 4},
    {1, 2, 3, 0, 4},
    {3, 0, 1, 2, 4},
    {2, 0, 4, 3, 1}
};

int main(int argc, char **argv) {
    initializeRandomGenerator();

    int *child = crossover(0,1);
    printSolution(child);
    free(child);

    return 0;
}

void initializeRandomGenerator() {
    srand(time(NULL));
}

unsigned int calculateCost(unsigned int solution_index) {
    int i=0, j=0, total_cost=0;

    if (validSolution(solution_index)) {
        for (i=0; i<instance_size; i++) {
            j = (i+1) % instance_size;
            // Add the cost of going from node i to node j0
            total_cost += instance [i][j];
        }
    }
    else {
        return 999999;
    }
    return total_cost;
}

int validSolution (unsigned int solution_index) {
    int i=0, j=0, found=0;
    for (i=0; i<instance_size; i++) {
        for(j=0; j<instance_size; j++) {
            if (population[solution_index][j] == i) {
                found++;
            }
        }
        if (found != 1)
            return 0;
        else
            found = 0;
    }
    return 1;
}

int notChosen(unsigned int node, int *solution) {
    int i;
    for(i=0; i<instance_size; i++) {
        if (solution[i] == node)
            return 0;
        else if (solution[i] == -1)
            return 1;
    }
    return 1;
}

// Given a solution, return the first node that does not yet
// appear on the solution. Returns -1 if not found.
unsigned int getFirstNotChosenNode (int *solution) {
    int i;
    for (i=0; i<instance_size; i++) {
        if (notChosen(i, solution)) {
            return i;
        }
    }

    return -1;
}

// Returns a new child in memory. NOTE: The child which will
// be substituted MUST be freed!!
int* crossover (unsigned int parent1_index, unsigned int parent2_index) {
    int* child = malloc(sizeof(int) * instance_size);
    int i=0;
    for (i=0; i<instance_size; i++) {
        child[i]=-1;
    }

    // randomly selects the first city from one of
    // the parents
    int parent = rand()%2;
    child[0] = (parent==0) ? population[parent1_index][0] : population[parent2_index][0];
    printf("Pegou a cidade %d como começo.\n", child[0]);

    for (i=1; i<instance_size; i++) {
        // Calculate the distances of the two cities leaving
        // the previous city
        int parent1_nextcity = population[parent1_index][i];
        int parent1_nextcity_cost = instance[child[i-1]][parent1_nextcity];

        int parent2_nextcity = population[parent2_index][i];
        int parent2_nextcity_cost = instance[child[i-1]][parent2_nextcity];

        if ((parent1_nextcity_cost<=parent2_nextcity_cost) && notChosen(parent1_nextcity, child)) {
            child[i] = parent1_nextcity;
        }
        else if ((parent2_nextcity_cost<parent1_nextcity_cost) && notChosen(parent2_nextcity, child)) {
            child[i] = parent2_nextcity;
        }
        else {
            int first = getFirstNotChosenNode(child);
            if (first == -1) {
                fprintf(stderr, "Isso não deve acontecer.\n");
                exit(EXIT_FAILURE);
            }
            child[i] = first;
        }
    }

    return child;
}

void printSolution(int *solution) {
    printf("Solution: ");
    int i, total_cost = 0;
    for(i=0; i<instance_size-1; i++) {
        if (i>0)
            total_cost += instance[solution[i-1]][solution[i]];
        printf("%d ->", solution[i]);
    }
    total_cost += instance[solution[i-1]][solution[i]];
    printf("%d.\nTotal cost: %d.\n", solution[i], total_cost);
}

// Advance to the next generation
void stepGeneration() {
    // Select a group of best fit solutions
    // cross them over
    // randomly mutate their results
}

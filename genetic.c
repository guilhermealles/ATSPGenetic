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
#include <string.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>
#include "genetic.h"

#define INFINITE 999999

unsigned int population_size = 50;
int children_per_generation = 15;

int instance_size;
int **instance;

int **population;

unsigned int *population_costs;
unsigned long long *population_fitness;
double *cumulative_fitness;
float population_average_cost;

int solutions_fitness_sum;

void initGenetic(char *instance_filename, unsigned int pop_size, unsigned int children_per_gen) {
    initializeRandomGenerator();
    children_per_generation = children_per_gen;
    population_size = pop_size;
    createMatrixFromData(instance_filename);

    long int i, j;
    // Allocate populartion matrix and set it to -1
    population = (int**) malloc (sizeof(int*) * population_size);
    for (i = 0; i<population_size; i++) {
        population[i] = (int*) malloc (sizeof(int) * instance_size);
        for (j=0; j<instance_size; j++) {
            population[i][j] = -1;
        }
    }

    // Initialize the population randomly
    for (i=0; i<population_size; i++) {
        for (j=0; j<instance_size; j++) {
            int random_node = rand() % instance_size;
            population[i][j] = getNotChosenNodeFromIndex(population[i], random_node);
        }
    }

    // Allocate arrays to calculate fitness
    population_costs = (unsigned int*) malloc (sizeof(unsigned int) * population_size);
    population_fitness = (unsigned long long*) malloc (sizeof(unsigned long long) * population_size);
    cumulative_fitness = (double*) malloc (sizeof(double) * population_size);
}

// Advance to the next generation
void stepGeneration() {
    calculateFitness();
    int parent1_index = selectSolutionFromFitness(-1);
    int parent2_index = selectSolutionFromFitness(parent1_index);

    int k;
    for (k = 0; k < children_per_generation; k++) {
        int *child = crossover(parent1_index, parent2_index);

        int mutation_prob = rand() % 100;
        if (mutation_prob <= 1) {
            mutate(child);
        }

        int solution_to_die = selectLeastFit();
        free(population[solution_to_die]);

        population[solution_to_die] = child;
        population_costs[solution_to_die] = calculateCost(solution_to_die);
        population_fitness[solution_to_die] = INFINITE; //don't let another son take his place


    }
}

// Returns a new child in memory. NOTE: The solution which will
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

    for (i=1; i<instance_size; i++) {
        // Calculate the distances of the two cities leaving
        // the previous city
        int parent1_nextcity = population[parent1_index][i];
        int parent1_nextcity_cost = instance[child[i-1]][parent1_nextcity];

        int parent2_nextcity = population[parent2_index][i];
        int parent2_nextcity_cost = instance[child[i-1]][parent2_nextcity];

        // Choose the city with the lowest cost
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

// The second crossover method, which yielded worse results
int* crossover_2 (unsigned int parent1_index, unsigned int parent2_index) {
    int* child = malloc(sizeof(int) * instance_size);

    int *parent2_copy = malloc(sizeof(int) * instance_size);
    memcpy(parent2_copy, population[parent2_index], (sizeof(int) * instance_size));

    int parent_split = rand() % instance_size;

    int i;
    for (i=0; i<parent_split; i++) {
        if (population[parent1_index][i] != parent2_copy[i]) {
            int node_index_on_parent2;
            for (node_index_on_parent2 = i; node_index_on_parent2<instance_size; node_index_on_parent2++) {
                if (population[parent1_index][i] == parent2_copy[node_index_on_parent2]) {
                    break;
                }
            }

            int swp = parent2_copy[i];
            parent2_copy[i] = parent2_copy[node_index_on_parent2];
            parent2_copy[node_index_on_parent2] = swp;
        }
    }

    for(i=0; i<parent_split; i++) {
        child[i] = population[parent1_index][i];
    }
    for(; i<instance_size; i++) {
        child[i] = parent2_copy[i];
    }
    free(parent2_copy);

    return child;
}

// Mutation, implemented by swapping two random nodes from a solution
void mutate(int *solution) {
    int swap_node_1 = rand() % instance_size;
    int swap_node_2 = rand() % instance_size;

    int tmp = solution[swap_node_1];
    solution[swap_node_1] = solution[swap_node_2];
    solution[swap_node_2] = tmp;
}

void calculateFitness() {
    int i;
    unsigned long long int costs_sum = 0;
    for (i=0; i<population_size; i++) {
        int cost_for_population = calculateCost(i);
        population_costs[i] = cost_for_population;
        costs_sum += population_costs[i];
    }

    unsigned long long int fitness_sum=0;
    for (i=0; i<population_size; i++) {
        population_fitness[i] = costs_sum - population_costs[i];
        fitness_sum += population_fitness[i];
    }

    cumulative_fitness[0] = population_fitness[0]/fitness_sum;
    for (i=1; i<population_size; i++) {
        cumulative_fitness[i] = cumulative_fitness[i-1] + ((double)population_fitness[i]/(double)fitness_sum);
    }
}

// Selects a solution from the population considering the
// cumulative fitness as a likelihood measure. The restriction
// parameter is used to avoid selecting the same solution twice
unsigned int selectSolutionFromFitness(int restriction) {
    double random = (rand()%100)/100.0;
    if ((random >= 0) && (random < cumulative_fitness[0]))
        return 0;

    int i;
    for (i=1; i<population_size; i++) {
        if ((random >= cumulative_fitness[i-1]) && (random < cumulative_fitness[i])) {
            if (i != restriction)
                return i;
            else
                return selectSolutionFromFitness(restriction);
        }
    }

    return population_size-1;
}

unsigned int calculateCost(unsigned int solution_index) {
    int i=0, j=0, total_cost=0;

    if (validSolution(solution_index)) {
        for (i=0; i<instance_size; i++) {
            j = (i+1) % instance_size;
            // Add the cost of going from node i to node j0
            total_cost += instance[population[solution_index][i]][population[solution_index][j]];
        }
    }
    else {
        return INFINITE;
    }
    return total_cost;
}

double getTime() {
    struct timeval tr;
    gettimeofday(&tr, NULL);
    return (double)tr.tv_sec;
}

void initializeRandomGenerator() {
    srand((unsigned int)time(NULL));
}

int validSolution (unsigned int solution_index) {
    int i=0, j=0, found=0;
    for (i=0; i<instance_size; i++) {
        for(j=0; j<instance_size; j++) {
            if (population[solution_index][j] == i)  {
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

// Given a solution, return the first node that does not yet
// appear on the solution. Start counting from node_to_search
unsigned int getNotChosenNodeFromIndex (int *solution, unsigned int node_to_search) {
    int i;
    for (i=0; i<instance_size; i++) {
        if (notChosen(node_to_search, solution)) {
            return node_to_search;
        }
        node_to_search = (node_to_search+1) % instance_size;
    }

    return -1;
}

// Returns the index of the least fit solution in the population
unsigned int selectLeastFit() {
    unsigned long long int lowest_fitness = population_fitness[0];
    unsigned int least_fit_index = 0;
    unsigned int i;
    for (i=1; i<population_size; i++) {
        if (population_fitness[i] < lowest_fitness) {
            lowest_fitness = population_fitness[i];
            least_fit_index = i;
        }
    }
    return least_fit_index;
}

unsigned int bestSolutionFromPopulation() {
    calculateFitness();
    unsigned int j;
    int lowest_cost = population_costs[0];
    int lowest_cost_index = 0;
    for (j=0; j<population_size; j++) {
        if (population_costs[j] < lowest_cost) {
            lowest_cost = population_costs[j];
            lowest_cost_index = j;
        }
    }

    return lowest_cost_index;
}

void printSolutionInPopulation(int solution_index) {
    printf("Solution: ");
    int i;
    for(i=0; i<instance_size-1; i++) {
        printf("%d ->", population[solution_index][i]);
    }
    printf("%d.\nTotal cost: %d.\n", population[solution_index][i], calculateCost(solution_index));
}

void createMatrixFromData(char *filename){
    FILE *data;
    data = fopen(filename, "r");

    if( !data ){
        printf("\nError in reading from text file.\n");
        return;
    }

    // pula 3 linhas
    int i;
    for (i=0; i<3; i++) {
        char c = fgetc(data);
        while (c != '\n') {
            c = fgetc(data);
        }
    }

    fscanf(data, "DIMENSION: %u", &instance_size);
    printf("Population dimension: %u", instance_size);

    // pula 4 linhas
    for (i=0; i<4; i++) {
        char c = fgetc(data);
        while (c != '\n') {
            c = fgetc(data);
        }
    }

    instance = (int **) malloc(sizeof(int*) * instance_size);
    for (i=0; i<instance_size; i++) {
        instance[i] = (int*) malloc(sizeof(int) * instance_size);
    }

    int j;
    for(i = 0; i < instance_size; i++){
        for(j = 0; j < instance_size; j++){
            fscanf(data, "%i", &instance[i][j]);
        }
    }

    fclose(data);
    return;
}

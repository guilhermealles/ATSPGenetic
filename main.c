#include <stdio.h>
#include <stdlib.h>
#include "genetic.h"

#define ITERATIONS_COUNT 9999999

extern int *population_costs;

int main (int argc, char **argv) {
    if (argc != 6) {
        fprintf(stderr, "Usage: %s filename <max iterations> <population size> <children per generation> <time limit in seconds>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    unsigned int time_limit = (unsigned int) strtol(argv[5], NULL, 10);
    unsigned int pop_size = (unsigned int) strtol(argv[3], NULL, 10);
    unsigned int ch_per_gen = (unsigned int) strtol(argv[4], NULL, 10);
    initGenetic(argv[1], pop_size, ch_per_gen);
    //printInstance();

    unsigned long int i=0;
    double begin_time, end_time, elapsed_time=0;
    begin_time = getTime();
    end_time = getTime();
    while ((i < ITERATIONS_COUNT) && (elapsed_time < time_limit)) {
        stepGeneration();
        i++;
        end_time = getTime();
        elapsed_time = end_time - begin_time;
    }

    printf("\n@@@ Generation #%li:\n", i);
    printSolutionInPopulation(bestSolutionFromPopulation());
    printf("Execution time = %.2f\n\n", elapsed_time);

    return 0;
}

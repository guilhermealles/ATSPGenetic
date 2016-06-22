#include <stdio.h>
#include <stdlib.h>
#include "genetic.h"

#define ITERATIONS_COUNT 9999999

extern int *population_costs;

int main (int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s filename <time limit in seconds>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    unsigned int time_limit = (unsigned int) strtol(argv[2], NULL, 10);
    initGenetic(argv[1]);
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

    return 0;
}

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

    unsigned long int i=0;
    double begin_time, end_time;
    begin_time = getTime();
    end_time = getTime();
    while ((i < ITERATIONS_COUNT) && ((end_time-begin_time) < time_limit)) {
        stepGeneration();
        i++;
        end_time = getTime();
    }

    printf("\n@@@ Generation #%li:\n", i);
    printSolutionInPopulation(bestSolutionFromPopulation());

    return 0;
}

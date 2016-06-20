#!/bin/bash

# Build target
gcc genetic.c -Wall -O3 -o genetic

./genetic ./instances/br17.atsp 3610 > outputs/br17.txt
./genetic ./instances/ft70.atsp 3610 > outputs/ft70.txt
./genetic ./instances/ftv33.atsp 3610 > outputs/ftv33.txt
./genetic ./instances/ftv44.atsp 3610 > outputs/ftv44.txt
./genetic ./instances/ftv55.atsp 3610 > outputs/ftv55.txt
./genetic ./instances/ftv170.atsp 3610 > outputs/ftv170.txt
./genetic ./instances/kro124p.atsp 3610 > outputs/kro124p.txt
./genetic ./instances/rbg323.atsp 3610 > outputs/rbg323.txt
./genetic ./instances/rbg358.atsp 3610 > outputs/rbg358.txt
./genetic ./instances/rbg403.atsp 3610 > outputs/rbg403.txt

#!/bin/bash

# Build target
make clean
make

./genetic ./instances/br17.atsp 1800 > outputs/1800s_br17.txt
./genetic ./instances/ft70.atsp 1800 > outputs/1800s_ft70.txt
./genetic ./instances/ftv33.atsp 1800 > outputs/1800s_ftv33.txt
./genetic ./instances/ftv44.atsp 1800 > outputs/1800s_ftv44.txt
./genetic ./instances/ftv55.atsp 1800 > outputs/1800s_ftv55.txt
./genetic ./instances/ftv170.atsp 1800 > outputs/1800s_ftv170.txt
./genetic ./instances/kro124p.atsp 1800 > outputs/1800s_kro124p.txt
./genetic ./instances/rbg323.atsp 1800 > outputs/1800s_rbg323.txt
./genetic ./instances/rbg358.atsp 1800 > outputs/1800s_rbg358.txt
./genetic ./instances/rbg403.atsp 1800 > outputs/1800s_rbg403.txt

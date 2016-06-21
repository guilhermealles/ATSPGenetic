#!/bin/bash

# Build target
make clean
make

./genetic ./instances/br17.atsp 40 > outputs/40s_br17.txt
./genetic ./instances/ft70.atsp 40 > outputs/40s_ft70.txt
./genetic ./instances/ftv33.atsp 40 > outputs/40s_ftv33.txt
./genetic ./instances/ftv44.atsp 40 > outputs/40s_ftv44.txt
./genetic ./instances/ftv55.atsp 40 > outputs/40s_ftv55.txt
./genetic ./instances/ftv170.atsp 40 > outputs/40s_ftv170.txt
./genetic ./instances/kro124p.atsp 40 > outputs/40s_kro124p.txt
./genetic ./instances/rbg323.atsp 40 > outputs/40s_rbg323.txt
./genetic ./instances/rbg358.atsp 40 > outputs/40s_rbg358.txt
./genetic ./instances/rbg403.atsp 40 > outputs/40s_rbg403.txt

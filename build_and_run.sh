#!/bin/bash

# Build target
make clean
make

./genetic ./instances/br17.atsp 120 > outputs/a_120s_br17.txt &
./genetic ./instances/ft70.atsp 120 > outputs/a_120s_ft70.txt &
./genetic ./instances/ftv33.atsp 120 > outputs/a_120s_ftv33.txt &
./genetic ./instances/ftv44.atsp 120 > outputs/a_120s_ftv44.txt &
./genetic ./instances/ftv55.atsp 120 > outputs/a_120s_ftv55.txt &
./genetic ./instances/ftv170.atsp 120 > outputs/a_120s_ftv170.txt &
./genetic ./instances/kro124p.atsp 120 > outputs/a_120s_kro124p.txt &
./genetic ./instances/rbg323.atsp 120 > outputs/a_120s_rbg323.txt &
./genetic ./instances/rbg358.atsp 120 > outputs/a_120s_rbg358.txt &
./genetic ./instances/rbg403.atsp 120 > outputs/a_120s_rbg403.txt &

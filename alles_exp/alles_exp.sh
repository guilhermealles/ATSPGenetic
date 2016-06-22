#!/bin/bash

# Clean and build targets
cd ..
make clean
make

for (( i = 0; i < 5; i++ )); do
    echo "=============================\n\n" >> alles_1min.txt
    ./genetic ./instances/br17.atsp 60 >> alles_1min.txt &
    ./genetic ./instances/ft70.atsp 60 >> alles_1min.txt &
    ./genetic ./instances/ftv33.atsp 60 >> alles_1min.txt &
    ./genetic ./instances/ftv44.atsp 60 >> alles_1min.txt

    sleep 65

    ./genetic ./instances/ftv55.atsp 60 >> alles_1min.txt &
    ./genetic ./instances/ftv170.atsp 60 >> alles_1min.txt &
    ./genetic ./instances/kro124p.atsp 60 >> alles_1min.txt &
    ./genetic ./instances/rbg323.atsp 60 >> alles_1min.txt

    sleep 65

    ./genetic ./instances/rbg358.atsp 60 >> alles_1min.txt&
    ./genetic ./instances/rbg403.atsp 60 >> alles_1min.txt
done

for (( i = 0; i < 5; i++ )); do
    echo "=============================\n\n" >> alles_5min.txt
    ./genetic ./instances/br17.atsp 300 >> alles_5min.txt &
    ./genetic ./instances/ft70.atsp 300 >> alles_5min.txt

    sleep 330

    ./genetic ./instances/ftv33.atsp 300 >> alles_5min.txt &
    ./genetic ./instances/ftv44.atsp 300 >> alles_5min.txt

    sleep 330

    ./genetic ./instances/ftv55.atsp 300 >> alles_5min.txt &
    ./genetic ./instances/ftv170.atsp 300 >> alles_5min.txt

    sleep 330

    ./genetic ./instances/kro124p.atsp 300 >> alles_5min.txt &
    ./genetic ./instances/rbg323.atsp 300 >> alles_5min.txt

    sleep 330

    ./genetic ./instances/rbg358.atsp 300 >> alles_5min.txt
    ./genetic ./instances/rbg403.atsp 300 >> alles_5min.txt
done

for (( i = 0; i < 5; i++ )); do
    echo "=============================\n\n" >> alles_10min.txt
    ./genetic ./instances/br17.atsp 600 >> alles_10min.txt &
    ./genetic ./instances/ft70.atsp 600 >> alles_10min.txt

    sleep 660

    ./genetic ./instances/ftv33.atsp 600 >> alles_10min.txt &
    ./genetic ./instances/ftv44.atsp 600 >> alles_10min.txt

    sleep 660

    ./genetic ./instances/ftv55.atsp 600 >> alles_10min.txt &
    ./genetic ./instances/ftv170.atsp 600 >> alles_10min.txt

    sleep 660

    ./genetic ./instances/kro124p.atsp 600 >> alles_10min.txt &
    ./genetic ./instances/rbg323.atsp 600 >> alles_10min.txt

    sleep 660

    ./genetic ./instances/rbg358.atsp 600 >> alles_10min.txt
    ./genetic ./instances/rbg403.atsp 600 >> alles_10min.txt
done

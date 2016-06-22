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
    ./genetic ./instances/ftv44.atsp 60 >> alles_1min.txt &

    sleep 65

    ./genetic ./instances/ftv55.atsp 60 >> alles_1min.txt &
    ./genetic ./instances/ftv170.atsp 60 >> alles_1min.txt &
    ./genetic ./instances/kro124p.atsp 60 >> alles_1min.txt &
    ./genetic ./instances/rbg323.atsp 60 >> alles_1min.txt &

    sleep 65

    ./genetic ./instances/rbg358.atsp 60 >> alles_1min.txt &
    ./genetic ./instances/rbg403.atsp 60 >> alles_1min.txt &

    sleep 65
done

for (( i = 0; i < 5; i++ )); do
    echo "=============================\n\n" >> alles_30min.txt
    ./genetic ./instances/br17.atsp 1800 >> alles_30min.txt &
    ./genetic ./instances/ft70.atsp 1800 >> alles_30min.txt &
    ./genetic ./instances/ftv33.atsp 1800 >> alles_30min.txt &
    ./genetic ./instances/ftv44.atsp 1800 >> alles_30min.txt &

    sleep 1860

    ./genetic ./instances/ftv55.atsp 1800 >> alles_30min.txt &
    ./genetic ./instances/ftv170.atsp 1800 >> alles_30min.txt &
    ./genetic ./instances/kro124p.atsp 1800 >> alles_30min.txt &
    ./genetic ./instances/rbg323.atsp 1800 >> alles_30min.txt &

    sleep 1860

    ./genetic ./instances/rbg358.atsp 1800 >> alles_30min.txt &
    ./genetic ./instances/rbg403.atsp 1800 >> alles_30min.txt &

    sleep 1860
done

#!/bin/bash

g++ -c *.cpp
g++ *.o -o game -lsfml-graphics -lsfml-window -lsfml-system -lGL -lsfml-audio
./game


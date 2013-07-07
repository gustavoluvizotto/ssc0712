#!/bin/bash

g++ -c *.cpp `pkg-config --libs --cflags playerc++` -lm
g++ -o programa *.o `pkg-config --libs --cflags playerc++` -lm


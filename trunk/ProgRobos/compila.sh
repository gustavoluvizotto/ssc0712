#!/bin/bash
g++ -o a.out main.cpp `pkg-config --cflags --libs playerc++`

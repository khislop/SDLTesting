#!/bin/bash

g++ main.cpp button.cpp init.cpp texture.cpp dialogue.cpp main_menu.cpp room_home.cpp -std=c++11 `pkg-config --cflags sdl2 SDL2_image SDL2_ttf` `pkg-config --libs sdl2 SDL2_image SDL2_ttf` -lstdc++ -o main 


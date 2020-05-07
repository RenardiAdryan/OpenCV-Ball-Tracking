#include <iostream>
#include <stdio.h>
#include <cstdlib>

int main (){

system("g++ -ggdb `pkg-config --cflags opencv` -o output main.cpp `pkg-config --libs opencv`");


}

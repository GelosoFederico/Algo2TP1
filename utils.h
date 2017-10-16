#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include "Array.h"

#define MSG_ERROR_DISTANCE_DIMENSION "Error al calcular distancia: los elementos no tienen la misma cantidad de dimensiones"

using namespace std;

void move_to_next_line(istream * ptr_iss);
double getDistance(Array <double> &coord1, Array <double> &coord2);
int find_min_distance_linear(Array < Array <double> >& database,Array <double> & query);

#endif

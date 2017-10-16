#include <iostream>
#include <cstdlib>
#include "utils.h"
#include "Array.h"

void move_to_next_line(std::istream * ptr_iss)
{
	char ch;

	if(ptr_iss)
		while( ((ch = (ptr_iss->get()) ) != '\n') && (!ptr_iss->eof()));
}

double getDistance(Array <double> &coord1, Array <double> &coord2) 
//devuelve el cuadrado de la distancia entre vectores de double coord1 y coord2
{
    size_t i;
    double s=0;
    if(coord1.getSize()==coord2.getSize())
    {
        for(i=0;i<coord1.getSize();i++)
        {
            s+=((coord1[i]-coord2[i])*(coord1[i]-coord2[i]));
        }
        return s;
    }
    else
        cerr<<MSG_ERROR_DISTANCE_DIMENSION <<endl;
    return -1;
}

int find_min_distance_linear(Array < Array <double> >& database,Array <double> & query)
{
	int database_dimension, min_pos=0;
	double min_distance,new_distance;

	database_dimension= database.getSize(); 
	min_distance = getDistance(database[0],query);
	
	for (int i=1; i< database_dimension;++i){
		new_distance = getDistance(database[i],query);
		if(new_distance < min_distance){
			min_distance = new_distance;
			min_pos = i;
		}
	}
	return min_pos;
}

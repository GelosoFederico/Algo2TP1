#ifndef KDTREE_H
#define KDTREE_H

#include <iostream>

#define NUM_DIMENSIONS 2 //Esto sería mejor como un atributo de clase en realidad
#define MAX_NUM_LEAF 3
#define MSG_ERROR_DIMENSIONS "Dimensiones distintas"

class Nodo;

typedef enum{
	MAX=0,
	MIN=1
}flag_min_max;

typedef enum{
	MEDIAN,
	HALF,
	AVERAGE
}heuristic_t;

class KDTree{
	private:
		Nodo* _root;
		Nodo* find_closest_node(Array <double> &);
		heuristic_t _heuristic;
		KDTree();
	public:
		KDTree(Array <Array <double> >& points,heuristic_t heuristic=MEDIAN);
		~KDTree();
		Array <double> find_min_distance(Array <double>&);
};

int split(Array <Array <double> > & points, char dimension, double break_point, Array <Array <double> >*& arr_left,Array <Array <double> >*& arr_right);
double find_max_min_in_dimension(Array <Array <double> >& points,flag_min_max flag,int dimension);
Array <double> find_max_min(Array <Array <double> >& points,flag_min_max flag);
double find_split_point(Array <Array <double> >& points,char bkd,heuristic_t heuristic);

double find_half(Array< Array <double> > & points, char bkd);
double rnd_average(Array <Array <double> >& points, char coord);
double quickselect(Array <Array <double> >& points, char coord, size_t left, size_t right, size_t k);
size_t quickpartition (Array <Array <double> >& points, size_t dimension, size_t left, size_t right, size_t pivotindex);
void arrayswap(Array <double> &a, Array <double> &b);
#endif

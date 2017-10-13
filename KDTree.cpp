// Implementación del KDTree para TP1 de algo2.
// TODO: funciones en el constructor de nodo, kdtree, tests

#include <iostream>
#include "Array.h"
#include "KDTree.h"


using namespace std;


class Nodo {
    private:

        Array <double> _botleft;
        Array <double> _topright;//Estos son la bounded box. No sé si tiene mas sentido un solo arreglo o 4 dobles separados

        char _breakdimension;	//Dimensión por la que dividió
        double _breakpoint;	//Punto por el que corta
        Array <Array <double> > _tiberium_points; // Puntos dentro de esta bounding box

        Nodo* _branch_left;
        Nodo* _branch_right;
        Nodo* _father;
    public:
        Nodo(Array <Array <double> >& Points,char bkd,Nodo* Father=NULL);
        virtual ~Nodo() {}//de nuevo, habria que preguntar lo del destructor virtual porque no lo termine de entender
	//Getters
        double get_breakpoint() ;
        char get_breakdimension();
        Array <double> get_topright();
        Array <double> get_botleft();
	Array <Array <double> >& get_points();
	//Setters
        void set_breakpoint(double );
        void set_breakdimension(char );
	void set_region();
	void set_topright(Array <double>& );
	void set_botleft(Array <double>& );
	void set_points(Array <Array <double> >& );
	void set_father(Nodo* &);
	void set_branch_left(Nodo* &nodo);
	void set_branch_right(Nodo* &nodo); 
};
Nodo::Nodo(Array <Array <double> >& Points,char bkd,Nodo* Father){
	this->set_breakdimension(bkd);
	this->set_points(Points);
	this->set_father(Father);
       	this->set_region();
		
	//Ya cargo todo, pero tiene que ver si este será una hoja (menos de x puntos) o si tiene que separarse
	if((this->get_points()).getSize()>MAX_NUM_LEAF){
       		this->set_breakpoint(find_split_point(Points,bkd));
		Array <Array <double> > * points_right;
		Array <Array <double> > * points_left;
		split(get_points(),get_breakdimension(),get_breakpoint(),points_left,points_right);
		Nodo * nodo_left;
		Nodo * nodo_right;
		nodo_left = new Nodo(*points_left,(bkd+1)%NUM_DIMENSIONS,this);
		nodo_right =new Nodo(*points_right,(bkd+1)%NUM_DIMENSIONS,this);
		this->set_branch_left(nodo_left);
		this->set_branch_right(nodo_right);
		delete points_left;
		delete points_right;
	}
}
double Nodo::get_breakpoint() {
	return _breakpoint;
}
char Nodo::get_breakdimension()
{
	return _breakdimension;
}
Array <double> Nodo::get_topright()
{
	return _topright;
}
Array <double> Nodo::get_botleft()
{
    return _botleft;
}
Array <Array <double> >& Nodo::get_points()
{
	return _tiberium_points;
}
void Nodo::set_breakpoint(double bkp)
{
    _breakpoint=bkp;
}
void Nodo::set_breakdimension(char bkd)
{
    _breakdimension=bkd;
}
void Nodo::set_region()
{
	this->set_topright(find_max_min(this->get_points(),MAX));
	this->set_botleft(find_max_min(this->get_points(),MIN));
}
void Nodo::set_topright(Array <double> &v)
{
	if(v.getSize() == NUM_DIMENSIONS){
		_topright = v;
	}
	else{
		cerr<< MSG_ERROR_DIMENSIONS<< endl;
		exit(1);
	}
}
void Nodo::set_botleft(Array <double> &v)
{
	if(v.getSize() == NUM_DIMENSIONS){
		_botleft = v;
	}
	else{
		cerr<< MSG_ERROR_DIMENSIONS<< endl;
		exit(1);
	}
}
void Nodo::set_points(Array <Array <double> > & new_points)
{
	_tiberium_points=new_points;
}
void Nodo::set_father(Nodo* &new_father)
{
	_father = new_father;
}
void Nodo::set_branch_left(Nodo* &nodo) {
	_branch_left = nodo;
}
void Nodo::set_branch_right(Nodo* &nodo) {
	_branch_right = nodo;
}

class KDTree{
	private:
		Nodo* _root;
	public:
		KDTree(){_root=NULL;}	
		KDTree(Nodo * nodo){_root = nodo;}
		~KDTree(){delete _root;}	
};

int split(Array <Array <double> > & points, char dimension, double break_point, Array <Array <double> >*& arr_left,Array <Array <double> >*& arr_right)
{
	arr_left = new Array< Array< double> >();
	arr_right = new Array< Array< double> >();
	for (int i=0;i<points.getSize();++i){
		if((points[i])[(int)dimension] < break_point){
			arr_left->append(points[i]);
		}
		else{
			arr_right->append(points[i]);
		}
	}
	return 0;
} 

double find_split_point(Array <Array <double> >& points,int bkd)
{
// Como hacemos con la heurística? Le paso un puntero a funcion? O un tipo enumerativo y solo aca se saben las heuristicas (diccionario de punteros a funcion)
// Impongo el punto del medio
	double max, min;

	max = find_max_min_in_dimension(points,MAX,bkd);
	min = find_max_min_in_dimension(points,MIN,bkd);
	return (max+min)/2;
}

Array <double> &find_max_min(Array <Array <double> >& points,flag_min_max flag)
{
// Este es para topright y bottom. Hace el maximo de cada dimension
// 
	Array <double> * v;

	v = new Array <double>(NUM_DIMENSIONS);
	for(int i=0;i<NUM_DIMENSIONS;++i){
		(*v)[i] = find_max_min_in_dimension(points,flag,i);
	}
	return *v;
	
}
double find_max_min_in_dimension(Array <Array <double> >& points,flag_min_max flag,int dimension)
{
	double top;

	top = (points[0])[dimension];
	if(flag == MIN){
		for(int i =1; i<points.getSize();++i){
			if((points[i])[dimension]<top)
				top = (points[i])[dimension];
		}
	}
	if(flag == MAX){
		for(int i =1; i<points.getSize();++i){
			if((points[i])[dimension]>top)
				top = (points[i])[dimension];
		}
	}
	return top;
}

int main (void)
{
	
	return 0;
}

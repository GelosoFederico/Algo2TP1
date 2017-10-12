// Implementación del KDTree para TP1 de algo2.
// TODO: funciones en el constructor de nodo, kdtree, tests

#include <iostream>
#include <Array.h>

#define NUM_DIMENSIONS 2 //Esto sería mejor como un atributo de clase en realidad

using namespace std;

int split(Array <Array <double> > & points, char dimension, double break_point, Array <double>* arr_left,Array <double>* arr_right);

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
	Array <Array <double> > get_points();
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
}
Nodo::Nodo(Array <Array <double> >& Points,char bkd,Nodo* Father=NULL){
	this->set_breakdimension(bkd);
	this->set_points(points);
	this->set_father(Father);
       	this->set_region();
		
	//Ya cargo todo, pero tiene que ver si este será una hoja (menos de x puntos) o si tiene que separarse
	if(get_points().getSize>MAX_NUM_LEAF){
       		this->set_breakpoint(find_split_point(Points,bkd));
		Array <Array <double> > * points_right;
		Array <Array <double> > * points_left;
		split(get_points(),get_breakdimension(),get_breakpoint(),points_left,points_right);
		set_branch_left(new Nodo(*points_left,(bkd+1)%NUM_DIMENSIONS,this);
		set_branch_right(new Nodo(*points_right,(bkd+1)%NUM_DIMENSIONS,this);
		delete points_left;
		delete points_right;
	}
}
Nodo::double get_breakpoint() {
	return _breakpoint;
}
Nodo::char get_breakdimension()
{
	return _breakdimension;
}
Nodo::Array <double> get_topright()
{
	return _topright;
}
Nodo::Array <double> get_botleft()
{
    return _botleft;
}
Nodo::void set_breakpoint(double bkp)
{
    _breakpoint=bkp;
}
Nodo::void set_breakdimension(char bkd)
{
    _breakdimension=bkd;
}
Nodo::void set_region()
{
	this->set_topright(find_max_min(this->get_points(),MAX));
	this->set_botleft(find_max_min(this->get_points(),MIN));
}
Nodo::void set_topright(Array <double> &v))
{
	if(v.getSize == NUM_DIMENSIONS){
		_topright = v;
	}
	else{
		cerr<< MSG_ERROR_DIMENSIONS<< endl;
		exit(1);
	}
}
Nodo::void set_botleft(Array <double> &v))
{
	if(v.getSize == NUM_DIMENSIONS){
		_botleft = v;
	}
	else{
		cerr<< MSG_ERROR_DIMENSIONS<< endl;
		exit(1);
	}
}
Nodo::void set_points(Array <Array <double> > & new_points)
{
	_tiberium_points=new_points;
}
Nodo::void set_father(Nodo* &new_father)
{
	_father = new_father;
}
Nodo::void set_branch_left(Nodo* &nodo) {
	_branch_left = nodo;
}
Nodo::void set_branch_right(Nodo* &nodo) {
	_branch_right = nodo;
}

class KDTree{
	private:
		Nodo* _root;
	public:
		KDTree(){root=NULL;}	
		KDTree(){}	
		~KDTree(){root=NULL;}	
}

int split(Array <Array <double> > & points, char dimension, double break_point, Array <double>* arr_left,Array <double>* arr_right)
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

double find_split_point(Array <Array <double> >& points,bkd)
{
// Como hacemos con la heurística? Le paso un puntero a funcion? O un tipo enumerativo y solo aca se saben las heuristicas (diccionario de punteros a funcion)
// Impongo el punto del medio
	double max, min;

	max = find_max_min_in_dimension(points,MAX);
	min = find_max_min_in_dimension(points,MIN);
	return (max+min)/2
}

Array <double> find_max_min(Array <Array <double> >& points,flag_min_max flag)
{
// Este es para topright y bottom. Hace el maximo de cada dimension
// 
	if(flag == MIN){
		
	}
	
}
double find_max_min_in_dimension(Array <Array <double> >& points,flag_min_max,int dimension)
{

}

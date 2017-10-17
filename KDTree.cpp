// Implementación del KDTree para TP1 de algo2.

#include <iostream>
#include <ctime>

#include "Array.h"
#include "KDTree.h"
#include "utils.h"



using namespace std;


class Nodo {
    private:

        Array <double> _botleft;
        Array <double> _topright;//Estos son la bounded box. No sé si tiene mas sentido un solo arreglo o 4 dobles separados

        char _breakdimension;	//Dimensión por la que dividió
        double _breakpoint;	//Punto por el que corta
	heuristic_t _heuristic;//Heurística seleccionada
        Array <Array <double> > _tiberium_points; // Puntos dentro de esta bounding box

        Nodo* _branch_left;
        Nodo* _branch_right;
        Nodo* _father;
    public:
	friend class KDTree;
        Nodo(Array <Array <double> >& Points,char bkd,heuristic_t heuristic,Nodo* Father=NULL);
        ~Nodo(); 
	//Getters
        double get_breakpoint() ;
        char get_breakdimension();
        Array <double> get_topright();
        Array <double> get_botleft();
	Array <Array <double> >& get_points();
	Nodo* get_left_branch();
	Nodo* get_right_branch();
	Nodo* get_father();
	Nodo* get_brother();
	bool is_leaf();
	bool has_points();
	
	//Setters
        void set_breakpoint(double );
        void set_breakdimension(char );
	void set_heuristic(heuristic_t);
	void set_region();
	void set_topright(Array <double>& );
	void set_botleft(Array <double>& );
	void set_points(Array <Array <double> >& );
	void set_father(Nodo* &);
	void set_branch_left(Nodo* &nodo);
	void set_branch_right(Nodo* &nodo); 

	Array <double>& find_min_distance(Array <double>&point, Array <double>& current_best,double distance=-1);
};


Nodo::Nodo(Array <Array <double> >& Points,char bkd,heuristic_t heuristic,Nodo* Father){
	this->set_heuristic(heuristic);
	this->set_breakdimension(bkd);
	this->set_points(Points);
	this->set_father(Father);
       	this->set_region();
		
	//Ya cargo todo, pero tiene que ver si este será una hoja (menos de x puntos) o si tiene que separarse
	if((this->get_points()).getSize()>MAX_NUM_LEAF){
       		this->set_breakpoint(find_split_point(Points,bkd,heuristic));
		Array <Array <double> > * points_right;
		Array <Array <double> > * points_left;
		split(get_points(),get_breakdimension(),get_breakpoint(),points_left,points_right);
		Nodo * nodo_left;
		Nodo * nodo_right;
		nodo_left = new Nodo(*points_left,(bkd+1)%NUM_DIMENSIONS,_heuristic,this);
		nodo_right =new Nodo(*points_right,(bkd+1)%NUM_DIMENSIONS,_heuristic,this);
		this->set_branch_left(nodo_left);
		this->set_branch_right(nodo_right);
		delete points_left;
		delete points_right;
	}
	else{
		_branch_left=NULL;
		_branch_right=NULL;
	}
}
Nodo::~Nodo()
{
        if(_branch_left!=NULL)
		delete _branch_left;
        if(_branch_right!=NULL)
		delete _branch_right;
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
void Nodo::set_heuristic(heuristic_t heuristic)
{
	_heuristic=heuristic;
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
	Array <double> v;

	if(this->has_points() == false)
		return ;

	v = find_max_min(this->get_points(),MAX);
	this->set_topright(v);
	v = find_max_min(this->get_points(),MIN);
	this->set_botleft(v);
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

Nodo* Nodo::get_left_branch()
{
	return _branch_left;
}
Nodo* Nodo::get_right_branch()
{
	return _branch_right;
}
Nodo* Nodo::get_father()
{
	return _father;
}
Nodo* Nodo::get_brother()
{
	if(_father!=NULL){
		if(_father->_branch_left == this)
			return _father->_branch_right;
		if(_father->_branch_right == this)
			return _father->_branch_left;
	}
	return NULL;
}

bool Nodo::is_leaf()
{
	if(_branch_left==NULL && _branch_right == NULL)
		return true;
	else
		return false;
}

bool Nodo::has_points()
{
	if(this->get_points().getSize() == 0)
		return false;
	else
		return true;
}

KDTree::KDTree()
{
	_root = NULL;
}

KDTree::KDTree(Array <Array <double> > points, heuristic_t heuristic)
{
	_root = new Nodo(points,0,heuristic);
	_heuristic = heuristic;
}

KDTree::~KDTree()
{
	delete _root;
}

int split(Array <Array <double> > & points, char dimension, double break_point, Array <Array <double> >*& arr_left,Array <Array <double> >*& arr_right)
{
	arr_left = new Array< Array< double> >();
	arr_right = new Array< Array< double> >();
	for (size_t i=0;i<points.getSize();++i){
		if((points[i])[(int)dimension] < break_point){
			arr_left->append(points[i]);
		}
		else{
			arr_right->append(points[i]);
		}
	}
	return 0;
} 

double find_split_point(Array <Array <double> >& points,char bkd,heuristic_t heuristic)
{
	switch(heuristic){
		case MEDIAN:
        		return quickselect(points, bkd, 0, points.getSize()-1, points.getSize()/2);
		case HALF:
			return find_half(points,bkd);
		case AVERAGE:
			return rnd_average(points,bkd);
		default:
			exit(1);
	}	
}

Array <double> find_max_min(Array <Array <double> >& points,flag_min_max flag)
{
// Este es para topright y bottom. Hace el maximo de cada dimension
	Array <double>  v(NUM_DIMENSIONS);

	for(size_t i=0;i<NUM_DIMENSIONS;++i){
		v[i] = find_max_min_in_dimension(points,flag,i);
	}
	return v;
	
}
double find_max_min_in_dimension(Array <Array <double> >& points,flag_min_max flag,int dimension)
{
	double top;

	top = (points[0])[dimension];
	if(flag == MIN){
		for(size_t i =1; i<points.getSize();++i){
			if((points[i])[dimension]<top)
				top = (points[i])[dimension];
		}
	}
	if(flag == MAX){
		for(size_t i =1; i<points.getSize();++i){
			if((points[i])[dimension]>top)
				top = (points[i])[dimension];
		}
	}
	return top;
}

Nodo* KDTree::find_closest_node(Array <double>& point)
{
	Nodo* ptr_actual_node;

	ptr_actual_node = _root;
	while(ptr_actual_node->_branch_left != NULL && ptr_actual_node->_branch_right != NULL){
		if(point[ptr_actual_node->_breakdimension]<ptr_actual_node->_breakpoint){
			ptr_actual_node = ptr_actual_node->_branch_left;
		}else{
			ptr_actual_node = ptr_actual_node->_branch_right;
		}
	}
	return ptr_actual_node;
}

Array <double>& KDTree::find_min_distance(Array <double>& point)
{
	
	return _root->find_min_distance(point,point);
}

Array <double>& Nodo::find_min_distance(Array <double>&point, Array <double>& current_best,double distance)
{
//distance por defecto es -1
//Si distancia es -1, closest_point tiene cualquier valor
	//Caso base: es una hoja
	if(this->is_leaf() == true){
		int pos = find_min_distance_linear(this->_tiberium_points,point);
		if(distance < 0){
			return (this->_tiberium_points)[pos];
		}else{
			if(distance < getDistance((this->_tiberium_points)[pos],point))
				return current_best;
			else
				return (this->_tiberium_points)[pos];
		}
	}else{//Caso general: tiene hijos, si es la primera llamada entra al que caeria el punto, sino, mira si entra o no a las ramas segun sus zonas
		if(distance<0){ //todavía no hizo ninguna búsqueda
			if(point[this->_breakdimension]<this->_breakpoint){
				//Voy a izq y luego a derecha
				current_best = _branch_left->find_min_distance(point,current_best,distance);
				distance = getDistance(point,current_best);
				current_best = _branch_right->find_min_distance(point,current_best,distance);
			}else{
				current_best = _branch_right->find_min_distance(point,current_best,distance);
				distance = getDistance(point,current_best);
				current_best = _branch_left->find_min_distance(point,current_best,distance);
			}
				
		}else{
			if(distance > getRegionDistance(point,_branch_left->_botleft,_branch_left->_topright)){
				current_best = _branch_left->find_min_distance(point,current_best,distance);
				distance = getDistance(point,current_best);
			}
			if(distance > getRegionDistance(point,_branch_right->_botleft,_branch_right->_topright)){
				current_best = _branch_right->find_min_distance(point,current_best,distance);
				distance = getDistance(point,current_best);
			}
				
	
		}
		return current_best;
	}
}

//calcula la distancia a cada subregion
double getRegionDistance(Array <double> &point, Array <double> &botleft, Array <double> &topright)
{
    Array <double> comparator(2);
    if(point[0]<botleft[0])
        comparator[0]=botleft[0];
    if(point[0]>topright[0])
        comparator[0]=topright[0];
    if(point[0]>=botleft[0]&&point[0]<=topright[0])
        comparator[0]=point[0];
    if(point[1]<botleft[1])
        comparator[1]=botleft[1];
    if(point[1]>topright[1])
        comparator[1]=topright[1];
    if(point[1]>=botleft[1]&&point[1]<=topright[1])
        comparator[1]=point[1];
    return getDistance(comparator,point);
}

// ======= Funciones para heurísticas =======
// ==========================================

//funciones internas de quickselect para aplicar la heuristica de la mediana
void arrayswap(Array <double> &a, Array <double> &b)
{
    Array <double> aux;
    aux=a;
    a=b;
    b=aux;
}

size_t quickpartition (Array <Array <double> >& points, size_t dimension, size_t left, size_t right, size_t pivotindex)
{
    size_t i, storeindex=left;
    double pivotvalue=(points[pivotindex])[dimension];

    arrayswap(points[pivotindex],points[right]);
    for(i=left;i<right;++i)
    {
        if((points[i])[dimension]<pivotvalue)
        {
            arrayswap(points[storeindex],points[i]);
            ++storeindex;
        }
    }
    arrayswap(points[right],points[storeindex]);
    return storeindex;
}

double quickselect(Array <Array <double> >& points, char coord, size_t left, size_t right, size_t k)
{
    size_t i, pivotindex;

    i = coord;

    if (left==right)	//Caso base
        return points[left][i];
    //Caso general
    srand(time(NULL));
    pivotindex= (rand()%(right-left))+left;//criterio para elegir un pivote aleatorio, esto se puede cambiar tranquilamente
    pivotindex= quickpartition(points, i,left, right, pivotindex);
    if (k==pivotindex)
        return (points[k])[i];
    else if (k<pivotindex)
        return quickselect(points, coord,left, pivotindex-1, k);
    else return quickselect(points, coord, pivotindex+1, right, k);
}

//funcion para aplicar heuristica del promedio
double rnd_average(Array <Array <double> >& points, char coord)
{
	double aux=0; size_t i;
	srand(time(NULL));
	for(i=0;i<3;++i)
	    aux+=(points[rand()%points.getSize()])[coord];
	return aux/3;
}

double find_half(Array< Array <double> > & points, char bkd)
{
	double max, min;
	max = find_max_min_in_dimension(points,MAX,bkd);
	min = find_max_min_in_dimension(points,MIN,bkd);
	return (max+min)/2;
}

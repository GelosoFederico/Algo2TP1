// Main TP1 algo2
//

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <cctype>

#include "cmdline.h"
#include "Array.h"
#include "main.h"
#include "utils.h"
#include "KDTree.h"


using namespace std;

static void opt_points (string const &arg);
static void opt_input(string const &arg);
static void opt_output(string const &arg);
static void opt_heuristic(string const &arg);
static void opt_unsafe(string const &arg);


//========= GLOBAL VARS =========
static option_t options[] = {
	{1, "p", "points", "-", opt_points, OPT_MANDATORY},
	{1, "i", "input", "-", opt_input, OPT_DEFAULT},
	{1, "o", "output", "-", opt_output, OPT_DEFAULT},
	{1, "s", "split", "-", opt_heuristic, OPT_DEFAULT},
	{0, "u", "unsafe", NULL, opt_unsafe, OPT_DEFAULT},
	{0, }
};

static istream *points_stream = 0;
static istream *input_stream = 0;
static ostream *output_stream = 0;
static heuristic_t heuristic_selected = MEDIAN;
static bool flag_unsafe = false;

static fstream pfs;
static fstream ifs;
static fstream ofs;

//======== Parsers de opciones =========

static void opt_points (string const &arg)
{
	pfs.open(arg.c_str(), ios::in);
	points_stream = &pfs;

	if(!points_stream->good()){
		cerr << MSG_ERR_OPEN_FILE << arg << endl;
		exit(1);
	}
}


static void opt_input(string const &arg)
{
	if(arg == "-") {
		input_stream = &cin;
	}
	else{
		ifs.open(arg.c_str(), ios::in);
		input_stream = &ifs;
	}

	if(!input_stream-> good()){
		cerr << MSG_ERR_OPEN_FILE << arg << endl;
		exit(1);
	}
}

static void opt_output(string const &arg)
{
	if(arg == "-") {
		output_stream = &cout;
	}
	else{
		ofs.open(arg.c_str(), ios::out);
		output_stream = &ofs;
	}

	if(!output_stream-> good()){
		cerr << MSG_ERR_OPEN_FILE << arg << endl;
		exit(1);
	}
}

static void opt_heuristic(string const &arg)
{
	if(arg == "-"|| arg == "mediana"){
		heuristic_selected = MEDIAN;
	}else if(arg == "mitad"){
		heuristic_selected = HALF;
	}else if(arg == "promedio"){
		heuristic_selected = AVERAGE;
	}else{
		cerr << MSG_ERROR_HEURISTIC_SELECTED << endl;
		heuristic_selected = MEDIAN;
	}	
}

static void opt_unsafe(string const &arg)
{
	flag_unsafe = true;
}

//========================================
//====== Funciones con coordenadas ========

int print_coord_csv(Array <double>& v, ostream * ptr_iss)
{
	if(NULL == ptr_iss){
		cerr << MSG_ERROR_NULL_POINTER << endl;
		return 1;
	}
	for(size_t i=0;i<v.getSize()-1;++i){
		*ptr_iss << v[i] << CSV_DELIMITER;
	}
	*ptr_iss << v[v.getSize()-1] << endl;
	
	return 1;
}



int parse_line_vector(int dimension, Array <double> & vector, istream * ptr_iss)
{	
// Leo una linea de ptr_iss, en csv, la parceo y la pongo en vector
	double aux;
	char ch;

	if(NULL == ptr_iss){
		cerr << MSG_ERROR_NULL_POINTER << endl;
		return 1;
	}

	for(int i=0;i<dimension;++i){
		if(!isdigit(ch = ptr_iss->get())){
			if(ch == '-' && isdigit(ch = ptr_iss->get())){
				ptr_iss->putback(ch);
				ptr_iss->putback('-');
			}else{
				if(ptr_iss->eof()){
					return -1;
				}
				if( (ch != '\n') && (ch != EOF) )
					move_to_next_line(ptr_iss);
				cerr << MSG_ERROR_LINE << endl;
				return 1;
			}
		}
		else{
			ptr_iss->putback(ch);
		}
		(*ptr_iss)>>aux;
		if( (i != dimension-1)  ){
			while( (ch =ptr_iss->get()) == CSV_DELIMITER || ch == CSV_DELIMITER2);
			ptr_iss->putback(ch);
			//salteo cosas hasta el siguiente caracter que no sea delimitador
		}
		vector[i] = aux;
	}
	//Ahora reviso si el último char leido es el final de linea (devuelvo 0), EOF (devuelvo -1 para que no sigan leyendo) o distinto de eso (algo esta mal en la linea)
	if( ((ch =ptr_iss->get()) == '\n') || (ch == EOF) || (ch == '\r' && (ch =ptr_iss->get() == '\n')) ){
		// Termino la línea. Para que se sepa desde fuera si terminó el archivo, hay que llamarlo de nuevo
		return 0;
	}
	// Si no entró en los otros, hubo un error
	cerr << MSG_ERROR_LINE << endl;
	move_to_next_line(ptr_iss);
	return 1;
}


//=== Funciones directas del programa ===

int read_points_dimension(int &dimension, istream * ptr_iss)
{
	int n=0;
	char ch=0;

	if( NULL == ptr_iss){
		return 1;
	}
	if( ((*ptr_iss)>>n) && ((ch = ptr_iss->get()) == '\n') ){ //Linux endl
		dimension = n;
		return 0;
	}
	if( (n && ch =='\r') && ((ch = ptr_iss->get()) == '\n') ){ //Win endl
		dimension = n;
		return 0;
	}
	return 1;
}

int load_points (int dimension, Array <Array <double> > & points_tiberium, istream * ptr_iss)
{
	bool eof=false;
	int st;
	Array <double> * ptr_current_array;

	if(NULL == ptr_iss){
		cerr << MSG_ERROR_NULL_POINTER << endl;
		return 1;
	}
	while(!eof){
		ptr_current_array = new Array <double> (dimension);
		st = parse_line_vector(dimension, *ptr_current_array, ptr_iss);
		if(st == -1){
			eof = true;
			delete ptr_current_array;
		}
		if(st == 1){
			delete ptr_current_array;
		}
		if(st == 0){
			if(flag_unsafe ||points_tiberium.linear_search(*ptr_current_array)==-1)
				points_tiberium.append(*ptr_current_array);	
			delete ptr_current_array;
		}
	}
	if(!points_tiberium.getSize()){
		cerr << MSG_ERROR_NO_DATA << endl;
		return 1;
	}
	return 0;
}

int make_query (KDTree& tree, int dimension, istream * query_file, ostream * target_file)
{
	Array <double> current_array (dimension);
	Array <double> closest_array (dimension);
	int st;
	bool eof=false;
	
	if(!query_file||!target_file){
		cerr << MSG_ERROR_NULL_POINTER << endl;
		return 1;
	}
	while(!eof){
		st = parse_line_vector(dimension, current_array, query_file);
		if(st == -1)
			eof = true;
		if(st == 1){
			//No hago nada
		}
		if(st == 0){
			closest_array = tree.find_min_distance(current_array);
			print_coord_csv(closest_array,target_file);
		}
	}
	return 0;
}


int main(int argc, char * const argv[])
{
	cmdline cmdl(options);
	int dimension;
	Array <Array <double> > * ptr_points_tiberium;
	KDTree * ptr_kdtree_points;

	cmdl.parse(argc, argv);
	if(read_points_dimension(dimension,points_stream)){
		ifs.close();
		pfs.close();
		ofs.close();
		cerr<<MSG_ERR_FIND_DIMENSION<<endl;
		return 1;
	}
	ptr_points_tiberium = new Array <Array <double> > ();
	if(load_points(dimension, *ptr_points_tiberium, points_stream)){
		delete ptr_points_tiberium;
		ifs.close();
		pfs.close();
		ofs.close();
		cerr<<MSG_ERR_LOADING_POINTS<<endl;
		return 1;
	}
	ptr_kdtree_points = new KDTree (*ptr_points_tiberium,heuristic_selected);
	delete ptr_points_tiberium;
	if(make_query(*ptr_kdtree_points,dimension,input_stream,output_stream)){
		delete ptr_kdtree_points;
		ifs.close();
		pfs.close();
		ofs.close();
		cerr<<MSG_ERROR_QUERY << endl;
		return 1;
	}
	delete ptr_kdtree_points;
	ifs.close();
	pfs.close();
	ofs.close();
	
	return 0;
}

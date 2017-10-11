#ifndef MAIN__C
#define MAIN__C

#include <iostream>

#define MSG_ERR_OPEN_FILE "Error al abrir el archivo "
#define MSG_ERR_FIND_DIMENSION "Error al leer la dimension"
#define MSG_ERROR_LINE "Error al leer la linea"
#define MSG_ERROR_DELIMITER "Error al buscar el delimitador"
#define MSG_ERROR_CALL_DIMENSION "Error en la llamada, las dimensiones no son correctas"
#define MSG_ERR_LOADING_POINTS "Error al cargar los puntos"
#define MSG_ERR_EOF_BEFORE "Error EOF visto antes de lo esperado"
#define MSG_ERROR_DISTANCE_DIMENSION "Error al calcular distancia: los elementos no tienen la misma cantidad de dimensiones"
#define MSG_ERROR_NULL_POINTER "Error puntero nulo"
#define MSG_ERROR_QUERY "Error en el query"
#define MSG_ERROR_NO_DATA "Error: el archivo de coordenadas no contiene coordenadas válidas" 

#define POINTS_STARTING_SIZE 1
#define CSV_DELIMITER ' '
#define CSV_DELIMITER2 '\t'


// Prototipos

using namespace std;

int read_points_dimension(int &dimension, istream * ptr_iss);
int load_points (int dimension, Array <Array <double> >& points_tiberium, istream * ptr_iss);
int parse_line_vector(int dimension, Array <double> & vector, istream * ptr_iss);

double getDistance(Array <double> &coord1, Array <double> &coord2);
int get_min_distance(Array < Array <double> > &database,Array <double> & query);
int make_query (Array <Array <double> > &database, int dimension, istream * query_file, ostream * target_file);
int print_coord_csv(Array <double> &v, ostream * ptr_oss);

#endif

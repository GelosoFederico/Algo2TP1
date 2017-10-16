// 
// Con este programa se genera el archivo de entrada y el de consultas

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <string>

#include "cmdline.h"
#include "Array.h"

#define BAD_DIMENSION_PROBABILITY 0.1
#define CSV_DELIMITER ' '
#define MSG_ERR_OPEN_FILE "no se puedo abrir el archivo"

using namespace std;

//Prototipos
int StrToInt (std::string const & s);
void opt_entries (std::string const & s);
void opt_dimension (std::string const & s);
void opt_include (std::string const & s);
void opt_minus (std::string const & s);
void opt_plus (std::string const & s);
static void opt_output(string const &arg);
int print_random_coord(int dim);

// ======= GLOBAL VARS =======
// option_t: has args, short name,long name,default value, parser,flags
static option_t options[] = {
	{1, "o", "output", "-", opt_output, OPT_DEFAULT},
	{1, "n", "num_entries", NULL, opt_entries, OPT_MANDATORY},
	{1, "d", "dimension", "-", opt_dimension, OPT_DEFAULT},
	{0, "I", "include-dimension", NULL, opt_include, OPT_DEFAULT},
	{0, "E", "plus_dimension", NULL, opt_plus, OPT_DEFAULT},
	{0, "e", "minus_dimension", NULL, opt_minus, OPT_DEFAULT},
//	{0, "h", "help", NULL, opt_help, OPT_DEFAULT},
	{0, },
};

static int num_entries;
static int num_dimension;
static bool flag_error_plus_dimension = false;
static bool flag_error_minus_dimension = false;
static bool flag_include_dimension = false;
static ostream *output_stream = 0;
static fstream ofs;

// ======= Parse functions =======

int StrToInt (std::string const & s)
{
	return strtol(s.c_str(),NULL,10);
}

void opt_entries (std::string const & s)
{
	num_entries = StrToInt(s);
}

void opt_dimension (std::string const & s)
{
	num_dimension = StrToInt(s);
}

void opt_include (std::string const & s)
{
	flag_include_dimension = true;
}

void opt_minus (std::string const & s)
{
	flag_error_minus_dimension = true;
}

void opt_plus (std::string const & s)
{
	flag_error_plus_dimension = true;
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

int print_random_coord(int dim)
{

	if(flag_error_minus_dimension == true){
		if((double) rand()/RAND_MAX < BAD_DIMENSION_PROBABILITY)
			dim--;	
	}
	if(flag_error_plus_dimension == true){
		if((double) rand()/RAND_MAX < BAD_DIMENSION_PROBABILITY)
			dim++;	
	}

	for(int i=0;i<dim-1;i++){
		(*output_stream) <<(double) rand()/RAND_MAX << CSV_DELIMITER;
	}
	(*output_stream) <<(double) rand()/RAND_MAX << endl;

	return 0;
}

int print_dimension (void)
{
	(*output_stream) << num_dimension << endl;
}

int main (int argc, char* argv[])
{
	cmdline cmdl(options);

	cmdl.parse(argc, argv);
	srand(time(NULL));
	
	if(flag_include_dimension == true)
		print_dimension();
	for(int i=0;i<num_entries;++i){
		print_random_coord(num_dimension);
	}

	return 0;
}


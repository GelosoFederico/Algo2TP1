#include <iostream>
#include <cstdlib>
#include "utils.h"

void move_to_next_line(std::istream * ptr_iss)
{
	char ch;

	if(ptr_iss)
		while( ((ch = (ptr_iss->get()) ) != '\n') && (!ptr_iss->eof()));
}


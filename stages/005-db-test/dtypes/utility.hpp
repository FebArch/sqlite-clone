
#ifndef UTILITY_FUNCTIONS
#define UTILITY_FUNCTIONS

#include <stdlib.h>
#include <string.h>
#include "table.hpp"


void serialize_row(Row* source, void* destination);
void deserialize_row(void* source, Row* destination);
void print_row(Row* row);


#endif
// Virtual Machine

#ifndef QUERY_EXECUTION
#define QUERY_EXECUTION

#include "statement.hpp"

typedef enum{
    QUERY_EXECUTION_SUCCESS,
    QUERY_EXECUTION_FAILURE,
} Execute_Query_Result;

void execute_query(Statement* statement);

#endif
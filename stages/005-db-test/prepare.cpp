// SQL Compiler

#include <string.h>
#include "dtypes/statement.hpp"

Prepare_Statement_Result prepare_statement(InputBuffer* inputBuffer, Statement* statement){
    if (strncmp(inputBuffer->buffer, "INSERT", 6) == 0)
    {
        statement->type = INSERT;
        return PREPARE_STATEMENT_SUCCESS;
    }
    else if(strncmp(inputBuffer->buffer, "SELECT", 6) == 0){
        statement->type = SELECT;
        return PREPARE_STATEMENT_SUCCESS;
    }
        return PREPARE_STATEMENT_FAILURE;
}
// SQL Compiler

#include <iostream>
#include <string.h>
#include "dtypes/statement.hpp"

Prepare_Statement_Result prepare_statement(InputBuffer* inputBuffer, Statement* statement){
    if (strncmp(inputBuffer->buffer, "INSERT", 6) == 0)
    {
        int args_assigned = sscanf(inputBuffer->buffer, "INSERT %d %s %s", &(statement->row_to_insert.id), &(statement->row_to_insert.username), &(statement->row_to_insert.email));

        if (args_assigned < 3)
        {
            return PREPARE_SYNTAX_ERROR;
        }
        statement->type = INSERT;

        return PREPARE_STATEMENT_SUCCESS;
    }
    else if(strncmp(inputBuffer->buffer, "SELECT", 6) == 0){
        statement->type = SELECT;
        return PREPARE_STATEMENT_SUCCESS;
    }
        return PREPARE_STATEMENT_FAILURE;
}
#ifndef STATEMENT
#define STATEMENT

#include "input_buffer.hpp"

typedef enum{
    SELECT,
    INSERT
} StatementType;

typedef struct
{
    StatementType type;
} Statement;


typedef enum{
    PREPARE_STATEMENT_SUCCESS,
    PREPARE_STATEMENT_FAILURE
} Prepare_Statement_Result;

Prepare_Statement_Result prepare_statement(InputBuffer* inputBuffer, Statement* statement);

#endif
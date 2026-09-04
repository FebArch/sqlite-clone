#ifndef STATEMENT
#define STATEMENT

#include "input_buffer.hpp"
#include "table.hpp"

typedef enum{
    SELECT,
    INSERT,
} StatementType;

typedef struct
{
    StatementType type;
    Row row_to_insert;
} Statement;


typedef enum{
    PREPARE_STATEMENT_SUCCESS,
    PREPARE_SYNTAX_ERROR,
    PREPARE_STATEMENT_FAILURE
} Prepare_Statement_Result;

Prepare_Statement_Result prepare_statement(InputBuffer* inputBuffer, Statement* statement);

#endif
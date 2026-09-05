// Virtual Machine

#ifndef QUERY_EXECUTION
#define QUERY_EXECUTION

#include <stdint.h>
#include "statement.hpp"
#include "table.hpp"

typedef enum{
    QUERY_EXECUTION_SUCCESS,
    QUERY_EXECUTION_TABLE_FULL,
    QUERY_EXECUTION_FAILURE,
} Execute_Query_Result;


Execute_Query_Result execute_query(Statement* statement, Table* table);

Execute_Query_Result execute_insert(Statement* statement, Table* table);
Execute_Query_Result execute_select(Statement* statement, Table* table);

void* row_slot(Table* table, uint32_t row_nums);

#endif
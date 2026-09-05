#include <iostream>
#include "dtypes/statement.hpp"
#include "dtypes/execute_query.hpp"
#include "dtypes/utility.hpp"

Execute_Query_Result execute_query(Statement* statement, Table* table){
    switch (statement->type)
    {
    case INSERT:
        return execute_insert(statement, table);
    
    case SELECT:
        return execute_select(statement, table);
    }
}



void* row_slot(Table* table, uint32_t row_num){
    uint32_t page_num = row_num / ROWS_PER_PAGE;  // 0/14, 1/14, ... 14/14, 15/14, 16/14, ... 28/14

    void* page = table->pages[page_num];
    if (page == NULL)
    {
        page = table->pages[page_num] = malloc(PAGE_SIZE);  // 4096  returns void pointer to 1st byte
    }
    
    uint32_t row_offset = row_num % ROWS_PER_PAGE;  // row_num % 14 row offset will range from 0-14 ==> 14 excluded
    uint32_t byte_offset = row_offset * ROW_SIZE;  // row_offset * 291
    return page + byte_offset;

}


Execute_Query_Result execute_insert(Statement* statement, Table* table){
    if ((table->num_rows) >= TABLE_MAX_ROWS)
    {
        std::cout << "number: " << table->num_rows << std::endl;
        return QUERY_EXECUTION_TABLE_FULL;
    }
    
    Row* row_to_insert = &(statement->row_to_insert);
    serialize_row(row_to_insert, row_slot(table, table->num_rows));
    table->num_rows += 1;

    return QUERY_EXECUTION_SUCCESS;
}



Execute_Query_Result execute_select(Statement* statement, Table* table){
    Row row;
    for (int i = 0; i < table->num_rows; i++)
    {
        deserialize_row(row_slot(table, i), &row);
        print_row(&row);
    }
    
    return QUERY_EXECUTION_SUCCESS;
}


void print_row(Row* row){
    std::cout << "(" << row->id << ", " << row->username << ", " << row->email << ")" << std::endl;
}






#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
using namespace std;



#define VARCHAR_32 32
#define VARCHAR_255 255
#define size_of_attribute(Struct, Attribute)  sizeof(((Struct*)0)->Attribute);
#define TABLE_MAX_PAGES 100


typedef enum
{
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;

typedef enum
{
    PREPARE_SUCCESS,
    PREPARE_UNRECOGNIZED_STATEMENT
} PrepareResult;

typedef enum
{
    STATEMENT_INSERT,
    STATEMENT_SELECT
} StatementType;

typedef enum{
    EXECUTE_SUCCESS,
    EXECUTE_TABLE_FULL
} ExecuteQueryResult;


typedef struct{
    uint32_t num_rows;
    void* pages[TABLE_MAX_PAGES];
} Table;



typedef struct {
  char* buffer;
  size_t buffer_length;
  ssize_t input_length;
} InputBuffer;

typedef struct{
    uint32_t id;
    char username[VARCHAR_255];
    char email[VARCHAR_255];
} Row;

typedef struct
{
    StatementType type;
    Row row_to_insert;
} Statement;


const uint32_t ID_SIZE = size_of_attribute(Row, id);
const uint32_t USERNAME_SIZE = size_of_attribute(Row, username);
const uint32_t EMAIL_SIZE = size_of_attribute(Row, email);

const uint32_t ID_OFFSET = 0;
const uint32_t USERNAME_OFFSET = ID_SIZE + ID_OFFSET;
const uint32_t EMAIL_OFFSET = USERNAME_SIZE + USERNAME_OFFSET;

uint32_t ROW_SIZE = ID_SIZE + USERNAME_SIZE + EMAIL_SIZE;  // 4 + 32 + 255 = 291



const uint32_t PAGE_SIZE = 4096;
const uint32_t ROWS_PER_PAGE = PAGE_SIZE / ROW_SIZE; // 4096 / 291 = 14.07560
const uint32_t TABLE_MAX_ROWS = ROWS_PER_PAGE * TABLE_MAX_PAGES;


Table* new_table();
InputBuffer *new_input_buffer();
void read_input(InputBuffer* input_buffer);
MetaCommandResult do_meta_command(InputBuffer *input_buffer);
PrepareResult prepare_statement(InputBuffer *input_buffer, Statement *statement);

void execute_statement(Statement *statement, Table* table);
void serialize_row(Row* source, void* destination);
void deserialize_row(Row* destination, void* source);
void print_row(Row* row);
ExecuteQueryResult execute_insert(Statement* statement, Table* table);
ExecuteQueryResult execute_select(Statement* statement, Table* table);


void free_table(Table* table);
void close_input_buffer(InputBuffer* input_buffer);



int main()
{
    Table* table = new_table();
    InputBuffer *input_buffer = new_input_buffer();
    cout << "~ ./db" << endl;
    while (true)
    {
        cout << "db > ";
        read_input(input_buffer);
        if (input_buffer->buffer[0] == '.')
        {
            switch (do_meta_command(input_buffer))
            {
            case (META_COMMAND_SUCCESS):
                continue;
            case (META_COMMAND_UNRECOGNIZED_COMMAND):
                    cout << "Unrecognized command " << input_buffer->buffer << endl;
                continue;
            }
        }

        Statement statement;
        switch (prepare_statement(input_buffer, &statement))
        {
        case (PREPARE_SUCCESS):
            break;
        case (PREPARE_UNRECOGNIZED_STATEMENT):
            cout << "Unrecognized keyword at start of " << input_buffer->buffer << endl;
            continue;
        }

        execute_statement(&statement, table);
        cout << "Executed " << endl;
    }
    return 0;
}

Table* new_table(){
    Table* table = (Table* ) malloc(sizeof(Table));
    table->num_rows = 0;
    
    for (int i = 0; i < TABLE_MAX_PAGES; i++)
    {
        table->pages[i] = NULL;
    }
    return table;
}

InputBuffer *new_input_buffer()
{
    InputBuffer *input_buffer = (InputBuffer *) malloc(sizeof(InputBuffer));
    input_buffer->buffer = NULL;
}

void read_input(InputBuffer* input_buffer) {
  ssize_t bytes_read =
      getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);

  if (bytes_read <= 0) {
        cout << "Error reading input" << endl;
    exit(EXIT_FAILURE);
  }

  // Ignore trailing newline
  input_buffer->input_length = bytes_read - 1;
  input_buffer->buffer[bytes_read - 1] = 0;
}

MetaCommandResult do_meta_command(InputBuffer *input_buffer)
{
    if (strcmp(input_buffer->buffer, ".exit") == 0)
    {
        close_input_buffer(input_buffer);
        exit(EXIT_SUCCESS);
    }
    else
    {
        return META_COMMAND_UNRECOGNIZED_COMMAND;
    }
}

PrepareResult prepare_statement(InputBuffer *input_buffer, Statement* statement)
{
    if (strncmp(input_buffer->buffer, "INSERT", 6) == 0)
    {
        int args_assigned = sscanf(input_buffer->buffer, "INSERT %d %s %s", &(statement->row_to_insert.id), &(statement->row_to_insert.username), &(statement->row_to_insert.email));
        statement->type = STATEMENT_INSERT;
        return PREPARE_SUCCESS;
    }
    if (strncmp(input_buffer->buffer, "SELECT", 6) == 0)
    {
        statement->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }

    return PREPARE_UNRECOGNIZED_STATEMENT;
}

void execute_statement(Statement *statement, Table* table)
{

    switch (statement->type)
    {
    case (STATEMENT_INSERT):
        // cout << "This is where we would do an insert." << endl;
        execute_insert(statement, table);
        break;
    case (STATEMENT_SELECT):
        // cout << "This is where we would do a select." << endl;
        execute_select(statement, table);
        break;
    }
}


void* row_slot(Table* table, uint32_t row_num){
    uint32_t page_num = row_num / ROWS_PER_PAGE;
    cout << "page_num: " << page_num << endl;
    void* page = table->pages[page_num];
    
    if (page == NULL)
    {
        page = table->pages[page_num] = malloc(PAGE_SIZE);  //4096 bytes
    }
    cout << "table->pages[page_num]: " << table->pages[page_num] << endl;

    uint32_t row_offset = row_num % ROWS_PER_PAGE;  // 0 % 14 = 0
    uint32_t byte_offset = row_offset * ROW_SIZE;  // 0 * 291 = 0

    return page + byte_offset;
    
}

void serialize_row(Row* source, void* destination){

    // cout << source->username << ", ";
    // cout << source->email << endl;
    
    memcpy((destination + ID_OFFSET), &(source->id), ID_SIZE);
    memcpy((destination + USERNAME_OFFSET), &(source->username), USERNAME_SIZE);
    memcpy((destination + EMAIL_OFFSET), &(source->email), EMAIL_SIZE);
}


ExecuteQueryResult execute_insert(Statement* statement, Table* table){
    if (table->num_rows >= TABLE_MAX_ROWS)
    {
        return EXECUTE_TABLE_FULL;
    }
    
    Row* row_to_insert = &statement->row_to_insert;
    serialize_row(row_to_insert, row_slot(table, table->num_rows));
    table->num_rows+=1;

    return EXECUTE_SUCCESS;
}


void deserialize_row(Row* destination, void* source){
    // cout << destination->id <<", ";
    // cout << destination->username << ", ";
    // cout << destination->email << endl;

    memcpy(&(destination->id), source+ID_OFFSET, ID_SIZE);
    memcpy(&(destination->username), source+USERNAME_OFFSET, USERNAME_OFFSET);
    memcpy(&(destination->email), source+EMAIL_OFFSET, EMAIL_SIZE);
}

ExecuteQueryResult execute_select(Statement* statement, Table* table){
    Row row;
    for (uint32_t i = 0; i < table->num_rows; i++)
    {
        deserialize_row(&row, row_slot(table, i));
        print_row(&row);
    }
        
    return EXECUTE_SUCCESS;
}

void print_row(Row* row){
    cout << "(" << row->id << ", " << row->username << ", " << row->email <<")"<<endl;
}

void free_table(Table* table){
    for (int i = 0; table->pages[i]; i++)
    {
        free(table->pages[i]);
    }
    free(table);
}

void close_input_buffer(InputBuffer* input_buffer) {
    free(input_buffer->buffer);
    free(input_buffer);
}


#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

#define VARCHAR_32 32
#define VARCHAR_255 255


const uint32_t PAGE_SIZE = 4096;
#define TABLE_MAX_PAGES 100
const uint32_t ROWS_PER_PAGE = PAGE_SIZE / ROW_SIZE;
const uint32_t TABLE_MAX_ROWS = ROWS_PER_PAGE * TABLE_MAX_PAGES;


typedef enum
{
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNISED
} MetaCommandResult;

typedef enum
{
    PREPARE_STATEMENT,
    PREPARE_SYNTAX_ERROR,
    PREPARE_STATEMENT_UNRECOGNISED,
} PrepareStatementResult;

typedef enum
{
    STATEMENT_INSERT,
    STATEMENT_SELECT
} StatementType;

typedef struct
{
    char *buffer;
    size_t buffer_length;
    ssize_t input_length;
} InputBuffer;

typedef struct{
    uint32_t id;
    char username[VARCHAR_32];
    char email[VARCHAR_255];
} Row;

typedef struct
{
    StatementType type;
    Row row_to_insert;
} Statement;




#define size_of_attribute(Struct, Attribute) sizeof(((Struct*)0)->Attribute)

const uint32_t ID_SIZE = size_of_attribute(Row, id);
const uint32_t USERNAME_SIZE = size_of_attribute(Row, username);
const uint32_t EMAIL_SIZE = size_of_attribute(Row, email);

const uint32_t ID_OFFSET = 0;
const uint32_t USERNAME_OFFSET = ID_OFFSET + ID_SIZE;
const uint32_t EMAIL_OFFSET = USERNAME_OFFSET + USERNAME_SIZE;

const uint32_t ROW_SIZE = ID_SIZE + USERNAME_SIZE + EMAIL_SIZE;  // 4+32+255 = 291



// Function prototypes
InputBuffer *set_input_buffer();
void read_input_buffer(InputBuffer *);

MetaCommandResult meta_commands(InputBuffer *);

PrepareStatementResult prepare_statement(InputBuffer *, Statement *);
void execute_query(Statement *);

void printRow(Row*);
void serialize_row(Row* soruce, void* destination);
void deserialize_row(void *source, Row* destination);

void* row_slot(Table *table, uint32_t row_num);




void close_input_buffer(InputBuffer *);




int main()
{
    InputBuffer *input_buffer = set_input_buffer();

    cout << "~ ./db" << endl;
    while (1)
    {
        cout << "db > ";
        read_input_buffer(input_buffer);

        // Meta commands
        if (input_buffer->buffer[0] == '.')
        {
            switch (meta_commands(input_buffer))
            {
            case META_COMMAND_SUCCESS:
                continue;

            case META_COMMAND_UNRECOGNISED:
                cout << "Unrecognised command " << input_buffer->buffer << endl;
                continue;
            }
        }

        Statement statement;
        switch (prepare_statement(input_buffer, &statement))
        {
        case PREPARE_STATEMENT:
            break;

        case PREPARE_STATEMENT_UNRECOGNISED:
            cout << "Unrecognised keyword at the start of " << input_buffer->buffer << endl;
            continue;
        }

        execute_query(&statement);
        cout << "Query executed!" << endl;
    }

    return 0;
}

InputBuffer *set_input_buffer()
{
    InputBuffer *inputBuffer = (InputBuffer *)malloc(sizeof(InputBuffer));
    inputBuffer->buffer = NULL;
    inputBuffer->buffer_length = 0;
    inputBuffer->input_length = 0;

    return inputBuffer;
}

void read_input_buffer(InputBuffer *inputBuffer)
{
    size_t bytes_read = getline(&(inputBuffer->buffer), &(inputBuffer->buffer_length), stdin);

    if (bytes_read < 1)
    {
        cout << "Failed to read query" << endl;
        exit(EXIT_FAILURE);
    }

    // Ignoring new trailling character (\n)
    inputBuffer->buffer[bytes_read - 1] = '\0';
    inputBuffer->input_length = bytes_read - 1;
}

MetaCommandResult meta_commands(InputBuffer *inputBuffer)
{
    if (strcmp(inputBuffer->buffer, ".exit") == 0)
    {
        close_input_buffer(inputBuffer);
        cout << "Exiting the database...\n"
             << endl;
        exit(EXIT_SUCCESS);
    }
    else
    {
        return META_COMMAND_UNRECOGNISED;
    }
}

PrepareStatementResult prepare_statement(InputBuffer *inputBuffer, Statement *statement)
{
    if (strncmp(inputBuffer->buffer, "INSERT", 6) == 0)
    {
        statement->type = STATEMENT_INSERT;
       int args = sscanf(inputBuffer->buffer, "INSERT %d %s %s", &(statement->row_to_insert.id), &(statement->row_to_insert.username), &(statement->row_to_insert.email));
       if (args < 3)
       {
        return PREPARE_SYNTAX_ERROR;
       }
       
        return PREPARE_STATEMENT;
    }
    else if (strncmp(inputBuffer->buffer, "SELECT", 6) == 0)
    {
        statement->type = STATEMENT_SELECT;
        return PREPARE_STATEMENT;
    }
    else
    {
        return PREPARE_STATEMENT_UNRECOGNISED;
    }
}

void execute_query(Statement *statement)
{
    switch (statement->type)
    {
    case STATEMENT_INSERT:
        cout << "Insertion" << endl;
        break;

    case STATEMENT_SELECT:
        cout << "Selection" << endl;
        break;
    }
}

void printRow(Row* row){
    cout << row->id << " " << row->username << " " << row->email << endl; 
}

void serialize_row(Row* source, void* destination){
    memcpy(destination + ID_OFFSET, &(source->id), ID_SIZE);
    memcpy(destination + USERNAME_OFFSET, &(source->username), USERNAME_SIZE);
    memcpy(destination + EMAIL_OFFSET, &(source->email), EMAIL_SIZE);
}

void deserialize_row(void* source, Row* destination){
    memcpy(&(destination->id), source+ID_OFFSET, ID_SIZE);
    memcpy(&(destination->username), source + USERNAME_SIZE, USERNAME_SIZE);
    memcpy(&(destination->email), source + EMAIL_SIZE, EMAIL_SIZE);
}


void* row_slot(Table *table, uint32_t row_num){
    uint32_t page_num = row_num / ROWS_PER_PAGE;
    void *page = table->pages[page_num];

    if (page == NULL)
    {
        // Allocate memory only when we try to access page
        page = table->pages[page_num] = malloc(PAGE_SIZE);
    }
    
    uint32_t row_offset = row_num % ROWS_PER_PAGE;
    uint32_t byte_offset = row_offset * ROW_SIZE;
    return page + byte_offset;
}

Table* new_table(){
    Table* table = (Table *) malloc(sizeof(Table));
    table->num_rows = 0;
    for (uint32_t i = 0; i < TABLE_MAX_PAGES; i++)
    {
        table->pages[i] = NULL;
    }
    return table;
}

void freeTable(Table* table){
    for (int i = 0; table->pages[i]; i++)
    {
        free(table->pages[i]);
    }
    
    free(table);
}

void close_input_buffer(InputBuffer* inputBuffer){
    free(inputBuffer->buffer);
    free(inputBuffer);
    return;
}

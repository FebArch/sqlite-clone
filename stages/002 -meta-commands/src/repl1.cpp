#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

typedef struct {
    char* buffer;
    size_t buffer_length;
    ssize_t input_length;
} InputBuffer;

typedef enum{
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNISED_COMMAND
} MetaCommandResult;

typedef enum{
    PREPARE_SUCCESS,
    PREPARE_UNRECOGNISED_STATEMENT
} PrepareResult;

typedef enum{
    STATEMENT_INSERT,
    STATEMENT_SELECT,
} StatementType;

typedef struct{
    StatementType type;
}Statement;

void read_input(InputBuffer* inputBuffer);
void free_input_buffer(InputBuffer*  inputBuffer);

InputBuffer* new_input_buffer();
MetaCommandResult do_meta_commands(InputBuffer*);
PrepareResult prepare_statement(InputBuffer*, Statement*);

void execute_statement(Statement*);

int main(){
    InputBuffer* input_buffer = new_input_buffer();
    printf("~ ./db\n");
    // cout << "~ ./db" << endl;

    while (1)
    {
        cout << "\ndb > ";
        read_input(input_buffer);

        if(input_buffer->buffer[0] == '.'){
            switch(do_meta_commands(input_buffer)){
                case (META_COMMAND_SUCCESS):
                //  cout << ""
                    continue;
                case (META_COMMAND_UNRECOGNISED_COMMAND):
                    cout << "Unrecognised command: " << input_buffer->buffer;
                    continue;
            }
        }
        
        Statement statement;

        switch(prepare_statement(input_buffer, &statement)){
            case (PREPARE_SUCCESS):
                break;
            case(PREPARE_UNRECOGNISED_STATEMENT):
                cout << "Unrecognised keyowrd at start of: " << input_buffer->buffer << "\n" << endl;
                continue;
        }
        
        execute_statement(&statement);
        cout << "Executed\n";
    }
    
    return 0;
}


InputBuffer* new_input_buffer(){
    InputBuffer* inputBuffer = (InputBuffer *) malloc(sizeof(InputBuffer));
    inputBuffer->buffer = NULL;
    inputBuffer->buffer_length = 0;
    inputBuffer->input_length = 0;
    
    return inputBuffer;
}



void read_input(InputBuffer* inputBuffer){
    size_t bytes_read = getline(&(inputBuffer->buffer), &(inputBuffer->buffer_length), stdin);

    if (bytes_read <= 0)
    {
        cout << "Error reading commands\n";
        exit(EXIT_FAILURE);
    }
    
    // Ignoring new trailling character (\n)
    inputBuffer->input_length = bytes_read-1;
    inputBuffer->buffer[bytes_read - 1] = 0;

}


void free_input_buffer(InputBuffer*  inputBuffer){
    free(inputBuffer->buffer);
    free(inputBuffer);
}



MetaCommandResult do_meta_commands(InputBuffer *inputBuffer){
    if (strcmp(inputBuffer->buffer, ".exit") == 0)
    {
        cout << "Exiting the database...\n" << endl;
        exit(EXIT_SUCCESS);
    }else{
        return META_COMMAND_UNRECOGNISED_COMMAND;
    }
    
}


PrepareResult prepare_statement(InputBuffer* inputBuffer, Statement* statement){
    if (strncmp(inputBuffer->buffer, "insert", 6) == 0)
    {
        statement->type = STATEMENT_INSERT;
        return PREPARE_SUCCESS;
    }else if(strcmp(inputBuffer->buffer, "select") == 0){
        statement->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }else{
        return PREPARE_UNRECOGNISED_STATEMENT;
    }
    
}


void execute_statement(Statement* statment){
    switch (statment->type)
    {
    case STATEMENT_INSERT:
        cout << "This is where we would do an insert.\n";
        break;
    
        case(STATEMENT_SELECT):
            cout << "This is where we would do a select\n";
            break;
    }
}






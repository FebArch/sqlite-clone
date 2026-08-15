#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// my-defined datatypes

typedef struct
{
    char *buffer;
    size_t buffer_length;
    size_t input_length;
} InputBuffer;

typedef enum
{
    META_COMMAND_SUCCESS,
    META_COMMAND_FAILURE
} MetaCommandResult;

typedef enum
{
    PREPARE_STATEMENT_SUCCESS,
    PREPARE_UNRECOGNISED_STATEMENT
} PrepareStatementResult;

typedef enum
{
    STATEMENT_SELECT,
    STATEMENT_INSERT
} StatementType;

typedef struct
{
    StatementType type;
} Statement;

// Function prototypes
InputBuffer *set_input_buffer();
void read_input_buffer(InputBuffer *inputBuffer);

MetaCommandResult execute_meta_command(InputBuffer *);

PrepareStatementResult prepare_statement(InputBuffer *inputBuffer, Statement *s);

void execute_query(Statement *s);

void close_input_buffer(InputBuffer *inputBuffer);

int main()
{
    InputBuffer *input_buffer = set_input_buffer();

    printf("~ ./db\n");
    while (1)
    {
        printf("db > ");
        read_input_buffer(input_buffer);

        if (input_buffer->buffer[0] == '.')
        {
            // Meta commands handling in this version only .exit is supported!
            switch (execute_meta_command(input_buffer))
            {
            case META_COMMAND_SUCCESS:
                continue;;
            case META_COMMAND_FAILURE:
                printf("Unrecognised meta command '%s'\n", input_buffer->buffer);
                continue;;
            }
        }

        Statement statement;
        switch (prepare_statement(input_buffer, &statement))
        {
        case PREPARE_STATEMENT_SUCCESS:
            break; // breaks the switch case and not a loop
        case PREPARE_UNRECOGNISED_STATEMENT:
            printf("Unrecognised keyword at the start of '%s'\n", input_buffer->buffer);
            continue;
        }

        execute_query(&statement);
        printf("Query Executed\n");
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
    size_t bytes_read = getline(&inputBuffer->buffer, &inputBuffer->buffer_length, stdin);
    if (bytes_read <= 0)
    {
        printf("Failed to read input\n");
        exit(EXIT_FAILURE);
    }

    inputBuffer->buffer[bytes_read - 1] = 0;
    inputBuffer->buffer_length = bytes_read - 1;
}

MetaCommandResult execute_meta_command(InputBuffer *inputBuffer)
{
    if (strcmp(inputBuffer->buffer, ".exit") == 0)
    {
        close_input_buffer(inputBuffer);
        exit(EXIT_SUCCESS);
        return META_COMMAND_SUCCESS;
    }
    else
    {
        return META_COMMAND_FAILURE;
    }
}

// returns wheteher statement is formed or not
PrepareStatementResult prepare_statement(InputBuffer *inputBuffer, Statement *statement)
{
    if (strncmp(inputBuffer->buffer, "INSERT", 6) == 0)
    {
        (*statement).type = STATEMENT_INSERT;
        return PREPARE_STATEMENT_SUCCESS;
    }
    else if (strncmp(inputBuffer->buffer, "SELECT", 6) == 0)
    {
        (*statement).type = STATEMENT_SELECT;
        return PREPARE_STATEMENT_SUCCESS;
    }
    else
    {
        return PREPARE_UNRECOGNISED_STATEMENT;
    }
}

void execute_query(Statement *statement)
{
    switch (statement->type)
    {
    case STATEMENT_INSERT:
        printf("Insertion\n");
        break;

    case STATEMENT_SELECT:
        printf("SELECTION\n");
        break;
    }
}

void close_input_buffer(InputBuffer *inputBuffer)
{
    free(inputBuffer->buffer); // freeing up the memory allocatesby getline() function first
    free(inputBuffer);
    return;
}

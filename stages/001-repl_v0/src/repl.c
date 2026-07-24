#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct InputBuffer
{
    char *buffer;
    size_t buffer_size;
    size_t input_length;
} InputBuffer;

InputBuffer* new_input_buffer();
void read_input(InputBuffer* input_buffer);
void close_input_buffer(InputBuffer* input_buffer);

int main()
{
    InputBuffer *inputBuffer = new_input_buffer();
    printf("~ ./db\n");

    while (1)
    {
        printf("db > ");
        read_input(inputBuffer);

        if (strcmp(inputBuffer->buffer, ".exit") == 0)
        {
            printf("Exiting the database\n");
            close_input_buffer(inputBuffer);
            exit(EXIT_SUCCESS);
        }else{
            printf("Unrecognised command %s\n", inputBuffer->buffer);
        }
        
    }

    return 0;
}


InputBuffer *new_input_buffer()
{
    InputBuffer *input_buffer = (InputBuffer *)malloc(sizeof(InputBuffer));
    input_buffer->buffer = NULL;
    input_buffer->buffer_size = 0;
    input_buffer->input_length = 0;

    return input_buffer;
}


void read_input(InputBuffer* input_buffer){
    size_t bytes_read = getline(&(input_buffer->buffer), &(input_buffer->buffer_size), stdin);

    if (bytes_read <= 0)
    {
        printf("Error reading the input\n");
        exit(EXIT_FAILURE);
    }
    

    // Ignoring trailing new line
    input_buffer->buffer_size = bytes_read - 1;
    input_buffer->buffer[bytes_read-1] = 0;
}


void close_input_buffer(InputBuffer* inputBuffer){
    free(inputBuffer->buffer);
    free(inputBuffer);
}

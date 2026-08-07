#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* buffer;
    size_t buffer_length;
    size_t input_length;
} InputBuffer;


InputBuffer* set_input_buffer();
void read_input_buffer(InputBuffer* input_buffer);
void close_input_buffer(InputBuffer* input_buffer);

int main(){
    InputBuffer* input_buffer = set_input_buffer();
    printf("~ ./db\n");

    while (1)
    {
        printf("db > ");
        read_input_buffer(input_buffer);

        if (strcmp(input_buffer->buffer, ".exit") == 0)
        {
            close_input_buffer(input_buffer);
            printf("Database exited...\n");
            exit(EXIT_SUCCESS);
        }else{
            printf("Unrecognised command: '%s'\n", input_buffer->buffer);
        }
        
    }
    
    return 0;
}

InputBuffer* set_input_buffer(){
    InputBuffer* input_buffer = (InputBuffer *) malloc(sizeof(InputBuffer));

    input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_length = 0;
    return input_buffer;
}


void read_input_buffer(InputBuffer* inputBuffer){
    size_t bytes_read = getline(&inputBuffer->buffer, &inputBuffer->buffer_length, stdin);

    if (bytes_read <= 0)
    {
        printf("Error reading input buffer\n");
        exit(EXIT_FAILURE); 
    }
    

    inputBuffer->buffer[bytes_read-1] = 0;
    inputBuffer->buffer_length = bytes_read -1;
}



void close_input_buffer(InputBuffer* inputBuffer){
    free(inputBuffer->buffer);
    free(inputBuffer);
}


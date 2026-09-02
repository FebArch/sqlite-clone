#include <iostream>
#include <string.h>
#include "dtypes/input_buffer.hpp"
#include "dtypes/meta_cmds.hpp"

InputBuffer* new_input_buffer(){
    InputBuffer* inputBuffer = (InputBuffer *) new InputBuffer;
    inputBuffer->buffer = NULL;
    inputBuffer->buffer_size = 0;
    inputBuffer->input_buffer_length = 0;

    return inputBuffer;
}

void read_input_buffer(InputBuffer* inputBuffer){
    size_t charsRead = getline(&(inputBuffer->buffer), &(inputBuffer->buffer_size), stdin);

    if (charsRead <= 0)
    {
        std::cout << "Error reading query" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    inputBuffer->input_buffer_length = charsRead - 1;
    inputBuffer->buffer[charsRead-1] = '\0';
}


void close_input_buffer(InputBuffer* inputBuffer){
    free(inputBuffer->buffer);
    delete inputBuffer;
}
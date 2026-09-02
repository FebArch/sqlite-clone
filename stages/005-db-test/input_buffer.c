#include "input_buffer.h"
#include <string.h>

InputBuffer* new_input_buffer(){
    InputBuffer* inputBuffer = (InputBuffer *) new InputBuffer;
    inputBuffer->buffer = NULL;
    inputBuffer->buffer_size = 0;
    inputBuffer->input_buffer_length = 0;
}

void read_input_buffer(InputBuffer* inputBuffer){
    size_t charsRead = getline(&(inputBuffer->buffer), &(inputBuffer->buffer_size), stdin);

    if (charsRead <= 0)
    {
        cout << "Error reading query" << endl;
        exit(EXIT_FAILURE);
    }
    
    inputBuffer->input_buffer_length = charsRead - 1;
    inputBuffer->buffer[charsRead-1] = '\0';
}
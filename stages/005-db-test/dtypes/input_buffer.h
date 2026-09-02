#ifndef INPUT_BUFFER
#define INPUT_BUFFER
#include <cstddef>

struct InputBuffer{
    char* buffer;
    size_t buffer_size;
    size_t input_buffer_length;
};

InputBuffer* new_input_buffer();
void read_input_buffer(InputBuffer* inputBuffer);

#endif
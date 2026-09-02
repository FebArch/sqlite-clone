#ifndef INPUT_BUFFER
#define INPUT_BUFFER

#include <cstddef>

typedef struct {
    char* buffer;
    size_t buffer_size;
    size_t input_buffer_length;
} InputBuffer;

InputBuffer* new_input_buffer();
void read_input_buffer(InputBuffer* inputBuffer);
void close_input_buffer(InputBuffer* inputBuffer);

#endif
#include <iostream>
using namespace std;

struct InputBuffer
{
    char* buffer;
    size_t buffer_size;
    ssize_t input_buffer;
};

InputBuffer* new_input_buffer();

int main(){
    InputBuffer* input_buffer = new_input_buffer();
    return 0;
}

InputBuffer* new_input_buffer(){
    InputBuffer* inputBuffer = (InputBuffer *) new InputBuffer;
    inputBuffer->buffer = NULL;
    inputBuffer->buffer_size = 0;
    inputBuffer->input_buffer = 0;

    return inputBuffer;
}








































































#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

typedef struct {
    char* buffer;
    size_t buffer_size;
    ssize_t input_size;
}InputBuffer;

InputBuffer* set_input_buffer();
void read_input(InputBuffer* input_buffer);
void free_input_buffer(InputBuffer*);

int main(){
    InputBuffer* input_buffer = set_input_buffer();
    cout << "~ ./db" << endl;

    while (1)
    {
        cout << "db > ";
        read_input(input_buffer);

        if ((strcmp(input_buffer->buffer, ".exit")) == 0 )
        {
            cout << "Exiiting the database" << endl;
            free_input_buffer(input_buffer);
            exit(EXIT_SUCCESS);
        }else{
            printf("Unrecognised command: %s\n", input_buffer->buffer);
        }
        
    }
    
    return 0;
}


InputBuffer* set_input_buffer(){
    InputBuffer* input_buffer = (InputBuffer*) malloc(sizeof(InputBuffer));
    input_buffer->buffer = NULL;
    input_buffer->buffer_size = 0;
    input_buffer->input_size = 0;

    return input_buffer;
}


void read_input(InputBuffer* input_buffer){
    size_t bytes_read = getline(&(input_buffer->buffer), &(input_buffer->buffer_size), stdin);
    if (bytes_read < 0)
    {
        cout << "Error reading commands\n";
        exit(EXIT_FAILURE);
    }
    
    // Ignoring trailing new lines(\n)
    input_buffer->buffer_size = bytes_read -1;
    input_buffer->buffer[bytes_read-1] = 0;
}


void free_input_buffer(InputBuffer* input_buffer){
    free(input_buffer->buffer);
    free(input_buffer);
}
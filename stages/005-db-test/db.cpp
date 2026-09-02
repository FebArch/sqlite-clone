#include <iostream>
#include "input_buffer.c"

using namespace std;
InputBuffer* new_input_buffer();

int main(){
    InputBuffer* input_buffer = new_input_buffer();

    cout << "~ ./db" << endl;
    while (1)
    {
        cout << "db > ";
        read_input_buffer(input_buffer);

        if (input_buffer->buffer[0] == '.')
        {
            /* code */
        }
        
    }
    
    
    return 0;
}






































































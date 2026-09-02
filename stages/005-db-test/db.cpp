#include <iostream>
#include <string.h>

#include "dtypes/input_buffer.hpp"
#include "dtypes/meta_cmds.hpp"
#include "dtypes/statement.hpp"


using namespace std;

int main(){
    InputBuffer* input_buffer = new_input_buffer();

    cout << "~ ./db" << endl;
    while (1)
    {
        cout << "db > ";
        read_input_buffer(input_buffer);

        if (input_buffer->buffer[0] == '.')
        {
            switch (do_meta_commands(input_buffer))
            {
            case META_COMMAND_SUCCESS:
                continue;
            
            case META_COMMAND_FAILURE:
                cout << "Unrecognized command" << input_buffer->buffer << endl;
                continue;;
            }
        }
        
        Statement statement;
        switch (prepare_statement(input_buffer, &statement))       // SQL Compiler
        {
        case PREPARE_STATEMENT_SUCCESS:
            break;
        
        case PREPARE_STATEMENT_FAILURE:
            cout << "Unrecognized keyword at start of " << input_buffer->buffer << endl;
            continue;
        }

    }
    
    
    return 0;
}






































































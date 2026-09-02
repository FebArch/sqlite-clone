#include <iostream>
#include <string.h>

#include "dtypes/input_buffer.hpp"
#include "dtypes/meta_cmds.hpp"
#include "dtypes/statement.hpp"
#include "dtypes/execute_query.hpp"


using namespace std;

int main(){
    InputBuffer* input_buffer = new_input_buffer();

    cout << "~ ./db" << endl;
    while (1)
    {
        cout << "db > ";
        read_input_buffer(input_buffer);

        // META Commands Compiler/VM
        if (input_buffer->buffer[0] == '.')
        {
            switch (do_meta_commands(input_buffer))
            {
            case META_COMMAND_SUCCESS:
                continue;
            
            case META_COMMAND_FAILURE:
                cout << "Unrecognized meta command " << input_buffer->buffer << endl;
                continue;;
            }
        }
        
        Statement statement;

        // SQL Compiler
        switch (prepare_statement(input_buffer, &statement))       
        {
        case PREPARE_STATEMENT_SUCCESS:
            break;
        
        case PREPARE_STATEMENT_FAILURE:
            cout << "Unrecognized keyword at start of " << input_buffer->buffer << endl;
            continue;
        }

        // Virtual Machine
        execute_query(&statement);

    }
    
    
    return 0;
}






































































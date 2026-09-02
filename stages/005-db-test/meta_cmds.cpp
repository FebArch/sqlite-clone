#include "dtypes/meta_cmds.hpp"
#include "dtypes/input_buffer.hpp"
#include <iostream>
#include <string.h>


META_COMMANDS_RESULT do_meta_commands(InputBuffer* inputBuffer){
    if (strcmp(inputBuffer->buffer, ".exit") == 0)
    {
        std::cout << "Database exited!" << std::endl;
        close_input_buffer(inputBuffer);
        exit(EXIT_SUCCESS);
        return META_COMMAND_SUCCESS;
    }else{
        return META_COMMAND_FAILURE;
    }
    
}
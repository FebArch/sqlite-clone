#ifndef META_COMMANDS
#define META_COMMANDS

#include "input_buffer.hpp"

typedef enum {
    META_COMMAND_SUCCESS,
    META_COMMAND_FAILURE
} META_COMMANDS_RESULT;

META_COMMANDS_RESULT do_meta_commands(InputBuffer* inputBuffer);

#endif
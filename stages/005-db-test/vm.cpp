#include <iostream>
#include "dtypes/statement.hpp"
#include "dtypes/execute_query.hpp"

void execute_query(Statement* statement){
    switch (statement->type)
    {
    case INSERT:
        std::cout << "Insertion" << std::endl;
        break;
    
    case SELECT:
        std::cout << "Select" << std::endl;
        break;
    }
}
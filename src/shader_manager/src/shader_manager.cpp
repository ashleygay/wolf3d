#include <shader_manager.hpp>
#include <iostream>

Shader_Manager::Shader_Manager()
{

/* Use X-Macros to automatically generate code that tests for definition ? */

////        #define stringify_macro(a)\
////        ifndef a\
////            #error "Macro a is not defined"\
////        else\
////            #a\
////        endif
        
        #define stringify_macro(a) #a
        std::cout << "Initializing shaders." << std::endl;
        std::cout  << stringify_macro(__SHADERS_DIRECTORY) << std::endl;
}

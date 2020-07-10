#include <string>
#include <array>

class Shader_Manager
{
    /* 
     * We want to statically embed all shaders in the `shaders` directory.
     * We can only embed the code of the shader and not the shader object
     * itself. The shader object compilation can be affected by a myriad of
     * things and its really not a good idea to try to be smart about it.
     * The only `optimization` we do is precompile all shaders at startup.

     * We probably need to use `xxd` to extract text from the files.
     * We also probably need some tomfoolery to patch the shader manager.
     * We can do it in cmake or in python (I'd prefer this approach as it has more
     * chances of being portable ?)
     */
public:
    Shader_Manager ();
private:
    std::array <std::string, @@ARRAY_SIZE@@> _shaders = 
    {
        @@SHADERS@@
    };
};

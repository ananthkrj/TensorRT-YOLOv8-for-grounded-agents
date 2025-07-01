/*
Goal of engine.hpp: Class declaration, public interface, includes

pragma once used to make sure header file
is not used more than once in compilation

including NvInfer.h allows us to enable C++ API
for tensorRT
*/

#pragma once
#include <NvInfer.h"
#include <string>

// create class that will essentiially act as a wrapper
// for tensorRT inference
class Engine {
    // create constructor
    // constructor will have a const type parameter
    // parameter is a reference to a string object
    // enginePath is name of parameter

    // also include destructor in public access specifier
public:
    Engine(const std::string& enginePath); 
    ~Engine();
    
    // member variables of enginePath parameter
    // will need engine loaded member function
    bool loadEngine();

    // checker for loading
    // should be const
    bool isLoaded() const;

    // running inference member function
    // main allocation and dellocation logic
    bool runInference(float* input, float* output);

    // 
private:
    // member of private access specifier
    // sets up GPU input/output buffers
    // cleans up gpu memory
    bool allocateBuffers();
    bool dellocateBuffers();
};


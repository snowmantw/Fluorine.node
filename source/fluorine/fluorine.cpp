
#define BUILDING_NODE_EXTENSION

#include "process.hpp"

#include <node.h>

using namespace v8;

void InitAll(Handle<Object> exports)
{   
    // -- !! Don't forget to initialize the class before do anything !
    //       It will cause segamentation fault at the line constructor instancing the class.
    Process::Init();
    exports->Set(String::NewSymbol("Process"), FunctionTemplate::New(Process::NewInstance)->GetFunction() );
}

NODE_MODULE(fluorine, InitAll)


#define BUILDING_NODE_EXTENSION

#include "process.hpp"

#include <node.h>

using namespace v8;
using namespace node;

Process::Process(){};
Process::~Process(){};

Persistent<Function> Process::constructor;

/**
 * Initialize the class, include static members like the `constructor`.
 *
 */
void Process::Init()    // -- Don't forget the class name.
{
    // Bind the `New` function into constructor, via the template.
    Local<FunctionTemplate> tpl = FunctionTemplate::New(New);

    // -- NewSymbol, not only New.
    tpl->SetClassName(String::NewSymbol("Process"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    constructor = Persistent<Function>::New(tpl->GetFunction());
}

// ---- 

/**
 * Construct the process.
 * 
 * @param args Most important is the this object.
 * @return The wrapped object from arguments' "This".
 */
Handle<Value> Process::New(const Arguments& args)
{
    HandleScope scope;

    Process* process = new Process();
    process->Wrap(args.This()); 

    return args.This();
}

/**
 * Factory method for export "Process" function.
 * In Javascript, calling "Process()" will actually call this function.
 *
 * @return The instance of "Process" function.
 */
Handle<Value> Process::NewInstance(const Arguments& args)
{
    HandleScope scope;

    const unsigned argc = 0;
    Handle<Value>  argv[argc] = {};
    Local<Object> instance = constructor->NewInstance(argc, argv);

    return scope.Close(instance);
}

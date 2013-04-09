#define BUILDING_NODE_EXTENSION

#include "toy_gallium.hpp"

#include <node.h>

using namespace v8;

Gallium::Gallium(){};
Gallium::~Gallium(){};

Persistent<Function> Gallium::constructor;

void Gallium::Init()
{
    // Binding this tpl to the New C++ function.
    Local<FunctionTemplate> tpl = FunctionTemplate::New(New);

    tpl->SetClassName(String::NewSymbol("Gallium"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    // Binding the constructor to the New C++ function via template.
    constructor = Persistent<Function>::New(tpl->GetFunction());
}

Handle<Value> Gallium::New(const Arguments& args)
{
    HandleScope scope;

    Gallium* gallium = new Gallium();
    gallium->val_ = args[0]->IsUndefined() ? 0 : args[0]->NumberValue();
    gallium->Wrap(args.This());

    return args.This();
}

Handle<Value> Gallium::NewInstance(const Arguments& args)
{
    HandleScope scope;
    
    const unsigned argc = 1;
    Handle<Value> argv[argc] = { args[0] };
    Local<Object> instance = constructor->NewInstance(argc, argv);

    return scope.Close(instance);
}   

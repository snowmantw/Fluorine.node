
#define BUILDING_NODE_EXTENSION

#include "toy.hpp"

#include <v8.h>
#include <node.h>

using namespace node;
using namespace v8;

// Test function.
static Handle<Value> foo(const Arguments& args)
{
    // Seems the `Handle<typename>` had extended the String, as it's child class.
    // Or we should can directly use tranditional `new String` or even string literal.
    return String::New("H e l l o");
}

// Test arguments.
static Handle<Value> bar(const Arguments& args)
{
    // New scope in this function.
    HandleScope scope;

    if( args.Length() != 2)
    {
        ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
        return scope.Close(Undefined());
    }

    if( !args[0]->IsNumber() || !args[1]->IsNumber())
    {
        ThrowException(Exception::TypeError(String::New("Wrong arguments")));
        return scope.Close(Undefined());
    }

    Local<Number> num = Number::New(args[0]->NumberValue() + args[1]->NumberValue());
    return scope.Close(num);
}

// Test execute Javascript function.
static Handle<Value> charlie(const Arguments& args)
{
    HandleScope scope;

    Local<Function> cb = Local<Function>::Cast(args[0]);
    const unsigned argc = 2;
    Local<Value> argv[argc] = { Local<Value>::New(Number::New(768)), Local<Value>::New(Number::New(256)) };
    cb->Call(Context::GetCurrent()->Global(), argc, argv);

    return scope.Close(cb->Call(Context::GetCurrent()->Global(), argc, argv));
}

// Test creating object from C++ function.
static Handle<Value> delta(const Arguments& args)
{
    HandleScope scope;

    Local<Object> obj = Object::New();
    obj->Set(String::NewSymbol("msg"), args[0]->ToString());

    return scope.Close(obj);
}

static Handle<Value> eagleChild(const Arguments& args)
{
    HandleScope scope;

    return scope.Close(String::New("H E L L O"));
}

// Test creating Javascript wrapped function, it's content is another C++ function.
static Handle<Value> eagle(const Arguments& args)
{
    HandleScope scope;

    // First wrap the child C++ function with template.
    Local<FunctionTemplate> tpl = FunctionTemplate::New(eagleChild);

    // Then get its JS verion. This is because we want to create a JS binding function.
    // Previous example do not need this because it's accept an already JS bound function from arguments.
    Local<Function> fn = tpl->GetFunction();
    fn->SetName(String::NewSymbol("eagleChild"));

    return scope.Close(fn);
}


void InitAll(Handle<Object> exports)
{
    exports->Set(String::NewSymbol("foo"), FunctionTemplate::New(foo)->GetFunction());
    exports->Set(String::NewSymbol("bar"), FunctionTemplate::New(bar)->GetFunction());
    exports->Set(String::NewSymbol("charlie"), FunctionTemplate::New(charlie)->GetFunction());
    exports->Set(String::NewSymbol("delta"), FunctionTemplate::New(delta)->GetFunction());
    exports->Set(String::NewSymbol("eagle"), FunctionTemplate::New(eagle)->GetFunction());
    exports->Set(String::NewSymbol("eagleChild"), FunctionTemplate::New(eagleChild)->GetFunction());

    Fluorine::Init(exports);
}

//---- Testing C++ Object ----
 
Fluorine::Fluorine(){}
Fluorine::~Fluorine(){}

void Fluorine::Init(Handle<Object> exports)
{
    // Prepare constructor template.
    // JS "new" will invoke the `New` function in Fluorine class.
    Local<FunctionTemplate> tpl = FunctionTemplate::New(New);

    // Function can own ClassName property, even though JS doesn't own class.
    tpl->SetClassName(String::NewSymbol("Fluorine"));

    // ? Some internal modifications at the instance got instanced ?
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    // Set prototype of this Function: register prototype functions.
    tpl->PrototypeTemplate()->Set(String::NewSymbol("plusOne")
        , FunctionTemplate::New(PlusOne)->GetFunction());
    
    // Wrap the instanceable function's constructor: the `Fluorine::New function`.
    Persistent<Function> constructor = Persistent<Function>::New(tpl->GetFunction());

    // And export constructor as the instanceable function.
    exports->Set(String::NewSymbol("Fluorine"), constructor);
}

Handle<Value> Fluorine::New(const Arguments& args)
{
    HandleScope scope;

    Fluorine* obj = new Fluorine();
    obj->counter_ = args[0]->IsUndefined() ? 0 : args[0]->NumberValue();
    obj->Wrap(args.This());

    return args.This(); 
}

Handle<Value> Fluorine::PlusOne(const Arguments& args)
{
    HandleScope scope;

    Fluorine* obj = ObjectWrap::Unwrap<Fluorine>(args.This());
    obj->counter_ += 1; 

    return scope.Close(Number::New(obj->counter_));
}

// NODE_MODULE is NOT a funcion.

NODE_MODULE(toy, InitAll)

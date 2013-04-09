
#define BUILDING_NODE_EXTENSION

#include "toy_fluorine.hpp"
#include "toy_gallium.hpp"

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

static Handle<Value> fluorineCreate(const Arguments& args)
{
    HandleScope scope;
    return scope.Close(Fluorine::NewInstance(args));
}

static Handle<Value> galliumCreate(const Arguments& args)
{
    HandleScope scope;
    return scope.Close(Gallium::NewInstance(args));
}

// Receive two Gallium object and add their values.
static Handle<Value> galliumAdd(const Arguments& args)
{
    HandleScope scope;

    Gallium* g1 = node::ObjectWrap::Unwrap<Gallium>(args[0]->ToObject());
    Gallium* g2 = node::ObjectWrap::Unwrap<Gallium>(args[1]->ToObject());

    double sum = g1->Val() + g2->Val();

    return scope.Close(Number::New(sum));
}


void InitAll(Handle<Object> exports)
{
    // Register wrapped C++ functions.
    
    exports->Set(String::NewSymbol("foo"), FunctionTemplate::New(foo)->GetFunction());
    exports->Set(String::NewSymbol("bar"), FunctionTemplate::New(bar)->GetFunction());
    exports->Set(String::NewSymbol("charlie"), FunctionTemplate::New(charlie)->GetFunction());
    exports->Set(String::NewSymbol("delta"), FunctionTemplate::New(delta)->GetFunction());
    exports->Set(String::NewSymbol("eagle"), FunctionTemplate::New(eagle)->GetFunction());
    exports->Set(String::NewSymbol("eagleChild"), FunctionTemplate::New(eagleChild)->GetFunction());

    Fluorine::Init();
    exports->Set(String::NewSymbol("fluorineCreate"), FunctionTemplate::New(fluorineCreate)->GetFunction());
    
    // Beside factory pattern, we export the object itself, too.
    exports->Set(String::NewSymbol("Fluorine"), Fluorine::constructor);

    Gallium::Init();
    exports->Set(String::NewSymbol("galliumCreate"), FunctionTemplate::New(galliumCreate)->GetFunction());
    exports->Set(String::NewSymbol("galliumAdd"), FunctionTemplate::New(galliumAdd)->GetFunction());
}

// NODE_MODULE is NOT a funcion.

NODE_MODULE(toy, InitAll)

#include <v8.h>
#include <node.h>

using namespace node;
using namespace v8;

static Handle<Value> foo(const Arguments& args)
{
    // Seems the `Handle<typename>` had extended the String, as it's child class.
    // Or we should can directly use tranditional `new String` or even string literal.
    return String::New("H e l l o");
}

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

void Init(Handle<Object> exports)
{
    exports->Set(String::NewSymbol("foo"), FunctionTemplate::New(foo)->GetFunction());
    exports->Set(String::NewSymbol("bar"), FunctionTemplate::New(bar)->GetFunction());
}

// NODE_MODULE is NOT a funcion.
NODE_MODULE(toy, Init)

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

extern "C" void init(Handle<Object> target)
{
    NODE_SET_METHOD(target, "foo", foo);
}

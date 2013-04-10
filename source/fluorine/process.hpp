
#define BUILDING_NODE_EXTENSION

#ifndef FLUORINE_PROCESS_H
#define FLUORINE_PROCESS_H

#include <node.h>

class Process : public node::ObjectWrap
{
public:

    static void Init();
    static v8::Handle<v8::Value> NewInstance(const v8::Arguments& args);

private:

    Process();
    ~Process();

    static v8::Persistent<v8::Function> constructor;

    static v8::Handle<v8::Value> New(const v8::Arguments& args);
};

#endif

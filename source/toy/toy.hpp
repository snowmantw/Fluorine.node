#define BUILDING_NODE_EXTENSION

#ifndef TOYOBJECT_H
#define TOYOBJECT_H

#include <node.h>

class Fluorine: public node::ObjectWrap
{
public:
    static void Init(v8::Handle<v8::Object> exports);

private:
    Fluorine();
    ~Fluorine();

    static v8::Handle<v8::Value> New(const v8::Arguments& args);
    static v8::Handle<v8::Value> PlusOne(const v8::Arguments& args);

    double counter_;
};

#endif

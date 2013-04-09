#define BUILDING_NODE_EXTENSION

#include "toy_fluorine.hpp"

#include <node.h>


using namespace v8;

Fluorine::Fluorine() {};
Fluorine::~Fluorine() {};

Persistent<Function> Fluorine::constructor;

void Fluorine::Init() {
  // Prepare constructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
  tpl->SetClassName(String::NewSymbol("Fluorine"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);
  // Prototype
  tpl->PrototypeTemplate()->Set(String::NewSymbol("plusOne"),
      FunctionTemplate::New(PlusOne)->GetFunction());

  constructor = Persistent<Function>::New(tpl->GetFunction());
}

Handle<Value> Fluorine::New(const Arguments& args) {
  HandleScope scope;

  Fluorine* obj = new Fluorine();
  obj->counter_ = args[0]->IsUndefined() ? 0 : args[0]->NumberValue();
  obj->Wrap(args.This());

  return args.This();
}

Handle<Value> Fluorine::NewInstance(const Arguments& args) {
  HandleScope scope;

  const unsigned argc = 1;
  Handle<Value> argv[argc] = { args[0] };
  Local<Object> instance = constructor->NewInstance(argc, argv);

  return scope.Close(instance);
}

Handle<Value> Fluorine::PlusOne(const Arguments& args) {
  HandleScope scope;

  Fluorine* obj = ObjectWrap::Unwrap<Fluorine>(args.This());
  obj->counter_ += 1;

  return scope.Close(Number::New(obj->counter_));
}

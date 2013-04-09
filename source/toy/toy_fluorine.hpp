#define BUILDING_NODE_EXTENSION
#ifndef FLUORINE_H
#define FLUORINE_H

#include <node.h>

class Fluorine : public node::ObjectWrap {
 public:
  static void Init();
  static v8::Handle<v8::Value> NewInstance(const v8::Arguments& args);
  static v8::Persistent<v8::Function> constructor;

 private:
  Fluorine();
  ~Fluorine();

  static v8::Handle<v8::Value> New(const v8::Arguments& args);
  static v8::Handle<v8::Value> PlusOne(const v8::Arguments& args);
  double counter_;
};

#endif

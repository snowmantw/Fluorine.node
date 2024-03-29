#define BUILDING_NODE_EXTENSION
#ifndef GALLIUM_H
#define GALLIUM_H

#include <node.h>

class Gallium : public node::ObjectWrap {
 public:
  static void Init();
  static v8::Handle<v8::Value> NewInstance(const v8::Arguments& args);
  double Val() const { return val_; }

 private:
  Gallium();
  ~Gallium();

  static v8::Persistent<v8::Function> constructor;
  static v8::Handle<v8::Value> New(const v8::Arguments& args);
  double val_;
};

#endif

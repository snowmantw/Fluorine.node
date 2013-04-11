
#ifndef FLUORINE_UTILS
#define FLUORINE_UTILS

#include <node.h>

#include <vector>

std::vector<v8::Local<v8::Value> >* vectorFromArguments(const v8::Arguments& args);

#endif


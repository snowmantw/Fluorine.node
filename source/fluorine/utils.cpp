
#include "utils.hpp"

#include <node.h>

#include <vector>

using namespace v8;
using namespace node;
using namespace std;

vector<Local<Value> >* vectorFromArguments(const Arguments& args)
{
    int argc = args.Length();
    vector<Local<Value> >* argv = new vector<Local<Value> >;
    for (int i = 0; i < argc; i++)
    {
        argv->push_back(args[i]);
    }
    return argv;
}

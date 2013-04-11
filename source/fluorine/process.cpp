
#define BUILDING_NODE_EXTENSION

#include "process.hpp"
#include "utils.hpp"

#include <queue>

#include <node.h>

using namespace v8;
using namespace node;
using namespace std;

Process::Process(){};

Process::~Process(){};

Persistent<Function> Process::constructor;

/**
 * Initialize the class, include static members like the `constructor`.
 *
 */
void Process::Init()    // -- Don't forget the class name.
{
    // Bind the `New` function into constructor, via the template.
    Local<FunctionTemplate> tpl = FunctionTemplate::New(New);

    // -- NewSymbol, not only New.
    tpl->SetClassName(String::NewSymbol("Process"));

    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    // -- Register functions on the prototype.
    tpl->PrototypeTemplate()->Set(String::NewSymbol("next")
        ,FunctionTemplate::New(Process::Next)->GetFunction() );

    tpl->PrototypeTemplate()->Set(String::NewSymbol("run")
        ,FunctionTemplate::New(Process::Run)->GetFunction() );

    tpl->PrototypeTemplate()->Set(String::NewSymbol("extract")
        ,FunctionTemplate::New(Process::Extract)->GetFunction() );

    constructor = Persistent<Function>::New(tpl->GetFunction());
}

// ---- 

/**
 * Construct the process.
 * 
 * @param args Most important is the this object.
 * @return The wrapped object from arguments' "This".
 */
Handle<Value> Process::New(const Arguments& args)
{
    HandleScope scope;

    Process* process = new Process();

    // -- Note register functions on the prototype is not a part of constructor.
    //    At least not in this constructor C++ function.
    //    It need to use `PrototypeTemplate`, @see the Init member function.
    // -- But other inner data still can be setup here.

    // -- ?? Don't know how can I do deconstructor to pevent the dangling pointer of the queue.
    process->m_pqueue = new queue<Persistent<Function> >();

    process->Wrap(args.This()); 

    return args.This();
}

/**
 * Factory method for export "Process" function.
 * In Javascript, calling "Process()" will actually call this function.
 *
 * @return The instance of "Process" function.
 */
Handle<Value> Process::NewInstance(const Arguments& args)
{
    HandleScope scope;

    const unsigned argc = 0;
    Handle<Value>  argv[argc] = {};
    Local<Object> instance = constructor->NewInstance(argc, argv);

    return scope.Close(instance);
}

/**
 * Define the next step this process should execute.
 * Every step in the Process will receive previous one's result as it's only one argument
 * before the tuple extracting-packeting implemeted. -- TODO
 * 
 * So user should pass a fuction can surely accept the right result of previous one.
 *
 * @param args Need pass a Javascript function in as the next step.
 * @return The Process instance itself.
 */
Handle<Value> Process::Next(const Arguments& args)
{
    HandleScope scope;

    // -- Unlike `Local<Function>::Cast`, use `Persistent<Function>::New` to cast it
    // -- !! Note the function passin function is `Handle<Function>`, it need to be casted manually before `New` it,
    //       or compiler will complain like : "v8.h:225:5: Error：... from 「v8::Value*」 to 「v8::Function*」 ... [-fpermissive]

    Persistent<Function> step = Persistent<Function>::New(Handle<Function>::Cast(args[0]));

    // -- Access "this" instance via unwrap it from arguments.
    Process* process = ObjectWrap::Unwrap<Process>(args.This());

    // -- Don't forget the arror, you're writting C++ !
    process->m_pqueue->push(step);

    return args.This();
}

/**
 * Execute one step of the process with a result from previous step.
 * The passed in result will become the process' current result, until another run update it.
 * 
 * @param args Pass any one parameter to let the function execute.
 * @return Undefined, nothing.
 */
Handle<Value> Process::Run(const Arguments& args)
{
    HandleScope scope;

    Process* process = ObjectWrap::Unwrap<Process>(args.This());
    process->m_result = Persistent<Value>::New(args[0]);
    Persistent<Function> step = process->m_pqueue->front();
    process->m_pqueue->pop();

    vector<Local<Value> >* argv = vectorFromArguments(args);

    // Steps should execute under the plain context; 
    // they're expecting become closure already.
    step->Call(Object::New(), args.Length(), &(*argv)[0] );

    return scope.Close(Undefined());
}

/**
 * Extract the result of this process.
 *
 * @return Object, any type of result.
 */
Handle<Value> Process::Extract(const Arguments& args)
{
    HandleScope scope;

    Process* process = ObjectWrap::Unwrap<Process>(args.This());

    return scope.Close(process->m_result);
}

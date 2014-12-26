#include <node.h>
#include <v8.h>

using namespace v8;

Handle<Value> Method(const Arguments& args) {
  HandleScope scope;

  if (args.Length() >= 1) {
    String::Utf8Value str(args[0]);
    char *cstr = *str;
    printf("%s\n", cstr);
  }
  return scope.Close(Boolean::New(true));
}

void init(Handle<Object> target) {
  target->Set(String::NewSymbol("print"), FunctionTemplate::New(Method)->GetFunction());
}

NODE_MODULE(hello, init)

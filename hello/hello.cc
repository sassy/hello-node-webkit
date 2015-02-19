#include <node.h>

using namespace v8;

void Hello(const FunctionCallbackInfo<Value>& args) {
  Isolate *isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  //ʸ�����������������ͤ������Ԥ���
  args.GetReturnValue().Set(String::NewFromUtf8(isolate, "world"));
}

void Add(const FunctionCallbackInfo<Value>& args) {
  Isolate *isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  //�����ο�������å�
  if (args.Length() < 2) {
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
    return;
  }

  //�����η�������å�
  if (!args[0]->IsNumber() || !args[1]->IsNumber()) {
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
    return;
  }

  Local<Number> num = Number::New(isolate, args[0]->NumberValue() + args[1]->NumberValue());
  args.GetReturnValue().Set(num);
}

void AddWithCallback(const FunctionCallbackInfo<Value>& args) {
  Isolate *isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  //�����ο�������å�
  if (args.Length() < 4) {
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
    return;
  }

  // success������Хå�(��1����)����Ф�
  Local<Function> scb = Local<Function>::Cast(args[0]);
  // error������Хå�(��2����)����Ф�
  Local<Function> ecb = Local<Function>::Cast(args[1]);

  //�����η�������å�
  if (!args[2]->IsNumber() || !args[3]->IsNumber()) {
    //���顼������Хå���Ƥ�
    const unsigned argc = 1;
    Local<Value> argv[argc] = { String::NewFromUtf8(isolate, "Wrong arguments") };
    ecb->Call(isolate->GetCurrentContext()->Global(), argc, argv);
    return;
  }

  // �׻�
  Local<Number> num = Number::New(isolate, args[2]->NumberValue() + args[3]->NumberValue());
  const unsigned argc = 1;

  //��̤򥳡���Хå�����1�������Ϥ�
  Local<Value> argv[argc] = { num };
  scb->Call(isolate->GetCurrentContext()->Global(), argc, argv);
}


void init(Handle<Object> exports) {
  NODE_SET_METHOD(exports, "hello", Hello);
  NODE_SET_METHOD(exports, "add", Add);
  NODE_SET_METHOD(exports, "addWithCallback", AddWithCallback);
}

NODE_MODULE(hello, init)

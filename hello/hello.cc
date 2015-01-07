#include <node.h>

using namespace v8;

void Hello(const FunctionCallbackInfo<Value>& args) {
  Isolate *isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  //文字列を生成して戻り値の設定を行う。
  args.GetReturnValue().Set(String::NewFromUtf8(isolate, "world"));
}

void Add(const FunctionCallbackInfo<Value>& args) {
  Isolate *isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  //引数の数をチェック
  if (args.Length() < 2) {
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
    return;
  }

  //引数の型をチェック
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

  //引数の数をチェック
  if (args.Length() < 4) {
    isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
    return;
  }

  // successコールバック(第1引数)を取り出す
  Local<Function> scb = Local<Function>::Cast(args[0]);
  // errorコールバック(第2引数)を取り出す
  Local<Function> ecb = Local<Function>::Cast(args[1]);

  //引数の型をチェック
  if (!args[2]->IsNumber() || !args[3]->IsNumber()) {
    //エラーコールバックを呼ぶ
    const unsigned argc = 1;
    Local<Value> argv[argc] = { String::NewFromUtf8(isolate, "Wrong arguments") };
    ecb->Call(isolate->GetCurrentContext()->Global(), argc, argv);
    return;
  }

  // 計算
  Local<Number> num = Number::New(isolate, args[2]->NumberValue() + args[3]->NumberValue());
  const unsigned argc = 1;

  //結果をコールバックの第1引数に渡す
  Local<Value> argv[argc] = { num };
  scb->Call(isolate->GetCurrentContext()->Global(), argc, argv);
}


void init(Handle<Object> exports) {
  NODE_SET_METHOD(exports, "hello", Hello);
  NODE_SET_METHOD(exports, "add", Add);
  NODE_SET_METHOD(exports, "addWithCallback", AddWithCallback);
}

NODE_MODULE(hello, init)

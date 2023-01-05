// 引用 node-addon-api 的 头文件
#include<napi.h>

// 定义一个返回值为 Napi::String 的 函数
// CallbackInfo 是个回调函数类型  info 里面存的是 JS 调用这个函数时的一些信息
Napi::String Method(const Napi::CallbackInfo& info) {
  // env 是个环境变量，提供一些执行上下文的环境
  Napi::Env env = info.Env();
  // 返回一个构造好的 Napi::String 类型的值
  // New是个静态方法，一般第一个参数是当前执行环境的上下变量，第二个是对应的值
  return Napi::String::New(env, "hello world~");
}

// 导出注册函数
// 这里其实等同于 exports = { hello: Method }
Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(
    Napi::String::New(env, "hello"),
    Napi::Function::New(env, Method)
  );
  return exports;
}
// node-addon-api 中用于注册函数的宏
// hello 为 key, 可以是任意变量
// Init 则会注册的函数
NODE_API_MODULE(hello, Init);

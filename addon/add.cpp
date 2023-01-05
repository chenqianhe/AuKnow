#include<napi.h>

// 因为这里可能会遇到抛 error 的情况，因此返回值类型设置为 Value
// Value 包含了 Napi 里面的所有数据结构
Napi::Value Add(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  if (info.Length() < 2) {
  // 异常处理相关的 API 可以参考
  // 不过这里可以看到 cpp 里面抛异常代码很麻烦... 建议这里可以在 js 端就处理好
  // https://github.com/nodejs/node-addon-api/blob/main/doc/error_handling.md
    Napi::TypeError::New(env, "Number of arg wrong").ThrowAsJavaScriptException();
    return env.Null();
  }

  double a = info[0].As<Napi::Number>().DoubleValue();
  double b = info[1].As<Napi::Number>().DoubleValue();
  Napi::Number num = Napi::Number::New(env, a + b);
  return num;
}

// exports = { add: Add };
Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(
    Napi::String::New(env, "add"),
    Napi::Function::New(env, Add)
  );
  return exports;
}

NODE_API_MODULE(addab, Init);

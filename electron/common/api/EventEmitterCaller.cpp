// Copyright (c) 2015 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include "common/api/EventEmitterCaller.h"

#include "node/include/node.h"

namespace mate {

namespace internal {

v8::Local<v8::Value> callEmitWithArgs(v8::Isolate* isolate, v8::Local<v8::Object> obj, ValueVector* args) {
#if V8_MAJOR_VERSION == 5
    // Perform microtask checkpoint after running JavaScript.
    v8::MicrotasksScope script_scope(isolate, v8::MicrotasksScope::kRunMicrotasks);
#endif
    // Use node::MakeCallback to call the callback, and it will also run pending
    // tasks in Node.js.
    return node::MakeCallback(isolate, obj, "emit", args->size(), &args->front()); 
}

}  // namespace internal

}  // namespace mate

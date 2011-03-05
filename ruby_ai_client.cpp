#include "ruby.h"
#include <stdio.h>

#include <windows.h>

#include <string>

typedef VALUE(*RubyFunction)(ANYARGS);

static VALUE IAmNative(VALUE self) {
  return Qtrue;
}

extern "C"
void Init_RubyBWAPIClient() {
  VALUE m = rb_define_module("Native");
  rb_define_singleton_method(m, "native?", (RubyFunction)IAmNative, 0);
}

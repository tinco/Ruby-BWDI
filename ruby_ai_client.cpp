#include "ruby.h"
#include <stdio.h>

#include <windows.h>

#include <string>

// some debugging stuff:
#define _ASSERT(expr)

#include <UTIL/Exceptions.h>
#include <BWDI.h>

typedef VALUE(*RubyFunction)(ANYARGS);

static VALUE IAmNative(VALUE self) {
  BWDI::SessionInfo info;
  info.usingBWDIVersion = 0;
  strncpy(info.moduleName, "Test", sizeof(info.moduleName));
  info.allowMultipleSlots = true;
  info.allowProtoss = true;
  info.allowTerran = true;
  info.allowZerg = true;
  BWDI::SessionHandle session = BWDI::BWDICreate(&info);

  return Qtrue;
}

extern "C"
void Init_RubyBWAPIClient() {
  VALUE m = rb_define_module("Native");
  rb_define_singleton_method(m, "native?", (RubyFunction)IAmNative, 0);
}

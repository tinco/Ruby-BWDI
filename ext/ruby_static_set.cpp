#include <ruby_bwdi.h>
#include <ruby_static_set.h>
#include <object_cache.h>

void Init_Static_Set() {
  VALUE mBWDI = rb_define_module("RubyBWDI");
  VALUE cStaticSet = rb_define_class_under(mBWDI, "StaticSet", rb_cObject);
}

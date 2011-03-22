#include <ruby_bwdi.h>

VALUE rb_wrap_unit_state(BWDI::UnitState) {
  VALUE mBWDI = rb_define_module("RubyBWDI");
  VALUE cStaticSet = rb_define_class_under(mBWDI, "UnitState", rb_cObject);
  VALUE obj = Data_Wrap_Struct(cStaticSet, 0, 0, ss);
  if(false) { SS_at<T, SIZE>(0, 0); } // Force compilation of SS_at
  rb_define_singleton_method(obj, "[]", (RubyFunction)SS_at<T, SIZE>, 1);

}

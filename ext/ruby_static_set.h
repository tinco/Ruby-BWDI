void Init_Static_Set();

template <class T, int SIZE>
VALUE SS_at(VALUE self, VALUE index) {
  Util::StaticSet<T, SIZE> *ss;
  typedef Util::StaticSet<T, SIZE> t;
  Data_Get_Struct(self, t, ss);  
  T element = ss->at(FIX2INT(index));
  return getCached(element);
}

template <class T, int SIZE>
VALUE SS_initialize(Util::StaticSet<T, SIZE> * ss) {
  VALUE mBWDI = rb_define_module("RubyBWDI");
  VALUE cStaticSet = rb_define_class_under(mBWDI, "StaticSet", rb_cObject);
  VALUE obj = Data_Wrap_Struct(cStaticSet, 0, 0, ss);
  if(false) { SS_at<T, SIZE>(0, 0); } // Force compilation of SS_at
  rb_define_singleton_method(obj, "[]", (RubyFunction)SS_at<T, SIZE>, 1);
  return obj;
}

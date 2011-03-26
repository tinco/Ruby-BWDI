#include <ruby_bwdi.h>

using namespace BWDI;

template<>
VALUE prepareValue<int>(int value) {
  return INT2FIX(value);
}

template<>
VALUE prepareValue<bool>(bool value) {
  return value ? Qtrue : Qfalse;
}

template<>
VALUE prepareValue<double>(double value) {
  return rb_float_new(value);
}

template<>
VALUE prepareValueByReference<Position>(Position * value) {
  return rb_ary_new3(2, INT2FIX(value->x), INT2FIX(value->y));
}

template<>
VALUE prepareValueByReference<Util::Point<double>>(Util::Point<double> * value) {
  return Qnil; //TODO implement point class
}

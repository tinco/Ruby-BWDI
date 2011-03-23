#include <ruby_bwdi.h>

template<>
VALUE prepareValue<int>(int value) {
  return INT2FIX(value);
}

template<>
VALUE prepareValue<bool>(bool value) {
  return value ? Qtrue : Qfalse;
}

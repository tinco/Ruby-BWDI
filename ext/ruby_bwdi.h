#include "ruby.h"
#include <stdio.h>

#include <windows.h>

#include <string>

// some debugging stuff:
#define _ASSERT(expr)

#include <UTIL/Exceptions.h>
#include <BWDI.h>

typedef VALUE(*RubyFunction)(ANYARGS);

template<typename T> VALUE prepareValue(T value);
template<typename T> VALUE prepareValueByReference(T * value);

template<typename T, typename C, T C::*M>
VALUE getStructMember(VALUE self) {
  C * str;
  Data_Get_Struct(self, C, str);
  return prepareValue<T>(str->*M);
}

template<typename T, typename C, T C::*M>
VALUE getStructMemberP(VALUE self) {
  C * str;
  Data_Get_Struct(self, C, str);
  return prepareValueByReference<T>(&(str->*M));
}

#define DEFINE_GETTER(THIS, FUNCNAME, TYPE, STRUCT, MEMBER, P...) \
if(false) \
{ \
getStructMember##P<TYPE, STRUCT, &STRUCT::MEMBER>(Qnil); \
} \
rb_define_method(THIS, FUNCNAME, (RubyFunction)getStructMember##P<TYPE, STRUCT, &STRUCT::MEMBER>, 0);

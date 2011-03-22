#include "ruby.h"
#include <stdio.h>

#include <windows.h>

#include <string>

// some debugging stuff:
#define _ASSERT(expr)

#include <UTIL/Exceptions.h>
#include <BWDI.h>

typedef VALUE(*RubyFunction)(ANYARGS);

template<typename T, typename C, T C::*M>
VALUE getStructMember(VALUE self) {
  C * str;
  Data_Get_Struct(self, C, str);
  return INT2FIX(str->*M);
}

#define DEFINE_GETTER(THIS, FUNCNAME, TYPE, STRUCT, MEMBER) \
if(false) \
{ \
getStructMember<TYPE, STRUCT, &MEMBER>(Qnil); \
} \
rb_define_method(THIS, FUNCNAME, (RubyFunction)getStructMember<TYPE, STRUCT, &MEMBER>, 0);

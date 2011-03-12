#include "ruby.h"
#include <stdio.h>

#include <windows.h>

#include <string>

// some debugging stuff:
#define _ASSERT(expr)

#include <UTIL/Exceptions.h>
#include <BWDI.h>

typedef VALUE(*RubyFunction)(ANYARGS);

template<T C::*M, VALUE (*PREPARE)(T), typename T, typename C>
VALUE getMember(VALUE self) {
  C * us;
  Data_Get_Struct(self, C, us);
  return PREPARE(us->*M);
}

#define DEFINE_GETTER(THIS, FUNCNAME, MEMBER, PREPARE) \
if(false) \
{ \
getMember<&MEMBER, PREPARE>(0); \
} \
rb_define_method(THIS, FUNCNAME, (RubyFunction)getMember<&MEMBER, PREPARE>, 0);

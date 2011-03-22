#include "ruby.h"
#include <stdio.h>

#include <windows.h>

#include <string>

// some debugging stuff:
#define _ASSERT(expr)

#include <UTIL/Exceptions.h>
#include <BWDI.h>

typedef VALUE(*RubyFunction)(ANYARGS);

template<typename T, typename C, T C::*M, VALUE (*PREPARE)(T)>
VALUE getMember(VALUE self) {
  C * us;
  Data_Get_Struct(self, C, us);
  return PREPARE(us->*M);
}

#define DEFINE_GETTER(THIS, FUNCNAME, MEMBER, PREPARE) \
if(false) \
{ \
getMember<int, BWDI::UnitState, &MEMBER, PREPARE>(Qnil); \
} \
rb_define_method(THIS, FUNCNAME, (RubyFunction)getMember<int, BWDI::UnitState, &MEMBER, PREPARE>, 0);

#include "ruby.h"
#include <stdio.h>

#include <windows.h>

#include <string>

// some debugging stuff:
#define _ASSERT(expr)

#include <UTIL/Exceptions.h>
#include <BWDI.h>

typedef VALUE(*RubyFunction)(ANYARGS);

namespace RubyBDWI {
  BWDI::StaticGameData *sgd;
  VALUE game;

  static VALUE initialize(VALUE self, VALUE ai) {
    BWDI::SessionInfo info;
    info.usingBWDIVersion = 0;
    strncpy(info.moduleName, "RubyBWDI", sizeof(info.moduleName));
    info.allowMultipleSlots = true;
    info.allowProtoss = true;
    info.allowTerran = true;
    info.allowZerg = true;
    BWDI::SessionHandle session = BWDI::BWDICreate(&info);
    game = Qnil;
    
    // position of global info output
    BWDI::Position statPos;
    while(true) {
      // synch with BWDI
      BWDI::SessionState sstate = BWDI::BWDIWaitForNextEvent();
      if(sstate == BWDI::SessionState_InternalError) {
        rb_funcall(ai, rb_intern("end"), 0);
        return Qfalse;
      }

      // handle onMatchStart
      if(sstate == BWDI::SessionState_MatchStart)
      {
        sgd = BWDI::BWDIGetStaticGameData();
        rb_funcall(ai, rb_intern("start"), 1, game);
      }
      // handle next frame
      if(sstate == BWDI::SessionState_MatchFrame)
      {
        rb_funcall(ai, rb_intern("on_frame"), 0);
      }
    }    
    return Qtrue;
  }
}

extern "C"
void Init_RubyBWDI() {
  VALUE m = rb_define_module("RubyBWDI");
  rb_define_singleton_method(m, "run", (RubyFunction)RubyBDWI::initialize, 1);
}

#include <ruby_bwdi.h>
#include <object_cache.h>
#include <ruby_static_set.h>
#include <rb_unit_state.h>

VALUE mBWDI;
BWDI::StaticGameData *sgd;

void Init_Game();

VALUE cGame;

namespace RubyBWDI {
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
    game = rb_funcall(cGame, rb_intern("new"), 0);
    
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
  mBWDI = rb_define_module("RubyBWDI");
  rb_define_singleton_method(mBWDI, "run", (RubyFunction)RubyBWDI::initialize, 1);
  Init_Static_Set();
  Init_Game();
  Init_UnitState();
}

VALUE g_PlayerId(VALUE self) { return INT2FIX(sgd->self); }

void Init_Game() {
  cGame = rb_define_class_under(mBWDI, "Game", rb_cObject);
  rb_define_method(cGame, "player_id", (RubyFunction)g_PlayerId, 0);
  VALUE unit_array = SS_initialize<BWDI::UnitState, BWDI::unitMaxCount>(&sgd->units);
  rb_define_const(cGame, "Units", unit_array);
}

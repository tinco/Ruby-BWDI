#include <ruby_bwdi.h>
#include <object_cache.h>

using namespace BWDI;

VALUE rb_wrap_unit_state(BWDI::UnitState * us) {
  VALUE mBWDI = rb_define_module("RubyBWDI");
  VALUE cUnitState = rb_define_class_under(mBWDI, "UnitState", rb_cObject);
  VALUE obj = Data_Wrap_Struct(cUnitState, 0, 0, us);
  return obj;
}

VALUE rb_clearance_level(VALUE self) {
  UnitStateNoticed * state;
  Data_Get_Struct(self, UnitStateNoticed, state);
  using namespace ClearanceLevels;
  switch(state->clearanceLevel) {
    case Noticed: return rb_intern("noticed");
    case Visible: return rb_intern("visible");
    case Full: return rb_intern("full");
    default: return rb_intern("none");
  }
}

VALUE rb_unit_type(VALUE self) {
  UnitStateNoticed * state;
  Data_Get_Struct(self, UnitStateNoticed, state);
  return getCached<UnitType>(state->type);
}

void Init_UnitState() {
  VALUE mBWDI = rb_define_module("RubyBWDI");
  VALUE cUnitState = rb_define_class_under(mBWDI, "UnitState", rb_cObject);

  // UnitStateNoticed
  // s/\(\w\+\) \(\w\+\)/DEFINE_GETTER(cUnitState, "\2", \1, UnitStateNoticed, \2)/

  DEFINE_GETTER(cUnitState, "sighting", int, UnitStateNoticed, sightingID);
  DEFINE_GETTER(cUnitState, "remove_timer", int, UnitStateNoticed, removeTimer);
  DEFINE_GETTER(cUnitState, "accelerating?", bool, UnitStateNoticed, isAccelerating);
  DEFINE_GETTER(cUnitState, "moving?", bool, UnitStateNoticed, isMoving);
  DEFINE_GETTER(cUnitState, "idle?", bool, UnitStateNoticed, isIdle);
  DEFINE_GETTER(cUnitState, "angle", double, UnitStateNoticed, angle);
  DEFINE_GETTER(cUnitState, "under_storm?", bool, UnitStateNoticed, isUnderStorm);

  DEFINE_GETTER(cUnitState, "position", Position, UnitStateNoticed, position, P);
  DEFINE_GETTER(cUnitState, "velocity", Util::Point<double>, UnitStateNoticed, velocity, P);

  rb_define_method(cUnitState, "clearance_level", (RubyFunction)rb_clearance_level, 0);
  rb_define_method(cUnitState, "type", (RubyFunction)rb_unit_type, 0);

  // UnitStateVisible
  DEFINE_GETTER(cUnitState, "hitpoints", int, UnitStateVisible, hitPoints);
}


#include "ruby.h"
#include <stdio.h>

#include <windows.h>

#include <string>

// some debugging stuff:
#define _ASSERT(expr)

#include <UTIL/Exceptions.h>
#include <BWDI.h>

typedef VALUE(*RubyFunction)(ANYARGS);

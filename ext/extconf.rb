require 'mkmf'

$CFLAGS << " -Wall -Ibwdi -fpermissive --std=c++0x"

abort unless find_library 'BWDI', nil

create_makefile 'RubyBWDI'

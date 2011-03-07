require 'mkmf'

$CFLAGS << " -Wall -Ibwdi -fpermissive"

abort unless find_library 'BWDI', nil

create_makefile 'RubyBWAPIClient'

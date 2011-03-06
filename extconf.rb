require 'mkmf'

$CFLAGS << " -Ibwdi -fpermissive" 
abort unless find_library 'BWDI', nil, 'bwdi/DEBUG'

create_makefile 'RubyBWAPIClient'

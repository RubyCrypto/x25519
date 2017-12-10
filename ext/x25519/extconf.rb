# frozen_string_literal: true

require "mkmf"

# rubocop:disable Style/GlobalVars
$CFLAGS << " -Wall -O3 -pedantic -std=c99 -mbmi -mbmi2 -march=native -mtune=native"

unless have_func("posix_memalign", "stdlib.h")
  raise "posix_memalign() is not available on this platform"
end

create_makefile "x25519"

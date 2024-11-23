# frozen_string_literal: true

# rubocop:disable Style/GlobalVars

require "mkmf"

if RUBY_PLATFORM.match?(/x86_64|x64/)
  $CFLAGS << " -Wall -O3 -pedantic -std=c99 -mbmi -mbmi2 -march=haswell"

  create_makefile "x25519_precomputed"
else
  File.write("Makefile", "install clean: ;")
end

# rubocop:enable Style/GlobalVars

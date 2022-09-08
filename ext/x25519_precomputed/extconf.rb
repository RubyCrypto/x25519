# frozen_string_literal: true

# rubocop:disable Style/GlobalVars

require "mkmf"

if RUBY_PLATFORM =~ /arm64-darwin|aarch64-linux/
  File.write("Makefile", "install clean: ;")
else
  $CFLAGS << " -Wall -O3 -pedantic -std=c99 -mbmi -mbmi2 -march=haswell"

  create_makefile "x25519_precomputed"
end

# rubocop:enable Style/GlobalVars

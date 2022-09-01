# frozen_string_literal: true

# rubocop:disable Style/GlobalVars

unless RUBY_PLATFORM =~ /arm64-darwin/
  require "mkmf"

  $CFLAGS << " -Wall -O3 -pedantic -std=c99 -mbmi -mbmi2 -march=haswell"

  create_makefile "x25519_precomputed"
end

# rubocop:enable Style/GlobalVars

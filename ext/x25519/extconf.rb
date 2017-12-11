# frozen_string_literal: true

# rubocop:disable Style/GlobalVars

require "mkmf"

abort("missing posix_memalign()") unless have_func("posix_memalign", "stdlib.h")

$INCFLAGS << " -I$(srcdir)/ref10 -I$(srcdir)/rfc7748_precomputed"

# Check for Intel 4th Gen Core CPU features
# TODO: move this detection completely to runtime
cputest_c = <<SRC
  #{File.read(File.expand_path('cputest.c', __dir__))}
  int main() {
    return check_4th_gen_intel_core_features() != 1;
  }
SRC

if try_run(cputest_c)
  $defs.push("-DHAVE_4TH_GEN_INTEL_CORE")
  $CFLAGS << " -Wall -O3 -pedantic -std=c99 -mbmi -mbmi2 -march=native -mtune=native"
  $srcs = Dir.glob(File.join(__dir__, "**", "*.c"))
else
  # Do not include the rfc7748_precomputed sources if we do not have a 4th gen+ Core CPU
  $srcs = Dir.glob(File.join(__dir__, "*.c")) + Dir.glob(File.expand_path("ref10/*.c", __dir__))
end

$objs = $srcs.map { |src| src.sub(/\.c$/, ".o") }

create_makefile "x25519"

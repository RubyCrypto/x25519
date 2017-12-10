# frozen_string_literal: true

require "bundler/setup"
require "x25519"

RSpec.configure do |config|
  # Enable flags like --only-failures and --next-failure
  config.example_status_persistence_file_path = ".rspec_status"

  # Disable RSpec exposing methods globally on `Module` and `main`
  config.disable_monkey_patching!

  config.expect_with :rspec do |c|
    c.syntax = :expect
  end
end

# Convert a binary string to hex
def hex(string)
  string.unpack("H*").first
end

# Parse a hex string to binary
def unhex(string)
  [string].pack("H*")
end

TestVector = Struct.new(:scalar, :input_coord, :output_coord)

# X25519 test vectors from RFC 7748
X25519_TEST_VECTORS = [
  TestVector.new(
    "a546e36bf0527c9d3b16154b82465edd62144c0ac1fc5a18506a2244ba449ac4",
    "e6db6867583030db3594c1a424b15f7c726624ec26b3353b10a903a6d0ab1c4c",
    "c3da55379de9c6908e94ea4df28d084f32eccf03491c71f754b4075577a28552"
  ),
  TestVector.new(
    "4b66e9d4d1b4673c5ad22691957d6af5c11b6421e0ea01d42ca4169e7918ba0d",
    "e5210f12786811d3f4b7959d0538ae2c31dbe7106fc03c3efc4cd549c715a493",
    "95cbde9476e8907d7aade45cb4b873f88b595a68799fa152e6f8f7647aac7957"
  )
].freeze

# frozen_string_literal: true

require "bundler/setup"
require "x25519"
require "support/provider_examples"

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

# frozen_string_literal: true

require "securerandom"

require "x25519/version"

require "x25519/montgomery_u"
require "x25519/scalar"
require "x25519/test_vectors"

# Native extension backends
require "x25519_ref10"
require "x25519_precomputed"

# The X25519 elliptic curve Diffie-Hellman algorithm
module X25519
  module_function

  # Size of an X25519 key (public or private) in bytes
  KEY_SIZE = 32

  # Raised when the built-in self-test fails
  SelfTestFailure = Class.new(StandardError)

  # ref10 is the default provider
  @provider = X25519::Provider::Ref10

  # X25519::Precomputed requires a 4th generation Intel Core CPU or newer,
  # so only enable it if we detect we're on a supported platform. Otherwise,
  # fall back to the ref10 portable C implementation.
  @provider = X25519::Provider::Precomputed if X25519::Provider::Precomputed.available?

  # Selected provider based on the logic above
  def provider
    @provider
  end

  # Raw Diffie-Hellman function that acts directly on bytestrings. An
  # alternative to the object-oriented API
  #
  # @param scalar_bytes [String] a serialized private scalar
  # @param montgomery_u_bytes [String] a point we wish to multiply by the scalar
  #
  # @return [String] resulting point, serialized as bytes
  def diffie_hellman(scalar_bytes, montgomery_u_bytes)
    validate_key_bytes(scalar_bytes)
    validate_key_bytes(montgomery_u_bytes)
    X25519.provider.scalarmult(scalar_bytes, montgomery_u_bytes)
  end

  # Ensure a serialized key meets the requirements
  def validate_key_bytes(key_bytes)
    raise TypeError, "expected String, got #{key_bytes.class}" unless key_bytes.is_a?(String)
    return true if key_bytes.bytesize == KEY_SIZE
    raise ArgumentError, "expected #{KEY_SIZE}-byte String, got #{key_bytes.bytesize}"
  end

  # Perform a self-test to ensure the selected provider is working
  def self_test
    X25519::TestVectors::VARIABLE_BASE.each do |v|
      shared_secret = provider.scalarmult([v.scalar].pack("H*"), [v.input_coord].pack("H*"))
      raise SelfTestFailure, "self test failed!" unless shared_secret.unpack("H*").first == v.output_coord
    end

    X25519::TestVectors::FIXED_BASE.each do |v|
      public_key = provider.scalarmult_base([v.scalar].pack("H*"))
      raise SelfTestFailure, "self test failed!" unless public_key.unpack("H*").first == v.output_coord
    end

    true
  end
end

# Automatically run self-test when library loads
X25519.self_test

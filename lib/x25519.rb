# frozen_string_literal: true

require "securerandom"

require "x25519/version"

require "x25519/montgomery_u"
require "x25519/scalar"

# Native extension backends
require "x25519_ref10"
require "x25519_precomputed"

# The X25519 elliptic curve Diffie-Hellman algorithm
module X25519
  module_function

  # Size of an X25519 key (public or private) in bytes
  KEY_SIZE = 32

  # X25519::Precomputed requires a 4th generation Intel Core CPU or newer,
  # so only enable it if we detect we're on a supported platform. Otherwise,
  # fall back to the ref10 portable C implementation.
  @provider = if X25519::Precomputed.available?
                X25519::Precomputed
              else
                X25519::Ref10
              end

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
    X25519.provider.multiply(scalar_bytes, montgomery_u_bytes)
  end

  # Ensure a serialized key meets the requirements
  def validate_key_bytes(key_bytes)
    raise TypeError, "expected String, got #{key_bytes.class}" unless key_bytes.is_a?(String)
    return true if key_bytes.bytesize == KEY_SIZE
    raise ArgumentError, "expected #{KEY_SIZE}-byte String, got #{key_bytes.bytesize}"
  end
end

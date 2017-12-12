# frozen_string_literal: true

module X25519
  # X25519 private keys
  #
  # Scalars are the integer component of scalar multiplication, multiplied
  # against an elliptic curve point.
  class Scalar
    # Securely generate a random scalar
    def self.generate
      new(SecureRandom.random_bytes(X25519::KEY_SIZE))
    end

    # Create an X25519 scalar object from a bytestring
    #
    # @param bytes [String] 32-byte random secret scalar
    def initialize(bytes)
      X25519.validate_key_bytes(bytes)
      @bytes = bytes
    end

    # Variable-base scalar multiplication a.k.a. Diffie-Hellman
    #
    # This can be used to obtain a shared secret from a public key
    #
    # @param montgomery_u [X25519::MontgomeryU] coordinate of the public key/point to perform D-H with
    #
    # @return [X25519::MontgomeryU] resulting point (i.e. D-H shared secret)
    def multiply(montgomery_u)
      raise TypeError, "expected X25519::MontgomeryU, got #{montgomery_u}" unless montgomery_u.is_a?(MontgomeryU)
      MontgomeryU.new(X25519.provider.multiply(@bytes, montgomery_u.to_bytes))
    end
    alias diffie_hellman multiply

    # Fixed-base scalar multiplication. Calculates a public key from a
    # private scalar
    #
    # @return [X25519::MontgomeryU] resulting point (i.e. public key)
    def multiply_base
      MontgomeryU.new(X25519.provider.multiply_base(@bytes))
    end
    alias public_key multiply_base

    # Return a bytestring representation of this scalar
    #
    # @return [String] scalar converted to a bytestring
    def to_bytes
      @bytes
    end

    # String inspection that does not leak the private scalar
    def inspect
      to_s
    end
  end
end

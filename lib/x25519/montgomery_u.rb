# frozen_string_literal: true

module X25519
  # X25519 public keys and shared secrets
  #
  # Montgomery-u coordinates of points on the elliptic curve used by X25519
  # (a.k.a. Curve25519)
  class MontgomeryU
    # Create an object representing a Montgomery-u coordinate from a bytestring
    #
    # @param bytes [String] 32-byte compressed Montgomery-u coordinate
    def initialize(bytes)
      X25519.validate_key_bytes(bytes)

      # The point located at a Montgomery-u coordinate of zero always returns
      # the point at zero regardless of which scalar it's multiplied with
      raise InvalidKeyError, "degenerate public key" if bytes == ("\0" * KEY_SIZE)

      @bytes = bytes
    end

    # Return a compressed Montgomery-u coordinate serialized as a bytestring
    #
    # @return [String] bytestring serialization of a Montgomery-u coordinate
    def to_bytes
      @bytes
    end

    # Show hex representation of serialized coordinate in string inspection
    def inspect
      "#<#{self.class}:#{@bytes.unpack('H*').first}>"
    end
  end
end

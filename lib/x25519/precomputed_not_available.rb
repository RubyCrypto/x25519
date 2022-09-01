# frozen_string_literal: true

module X25519
  module Provider
    # We need this class and method even if we can't compile x25519_precomputed
    class Precomputed
      def self.available?
        false
      end
    end
  end
end

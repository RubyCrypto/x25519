# frozen_string_literal: true

module X25519
  # Known-good inputs and outputs for X25519 functions
  module TestVectors
    # Test vector for variable-base scalar multiplication
    VariableBaseVector = Struct.new(:scalar, :input_coord, :output_coord)

    # X25519 variable-base test vectors from RFC 7748
    VARIABLE_BASE = [
      VariableBaseVector.new(
        "a546e36bf0527c9d3b16154b82465edd62144c0ac1fc5a18506a2244ba449ac4",
        "e6db6867583030db3594c1a424b15f7c726624ec26b3353b10a903a6d0ab1c4c",
        "c3da55379de9c6908e94ea4df28d084f32eccf03491c71f754b4075577a28552"
      ),
      VariableBaseVector.new(
        "4b66e9d4d1b4673c5ad22691957d6af5c11b6421e0ea01d42ca4169e7918ba0d",
        "e5210f12786811d3f4b7959d0538ae2c31dbe7106fc03c3efc4cd549c715a493",
        "95cbde9476e8907d7aade45cb4b873f88b595a68799fa152e6f8f7647aac7957"
      )
    ].freeze

    # Test vector for fixed-base scalar multiplication
    FixedBaseVector = Struct.new(:scalar, :output_coord)

    # X25519 fixed-base test vectors, generated via RbNaCl/libsodium
    FIXED_BASE = [
      FixedBaseVector.new(
        "a546e36bf0527c9d3b16154b82465edd62144c0ac1fc5a18506a2244ba449ac4",
        "1c9fd88f45606d932a80c71824ae151d15d73e77de38e8e000852e614fae7019"
      ),
      FixedBaseVector.new(
        "4b66e9d4d1b4673c5ad22691957d6af5c11b6421e0ea01d42ca4169e7918ba0d",
        "ff63fe57bfbf43fa3f563628b149af704d3db625369c49983650347a6a71e00e"
      )
    ].freeze
  end
end

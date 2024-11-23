# frozen_string_literal: true

RSpec.describe X25519::MontgomeryU do
  subject(:point) { described_class.new(unhex(coordinate_hex)) }

  let(:coordinate_hex) { "e6db6867583030db3594c1a424b15f7c726624ec26b3353b10a903a6d0ab1c4c" }

  describe "#to_bytes" do
    it "serializes #{described_class} as a Encoding::BINARY String" do
      bytes = point.to_bytes
      expect(bytes).to be_a String
      expect(bytes.encoding).to eq Encoding::BINARY

      expect(hex(bytes)).to eq coordinate_hex
    end
  end
end

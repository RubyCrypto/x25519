# frozen_string_literal: true

RSpec.describe X25519::Scalar do
  let(:scalar_hex) { "a546e36bf0527c9d3b16154b82465edd62144c0ac1fc5a18506a2244ba449ac4" }

  subject(:scalar) { described_class.new(unhex(scalar_hex)) }

  describe ".generate" do
    it "generates random keys" do
      # Not great, but better than nothing
      key1 = described_class.generate
      key2 = described_class.generate

      expect(key1).not_to eq key2
    end
  end

  describe "#multiply" do
    it "raises TypeError if given a non-X25519::MontgomeryU type" do
      expect { scalar.multiply(nil) }.to raise_error(TypeError)
      expect { scalar.multiply("derp") }.to raise_error(TypeError)
    end

    context "RFC 7748 test vectors" do
      it "passes the test vectors" do
        X25519_VARIABLE_BASE_TEST_VECTORS.each do |v|
          scalar = described_class.new(unhex(v.scalar))
          point  = X25519::MontgomeryU.new(unhex(v.input_coord))

          shared_secret = scalar.multiply(point)
          expect(hex(shared_secret.to_bytes)).to eq v.output_coord
        end
      end
    end
  end

  describe "#to_bytes" do
    it "serializes #{described_class} as a Encoding::BINARY String" do
      bytes = scalar.to_bytes
      expect(bytes).to be_a String
      expect(bytes.encoding).to eq Encoding::BINARY
      expect(hex(bytes)).to eq scalar_hex
    end
  end
end

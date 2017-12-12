# frozen_string_literal: true

RSpec.describe X25519 do
  it "has a version number" do
    expect(described_class::VERSION).not_to be nil
  end

  describe ".diffie_hellman" do
    it "raises ArgumentError if one of the inputs is the wrong length" do
      expect { described_class.diffie_hellman("foo", "bar") }.to raise_error(ArgumentError)
    end

    it "raises TypeError if one of the inputs is nil" do
      expect { described_class.diffie_hellman(nil, "foobar") }.to raise_error(TypeError)
    end

    context "RFC 7748 test vectors" do
      it "passes the test vectors" do
        X25519::TestVectors::VARIABLE_BASE.each do |v|
          shared_secret = described_class.diffie_hellman(unhex(v.scalar), unhex(v.input_coord))
          expect(hex(shared_secret)).to eq v.output_coord
        end
      end
    end
  end
end

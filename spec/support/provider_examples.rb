# frozen_string_literal: true

# Shared examples for all X25519::Provider backends
RSpec.shared_examples "X25519::Provider" do
  describe "#scalarmult" do
    it "passes the RFC 7748 test vectors" do
      X25519::TestVectors::VARIABLE_BASE.each do |v|
        shared_secret = described_class.scalarmult(unhex(v.scalar), unhex(v.input_coord))
        expect(hex(shared_secret)).to eq v.output_coord
      end
    end
  end

  describe "#scalarmult_base" do
    it "passes the test vectors" do
      X25519::TestVectors::FIXED_BASE.each do |v|
        public_key = described_class.scalarmult_base(unhex(v.scalar))
        expect(hex(public_key)).to eq v.output_coord
      end
    end
  end
end

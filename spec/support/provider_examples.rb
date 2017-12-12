# frozen_string_literal: true

# Shared examples for all X25519 providers (e.g. X25519::Precomputed, X25519::Ref10)
RSpec.shared_examples "X25519 provider" do
  describe "#multiply" do
    it "passes the RFC 7748 test vectors" do
      X25519_VARIABLE_BASE_TEST_VECTORS.each do |v|
        shared_secret = described_class.multiply(unhex(v.scalar), unhex(v.input_coord))
        expect(hex(shared_secret)).to eq v.output_coord
      end
    end
  end

  describe "#multiply_base" do
    it "passes the test vectors" do
      X25519_FIXED_BASE_TEST_VECTORS.each do |v|
        shared_secret = described_class.multiply_base(unhex(v.scalar))
        expect(hex(shared_secret)).to eq v.output_coord
      end
    end
  end
end

# frozen_string_literal: true

RSpec.describe X25519 do
  it "has a version number" do
    expect(X25519::VERSION).not_to be nil
  end
end

# frozen_string_literal: true

RSpec.describe X25519::Provider::Precomputed do
  if described_class.available?
    include_examples "X25519::Provider"
  else
    pending "#{described_class} provider not available on this CPU"
  end
end

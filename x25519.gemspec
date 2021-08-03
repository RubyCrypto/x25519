# frozen_string_literal: true

require File.expand_path("lib/x25519/version", __dir__)

Gem::Specification.new do |spec|
  spec.name          = "x25519"
  spec.version       = X25519::VERSION
  spec.authors       = ["Tony Arcieri"]
  spec.email         = ["bascule@gmail.com"]
  spec.summary       = "Public key cryptography library providing the X25519 Elliptic Curve Diffie-Hellman function"
  spec.description = <<-DESCRIPTION.strip.gsub(/\s+/, " ")
    An efficient public key cryptography library for Ruby providing key
    exchange/agreement via the X25519 (a.k.a. Curve25519) Elliptic Curve
    Diffie-Hellman function as described in RFC 7748.
  DESCRIPTION
  spec.homepage      = "https://github.com/RubyCrypto/x25519"
  spec.license       = "BSD-3-Clause" # https://spdx.org/licenses/BSD-3-Clause.html
  spec.files         = `git ls-files -z`.split("\x0").reject { |f| f.match(%r{^(test|spec|features)/}) }
  spec.bindir        = "exe"
  spec.executables   = spec.files.grep(%r{^exe/}) { |f| File.basename(f) }
  spec.require_paths = ["lib"]
  spec.platform      = Gem::Platform::RUBY
  spec.extensions    = ["ext/x25519_precomputed/extconf.rb", "ext/x25519_ref10/extconf.rb"]

  spec.required_ruby_version = ">= 2.5"
  spec.add_development_dependency "bundler", "~> 2.1"
end

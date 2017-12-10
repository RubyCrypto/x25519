# frozen_string_literal: true

Gem::Specification.new do |spec|
  spec.name          = "x25519"
  spec.version       = "0.0.0"
  spec.authors       = ["Tony Arcieri"]
  spec.email         = ["bascule@gmail.com"]
  spec.summary       = "Public key cryptography library providing the X25519 D-H function"
  spec.description = <<-DESCRIPTION.strip.gsub(/\s+/, " ")
    An efficient public key cryptography library for Ruby providing key
    exchange/agreement via the X25519 (a.k.a. Curve25519) Elliptic Curve
    Diffie-Hellman function as described in [RFC7748].
  DESCRIPTION
  spec.homepage      = "https://github.com/cryptosphere/x25519"
  spec.license       = "MIT"
  spec.files         = `git ls-files -z`.split("\x0").reject { |f| f.match(%r{^(test|spec|features)/}) }
  spec.bindir        = "exe"
  spec.executables   = spec.files.grep(%r{^exe/}) { |f| File.basename(f) }
  spec.require_paths = ["lib"]
  spec.platform      = Gem::Platform::RUBY
  spec.extensions    = "ext/x25519/extconf.rb"

  spec.required_ruby_version = ">= 2.2.2"
  spec.add_development_dependency "bundler", "~> 1.16"
end

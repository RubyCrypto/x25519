# x25519.rb [![Latest Version][gem-shield]][gem-link] [![Yard Docs][docs-image]][docs-link] [![License: BSD 3-Clause][license-image]][license-link] [![Build Status][build-image]][build-link]

[gem-shield]: https://img.shields.io/gem/v/x25519?logo=ruby
[gem-link]: https://rubygems.org/gems/x25519
[docs-image]: https://img.shields.io/badge/yard-docs-blue.svg
[docs-link]: http://www.rubydoc.info/gems/x25519/1.0.6
[license-image]: https://img.shields.io/badge/License-BSD%203--Clause-blue.svg
[license-link]: https://spdx.org/licenses/BSD-3-Clause.html
[build-image]: https://github.com/RubyCrypto/x25519/actions/workflows/ci.yml/badge.svg
[build-link]: https://github.com/RubyCrypto/x25519/actions/workflows/ci.yml

An efficient public key cryptography library for Ruby providing key
exchange/agreement.

This gem implements X25519 (a.k.a. Curve25519) Elliptic Curve Diffie-Hellman
function as described in [RFC7748] as a C extension using the
high performance [rfc7748_precomputed] implementation based on the paper
[How to (pre-)compute a ladder]
(with fallback to the ref10 C implementation).

X25519 is one of two notable algorithms implemented atop the Curve25519
elliptic curve. The [ed25519 gem] is a related project of this one,
and implements the Ed25519 signature scheme on the twisted Edwards form of
Curve25519.

[RFC7748]: https://tools.ietf.org/html/rfc7748
[How to (pre-)compute a ladder]: https://eprint.iacr.org/2017/264
[rfc7748_precomputed]: https://github.com/armfazh/rfc7748_precomputed
[ed25519 gem]: https://github.com/RubyCrypto/ed25519

### Is it any good?

[Yes.](http://news.ycombinator.com/item?id=3067434)

### What is it useful for?

X25519 is a key exchange/agreement algorithm generally used as a low-level
building block in cryptographic protocols.

### Can I use X25519 to encrypt things?

Please use [RbNaCl::Box] if you would like a high-level construction which uses
X25519 for public-key encryption. Otherwise, the X25519 algorithm is not directly
useful for encryption without a higher-level encryption protocol built on top of it.

[RbNaCl::Box]: https://github.com/RubyCrypto/rbnacl/wiki/Public-Key-Encryption

## Help and Discussion

Have questions? Want to suggest a feature or change? Join a discussion group:

* [Crypto.rb Gitter]: web-based chat about Ruby crypto projects including **x25519**.
* [Crypto.rb Google Group]: join via web or email ([RubyCrypto+subscribe@googlegroups.com])

[Crypto.rb Gitter]: https://gitter.im/RubyCrypto/Lobby
[Crypto.rb Google Group]: https://groups.google.com/forum/#!forum/RubyCrypto
[RubyCrypto+subscribe@googlegroups.com]: mailto:RubyCrypto+subscribe@googlegroups.com?subject=subscribe

## Requirements

**x25519.rb** is supported on and tested against the following platforms:

- MRI 2.5, 2.6, 2.7, 3.0

## Installation

Add this line to your application's Gemfile:

```ruby
gem "x25519"
```

And then execute:

    $ bundle

Or install it yourself as:

    $ gem install x25519

## Usage

The example below shows how to perform a full Diffie-Hellman key exchange:

```ruby
require "x25519"

# Alice generates random scalar (private key)
alice_sk = X25519::Scalar.generate

# Alice obtains public key for her private key/scalar
alice_pk = alice_sk.public_key

# Bob generates random scalar (private key)
# Ostensibly this would be on a different computer somewhere
bob_sk = X25519::Scalar.generate
bob_pk = bob_sk.public_key

# Alice can perform Diffie-Hellman with Bob's public key
alice_secret = alice_sk.diffie_hellman(bob_pk).to_bytes

# Bob can perform Diffie-Hellman with Alice's public key
bob_secret = bob_sk.diffie_hellman(alice_pk).to_bytes

# The resulting secrets should be the same
alice_secret == bob_secret # true
```

## X25519::Scalar: private keys

The `X25519::Scalar` class represents secret integers used as X25519 private
keys. These secret integers are multiplied by a well-known base point to
obtain X25519 public keys (`X25519::MontgomeryU`).

### `X25519::Scalar.generate()`: make a random private key

Generate a random private scalar (using `SecureRandom`)

**Example:**

```ruby
secret_key = X25519::Scalar.generate
```

### `X25519::Scalar.new(bytes)`: load existing private key

* `bytes`: a 32-byte `String` value containing the private key

**Example:**

```ruby
secret_key = X25519::Scalar.new(File.read("alice.key"))
```

### `X25519::Scalar#public_key()`: obtain public key for this scalar

NOTE: The `#multiply_base` method is an alias of this one.

Performs fixed-base scalar multiplication (i.e. calculates public key)

**Return Value:**

Returns a `X25519::MontgomeryU` object which represents the public key for this private key/scalar.

**Example:**

```ruby
secret_key = X25519::Scalar.generate
public_key = secret_key.public_key
```

### `X25519::Scalar#diffie_hellman(other_public_key)`: obtain public key for this scalar

NOTE: The `#multiply` method is an alias of this one.

Performs variable-base scalar multiplication, computing a shared secret between
our private scalar and someone else's public key/point.

**Arguments:**

* `other_public_key`: a `X25519::MontgomeryU` object containing the public key
  with which we'd like to compute a shared secret.

**Return Value:**

Returns a `X25519::MontgomeryU` object which represents the shared secret.

**Example:**

```ruby
secret_key = X25519::Scalar.generate
public_key = X25519::MontgomeryU.new(File.read("bob.pub"))

# Returns an X25519::MontgomeryU
shared_secret = secret_key.multiply(public_key)

# Obtain the shared secret as a serialized byte representation
shared_secret_bytes = shared_secret.to_bytes
```

### `X25519::Scalar#to_bytes`: serialize a scalar as a `String`

**Return Value:**

Returns a `String` containing a byte representation of this scalar:

**Example:**

```ruby
secret_key = X25519::Scalar.new(...)
File.write("alice.key", secret_key.to_bytes)
```

## X25519::MontgomeryU: public keys and shared secrets

The `X25519::MontgomeryU` class represents a coordinate (specifically a
Montgomery-u coordinate) on the elliptic curve. In the X25519 Diffie-Hellman
function, these serve both as public keys and as shared secrets.

### `X25519::MontgomeryU.new(bytes)`: load existing public key

**Arguments:**

* `bytes`: a 32-byte `String` value containing the public key

**Example:**

```ruby
public_key = X25519::MontgomeryU.new(File.read("bob.pub"))
```

### `X25519::MontgomeryU#to_bytes`: serialize a Montgomery-u coordinate as a `String`

**Return Value:**

Returns a `String` containing a byte representation of a compressed Montgomery-u coordinate:

**Example:**

```ruby
public_key = X25519::MontgomeryU..new(...)
File.write("bob.pub", public_key.to_bytes)
```

## X25519: module-level functionality

### `X25519.diffie_hellman(secret_key, public_key)`: shorthand `String`-oriented API

If you'd like to avoid the object-oriented API, you can use a simplified API which
acts entirely on bytestrings.

**Arguments:**

* `secret_key`: a 32-byte `String` containing a private scalar
* `public_key`: a 32-byte `String` containing a compressed Montgomery-u coordinate

**Return Value:**

Returns a `String` containing a 32-byte compressed Montgomery-u coordinate

## Contributing

Bug reports and pull requests are welcome on GitHub at https://github.com/RubyCrypto/x25519.
This project is intended to be a safe, welcoming space for collaboration,
and contributors are expected to adhere to the [Contributor Covenant](https://contributor-covenant.org)
code of conduct.

## Implementation Details

This gem contains two implementations of X25519: an optimized assembly
implementation and a portable C implementation. Implementations are selected
based on available CPU features.

### [rfc7748_precomputed]: optimized assembly implementation

* Prime field arithmetic is optimized for the 4th and 6th generation of Intel Core processors
  (Haswell and Skylake micro-architectures).
* Efficient integer multiplication using MULX instruction.
* Integer additions accelerated with ADCX/ADOX instructions.
* Key generation uses a read-only table of 8 KB for X25519.

### ref10: portable C implementation

* Taken from the [SUPERCOP] cryptographic benchmarking suite (supercop-20171020)
* Portable C code which should compile on any architecture

[SUPERCOP]: https://bench.cr.yp.to/supercop.html

## Designers

The X25519 Diffie-Hellman function was originally designed by Dan Bernstein:

https://cr.yp.to/ecdh.html

The optimized [rfc7748_precomputed] implementation was designed by:

* Thomaz Oliveira, Computer Science Department, Cinvestav-IPN, Mexico.
* Julio López, University of Campinas, Brazil.
* Hüseyin Hisil, Yasar University, Turkey.
* Armando Faz-Hernández, University of Campinas, Brazil.
* Francisco Rodríguez-Henríquez, Computer Science Department, Cinvestav-IPN, Mexico.

## License

Copyright (c) 2017-2018 Armando Faz
Copyright (c) 2017-2021 Tony Arcieri

This gem is available as open source under the terms of the
BSD-3 Clause License ([LICENSE](./LICENSE))

## Code of Conduct

Everyone interacting in the x25519.rb project’s codebases, issue trackers, chat
rooms and mailing lists is expected to follow the [code of conduct].

[code of conduct]: https://github.com/RubyCrypto/x25519/blob/main/CODE_OF_CONDUCT.md

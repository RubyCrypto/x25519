# [1.0.4] (2017-12-31)

[1.0.4]: https://github.com/crypto-rb/x25519/compare/v1.0.3...v1.0.4

* [#13](https://github.com/crypto-rb/x25519/pull/13)
  Test against Ruby 2.5.0

* [#12](https://github.com/crypto-rb/x25519/pull/12)
  Move project to the crypto-rb GitHub organization

# [1.0.3] (2017-12-13)

[1.0.3]: https://github.com/crypto-rb/x25519/compare/v1.0.2...v1.0.3

* [#10](https://github.com/crypto-rb/x25519/pull/10)
  Detect degenerate (i.e. all-zero) public keys (fixes #6)

# [1.0.2] (2017-12-13)

[1.0.2]: https://github.com/crypto-rb/x25519/compare/v1.0.1...v1.0.2

* [#9](https://github.com/crypto-rb/x25519/pull/9)
  Make `X25519.provider` an `attr_accessor`
* Raise `X25519::SelfTestFailure` when self-test fails

# [1.0.1] (2017-12-12)

[1.0.1]: https://github.com/crypto-rb/x25519/compare/v1.0.0...v1.0.1

* Have `X25519.self_test` return true on success

# [1.0.0] (2017-12-12)

[1.0.0]: https://github.com/crypto-rb/x25519/compare/v0.2.0...v1.0.0

* [#8](https://github.com/crypto-rb/x25519/pull/8)
  Add self-test

* [#7](https://github.com/crypto-rb/x25519/pull/7)
  Factor providers into the `X25519::Provider` namespace

# [0.2.0] (2017-12-12)

[0.2.0]: https://github.com/crypto-rb/x25519/compare/v0.1.0...v0.2.0

* [#5](https://github.com/crypto-rb/x25519/pull/5)
  Rewrite gem in Ruby with minimal native extensions

# 0.1.0 (2017-12-11)

* Initial release

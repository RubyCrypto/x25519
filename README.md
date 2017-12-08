# x25519.rb

An efficient public key cryptography library for Ruby providing key
exchange/agreement.

This gem implements X25519 (a.k.a. Curve25519) Elliptic Curve Diffie-Hellman
function as described in [RFC7748] as a C extension using the
high performance [rfc7748-precomputed] implementation based on the paper
[How to (pre-)compute a ladder].

[RFC7748]: https://tools.ietf.org/html/rfc7748
[How to (pre-)compute a ladder]: https://eprint.iacr.org/2017/264
[rfc7748_precomputed]: https://github.com/armfazh/rfc7748_precomputed

## Installation

Add this line to your application's Gemfile:

```ruby
gem 'x25519'
```

And then execute:

    $ bundle

Or install it yourself as:

    $ gem install x25519

## Usage

Coming soon!

## Contributing

Bug reports and pull requests are welcome on GitHub at https://github.com/cryptosphere/x25519.
This project is intended to be a safe, welcoming space for collaboration,
and contributors areexpected to adhere to the [Contributor Covenant](http://contributor-covenant.org)
code of conduct.

## Implementation Details

* Prime field arithmetic is optimized for the 4th and 6th generation of Intel Core processors (Haswell and Skylake micro-architectures).
* Efficient integer multiplication using MULX instruction.
* Integer additions accelerated with ADCX/ADOX instructions.
* Key generation uses a read-only table of 8 KB (25 KB) for X25519 (X448).

## Designers

Thomaz Oliveira, Computer Science Department, Cinvestav-IPN, Mexico.
Julio López, University of Campinas, Brazil.
Hüseyin Hisil, Yasar University, Turkey.
Armando Faz-Hernández, University of Campinas, Brazil.
Francisco Rodríguez-Henríquez, Computer Science Department, Cinvestav-IPN, Mexico.

## License

The gem is available as open source under the terms of the
GNU Lesser General Public License v3.0 ([LICENSE](https://www.gnu.org/licenses/lgpl-3.0.txt))

## Code of Conduct

Everyone interacting in the X25519 project’s codebases, issue trackers, chat
rooms and mailing lists is expected to follow the [code of conduct].

[code of conduct]: https://github.com/cryptosphere/x25519/blob/master/CODE_OF_CONDUCT.md

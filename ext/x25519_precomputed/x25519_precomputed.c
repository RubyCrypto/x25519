/*
Ruby C extension providing bindings to the rfc7748_precomputed implementation of
the X25519 Diffie-Hellman algorithm
*/

#include "ruby.h"
#include "x25519_precomputed.h"

static VALUE mX25519 = Qnil;
static VALUE mX25519_Provider = Qnil;
static VALUE mX25519_Provider_Precomputed = Qnil;

static VALUE mX25519_Provider_Precomputed_scalarmult(VALUE self, VALUE scalar, VALUE montgomery_u);
static VALUE mX25519_Provider_Precomputed_scalarmult_base(VALUE self, VALUE scalar);
static VALUE mX25519_is_available(VALUE self);

/* Initialize the x25519_precomputed C extension */
void Init_x25519_precomputed()
{
    mX25519 = rb_define_module("X25519");
    mX25519_Provider = rb_define_module_under(mX25519, "Provider");
    mX25519_Provider_Precomputed = rb_define_module_under(mX25519_Provider, "Precomputed");

    rb_define_singleton_method(mX25519_Provider_Precomputed, "scalarmult", mX25519_Provider_Precomputed_scalarmult, 2);
    rb_define_singleton_method(mX25519_Provider_Precomputed, "scalarmult_base", mX25519_Provider_Precomputed_scalarmult_base, 1);
    rb_define_singleton_method(mX25519_Provider_Precomputed, "available?", mX25519_is_available, 0);
}

/* Variable-base scalar multiplication */
static VALUE mX25519_Provider_Precomputed_scalarmult(VALUE self, VALUE scalar, VALUE montgomery_u)
{
    /* X25519_KEY ensures inputs are aligned at 32-bytes */
    X25519_KEY raw_scalar, raw_montgomery_u, product;

    StringValue(scalar);
    if(RSTRING_LEN(scalar) != X25519_KEYSIZE_BYTES) {
        rb_raise(
            rb_eArgError,
            "expected %d-byte scalar, got %ld",
            X25519_KEYSIZE_BYTES,
            RSTRING_LEN(scalar)
        );
    }

    StringValue(montgomery_u);
    if(RSTRING_LEN(montgomery_u) != X25519_KEYSIZE_BYTES) {
        rb_raise(
            rb_eArgError,
            "expected %d-byte Montgomery-u coordinate, got %ld",
            X25519_KEYSIZE_BYTES,
            RSTRING_LEN(montgomery_u)
        );
    }

    memcpy(raw_scalar, RSTRING_PTR(scalar), X25519_KEYSIZE_BYTES);
    memcpy(raw_montgomery_u, RSTRING_PTR(montgomery_u), X25519_KEYSIZE_BYTES);
    x25519_precomputed_scalarmult(product, raw_scalar, raw_montgomery_u);

    return rb_str_new((const char *)product, X25519_KEYSIZE_BYTES);
}

/* Fixed-base scalar multiplication */
static VALUE mX25519_Provider_Precomputed_scalarmult_base(VALUE self, VALUE scalar)
{
    /* X25519_KEY ensures inputs are aligned at 32-bytes */
    X25519_KEY raw_scalar, product;

    StringValue(scalar);
    if(RSTRING_LEN(scalar) != X25519_KEYSIZE_BYTES) {
        rb_raise(
            rb_eArgError,
            "expected %d-byte scalar, got %ld",
            X25519_KEYSIZE_BYTES,
            RSTRING_LEN(scalar)
        );
    }

    memcpy(raw_scalar, RSTRING_PTR(scalar), X25519_KEYSIZE_BYTES);
    x25519_precomputed_scalarmult_base(product, raw_scalar);

    return rb_str_new((const char *)product, X25519_KEYSIZE_BYTES);
}

/* Is the x25519_precomputed backend supported on this CPU? */
static VALUE mX25519_is_available(VALUE self)
{
    return check_4th_gen_intel_core_features() ? Qtrue : Qfalse;
}

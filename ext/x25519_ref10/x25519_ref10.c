/*
Ruby C extension providing bindings to the ref10 implementation of the
X25519 Diffie-Hellman algorithm
*/

#include "ruby.h"
#include "x25519_ref10.h"

static VALUE mX25519 = Qnil;
static VALUE mX25519_Ref10 = Qnil;

static VALUE mX25519_Scalar_multiply(VALUE self, VALUE scalar, VALUE montgomery_u);
static VALUE mX25519_Scalar_multiply_base(VALUE self, VALUE scalar);

/* Initialize the x25519_ref10 C extension */
void Init_x25519_ref10()
{
    mX25519 = rb_define_module("X25519");
    mX25519_Ref10 = rb_define_module_under(mX25519, "Ref10");

    rb_define_singleton_method(mX25519_Ref10, "multiply", mX25519_Scalar_multiply, 2);
    rb_define_singleton_method(mX25519_Ref10, "multiply_base", mX25519_Scalar_multiply_base, 1);
}

/* Variable-base scalar multiplication */
static VALUE mX25519_Scalar_multiply(VALUE self, VALUE scalar, VALUE montgomery_u)
{
    X25519_KEY product;

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

    x25519_ref10_scalarmult(
        product,
        (const uint8_t *)RSTRING_PTR(scalar),
        (const uint8_t *)RSTRING_PTR(montgomery_u)
    );

    return rb_str_new((const char *)product, X25519_KEYSIZE_BYTES);
}

/* Fixed-base scalar multiplication */
static VALUE mX25519_Scalar_multiply_base(VALUE self, VALUE scalar)
{
    X25519_KEY product;

    StringValue(scalar);
    if(RSTRING_LEN(scalar) != X25519_KEYSIZE_BYTES) {
        rb_raise(
            rb_eArgError,
            "expected %d-byte scalar, got %ld",
            X25519_KEYSIZE_BYTES,
            RSTRING_LEN(scalar)
        );
    }

    x25519_ref10_scalarmult_base(
        product,
        (const uint8_t *)RSTRING_PTR(scalar)
    );

    return rb_str_new((const char *)product, X25519_KEYSIZE_BYTES);
}

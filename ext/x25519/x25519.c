#include <stdlib.h>

#include "ruby.h"
#include "x25519.h"

/* The X25519::VERSION */
#define GEM_VERSION "0.0.0"

/* X25519::Scalar prototypes */
static VALUE cX25519_Scalar_allocate(VALUE klass);
static void cX25519_Scalar_mark(X25519_KEY *scalar);
static void cX25519_Scalar_free(X25519_KEY *scalar);
static VALUE cX25519_Scalar_generate(VALUE self);
static VALUE cX25519_Scalar_initialize(VALUE self, VALUE bytes);
static VALUE cX25519_Scalar_public_key(VALUE self);
static VALUE cX25519_Scalar_multiply(VALUE self, VALUE montgomery_u);
static VALUE cX25519_Scalar_to_bytes(VALUE self);

/* X25519::MontgomeryU prototypes */
static VALUE cX25519_MontgomeryU_allocate(VALUE klass);
static void cX25519_MontgomeryU_mark(X25519_KEY *coord);
static void cX25519_MontgomeryU_free(X25519_KEY *coord);
static VALUE cX25519_MontgomeryU_initialize(VALUE self, VALUE bytes);
static VALUE cX25519_MontgomeryU_to_bytes(VALUE self);

static VALUE X25519_self_test(VALUE self);
static VALUE X25519_diffie_hellman(VALUE self, VALUE public_key, VALUE secret_key);

static VALUE mX25519 = Qnil;
static VALUE cX25519_Scalar  = Qnil;
static VALUE cX25519_MontgomeryU = Qnil;

/* Initialize the Ruby module */
void Init_x25519()
{
    /* Used for key generation */
    rb_require("securerandom");

    mX25519 = rb_define_module("X25519");
    rb_define_const(mX25519, "VERSION", rb_str_new2(GEM_VERSION));
    rb_define_singleton_method(mX25519, "self_test", X25519_self_test, 0);
    rb_define_singleton_method(mX25519, "diffie_hellman", X25519_diffie_hellman, 2);

    cX25519_Scalar = rb_define_class_under(mX25519, "Scalar", rb_cObject);
    rb_define_alloc_func(cX25519_Scalar, cX25519_Scalar_allocate);
    rb_define_singleton_method(cX25519_Scalar, "generate", cX25519_Scalar_generate, 0);
    rb_define_method(cX25519_Scalar, "initialize", cX25519_Scalar_initialize, 1);
    rb_define_method(cX25519_Scalar, "public_key", cX25519_Scalar_public_key, 0);
    rb_define_method(cX25519_Scalar, "multiply", cX25519_Scalar_multiply, 1);
    rb_define_method(cX25519_Scalar, "diffie_hellman", cX25519_Scalar_multiply, 1);
    rb_define_method(cX25519_Scalar, "to_bytes", cX25519_Scalar_to_bytes, 0);
    rb_define_method(cX25519_Scalar, "to_str", cX25519_Scalar_to_bytes, 0);

    cX25519_MontgomeryU = rb_define_class_under(mX25519, "MontgomeryU", rb_cObject);
    rb_define_alloc_func(cX25519_MontgomeryU, cX25519_MontgomeryU_allocate);
    rb_define_method(cX25519_MontgomeryU, "initialize", cX25519_MontgomeryU_initialize, 1);
    rb_define_method(cX25519_MontgomeryU, "to_bytes", cX25519_MontgomeryU_to_bytes, 0);
    rb_define_method(cX25519_MontgomeryU, "to_str", cX25519_MontgomeryU_to_bytes, 0);

    /* Run the self-test on load to ensure everything is working */
    rb_funcall(mX25519, rb_intern("self_test"), 0);
}

/********************************
 * X25519::Scalar: private keys *
 ********************************/

static VALUE cX25519_Scalar_allocate(VALUE klass)
{
    X25519_KEY *scalar = NULL;

    /* Ensure allocation with the correct (32-byte) memory alignent */
    if(posix_memalign((void **)&scalar, ALIGN_BYTES, X25519_KEYSIZE_BYTES)) {
        rb_fatal("x25519: can't allocate memory with posix_memalign()");
    }

    /* Avoid using unitialized memory */
    memset(scalar, 0, X25519_KEYSIZE_BYTES);

    return Data_Wrap_Struct(klass, cX25519_Scalar_mark, cX25519_Scalar_free, scalar);
}

static void cX25519_Scalar_mark(X25519_KEY *scalar)
{
}

static void cX25519_Scalar_free(X25519_KEY *scalar)
{
    free(scalar);
}

/* Generate a random X25519 private scalar */
static VALUE cX25519_Scalar_generate(VALUE self)
{
    VALUE rb_mSecureRandom, scalar_bytes;
    rb_mSecureRandom = rb_const_get(rb_cObject, rb_intern("SecureRandom"));

    scalar_bytes = rb_funcall(
        rb_mSecureRandom,
        rb_intern("random_bytes"),
        1,
        INT2NUM(X25519_KEYSIZE_BYTES)
    );

    return rb_class_new_instance(1, &scalar_bytes, self);
}

/* Create an X25519::Scalar from a String containing bytes */
static VALUE cX25519_Scalar_initialize(VALUE self, VALUE bytes)
{
    X25519_KEY *scalar = NULL;
    Data_Get_Struct(self, X25519_KEY, scalar);

    StringValue(bytes);
    if(RSTRING_LEN(bytes) != X25519_KEYSIZE_BYTES) {
        rb_raise(
            rb_eArgError,
            "expected %d-byte scalar, got %ld",
            X25519_KEYSIZE_BYTES,
            RSTRING_LEN(bytes)
        );
    }

    memcpy(scalar, RSTRING_PTR(bytes), X25519_KEYSIZE_BYTES);

    return self;
}

/* Obtain a public key for an X25519 private scalar
 * (i.e. fixed base scalar multiplication ) */
static VALUE cX25519_Scalar_public_key(VALUE self)
{
    X25519_KEY *scalar = NULL, public_key;
    VALUE public_key_str;

    Data_Get_Struct(self, X25519_KEY, scalar);

    /* Avoid using unitialized memory */
    memset(&public_key, 0, X25519_KEYSIZE_BYTES);

    /* Compute public key from private scalar using fixed-base scalar multiplication */
    X25519_KeyGen_x64(public_key, *scalar);

    public_key_str = rb_str_new((const char *)&public_key, X25519_KEYSIZE_BYTES);
    return rb_class_new_instance(1, &public_key_str, cX25519_MontgomeryU);
}

/* Obtain a public key for an X25519 private scalar
 * (i.e. fixed base scalar multiplication ) */
static VALUE cX25519_Scalar_multiply(VALUE self, VALUE montgomery_u)
{
    X25519_KEY *scalar = NULL, *coord = NULL, product;
    VALUE product_str;

    if(rb_obj_class(montgomery_u) != cX25519_MontgomeryU) {
        rb_raise(rb_eTypeError, "wrong argument type (expected X25519::MontgomeryU)");
    }

    Data_Get_Struct(self, X25519_KEY, scalar);
    Data_Get_Struct(montgomery_u, X25519_KEY, coord);

    /* Avoid using unitialized memory */
    memset(&product, 0, X25519_KEYSIZE_BYTES);

    /* Compute the Diffie-Hellman shared secret */
    X25519_Shared_x64(product, *coord, *scalar);

    product_str = rb_str_new((const char *)&product, X25519_KEYSIZE_BYTES);
    return rb_class_new_instance(1, &product_str, cX25519_MontgomeryU);
}

/* Return a String containing the raw bytes of this scalar */
static VALUE cX25519_Scalar_to_bytes(VALUE self)
{
    X25519_KEY *scalar = NULL;
    Data_Get_Struct(self, X25519_KEY, scalar);

    return rb_str_new((const char *)scalar, X25519_KEYSIZE_BYTES);;
}

/************************************
 * X25519::MontgomeryU: public keys *
 ************************************/

static VALUE cX25519_MontgomeryU_allocate(VALUE klass)
{
    X25519_KEY *coord = NULL;

    /* Ensure allocation with the correct (32-byte) memory alignent */
    if(posix_memalign((void **)&coord, ALIGN_BYTES, X25519_KEYSIZE_BYTES)) {
        rb_fatal("x25519: can't allocate memory with posix_memalign()");
    }

    /* Avoid using unitialized memory */
    memset(coord, 0, X25519_KEYSIZE_BYTES);

    return Data_Wrap_Struct(klass, cX25519_MontgomeryU_mark, cX25519_MontgomeryU_free, coord);
}

static void cX25519_MontgomeryU_mark(X25519_KEY *coord)
{
}

static void cX25519_MontgomeryU_free(X25519_KEY *coord)
{
    free(coord);
}

static VALUE cX25519_MontgomeryU_initialize(VALUE self, VALUE bytes)
{
    X25519_KEY *coord = NULL;
    Data_Get_Struct(self, X25519_KEY, coord);

    StringValue(bytes);
    if(RSTRING_LEN(bytes) != X25519_KEYSIZE_BYTES) {
        rb_raise(
            rb_eArgError,
            "expected %d-byte scalar, got %ld",
            X25519_KEYSIZE_BYTES,
            RSTRING_LEN(bytes)
        );
    }

    memcpy(coord, RSTRING_PTR(bytes), X25519_KEYSIZE_BYTES);

    return self;
}

/* Return a String containing the raw bytes of this scalar */
static VALUE cX25519_MontgomeryU_to_bytes(VALUE self)
{
    X25519_KEY *coord = NULL;
    Data_Get_Struct(self, X25519_KEY, coord);

    return rb_str_new((const char *)coord, X25519_KEYSIZE_BYTES);;
}

/* Perform an end-to-end test of the Ruby binding to ensure it's working correctly */
static VALUE X25519_self_test(VALUE self)
{
    VALUE sk, pk, shared;

    /* Test vectors from RFC 7748 */
    X25519_KEY ietf_cfrg_key0 = {
        0xa5,0x46,0xe3,0x6b,0xf0,0x52,0x7c,0x9d,
        0x3b,0x16,0x15,0x4b,0x82,0x46,0x5e,0xdd,
        0x62,0x14,0x4c,0x0a,0xc1,0xfc,0x5a,0x18,
        0x50,0x6a,0x22,0x44,0xba,0x44,0x9a,0xc4
    };

    X25519_KEY ietf_cfrg_input_coord0 = {
        0xe6,0xdb,0x68,0x67,0x58,0x30,0x30,0xdb,
        0x35,0x94,0xc1,0xa4,0x24,0xb1,0x5f,0x7c,
        0x72,0x66,0x24,0xec,0x26,0xb3,0x35,0x3b,
        0x10,0xa9,0x03,0xa6,0xd0,0xab,0x1c,0x4c
    };

    X25519_KEY ietf_cfrg_output_coord0 = {
        0xc3,0xda,0x55,0x37,0x9d,0xe9,0xc6,0x90,
        0x8e,0x94,0xea,0x4d,0xf2,0x8d,0x08,0x4f,
        0x32,0xec,0xcf,0x03,0x49,0x1c,0x71,0xf7,
        0x54,0xb4,0x07,0x55,0x77,0xa2,0x85,0x52
    };

    sk = rb_str_new((const char *)&ietf_cfrg_key0, X25519_KEYSIZE_BYTES);
    pk = rb_str_new((const char *)&ietf_cfrg_input_coord0, X25519_KEYSIZE_BYTES);

    shared = rb_funcall(mX25519, rb_intern("diffie_hellman"), 2, sk, pk);

    if(RSTRING_LEN(shared) != X25519_KEYSIZE_BYTES ||
       memcmp(RSTRING_PTR(shared), ietf_cfrg_output_coord0, X25519_KEYSIZE_BYTES) != 0)
    {
        rb_raise(rb_eRuntimeError, "X25519 self-test failed!");
    }

    return Qtrue;
}

/* Compute Diffie-Hellman for the given key and Montgomery-u coordinate
 * (i.e. variable base scalar multiplication) */
static VALUE X25519_diffie_hellman(VALUE self, VALUE secret_key, VALUE public_key)
{
    VALUE scalar, coord, shared;

    scalar = rb_class_new_instance(1, &secret_key, cX25519_Scalar);
    coord  = rb_class_new_instance(1, &public_key, cX25519_MontgomeryU);
    shared = rb_funcall(scalar, rb_intern("diffie_hellman"), 1, coord);

    return rb_funcall(shared, rb_intern("to_bytes"), 0);
}


# Fast Implementation of RFC-7748 for 64-bit Architectures
----

This project provides a fast implementation of the 
RFC-7748. The Diffie-Hellman functions known as X25519 and X448.

Features:
 * This code is optimized for the 4th generation of Intel Core processors.
 * Efficient integer multiplier using MULX instruction.
 * Additions accelerated with ADCX/ADOX instructions.
 * Key generation uses a precomputed table of 8 KB.


**Author:** Armando Faz-Hernández, University of Campinas, Brazil.


## Compilation


Extract and compile as follows:

```
 $ git clone https://github.com/armfazh/rfc7748_precomputed
 $ cd rfc7748_precomputed
 $ mkdir build
 $ cd build
 $ CC=gcc cmake ..
 $ make
```

For running the benchmark program use:
```
 $ bin/bench
```

For running the tests program use:
```
 $ bin/tests
```

For running a sample program use:
```
 $ bin/samples
```

----
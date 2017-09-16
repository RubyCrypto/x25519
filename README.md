
# How to (pre-)compute a ladder 


This is a C-language software library that provides optimized implementations of the Diffie-Hellman functions known as X25519 and X448 ([RFC-7748](https://datatracker.ietf.org/doc/rfc7748/)) for 64-bit architectures. 

This source code is part of the research work titled: _"How to (pre-)compute a ladder"_ by the authors:
 * [Thomaz Oliveira](http://dblp.uni-trier.de/pers/hd/o/Oliveira:Thomaz), Computer Science Department, Cinvestav-IPN, Mexico.
 * [Julio López](http://www.ic.unicamp.br/pessoas/docentes/jlopez), University of Campinas, Brazil.
 * [Hüseyin Hisil](http://hhisil.yasar.edu.tr/), Yasar University, Turkey.
 * [Armando Faz-Hernández](http://www.ic.unicamp.br/~armfazh), University of Campinas, Brazil.
 * [Francisco Rodríguez-Henríquez](http://delta.cs.cinvestav.mx/~francisco/), Computer Science Department, Cinvestav-IPN, Mexico.


----

### Research Resources

A peer-reviewed paper was presented in the 24th Annual Conference on Selected Areas in Cryptography ([SAC2017](http://sacworkshop.org/SAC17/SAC2017.htm)). Slides [[PDF](http://www.ic.unicamp.br/~ra142685/userfiles/papers/oliveira_sac2017.pdf)].

A pre-print of this document can be found at the IACR ePrint Archive: 
 [http://iacr.eprint.org/2017/264](https://eprint.iacr.org/2017/264) [[PDF](https://eprint.iacr.org/2017/264.pdf)}



To cite this work use:

```tex
@inproceedings{oliveira_sac2017,
    author = {Thomaz Oliveira and Julio L\'opez and H\"useyin H{\i}\c{s}{\i}l and Armando Faz-Hern\'andez and Francisco Rodr\'iguez-Henr\'iquez},
    title = {How to (pre-)compute a ladder},
    booktitle = {Selected Areas in Cryptography – SAC 2017: 24th International Conference, Ottawa, Ontario, Canada, August 16 - 18, 2017, Revised Selected Papers},
    year = {2017},
	publisher = {Springer International Publishing},
}
```
----

### Implementation Details
 * Prime field arithmetic is optimized for the 4th  and 6th generation of Intel Core processors (Haswell and Skylake micro-architectures).
 * Efficient integer multiplication using MULX instruction.
 * Integer additions accelerated with ADCX/ADOX instructions.
 * Key generation uses a read-only table of 8 KB (25 KB) for X25519 (X448).
 * It follows secure coding countermeasures.

----

### Compilation
Clone repository and configure project using the [CMake](https://cmake.org/) tool:

```sh
 $ git clone https://github.com/armfazh/rfc7748_precomputed
 $ cd rfc7748_precomputed
 $ mkdir build
 $ cd build
```
You can specify the compiler as follows:
```sh
 $ CC=gcc cmake ..
 $ make
```

----

### Runing Companion Programs
Once compilation was done, you can run three companion programs. For running the benchmark program use:
```sh
 $ bin/bench
```

For running the tests program use:
```sh
 $ bin/tests
```

For running a sample program use:
```sh
 $ bin/samples
```
----

### Timings 
Benchmark performance on 64-bit Intel architectures (table entries are clock cycles).

| X25519 | Haswell | Skylake |
| ------ | ------ | ------ |
| Keygen        |  90,895 | 72,571 |
| Shared Secret | 138,962 | 107,942 |
 	 	 	
| X448 | Haswell | Skylake |
| ------ | ------ | ------ |
| Keygen        | 401,902 | 322,040 |
| Shared Secret | 670,747 | 528,470 |

----

### License 
GNU Lesser General Public License v3.0 ([LICENSE](https://www.gnu.org/licenses/lgpl-3.0.txt))

----

### Contact 

To report some issues or comments of this project, please use the issues webpage [[here](https://github.com/armfazh/rfc7748_precomputed/issues)]. 

----


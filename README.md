A fast implementation of Euler's Totient Function in C++
========================================================

This package contains a very fast version of the phi-function:

https://en.wikipedia.org/wiki/Euler%27s_totient_function

It uses several tricks to make it run fast and also relies on a very fast
prime number sieve and a binary GCD algorithm.

In fact, the sieve and gcd function can be used separately if needed.

Also, it is template based, so you can use it with native integer types or
big integers like libgmp's mpz__class.  

Other than that this package is written in pure C++ using nothing but the
standard library.

LICENSE
-------

Copyright (c) 2012 Christian Stigen Larsen
http://csl.sublevel3.org

Distributed under the BSD 3-clause license; see the file LICENSE for a copy
of the full license text.

USAGE EXAMPLES
--------------

Note that the first time you invoke `phi()` it will start calculating a
given set of prime numbers (one million, by default).  This usually takes a
couple of milliseconds, but for larger sizes (e.g., a billion) it can take
several seconds!

Here's a straight-forward example:

    #include <iostream>
    #include <inttypes.h>
    #include "phi.h"

    int main()
    {
      for ( uint64_t n=1; n<1000000; ++n ) {
        uint64_t p = phi<10000000>(n);
        std::cout << "phi(" << n << ") = " << p << std::endl;
      }

      return 0;
    }

Note that you can blow up the function since it relies on a certain size of
the prime number sieve.  It doesn't use exceptions, only assertions in debug
mode.  To compile without assertions, use an appropriate compiler definition
for your system (`-DNDEBUG` for GCC).

BUILDING
--------

To build the test, just type `make check` and hope for the best:

    $ make check
    c++ -W -Wall -O3    test.cpp   -o test
    bash -c "time ./test"
    Calculating 10000000 prime numbers
    phi(0) = 0
    phi(56789) = 56160
    phi(113578) = 56160
    phi(170367) = 112320
    phi(227156) = 112320
    phi(283945) = 224640
    phi(340734) = 112320
    phi(397523) = 336960
    phi(454312) = 224640
    phi(511101) = 336960
    phi(567890) = 224640
    phi(624679) = 561600
    phi(681468) = 224640
    phi(738257) = 673920
    phi(795046) = 336960
    phi(851835) = 449280
    phi(908624) = 449280
    phi(965413) = 898560

    Calculating 100000000 prime numbers
    phi(1000000) = 400000
    phi(1561167) = 1024056
    phi(2122334) = 1058616
    phi(2683501) = 2466240
    phi(3244668) = 870048
    phi(3805835) = 2767840
    phi(4367002) = 2183500
    phi(4928169) = 3285444
    phi(5489336) = 2733184
    phi(6050503) = 6050502
    phi(6611670) = 1627200
    phi(7172837) = 6128352
    phi(7734004) = 3697920
    phi(8295171) = 5412360
    phi(8856338) = 4428168
    phi(9417505) = 7534000
    phi(9978672) = 3023680

    real	0m2.942s
    user	0m2.029s
    sys	  0m0.097s

USING IN YOUR PROGRAMS
----------------------

Just `#include "phi.h"` and you should be set.


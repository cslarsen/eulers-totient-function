A fast implementation of Euler's Totient Function in C++
========================================================

This package consists of

  * a fast gcd function,
  * a fast prime number sieve and
  * a fast implementation of Euler's phi function using the above

These are fast because

  * we're using the recursive binary GCD algorithm with bit shifts,
  * the Eratosthenes prime sieve uses bitsets for primality testing and
  * the totient implementation is aware of Lehmer's conjecture, even-odd reductions
    and that the phi function is multiplicative.

The classes and functions are template-based, so you can plug in any integer
type you want to, including multiple precision integers (GMPs; see note on
big integers below).

You can also use the gcd function and prime number sieve separately.
Finally, the code is in pure C++ and only relies on the standard library.

The phi function
----------------
For more information about Euler's totient function, please see
https://en.wikipedia.org/wiki/Euler%27s_totient_function

Notes on big integers
---------------------

The implementation needs to store ALL prime numbers below a certain limit to
be able to utilize the multiplicativity trick of the phi function.
Unfortunately, this means that we can't really use the phi function for
insanely big integers, because we would need too much memory.

License
-------

Copyright (c) 2012 Christian Stigen Larsen
http://csl.sublevel3.org

Distributed under the BSD 3-clause license; see the file LICENSE for a copy
of the full license text.

Usage examples
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
      std::cout << phi<100>(12) << std::endl;
    }

Here's another:

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

Building and testing
--------------------

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

How to use it in your programs
------------------------------

Just `#include "phi.h"` and you should be set.


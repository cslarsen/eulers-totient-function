A fast implementation of Euler's Totient Function in C++
========================================================

This package consists of

  * a fast gcd function,
  * a fast prime number sieve and
  * a fast implementation of Euler's phi function using the above.

They are fast because

  * we're using the recursive binary gcd algorithm with bit shifts,
  * bitsets for primality testing and
  * Lehmer's conjecture, even-odd reductions and multiplicativity for phi.

The classes and functions are template-based, so you can plug in any integer
type you want to, including multiple precision integers (GMPs; although you
should see the note below).

You can also use the gcd function and prime number sieve separately.
Finally, the code is in pure C++ and only relies on the standard library.

Design
------
The library is designed for calling the phi function _multiple_ times; it
trades memory for speed.  If you just need to calculate a one-off phi, you
probably don't need this library.

The phi function
----------------
For more information about Euler's totient function, please see
https://en.wikipedia.org/wiki/Euler%27s_totient_function

Note on big integers
--------------------

For fast calculations of phi(n), we ideally want a prime number sieve that
contains all the prime numbers below sqrt(n).  For very large n, however,
this would take up too much memory.

Because of this, the implementation will happily chug along with a plain
trial division when it reaches the end of the number sieve.  This is slow,
but at least it works.

The most glaring problem, though, is that gmplib doesn't work out of the
box, because it lacks operators for bit shifting.  This means you need to
implement these operators yourself.

Also, I haven't tested the speed on very large numbers yet.

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

    $ make
    c++ -W -Wall -O3    test.cpp   -o test
    bash -c "time ./test"
    Calculating all primes below 10000000
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
    phi( 78)= 24   phi( 89)= 88   phi(100)= 40   
    phi(111)= 72   phi(122)= 60   phi(133)=108   
    phi(144)= 48   phi(155)=120   phi(166)= 82   
    phi(177)=116   phi(188)= 92   phi(199)=198   
    phi(210)= 48   phi(221)=192   phi(232)=112   
    phi(243)=162   phi(254)=126   phi(265)=208   
    phi(276)= 88   phi(287)=240   phi(298)=148   
    phi(309)=204   phi(320)=128   phi(331)=330   
    phi(342)=108   phi(353)=352   phi(364)=144   
    phi(375)=200   phi(386)=192   phi(397)=396   
    phi(408)=128   phi(419)=418   phi(430)=168   
    phi(441)=252   phi(452)=224   phi(463)=462   
    phi(474)=156   phi(485)=384   phi(496)=240   
    phi(507)=312   phi(518)=216   phi(529)=506   
    phi(540)=144   phi(551)=504   phi(562)=280   
    phi(573)=380   phi(584)=288   phi(595)=384   
    phi(606)=200   phi(617)=616   phi(628)=312   
    phi(639)=420   phi(650)=240   phi(661)=660   
    phi(672)=192   phi(683)=682   phi(694)=346   
    phi(705)=368   phi(716)=356   phi(727)=726   
    phi(738)=240   phi(749)=636   phi(760)=288   
    phi(771)=512   phi(782)=352   phi(793)=720   
    phi(804)=264   phi(815)=648   phi(826)=348   
    phi(837)=540   phi(848)=416   phi(859)=858   
    phi(870)=224   phi(881)=880   phi(892)=444   
    phi(903)=504   phi(914)=456   phi(925)=720   
    phi(936)=288   phi(947)=946   phi(958)=478   
    phi(969)=576   phi(980)=336   phi(991)=990   
    1 OK:  phi(12) ==> 4 == 4
    2 OK:  phi(12) ==> 4 == 4
    3 OK:  phi(12) ==> 4 == 4
    4 OK:  phi(1234) ==> 616 == 616
    5 OK:  phi(12345) ==> 6576 == 6576
    6 OK:  phi(123456) ==> 41088 == 41088
    7 OK:  phi(1234567) ==> 1224720 == 1224720
    8 OK:  phi(12345678) ==> 4027392 == 4027392
    9 OK:  phi(123456789) ==> 82260072 == 82260072
    10 OK:  phi(1234567890) ==> 329040288 == 329040288
    11 OK:  phi(1234) ==> 616 == 616
    12 OK:  phi(12345) ==> 6576 == 6576
    13 OK:  phi(123456) ==> 41088 == 41088
    14 OK:  phi(1234567) ==> 1224720 == 1224720
    15 OK:  phi(12345678) ==> 4027392 == 4027392
    16 OK:  phi(123456789) ==> 82260072 == 82260072
    17 OK:  phi(1234567890) ==> 329040288 == 329040288
    18 OK:  phi(1234) ==> 616 == 616
    19 OK:  phi(12345) ==> 6576 == 6576
    20 OK:  phi(123456) ==> 41088 == 41088
    21 OK:  phi(1234567) ==> 1224720 == 1224720
    22 OK:  phi(12345678) ==> 4027392 == 4027392
    23 OK:  phi(123456789) ==> 82260072 == 82260072
    24 OK:  phi(1234567890) ==> 329040288 == 329040288
    25 OK:  phi(1234) ==> 616 == 616
    26 OK:  phi(12345) ==> 6576 == 6576
    27 OK:  phi(123456) ==> 41088 == 41088
    28 OK:  phi(1234567) ==> 1224720 == 1224720
    29 OK:  phi(12345678) ==> 4027392 == 4027392
    30 OK:  phi(123456789) ==> 82260072 == 82260072
    31 OK:  phi(1234567890) ==> 329040288 == 329040288
    32 OK:  phi(1234) ==> 616 == 616
    33 OK:  phi(12345) ==> 6576 == 6576
    34 OK:  phi(123456) ==> 41088 == 41088
    35 OK:  phi(1234567) ==> 1224720 == 1224720
    36 OK:  phi(12345678) ==> 4027392 == 4027392
    37 OK:  phi(123456789) ==> 82260072 == 82260072
    38 OK:  phi(1234567890) ==> 329040288 == 329040288
    39 OK:  phi(1234) ==> 616 == 616
    40 OK:  phi(12345) ==> 6576 == 6576
    41 OK:  phi(123456) ==> 41088 == 41088
    42 OK:  phi(1234567) ==> 1224720 == 1224720
    43 OK:  phi(12345678) ==> 4027392 == 4027392
    44 OK:  phi(123456789) ==> 82260072 == 82260072
    45 OK:  phi(1234567890) ==> 329040288 == 329040288
    46 OK:  phi(1234) ==> 616 == 616
    47 OK:  phi(12345) ==> 6576 == 6576
    48 OK:  phi(123456) ==> 41088 == 41088
    49 OK:  phi(1234567) ==> 1224720 == 1224720
    50 OK:  phi(12345678) ==> 4027392 == 4027392
    51 OK:  phi(123456789) ==> 82260072 == 82260072
    52 OK:  phi(1234567890) ==> 329040288 == 329040288
    53 OK:  phi(12345678901234567890) ==> 3256788124177920000 == 3256788124177920000

    real	0m0.243s
    user	0m0.170s
    sys	  0m0.013s

How to use it in your programs
------------------------------

Just `#include "phi.h"` and you should be set.

// Prime number generator
// Implements Eulers totient function with libgmp, for arbitrarily large
// integers.
//
// Written by Christian Stigen in 2017
//
// To compile, you need GNU MP (GMP), and you need to link with it:
// g++ primes_gmp.cpp -oprimes_gmp -lgmp -lgmpxx

#include <gmpxx.h>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <time.h>

// Random number generator. Using a single one means that the whole code is not
// thread-safe.
static gmp_randclass *rnd = NULL;

// Fast calculation of a^x mod n
//
// This algorithm is taken from Bruce Schneier's book "Applied Cryptography".
// See http://en.wikipedia.org/wiki/Modular_exponentiation
static mpz_class pow_mod(mpz_class a, mpz_class x, const mpz_class& n)
{
  mpz_class r = 1;

  while (x > 0) {
    if ((x & 1) == 1) {
      r = a*r % n;
    }
    x >>= 1;
    a = a*a % n;
  }

  return r;
}

// Sets the initial random seed.
//
// Bytes is how many bytes from /dev/urandom to use as a seed. If set to zero,
// will just seed with the current time.
//
// Returns the number of bytes read from /dev/urandom.
//
extern "C" int initialize_seed(const size_t bytes)
{
  if (!rnd)
    rnd = new gmp_randclass(gmp_randinit_default);

  if (bytes > 0) {
    FILE *f = fopen("/dev/urandom", "rb");
    if (!f) {
      perror("/dev/urandom");
      // Fall-through to use current time as seed
    } else {
      mpz_class seed = 0;
      for ( size_t i = 0; i < bytes; ++i ) {
        int n = fgetc(f);
        seed = (seed << 8) | n;
      }

      fclose(f);
      rnd->seed(seed);
      return bytes;
    }
  }

  // Just seed with the current time
  rnd->seed(time(NULL));
  return 0;
}

static mpz_class randint(const mpz_class& lowest, const mpz_class& highest)
{
  if (!rnd) {
    // Default number of bytes to read for seed
    initialize_seed(256 / 8);
  }

  return rnd->get_z_range(highest - lowest) + lowest;
}

// The Miller-Rabin primality test
//
// This part was closely based on an earlier version of the Miller-Rabin
// primality tester that I wrote in 2012, available at:
// https://github.com/cslarsen/miller-rabin
//
static bool prob_prime(const mpz_class& n, const size_t rounds)
{
  // Base cases:
  //   - Treat 1 and all negative numbers as non-prime
  //   - Drop even numbers (including zero)
  if (n <= 1 || (n & 1) == 0)
    return false;

  // Do not iterate for the first two prime numbers
  if (n == 2 || n == 3)
    return true;

  // Write n-1 as d*2^s by factoring powers of 2 from n-1
  size_t s = 0;
  {
    mpz_class m = n - 1;
    while ((m & 1) == 0) {
      ++s;
      m >>= 1;
    }
  }
  const mpz_class d = (n - 1) / (mpz_class(1) << s);

  for (size_t i = 0; i < rounds; ++i) {
    const mpz_class a = randint(2, n - 2);
    mpz_class x = pow_mod(a, d, n);

    if (x ==1 || x == (n - 1))
      continue;

    for (size_t r = 0; r < (s-1); ++r) {
      x = pow_mod(x, 2, n);
      if (x == 1) {
        // Definitely not a prime
        return false;
      }
      if (x == n - 1)
        break;
    }

    if (x != (n - 1)) {
      // Definitely not a prime
      return false;
    }
  }

  // Might be prime
  return true;
}

int main()
{
  const size_t bits = 256;
  const size_t accuracy = bits/2;

  std::cout << "Finding two " << bits
    << "-bit prime number q and p so that p=2q+1" << std::endl;

  mpz_class low = 1;
  low <<= (bits-1);

  mpz_class high = 1;
  high <<= bits;
  high -= 1;

  for (;;) {
    mpz_class q = randint(low, high);

    // Skip even numbers
    if ((q & 1) == 0)
      continue;

    // Speed up by simple check
    if (!prob_prime(q, 5))
      continue;

    if (prob_prime(q, accuracy)) {
      mpz_class p = 2*q + 1;

      if (prob_prime(p, accuracy)) {
        std::cout << "q = " << q << std::endl;
        std::cout << "p = " << p << std::endl;
        break;
      }
    }
  }
}

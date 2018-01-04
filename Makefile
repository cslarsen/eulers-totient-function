TARGET = test primes_gmp
CXXFLAGS = -W -Wall -O3 -march=native

check: all
	bash -c "time ./$(TARGET)"

all: $(TARGET)

primes_gmp: primes_gmp.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ -lgmp -lgmpxx

clean:
	rm -f $(TARGET)

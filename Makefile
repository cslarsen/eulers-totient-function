TARGET = test
CXXFLAGS = -W -Wall -O3

check: all
	bash -c "time ./$(TARGET)"

all: $(TARGET)

clean:
	rm -f $(TARGET)

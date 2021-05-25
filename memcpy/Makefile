CXX=g++
CXXFLAGS=-O1
#$(warning SIMDFLAG=$(SIMDFLAG))

all:test_stdlib test_avx512f test_mavx test_naive test_long

test_stdlib:test.cpp
	$(CXX) -o test_stdlib test.cpp $(CXXFLAGS) -D STD_MEMCPY

test_avx512f:test.cpp
	$(CXX) -o test_mavx512f test.cpp $(CXXFLAGS) -mavx512f -D AVX512_MEMCPY

test_mavx:test.cpp
	$(CXX) -o test_mavx test.cpp $(CXXFLAGS) -mavx -D AVX_MEMCPY

test_naive:test.cpp
	$(CXX) -o test_naive test.cpp $(CXXFLAGS) -D NAIVE_MEMCPY

test_long:test.cpp
	$(CXX) -o test_long test.cpp $(CXXFLAGS) -D LONG_MEMCPY

clean:
	-rm -f ./test_*


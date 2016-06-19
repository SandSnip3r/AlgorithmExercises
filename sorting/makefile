CC := g++-5
WARNING_FLAGS := -Wall
# WARNING_FLAGS := -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wswitch-default -Wundef -Werror -Wno-unused -Wstrict-overflow=5
# WARNING_FLAGS := -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wswitch-default -Wundef -Werror -Wno-unused -Wstrict-overflow=2
CFLAGS := -std=c++17 -O3 $(WARNING_FLAGS)

all: timeTest

timeTest: timeTest.o
	$(CC) -o timeTest timeTest.o $(CFLAGS)

timeTest.o: bogosort.hpp heapsort.hpp insertionSort.hpp introsort.hpp quicksort.hpp timeTest.cpp ../utilites/timeUtility.hpp
	$(CC) -c timeTest.cpp -I../utilites/ $(CFLAGS)

clean:
	$(RM) *.o

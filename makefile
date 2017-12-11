# Shimon Cohen 315383133
# Nadav Spitzer 302228275

a.out: compileAll
	g++ *.o -o ../../exe/a.out
	rm -f *.o

compileAll: *.h *.cpp
	g++ -c *.cpp

run:
	./a.out

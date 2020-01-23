all:
	mkdir -p bin/
	g++ leb_128_test.c lib/leb128.c lib/types.h lib/utils.c -o bin/leb_128_test.out
	g++ elias_gamma_test.c lib/elias_gamma.c lib/types.h lib/utils.c -o bin/elias_gamma_test.out

run:
	./bin/leb_128_test.out

clean:
	rm -rf ./bin
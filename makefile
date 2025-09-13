bin/programa : src/main.cpp include/Foco.hpp include/Es
	c++ src/main.cpp -o bin/programa -I include

run : bin/programa
	./bin/programa

bin/memoria : src/memoria.cpp
	c++ src/memoria.cpp -o bin/memoria

runMemoria : bin/memoria
	./bin/memoria
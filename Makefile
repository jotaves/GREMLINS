make:
	g++ -Wall -std=c++11 src/gremlins_drive.cpp -o bin/drive -I include/
run:
	./bin/drive
clean:
	rm bin/*
mleak:
	valgrind --tool=memcheck --leak-check=yes ./bin/drive
mlfull:
	valgrind --leak-check=full --show-leak-kinds=all ./bin/drive
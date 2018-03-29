CC = g++

gameResources: main.o resource.o userInterface.o resourceManager.o
	$(CC) main.o resource.o userInterface.o resourceManager.o -o gameResources

main.o: main.cpp
	$(CC) -c main.cpp -Wall

resource.o: resource.cpp resource.h
	$(CC) -c resource.cpp -Wall

userInterface.o: userInterface.cpp userInterface.h
	$(CC) -c userInterface.cpp -Wall

resourceManager.o: resourceManager.cpp resourceManager.h
	$(CC) -c resourceManager.cpp -Wall

clean:
	rm -rf *.o

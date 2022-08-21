CC = g++
PROJECT = zMatrix
SRC = *.cpp

$(PROJECT) : $(SRC)
	$(CC) $(SRC) -o $(PROJECT) -lstdc++fs -g
CC=g++
CFLAGS=-std=c++11 -Wall

EXECULTABLE=./main

OBJ_DIR    = ./bin
SOURCE_DIR = ./src
INCLUDE_DIR  = ./include

${EXECULTABLE}: ${OBJ_DIR}/main.o ${OBJ_DIR}/casa.o ${OBJ_DIR}/mesa.o
	${CC} ${CFLAGS} ${OBJ_DIR}/*.o -o ${EXECULTABLE} -g

${OBJ_DIR}/main.o: ${SOURCE_DIR}/main.cpp ${INCLUDE_DIR}/casa.hpp ${INCLUDE_DIR}/mesa.hpp 
	${CC} ${CFLAGS} -I ${INCLUDE_DIR} -c ${SOURCE_DIR}/main.cpp -o ${OBJ_DIR}/main.o -g

${OBJ_DIR}/casa.o: ${INCLUDE_DIR}/casa.hpp ${SOURCE_DIR}/casa.cpp ${INCLUDE_DIR}/mesa.hpp
	${CC} ${CFLAGS} -I ${INCLUDE_DIR} -c ${SOURCE_DIR}/casa.cpp -o ${OBJ_DIR}/casa.o -g

${OBJ_DIR}/mesa.o: ${INCLUDE_DIR}/mesa.hpp ${SOURCE_DIR}/mesa.cpp ${INCLUDE_DIR}/casa.hpp 
	${CC} ${CFLAGS} -I ${INCLUDE_DIR} -c ${SOURCE_DIR}/mesa.cpp -o ${OBJ_DIR}/mesa.o -g

clean:
	rm -rf ${OBJ_DIR}/*
	rm -rf ./bin/*
	rm main
	clear

try:
	./main < inputs/5.in
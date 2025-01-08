CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -Iinclude

#Ruta de los archivos .c
RUTA_C = src
#Ruta de los archivos .h
RUTA_H = include

all: bin/simula_car

.PHONY: clean 
clean: #Borra el ejecutable y los archivos objeto
	rm -rf bin/* build/*
	rm -rf bin build

build: #Crea la carpeta build
	mkdir -p build 

bin: #Crea la carpeta bin
	mkdir -p bin

bin/simula_car: bin build build/funcion_coche.o build/simula_car.o
	$(CC) $(CFLAGS) -o bin/simula_car build/funcion_coche.o build/simula_car.o -lpthread

build/funcion_coche.o: $(RUTA_C)/funcion_coche.c $(RUTA_H)/simula_car.h
	$(CC) $(CFLAGS) -c $(RUTA_C)/funcion_coche.c -o build/funcion_coche.o

build/simula_car.o: $(RUTA_C)/simula_car.c $(RUTA_H)/simula_car.h
	$(CC) $(CFLAGS) -c $(RUTA_C)/simula_car.c -o build/simula_car.o

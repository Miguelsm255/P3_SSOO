CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

#Ruta de los archivos .c
RUTA_C = src

all: bin/simula_car

.PHONY: clean 
clean: #Borra el ejecutable y los archivos objeto
	rm -rf bin/* build/*
	rmdir bin build

build: #Crea la carpeta build
	mkdir -p build 

bin: #Crea la carpeta bin
	mkdir -p bin

bin/simula_car: bin build build/funcion_coche.o build/simula_car.o
	$(CC) $(CFLAGS) -o bin/simula_car build/funcion_coche.o build/simula_car.o

build/funcion_coche.o: $(RUTA_C)/funcion_coche.c
	$(CC) $(CFLAGS) -c $(RUTA_C)/funcion_coche.c -o build/funcion_coche.o

build/simula_car.o: $(RUTA_C)/simula_car.c
	$(CC) $(CFLAGS) -c $(RUTA_C)/simula_car.c -o build/simula_car.o

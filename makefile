build:
	cc -c source/table/table.c -o objects/table.o
	cc objects/table.o source/main.c -o start
	./start
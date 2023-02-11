build:
	cc -c source/parser/parser.c -o objects/parser.o
	cc -c source/table/table.c -o objects/table.o
	cc objects/macros.o objects/table.o objects/parser.o source/main.c -o preprocessor
# Autores:
#	--> Douglas Gehring
#	--> Tobias Soares
#
# Grupo: O

TARGET = etapa3
OFILES = *.o
PARSFILES = parser.tab* parser.output
LEXFILE = lex*

default: all

main: main.c
	gcc main.c -c

scanner: scanner.l
	flex scanner.l
	gcc lex.yy.c -c

extra: extra.c
	gcc extra.c -c

parser: parser.y
	bison -d parser.y
	gcc parser.tab.c -c

ast: AST.c
	gcc AST.c -c

valorLexico: ValorLexico.c
	gcc ValorLexico.c -c

parserRportFile: parser.y
	bison -d parser.y --report-file=parser.output -r cex
	gcc parser.tab.c -c

all: parser main scanner extra valorLexico ast
	gcc $(OFILES) -o $(TARGET)

reportFile: parserRportFile main scanner extra
	gcc $(OFILES) -o $(TARGET)

valgrind: parser main scanner extra valorLexico ast
	gcc $(OFILES) -o $(TARGET) -g
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET) < input.txt


clean:
	rm -f $(OFILES) $(PARSFILES) $(LEXFILE) $(TARGET)

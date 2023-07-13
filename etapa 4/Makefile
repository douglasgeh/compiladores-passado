# Autores:
#	--> Douglas Gehring
#	--> Tobias Soares
#
# Grupo: O

TARGET = etapa4
OFILES = *.o
PARSFILES = parser.tab* parser.output
LEXFILE = lex*
OUTPUT = output.txt
CFLAGS = -c
VALFLAGS = -s --leak-check=full --show-leak-kinds=all

default: all

main: main.c
	gcc main.c $(CFLAGS)

scanner: scanner.l
	flex scanner.l
	gcc lex.yy.c $(CFLAGS)

extra: extra.cpp
	g++ -std=c++11 -c extra.cpp

parser: parser.y
	bison -d parser.y
	g++ -std=c++11 -c parser.tab.c

ast: AST.c
	gcc AST.c $(CFLAGS)

valorLexico: ValorLexico.c
	gcc ValorLexico.c $(CFLAGS)

symbolTableNode: SymbolTableNode.c
	gcc SymbolTableNode.c $(CFLAGS)

syntacticalType: SyntacticalType.c
	gcc SyntacticalType.c $(CFLAGS)

symbolsTable: SymbolsTable.cpp
	g++ -std=c++11 -c SymbolsTable.cpp

scopesManager: ScopesManager.cpp
	g++ -std=c++11 -c ScopesManager.cpp	

utils: Utils.cpp
	g++ -std=c++11 -c Utils.cpp	

errorManager: ErrorManager.cpp
	g++ -std=c++11 -c ErrorManager.cpp	

parserRportFile: parser.y
	bison -d parser.y --report-file=parser.output -r cex
	gcc parser.tab.c $(CFLAGS)

all: parser main scanner extra valorLexico ast symbolTableNode syntacticalType symbolsTable scopesManager utils errorManager
	g++ -std=c++11 -o $(TARGET) $(OFILES)

reportFile: parserRportFile main scanner extra
	gcc $(OFILES) -o $(TARGET)

valgrind: debug
	valgrind $(VALFLAGS) ./$(TARGET) < input.txt

debug: CFLAGS += -g
debug: all

clean:
	rm -f $(OFILES) $(PARSFILES) $(LEXFILE) $(TARGET) $(OUTPUT)

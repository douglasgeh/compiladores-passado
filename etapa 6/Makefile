# Autores:
#	--> Douglas Gehring
#	--> Tobias Soares
#
# Grupo: O

TARGET = etapa6
OFILES = *.o
PARSFILES = parser.tab* parser.output
LEXFILE = lex*
CPPFILES = *.cpp
HPPFILES = *.hpp
CFILES = *.c
OUTPUT = output.txt
CPPSTD = -std=c++11
CPPFLAGS = $(CPPSTD) -c

default: build

scanner: scanner.l
	flex scanner.l

parser: parser.y
	bison -d parser.y

createOFiles: parser scanner
	g++ $(CPPFLAGS) $(CFILES) $(CPPFILES)

build: createOFiles
	g++ $(CPPSTD) -o $(TARGET) $(OFILES) -lfl

debug: CPPFLAGS += -g
debug: build

clean:
	rm -f $(OFILES) $(PARSFILES) $(LEXFILE) $(TARGET) $(OUTPUT)

wrapItUp:
	tar cvzf $(TARGET).tgz $(CPPFILES) $(HPPFILES) Makefile parser.y readme.txt scanner.l
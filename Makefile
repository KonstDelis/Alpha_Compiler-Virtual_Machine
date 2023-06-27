CC = gcc
CPPC = g++ -std=c++17

all: compiler alphavm

again: clean cleanGenerated compiler alphavm	

compiler: AlphaCompiler/lexer.c AlphaCompiler/parser.c
	@echo compiling libraries..
	@$(CC) AlphaCompiler/libraries/*.c -c
	@echo compiling lexer and parser..
	@gcc AlphaCompiler/lexer.c -c
	@gcc AlphaCompiler/parser.c *.o -o alphac
	@rm -rf *.o
	@rm -rf quads_out.txt
	@echo alpha compiler is ready!


alphavm:
	@echo creating alpha virtual machine..
	@$(CPPC) VM/*.cpp -c
	@$(CPPC) VM/VM_executes/*.cpp -c
	@$(CPPC) VM/LibFunctions/*.cpp -c
	@$(CPPC) *.o -o avm
	@rm -rf *.o
	@echo avm is ready!

AlphaCompiler/lexer.c: 
	@echo generating lexer..
	@flex --outfile=AlphaCompiler/lexer.c AlphaCompiler/flex.l
	
AlphaCompiler/parser.c:
	@echo generating parser..
	@bison --defines --output=AlphaCompiler/parser.c AlphaCompiler/syntax_analyzer.y

clean: cleanBinaries cleanExecutables
	
cleanExecutables:
	@rm -rf *.exe *.o *.out
	@rm -rf avm alphac quads_out.txt
	@echo all executables have been cleaned!

cleanBinaries:
	@rm -rf *.abc
	@echo all binaries have been cleaned!

cleanGenerated:
	@rm -rf AlphaCompiler/parser.h AlphaCompiler/parser.c AlphaCompiler/lexer.c
	@echo Parser and Lexer generated files have been deleted!

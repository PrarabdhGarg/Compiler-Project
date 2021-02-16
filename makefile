all:
	gcc -g -w main.c ./Lexer/TwinBuffer.c ./Lexer/Lexer.c ./Parser/grammar.c symbolTable.c
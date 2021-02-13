#include "Lexer.h"

char *tokenTypeToString[] = {"ID", "PLUS", "MINUS", "MUL", "DIV", "LE", "DEF", "LT", "GE", "ENDDEF", "GT", "EQ", "NE", "ASSIGNOP",
    "COLON", "RANGEOP", "SEMICOL", "COMMA", "SQBO", "SQBC", "BO", "BC", "NUM", "RNUM", "INTEGER", 
    "REAL", "BOOLEAN", "OF", "ARRAY", "START", "END", "DECLARE", "MODULE", "DRIVER", "PROGRAM",
    "RECORD", "TAGGED", "UNION", "GET_VALUE", "PRINT", "USE", "WITH", "PARAMETERS", "TRUE", 
    "FALSE", "TAKES", "INPUT", "RETURNS", "AND", "OR", "FOR", "IN", "SWITCH", "CASE", "BREAK",
    "DEFAULT", "WHILE"};

Lexer *newLexer(char *fileName) {
    Lexer *lexer = (Lexer *) malloc(sizeof(Lexer));
    lexer -> buffer = newBuffer(fileName);
    lexer -> lineNumber = 1;
    lexer -> symbolTable = newSymbolTable();
    return lexer;
}

Token *newToken(Lexer *lexer, TokenType tokenType) {
    Token *token = (Token *) malloc(sizeof(Token));
    token -> token = tokenType;
    token -> lexeme = getLexeme(lexer -> buffer);
    token -> lineNumber = lexer -> lineNumber;
    if(exists(token -> lexeme, lexer -> symbolTable) == NULL && (tokenType == ID)) {
        insertToken(token -> lexeme, token -> token, lexer -> symbolTable);
    }
    return token;
}

Token *getNextToken(Lexer *lexer) {
    TwinBuffer *buffer = lexer -> buffer;
    int state = 0;
    char lookahead = nextChar(buffer);
    while(1) {
        switch (state) {
        case 0:
            switch (lookahead) {
                case '\n':
                    printf("NewLine \n");
                    lexer -> lineNumber += 1;
                case '\t':
                case ' ':
                    getLexeme(buffer);
                    break;
                case '+':
                    return newToken(lexer, PLUS);
                case '-':
                    return newToken(lexer, MINUS);
                case '*':
                    state = 3;
                    break;
                case '/':
                    return newToken(lexer, DIV);
                case '<':
                    state = 6;
                    break;
                case '>':
                    state = 10;
                    break;
                case '=':
                    state = 14;
                    break;
                case '!':
                    state = 16;
                    break;
                case ':':
                    state = 18;
                    break;
                case '.':
                    state = 21;
                    break;
                case ';':
                    return newToken(lexer, SEMICOL);
                case ',':
                    return newToken(lexer, COMMA);
                case '[':
                    return newToken(lexer, SQBO);
                case ']':
                    return newToken(lexer, SQBC);
                case '(':
                    return newToken(lexer, BO);
                case ')':
                    return newToken(lexer, BC);
                case '\0':
                    retract(buffer, 1);
                    return NULL;
                default: {
                    if(isalpha(lookahead)) {
                        state = 29;
                    } else if(isdigit(lookahead)) {
                        state = 31;
                    } else {
                        printf("Lexical Error: Line Number: %d Invalid character detected\n", lexer -> lineNumber);
                        return NULL;
                    }
                }
            }
            break;
        case 3:
            if(lookahead == '*') {
                state = 39;
            } else {
                retract(buffer, 1);
                return newToken(lexer, MUL);
            }
            break;
        case 6:
            switch(lookahead) {
                case '=':
                    return newToken(lexer, LE);
                case '<':
                    return newToken(lexer, DEF);
                default:
                    retract(buffer, 1);
                    return newToken(lexer, LT);
            }
            break;
        case 10:
            switch(lookahead) {
                case '=':
                    return newToken(lexer, GE);
                case '>':
                    return newToken(lexer, ENDDEF);
                default:
                    retract(buffer, 1);
                    return newToken(lexer, GT);
            }
            break;
        case 14:
            if(lookahead == '=') {
                return newToken(lexer, EQ);
            } else {
                printf("Lexical Error: Line Number: %d Expecting = Found %c\n", lexer -> lineNumber, lookahead);
                return NULL;
            }
            break;
        case 16:
            if(lookahead == '=') {
                return newToken(lexer, NE);
            } else {
                printf("Lexical Error: Line Number: %d Expecting = Found %c\n", lexer -> lineNumber, lookahead);
                return NULL;
            }
            break;
        case 18:
            if(lookahead == '=')
                return newToken(lexer, ASSIGNOP);
            else {
                retract(buffer, 1);
                return newToken(lexer, COLON);
            }
            break;
        case 21:
            if(lookahead == '.') {
                return newToken(lexer, RANGEOP);
            } else {
                printf("Lexical Error: Line Number: %d Expecting . Found %c\n", lexer -> lineNumber, lookahead);
                return NULL;
            }
            break;
        case 29:
            if(isspace(lookahead)) {
                retract(buffer, 1);
                return newToken(lexer, ID);
            } else if(isalnum(lookahead) || lookahead == '_') {
                state = 29;
            } else {
                retract(buffer, 1);
                return newToken(lexer, ID);
            }
            break;
        case 31:
            if(isdigit(lookahead)) {
                state = 31;
            } else if(lookahead == 'e' || lookahead == 'E') {
                state = 36;
            } else if(lookahead == '.') {
                state = 33;
            } else {
                retract(buffer, 1);
                return newToken(lexer, NUM);
            }
            break;
        case 33:
            if(isdigit(lookahead)) {
                state = 34;
            } else {
                printf("Lexical Error: Line Number: %d Expecting Digit. Found %c\n", lookahead);
                return NULL;
            }
            break;
        case 34:
            if(isdigit(lookahead)) {
                state = 34;
            } else if(lookahead == 'e' || lookahead == 'E') {
                state = 36;
            } else {
                retract(buffer, 1);
                return newToken(lexer, RNUM);
            }
            break;
        case 36:
            if(isdigit(lookahead)) {
                state = 38;
            } else if(lookahead == '+' || lookahead == '-') {
                state = 37;
            } else {
                printf("Lexical Error: Line Number: %d Expecting +, -, or Digit. Found %c\n", lookahead);
                return NULL;
            }
            break;
        case 37:
            if(isdigit(lookahead)) {
                state = 38;
            } else {
                printf("Lexical Error: Line Number: %d Expecting Digit. Found %c\n", lookahead);
                return NULL;
            }
            break;
        case 38:
            if(isdigit(lookahead)) {
                state = 38;
            } else {
                retract(buffer, 1);
                return newToken(lexer, RNUM);
            }
            break;
        case 39:
            if(lookahead == '*') {
                state = 40;
            }
            break;
        case 40:
            if(lookahead == '*') {
                state = 0;
            }
            break;
        default:
            printf("Error in lexer. Invalid State Reached\n");
            break;
        }
        lookahead = nextChar(buffer);
    }
}

void printToken(Token *token) {
    printf("Token Type = %-10s Line Number = %-3d Value = %s\n", tokenTypeToString[token -> token], token -> lineNumber, token -> lexeme);
}
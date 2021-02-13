#include <string.h>

#define SIZE_OF_HASH_TABLE 10
#define NO_OF_KEYWORDS 32

typedef enum {
    ID, PLUS, MINUS, MUL, DIV, LE, DEF, LT, GE, ENDDEF, GT, EQ, NE, ASSIGNOP,
    COLON, RANGEOP, SEMICOL, COMMA, SQBO, SQBC, BO, BC, NUM, RNUM, INTEGER, 
    REAL, BOOLEAN, OF, ARRAY, START, END, DECLARE, MODULE, DRIVER, PROGRAM,
    RECORD, TAGGED, UNION, GET_VALUE, PRINT, USE, WITH, PARAMETERS, TRUE, 
    FALSE, TAKES, INPUT, RETURNS, AND, OR, FOR, IN, SWITCH, CASE, BREAK,
    DEFAULT, WHILE
} TokenType;

typedef struct {
    TokenType token;
    char *lexeme;
    int lineNumber;
} Token;

// The structure containing all information stored in a symbol table
typedef struct {
    TokenType type;
    char *lexeme;
} SymbolTableElement;

// Internal Structure used to store the symbol table as a hash table
typedef struct {
    SymbolTableElement *element;
    SymbolTableElement *next;
} SymbolTableNode;

typedef SymbolTableNode *SymbolTable;

extern SymbolTable newSymbolTable();
extern SymbolTableElement *exists(char *lexeme, SymbolTable symbolTable);
extern SymbolTableElement *insertToken(char *lexeme, TokenType tokenType, SymbolTable symbolTable);
extern void printSymbolTable(SymbolTable SymbolTable);
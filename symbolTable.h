#include <string.h>

#define SIZE_OF_HASH_TABLE 10

typedef enum {
    ID
} TokenType;

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
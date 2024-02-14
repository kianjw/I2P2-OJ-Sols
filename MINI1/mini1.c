#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


// for lex
#define MAXLEN 256

// Token types
typedef enum {
    UNKNOWN, END, ENDFILE,
    INT, ID,
    ADDSUB, MULDIV,
    ASSIGN, INCDEC,
    LPAREN, RPAREN, XOR, OR, AND, ADDSUB_ASSIGN
} TokenSet;

TokenSet getToken(void);
TokenSet curToken = UNKNOWN;
char lexeme[MAXLEN];

// Test if a token matches the current token
int match(TokenSet token);
// Get the next token
void advance(void);
// Get the lexeme of the current token
char *getLexeme(void);


// for parser
#define TBLSIZE 64
// Set PRINTERR to 1 to print error message while calling error()
// Make sure you set PRINTERR to 0 before you submit your code
#define PRINTERR 0

// Call this macro to print error message and exit the program
// This will also print where you called it in your program
#define error(errorNum) { \
    if (PRINTERR) \
        fprintf(stderr, "error() called at %s:%d: ", __FILE__, __LINE__); \
    err(errorNum); \
}

// Error types
typedef enum {
    UNDEFINED, MISPAREN, NOTNUMID, NOTFOUND, RUNOUT, NOTLVAL, DIVZERO, SYNTAXERR
} ErrorType;

// Structure of the symbol table
typedef struct {
    int val;
    char name[MAXLEN];
} Symbol;

// Structure of a tree node
typedef struct _Node {
    TokenSet data;
    int val;
    char lexeme[MAXLEN];
    struct _Node *left;
    struct _Node *right;
} BTNode;

int sbcount = 0;
Symbol table[TBLSIZE];
// Initialize the symbol table with builtin variables
void initTable(void);
// Get the value of a variable
int getval(char *str, int **idx);
// Set the value of a variable
int setval(char *str, int val, int **idx);
// Make a new node according to token type and lexeme
BTNode *makeNode(TokenSet tok, const char *lexe);
// Free the syntax tree
void freeTree(BTNode *root);
BTNode *factor(void);

BTNode *assign_expr(void);
BTNode *or_expr(void);
BTNode *or_expr_tail(BTNode *left);
BTNode *xor_expr(void);
BTNode *xor_expr_tail(BTNode *left);
BTNode *and_expr(void);
BTNode *and_expr_tail(BTNode *left);
BTNode *addsub_expr(void);
BTNode *addsub_expr_tail(BTNode *left);
BTNode *muldiv_expr(void);
BTNode *muldiv_expr_tail(BTNode *left);
BTNode *unary_expr(void);
void statement(void);
// Print error message and exit the program
void err(ErrorType errorNum);


// for codeGen
// Evaluate the syntax tree
int evaluateTree(BTNode *root);
// Print the syntax tree in prefix
void printPrefix(BTNode *root);

int /*reg=0,*/ idx; //move the regular register count into local function variables.
int totReg=0; //keep track of total amount of registers

/*============================================================================================
lex implementation
============================================================================================*/

TokenSet getToken(void)
{
    int i = 0;
    char c = '\0';

    while ((c = fgetc(stdin)) == ' ' || c == '\t');

    if (isdigit(c)) {
        lexeme[0] = c;
        c = fgetc(stdin);
        i = 1;
        while (isdigit(c) && i < MAXLEN) {
            lexeme[i] = c;
            ++i;
            c = fgetc(stdin);
        }
        ungetc(c, stdin);
        lexeme[i] = '\0';
        return INT;
    } else if (c == '+' || c == '-') {
        lexeme[0] = c;
        c=fgetc(stdin);
        if(c == lexeme[0]){
            lexeme[1] = c;
            lexeme[2] = '\0';
            return INCDEC;
        }
        else if(c == '='){
            lexeme[1] = c;
            lexeme[2] = '\0';
            return ADDSUB_ASSIGN;
        }
        ungetc(c, stdin);
        lexeme[1] = '\0';
        return ADDSUB;
    } else if (c == '*' || c == '/') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return MULDIV;
    } else if (c == '\n') {
        lexeme[0] = '\0';
        return END;
    } else if (c == '=') {
        strcpy(lexeme, "=");
        return ASSIGN;
    } else if (c == '(') {
        strcpy(lexeme, "(");
        return LPAREN;
    } else if (c == ')') {
        strcpy(lexeme, ")");
        return RPAREN;
    } else if (c == '^'){
        strcpy(lexeme, "^");
        return XOR;
    }
    else if(c=='|'){
        strcpy(lexeme, "|");
        return OR;
    }
    else if(c=='&'){
        strcpy(lexeme, "&");
        return AND;
    }
    else if (isalpha(c)) {
        lexeme[0] = c;
        c = fgetc(stdin);
        i = 1;
        while ((isalpha(c) || isdigit(c) || c == '_')&& i < MAXLEN) {
            lexeme[i] = c;
            ++i;
            c = fgetc(stdin);
        }
        ungetc(c, stdin);
        lexeme[i] = '\0';
        return ID;
    } else if (c == EOF) {
        return ENDFILE;
    } else {
        return UNKNOWN;
    }
}

void advance(void) {
    curToken = getToken();
}

int match(TokenSet token) {
    if (curToken == UNKNOWN)
        advance();
    return token == curToken;
}

char *getLexeme(void) {
    return lexeme;
}


/*============================================================================================
parser implementation
============================================================================================*/

void initTable(void) {
    strcpy(table[0].name, "x");
    table[0].val = 0;
    strcpy(table[1].name, "y");
    table[1].val = 0;
    strcpy(table[2].name, "z");
    table[2].val = 0;
    sbcount = 3;
}

int getval(char *str, int **idx) {
    int i = 0;

    for (i = 0; i < sbcount; i++){
        if (strcmp(str, table[i].name) == 0){
            *idx = i;
            return table[i].val;
        }
    }


    if (sbcount >= TBLSIZE)
        error(RUNOUT);

    err(UNDEFINED);
}

int setval(char *str, int val, int **idx) {
    int i = 0;

    for (i = 0; i < sbcount; i++) {
        if (strcmp(str, table[i].name) == 0) {
            table[i].val = val;
            *idx = i;
            return val;
        }
    }

    if (sbcount >= TBLSIZE)
        error(RUNOUT);

    strcpy(table[sbcount].name, str);
    table[sbcount].val = val;
    *idx = sbcount;
    sbcount++;
    return val;
}

BTNode *makeNode(TokenSet tok, const char *lexe) {
    BTNode *node = (BTNode*)malloc(sizeof(BTNode));
    strcpy(node->lexeme, lexe);
    node->data = tok;
    node->val = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void freeTree(BTNode *root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

// factor := INT | ADDSUB INT |
//		   	 ID  | ADDSUB ID  |
//		   	 ID ASSIGN expr |
//		   	 LPAREN expr RPAREN |
//		   	 ADDSUB LPAREN expr RPAREN
BTNode *factor(void) {
    BTNode *retp = NULL, *left = NULL;

    if (match(INT)) {
        retp = makeNode(INT, getLexeme());
        advance();
    } else if (match(ID)) {
        retp = makeNode(ID, getLexeme());
        advance();
    }
    else if (match(INCDEC)){
        retp = makeNode(INCDEC, getLexeme());
        retp->right = makeNode(INT, "1");
        advance();
        if(!match(ID)){
            err(SYNTAXERR);
        }
        else{
            retp->left = makeNode(ID, getLexeme());
            advance();
        }
    }
    else if (match(LPAREN)) {
        advance();
        retp = assign_expr();
        if (match(RPAREN))
            advance();
        else
            error(MISPAREN);
    } else {
        error(NOTNUMID);
    }
    return retp;
}


BTNode *assign_expr(void){
    BTNode *node = NULL;
    BTNode *left = or_expr();
    if(match(ASSIGN)){
        if(left->data != ID){
            err(SYNTAXERR);
        }

            node = makeNode(ASSIGN, getLexeme());
            advance();
            node->left = left;
            node->right = assign_expr();
            return node;

    }
    else if(match(ADDSUB_ASSIGN)){
        if(left->data != ID){
            err(SYNTAXERR);
        }

            node = makeNode(ADDSUB_ASSIGN, getLexeme());
            advance();
            node->left = left;
            node->right = assign_expr();
            return node;

    }
    else{
        return left;
    }
}

BTNode *or_expr(void){
    BTNode *node = xor_expr();
    return or_expr_tail(node);
}
BTNode *or_expr_tail(BTNode *left){
    BTNode *node = NULL;

    if (match(OR)) {
        node = makeNode(OR, getLexeme());
        advance();
        node->left = left;
        node->right = xor_expr();
        return or_expr_tail(node);
    } else {
        return left;
    }
}

BTNode *xor_expr(void){
    BTNode *node = and_expr();
    return xor_expr_tail(node);
}
BTNode *xor_expr_tail(BTNode *left){
    BTNode *node = NULL;

    if (match(XOR)) {
        node = makeNode(XOR, getLexeme());
        advance();
        node->left = left;
        node->right = and_expr();
        return xor_expr_tail(node);
    } else {
        return left;
    }
}

BTNode *and_expr(void){
    BTNode *node = addsub_expr();
    return and_expr_tail(node);
}
BTNode *and_expr_tail(BTNode *left){
    BTNode *node = NULL;

    if (match(AND)) {
        node = makeNode(AND, getLexeme());
        advance();
        node->left = left;
        node->right = addsub_expr();
        return and_expr_tail(node);
    } else {
        return left;
    }
}

BTNode *addsub_expr(void){
    BTNode *node = muldiv_expr();
    return addsub_expr_tail(node);
}
BTNode *addsub_expr_tail(BTNode *left){
    BTNode *node = NULL;

    if (match(ADDSUB)) {
        node = makeNode(ADDSUB, getLexeme());
        advance();
        node->left = left;
        node->right = muldiv_expr();
        return addsub_expr_tail(node);
    } else {
        return left;
    }
}

BTNode *muldiv_expr(void){
    BTNode *node = unary_expr();
    return muldiv_expr_tail(node);
}
BTNode *muldiv_expr_tail(BTNode *left){
    BTNode *node = NULL;

    if (match(MULDIV)) {
        node = makeNode(MULDIV, getLexeme());
        advance();
        node->left = left;
        node->right = unary_expr();
        return muldiv_expr_tail(node);
    } else {
        return left;
    }
}

BTNode *unary_expr(void){
    BTNode *node = NULL;
    if(match(ADDSUB)){
        node = makeNode(ADDSUB, getLexeme());
        advance();
        node->left = makeNode(INT, "0");
        node->right = unary_expr();
        return node;
    }
    else{
        return factor();
    }
}
// statement := ENDFILE | END | expr END
void statement(void) {
    BTNode *retp = NULL;
    totReg = 0;
    if (match(ENDFILE)) {
        printf("MOV r%d [%d]\n",0,0);
        printf("MOV r%d [%d]\n",1,4);
        printf("MOV r%d [%d]\n",2,8);
        printf("EXIT 0\n");
        exit(0);
    } else if (match(END)) {
        //printf(">> ");
        advance();
    } else {
        retp = assign_expr();
        if (match(END)) {
            if(PRINTERR){
                printf("%d\n", evaluateTree(retp));
                printf("Prefix traversal: ");
                printPrefix(retp);
                printf("\n");
                freeTree(retp);
                printf(">> ");
            }
            else{
                evaluateTree(retp);
                freeTree(retp);
            }
            advance();
        } else {
            error(SYNTAXERR);
        }
    }
}

void err(ErrorType errorNum) {
    if (PRINTERR) {
        fprintf(stderr, "error: ");
        switch (errorNum) {
            case MISPAREN:
                fprintf(stderr, "mismatched parenthesis\n");
                break;
            case NOTNUMID:
                fprintf(stderr, "number or identifier expected\n");
                break;
            case NOTFOUND:
                fprintf(stderr, "variable not defined\n");
                break;
            case RUNOUT:
                fprintf(stderr, "out of memory\n");
                break;
            case NOTLVAL:
                fprintf(stderr, "lvalue required as an operand\n");
                break;
            case DIVZERO:
                fprintf(stderr, "divide by constant zero\n");
                break;
            case SYNTAXERR:
                fprintf(stderr, "syntax error\n");
                break;
            default:
                fprintf(stderr, "undefined error\n");
                break;
        }
    }
    printf("EXIT 1\n");
    exit(0);
}


/*============================================================================================
codeGen implementation
============================================================================================*/
int zeroflag=0;
int evaluateTree(BTNode *root) {
    int retval = 0, lv = 0, rv = 0;
    int reg = totReg;
    if (root != NULL) {
        switch (root->data) {
            case ID:
                retval = getval(root->lexeme, &idx);
                zeroflag = 1;
                if(totReg > 7){ //if total registers more than 7 when printing will be r8 so have to move the "current least significance to address" which is r0.
                    printf("MOV [%d] r%d\n", sbcount*4, totReg%8);
                    sbcount++;
                }
                printf("MOV r%d [%d]\n", totReg%8, idx*4);
                totReg++;
                break;
            case INT:
                retval = atoi(root->lexeme);
                if(totReg > 7){
                    printf("MOV [%d] r%d\n", sbcount*4, totReg%8);
                    sbcount++;
                }
                printf("MOV r%d %d\n", totReg%8, retval);
                totReg++;
                break;
            case ASSIGN:
                rv = evaluateTree(root->right);
                retval = setval(root->left->lexeme, rv, &idx);
                printf("MOV [%d] r%d\n", idx*4, reg%8);
                break;
            case ADDSUB_ASSIGN:
                lv = evaluateTree(root->left);
                rv = evaluateTree(root->right);
                if(strcmp(root->lexeme, "+=") == 0){
                    retval = lv + rv;
                    setval(root->left->lexeme, retval, &idx);
                    printf("ADD r%d r%d\n", reg%8, (reg+1)%8);
                    //printf("MOV [%d] r%d\n", idx*4, reg-2);
                }
                else if(strcmp(root->lexeme, "-=") == 0){
                    retval = lv - rv;
                    setval(root->left->lexeme, retval, &idx);
                    printf("SUB r%d r%d\n", reg%8, (reg+1)%8);
                    //printf("MOV [%d] r%d\n", idx*4, reg-2);
                }
                printf("MOV [%d] r%d\n", idx*4, reg%8);
                if(totReg > 8){
                    sbcount--;
                    totReg--;
                    printf("MOV r%d [%d]\n", totReg%8,sbcount*4);
                }
                else{
                    totReg--;
                }
                break;
            case MULDIV:
                lv = evaluateTree(root->left);
                zeroflag =0;
                rv = evaluateTree(root->right);
                if (strcmp(root->lexeme, "*") == 0) {
                    retval = lv * rv;
                    printf("MUL r%d r%d\n", reg%8, (reg+1)%8);
                }
                else if (strcmp(root->lexeme, "/") == 0) {
                    if (rv == 0 && zeroflag==0){
                        error(DIVZERO);
                    } else if(rv==0 && zeroflag ==1){
                        retval = 0;
                        printf("DIV r%d r%d\n", reg%8, (reg+1)%8);
                    }
                    else{
                        retval = lv / rv;
                        printf("DIV r%d r%d\n", reg%8, (reg+1)%8);
                    }
                }
                if(totReg > 8){
                    sbcount--;
                    totReg--;
                    printf("MOV r%d [%d]\n", totReg%8,sbcount*4);
                }
                else{
                    totReg--;
                }
                //reg--;
                break;
            case ADDSUB:
            case XOR:
            case OR:
            case AND:
            case INCDEC:
                lv = evaluateTree(root->left);
                rv = evaluateTree(root->right);
                if (strcmp(root->lexeme, "+") == 0) {
                    retval = lv + rv;
                    printf("ADD r%d r%d\n", (reg%8), (reg+1)%8);
                } else if (strcmp(root->lexeme, "-") == 0) {
                    retval = lv - rv;
                    printf("SUB r%d r%d\n", reg%8 ,(reg+1)%8);
                }
                else if (strcmp(root->lexeme, "++") == 0){
                    retval = lv + rv;
                    setval(root->left->lexeme, retval, &idx);
                    printf("ADD r%d r%d\n", (reg%8), (reg+1)%8);
                    printf("MOV [%d] r%d\n", idx*4, reg%8);
                }
                else if(strcmp(root->lexeme, "--") == 0){
                    retval = lv - rv;
                    setval(root->left->lexeme, retval, &idx);
                    printf("SUB r%d r%d\n", (reg%8), (reg+1)%8);
                    printf("MOV [%d] r%d\n", idx*4, reg%8);
                }
                else if(strcmp(root->lexeme, "^") == 0){
                    retval = lv ^ rv;
                    printf("XOR r%d r%d\n", (reg%8), (reg+1)%8);
                }
                else if(strcmp(root->lexeme, "|") == 0){
                    retval = lv | rv;
                    printf("OR r%d r%d\n", (reg%8), (reg+1)%8);
                }
                else if(strcmp(root->lexeme, "&") == 0){
                    retval = lv & rv;
                    printf("AND r%d r%d\n", (reg%8), (reg+1)%8);
                }
                if(totReg > 8){
                    sbcount--;
                    totReg--;
                    printf("MOV r%d [%d]\n", totReg%8,sbcount*4);
                }
                else{
                    totReg--;
                }
                //totReg--;
                //reg--;
                break;
            default:
                retval = 0;
        }
    }
    return retval;
}

void printPrefix(BTNode *root) {
    if (root != NULL) {
        printf("%s ", root->lexeme);
        printPrefix(root->left);
        printPrefix(root->right);
    }
}


/*============================================================================================
main
============================================================================================*/

// This package is a calculator
// It works like a Python interpretor
// Example:
// >> y = 2
// >> z = 2
// >> x = 3 * y + 4 / (2 * z)
// It will print the answer of every line
// You should turn it into an expression compiler
// And print the assembly code according to the input

// This is the grammar used in this package
// You can modify it according to the spec and the slide
// statement  :=  ENDFILE | END | expr END
// expr    	  :=  term expr_tail
// expr_tail  :=  ADDSUB term expr_tail | NiL
// term 	  :=  factor term_tail
// term_tail  :=  MULDIV factor term_tail| NiL
// factor	  :=  INT | ADDSUB INT |
//		   	      ID  | ADDSUB ID  |
//		   	      ID ASSIGN expr |
//		   	      LPAREN expr RPAREN |
//		   	      ADDSUB LPAREN expr RPAREN

int main() {
    initTable();
    if(PRINTERR) printf(">> ");
    while (1) {
        statement();
    }
    return 0;
}

load r0 [0]
add r1 0 5
add r1 r0 r1
load r2 [4]
sub r1 r1 r2
load r3 [8]
mul r1 r1 r3
div r1 r1 r0
rem r1 r1 r2
add r1 r1 r3
sub r1 r1 r0
mul r1 r1 r2
div r1 r1 r3
rem r1 r1 r0
add r1 r1 r2
sub r1 r1 r3
mul r1 r1 r0
div r1 r1 r2
rem r1 r1 r3
store [4] r1


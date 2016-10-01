#ifndef structs_h
#define structs_h

typedef struct idStructExpression {
    struct value *value;
} idStructExpression;

// --------------------------------

typedef union factor {
    union value *value;
    union assExpression *assExp;
} factor;

typedef union multdivExp {
    union multdivExp *mdExp;
    union factor *factor;
} multdivExp;

typedef union term {
    union multdivExp *mdExp;
    union factor *factor;
} term;

typedef struct plusminusExp {
    union assExpression *assExp;
    union term *term;
} plusminusExp;

typedef union assExpression {
    struct plusminusExp *pmExp;
    union term *term;
} assExpression;

// --------------------------------

typedef union block {
    struct statement *stm;
    struct statements *stms;
} block;

typedef struct compare_expression {
    struct value *value1;
    struct value *value2;
} compare_expression;

typedef struct whileOp {
    struct compare_expression *compExp;
    struct block *whileBlock;
} whileOp;

typedef struct ifWithElse {
    struct compare_expression *compExp;
    struct block *ifBlock;
    struct block *elseBlock;
} ifWithElse;

typedef struct ifNoElse {
    struct compare_expression *compExp;
    struct block *ifBlock;
} ifNoElse;

// --------------------------------

typedef union value {
    int i;
    float f;
    char c;
    char *s;
    // FALTA FAZER UMA FILA E BOTAR O TIPO DELA AQUI
} value;

typedef union valsVal {
    struct values *values;
    struct value *value;
} valsVal;

typedef union values {
    struct valsVal *valsVal;
    struct value *value;
} values;

// --------------------------------

typedef struct funcCall {
    struct values *params;
} funcCall;

typedef struct definition {
    struct argument *arg;
} definition;

typedef union statement {
    struct definition *def;
    struct funcCall *funcCall;
    struct ifNoElse *ifNoElse;
    struct ifWithElse *ifWithElse;
    struct whileOp *whileOp;
    struct assExpression *assExp;
    struct idStructExpression *idStrExp;
} statement;

typedef struct statements {
    struct statements *stms;
    union statement *stm;
} statements;

// --------------------------------

typedef struct argsArg {
    union arguments *args;
    struct argument *arg;
} argsArg;

typedef union arguments {
    struct argsArg *argargs;
    struct argument *arg;
} arguments;

typedef union type {
    char *type; // "int" ou QUEUE<int>
} type;
typedef struct argument {
    struct type *type;
} argument;

// --------------------------------

typedef struct progFunc {
    union program *prog;
    struct function *func;
} progFunc;

typedef struct function {
    struct argument *arg;
    union arguments *args;
    struct statements *stms; // --
    struct value *v;
} function;

typedef union program { // OK
    struct progFunc *pf;
    struct function *func;
} program;

#endif /* structs_h */
#ifndef structs_h
#define structs_h

// ---------------------------------------------------------------
// ---------------------------- STRUCTS --------------------------
// ---------------------------------------------------------------

typedef struct idStructExpression {
    union value *value;
} idStructExpression;

// --------------------------------

typedef union factor {
    union value *value;
    union assExpression *assExp;
} factor;

typedef struct multdivExp {
    union term *term;
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
    union statement *stm;
    struct statements *stms;
} block;

typedef struct whileOp {
    union value *value1;
    union value *value2;
    union block *whileBlock;
} whileOp;

typedef struct ifWithElse {
    union value *value1;
    union value *value2;
    union block *ifBlock;
    union block *elseBlock;
} ifWithElse;

typedef struct ifNoElse {
    union value *value1;
    union value *value2;
    union block *ifBlock;
} ifNoElse;

// --------------------------------

typedef union value {
    int i;
    float f;
    char c;
    char *s;
    // FALTA FAZER UMA FILA E BOTAR O TIPO DELA AQUI
} value;

typedef struct valsVal {
    union values *values;
    union value *value;
} valsVal;

typedef union values {
    union valsVal *valsVal;
    union value *value;
} values;

// --------------------------------

typedef struct funcCall {
    union values *params;
} funcCall;

typedef union statement {
    char *type;
    struct funcCall *funcCall;
    struct ifNoElse *ifNoElse;
    struct ifWithElse *ifWithElse;
    struct whileOp *whileOp;
    union assExpression *assExp;
    struct idStructExpression *idStrExp;
} statement;

typedef struct statements {
    struct statements *stms;
    union statement *stm;
} statements;

// --------------------------------

typedef struct argsArg {
    union arguments *args;
    char *typeArg;
} argsArg;

typedef union arguments {
    struct argsArg *argargs;
    char *typeArg;
} arguments;

// --------------------------------

typedef struct progFunc {
    union program *prog;
    struct function *func;
} progFunc;

typedef struct function {
    char *typeReturn;
    union arguments *args;
    struct statements *stms;
    union value *v;
} function;

typedef union program {
    struct progFunc *pf;
    struct function *func;
} program;

// ---------------------------------------------------------------
// ---------------------------- FUNÇÕES --------------------------
// ---------------------------------------------------------------

idStructExpression *new_idStructExpression() { // STRUCT
    idStructExpression *idStrExp = (idStructExpression*) malloc(sizeof(idStructExpression));
    value *v = (value*) malloc(sizeof(value));
    
    //idStrExp->v
    return idStrExp;
}

factor *new_factor() { // UNION
    factor *f = (factor*) malloc(sizeof(factor));
    // IF
    assExpression *assExp = (assExpression*) malloc(sizeof(assExpression));
    
    // ELSE
    value *v = (value*) malloc(sizeof(value));
    return f;
}

multdivExp *new_multdivExp() { // STRUCT
    multdivExp *mdExp = (multdivExp*) malloc(sizeof(multdivExp));
    term *t = (term*) malloc(sizeof(term));
    factor *f = (factor*) malloc(sizeof(factor));
    return mdExp;
}

term *new_term() { // UNION
    term *t = (term*) malloc(sizeof(term));
    // IF
    multdivExp *mdExp = (multdivExp*) malloc(sizeof(multdivExp));
    // ELSE
    factor *f = (factor*) malloc(sizeof(factor));
    return t;
}

plusminusExp *new_plusminusExp() { // STRUCT
    plusminusExp *pmExp = (plusminusExp*) malloc(sizeof(plusminusExp));
    assExpression *assExp = (assExpression*) malloc(sizeof(assExpression));
    term *t = (term*) malloc(sizeof(term));
    return pmExp;
}

assExpression *new_assExpression() { // UNION
    assExpression *p = (assExpression*) malloc(sizeof(assExpression));
    // IF
    plusminusExp *pmExp = (plusminusExp*) malloc(sizeof(plusminusExp));
    // ELSE
    term *t = (term*) malloc(sizeof(term));
    return p;
}

block *new_block() { // UNION
    block *bl = (block*) malloc(sizeof(block));
    // IF
    statement *stmt = (statement*) malloc(sizeof(statement));
    // ELSE
    statements *stmts = (statements*) malloc(sizeof(statements));
    return bl;
}

whileOp *new_whileOp() { // STRUCT
    whileOp *wh = (whileOp*) malloc(sizeof(whileOp));
    value *v1 = (value*) malloc(sizeof(value));
    value *v2 = (value*) malloc(sizeof(value));
    block *bl = (block*) malloc(sizeof(block));
    return wh;
}

ifWithElse *new_ifWithElse() { // STRUCT
    ifWithElse *ifElse = (ifWithElse*) malloc(sizeof(ifWithElse));
    value *v1 = (value*) malloc(sizeof(value));
    value *v2 = (value*) malloc(sizeof(value));
    block *blIf = (block*) malloc(sizeof(block));
    block *blElse = (block*) malloc(sizeof(block));
    return ifElse;
}

ifNoElse *new_ifNoElse() { // STRUCT 
    ifNoElse *ifNElse = (ifNoElse*) malloc(sizeof(ifNoElse));
    value *v1 = (value*) malloc(sizeof(value));
    value *v2 = (value*) malloc(sizeof(value));
    block *blIf = (block*) malloc(sizeof(block));
    return ifNElse;
}

value *new_value() { // UNION
    value *val = (value*) malloc(sizeof(value));
    // IF
    int inteiro;
    // ELSE IF
    float real;
    // ELSE IF
    char caractere;
    // ELSE
    char *str;
    return val;
}

valsVal *new_valsVal() { // STRUCT
    valsVal *vsv = (valsVal*) malloc(sizeof(valsVal));
    values *vals = (values*) malloc(sizeof(values));
    value *val = (value*) malloc(sizeof(value));
    return vsv;
}

values *new_values() { // UNION
    values *vals = (values*) malloc(sizeof(values));
    // IF
    valsVal *vsv = (valsVal*) malloc(sizeof(valsVal));
    // ELSE
    value *val = (value*) malloc(sizeof(value));
    return vals;
}

funcCall *new_funcCall() { // STRUCT
    funcCall *fC = (funcCall*) malloc(sizeof(funcCall));
    values *vals = (values*) malloc(sizeof(values));
    return fC;
}

statement *new_statement() {
    statement *p = (statement*) malloc(sizeof(statement));
    
    return p;
}

statements *new_statements() {
    statements *p = (statements*) malloc(sizeof(statements));
    
    return p;
}

argsArg *new_argsArg() {
    argsArg *p = (argsArg*) malloc(sizeof(argsArg));
    
    return p;
}

arguments *new_arguments() {
    arguments *p = (arguments*) malloc(sizeof(arguments));
    
    return p;
}

progFunc *new_progFunc() {
    progFunc *p = (progFunc*) malloc(sizeof(progFunc));
    
    return p;
}

function *new_function() {
    function *p = (function*) malloc(sizeof(function));
    
    return p;
}

program *new_program() {
    program *p = (program*) malloc(sizeof(program));
    
    return p;
}


#endif /* structs_h */
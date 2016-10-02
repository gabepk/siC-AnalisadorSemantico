#ifndef structs_h
#define structs_h

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

// ---------------------------------------------------------------
// ---------------------------- STRUCTS --------------------------
// ---------------------------------------------------------------

typedef struct idStructExpression {
    union value *value;
} idStructExpression;

// --------------------------------

typedef union factor {
    union value *value;
    struct assExpression *assExp;
} factor;

typedef struct term {
    struct term *term;
    char op;
    union factor *factor;
} term;

typedef struct assExpression {
    struct assExpression *assExp;
    char op;
    struct term *term;
} assExpression;

// --------------------------------

typedef union block {
    union statement *stmt;
    struct statements *stmts;
} block;

typedef struct cmpExpression {
    char *compare;
} cmpExpression;

typedef struct whileOp {
    union value *value1;
    char *compare;
    union value *value2;
    union block *whileBlock;
} whileOp;

typedef struct ifWithElse {
    union value *value1;
    char *compare;
    union value *value2;
    union block *ifBlock;
    union block *elseBlock;
} ifWithElse;

typedef struct ifNoElse {
    union value *value1;
    char *compare;
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

typedef union values {
    struct values *values;
    union value *value;
} values;

// --------------------------------

typedef struct funcCall {
    union values *params;
    char *nomeFunc;
} funcCall;

typedef struct definition {
    union typeStr *type;
    char *var;
} funcCall;

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
    struct statements *stmts;
    union statement *stmt;
} statements;

// --------------------------------

typedef struct arguments {
    struct arguments *arguments;
    struct typeStr *typeArg;
    char *argNome;
} arguments;

typedef struct typeQueue {
    struct typeSimple *typeS;
} typeQueue;

typedef struct typeSimple {
    char *typeS; // void, int, char, float;
} typeSimple;


typedef union typeStr {
    struct typeSimple *typeS;
    struct typeQueue *typeQ;    
} typeStr;

typedef struct function {
    struct typeStr *typeReturn;
    char *nomeFunc;
    struct arguments *args;
    struct statements *stmts;
    union value *v;
} function;

typedef union program {
    struct program *prog;
    struct function *func;
} program;

// ---------------------------------------------------------------
// ---------------------------- FUNÇÕES --------------------------
// ---------------------------------------------------------------

idStructExpression *new_idStructExpression() { // STRUCT
    idStructExpression *idStrExp = (idStructExpression*) malloc(sizeof(idStructExpression));
    
    
    //idStrExp->v
    return idStrExp;
}

factor *new_factor(int tag, value *value, assExpression *assExp) { // UNION
    factor *f = (factor*) malloc(sizeof(factor));
    f->value = value;
    f->assExp = assExp;
    return f;
}

term *new_term(term *term, char op, factor *factor) { // STRUCT
    term *t = (term*) malloc(sizeof(term));
    t->term = term;
    t->op = op;
    t->factor = factor;
    return t;
}

assExpression *new_assExpression(int tag, assExpression *assExp, char op, term *term) { // STRUCT
    assExpression *ae = (assExpression*) malloc(sizeof(assExpression));
    ae->assExp = assExp;
    ae->op = op;
    ae->term = term;
    return ae;
}

cmpExpression *new_cmpExpression(char *compare) { // STRUCT
    cmpExpression *cmp = (cmpExpression*) malloc(sizeof(cmpExpression));
    cmp->compare = compare;
    return cmp;
}

block *new_block(int tag, statement *stmt, statements *stmts) { // UNION
    block *bl = (block*) malloc(sizeof(block));
    bl->stmt = stmt;
    bl->stmts = stmts;
    return bl;
}

whileOp *new_whileOp(value *value1, char *compare, value *value2, block *whileBlock) { // STRUCT
    whileOp *wh = (whileOp*) malloc(sizeof(whileOp));
    wh->value1 = value1;
    wh->compare = compare;
    wh->value2 = value2;
    wh->whileBlock = whileBlock;
    return wh;
}

ifWithElse *new_ifWithElse(value *value1, char *compare, value *value2, block *ifBlock, block *elseBlock) { // STRUCT
    ifWithElse *ifElse = (ifWithElse*) malloc(sizeof(ifWithElse));
    ifElse->value1 = value1;
    ifElse->compare = compare;
    ifElse->value2 = value2;
    ifElse->ifBlock = ifBlock;
    ifElse->elseBlock = elseBlock;
    return ifElse;
}

ifNoElse *new_ifNoElse(value *value1, char *compare, value *value2, block *ifBlock) { // STRUCT 
    ifNoElse *ifNElse = (ifNoElse*) malloc(sizeof(ifNoElse));
    ifNElse->value1 = value1;
    ifNElse->compare = compare;
    ifNElse->value2 = value2;
    ifNElse->ifBlock = ifBlock;
    return ifNElse;
}

value *new_value(int tag, int i, float f, char c, char *s) { // UNION - FALTA TIPO FILA !!!!!!!!
    value *val = (value*) malloc(sizeof(value));
    val->i = i;
    val->f = f;
    val->c = c;
    val->s = s;
    return val;
}

values *new_values(int tag, values *values, value *value) { // UNION
    values *vals = (values*) malloc(sizeof(values));
    vals->values = values;
    vals->value = value;
    return vals;
}

funcCall *new_funcCall(char *nomeFunc, values *params) { // STRUCT
    funcCall *fc = (funcCall*) malloc(sizeof(funcCall));
    fc->nomeFunc = nomeFunc;
    fc->params = params;
    return fc;
}

definition *new_definition(typeStr *type, char *var) {
    definition *def = (definition*) malloc(sizeof(definition));
    def->type = type;
    def->var = var;
    return def;
}

statement *new_statement(int tag, definition *def, funcCall *funcCall, ifNoElse *ifNoElse, ifWithElse *ifWithElse, whileOp *whileOp, assExpression *assExp, idStructExpression *idStrExp) { // UNION
    statement *stmt = (statement*) malloc(sizeof(statement));
    stmt->def = def;
    stmt->funcCall = funcCall;
    stmt->ifNoElse = ifNoElse;
    stmt->ifWithElse = ifWithElse;
    stmt->whileOp = whileOp;
    stmt->assExp = assExp;
    stmt->idStrExp = idStrExp;
    return stmt;
}

statements *new_statements(statements *stmts_left, statement *stmt) { // STRUCT
    statements *stmts = (statements*) malloc(sizeof(statements));
    stmts->stmts = stmts_left;
    stmts->stmt = stmt;
    return stmts;
}

arguments *new_arguments(int tag, arguments *arguments, typeStr *typeArg, char *argNome) { // UNION
    arguments *args = (arguments*) malloc(sizeof(arguments));
    args->arguments = arguments;
    args->typeArg = typeArg;
    args->argNome = argNome;
    return args;
}

typeQueue *new_typeQueue(char *typeS) {
    typeQueue *typeQ = (typeQueue*) malloc(sizeof(typeQueue));
    typeQ->typeS = typeS;
    return typeQ;
}

typeSimple *new_typeSimple(char *type) {
    typeSimple *typeSmp = (typeSimple*) malloc(sizeof(typeSimple));
    typeSmp->type = type;
    return typeSmp;
}

typeStr *new_typeStr(int tag, typeSimple *typeS, typeQueue *typeQ) { // UNION
    typeStr *typeStr = (typeStr*) malloc(sizeof(typeStr));
    typeStr->typeS = typeS;
    typeStr->typeQ = typeQ;
    return typeStr;
}

function *new_function(typeStr *typeReturn, char *nomeFunc, arguments *args, statements *stmts, value *v) { // STRUCT
    function *func = (function*) malloc(sizeof(function));
    func->typeReturn = typeReturn;
    func->nomeFunc = nomeFunc;
    func->args = args;
    func->stmts = stmts;
    func->v = v;
    return func;
}

program *new_program(int tag, program *prog, function *func) { // UNION
    program *p = (program*) malloc(sizeof(program));
    p->prog = prog;
    p->func = func;
    return p;
}


#endif /* structs_h */
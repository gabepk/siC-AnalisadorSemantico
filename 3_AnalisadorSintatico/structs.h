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
    union assExpression *assExp;
} factor;

typedef struct multdivExp {
    union term *term;
    union factor *factor;
} multdivExp;

typedef union term {
    struct multdivExp *mdExp;
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
    union statement *stmt;
    struct statements *stmts;
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
    struct valsVal *valsVal;
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
    struct statements *stmts;
    union statement *stmt;
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
    struct statements *stmts;
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
    
    
    //idStrExp->v
    return idStrExp;
}

factor *new_factor(int tag, value *value, assExpression *assExp) { // UNION
    factor *f = (factor*) malloc(sizeof(factor));
    //if (tag == 1) {
    f->value = value;
    f->assExp = assExp;
    //}
    
    return f;
}

multdivExp *new_multdivExp(term *term, factor *factor) { // STRUCT
    multdivExp *mdExp = (multdivExp*) malloc(sizeof(multdivExp));
    mdExp->term = term;
    mdExp->factor = factor;
    return mdExp;
}

term *new_term(int tag, multdivExp *mdExp, factor *factor) { // UNION
    term *t = (term*) malloc(sizeof(term));
    t->mdExp = mdExp;
    t->factor = factor;
    return t;
}

plusminusExp *new_plusminusExp(assExpression *assExp, term *term) { // STRUCT
    plusminusExp *pmExp = (plusminusExp*) malloc(sizeof(plusminusExp));
    pmExp->assExp = assExp;
    pmExp->term = term;
    return pmExp;
}

assExpression *new_assExpression(int tag, plusminusExp *pmExp, term *term) { // UNION
    assExpression *p = (assExpression*) malloc(sizeof(assExpression));
    p->pmExp = pmExp;
    p->term = term;
    return p;
}

block *new_block(int tag, statement *stmt, statements *stmts) { // UNION
    block *bl = (block*) malloc(sizeof(block));
    bl->stmt = stmt;
    bl->stmts = stmts;
    return bl;
}

whileOp *new_whileOp(value *value1, value *value2, block *whileBlock) { // STRUCT
    whileOp *wh = (whileOp*) malloc(sizeof(whileOp));
    wh->value1 = value1;
    wh->value2 = value2;
    wh->whileBlock = whileBlock;
    return wh;
}

ifWithElse *new_ifWithElse(value *value1, value *value2, block *ifBlock, block *elseBlock) { // STRUCT
    ifWithElse *ifElse = (ifWithElse*) malloc(sizeof(ifWithElse));
    ifElse->value1 = value1;
    ifElse->value2 = value2;
    ifElse->ifBlock = ifBlock;
    ifElse->elseBlock = elseBlock;
    return ifElse;
}

ifNoElse *new_ifNoElse(value *value1, value *value2, block *ifBlock) { // STRUCT 
    ifNoElse *ifNElse = (ifNoElse*) malloc(sizeof(ifNoElse));
    ifNElse->value1 = value1;
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

valsVal *new_valsVal(values *values, value *value) { // STRUCT
    valsVal *vsv = (valsVal*) malloc(sizeof(valsVal));
    vsv->values = values;
    vsv->value = value;
    return vsv;
}

values *new_values(int tag, valsVal *valsVal, value *value) { // UNION
    values *vals = (values*) malloc(sizeof(values));
    vals->valsVal = valsVal;
    vals->value = value;
    return vals;
}

funcCall *new_funcCall(values *params) { // STRUCT
    funcCall *fC = (funcCall*) malloc(sizeof(funcCall));
    fC->params = params;
    return fC;
}

statement *new_statement(int tag, char *type, funcCall *funcCall, ifNoElse *ifNoElse, ifWithElse *ifWithElse, whileOp *whileOp, assExpression *assExp, idStructExpression *idStrExp) { // UNION
    statement *stmt = (statement*) malloc(sizeof(statement));
    stmt->type = type;
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

argsArg *new_argsArg(arguments *args, char *typeArg) { // STRUCT
    argsArg *asa = (argsArg*) malloc(sizeof(argsArg));
    asa->args = args;
    asa->typeArg = typeArg;
    return asa;
}

arguments *new_arguments(int tag, argsArg *argargs, char *typeArg) { // UNION
    arguments *args = (arguments*) malloc(sizeof(arguments));
    args->argargs = argargs;
    args->typeArg = typeArg;
    return args;
}

progFunc *new_progFunc(program *prog, function *func) { // STRUCT
    progFunc *pf = (progFunc*) malloc(sizeof(progFunc));
    pf->prog = prog;
    pf->func = func;
    return pf;
}

function *new_function(char *typeReturn, arguments *args, statements *stmts, value *v) { // STRUCT
    function *func = (function*) malloc(sizeof(function));
    func->typeReturn = typeReturn;
    func->args = args;
    func->stmts = stmts;
    func->v = v;
    return func;
}

program *new_program(int tag, progFunc *pf, function *func) { // UNION
    program *p = (program*) malloc(sizeof(program));
    p->pf = pf;
    p->func = func;
    return p;
}


#endif /* structs_h */
#ifndef structs_h
#define structs_h

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

// ---------------------------------------------------------------
// ---------------------------- STRUCTS --------------------------
// ---------------------------------------------------------------

typedef union allRules {
    union program *program; // 1
    struct function *func; // 2 
    union typeStr *tst; // 3
    struct typeSimple *tsp; // 4
    struct arguments *args; // 5
    struct statements *stmts; // 6
    union statement *stmt; // 7
    struct definition *def; // 8
    struct funcCall *fc; // 9
    struct values *vals; // 10
    union value *val; // 11
    struct ifNoElse *ife; // 12
    struct ifWithElse *iwe; // 13
    struct whileOp *wh; // 14
    union block *bl; // 15
    struct cmpExpression *cmpExp; // 16
    struct assignment *assmnt; // 17
    struct assExpression *assExp; // 18
    struct term *term; // 19
    union factor *factor; // 200
    int tag;
} allRules;

// --------------------------------

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

typedef struct assignment {
    char *var;
    assExpression *assExp;
} assignment;

// --------------------------------

typedef union block {
    union statement *stmt;
    struct statements *stmts;
} block;

typedef struct cmpExpression {
    char *comp;
} cmpExpression;

typedef struct whileOp {
    union value *value1;
    struct cmpExpression *compare;
    union value *value2;
    union block *whileBlock;
} whileOp;

typedef struct ifWithElse {
    union value *value1;
    struct cmpExpression *compare;
    union value *value2;
    union block *ifBlock;
    union block *elseBlock;
} ifWithElse;

typedef struct ifNoElse {
    union value *value1;
    struct cmpExpression *compare;
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

typedef struct values {
    struct values *values;
    union value *value;
} values;

// --------------------------------

typedef struct funcCall {
    struct values *params;
    char *nomeFunc;
} funcCall;

typedef struct definition {
    union typeStr *type;
    char *var;
} definition;

typedef union statement {
    struct definition *def;
    struct funcCall *funcCall;
    struct ifNoElse *ifNoElse;
    struct ifWithElse *ifWithElse;
    struct whileOp *whileOp;
    struct assignment *assmnt;
    struct idStructExpression *idStrExp;
} statement;

typedef struct statements {
    struct statements *stmts;
    union statement *stmt;
} statements;

// --------------------------------

typedef struct arguments {
    struct arguments *arguments;
    union typeStr *typeArg;
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
    union typeStr *typeReturn;
    char *nomeFunc;
    struct arguments *args;
    struct statements *stmts;
    union value *v;
} function;

typedef union program {
    union program *prog;
    struct function *func;
} program;

// ---------------------------------------------------------------
// ---------------------------- FUNÇÕES NEW ----------------------
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
    
    allRules *ar = (allRules*) malloc(sizeof(allRules));
    ar->factor = f;
    ar->tag = 20;
    return f;
}

term *new_term(term *newTerm, char op, factor *factor) { // STRUCT
    term *t = (term*) malloc(sizeof(term));
    t->term = newTerm;
    t->op = op;
    t->factor = factor;
    
    allRules *ar = (allRules*) malloc(sizeof(allRules));
    ar->term = t;
    ar->tag = 19;
    return t;
}

assExpression *new_assExpression (assExpression *assExp, char op, term *term) { // STRUCT
    assExpression *ae = (assExpression*) malloc(sizeof(assExpression));
    ae->assExp = assExp;
    ae->op = op;
    ae->term = term;
    
    allRules *ar = (allRules*) malloc(sizeof(allRules));
    ar->assExp = ae;
    ar->tag = 18;
    return ae;
}

assignment *new_assignment (char *var, assExpression *assExp) { // STRUCT
    assignment *assmnt = (assignment*) malloc(sizeof(assignment));
    assmnt->var = var;
    assmnt->assExp = assExp;
    
    allRules *ar = (allRules*) malloc(sizeof(allRules));
    ar->assmnt = assmnt;
    ar->tag = 17;
    return assmnt;
}

cmpExpression *new_cmpExpression(char *cm) { // STRUCT
    cmpExpression *compare = (cmpExpression*) malloc(sizeof(cmpExpression));
    compare->comp = cm;
    
    allRules *ar = (allRules*) malloc(sizeof(allRules));
    ar->cmpExp = compare;
    ar->tag = 16;
    return compare;
}

block *new_block(int tag, statement *stmt, statements *stmts) { // UNION
    block *bl = (block*) malloc(sizeof(block));
    bl->stmt = stmt;
    bl->stmts = stmts;
    
    allRules *ar = (allRules*) malloc(sizeof(allRules));
    ar->bl = bl;
    ar->tag = 15;
    return bl;
}

whileOp *new_whileOp(value *value1, cmpExpression *compare, value *value2, block *whileBlock) { // STRUCT
    whileOp *wh = (whileOp*) malloc(sizeof(whileOp));
    wh->value1 = value1;
    wh->compare = compare;
    wh->value2 = value2;
    wh->whileBlock = whileBlock;
    
    allRules *ar = (allRules*) malloc(sizeof(allRules));
    ar->wh = wh;
    ar->tag = 14;
    return wh;
}

ifWithElse *new_ifWithElse(value *value1, cmpExpression *compare, value *value2, block *ifBlock, block *elseBlock) { // STRUCT
    ifWithElse *ifElse = (ifWithElse*) malloc(sizeof(ifWithElse));
    ifElse->value1 = value1;
    ifElse->compare = compare;
    ifElse->value2 = value2;
    ifElse->ifBlock = ifBlock;
    ifElse->elseBlock = elseBlock;
    
    allRules *ar = (allRules*) malloc(sizeof(allRules));
    ar->iwe = ifElse;
    ar->tag = 13;
    return ifElse;
}

ifNoElse *new_ifNoElse(value *value1, cmpExpression *compare, value *value2, block *ifBlock) { // STRUCT 
    ifNoElse *ifNElse = (ifNoElse*) malloc(sizeof(ifNoElse));
    ifNElse->value1 = value1;
    ifNElse->compare = compare;
    ifNElse->value2 = value2;
    ifNElse->ifBlock = ifBlock;
    
    allRules *ar = (allRules*) malloc(sizeof(allRules));
    ar->ife = ifNElse;
    ar->tag = 12;
    return ifNElse;
}

value *new_value(int tag, int i, float f, char c, char *s) { // UNION - FALTA TIPO FILA !!!!!!!!
    value *val = (value*) malloc(sizeof(value));
    val->i = i;
    val->f = f;
    val->c = c;
    val->s = s;
    
    allRules *ar = (allRules*) malloc(sizeof(allRules));
    ar->val = val;
    ar->tag = 11;
    return val;
}

values *new_values(int tag, values *newValues, value *value) { // UNION
    values *vals = (values*) malloc(sizeof(values));
    vals->values = newValues;
    vals->value = value;
    
    allRules *ar = (allRules*) malloc(sizeof(allRules));
    ar->vals = vals;
    ar->tag = 10;
    return vals;
}

funcCall *new_funcCall(char *nomeFunc, values *params) { // STRUCT
    funcCall *fc = (funcCall*) malloc(sizeof(funcCall));
    fc->nomeFunc = nomeFunc;
    fc->params = params;
    
    allRules *ar = (allRules*) malloc(sizeof(allRules));
    ar->fc = fc;
    ar->tag = 9;
    return fc;
}

definition *new_definition(typeStr *type, char *var) {
    definition *def = (definition*) malloc(sizeof(definition));
    def->type = type;
    def->var = var;
    
    allRules *ar = (allRules*) malloc(sizeof(allRules));
    ar->def = def;
    ar->tag = 8;
    return def;
}

statement *new_statement(int tag, definition *def, funcCall *funcCall, ifNoElse *ifNoElse, ifWithElse *ifWithElse, whileOp *whileOp, assignment *assmnt, idStructExpression *idStrExp) { // UNION
    statement *stmt = (statement*) malloc(sizeof(statement));
    stmt->def = def;
    stmt->funcCall = funcCall;
    stmt->ifNoElse = ifNoElse;
    stmt->ifWithElse = ifWithElse;
    stmt->whileOp = whileOp;
    stmt->assmnt = assmnt;
    stmt->idStrExp = idStrExp;
    
    allRules *ar = (allRules*) malloc(sizeof(allRules));
    ar->stmt = stmt;
    ar->tag = 7;
    return stmt;
}

statements *new_statements(statements *stmts_left, statement *stmt) { // STRUCT
    statements *stmts = (statements*) malloc(sizeof(statements));
    stmts->stmts = stmts_left;
    stmts->stmt = stmt;
    
    allRules *ar = (allRules*) malloc(sizeof(allRules));
    ar->stmts = stmts;
    ar->tag = 6;
    return stmts;
}

arguments *new_arguments(int tag, arguments *newArguments, typeStr *typeArg, char *argNome) { // UNION
    arguments *args = (arguments*) malloc(sizeof(arguments));
    args->arguments = newArguments;
    args->typeArg = typeArg;
    args->argNome = argNome;
    
    allRules *ar = (allRules*) malloc(sizeof(allRules));
    ar->args = args;
    ar->tag = 5;
    return args;
}

typeQueue *new_typeQueue(typeSimple *tS) {
    typeQueue *typeQ = (typeQueue*) malloc(sizeof(typeQueue));
    typeQ->typeS = tS;
    
    //allRules *ar = (allRules*) malloc(sizeof(allRules));
    //ar->factor = f;
    //ar->tag = 19;
    return typeQ;
}

typeSimple *new_typeSimple(char *type) {
    typeSimple *typeSmp = (typeSimple*) malloc(sizeof(typeSimple));
    typeSmp->typeS = type;
    
    allRules *ar = (allRules*) malloc(sizeof(allRules));
    ar->tsp = typeSmp;
    ar->tag = 4;
    return typeSmp;
}

typeStr *new_typeStr(int tag, typeSimple *tS, typeQueue *tQ) { // UNION
    typeStr *tStr = (typeStr*) malloc(sizeof(typeStr));
    tStr->typeS = tS;
    tStr->typeQ = tQ;
    
    allRules *ar = (allRules*) malloc(sizeof(allRules));
    ar->tst = tStr;
    ar->tag = 3;
    return tStr;
}

function *new_function(typeStr *typeReturn, char *nomeFunc, arguments *args, statements *stmts, value *v) { // STRUCT
    function *func = (function*) malloc(sizeof(function));
    func->typeReturn = typeReturn;
    func->nomeFunc = nomeFunc;
    func->args = args;
    func->stmts = stmts;
    func->v = v;
    
    allRules *ar = (allRules*) malloc(sizeof(allRules));
    ar->func = func;
    ar->tag = 2;
    return func;
}

program *new_program(int tag, program *prog, function *func) { // UNION
    program *p = (program*) malloc(sizeof(program));
    p->prog = prog;
    p->func = func;
    
    allRules *ar = (allRules*) malloc(sizeof(allRules));
    ar->program = p;
    ar->tag = 1;
    return p;
}


// ---------------------------------------------------
// ---------------------------------------------------
// ---------------------------------------------------

/*
void show_tree(program *root, int tabs) {
	int i;
	for (i = 0; i < tabs; ++i) printf("  ");
	switch (root->tag) {
            case (1):
                printf("program\n");
                break;
            case (2):
                printf("function\n");
                break;
            case (3):
                printf("typeStr\n");
                break;
            case (4):
                printf("typeSimple\n");
                break;
            case (5):
                printf("arguments\n");
                break;
            case (6):
                printf("statements\n");
                break;
            case (7):
                printf("statement\n");
                break;
            case (8):
                printf("definition\n");
                break;
            case (9):
                printf("funcCall\n");
                break;
            case (10):
                printf("values\n");
                break;
            case (11):
                printf("value\n");
                break;
            case (12):
                printf("ifNoElse\n");
                break;
            case (13):
                printf("ifWithElse\n");
                break;
            case (14):
                printf("whileOp\n");
                break;
            case (15):
                printf("block\n");
                break;
            case (16):
                printf("cmpExpression\n");
                break;
            case (17):
                printf("assignment\n");
                break;
            case (18):
                printf("assExpression\n");
                break;
            case (19):
                printf("term\n");
                break;
            case (20):
                printf("factor\n");
                break;
            
	}
}
*/

#endif /* structs_h */
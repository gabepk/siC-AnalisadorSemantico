#ifndef structs_h
#define structs_h

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

// ---------------------------------------------------------------
// ---------------------------- STRUCTS --------------------------
// ---------------------------------------------------------------

typedef union rule {
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
} rule;

// --------------------------------

    
typedef struct idStructExpression {
    union value *value;
} idStructExpression;


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
// ------------------------ FUNÇÃO ALLRULES ---------------------
// ---------------------------------------------------------------

rule *new_rule(int tag, void *regra) {
    rule *r = (rule*) malloc(sizeof(rule));
    switch (tag) {
            case (1):
                r->program = (program *) regra;
                r->tag = 1;
                break;
            case (2):
                r->func = (function *) regra;
                r->tag = 2;
                break;
            case (3):
                r->tst = (typeStr *) regra;
                r->tag = 3;
                break;
            case (4):
                r->tsp = (typeSimple *) regra;
                r->tag = 4;
                break;
            case (5):
                r->args = (arguments *)regra;
                r->tag = 5;
                break;
            case (6):
                r->stmts = (statements *) regra;
                r->tag = 6;
                break;
            case (7):
                r->stmt = (statement *) regra;
                r->tag = 7;
                break;
            case (8):
                r->def = (definition *)regra;
                r->tag = 8;
                break;
            case (9):
                r->fc = (funcCall *)regra;
                r->tag = 9;
                break;
            case (10):
                r->vals = (values *) regra;
                r->tag = 10;
                break;
            case (11):
                r->val = (value *) regra;
                r->tag = 11;
                break;
            case (12):
                r->ife = (ifNoElse *) regra;
                r->tag = 12;
                break;
            case (13):
                r->iwe = (ifWithElse *) regra;
                r->tag = 13;
                break;
            case (14):
                r->wh = (whileOp *) regra;
                r->tag = 14;
                break;
            case (15):
                r->bl = (block *) regra;
                r->tag = 15;
                break;
            case (16):
                r->cmpExp = (cmpExpression *) regra;
                r->tag = 16;
                break;
            case (17):
                r->assmnt = (assignment *) regra;
                r->tag = 17;
                break;
            case (18):
                r->assExp = (assExpression *) regra;
                r->tag = 18;
                break;
            case (19):
                r->term = (term *) regra;
                r->tag = 19;
                break;
            case (20):
                r->factor = (factor *) regra;
                r->tag = 20;
                break;
	}
	return r;
}

// ---------------------------------------------------------------
// -------------------------- FUNÇÕES NEW ----------------------
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

term *new_term(term *newTerm, char op, factor *factor) { // STRUCT
    term *t = (term*) malloc(sizeof(term));
    t->term = newTerm;
    t->op = op;
    t->factor = factor;
    return t;
}

assExpression *new_assExpression (assExpression *assExp, char op, term *term) { // STRUCT
    assExpression *ae = (assExpression*) malloc(sizeof(assExpression));
    ae->assExp = assExp;
    ae->op = op;
    ae->term = term;
    return ae;
}

assignment *new_assignment (char *var, assExpression *assExp) { // STRUCT
    assignment *assmnt = (assignment*) malloc(sizeof(assignment));
    assmnt->var = var;
    assmnt->assExp = assExp;
    return assmnt;
}

cmpExpression *new_cmpExpression(char *cm) { // STRUCT
    cmpExpression *compare = (cmpExpression*) malloc(sizeof(cmpExpression));
    compare->comp = cm;
    return compare;
}

block *new_block(int tag, statement *stmt, statements *stmts) { // UNION
    block *bl = (block*) malloc(sizeof(block));
    bl->stmt = stmt;
    bl->stmts = stmts;
    return bl;
}

whileOp *new_whileOp(value *value1, cmpExpression *compare, value *value2, block *whileBlock) { // STRUCT
    whileOp *wh = (whileOp*) malloc(sizeof(whileOp));
    wh->value1 = value1;
    wh->compare = compare;
    wh->value2 = value2;
    wh->whileBlock = whileBlock;
    return wh;
}

ifWithElse *new_ifWithElse(value *value1, cmpExpression *compare, value *value2, block *ifBlock, block *elseBlock) { // STRUCT
    ifWithElse *ifElse = (ifWithElse*) malloc(sizeof(ifWithElse));
    ifElse->value1 = value1;
    ifElse->compare = compare;
    ifElse->value2 = value2;
    ifElse->ifBlock = ifBlock;
    ifElse->elseBlock = elseBlock;
    return ifElse;
}

ifNoElse *new_ifNoElse(value *value1, cmpExpression *compare, value *value2, block *ifBlock) { // STRUCT
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

values *new_values(int tag, values *newValues, value *value) { // UNION
    values *vals = (values*) malloc(sizeof(values));
    vals->values = newValues;
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

statement *new_statement(int tag, definition *def, funcCall *funcCall, ifNoElse *ifNoElse, ifWithElse *ifWithElse, whileOp *whileOp, assignment *assmnt, idStructExpression *idStrExp) { // UNION
    statement *stmt = (statement*) malloc(sizeof(statement));
    stmt->def = def;
    stmt->funcCall = funcCall;
    stmt->ifNoElse = ifNoElse;
    stmt->ifWithElse = ifWithElse;
    stmt->whileOp = whileOp;
    stmt->assmnt = assmnt;
    stmt->idStrExp = idStrExp;
    return stmt;
}

statements *new_statements(statements *stmts_left, statement *stmt) { // STRUCT
    statements *stmts = (statements*) malloc(sizeof(statements));
    stmts->stmts = stmts_left;
    stmts->stmt = stmt;
    return stmts;
}

arguments *new_arguments(int tag, arguments *newArguments, typeStr *typeArg, char *argNome) { // STRUCT
    arguments *args = (arguments*) malloc(sizeof(arguments));
    args->arguments = newArguments;
    args->typeArg = typeArg;
    args->argNome = argNome;
    return args;
}

typeQueue *new_typeQueue(typeSimple *tS) {
    typeQueue *typeQ = (typeQueue*) malloc(sizeof(typeQueue));
    typeQ->typeS = tS;
    return typeQ;
}

typeSimple *new_typeSimple(char *type) {
    typeSimple *typeSmp = (typeSimple*) malloc(sizeof(typeSimple));
    typeSmp->typeS = type;
    return typeSmp;
}

typeStr *new_typeStr(int tag, typeSimple *tS, typeQueue *tQ) { // UNION
    typeStr *tStr = (typeStr*) malloc(sizeof(typeStr));
    tStr->typeS = tS;
    tStr->typeQ = tQ;
    return tStr;
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


// ---------------------------------------------------
// ---------------------------------------------------
// ---------------------------------------------------


void show_tree(rule *r, int tabs) {
	int i;
	for (i = 0; i < tabs; ++i) printf("%d", r->tag);
	switch (r->tag) {
            case (1):
                printf("[program]");
                if(r->program->prog) { // Regra não é vazia
                    // program
                    // function
                }
                break;
            case (2):
                printf("[function]\n");
                // type_struct
                printf("%s\n(\n", r->func->nomeFunc);
                // arguments
                printf(")\n{\n");
                // statements
                printf("return\n");
                // value
                printf(";\n}\n");
                break;
            case (3):
                printf("[typeStr]\n");
                if (r->tst->typeQ) { // Tipo fila
                    printf("queue\n<\n");
                    // type_simple
                    printf(">\n");
                }
                else {
                    // type_simple
                }
                break;
            case (4):
                printf("[typeSimple]\n");
                printf("%s\n", r->tsp->typeS);
                break;
            case (5):
                printf("[arguments]\n");
                if (r->args->arguments) {// Existem argumentos antes da virgula
                    // arguments
                    printf(",");
                    // type_struct
                    printf("%s\n", r->args->argNome);
                }
                else {
                    // type_struct
                    printf("%s\n", r->args->argNome);
                }
                break;
            case (6):
                printf("[statements]\n");
                if (r->stmts->stmt) { // Regra não é vazia
                    // statements
                    // statement
                }
                break;
            case (7):
                printf("statement\n");
                if (r->stmt->def) { // regra de declaração não é nula
                    // type_struct
                    printf("%s\n;\n", r->stmt->def->var);
                }
                else if (r->stmt->funcCall) {
                    printf("%s\n(\n", r->stmt->funcCall->nomeFunc); //----------
                    // values
                    printf(")\n;\n");
                }
                else if (r->stmt->ifNoElse) {
                    printf("if\n(\n");
                    // value
                    // compare_assignment
                    // value
                    printf(")\n");
                    // block
                }
                else if (r->stmt->ifWithElse) {
                    printf("if\n(\n");
                    // value
                    // compare_assignment
                    // value
                    printf(")\n");
                    // block
                    printf("else\n");
                    // block
                }
                else if (r->stmt->whileOp) {
                    printf("while\n(\n");
                    // value
                    // compare_assignment
                    // value
                    printf(")\n");
                    // block
                }
                else if (r->stmt->assmnt) {
                    printf("%s\n=\n", r->stmt->assmnt->var);
                    // assignment_expression
                    printf(";\n");
                }
                //else if (r->stmt->idStrExp) {}
                else {/*ERRO*/}
                
                
                break;
            case (8):
                printf("[definition]\n"); // NUNCA CHEGA
                break;
            case (9):
                printf("[funcCall]\n"); // NUNCA CHEGA
                break;
            case (10):
                printf("[values]\n"); 
                if (r->vals->values) { // Regra: "values , value"
                    // values
                    printf(",\n");
                    // value
                }
                else if (r->vals->value) { // Regra: "value"
                    // value
                }
                else {/*REGRA VAZIA*/}
                break;
            case (11):
                printf("[value]\n"); // ------------ USAR TAG NESSE AQUI, PRA SABER QUAL VALOR
                if (r->val->i) {
                    printf("%d\n", r->val->i);
                }
                else if (r->val->f) {
                    printf("%2.f\n", r->val->f);
                }
                else if (r->val->c) {
                    printf("%c\n", r->val->c);
                }
                else if (r->val->s) {
                    printf("%s\n", r->val->s);
                }
                else {/*ERRO*/}
                break;
            case (12):
                printf("[ifNoElse]\n"); // NUNCA CHEGA
                break;
            case (13):
                printf("ifWithElse\n"); // NUNCA CHEGA
                break;
            case (14):
                printf("whileOp\n"); // NUNCA CHEGA
                break;
            case (15):
                printf("[block]\n");
                if(r->bl->stmt) { // Regra: "statement"
                    // statement
                }
                else if (r->bl->stmts) {
                    printf("{\n");
                    // statements
                    printf("}\n");
                }
                else {/*ERRO*/}
                break;
            case (16):
                printf("%s\n", r->cmpExp->comp);
                break;
            case (17):
                printf("[assignment]\n");
                if(r->assmnt->assExp) {
                    // assExp
                    printf("%c\n", r->assmnt->assExp->op);
                    // term
                }
                else {
                    // term
                }
                break;
            case (18):
                printf("assExpression\n"); // NUNCA CHEGA
                break;
            case (19):
                printf("[term]\n");
                if(r->term->term) {
                    // term
                    printf("%c\n", r->term->term->op);
                    // factor
                }
                else {
                    // factor
                }
                break;
            case (20):
                printf("[factor]\n");
                if (r->factor->value) {
                    // value
                }
                else if (r->factor->assExp) {
                    printf("(\n");
                    // assignment_expression
                    printf(")\n");
                }
                else {/*ERRO*/}
                break;

	}
}


#endif /* structs_h */

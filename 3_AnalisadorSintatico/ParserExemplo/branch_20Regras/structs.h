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
    union factor *factor; // 20
    int tag;
} rule;

// --------------------------------

    
typedef struct idStructExpression {
    union rule *value;
} idStructExpression;


typedef union factor {
    union rule *value;
    union rule *assExp;
} factor;

typedef struct term {
    union rule *term;
    char op;
    union rule *factor;
} term;

typedef struct assExpression {
    union rule *assExp;
    char op;
    union rule *term;
} assExpression;

typedef struct assignment {
    char *var;
    union rule *assExp;
} assignment;

// --------------------------------

typedef union block {
    union rule *stmt;
    union rule *stmts;
} block;

typedef struct cmpExpression {
    char *comp;
} cmpExpression;

typedef struct whileOp {
    union rule *value1;
    union rule *compare;
    union rule *value2;
    union rule *whileBlock;
} whileOp;

typedef struct ifWithElse {
    union rule *value1;
    union rule *compare;
    union rule *value2;
    union rule *ifBlock;
    union rule *elseBlock;
} ifWithElse;

typedef struct ifNoElse {
    union rule *value1;
    union rule *compare;
    union rule *value2;
    union rule *ifBlock;
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
    union rule *values;
    union rule *value;
} values;

// --------------------------------

typedef struct funcCall {
    union rule *params;
    char *nomeFunc;
} funcCall;

typedef struct definition {
    union rule *type;
    char *var;
} definition;

typedef union statement {
    union rule *def;
    union rule *funcCall;
    union rule *ifNoElse;
    union rule *ifWithElse;
    union rule *whileOp;
    union rule *assmnt;
    union rule *idStrExp;
} statement;

typedef struct statements {
    union rule *stmts;
    union rule *stmt;
} statements;

// --------------------------------

typedef struct arguments {
    union rule *arguments;
    union rule *typeArg;
    char *argNome;
} arguments;

typedef struct typeQueue {
    union rule *typeS;
} typeQueue;

typedef struct typeSimple {
    char *typeS; // void, int, char, float;
} typeSimple;


typedef union typeStr {
    union rule *typeS;
    union rule *typeQ;
} typeStr;

typedef struct function {
    union rule *typeReturn;
    char *nomeFunc;
    union rule *args;
    union rule *stmts;
    union rule *v;
} function;

typedef union program {
    union rule *prog;
    union rule *func;
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

rule *new_factor(int tag_rule, int tag, rule *value, rule *assExp) { // UNION
    rule *r = (rule *)malloc(sizeof(rule)); // Cria regra nova
    factor *f = (factor*) malloc(sizeof(factor)); // Que será do tipo factor
    f->value = value; // Factor aponta para value, que também é uma regra ...
    f->assExp = assExp; // ou factor aponta para uma assignment_expression, que também é uma regra
    
    r->factor = f;
    return r; // Retorna regra do tipo factor
}

rule *new_term(int tag_rule, rule *newTerm, char op, rule *factor) { // STRUCT
    rule *r = (rule *)malloc(sizeof(rule)); // Cria regra nova
    term *t = (term*) malloc(sizeof(term));
    t->term = newTerm;
    t->op = op;
    t->factor = factor;
    
    r->term = t;
    return r; // Retorna regra do tipo term
}

rule *new_assExpression (int tag_rule, rule *assExp, char op, rule *term) { // STRUCT
    rule *r = (rule *)malloc(sizeof(rule)); // Cria regra nova
    assExpression *ae = (assExpression*) malloc(sizeof(assExpression));
    ae->assExp = assExp;
    ae->op = op;
    ae->term = term;
    
    r->assExp = ae;
    return r; // Retorna regra do tipo assignment_expression
}

rule *new_assignment (int tag_rule, char *var, rule *assExp) { // STRUCT
    rule *r = (rule *)malloc(sizeof(rule)); // Cria regra nova
    assignment *assmnt = (assignment*) malloc(sizeof(assignment));
    assmnt->var = var;
    assmnt->assExp = assExp;
    
    r->assmnt = assmnt;
    return r; // Retorna regra do tipo assignment
}

rule *new_cmpExpression(int tag_rule, char *cm) { // STRUCT
    rule *r = (rule *)malloc(sizeof(rule)); // Cria regra nova
    cmpExpression *compare = (cmpExpression*) malloc(sizeof(cmpExpression));
    compare->comp = cm;
    
    r->cmpExp = compare;
    return r; // Retorna regra do tipo compare_assignment
}

rule *new_block(int tag_rule, int tag, rule *stmt, rule *stmts) { // UNION
    rule *r = (rule *)malloc(sizeof(rule)); // Cria regra nova
    block *bl = (block*) malloc(sizeof(block));
    bl->stmt = stmt;
    bl->stmts = stmts;
    
    r->bl = bl;
    return r; // Retorna regra do tipo block
}

rule *new_whileOp(int tag_rule, rule *value1, rule *compare, rule *value2, rule *whileBlock) { // STRUCT
    rule *r = (rule *)malloc(sizeof(rule)); // Cria regra nova
    whileOp *wh = (whileOp*) malloc(sizeof(whileOp));
    wh->value1 = value1;
    wh->compare = compare;
    wh->value2 = value2;
    wh->whileBlock = whileBlock;
    
    r->wh = wh;
    return r; // Retorna regra do tipo whileOp
}

rule *new_ifWithElse(int tag_rule, rule *value1, rule *compare, rule *value2, rule *ifBlock, rule *elseBlock) { // STRUCT
    rule *r = (rule *)malloc(sizeof(rule)); // Cria regra nova
    ifWithElse *ifElse = (ifWithElse*) malloc(sizeof(ifWithElse));
    ifElse->value1 = value1;
    ifElse->compare = compare;
    ifElse->value2 = value2;
    ifElse->ifBlock = ifBlock;
    ifElse->elseBlock = elseBlock;
    
    r->iwe = ifElse;
    return r; // Retorna regra do tipo ifWithElse
}

rule *new_ifNoElse(int tag_rule, rule *value1, rule *compare, rule *value2, rule *ifBlock) { // STRUCT
    rule *r = (rule *)malloc(sizeof(rule)); // Cria regra nova
    ifNoElse *ifNElse = (ifNoElse*) malloc(sizeof(ifNoElse));
    ifNElse->value1 = value1;
    ifNElse->compare = compare;
    ifNElse->value2 = value2;
    ifNElse->ifBlock = ifBlock;
    
    r->ife = ifNElse;
    return r; // Retorna regra do tipo ifNoElse
}

rule *new_value(int tag_rule, int tag, int i, float f, char c, char *s) { // UNION - FALTA TIPO FILA !!!!!!!!
    rule *r = (rule *)malloc(sizeof(rule)); // Cria regra nova
    value *val = (value*) malloc(sizeof(value));
    val->i = i;
    val->f = f;
    val->c = c;
    val->s = s;
    
    r->val = val;
    return r; // Retorna regra do tipo value
}

rule *new_values(int tag_rule, int tag, rule *newValues, rule *value) { // UNION
    rule *r = (rule *)malloc(sizeof(rule)); // Cria regra nova
    values *vals = (values*) malloc(sizeof(values));
    vals->values = newValues;
    vals->value = value;
    
    r->vals = vals;
    return r; // Retorna regra do tipo values
}

rule *new_funcCall(int tag_rule, char *nomeFunc, rule *params) { // STRUCT
    rule *r = (rule *)malloc(sizeof(rule)); // Cria regra nova
    funcCall *fc = (funcCall*) malloc(sizeof(funcCall));
    fc->nomeFunc = nomeFunc;
    fc->params = params;
    
    r->fc = fc;
    return r; // Retorna regra do tipo funcCall
}

rule *new_definition(int tag_rule, rule *type, char *var) {
    rule *r = (rule *)malloc(sizeof(rule)); // Cria regra nova
    definition *def = (definition*) malloc(sizeof(definition));
    def->type = type;
    def->var = var;
    
    r->def = def;
    return r; // Retorna regra do tipo definition
}

rule *new_statement(int tag_rule, int tag, rule *def, rule *funcCall, rule *ifNoElse, rule *ifWithElse, rule *whileOp, rule *assmnt, rule *idStrExp) { // UNION
    rule *r = (rule *)malloc(sizeof(rule)); // Cria regra nova
    statement *stmt = (statement*) malloc(sizeof(statement));
    stmt->def = def;
    stmt->funcCall = funcCall;
    stmt->ifNoElse = ifNoElse;
    stmt->ifWithElse = ifWithElse;
    stmt->whileOp = whileOp;
    stmt->assmnt = assmnt;
    stmt->idStrExp = idStrExp;
    
    r->stmt = stmt;
    return r; // Retorna regra do tipo statment
}

rule *new_statements(int tag_rule, rule *stmts_left, rule *stmt) { // STRUCT
    rule *r = (rule *)malloc(sizeof(rule)); // Cria regra nova
    statements *stmts = (statements*) malloc(sizeof(statements));
    stmts->stmts = stmts_left;
    stmts->stmt = stmt;
    
    r->stmts = stmts;
    return r; // Retorna regra do tipo statements
}

rule *new_arguments(int tag_rule, int tag, rule *newArguments, rule *typeArg, char *argNome) { // STRUCT
    rule *r = (rule *)malloc(sizeof(rule)); // Cria regra nova
    arguments *args = (arguments*) malloc(sizeof(arguments));
    args->arguments = newArguments;
    args->typeArg = typeArg;
    args->argNome = argNome;
    
    r->args = args;
    return r; // Retorna regra do tipo arguments
}

rule *new_typeQueue(int tag_rule, rule *tS) { // ------------------------------------- ACHO QUE NAO PRECISA MAIS DISSO
    rule *r = (rule *)malloc(sizeof(rule)); // Cria regra nova
    typeQueue *typeQ = (typeQueue*) malloc(sizeof(typeQueue));
    typeQ->typeS = tS;
    
   // r->tst = typeQ;
    return r; // Retorna regra do tipo typeQueue
}

rule *new_typeSimple(int tag_rule, char *type) {
    rule *r = (rule *)malloc(sizeof(rule)); // Cria regra nova
    typeSimple *typeSmp = (typeSimple*) malloc(sizeof(typeSimple));
    typeSmp->typeS = type;
    
    r->tsp = typeSmp;
    return r; // Retorna regra do tipo typeSimple
}

rule *new_typeStr(int tag_rule, int tag, rule *tS, rule *tQ) { // UNION
    rule *r = (rule *)malloc(sizeof(rule)); // Cria regra nova
    typeStr *tStr = (typeStr*) malloc(sizeof(typeStr));
    tStr->typeS = tS;
    tStr->typeQ = tQ;
    
    r->tst = tStr;
    return r; // Retorna regra do tipo typeStr
}

rule *new_function(int tag_rule, rule *typeReturn, char *nomeFunc, rule *args, rule *stmts, rule *v) { // STRUCT
    rule *r = (rule *)malloc(sizeof(rule)); // Cria regra nova
    function *func = (function*) malloc(sizeof(function));
    func->typeReturn = typeReturn;
    func->nomeFunc = nomeFunc;
    func->args = args;
    func->stmts = stmts;
    func->v = v;
    
    r->func = func;
    return r; // Retorna regra do tipo function
}

rule *new_program(int tag_rule, int tag, rule *prog, rule *func) { // UNION
    rule *r = (rule *)malloc(sizeof(rule)); // Cria regra nova
    program *p = (program*) malloc(sizeof(program));
    p->prog = prog;
    p->func = func;
    
    r->program = p;
    return r; // Retorna regra do tipo program
}


// ---------------------------------------------------
// ---------------------------------------------------
// ---------------------------------------------------


void show_tree(rule *r, int tabs) {
	int i;
	for (i = 0; i < tabs; ++i) printf("\t");
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
                    printf("%s\n;\n", r->stmt->def->def->var);
                }
                else if (r->stmt->funcCall) {
                    printf("%s\n(\n", r->stmt->funcCall->fc->nomeFunc); //----------
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
                    printf("%s\n=\n", r->stmt->assmnt->assmnt->var);
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
                    printf("%c\n", r->assmnt->assExp->assExp->op);
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
                    printf("%c\n", r->term->term->term->op);
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

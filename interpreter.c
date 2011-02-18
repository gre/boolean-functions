#include "stdlib.h"
#include "interpreter.h"
#include "function.h"
#include "ftree.h"
#include "parser/parser.h"

struct _Env {
  // ...
  
  // Symbols
  Function* functions[100]; // TODO dynamic
  int nbfunction;
  
  Points* points;
  int nbpoints;
};

typedef enum { TPA_UNDEF=0, TPA_VALUE, TPA_VARIABLE, TPA_OPERATOR } TPA_Type;

struct _TPA_Expr {
    /* 
     * value: boolean=0 ou 1, = -1 pour wildcard 
     * variable: num of the variable
     * operator: ('+', '*', '^', '!')
     */
    int val; 
    TPA_Type type; // 
    TPA_Expr *left; // also used for NOT
    TPA_Expr *right; // = 0 for NOT
};

Env* interp_init() {
  Env* env = malloc(sizeof(*env));
  env -> nbfunction = 0;
  env -> nbpoints = 0;
  return env;
}
void interp_free(Env* env) {
  free(env);
}

void addFunction(Env* env, char* name, Function* f) {
    env -> functions[nbfunction++] = f;
}

FunctionTree* TPAExpr_toFunctionTree(TPA_Expr* expr) {
    return createWithNode(rec_tpa_ftree(expr));
}
FunctionNode* rec_tpa_ftree(TPA_Expr* expr) {
    if(expr==0 || expr->type==TPA_UNDEF) return 0;
    if(expr->type==TPA_VALUE) return ftree_newBool(expr->val==1);
    if(expr->type==TPA_VARIABLE) return ftree_newVar((char)expr->val);
    if(expr->type==TPA_OPERATOR) {
        if(expr->val=='!')
            return ftree_newNot(expr->left);
        else
            return ftree_newBin(expr->left, expr->val, expr->right);
    }
}


void interp_runCommand(Env* env, TPA_Instruction* inst) {
	switch(ins->kind) {
        case PA_IK_Expr:
            Function* f = function_createWithFunctionTree(TPAExpr_toFunctionTree(inst.u.expr.expr));
            addFunction(env, inst.u.expr.name, f);

            break;
        case PA_IK_Table:
            fprintf(stderr," table fct=%s table=%p\n", inst.u.table.name, inst.u.table.vals);
            break;
        case PA_IK_Print:
            fprintf(stderr," print fct=%s fmt=%d file=%s\n", inst.u.print.name, inst.u.print.fmt, inst.u.print.filename!=0 ? inst.u.print.filename : "default");
            break;
        case PA_IK_Point:
            fprintf(stderr," point ens=%s point=%p\n", inst.u.print.name, inst.u.point.vals);
            break;
        case PA_IK_EvalPoint:
            fprintf(stderr," eval fct=%s point=%p\n", inst.u.evalpoint.name, inst.u.evalpoint.vals);
        case PA_IK_EvalEns:
            fprintf(stderr," eval fct=%s ens=%s\n", inst.u.evalens.name, inst.u.evalens.ens);
            break;
        default:
            fprintf(stderr," Instruction inconnue\n");
            break;
    }
}

TPA_Expr* tpa_init() {
    TPA_Expr* t = (TPA_Expr*)malloc(sizeof(*t));
    t -> val = 0;
    t -> type = TPA_UNDEF;
    t -> right = 0;
    t -> left = 0;
    return t;
}

extern TPA_Expr* pa_newBool(int b) { 
    TPA_Expr* t = tpa_init();
    t -> val = b;
    t -> type = TPA_VALUE;
    return t;
}

extern TPA_Expr* pa_newVar(char s) {
    TPA_Expr* t = tpa_init();
    t -> val = (int)s;
    t -> type = TPA_VARIABLE;
    return t;
}

extern TPA_Expr* pa_newNot(TPA_Expr*e) {
    TPA_Expr* t = tpa_init();
    t -> val = '!';
    t -> type = TPA_OPERATOR;
    t -> left = e;
    return t;  
}

extern TPA_Expr* pa_newCall(char*s, TPA_Expr** t) {
    return (TPA_Expr*) (0x100000); // TODO
}

extern TPA_Expr* pa_newBin(TPA_Expr*l, char o, TPA_Expr*r) { 
    TPA_Expr* t = tpa_init();
    t -> left = l;
    t -> right = r;
    t -> val = o;
    t -> type = TPA_OPERATOR;
    return t;
}

extern TPA_Expr* pa_newWildcard() { 
    TPA_Expr* t = tpa_init();
    t -> val = -1;
    t -> type = TPA_VALUE;
    return t;
}

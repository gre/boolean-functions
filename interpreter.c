#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "point.h"
#include "interpreter.h"
#include "function.h"
#include "ftree.h"
#include "btable.h"
#include "file.h"
#include "globals.h"
#include "point.h"
#include "points.h"
#include "parser/parser.h"

struct _Env {
  // ...

  // Symbols
  Function* functions[100]; // TODO dynamic
  int nbfunction;

  Points* points[100]; // TODO dynamic
  int nbpoints;
};

typedef enum { TPA_UNDEF=0, TPA_VALUE, TPA_VARIABLE, TPA_OPERATOR, TPA_CALL } TPA_Type;

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

    char* call;
    Point point;
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

static void addFunction(Env* env, char* name, Function* f) {
    function_setName(f, name);
		int i;
		for(i=0; i<env->nbfunction; ++i) {
			if(function_is(env->functions[i], name)) {
				env->functions[i] = f;
				return;
			}
		}
    env -> functions[env -> nbfunction ++] = f;
}

static void addPoints(Env* env, char* name, Points* p) {
    points_setName(p, name);
    env->points[env->nbpoints++] = p;
}


Function* interp_getFunctionByName(Env* env, char* name) {
  int i;
  for(i=0; i<env->nbfunction; ++i)
    if(function_is(env->functions[i], name))
      return env->functions[i];
  return 0;
}

Points* interp_getPointsByName(Env* env, char* name) {
  int i;
  for(i=0; i<env->nbpoints; ++i)
    if(points_is(env->points[i], name))
      return env->points[i];
  return 0;
}

static FunctionNode* TPAExpr_toFunctionNode(TPA_Expr* expr, Env* env) {
    if(expr==0 || expr->type==TPA_UNDEF) return 0;
    if(expr->type==TPA_VALUE) return ftree_newBool(expr->val==1);
    if(expr->type==TPA_VARIABLE) return ftree_newVar((char)expr->val);
    if(expr->type==TPA_OPERATOR) {
      return (expr->val=='!') ? ftree_newNot(TPAExpr_toFunctionNode(expr->left, env))
      : ftree_newBin(TPAExpr_toFunctionNode(expr->left, env), expr->val, TPAExpr_toFunctionNode(expr->right, env));
		}
    if(expr->type==TPA_CALL) {
      Function * f = interp_getFunctionByName(env, expr->call);
      if(f==0) {
        printf("Warning: no function was found for name: '%s'. Assuming false node.\n", expr->call);
        return ftree_newBool(0);
      }
      return ftree_newBool(function_eval(f, expr->point));
    }
    return 0;
}

static FunctionTree* TPAExpr_toFunctionTree(TPA_Expr* expr, Env* env) {
    return ftree_createWithNode(TPAExpr_toFunctionNode(expr, env));
}

static TruthTable* TPAExpr_toTruthTable(TPA_Expr** expr) {
    int size, i;
		for(size=0; expr[size]!=0; ++size);
		TruthTable* table = btable_init(size);
		for(i=0; i<size; ++i) {
			btable_setVal(table, i, expr[i]->val);
		}
		return table;
}

static Point TPAExpr_toPoint(TPA_Expr** expr) {
    int size, i;
    for(size=0; expr[size]!=0; ++size);
    Bool* vals = malloc(size*sizeof(Bool));
    for(i=0; i<size; ++i) {
      vals[i] = expr[i]->val;
    }
    return point_create(vals, size);
}


void interp_runCommand(Env* env, TPA_Instruction* inst) {
	char* str;
	Function* f;
	Points* points;
	PointItem* pointItem;
	FILE* out;
	#ifdef DEBUG
	//printf("DEBUG: instruction: kind: %d, name: %s, format: %d, ope: %c, ens: %s\n", inst->kind, inst->u.expr.name, inst->u.print.fmt, inst->u.point.ope, inst->u.evalens.ens);
	#endif
	out = stdout;
	switch(inst->kind) {
        case PA_IK_Expr:
            f = function_createWithFunctionTree(TPAExpr_toFunctionTree(inst->u.expr.expr, env));
            addFunction(env, inst->u.expr.name, f);
            break;

				case PA_IK_Table:
					f = function_createWithTruthTable(TPAExpr_toTruthTable(inst->u.table.vals));
					addFunction(env, inst->u.table.name, f);
					break;

        case PA_IK_Print:
            f = interp_getFunctionByName(env, inst->u.print.name);
            if(f==0) {
              fprintf(stderr,"Fonction inconnue\n");
            }
            else {
							out = stdout;

							if(inst->u.print.filename) {
								str = calloc(strlen(inst->u.print.filename)+1, sizeof(*str));
								strcpy(str, inst->u.print.filename+1);
								str[strlen(str)-1] = 0;
								out = file_fopenOutput(str);
								if(!out) {
									printf("Fallback on stdout print.\n");
									out = stdout;
								}
							}

							switch(inst->u.print.fmt) {
								case PA_PF_expr:
									function_print(f, out);
									break;

								case PA_PF_bdd:
									function_printAsBDD(f, out);
									break;

								case PA_PF_table:
									function_printAsTruthTable(f, out);
									break;

								case PA_PF_disjonctive:
									function_printAsDNF(f, out);
									break;

								case PA_PF_tree:
									function_printAsTree(f, out);
									break;

								case PA_PF_karnaugh:
									function_printAsKarnaugh(f, out);
									break;
							}

							if(out!=stdout)
								fclose(out);
            }
            break;
        case PA_IK_Point:
                // u.print.name - point name
                // u->u.point:
                // char*      name; // nom de l'ensemble
                // char       ope;  // operateur: '=':= ; '+':+= ; '-':-=
                // TPA_Expr** vals; // les valeurs du point:
                points = interp_getPointsByName(env,inst->u.point.name);
                if (points == 0) {
                    points = points_init();
                    addPoints(env, inst->u.expr.name, points);
                }
                if (interp_pointsOperation(points,inst->u.point.name,inst->u.point.ope,inst->u.point.vals) == 0)
                	fprintf(stderr, "La taille de point est incompatible avec l'ensamble\n");
				else 
	                points_print(points, out);
                break;
        case PA_IK_EvalEns:
        		
                points = interp_getPointsByName(env,inst->u.evalens.ens);
                if (points == 0) {
                	fprintf(stderr, "Ensamble des points inconnue\n");
                	break;
				}
				pointItem = points->point;
				if (pointItem == 0) {
					fprintf(stderr, "L'ensamble des points est vide\n");
					break;
				}
				
				f = interp_getFunctionByName(env, inst->u.evalens.name);
				if (f == 0) {
					fprintf(stderr,"Fonction inconnue\n");
				  	break;
				}
				
				if (points_pointDim(points) != function_varsLength(f)) {
					fprintf(stderr,"Point vector dim and function vars number mismatch.\n");
				  	break;					
				}
								
				do {
					function_printEvalPoint(f,pointItem->p,out);					
					pointItem = pointItem->next;
				} while (pointItem != 0);

                break;
	    case PA_IK_EvalPoint:
	  		function_printEvalPoint(
	  			interp_getFunctionByName(env, inst->u.evalpoint.name),
	  			TPAExpr_toPoint(inst->u.evalpoint.vals),out
	  		);
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
    t -> call = 0;
    return t;
}

extern TPA_Expr* pa_newBool(int b) {
    TPA_Expr* t = tpa_init();
    t -> val = b;
    t -> type = TPA_VALUE;
    #ifdef TRACE
    printf("newBool val: %d type:TPA_VALUE \n", b);
    #endif
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

extern TPA_Expr* pa_newCall(char* s, TPA_Expr** params) {
    TPA_Expr* t = tpa_init();
    char* cpy = malloc( (strlen(s)+1)*sizeof(char) );
    strcpy(cpy, s);
    t -> type = TPA_CALL;
    t -> call = cpy;
    t -> point = (params==0) ? point_init(0) : TPAExpr_toPoint(params);
    return t;
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

/**
* Handle operation on a point
* @param char* name points name
* @param char ope operateur: '=':= ; '+':+= ; '-':-=
* @param TPA_Expr** vals
**/
int interp_pointsOperation(Points* points, char* name, char ope, TPA_Expr** vals) {
    Point point;
    int i, size;
    TPA_Expr ** val;

    val = vals;
    size = 0;

    // Calculate the size of our point vector
    while(*val != 0) {
        size++;
        val++;
    }

    point = point_init(size);

    for(i=0; i<size; i++)
        point.vect[i] = (char)(*vals[i]).val; // int that can contain 0,1,-1 (wildcard)

    switch(ope) {
        case '=':
            points_free(points);
            points_wildOp(points, point, '+');
            break;
        case '+':
        	if (!points_fit(points, point)) return 0;
            points_wildOp(points, point, ope);
            break;
        case '-':
        	if (!points_fit(points, point)) return 0;
            points_wildOp(points, point, ope);
            break;
    }
    return 1;
}

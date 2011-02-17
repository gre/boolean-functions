%{
#include <stdio.h>
#include <stdlib.h>

#include "parser.h"


static TPA_Instruction pa_inst;

static TPA_Expr** pa_exprset_add_expr(TPA_Expr** set, TPA_Expr* e)
{
    TPA_Expr** ret;
    if ( set==0 ) {
        ret = (TPA_Expr**) malloc(sizeof(*ret)*2);
        ret[0]=e; ret[1]=0;
    } else {
        int nb;
        for (nb=0 ; set[0]!=0 ; nb+=1);
        ret = (TPA_Expr**) realloc(ret,sizeof(*ret)*(nb+2));
        ret[nb]=e; ret[nb+1]=0;
    }
    return ret;
}
%}

%union {
    int             numval;
    TPA_PrintFormat fmtval;
    char*           string;
    TPA_Expr*       expr;
    TPA_Expr**      exprs;
}

%token         TK_EXPR TK_TABLE TK_PRINT TK_POINT TK_EVAL
%token<numval> TK_VAR
%token<string> TK_IDENT TK_STRING
%token<fmtval> TK_PrintFormat
%token         TK_EOL TK_EOF TK_ERROR

%type<fmtval>  print_format_optional
%type<string>  string_optional

%type<expr>    expr expr_terminal
%type<exprs>   point01_list point01s_list point01v_list

%left '^'
%left '+'
%left '*'
%left '!'

%%
instruction
    : TK_EXPR  TK_IDENT '=' expr TK_EOL {
        pa_inst.kind=PA_IK_Expr;
        pa_inst.u.expr.name=$2;
        pa_inst.u.expr.expr=$4;
        return 0; }
    | TK_TABLE TK_IDENT '=' '(' point01_list ')' TK_EOL {
        pa_inst.kind=PA_IK_Table;
        pa_inst.u.table.name=$2;
        pa_inst.u.table.vals=$5; 
        return 0; }
    | TK_PRINT print_format_optional TK_IDENT string_optional TK_EOL {
        pa_inst.kind=PA_IK_Print;
        pa_inst.u.print.name=$3;
        pa_inst.u.print.fmt=$2;
        pa_inst.u.print.filename=$4;
        return 0; }
    | TK_POINT TK_IDENT '=' '(' point01s_list ')' TK_EOL {
        pa_inst.kind=PA_IK_Point;
        pa_inst.u.point.name=$2;
        pa_inst.u.point.ope='='; 
        pa_inst.u.point.vals=$5;
        return 0; }
    | TK_POINT TK_IDENT '+' '=' '(' point01s_list ')' TK_EOL {
        pa_inst.kind=PA_IK_Point;
        pa_inst.u.point.name=$2;
        pa_inst.u.point.ope='+'; 
        pa_inst.u.point.vals=$6;
        return 0; }
    | TK_POINT TK_IDENT '-' '=' '(' point01s_list ')' TK_EOL {
        pa_inst.kind=PA_IK_Point;
        pa_inst.u.point.name=$2;
        pa_inst.u.point.ope='-'; 
        pa_inst.u.point.vals=$6;
        return 0; }
    | TK_EVAL  TK_IDENT '(' point01_list ')' TK_EOL {
        pa_inst.kind=PA_IK_EvalPoint; 
        pa_inst.u.evalpoint.name=$2;
        pa_inst.u.evalpoint.vals=$4;
        return 0; }
    | TK_EVAL  TK_IDENT TK_IDENT TK_EOL {
        pa_inst.kind=PA_IK_EvalEns; 
        pa_inst.u.evalens.name=$2;
        pa_inst.u.evalens.ens=$3;
        return 0; }
    | TK_EOF { return -1; }
;

/*************************************************************/
/*** print                                                 ***/

print_format_optional
    : TK_PrintFormat { $$=$1; }
    |                { $$ = PA_PF_expr; }
;

/*************************************************************/
/*** expression                                            ***/
expr
    : expr_terminal { $$=$1; }
    | '(' expr ')'  { $$=$2; }
    | '!' expr      { $$=pa_newNot($2); }
    | expr '*' expr { $$=pa_newBin($1,'*',$3); }
    | expr '+' expr { $$=pa_newBin($1,'+',$3); }
    | expr '^' expr { $$=pa_newBin($1,'^',$3); }
;

expr_terminal
    : '0'                            { $$ = pa_newBool(0); }
    | '1'                            { $$ = pa_newBool(1); }
    | TK_VAR                         { $$ = pa_newVar($1); }
    | TK_IDENT                       { $$ = pa_newCall($1,0); }
    | TK_IDENT '(' point01v_list ')' { $$ = pa_newCall($1,$3); }
;

/*************************************************************/
/*** shared rules                                          ***/

point01_list
    : point01_list '0'     { $$= pa_exprset_add_expr($1,pa_newBool(0)); }
    | point01_list '1'     { $$= pa_exprset_add_expr($1,pa_newBool(1)); }
    |                      { $$=0; }
;

point01s_list
    : point01s_list '0'     { $$= pa_exprset_add_expr($1,pa_newBool(0)); }
    | point01s_list '1'     { $$= pa_exprset_add_expr($1,pa_newBool(1)); }
    | point01s_list '*'     { $$= pa_exprset_add_expr($1,pa_newWildcard()); }
    |                       { $$=0; }
;

point01v_list
    : point01v_list '0'     { $$= pa_exprset_add_expr($1,pa_newBool(0)); }
    | point01v_list '1'     { $$= pa_exprset_add_expr($1,pa_newBool(1)); }
    | point01v_list TK_VAR  { $$= pa_exprset_add_expr($1,pa_newVar($2)); }
    |                       { $$=0; }
;

string_optional
    : TK_STRING  { $$=$1; }
    |            { $$=0; }
;

%%

#include "lex.yy.c"

int yyerror(const char* mess)
{
    fprintf(stderr,"ERROR: %s near %s\n",mess,yytext);
    return 0;
}

int pa_parser(TPA_Instruction* i)
{
    int ret = yyparse();
    if ( ret==0 ) {
        *i = pa_inst;
        return 1;
    } else if ( ret == -1 ) {
        return -1;
    } else 
        return 0;
}

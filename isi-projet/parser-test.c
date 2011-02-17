#include <stdio.h>
#include <stdlib.h>

#include "parser.h"

int main()
{
    TPA_Instruction inst;
    fprintf(stdout,"--> "); fflush(stdout);
    while (1) {
        int status=pa_parser(&inst);
        if ( status == 0 ) {
            fprintf(stderr,"  Instruction sautee\n");
        } else  if ( status == -1 ) {
            break;
        } else {
            switch ( inst.kind ) {
              case PA_IK_Expr:
                fprintf(stderr,"  expr fct=%s expr=%p\n",
                    inst.u.expr.name,inst.u.expr.expr);
                break;
              case PA_IK_Table:
                fprintf(stderr,"  table fct=%s table=%p\n",
                    inst.u.table.name,
                    inst.u.table.vals);
                break;
              case PA_IK_Print:
                fprintf(stderr,"  print fct=%s fmt=%d file=%s\n",
                    inst.u.print.name,
                    inst.u.print.fmt,
                    inst.u.print.filename!=0 ? inst.u.print.filename : "default");
                break;
              case PA_IK_Point:
                fprintf(stderr,"  point ens=%s point=%p\n",
                    inst.u.print.name,
                    inst.u.point.vals);
                break;
              case PA_IK_EvalPoint:
                fprintf(stderr,"  eval fct=%s point=%p\n",
                    inst.u.evalpoint.name,
                    inst.u.evalpoint.vals);
              case PA_IK_EvalEns:
                fprintf(stderr,"  eval fct=%s ens=%s\n",
                    inst.u.evalens.name,
                    inst.u.evalens.ens);
                break;
              default:
                fprintf(stderr,"  Instruction inconnue\n");
                break;
            }
        }
        fprintf(stdout,"--> "); fflush(stdout);
    }
    return 0;
}


extern TPA_Expr* pa_newBool(int b)                         { return (TPA_Expr*) (0x100100 + b); }
extern TPA_Expr* pa_newVar(char s)                         { return (TPA_Expr*) (0x100200 + 0); }
extern TPA_Expr* pa_newCall(char*s, TPA_Expr** t)          { return (TPA_Expr*) (0x100300 + 0); }
extern TPA_Expr* pa_newNot(TPA_Expr*e)                     { return (TPA_Expr*) (0x100400 + 0); }
extern TPA_Expr* pa_newBin(TPA_Expr*l, char o, TPA_Expr*r) { return (TPA_Expr*) (0x100500 + 0); }
extern TPA_Expr* pa_newWildcard()                          { return (TPA_Expr*) (0x100600 + 2); }


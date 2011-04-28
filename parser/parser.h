
/*******************************************************************/
/* Le parser construit des expressions logique (instruction expr). */
/* Celles si sont representees par le type TPA_Expr.               */
/* Pour les construire le parser utilise les fonctions de          */
/* construction pa_newXxx declarées ci-dessous.                    */
/*                                                                 */
/* VOUS DEVEZ IMPLANTER CE TYPE ET CES FONCTIONS.                  */

/* type décrivant une exprssion logique */
typedef struct _TPA_Expr TPA_Expr;

/* fonction de construction d'expression logique. */
extern TPA_Expr* pa_newBool(int);
extern TPA_Expr* pa_newVar(char);
extern TPA_Expr* pa_newCall(char*, TPA_Expr**);
extern TPA_Expr* pa_newNot(TPA_Expr*);
extern TPA_Expr* pa_newBin(TPA_Expr*, char, TPA_Expr*);
extern TPA_Expr* pa_newWildcard();

/* type décrivant une exprssion logique */
typedef enum _TPA_InstKind {
    PA_IK_Expr,
    PA_IK_Table,
    PA_IK_Print,
    PA_IK_Point,
    PA_IK_EvalPoint,
    PA_IK_EvalEns
} TPA_InstKind;

/*******************************************************************/
/* Structure de données du parser.                                 */
/*                                                                 */
/* La fonction pa_parser(TPA_Instruction* i) lit sur stdin une     */
/* instruction et la stocke dans la structure i.                   */
/* La structure i est décrite ci-dessous.                          */
/*                                                                 */
/* La fonction renvoie:                                            */
/*    1: si une nouvelle instruction a été lue, celle ci se trouve */
/*       dans i.                                                   */
/*   -1: si l'instruction est mal formatée, dans ce cas i ne       */
/*       contient rien.                                            */
/*    0: fin du fichier d'entrée, dans ce cas i ne  contient rien. */
/*                                                                 */
/* Un exemple d'utilisation est donné dans le main se trouvant     */
/* le fichier parser-test.c.                                       */

typedef enum _TPA_PrintFormat {
    PA_PF_expr,
    PA_PF_bdd,
    PA_PF_table,
    PA_PF_disjonctive,
    PA_PF_dot,
    PA_PF_karnaugh
} TPA_PrintFormat;

typedef struct _TPA_Instruction {
    TPA_InstKind kind;
    union {
      struct _TPA_InstructionExpr {
        char*     name; // nom de la fonction
        TPA_Expr* expr; // la fonction
      } expr;
      struct _TPA_InstructionTable {
        char*      name; // nom de la fonction
        TPA_Expr** vals; // la fonction:
                         //   - le tableau est null terminated.
                         //   - les vals[i] sont des pa_newBool(...).
      } table;
      struct _TPA_InstructionPrint {
        char*      name;      // nom de la fonction
        TPA_PrintFormat fmt;  // le format demande
        char*      filename;  // le nom du fichier de sortie (
                              // null means le fichier par defaut).
      } print;
      struct _TPA_InstructionPoint {
        char*      name; // nom de l'ensemble
        char       ope;  // operateur: '=':= ; '+':+= ; '-':-=
        TPA_Expr** vals; // les valeurs du point:
                         //   - le tableau est null terminated.
                         //   - les vals[i] sont des pa_newBool(...),
                         //     ou des pa_newWildcard().
      } point;
      struct _TPA_InstructionEvalPoint {
        char*      name; // nom de la fonction
        TPA_Expr** vals; // les valeurs du point:
                         //   - le tableau est null terminated.
                         //   - les vals[i] sont des pa_newBool(...).
      } evalpoint;
      struct _TPA_InstructionEvalEns {
        char*      name; // nom de la fonction
        char*      ens;  // nom de l'ensemble de points
      } evalens;
    } u;
} TPA_Instruction;

// renvoie 1 et l'instruction dans *i.
// renvoie -1 si l'instruction n'a pas été lue (syntax error).
// renvoie 0 sur fin de fichier.
int pa_parser(TPA_Instruction* i);


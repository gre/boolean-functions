%option noyywrap

%%
expr  { return TK_EXPR; }
table { return TK_TABLE; }
print { return TK_PRINT; }
point { return TK_POINT; }
eval  { return TK_EVAL; }
[a-z] { yylval.numval = *yytext; return TK_VAR; }
[a-zA-Z][a-zA-Z0-9]*[']* {
        yylval.string = strdup(yytext); return TK_IDENT; }
\"[^\n]*\" {
        yylval.string = strdup(yytext); return TK_STRING; }

[=+()-01!*^] { return *yytext; }
"/e"[a-z]*        { yylval.fmtval= PA_PF_expr;  return TK_PrintFormat; }
"/b"[a-z]*        { yylval.fmtval= PA_PF_bdd;   return TK_PrintFormat; }
"/t"[a-z]*        { yylval.fmtval= PA_PF_table; return TK_PrintFormat; }
"/d"[a-z]*        { yylval.fmtval= PA_PF_disjonctive; return TK_PrintFormat; }
"/k"[a-z]*        { yylval.fmtval= PA_PF_karnaugh; return TK_PrintFormat; }
"/a"[a-z]*        { yylval.fmtval= PA_PF_dot; return TK_PrintFormat; }
[\n]      { return TK_EOL; }
[ \t]     ;
.         { return TK_ERROR; }
<<EOF>>   { return TK_EOF; }

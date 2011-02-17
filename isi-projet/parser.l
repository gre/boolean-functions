%option noyywrap

%%
expr  { return TK_EXPR; }
table { return TK_TABLE; }
print { return TK_PRINT; }
point { return TK_POINT; }
eval  { return TK_EVAL; }
[a-z] { yylval.numval = *yytext; return TK_VAR; }
[a-zA-Z][a-zA-Z0_9]*[']* {
        yylval.string = strdup(yytext); return TK_IDENT; }
\"[^\n]*\" {
        yylval.string = strdup(yytext); return TK_STRING; }

[=+()-01!*] { return *yytext; }
[\n]      { return TK_EOL; }
[ \t]     ;
.         { return TK_ERROR; }
<<EOF>>   { return TK_EOF; }

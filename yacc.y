%{
#define YYSTYPE double
#include <stdio.h>
%}

%token NUMBER

/*
expression
    : term   { return((make-instance 'node :val $1)) }
    | expression '+' term { return((make-instance 'node :left $1 :val '+ :right $3)) }
    | expression '-' term { return((make-instance 'node :left $1 :val '- :right $3)) }
    ;

(let ((yyvsp (make-array '(1 2 3))))
  (cond ((eq yyn 3)
         ((make-instance 'node :left (aref yyvsp (- 1 3)) :val '+ :right (aref yyvsp (- 1 3)))))
        ((eq yyn 4)
         ((make-instance 'node :left (aref yyvsp (- 1 3)) :val '- :right (aref yyvsp (- 1 3)))))))
*/

%%
lines
    :
    | lines expression '\n'  { printf(" = %lf\n", $2); }
    ;

expression
    : term   { $$ = $1; }
    | expression { $$ = $1; } '+' { $$ = $2; } term { $$ = $1 + $3; }
    | expression '-' term { $$ = $1 - $3; }
    ;

term
    : factor   { $$ = $1; }
    | term '*' factor  { $$ = $1 * $3; }
    | term '/' factor  { $$ = $1 / $3; }
    ;

factor
    : NUMBER   { $$ = $1; }
    | group   { $$ = $1; }
    ;

group
    : '(' expression ')' { $$ = $2; }
    ;

%%
int
main(int argc, char** argv) {
    yyparse();
    return 0;
}

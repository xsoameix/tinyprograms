#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

// Terminals
// level     l[0-9]+
// FirstName [A-Z][a-z]*
// LastName  [a|c-z]+
// cid       [0-9]+
// battle    b

enum TYPE {
    LEVEL,
    ...
};

struct Scanner {
    char * input;
    char * forword;
    char * lexeme;
};

struct Parser {
    struct Scanner * scanner;
    enum TYPE type;
};

char *
user_input(void) {
    size_t capa = 80 + 1; // last char: '\n'
    char * input = malloc(capa);
    fgets(input, capa, stdin);
    return input;
}

struct Scanner *
new_scanner(void) {
    struct Scanner * scanner = malloc(sizeof(struct Scanner));
    char * input = user_input();
    scanner->input = input;
    scanner->forword = input;
    scanner->lexeme = input;
    return scanner;
}

bool
level_p(char c) {
    return c == 'l';
}

struct Token *
scan(struct Scanner * scanner) {
    char * forword = scanner->forword;
    char * lexeme  = scanner->lexeme;
    enum TYPE type;
    if(level_p(* forword)) {
        forword += 1;
        if(!number_p(* forword)) {
            raise_error();
        }
        do {
            forword += 1;
        } while(number_p(* forword));
        type = LEVEL;
    } else if(first_name_p(forword)) {
    } else if(last_name_p(forword)) {
    } else if(cid_p(forword)) {
    } else if(battle_p(forword)) {
    } else if(end_of_line_p(forword)) {
    }
    scanner->forword = forword;
    scanner->lexeme = forword;
    return new_token(type, lexeme, forword - lexeme);
}

void
parse(struct Parser * parser) {
    next(parser);
    parse_Proc(parser);
}

void
next(struct Parser * parser) {
    struct Token * token = scan(scanner);
    parser->type = token->type;
}

int
main(void) {
    struct Scanner * scanner = new_scanner();
    struct Parser * parser = new_parser();
    parse(parser);
    return 0;
}

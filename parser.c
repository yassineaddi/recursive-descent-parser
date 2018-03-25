#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define NUM     "NUM"
#define PLUS    "PLUS"
#define MINUS   "MINUS"
#define MUL     "MUL"
#define DIV     "DIV"
#define LPAREN  "LPAREN"
#define RPAREN  "RPAREN"
#define EOE     "EOE" // end of expression.

typedef struct Token {
    char type[20];
    //int value;
    float value;
} Token;

void __invalid_char_error(char);
void __invalid_syntax_error();
void __repr_token(Token);
Token get_next_token();
void consume(char[]);
float factor();
float term();
float parse();
float evaluate_expression();

char *expr;
Token curr_token;

void __invalid_char_error(char c) {
    printf("Error: invalid character \'%c\'\n", c);
    exit(EXIT_FAILURE);
}

void __invalid_syntax_error() {
    printf("Error: invalid syntax\n");
    exit(EXIT_FAILURE);
}

void __repr_token(Token token) {
    printf("Token(%s, %f)\n", token.type, token.value);
}

Token get_next_token() {
    while (*expr != '\0') {
        if (*expr >= '0' && *expr <= '9') {
            Token token = {NUM, *expr++ - '0'};
            while ((*expr >= '0' && *expr <= '9') || *expr == '.') {
                if (*expr == '.') {
                    expr++;
                    int frac = 0, i = 0;
                    while (*expr >= '0' && *expr <= '9') {
                        frac = frac * 10 + (*expr++ - '0');
                        i++;
                    }
                    if ( ! i) {
                        __invalid_syntax_error();
                    }

                    token.value = token.value + (frac / pow(10, i));

                    return token;
                } else {
                    token.value = token.value * 10 + (*expr++ - '0');
                }
            }
            return token;
        }
        if (*expr == '+') {
            Token token = {PLUS, 0};
            expr++;
            return token;
        }
        if (*expr == '-') {
            Token token = {MINUS, 0};
            expr++;
            return token;
        }
        if (*expr == '*') {
            Token token = {MUL, 0};
            expr++;
            return token;
        }
        if (*expr == '/') {
            Token token = {DIV, 0};
            expr++;
            return token;
        }
        if (*expr == '(') {
            Token token = {LPAREN, 0};
            expr++;
            return token;
        }
        if (*expr == ')') {
            Token token = {RPAREN, 0};
            expr++;
            return token;
        }
        if (isspace(*expr)) {
            expr++;
            continue;
        }
        __invalid_char_error(*expr);
    }
    Token token = {EOE, 0};
    return token;
}

void consume(char token_type[]) {
    if ( ! strcmp(token_type, curr_token.type)) {
        curr_token = get_next_token();
    } else {
        __invalid_syntax_error();
    }
}

float factor() {
    Token token = curr_token;

    if ( ! strcmp(token.type, NUM)) {
        consume(NUM);
        return token.value;
    }
    if ( ! strcmp(token.type, LPAREN)) {
        consume(LPAREN);
        int result = parse();
        consume(RPAREN);
        return result;
    }
    if ( ! strcmp(token.type, PLUS) || ! strcmp(token.type, MINUS)) {
        int result = 0;
        if ( ! strcmp(token.type, PLUS)) {
            consume(PLUS);
            result += factor();
        } else if ( ! strcmp(token.type, MINUS)) {
            consume(MINUS);
            result -= factor();
        }
        return result;
    }

    __invalid_syntax_error();
}

float term() {
    float result = factor();

    while ( ! strcmp(curr_token.type, MUL) || ! strcmp(curr_token.type, DIV)) {
        Token token = curr_token;
        if ( ! strcmp(token.type, MUL)) {
            consume(MUL);
            result *= factor();
        } else if ( ! strcmp(token.type, DIV)) {
            consume(DIV);
            result /= factor();
        }
    }

    return result;
}

float parse() {
    float result = term();

    while ( ! strcmp(curr_token.type, PLUS) || ! strcmp(curr_token.type, MINUS)) {
        Token token = curr_token;
        if ( ! strcmp(token.type, PLUS)) {
            consume(PLUS);
            result += term();
        } else if ( ! strcmp(token.type, MINUS)) {
            consume(MINUS);
            result -= term();
        }
    }

    return result;
}

float evaluate_expression() {
    float result = parse();

    if (strcmp(curr_token.type, EOE)) {
        __invalid_syntax_error();
    }

    return result;
}

int main() {
    char eval[256];
    do {
        printf("> ");
        gets(eval);
        if ( ! strcmp(eval, "")) {
            continue;
        }

        expr = eval;
        curr_token = get_next_token();

        float result = evaluate_expression();
        if (ceil(result) == result) {
            printf("%d\n", (int) result);
        } else {
            printf("%f\n", result);
        }
    } while (1);

    return 0;
}







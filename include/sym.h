#ifndef SYM_H
#define SYM_H

#include <stdbool.h>
#include <wchar.h>

// Types
#define INTEGER  0
#define OPERATOR 1
#define FUNCTION 2

// Operators
#define NONE 0
#define ADD  1
#define MUL  2
#define POW  3

// Visulal operators
#define SUB 4
#define DIV 5

// Functions
#define NEG 6
#define SIN 7
#define COS 8
#define TAN 9

typedef struct Expr Expr;
struct Expr {
    Expr* a;  // NULL if is an integer
    Expr* b;  // NULL if is a function
    long val;
    int type;
    int operator;
    bool hl; // true if expression is selected
};

void getInt(Expr* expr, long integer);

void getOperator(Expr* expr, Expr* a, Expr* b, int operator);

void getAdd(Expr* expr, Expr* a, Expr* b);

void getMul(Expr* expr, Expr* a, Expr* b);

void getPow(Expr* expr, Expr* a, Expr* b);

void getSub(Expr* expr, Expr* a, Expr* b);

void getDiv(Expr* expr, Expr* a, Expr* b);

void getFunction(Expr* expr, Expr* a, int name);

void getNeg(Expr* expr, Expr* a);

void getSin(Expr* expr, Expr* a);

void getCos(Expr* expr, Expr* a);

void getTan(Expr* expr, Expr* a);

//Expr* evaluate(Expr* expr);

#endif


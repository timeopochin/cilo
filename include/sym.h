#ifndef SYM_H
#define SYM_H

#include <stdbool.h>
#include <wchar.h>

// Types
#define UNDEF    -1
#define INTEGER   0
#define OPERATOR  1
#define FUNCTION  2

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

// a == b
bool equals(Expr* a, Expr* b);

// should a be before b
bool before(Expr* a, Expr* b);

long greatestCommonFactor(long a, long b);

Expr* getUndef();

Expr* getInt(long integer);

Expr* getOperator(Expr* a, Expr* b, int operator);

Expr* getAdd(Expr* a, Expr* b);

Expr* getMul(Expr* a, Expr* b);

Expr* getPow(Expr* a, Expr* b);

Expr* getSub(Expr* a, Expr* b);

Expr* getDiv(Expr* a, Expr* b);

Expr* getFunction(Expr* a, int name);

Expr* getNeg(Expr* a);

Expr* getSin(Expr* a);

Expr* getCos(Expr* a);

Expr* getTan(Expr* a);

Expr* evaluate(Expr* expr);

double calculate(Expr* expr);

#endif


#include "sym.h"

#include <stdlib.h>
#include <math.h>

Expr* getInt(long integer) {
    Expr* expr = malloc(sizeof(Expr));
    expr->a = NULL;
    expr->b = NULL;
    expr->val = integer;
    expr->type = INTEGER;
    expr->operator = NONE;
    expr->hl = false;
}

Expr* getOperator(Expr* a, Expr* b, int operator) {
    Expr* expr = malloc(sizeof(Expr));
    expr->a = a;
    expr->b = b;
    expr->val = 0;
    expr->type = OPERATOR;
    expr->operator = operator;
    expr->hl = false;
}

Expr* getAdd(Expr* a, Expr* b) {
    return getOperator(a, b, ADD);
}

Expr* getMul(Expr* a, Expr* b) {
    return getOperator(a, b, MUL);
}

Expr* getPow(Expr* a, Expr* b) {
    return getOperator(a, b, POW);
}

Expr* getSub(Expr* a, Expr* b) {
    return getOperator(a, b, SUB);
}

Expr* getDiv(Expr* a, Expr* b) {
    return getOperator(a, b, DIV);
}

Expr* getFunction(Expr* a, int name) {
    Expr* expr = malloc(sizeof(Expr));
    expr->a = a;
    expr->b = NULL;
    expr->val = 0;
    expr->type = FUNCTION;
    expr->operator = name;
    expr->hl = false;
}

Expr* getNeg(Expr* a) {
    return getFunction(a, NEG);
}

Expr* getSin(Expr* a) {
    return getFunction(a, SIN);
}

Expr* getCos(Expr* a) {
    return getFunction(a, COS);
}

Expr* getTan(Expr* a) {
    return getFunction(a, TAN);
}

Expr* evaluate(Expr* expr) {
    Expr* a;
    Expr* b;
    Expr* temp; // Used for swapping
    long val; // Used for freeing before returning
    switch (expr->type) {
        case INTEGER:

            // Already evaluated
            return getInt(expr->val);

            break;
        case OPERATOR:

            // Needs evaluating
            a = evaluate(expr->a);
            b = evaluate(expr->b);

            switch (expr->operator) {
                case ADD:
                    if (a->operator > b->operator) {
                        temp = a;
                        a = b;
                        b = temp;
                    }

                    // Two integers
                    if (a->type == INTEGER &&
                        b->type == INTEGER) {
                        val = a->val + b->val;
                        free(a);
                        free(b);
                        return getInt(val);
                    }

                    // Was not evaluated
                    return getAdd(a, b);

                    break;
                case MUL:
                    if (a->operator > b->operator) {
                        temp = a;
                        a = b;
                        b = temp;
                    }

                    // Was not evaluated
                    return getMul(a, b);

                    break;
                case POW:

                    // Was not evaluated
                    return getPow(a, b);

                    break;
                case SUB:

                    // Was not evaluated
                    return getSub(a, b);

                    break;
                case DIV:

                    // Was not evaluated
                    return getDiv(a, b);

                    break;
            }
            break;
        case FUNCTION:

            // Needs evaluating
            a = evaluate(expr->a);

            switch (expr->operator) {
                case NEG:

                    // Negate
                    if (a->type == INTEGER) {
                        a->val *= -1;
                        return a;
                    } else {
                        return evaluate(getMul(getInt(-1), a));
                    }

                    break;
                case SIN:
                    break;
                case COS:
                    break;
                case TAN:
                    break;
            }
            break;
    }
}

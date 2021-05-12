#include "sym.h"

#include <stdlib.h>
#include <math.h>

void getInt(Expr* expr, long integer) {
    expr->a = NULL;
    expr->b = NULL;
    expr->val = integer;
    expr->type = INTEGER;
    expr->operator = NONE;
    expr->hl = false;
}

void getOperator(Expr* expr, Expr* a, Expr* b, int operator) {
    expr->a = a;
    expr->b = b;
    expr->val = 0;
    expr->type = OPERATOR;
    expr->operator = operator;
    expr->hl = false;
}

void getAdd(Expr* expr, Expr* a, Expr* b) {
    getOperator(expr, a, b, ADD);
}

void getMul(Expr* expr, Expr* a, Expr* b) {
    getOperator(expr, a, b, MUL);
}

void getPow(Expr* expr, Expr* a, Expr* b) {
    getOperator(expr, a, b, POW);
}

void getSub(Expr* expr, Expr* a, Expr* b) {
    getOperator(expr, a, b, SUB);
}

void getDiv(Expr* expr, Expr* a, Expr* b) {
    getOperator(expr, a, b, DIV);
}

void getFunction(Expr* expr, Expr* a, int name) {
    expr->a = a;
    expr->b = NULL;
    expr->val = 0;
    expr->type = FUNCTION;
    expr->operator = name;
    expr->hl = false;
}

void getNeg(Expr* expr, Expr* a) {
    getFunction(expr, a, NEG);
}

void getSin(Expr* expr, Expr* a) {
    getFunction(expr, a, SIN);
}

void getCos(Expr* expr, Expr* a) {
    getFunction(expr, a, COS);
}

void getTan(Expr* expr, Expr* a) {
    getFunction(expr, a, TAN);
}

void evaluate(Expr* eval, Expr* expr) {
    Expr* a;
    Expr* b;
    Expr* neg;
    Expr* temp;
    Expr* temp2;
    switch (expr->type) {
        case INTEGER:

            // Already evaluated
            getInt(eval, expr->val);

            break;
        case OPERATOR:

            // Needs evaluating
            a = malloc(sizeof(Expr));
            b = malloc(sizeof(Expr));
            evaluate(a, expr->a);
            evaluate(b, expr->b);

            switch (expr->operator) {
                case ADD:
                    if (a->operator > b->operator) {
                        temp = a;
                        a = b;
                        b = temp;
                    }
                    switch (a->operator) {
                        case NONE: // Is an integer
                            switch (b->operator) {
                                case NONE: // Is an integer
                                    getInt(eval, a->val + b->val);
                                    free(a);
                                    free(b);
                                    break;
                                case ADD:
                                    // TODO
                                    getAdd(eval, a, b);
                                    break;
                                case MUL:
                                    // TODO
                                    getAdd(eval, a, b);
                                    break;
                                case POW:
                                    // TODO
                                    getAdd(eval, a, b);
                                    break;
                            }
                            break;
                        case ADD:
                            switch (b->operator) {
                                case ADD:
                                    // TODO
                                    getAdd(eval, a, b);
                                    break;
                                case MUL:
                                    // TODO
                                    getAdd(eval, a, b);
                                    break;
                                case POW:
                                    // TODO
                                    getAdd(eval, a, b);
                                    break;
                            }
                            break;
                        case MUL:
                            switch (b->operator) {
                                case MUL:
                                    // TODO
                                    getAdd(eval, a, b);
                                    break;
                                case POW:
                                    // TODO
                                    getAdd(eval, a, b);
                                    break;
                            }
                            break;
                        case POW: // Both are Pow
                            // TODO
                            getAdd(eval, a, b);
                            break;
                    }
                    break;
                case MUL:
                    if (a->operator > b->operator) {
                        temp = a;
                        a = b;
                        b = temp;
                    }
                    switch (a->operator) {
                        case NONE: // Is an integer
                            switch (b->operator) {
                                case NONE: // Is an integer
                                    getInt(eval, a->val * b->val);
                                    free(a);
                                    free(b);
                                    break;
                                case ADD:
                                    // TODO
                                    getMul(eval, a, b);
                                    break;
                                case MUL:
                                    // TODO
                                    getMul(eval, a, b);
                                    break;
                                case POW:
                                    // TODO
                                    getMul(eval, a, b);
                                    break;
                            }
                            break;
                        case ADD:
                            switch (b->operator) {
                                case ADD:
                                    // TODO
                                    getMul(eval, a, b);
                                    break;
                                case MUL:
                                    // TODO
                                    getMul(eval, a, b);
                                    break;
                                case POW:
                                    // TODO
                                    getMul(eval, a, b);
                                    break;
                            }
                            break;
                        case MUL:
                            switch (b->operator) {
                                case MUL:
                                    // TODO
                                    getMul(eval, a, b);
                                    break;
                                case POW:
                                    // TODO
                                    getMul(eval, a, b);
                                    break;
                            }
                            break;
                        case POW: // Both are Pow
                            // TODO
                            getMul(eval, a, b);
                            break;
                    }
                    break;
                case POW:
                    switch (a->operator) {
                        case NONE: // Is an integer
                            if (a->val == 1) {
                                getInt(eval, 1);
                                free(a);
                                free(b);
                                break;
                            }
                            switch (b->operator) {
                                case NONE: // Is an integer
                                    if (b->val < 0) { // a^(-b) == (a^b)^(-1)
                                        temp = malloc(sizeof(Expr));
                                        getInt(temp, pow(a->val, -b->val));
                                        neg = malloc(sizeof(Expr));
                                        getInt(neg, -1);
                                        getPow(eval, temp, neg);
                                    } else {
                                        getInt(eval, pow(a->val, b->val));
                                    }
                                    free(a);
                                    free(b);
                                    break;
                                case ADD:
                                    // TODO
                                    getPow(eval, a, b);
                                    break;
                                case MUL:
                                    // TODO
                                    getPow(eval, a, b);
                                    break;
                                case POW:
                                    // TODO
                                    getPow(eval, a, b);
                                    break;
                            }
                            break;
                        case ADD:
                            switch (b->operator) {
                                case NONE: // Is an integer
                                    // TODO
                                    if (b->val == 0) {
                                        getInt(eval, 1);
                                        free(a);
                                        free(b);
                                        break;
                                    }
                                    getPow(eval, a, b);
                                    break;
                                case ADD:
                                    // TODO
                                    getPow(eval, a, b);
                                    break;
                                case MUL:
                                    // TODO
                                    getPow(eval, a, b);
                                    break;
                                case POW:
                                    // TODO
                                    getPow(eval, a, b);
                                    break;
                            }
                            break;
                        case MUL:
                            switch (b->operator) {
                                case NONE: // Is an integer
                                    // TODO
                                    if (b->val == 0) {
                                        getInt(eval, 1);
                                        free(a);
                                        free(b);
                                        break;
                                    }
                                    getPow(eval, a, b);
                                    break;
                                case ADD:
                                    // TODO
                                    getPow(eval, a, b);
                                    break;
                                case MUL:
                                    // TODO
                                    getPow(eval, a, b);
                                    break;
                                case POW:
                                    // TODO
                                    getPow(eval, a, b);
                                    break;
                            }
                            break;
                        case POW:
                            switch (b->operator) {
                                case NONE: // Is an integer
                                    // TODO
                                    if (b->val == 0) {
                                        getInt(eval, 1);
                                        free(a);
                                        free(b);
                                        break;
                                    }
                                    getPow(eval, a, b);
                                    break;
                                case ADD:
                                    // TODO
                                    getPow(eval, a, b);
                                    break;
                                case MUL:
                                    // TODO
                                    getPow(eval, a, b);
                                    break;
                                case POW:
                                    // TODO
                                    getPow(eval, a, b);
                                    break;
                            }
                            break;
                    }
                    break;
                case SUB:

                    // a - b = a + (-1) * b
                    neg = malloc(sizeof(Expr));
                    getInt(neg, -1);
                    temp = malloc(sizeof(Expr));
                    getMul(temp, neg, b);
                    temp2 = malloc(sizeof(Expr));
                    getAdd(temp2, a, temp);
                    evaluate(eval, temp2);
                    break;
                case DIV:

                    // a/b = a * b^(-1)
                    neg = malloc(sizeof(Expr));
                    getInt(neg, -1);
                    temp = malloc(sizeof(Expr));
                    getPow(temp, b, neg);
                    temp2 = malloc(sizeof(Expr));
                    getMul(temp2, a, temp);
                    evaluate(eval, temp2);
                    break;
            }
            break;
        case FUNCTION:

            // Needs evaluating
            a = malloc(sizeof(Expr));
            evaluate(a, expr->a);

            switch (expr->operator) {
                case NEG:
                    temp = malloc(sizeof(Expr));
                    neg = malloc(sizeof(Expr));
                    getInt(neg, -1);
                    getMul(temp, neg, a);
                    evaluate(eval, temp);
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
    //display(eval, "\x1b[0m", true);
}

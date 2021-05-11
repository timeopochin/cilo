#include "sym.h"

#include <stdlib.h>

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

/*
Expr* evaluate(Expr* expr) {
    switch (expr->type) {
        case INTEGER:

            // Already evaluated
            getInt(expr, expr->val);

        case OPERATOR:

            // Needs evaluating
            eval->a = evaluate(expr->a);
            eval->b = evaluate(expr->b);

            switch (expr->operator) {
                case ADD:
                    switch (eval->a->operator) {
                        case NONE: // Is an integer
                            switch (eval->b->operator) {
                                case NONE: // Is an integer
                                    break;
                                case ADD:
                                    break;
                                case MUL:
                                    break;
                                case POW:
                                    break;
                            }
                            break;
                        case ADD:
                            switch (eval->b->operator) {
                                case NONE: // Is an integer
                                    break;
                                case ADD:
                                    break;
                                case MUL:
                                    break;
                                case POW:
                                    break;
                            }
                            break;
                        case MUL:
                            switch (eval->b->operator) {
                                case NONE: // Is an integer
                                    break;
                                case ADD:
                                    break;
                                case MUL:
                                    break;
                                case POW:
                                    break;
                            }
                            break;
                        case POW:
                            switch (eval->b->operator) {
                                case NONE: // Is an integer
                                    break;
                                case ADD:
                                    break;
                                case MUL:
                                    break;
                                case POW:
                                    break;
                            }
                            break;
                    }
                    break;
                case MUL:
                    switch (eval->a->operator) {
                        case NONE: // Is an integer
                            switch (eval->b->operator) {
                                case NONE: // Is an integer
                                    break;
                                case ADD:
                                    break;
                                case MUL:
                                    break;
                                case POW:
                                    break;
                            }
                            break;
                        case ADD:
                            switch (eval->b->operator) {
                                case NONE: // Is an integer
                                    break;
                                case ADD:
                                    break;
                                case MUL:
                                    break;
                                case POW:
                                    break;
                            }
                            break;
                        case MUL:
                            switch (eval->b->operator) {
                                case NONE: // Is an integer
                                    break;
                                case ADD:
                                    break;
                                case MUL:
                                    break;
                                case POW:
                                    break;
                            }
                            break;
                        case POW:
                            switch (eval->b->operator) {
                                case NONE: // Is an integer
                                    break;
                                case ADD:
                                    break;
                                case MUL:
                                    break;
                                case POW:
                                    break;
                            }
                            break;
                    }
                    break;
                case POW:
                    switch (eval->a->operator) {
                        case NONE: // Is an integer
                            switch (eval->b->operator) {
                                case NONE: // Is an integer
                                    break;
                                case ADD:
                                    break;
                                case MUL:
                                    break;
                                case POW:
                                    break;
                            }
                            break;
                        case ADD:
                            switch (eval->b->operator) {
                                case NONE: // Is an integer
                                    break;
                                case ADD:
                                    break;
                                case MUL:
                                    break;
                                case POW:
                                    break;
                            }
                            break;
                        case MUL:
                            switch (eval->b->operator) {
                                case NONE: // Is an integer
                                    break;
                                case ADD:
                                    break;
                                case MUL:
                                    break;
                                case POW:
                                    break;
                            }
                            break;
                        case POW:
                            switch (eval->b->operator) {
                                case NONE: // Is an integer
                                    break;
                                case ADD:
                                    break;
                                case MUL:
                                    break;
                                case POW:
                                    break;
                            }
                            break;
                    }
                    break;
                case SUB:

                    // Same as a + (-1) * b

                    break;
                case DIV:

                    // Same as a * b^(-1)

                    break;
            }

            break;
        case FUNCTION:
            break;
    }
}
*/

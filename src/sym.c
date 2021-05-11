#include "sym.h"

Expr* getInt(long integer) {
    Expr* expr;
    expr->a = NULL;
    expr->b = NULL;
    expr->val = integer;
    expr->type = INTEGER;
    expr->operator = NONE;
    expr->hl = false;
    return expr;
}

Expr* getOperator(Expr* a, Expr* b, int operator) {
    Expr* expr;
    expr->a = a;
    expr->b = b;
    expr->val = 0;
    expr->type = OPERATOR;
    expr->operator = operator;
    expr->hl = false;
    return expr;
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
    Expr* expr;
    expr->a = a;
    expr->b = NULL;
    expr->val = 0;
    expr->type = FUNCTION;
    expr->operator = name;
    expr->hl = false;
    return expr;
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

/*
Expr* evaluate(Expr* expr) {
    switch (expr->type) {
        case INTEGER:

            // Already evaluated
            return getInt(expr->val);

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

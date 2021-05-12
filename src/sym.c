#include "sym.h"

#include <stdlib.h>
#include <limits.h>
#include <math.h>

bool equals(Expr* a, Expr* b) {
    if (a->type == INTEGER &&
        b->type == INTEGER) {
        return a->val == b->val;
    } else if (a->operator == b->operator) {
        if (a->type == OPERATOR) {
            return equals(a->a, b->a) && equals(a->b, b->b);
        }
        return equals(a->a, b->a);
    }
    return false;
}

bool before(Expr* a, Expr* b) {
    if (a->type == INTEGER &&
        b->type == INTEGER) {
        return a->val < b->val;
    } else if (a->operator == b->operator) {
        if (equals(a->a, b->a) && a->type == OPERATOR) {
            return before(a->b, b->b);
        }
        return before(a->a, b->a);
    }
    return a->operator < b->operator;
}

long greatestCommonFactor(long a, long b) {
    long temp;
    while (b) {
        temp = a;
        a = b;
        b = temp % b;
    }
    return a;
}

Expr* getUndef() {
    Expr* expr = malloc(sizeof(Expr));
    expr->a = NULL;
    expr->b = NULL;
    expr->val = 0;
    expr->type = UNDEF;
    expr->operator = NONE;
    expr->hl = false;
    return expr;
}

Expr* getInt(long integer) {
    Expr* expr = malloc(sizeof(Expr));
    expr->a = NULL;
    expr->b = NULL;
    expr->val = integer;
    expr->type = INTEGER;
    expr->operator = NONE;
    expr->hl = false;
    return expr;
}

Expr* getOperator(Expr* a, Expr* b, int operator) {
    Expr* expr = malloc(sizeof(Expr));
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
    Expr* expr = malloc(sizeof(Expr));
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

Expr* evaluate(Expr* expr) {
    Expr* a;
    Expr* b;
    Expr* temp; // Used for swapping
    long val; // Used for freeing before returning
    int i; // Used in loops
    switch (expr->type) {
        case UNDEF:

            // Undefined
            return getUndef();

        case INTEGER:

            // Already evaluated
            return getInt(expr->val);

        case OPERATOR:

            // Needs evaluating
            a = evaluate(expr->a);
            b = evaluate(expr->b);

            // Undefined
            if (a->type == UNDEF ||
                b->type == UNDEF) {
                return getUndef();
            }

            switch (expr->operator) {
                case ADD:
                    if (before(a, b)) {
                        temp = a;
                        a = b;
                        b = temp;
                    }

                    // Two integers
                    if (a->type == INTEGER &&
                        b->type == INTEGER) {

                        // Check for overflow/underflow
                        if (((b->val > 0) && (a->val > LLONG_MAX - b->val)) ||
                            ((b->val < 0) && (a->val < LLONG_MIN - b->val))) {
                            return getAdd(a, b);
                        }


                        val = a->val + b->val;
                        free(a);
                        free(b);
                        return getInt(val);
                    }

                    // a/b + c = (a + b*c)/b
                    if (a->operator == DIV) {
                        a->a = getAdd(a->a, getMul(b, a->b));
                        return evaluate(a);
                    } else if (b->operator == DIV) {
                        b->a = getAdd(b->a, getMul(a, b->b));
                        return evaluate(b);
                    }

                    // Was not evaluated
                    return getAdd(a, b);

                case MUL:
                    if (before(a, b)) {
                        temp = a;
                        a = b;
                        b = temp;
                    }

                    // a*1 = a
                    if (a->type == INTEGER &&
                        a->val == 1) {
                        free(a);
                        return b;
                    } else if (b->type == INTEGER &&
                        b->val == 1) {
                        free(b);
                        return a;
                    }

                    // Two integers
                    if (a->type == INTEGER &&
                        b->type == INTEGER) {

                        // Check for overflow/underflow
                        if (((a->val == -1) && (b->val == LLONG_MIN)) ||
                            ((b->val == -1) && (a->val == LLONG_MIN)) ||
                            (a->val > LLONG_MAX / b->val) ||
                            (a->val < LLONG_MIN / b->val)) {
                            return getMul(a, b);
                        }

                        val = a->val * b->val;
                        free(a);
                        free(b);
                        return getInt(val);
                    }

                    // a*(b/c) = (a*b)/c
                    if (a->operator == DIV) {
                        a->a = getMul(a->a, b);
                        return evaluate(a);
                    } else if (b->operator == DIV) {
                        b->a = getMul(b->a, a);
                        return evaluate(b);
                    }

                    // Was not evaluated
                    return getMul(a, b);

                case POW:

                    // 1^b = a^0 = 1
                    if ((a->type == INTEGER &&
                         a->val == 1) ||
                        (b->type == INTEGER &&
                         b->val == 0)) {
                        free(a);
                        free(b);
                        return getInt(1);
                    }

                    // a^(-n) = 1/(a^n)
                    if (b->type == INTEGER &&
                        b->val < 0) {
                        val = b->val;
                        free(b);
                        return evaluate(getDiv(getInt(1), getPow(a, getInt(-val))));
                    }

                    // a^n
                    if (b->type == INTEGER) {
                        temp = a;
                        for (i = 1; i < b->val; i++) {
                            a = getMul(a, temp);
                        }
                        free(b);
                        return evaluate(a);
                    }

                    // Was not evaluated
                    return getPow(a, b);

                case SUB:

                    // Same as a + (-1)*b
                    return evaluate(getAdd(a, getMul(getInt(-1), b)));

                case DIV:

                    // a/1 = a
                    if (b->type == INTEGER &&
                        b->val == 1) {
                        free(b);
                        return a;
                    }

                    // a/0 = Undefined
                    if (b->type == INTEGER &&
                        b->val == 0) {
                        free(a);
                        free(b);
                        return getUndef();
                    }

                    // a/a = 1
                    if (equals(a, b)) {
                        free(a);
                        free(b);
                        return getInt(1);
                    }

                    // an/bn = a/b
                    if (a->type == INTEGER &&
                        b->type == INTEGER) {
                        val = greatestCommonFactor(a->val, b->val);
                        if (val > 1) {
                            a->val /= val;
                            b->val /= val;
                            return evaluate(getDiv(a, b));
                        }
                    }

                    // an/bn == a/b
                    if (a->operator == MUL &&
                        b->operator == MUL) {
                        if (equals(a->a, b->a)) {
                            free(a->a);
                            free(b->a);
                            return evaluate(getDiv(a->b, b->b));
                        } else if (equals(a->b, b->b)) {
                            free(a->b);
                            free(b->b);
                            return evaluate(getDiv(a->a, b->a));
                        }
                    }

                    // a/(b/c) = a*(c/b)
                    if (b->operator == DIV) {
                        temp = b->a;
                        b->a = b->b;
                        b->b = temp;
                        return evaluate(getMul(a, b));
                    }

                    // Was not evaluated
                    return getDiv(a, b);

            }
            break;
        case FUNCTION:

            // Needs evaluating
            a = evaluate(expr->a);

            // Undefined
            if (a->type == UNDEF) {
                return getUndef();
            }

            switch (expr->operator) {
                case NEG:

                    // Negate
                    return evaluate(getMul(getInt(-1), a));

                case SIN:

                    // Was not evaluated
                    return getSin(a);

                case COS:

                    // Was not evaluated
                    return getCos(a);

                case TAN:

                    // Was not evaluated
                    return getTan(a);

            }
            break;
    }
}

double calculate(Expr* expr) {
    switch (expr->type) {
        case INTEGER:
            return expr->val;
        case OPERATOR:
            switch (expr->operator) {
                case ADD:
                    return calculate(expr->a) + calculate(expr->b);
                case MUL:
                    return calculate(expr->a)*calculate(expr->b);
                case POW:
                    return pow(calculate(expr->a), calculate(expr->b));
                case SUB:
                    return calculate(expr->a) - calculate(expr->b);
                case DIV:
                    return calculate(expr->a)/calculate(expr->b);
            }
            break;
        case FUNCTION:
            switch (expr->operator) {
                case NEG:
                    return -calculate(expr->a);
                case SIN:
                    return sin(calculate(expr->a));
                case COS:
                    return cos(calculate(expr->a));
                case TAN:
                    return tan(calculate(expr->a));
            }
            break;
    }
    return 0;
}

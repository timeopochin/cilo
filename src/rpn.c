#include "rpn.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "sym.h"

#define OPCHARS "+-*/^"
#define FUNCCHARS "nsct"

int exprFromRPN(Expr** (exprs), Expr*** stack, char* rpn) {

    // Create a stack
    int exprCount = 0;
    int maxSize = 0;
    int finalSize = 0;
    bool valueStarted = false;
    int i = 0;
    char c = rpn[i];
    do {
        if (isdigit(c)) {
            valueStarted = true;
        } else if (valueStarted) {
            valueStarted = false;
            finalSize++;
            exprCount++;
        }
        if (strchr(OPCHARS, c) != NULL) {
            finalSize--;
            exprCount++;
        } else if (strchr(FUNCCHARS, c) != NULL) {
            exprCount++;
        }
        if (finalSize > maxSize) {
            maxSize = finalSize;
        }
        i++;
        c = rpn[i];
        if (c == 0 && valueStarted) {
            i--;
            c = ' ';
        }
    } while (c != 0);
    (*stack) = malloc(sizeof(Expr*)*maxSize);
    (*exprs) = malloc(sizeof(Expr)*exprCount);

    // Execute RPN
    valueStarted = false;
    long value = 0;
    int exprPos = 0;
    int pos = 0;
    i = 0;
    c = rpn[i];
    do {
        if (isdigit(c)) {
            value *= 10;
            value += c - '0';
            valueStarted = true;
        } else if (valueStarted) {

            // Push an integer
            (*exprs)[exprPos].a = NULL;
            (*exprs)[exprPos].b = NULL;
            (*exprs)[exprPos].val = value;
            (*exprs)[exprPos].type = INTEGER;
            (*exprs)[exprPos].operator = NONE;
            (*exprs)[exprPos].hl = false;
            (*stack)[pos] = &(*exprs)[exprPos];
            exprPos++;
            pos++;
            value = 0;
            valueStarted = false;
        }
        if (strchr(OPCHARS, c) != NULL) {

            // Push an operator
            if (pos < 2) {
                return 0;
            }
            (*exprs)[exprPos].a = (*stack)[pos - 2];
            (*exprs)[exprPos].b = (*stack)[pos - 1];
            (*exprs)[exprPos].val = 0;
            (*exprs)[exprPos].type = OPERATOR;
            (*exprs)[exprPos].hl = false;
            switch (c) {
                case '+':
                    (*exprs)[exprPos].operator = ADD;
                    break;
                case '-':
                    (*exprs)[exprPos].operator = SUB;
                    break;
                case '*':
                    (*exprs)[exprPos].operator = MUL;
                    break;
                case '/':
                    (*exprs)[exprPos].operator = DIV;
                    break;
                case '^':
                    (*exprs)[exprPos].operator = POW;
                    break;
                default:
                    break;
            }
            (*stack)[pos - 1] = NULL;
            (*stack)[pos - 2] = &(*exprs)[exprPos];
            pos--;
            exprPos++;
        } else if (strchr(FUNCCHARS, c) != NULL) {

            // Push a function
            if (pos < 1) {
                return 0;
            }
            (*exprs)[exprPos].a = (*stack)[pos - 1];
            (*exprs)[exprPos].b = NULL;
            (*exprs)[exprPos].val = 0;
            (*exprs)[exprPos].type = FUNCTION;
            (*exprs)[exprPos].hl = false;
            switch (c) {
                case 'n':
                    (*exprs)[exprPos].operator = NEG;
                    break;
                case 's':
                    (*exprs)[exprPos].operator = SIN;
                    break;
                case 'c':
                    (*exprs)[exprPos].operator = COS;
                    break;
                case 't':
                    (*exprs)[exprPos].operator = TAN;
                    break;
                default:
                    break;
            }
            (*stack)[pos - 1] = &(*exprs)[exprPos];
            exprPos++;
        } else if (c == 'h') {
            (*stack)[pos - 1]->hl = true;
        }
        i++;
        c = rpn[i];
        if (c == 0 && valueStarted) {
            i--;
            c = ' ';
        }
    } while (c != 0);

    return finalSize;
}

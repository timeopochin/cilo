#include "rpn.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "sym.h"

#define OPCHARS "+-*/^"
#define FUNCCHARS "nsct"

int exprFromRPN(Expr*** stack, char* rpn) {

    // Create a (*stack)
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
            maxSize++;
            exprCount++;
        }
        if (strchr(OPCHARS, c) != NULL) {
            finalSize--;
            exprCount++;
        } else if (strchr(FUNCCHARS, c) != NULL) {
            exprCount++;
        }
        i++;
        c = rpn[i];
        if (c == 0 && valueStarted) {
            i--;
            c = ' ';
        }
    } while (c != 0);
    (*stack) = malloc(sizeof(Expr*)*maxSize);
    //Expr* exprs = malloc(sizeof(Expr)*exprCount);
    Expr** exprs = malloc(sizeof(Expr*)*exprCount);

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
            exprs[exprPos] = getInt(value);
            (*stack)[pos] = exprs[exprPos];
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
            switch (c) {
                case '+':
                    exprs[exprPos] = getAdd((*stack)[pos - 2], (*stack)[pos - 1]);
                    break;
                case '-':
                    exprs[exprPos] = getSub((*stack)[pos - 2], (*stack)[pos - 1]);
                    break;
                case '*':
                    exprs[exprPos] = getMul((*stack)[pos - 2], (*stack)[pos - 1]);
                    break;
                case '/':
                    exprs[exprPos] = getDiv((*stack)[pos - 2], (*stack)[pos - 1]);
                    break;
                case '^':
                    exprs[exprPos] = getPow((*stack)[pos - 2], (*stack)[pos - 1]);
                    break;
            }
            (*stack)[pos - 1] = NULL;
            (*stack)[pos - 2] = exprs[exprPos];
            pos--;
            exprPos++;
        } else if (strchr(FUNCCHARS, c) != NULL) {

            // Push a function
            if (pos < 1) {
                return 0;
            }
            switch (c) {
                case 'n':
                    exprs[exprPos] = getNeg((*stack)[pos - 1]);
                    break;
                case 's':
                    exprs[exprPos] = getSin((*stack)[pos - 1]);
                    break;
                case 'c':
                    exprs[exprPos] = getCos((*stack)[pos - 1]);
                    break;
                case 't':
                    exprs[exprPos] = getTan((*stack)[pos - 1]);
                    break;
                default:
                    break;
            }
            (*stack)[pos - 1] = exprs[exprPos];
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

    free(exprs);
    return finalSize;
}

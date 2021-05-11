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
    Expr* exprs = malloc(sizeof(Expr)*exprCount);

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
            getInt(&exprs[exprPos], value);
            (*stack)[pos] = &exprs[exprPos];
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
                    getAdd(&exprs[exprPos], (*stack)[pos - 2], (*stack)[pos - 1]);
                    break;
                case '-':
                    getSub(&exprs[exprPos], (*stack)[pos - 2], (*stack)[pos - 1]);
                    break;
                case '*':
                    getMul(&exprs[exprPos], (*stack)[pos - 2], (*stack)[pos - 1]);
                    break;
                case '/':
                    getDiv(&exprs[exprPos], (*stack)[pos - 2], (*stack)[pos - 1]);
                    break;
                case '^':
                    getPow(&exprs[exprPos], (*stack)[pos - 2], (*stack)[pos - 1]);
                    break;
            }
            (*stack)[pos - 1] = NULL;
            (*stack)[pos - 2] = &exprs[exprPos];
            pos--;
            exprPos++;
        } else if (strchr(FUNCCHARS, c) != NULL) {

            // Push a function
            if (pos < 1) {
                return 0;
            }
            switch (c) {
                case 'n':
                    getNeg(&exprs[exprPos], (*stack)[pos - 1]);
                    break;
                case 's':
                    getSin(&exprs[exprPos], (*stack)[pos - 1]);
                    break;
                case 'c':
                    getCos(&exprs[exprPos], (*stack)[pos - 1]);
                    break;
                case 't':
                    getTan(&exprs[exprPos], (*stack)[pos - 1]);
                    break;
                default:
                    break;
            }
            (*stack)[pos - 1] = &exprs[exprPos];
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

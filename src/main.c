#include <ctype.h>
#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "rpn.h"
#include "pretty.h"

int main() {

    // Set locale for correct Unicode output
    setlocale(LC_CTYPE, "");

    // RPN
    char* rpn = "1 2 3 / s 3 + - 7 / 2 ^ n 6 t + c";
    wprintf(L"%s\n", rpn);

    // Get the expression tree
    Expr* exprs;
    Expr** stack;
    int exprCount = exprFromRPN(&exprs, &stack, rpn);

    // Display pretty output
    wchar_t format[11] = L"\x1b[0;30;42m";
    display(&(*stack[exprCount - 1]), format, true);

    free(exprs);
    free(stack);

    return 0;
}

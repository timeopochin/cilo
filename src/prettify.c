#include <ctype.h>
#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "rpn.h"
#include "pretty.h"

#define BLACK 0
#define RED 1
#define GREEN 2
#define YELLOW 3
#define BLUE 4
#define MAGENTA 5
#define CYAN 6
#define WHITE 7

void usage();

int main(int argc, char* argv[]) {

    if (argc == 1) {
        usage();
        return 0;
    }

    // Set locale for correct Unicode output
    setlocale(LC_CTYPE, "");

    // Set formating
    wchar_t formating[11];
    int fg = 7;
    int bg = 0;

    int i;
    for (i = 1; i < argc; i++) {

        // Set colours
        if (!strcmp(argv[i], "-fg")) {
            if (i == argc - 1) {
                usage();
                return 1;
            }
            if (!strcmp(argv[i + 1], "black")) {
                fg = BLACK;
            } else if (!strcmp(argv[i + 1], "red")) {
                fg = RED;
            } else if (!strcmp(argv[i + 1], "green")) {
                fg = GREEN;
            } else if (!strcmp(argv[i + 1], "yellow")) {
                fg = YELLOW;
            } else if (!strcmp(argv[i + 1], "blue")) {
                fg = BLUE;
            } else if (!strcmp(argv[i + 1], "magenta")) {
                fg = MAGENTA;
            } else if (!strcmp(argv[i + 1], "cyan")) {
                fg = CYAN;
            } else if (!strcmp(argv[i + 1], "white")) {
                fg = WHITE;
            } else {
                wprintf(L"'%s' is not a valid colour!", argv[i + 1]);
                usage();
                return 1;
            }
            i++;
        } else if (!strcmp(argv[i], "-bg")) {
            if (i == argc - 1) {
                usage();
                return 1;
            }
            if (!strcmp(argv[i + 1], "black")) {
                bg = BLACK;
            } else if (!strcmp(argv[i + 1], "red")) {
                bg = RED;
            } else if (!strcmp(argv[i + 1], "green")) {
                bg = GREEN;
            } else if (!strcmp(argv[i + 1], "yellow")) {
                bg = YELLOW;
            } else if (!strcmp(argv[i + 1], "blue")) {
                bg = BLUE;
            } else if (!strcmp(argv[i + 1], "magenta")) {
                bg = MAGENTA;
            } else if (!strcmp(argv[i + 1], "cyan")) {
                bg = CYAN;
            } else if (!strcmp(argv[i + 1], "white")) {
                bg = WHITE;
            } else {
                wprintf(L"'%s' is not a valid colour!", argv[i + 1]);
                usage();
                return 1;
            }
            i++;
        } else {
            wprintf(L"\n");

            // Set the colours
            swprintf(formating, 11, L"\x1b[0;3%d;4%dm", fg, bg);

            // Get the expression tree
            Expr* exprs;
            Expr** stack;
            int exprCount = exprFromRPN(&exprs, &stack, argv[i]);
            if (!exprCount) {
                wprintf(L"\x1b[41;38mStack is empty!\x1b[0m\n");
                return 1;
            }

            // Display pretty output
            display(&(*stack[exprCount - 1]), formating, true);

            free(exprs);
            free(stack);
        }
    }
    wprintf(L"\n");

    return 0;
}

void usage() {
    wprintf(L"USAGE: prettify 'expr_1' 'expr_2' ...\n");
}
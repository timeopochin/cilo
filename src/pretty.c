#include "pretty.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

Pretty brackets(Expr* expr) {

    // Calculate the size
    Pretty a = pretty(expr);
    Pretty p;
    p.width = a.width + 2;
    p.height = a.height;
    p.align = p.height/2;
    p.text = malloc(sizeof(wchar_t)*p.width*p.height);

    int column;
    if (p.height == 1) {

        // Height of 1
        p.text[0] = L'(';
        p.text[p.width - 1] = L')';
        for (column = 0; column < a.width; column++)
            p.text[column + 1] = a.text[column];
    } else {

        // Set corners
        p.text[0] = L'⎛';
        p.text[p.width - 1] = L'⎞';
        p.text[p.width*(p.height - 1)] = L'⎝';
        p.text[p.width*p.height - 1] = L'⎠';
        int row;
        for (row = 0; row < p.height; row++) {
            if (row != 0 && row != p.height - 1) {
                p.text[p.width*row] = L'⎜';
                p.text[p.width*(row + 1) - 1] = L'⎟';
            }
            for (column = 0; column < a.width; column++) {
                p.text[p.width*row + column + 1] = a.text[a.width*row + column];
            }
        }
    }

    // Set highlight
    if (a.hl) {
        p.hl = true;
        p.hlX = a.hlX + 1;
        p.hlY = a.hlY;
        p.hlWidth = a.hlWidth;
        p.hlHeight = a.hlHeight;
    } else {
        p.hl = false;
    }

    return p;
}

void horizontalPretty(Expr* expr, Pretty* p, wchar_t separator) {
    Pretty a;
    Pretty b;

    // Set needed brackets
    if (expr->operator == MUL &&
        (expr->a->operator == ADD ||
         expr->a->operator == SUB)) {
        a = brackets(expr->a);
    } else {
    a = pretty(expr->a);
    }
    if ((expr->operator == ADD && expr->b->operator == SUB) ||
        ((expr->operator == MUL || expr->operator == SUB) &&
         (expr->b->operator == ADD || expr->b->operator == SUB))) {
        b = brackets(expr->b);
    } else {
        b = pretty(expr->b);
    }

    // Calculate the new size
    p->width = a.width + b.width + 3;
    p->align = a.align > b.align ? a.align : b.align;
    p->height = p->align;
    p->height += a.height - a.align >= b.height - b.align ? a.height - a.align : b.height - b.align;
    p->text = malloc(sizeof(wchar_t)*p->width*p->height);

    // Set characters
    int row;
    int column;
    for (row = 0; row < p->height; row++) {

        // a
        for (column = 0; column < a.width; column++) {
            if (row >= p->align - a.align && row < p->align - a.align + a.height) {
                p->text[p->width*row + column] = a.text[a.width*(row - p->align + a.align) + column];
            } else {
                p->text[p->width*row + column] = L' ';
            }
        }

        // Separator
        for (column = a.width; column < a.width + 3; column++) {
            if (row == p->align && column == a.width + 1) {
                p->text[p->width*row + column] = separator;
            } else {
                p->text[p->width*row + column] = L' ';
            }
        }

        // b
        for (column = 0; column < b.width; column++) {
            if (row >= p->align - b.align && row < p->align - b.align + b.height) {
                p->text[p->width*row + column + a.width + 3] = b.text[b.width*(row - p->align + b.align) + column];
                //p->text[p->width*row + column + a.width + 3] = L'B';
            } else {
                p->text[p->width*row + column + a.width + 3] = L' ';
            }
        }
    }

    // Set highlight
    if (a.hl) {
        p->hl = true;
        p->hlX = a.hlX;
        p->hlY = p->align - a.align + a.hlY;
        p->hlWidth = a.hlWidth;
        p->hlHeight = a.hlHeight;
    } else if (b.hl) {
        p->hl = true;
        p->hlX = a.width + 3 + b.hlX;
        p->hlY = p->align - b.align + b.hlY;
        p->hlWidth = b.hlWidth;
        p->hlHeight = b.hlHeight;
    } else {
        p->hl = false;
    }
}

void functionPretty(Expr* expr, Pretty* p, int length, wchar_t* name) {

    // Set needed brackets
    Pretty a = brackets(expr->a);

    p->width = a.width + length;
    p->height = a.height;
    p->align = a.align;
    p->text = malloc(sizeof(wchar_t)*p->width*p->height);

    // Function name
    int row;
    int column;
    for (row = 0; row < p->height; row++) {
        for (column = 0; column < length; column++) {
            if (row == p->align) {
                p->text[p->width*row + column] = name[column];
            } else {
                p->text[p->width*row + column] = ' ';
            }
        }
    }

    // a
    for (row = 0; row < a.height; row++) {
        for (column = 0; column < a.width; column++) {
            p->text[p->width*row + column + length] = a.text[a.width*row + column];
        }
    }

    // Set highlight
    if (a.hl) {
        p->hl = true;
        p->hlX = 1 + a.hlX;
        p->hlY = a.hlY;
        p->hlWidth = a.hlWidth;
        p->hlHeight = a.hlHeight;
    } else {
        p->hl = false;
    }
}

Pretty pretty(Expr* expr) {
    Pretty p;
    Pretty a;
    Pretty b;
    int row;
    int column;
    switch (expr->type) {

        // Integer
        case INTEGER:
            p.text = malloc(sizeof(wchar_t)*20);
            p.width = swprintf(p.text, 20, L"%ld", expr->val);
            p.height = 1;
            p.align = 0;
            p.hl = expr->hl;
            break;

        case OPERATOR:
            switch (expr->operator) {
                case ADD:
                    horizontalPretty(expr, &p, L'+');
                    break;
                case MUL:
                    horizontalPretty(expr, &p, L'•');
                    break;
                case POW:

                    // Set needed brackets
                    a = expr->a->type != NONE ? brackets(expr->a) : pretty(expr->a);
                    b = pretty(expr->b);

                    // Calculate size
                    p.width = a.width + b.width;
                    p.height = a.height + b.height;
                    p.align = a.align + b.height;
                    p.text = malloc(sizeof(wchar_t)*p.width*p.height);

                    // a
                    for (row = 0; row < a.height; row++) {
                        for (column = 0; column < a.width; column++) {
                            p.text[p.width*(row + b.height) + column] = a.text[a.width*row + column];
                        }
                    }

                    // b
                    for (row = 0; row < b.height; row++) {
                        for (column = 0; column < b.width; column++) {
                            p.text[p.width*row + column + a.width] = b.text[b.width*row + column];
                        }
                    }

                    // Spaces
                    for (row = 0; row < b.height; row++) {
                        for (column = 0; column < a.width; column++) {
                            p.text[p.width*row + column] = L' ';
                        }
                    }
                    for (row = b.height; row < p.height; row++) {
                        for (column = a.width; column < p.width; column++) {
                            p.text[p.width*row + column] = L' ';
                        }
                    }

                    // Set highlight
                    if (a.hl) {
                        p.hl = true;
                        p.hlX = a.hlX;
                        p.hlY = b.height + a.hlY;
                        p.hlWidth = a.hlWidth;
                        p.hlHeight = a.hlHeight;
                    } else if (b.hl) {
                        p.hl = true;
                        p.hlX = a.width + b.hlX;
                        p.hlY = b.hlY;
                        p.hlWidth = b.hlWidth;
                        p.hlHeight = b.hlHeight;
                    } else {
                        p.hl = false;
                    }

                    break;
                case SUB:
                    horizontalPretty(expr, &p, L'-');
                    break;

                // Fraction
                case DIV:

                    // Set needed brackets
                    a = expr->a->operator == DIV ? brackets(expr->a) : pretty(expr->a);
                    b = expr->b->operator == DIV ? brackets(expr->b) : pretty(expr->b);

                    p.width  = a.width > b.width ? a.width : b.width;
                    p.height = a.height + b.height + 1;
                    p.align = a.height;
                    p.text = malloc(sizeof(wchar_t)*p.width*p.height);

                    // Set the dividing line
                    for (column = 0; column < p.width; column++) {
                        p.text[p.width*a.height + column] = L'─';
                    }

                    // Set offsets
                    int aOffset = (p.width - a.width) / 2;
                    int bOffset = (p.width - b.width) / 2;
                    for (row = 0; row < a.height; row++) {
                        for (column = 0; column < aOffset; column++) {
                            p.text[p.width*row + column] = ' ';
                            p.text[p.width*(row + 1) - column - 1] = ' ';
                        }
                        if (p.width - a.width % 2) {
                            p.text[p.width*(row + 1) - aOffset - 1] = ' ';
                        }
                    }
                    for (row = a.height + 1; row < p.height; row++) {
                        for (column = 0; column < bOffset; column++) {
                            p.text[p.width*row + column] = ' ';
                            p.text[p.width*(row + 1) - column - 1] = ' ';
                        }
                        if (p.width - b.width % 2) {
                            p.text[p.width*(row + 1) - bOffset - 1] = ' ';
                        }
                    }

                    // Set sub expressions
                    for (row = 0; row < a.height; row++) {
                        for (column = 0; column < a.width; column++) {
                            p.text[p.width*row + column + aOffset] = a.text[a.width*row + column];
                        }
                    }
                    for (row = 0; row < b.height; row++) {
                        for (column = 0; column < b.width; column++) {
                            p.text[p.width*(a.height + 1 + row) + column + bOffset] = b.text[b.width*row + column];
                        }
                    }

                    // Set highlight
                    if (a.hl) {
                        p.hl = true;
                        p.hlX = aOffset + a.hlX;
                        p.hlY = a.hlY;
                        p.hlWidth = a.hlWidth;
                        p.hlHeight = a.hlHeight;
                    } else if (b.hl) {
                        p.hl = true;
                        p.hlX = bOffset + b.hlX;
                        p.hlY = b.height + 1 + b.hlY;
                        p.hlWidth = b.hlWidth;
                        p.hlHeight = b.hlHeight;
                    } else {
                        p.hl = false;
                    }

                    break;
                free(a.text);
                free(b.text);
            };
            break;
        case FUNCTION:
            switch (expr->operator) {
                case NEG:

                    // Set needed brackets
                    if (expr->a->operator == ADD ||
                        expr->a->operator == SUB ||
                        expr->a->operator == MUL) {
                        a = brackets(expr->a);
                    } else {
                        a = pretty(expr->a);
                    }

                    p.width = a.width + 2;
                    p.height = a.height;
                    p.align = a.align;
                    p.text = malloc(sizeof(wchar_t)*p.width*p.height);

                    // Minus sign
                    for (row = 0; row < p.height; row++) {
                        p.text[p.width*row] = ' ';
                        p.text[p.width*row + 1] = ' ';
                    }
                    p.text[p.width*p.align] = '-';

                    // a
                    for (row = 0; row < a.height; row++) {
                        for (column = 0; column < a.width; column++) {
                            p.text[p.width*row + column + 2] = a.text[a.width*row + column];
                        }
                    }

                    // Set highlight
                    if (a.hl) {
                        p.hl = true;
                        p.hlX = 1 + a.hlX;
                        p.hlY = a.hlY;
                        p.hlWidth = a.hlWidth;
                        p.hlHeight = a.hlHeight;
                    } else {
                        p.hl = false;
                    }

                    break;
                case SIN:
                    functionPretty(expr, &p, 3, L"sin");
                    break;
                case COS:
                    functionPretty(expr, &p, 3, L"cos");
                    break;
                case TAN:
                    functionPretty(expr, &p, 3, L"tan");
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    };

    // Set highlight
    if (expr->hl) {
        p.hl = true;
        p.hlX = 0;
        p.hlY = 0;
        p.hlWidth = p.width;
        p.hlHeight = p.height;
    }
    return p;
}

void display(Expr* expr, wchar_t* format, bool displayInline) {
    wprintf(format);
    int row;
    int column;
    int i;
    Pretty p = pretty(expr);
    for (row = 0; row < p.height; row++) {
        for (column = 0; column < p.width; column++) {
            if (p.hl && column == p.hlX && row >= p.hlY && row < p.hlY + p.hlHeight) {
                wprintf(L"\x1b[7m");
            }
            fputwc(p.text[p.width*row + column], stdout);
            if (p.hl && column == p.hlX + p.hlWidth - 1 && row >= p.hlY && row < p.hlY + p.hlHeight) {
                wprintf(format);
            }
        }
        if (displayInline) {
            wprintf(L"\x1b[0m\n%S", format);
        } else {
            wprintf(L"\x1b[1B\x1b[%dD", p.width);
        }
    }
    wprintf(L"\x1b[0m");
    free(p.text);
}

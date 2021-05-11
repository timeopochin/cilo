#ifndef PRETTY_H
#define PRETTY_H

#include "sym.h"

#include <wchar.h>

typedef struct Pretty Pretty;
struct Pretty {
    int width;
    int height;
    int align;
    wchar_t* text;

    // Used to highlight a section
    bool hl;
    int hlX;
    int hlY;
    int hlWidth;
    int hlHeight;
};

Pretty brackets(Expr* expr);

void horizontalPretty(Expr* expr, Pretty* p, wchar_t separator);

void functionPretty(Expr* expr, Pretty* p, int length, wchar_t* name);

Pretty pretty(Expr* expr);

void display(Expr* expr, wchar_t* format, bool displayInline);

#endif


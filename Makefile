CC=cc
LDFLAGS=

INCDIR=include
SRCDIR=src
OBJDIR=build
EXEDIR=bin

INCLUDE=-I$(INCDIR)
HEAD=$(wildcard $(INCDIR)/*.h)
SRC=$(HEAD:$(INCDIR)/%.h=$(SRCDIR)/%.c)
OBJ=$(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

PRETTIFY=$(EXEDIR)/prettify

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(INCLUDE) -c $< -o $@

$(PRETTIFY): $(OBJ) $(OBJDIR)/prettify.o
	@mkdir -p $(@D)
	$(CC) $(LDFLAGS) -o $@ $^

.PHONY: all clean

clean:
	@rm -rf $(OBJDIR)
	@rm -rf $(EXEDIR)

all: $(PRETTIFY)

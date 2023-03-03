CC      := cc
CFLAGS  :=
LDFLAGS := 

SRCDIR  := source
OBJDIR  := objects

EXECUTABLE := preprocessor

SOURCES := $(SRCDIR)/main.c $(SRCDIR)/output/output.c $(SRCDIR)/parser/util.c $(SRCDIR)/parser/parser.c $(SRCDIR)/parser/macros.c $(SRCDIR)/table/table.c
OBJECTS := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))
DEPS    := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.d,$(SOURCES))

.PHONY: all clean

all: $(EXECUTABLE)

-include $(DEPS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(@D)
	$(CC) $(LDFLAGS) $^ -o $@

clean:
	$(RM) -r $(OBJDIR) .
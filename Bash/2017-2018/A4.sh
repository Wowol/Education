LD := gcc
OFLAGS := -c
PREPROCFLAGS := -MP -MM

srcdir := src
builddir := build
outdir := bin

$(shell mkdir -p "$(outdir)")
$(shell mkdir -p "$(builddir)")

$(shell cd $(srcdir) && find . -type d -print0 | xargs -0 -I {} sh -c "mkdir -p '../$(builddir)/{}'")

SOURCES := $(shell find * -type f -name "*.c")
OBJS := $(SOURCES:$(srcdir)/%.c=$(builddir)/%.o)
DEPS := $(SOURCES:$(srcdir)/%.c=$(builddir)/%.d)
TARGET := $(outdir)/main

all: $(TARGET)

$(TARGET) : $(OBJS)
	@echo "Building $@"	
	@$(LD) $+ -o $@

$(builddir)/%.o : $(srcdir)/%.c $(builddir)/%.d
	@echo "Building $@"
	@$(LD) $< $(OFLAGS) -o $@

$(builddir)/%.d : $(srcdir)/%.c
	@$(LD) $< $(PREPROCFLAGS) | sed -r 's:(.*)(\.o):$(@D)/\1.o $@:g' > $@

clean:
	@rm -rf $(DEPS)
	@rm -rf $(OBJS)
	@rm -rf $(TARGET)
	@find $(outdir) -type d -empty -delete  2>/dev/null || true
	@find $(builddir) -type d -empty -delete 2>/dev/null || true

.SECONDARY : $(OBJS) $(DEPS)
.PHONY: clean all
-include $(DEPS)
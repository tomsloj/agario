CC := g++ 
SRCDIR := src
BUILDDIR := build
TARGET := bin/runner
OUT := bin

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -g -Wall -pedantic -std=c++11 -O3
INC := -I include



$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB) -lsfml-graphics -lsfml-window -lsfml-system

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)

.PHONY: clean

$(shell   mkdir -p $(OUT))

.PHONY: test
test:
	@g++ -o test/testfile test/test.cpp src/GlobalValues.cpp -lboost_unit_test_framework -lsfml-graphics -lsfml-window -lsfml-system
	@./test/testfile --log_level=test_suite 

TARGET = libsaori.so

DIST ?= ./bin
ODIR ?= ./obj
SDIR ?= ./src

SRCS := $(shell find $(SDIR) -name *.cpp -or -name *.c)
OBJS := $(SRCS:$(SDIR)/%.cpp=$(ODIR)/%.o)

INCLUDE = $(addprefix -I,$(shell find $(SDIR) -type d))  -I/Library/Developer/CommandLineTools/usr/include/c++/v1/ -I/Library/Developer/CommandLineTools/usr/lib/clang/7.0.2/include/

LD := g++
LDFLAGS ?= -shared
AS ?= as
ASFLAGS ?=
CXX = g++
CXXFLAGS = -std=c++14 -O1 -Wall -fPIC


all : $(DIST)/$(TARGET)

# linker: object[] -> so
$(DIST)/$(TARGET): $(OBJS)
	if [ ! -d $(DIST) ]; then mkdir $(DIST); fi
	$(LD) $(LDFLAGS) $(LDLIBS) $^ -o $@
	#em++ -O1        $(^:%.o=%.bc) -o $@.js
	#tree .

# assembler: source -> (object, LLVM BC)
$(ODIR)/%.o: $(SDIR)/%.cpp
	if [ ! -d $(ODIR) ]; then mkdir $(ODIR); fi
	$(CXX)  $(CXXFLAGS) -MMD -MP      $(INCLUDE) -c $< -o $@
	#$(CXX)  $(CXXFLAGS) -S            $(INCLUDE) -c $< -o $@.s
	#em++    $(CXXFLAGS) -MMD -MP      $(INCLUDE) -c $< -o $(@:%.o=%.bc)
	#llvm-dis $(@:%.o=%.bc) -o $(@:%.o=%.bc).ll
	#tree .


.PHONY: clean
clean:
	$(RM) -rf $(ADIR) $(ODIR) $(DIST)

-include $(DEPS)

BINDIR := .
SRCDIR := .

CXXFLAGS = -O2 -std=c++17

.PHONY: all clean test
all: build

TESTSRC := $(wildcard $(SRCDIR)/*_test.cpp)
TESTTARGET := $(patsubst $(SRCDIR)/%.cpp, $(BINDIR)/%, $(TESTSRC))

SHELL := /bin/bash

build: $(TESTTARGET)

test: $(TESTTARGET)
	rm -f test.log
	for exe in $(TESTTARGET) ; do \
		$$exe >> test.log ; \
	done

$(BINDIR)/%_test : $(SRCDIR)/%_test.cpp
	$(CXX) $^ $(CXXFLAGS) -o $@

clean:
	rm $(BINDIR)/*_test

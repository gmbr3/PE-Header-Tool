.PHONY: all clean test

all: test

OBJS = main.o file_header.o optional_header.o

pe_header_tool: $(OBJS)
	$(CXX) $(LDFLAGS) $^ $(LOADLIBES) $(LDLIBS) -o $@

clean:
	rm -f $(OBJS) pe_header_tool

test: pe_header_tool
	./pe_header_tool


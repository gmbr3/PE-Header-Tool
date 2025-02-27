.PHONY: all clean

all: pe_header_tool

OBJS = main.o

pe_header_tool: $(OBJS)
	$(CXX) $(LDFLAGS) $^ $(LOADLIBES) $(LDLIBS) -o $@

clean:
	rm -f $(OBJS) pe_header_tool


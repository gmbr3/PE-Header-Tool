.PHONY: all clean test

all: test

UIC ?= /usr/libexec/qt6/uic
MOC ?= /usr/libexec/qt6/moc

PC := pkg-config

OBJS = main.o file_header.o optional_header.o ui/mainwindow.o ui/fileselection.o ui/fhinformation.o

CXXFLAGS += $(shell $(PC) --cflags Qt6Widgets)
LDFLAGS += $(shell $(PC) --libs Qt6Widgets)

ui/mainwindow.cpp: ui/mainwindow_ui.ui.h ui/mainwindow.moc.h
ui/fileselection.cpp: ui/fileselection_ui.ui.h ui/fileselection.moc.h
ui/fhinformation.cpp: ui/fhinformation_ui.ui.h ui/fhinformation.moc.h

pe_header_tool: $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ $(LOADLIBES) $(LDLIBS) -o $@

%.ui.h: %.ui
	$(UIC) $< -o $@

%.moc.h: %.h
	$(MOC) $< -o $@

clean:
	rm -f $(OBJS) pe_header_tool ui/*.ui.h ui/*.moc.h

test: pe_header_tool
	./pe_header_tool


.PHONY: all clean

HX_SRCs = $(shell hx-srcs.sh)
CXX_SRCs = $(filter %.cpp,$(shell hx-files.sh $(HX_SRCs)))
CXXFLAGS += -Wall -std=c++17

all: hx_run

hx_run: $(HX_SRCs)
	@echo HX
	@which hx 2> /dev/null && hx || true
	@date >$@
	@make --no-print-directory dox

dox: $(CXX_SRCs)
	@echo C++ $@
	@$(CXX) $(CXXFLAGS) $^ -lstdc++fs -o $@

$(CXX_SRCs): hx_run

clean:
	@echo RM
	@rm -f $(CXX_SRCs) hx_run dox


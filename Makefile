.PHONY: clean

HX_SRCs = $(shell hx-srcs.sh)
CXX_SRCs = $(shell hx-files.sh $(HX_SRCs))
CXXFLAGS += -Wall -std=c++17

hx_run: $(HX_SRCs)
	@echo HX
	@hx
	@date >$@
	@make --no-print-directory dox

dox: $(CXX_SRCs)
	@echo C++ $@
	@$(CXX) $^ -o $@

$(CXX_SRCs): hx_run

clean:
	@echo RM
	@rm -f $(CXX_SRCs) hx_run dox


CC = gcc -std=c99
CXX = g++ -std=c++17

LONG = 0
SANITIZE = 1
SRAND = 1

O0 = 0
O1 = 0
O2 = 0
O3 = 0
Og = 0
Ofast = 0

CFLAGS  = -Ictl
CFLAGS += -Wall -Wextra -Wpedantic -Wfatal-errors -Wshadow
CFLAGS += -march=native
CFLAGS += -g

ifeq (1, $(LONG))
CFLAGS += -Werror
CFLAGS += -DLONG
endif

ifeq (1, $(SANITIZE))
CFLAGS += -fsanitize=address -fsanitize=undefined
endif

ifeq (1, $(Og))
CFLAGS += -Og
endif

ifeq (1, $(O0))
CFLAGS += -O0
endif

ifeq (1, $(O1))
CFLAGS += -O1
endif

ifeq (1, $(O2))
CFLAGS += -O2
endif

ifeq (1, $(O3))
CFLAGS += -O3
endif

ifeq (1, $(Ofast))
CFLAGS += -Ofast
endif

ifeq (1, $(SRAND))
CFLAGS += -DSRAND
endif

define expand
	@$(CC) $(CFLAGS) ctl/$(1).h -E $(2)
endef

BINS = a b c d e

# RUN TESTS.
test: tc99 tlst tstr tvec
	$(foreach bin,$(BINS),./$(bin) &&) exit 0
	@rm -f $(BINS)
	@$(CC) --version
	@$(CXX) --version

clean:
	@rm -f $(BINS)

# COMPILE TESTS.
tc99:
	$(CC) $(CFLAGS) tests/test_c99.c -o a
	$(CXX) $(CFLAGS) tests/test_c99.c -o b
tlst:
	$(CXX) $(CFLAGS) tests/test_lst.cc -o c
tstr:
	$(CXX) $(CFLAGS) tests/test_str.cc -o d
tvec:
	$(CXX) $(CFLAGS) tests/test_vec.cc -o e

# EXPAND TEMPLATES (CTL_T DEFAULTED TO INT).
str:
	$(call expand,$@)
lst:
	$(call expand,$@,-DCTL_T=int)
vec:
	$(call expand,$@,-DCTL_T=int)
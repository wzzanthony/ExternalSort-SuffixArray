COMPILER = g++
CCFLAGS = -O3 -std=c++17 -DNORMAL 
all: $(METHOD)

main: main.cc
	${COMPILER} ${CCFLAGS} -o $@ $<
test: test.cc
	${COMPILER} ${CCFLAGS} -o $@ $<


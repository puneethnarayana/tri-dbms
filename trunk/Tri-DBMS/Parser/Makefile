CC=g++
CFLAGS=-c -Wall
flex: lex.yy.c yparser.tab.cpp yparser.tab.hpp
	g++ yparser.tab.cpp lex.yy.c -lfl -o flex

yparser.tab.cpp yparser.tab.hpp: yparser.ypp
	bison -d yparser.ypp

lex.yy.c: lparser.l yparser.tab.hpp
	flex lparser.l

# Makefile

OBJS = parser.o lexer.o main.o Record.o PostFixEvaluator.o WhereExpressionElement.o DataPage.o DBMainHeaderPage.o DirectoryEntry.o DirectoryHeaderPage.o DirectoryPage.o FreePageManager.o Schema.o IndexCatalog.o SysColumnsCatalog.o SysTablesCatalog.o BasicDiskOperations.o BufferManager.o Frame.o LRUPageReplacement.o DatabaseOperations.o BPlusTree.o BPlusTreeUtil.o IndexHeader.o IndexNode.o LeafNode.o IndexUI.o
 
#CC﻿ = g++

CXX = g++

CFLAGS﻿ = -g -Wall

TARGET = Tri-DBMS.exe

################# Final exe


$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)
	
all: $(TARGET)

main.o: main.cpp
	$(CXX) $(CFLAGS) -c main.cpp -o main.o

################# Utils

Record.o: Utils/Record.cpp
	$(CXX) $(CFLAGS) -o Record.o Utils/Record.cpp -c

PostFixEvaluator.o: Utils/PostFixEvaluator.cpp
	$(CXX) $(CFLAGS) -o PostFixEvaluator.o Utils/PostFixEvaluator.cpp -c

WhereExpressionElement.o: Utils/WhereExpressionElement.cpp
	$(CXX) $(CFLAGS) -o WhereExpressionElement.o Utils/WhereExpressionElement.cpp -c

################# Heap File Management

DataPage.o: HeapFileManagement/DataPage.cpp
	$(CXX) $(CFLAGS) -o DataPage.o HeapFileManagement/DataPage.cpp -c

DBMainHeaderPage.o: HeapFileManagement/DBMainHeaderPage.cpp
	$(CXX) $(CFLAGS) HeapFileManagement/DBMainHeaderPage.cpp -c -o DBMainHeaderPage.o

DirectoryEntry.o: HeapFileManagement/DirectoryEntry.cpp
	$(CXX) $(CFLAGS) HeapFileManagement/DirectoryEntry.cpp -c -o DirectoryEntry.o

DirectoryHeaderPage.o: HeapFileManagement/DirectoryHeaderPage.cpp
	$(CXX) $(CFLAGS) HeapFileManagement/DirectoryHeaderPage.cpp -c -o DirectoryHeaderPage.o

DirectoryPage.o: HeapFileManagement/DirectoryPage.cpp
	$(CXX) $(CFLAGS) HeapFileManagement/DirectoryPage.cpp -c -o DirectoryPage.o

FreePageManager.o: HeapFileManagement/FreePageManager.cpp
	$(CXX) $(CFLAGS) HeapFileManagement/FreePageManager.cpp -c -o FreePageManager.o

Schema.o: HeapFileManagement/Schema.cpp
	$(CXX) $(CFLAGS) HeapFileManagement/Schema.cpp -c -o Schema.o

################# System Catalogs
IndexCatalog.o:	SystemCatalogs/IndexCatalog.cpp
	$(CXX) $(CFLAGS) SystemCatalogs/IndexCatalog.cpp -c -o IndexCatalog.o

SysColumnsCatalog.o: SystemCatalogs/SysColumnsCatalog.cpp
	$(CXX) $(CFLAGS) SystemCatalogs/SysColumnsCatalog.cpp -c -o SysColumnsCatalog.o

SysTablesCatalog.o: SystemCatalogs/SysTablesCatalog.cpp
	$(CXX) $(CFLAGS) SystemCatalogs/SysTablesCatalog.cpp -c -o SysTablesCatalog.o

################# disk Management
BasicDiskOperations.o: diskManagement/BasicDiskOperations.cpp
	$(CXX) $(CFLAGS) diskManagement/BasicDiskOperations.cpp -c -o BasicDiskOperations.o

################# Buffer Management

BufferManager.o: BufferManagement/BufferManager.cpp
	$(CXX) $(CFLAGS) BufferManagement/BufferManager.cpp -c -o BufferManager.o

Frame.o: BufferManagement/Frame.cpp
	$(CXX) $(CFLAGS) BufferManagement/Frame.cpp -c -o Frame.o

LRUPageReplacement.o: BufferManagement/LRUPageReplacement.cpp
	$(CXX) $(CFLAGS) BufferManagement/LRUPageReplacement.cpp -c

################# Database Management
DatabaseOperations.o: DatabaseManagement/DatabaseOperations.cpp
	$(CXX) $(CFLAGS) DatabaseManagement/DatabaseOperations.cpp -c -o DatabaseOperations.o

################# Index
BPlusTree.o: Index/BPlusTree.cpp
	$(CXX) $(CFLAGS) Index/BPlusTree.cpp -c -o BPlusTree.o

BPlusTreeUtil.o: Index/BPlusTreeUtil.cpp
	$(CXX) $(CFLAGS) Index/BPlusTreeUtil.cpp -c -o BPlusTreeUtil.o
	
IndexHeader.o: Index/IndexHeader.cpp
	$(CXX) $(CFLAGS) Index/IndexHeader.cpp -c -o IndexHeader.o
	
IndexNode.o: Index/IndexNode.cpp
	$(CXX) $(CFLAGS) Index/IndexNode.cpp -c -o IndexNode.o
	
LeafNode.o: Index/LeafNode.cpp
	$(CXX) $(CFLAGS) Index/LeafNode.cpp -c -o LeafNode.o

IndexUI.o: Index/IndexUI.cpp
	$(CXX) $(CFLAGS) Index/IndexUI.cpp -c -o IndexUI.o
	
################# Parser
Parser/parser.cpp: Parser/yparser.ypp
	bison -d -v Parser/yparser.ypp
	cp yparser.tab.cpp Parser/parser.cpp
	cmp -s yparser.tab.hpp Parser/tok.h || cp yparser.tab.hpp Parser/tok.h

parser.o: Parser/parser.cpp
	$(CXX) $(CFLAGS) -c Parser/parser.cpp -o parser.o

lparser.c: Parser/lparser.l
	flex Parser/lparser.l
	mv lex.yy.c Parser/lparser.c

lexer.o: lparser.c
	$(CXX) $(CFLAGS) -c Parser/lparser.c -o lexer.o

###This main for testing parser
#main.o:﻿  ﻿  Parser/main.cc
#	$(CC) $(CFLAGS) -c Parser/main.cc -o main.o
#lexer.o parser.o  : parser/heading.h
#lexer.o main.o﻿  ﻿  : parser/tok.h
#Schema.o﻿  ﻿  : dependency/Schema.h
#ExecuteStructures.o﻿  : dependency/ExecuteStructures.h
#ExprInfo.o: dependency/ExprInfo.h
#ParseUtil.o: parser/ParseUtil.h

clean:
	rm -f *.o *.output *.tab.* Parser/parser.cpp Parser/tok.h Parser/lparser.c *~ Tri-DBMS.exe

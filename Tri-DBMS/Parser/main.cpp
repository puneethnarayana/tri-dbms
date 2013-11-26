
#include <stdlib.h>
#include <cstdio>
#include <iostream>
#include <stdio.h>
using namespace std;
// prototype of bison-generated parser function

extern int yylex();
extern int yyparse();
extern FILE *yyin;
extern int yy_scan_string(const char *);

/*
void parse_main(char *buff) {

	yy_scan_string(buff);
	if(!yyparse()){
		std::cout<<"Parsed!!"<<std::endl;
	}

}
*/
int main( ){

	/*char *buff = "CREATE TABLE HELLO(col_one INTEGER)";
	parse_main(buff);

	FILE *myfile = fopen("input.txt", "r");
	if (!myfile) {
		cout << "I can't open file!" << endl;
		return -1;
	}
	yyin = myfile;
	do {
		yyparse();
	} while (!feof(yyin));*/

yyparse();
  return 0;
}


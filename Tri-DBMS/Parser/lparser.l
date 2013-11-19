%{
#include <iostream>
using namespace std;
#include "yparser.tab.hpp" //after compiling bison with -d to understand tokens
#define YY_DECL int yylex()
void yyerror(char *s);
int lineno = 1;
%}

%option noyywrap
%e 1200
%%

[ \t\r]+         ;
\n		lineno++;
	
	/* keywords */
FLOAT		{ yylval.sval = strdup(yytext);return FLOAT; }
INT   		{ yylval.sval = strdup(yytext);return INT; }
ALL		{ return ALL; }
AND		{ yylval.sval = strdup(yytext);return AND; }
AVG		{ return AMMSC; }
BOOL		{ yylval.sval = strdup(yytext);return BOOL; }
MIN		{ return AMMSC; }
MAX		{ return AMMSC; }
SUM		{ return AMMSC; }
COUNT		{ return AMMSC; }
ANY		{ return ANY; }
AS		{ return AS; }
ASC		{ return ASC; }
AUTHORIZATION	{ return AUTHORIZATION; }
BETWEEN		{ return BETWEEN; }
BY		{ return BY; }
C		{ return C; }
CHAR(ACTER)?	{ yylval.sval = strdup(yytext);return CHARACTER; }
CHECK		{ return CHECK; }
CLOSE		{ return CLOSE; }
COMMIT		{ return COMMIT; }
CONTINUE	{ return CONTINUE; }
CREATE		{return CREATE; }
CURRENT		{ return CURRENT; }
CURSOR		{ return CURSOR; }
DATABASE	{ return DATABASE; }
DECIMAL		{ return DECIMAL; }
DECLARE		{ return DECLARE; }
DEFAULT		{ return DEFAULT; }
DELETE		{ return DELETE; }
DESC		{ return DESC; }
DESCRIBE	{ return DESCRIBE; }
DISTINCT	{ return DISTINCT; }
DOUBLE		{ return DOUBLE; }
DROP		{ return DROP; }
ESCAPE		{ return ESCAPE; }
EXISTS		{ return EXISTS; }
FETCH		{ return FETCH; }
FLOAT		{ yylval.sval = strdup(yytext);return FLOAT; }
FOR		{ return FOR; }
FOREIGN		{ return FOREIGN; }
FOUND		{ return FOUND; }
FROM		{ return FROM; }
GRANT		{ return GRANT; }
GROUP		{ return GROUP; }
HAVING		{ return HAVING; }
IN		{ return IN; }
INDEX		{ return INDEX; }
INDICATOR	{ return INDICATOR; }
INSERT		{ return INSERT; }
INT(EGER)?	{ yylval.sval = strdup(yytext);return INTEGER; }
INTO		{ return INTO; }
IS		{ return IS; }
KEY		{ yylval.sval = strdup(yytext);return KEY; }
LANGUAGE	{ return LANGUAGE; }
LIKE		{ return LIKE; }
MODULE		{ return MODULE; }
NOT		{ yylval.sval = strdup(yytext);return NOT; }
NULL		{ yylval.sval = strdup(yytext);return NULLX; }
NUMERIC		{ return NUMERIC; }
OF		{ return OF; }
ON		{ return ON; }
OPEN		{ return OPEN; }
OPTION		{ return OPTION; }
OR		{ yylval.sval = strdup(yytext);return OR; }
ORDER		{ return ORDER; }
PRECISION	{ return PRECISION; }
PRIMARY		{ yylval.sval = strdup(yytext);return PRIMARY; }
PRIVILEGES	{ return PRIVILEGES; }
PROCEDURE	{ return PROCEDURE; }
PUBLIC		{ return PUBLIC; }
QUERY		{ return QUERY; }
REAL		{ yylval.sval = strdup(yytext);return REAL; }
REFERENCES	{ return REFERENCES; }
ROLLBACK	{ return ROLLBACK; }
SCHEMA		{ return SCHEMA; }
SELECT		{ return SELECT; }
SET		{ return SET; }
SHOW		{ return SHOW; }
SMALLINT	{ return SMALLINT; }
SOME		{ return SOME; }
SQLCODE		{ return SQLCODE; }
TABLE		{ return TABLE; }
TABLES		{ return TABLES; }
TO		{ return TO; }
UNION		{ return UNION; }
UNIQUE		{ return UNIQUE; }
UPDATE		{ return UPDATE; }
USER		{ return USER; }
VALUES		{ return VALUES; }
VARCHAR		{ yylval.sval = strdup(yytext);return VARCHAR; }
VIEW		{ return VIEW; }
WHENEVER	{ return WHENEVER; }
WHERE		{ return WHERE; }
WITH		{ return WITH; }
WORK		{ return WORK; }
DATABASES	{ return DATABASES;}
USE		{ return USE;}


[(),.;]		{ return yytext[0]; }


	/* punctuation */
"="	|	{ yylval.sval = strdup(yytext);return COMPARISON; }
"<>" 	|	{ yylval.sval = strdup(yytext);return COMPARISON; }
"<"	|	{ yylval.sval = strdup(yytext);return COMPARISON; }
">"	|	{ yylval.sval = strdup(yytext);return COMPARISON; }
"<="	|	{ yylval.sval = strdup(yytext);return COMPARISON; }
">="		{ yylval.sval = strdup(yytext);return COMPARISON; }


[A-Za-z][A-Za-z0-9_]*	{ yylval.sval = strdup(yytext);return NAME; }

	/* numbers */

[0-9]+	|
[0-9]+"."[0-9]* |
"."[0-9]*	{ yylval.sval = strdup(yytext);return INTNUM; }

[0-9]+[eE][+-]?[0-9]+	|
[0-9]+"."[0-9]*[eE][+-]?[0-9]+ |
"."[0-9]*[eE][+-]?[0-9]+	{ return APPROXNUM; }

"[A-Za-z0-9_"."@-]*[ \t\n\r\f]*"	{
			yylval.sval = strdup(yytext);
			return STRING;
	}
.		;
%%

void yyerror(char *s)
{
	cout<<"ERROR at "<<lineno<<":"<<s << yytext;
}

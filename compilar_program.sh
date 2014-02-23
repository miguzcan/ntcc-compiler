bison -d program_parser.y
flex program_scanner.l
cc lex.yy.c program_parser.tab.c -o analyzer -lfl -lm

#include <iostream>
#include <string>
#include <ctype.h>
using namespace std;
// This is all the variables that i used 
int charClass;
char lexeme[100];
char nextChar;
int lexLen;
int token;
int nextToken;
string input = "(A + S193) * 45 - 7 / X2";
size_t currentPos = 0;

//this is  functions
void addChar(); //adds nextchar to lexem
void getChar(); //get nextchar and determine class
void getNonBlank(); //skips empty space
int lex(); //this is the main function of lexeme analysis
int lookup(char ch); // looks up op and parens and return their tokens

//categories of chars
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

//define tokens
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26
#define EOF_TOKEN -1

//the main function that starts the lexical analyzar and makes a loop till EOF_TOKEN is encountered
int main() {
    getChar();
    do {
        lex();
    } while (nextToken != EOF_TOKEN);
    system("pause");
    return 0;

}

//identfy op and parens and return thier tokens
int lookup(char ch) {
    switch (ch) {
    case '(':
        addChar();
        nextToken = LEFT_PAREN;
        break;
    case ')':
        addChar();
        nextToken = RIGHT_PAREN;
        break;
    case '+':
        addChar();
        nextToken = ADD_OP;
        break;
    case '-':
        addChar();
        nextToken = SUB_OP;
        break;
    case '*':
        addChar();
        nextToken = MULT_OP;
        break;
    case '/':
        addChar();
        nextToken = DIV_OP;
        break;
    default:
        addChar();
        nextToken = EOF_TOKEN;
        break;
    }
    return nextToken;
}
//add nextchar to lexeme and check length 
void addChar() {
    if (lexLen <= 98) {
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = '\0';
    }
    else {
        cout << "Error - lexeme is too long" << endl;
    }
}
//get the nextchar and determine class
void getChar() {
    if (currentPos < input.size()) {
        nextChar = input[currentPos++];
        if (isalpha(nextChar))
            charClass = LETTER;
        else if (isdigit(nextChar))
            charClass = DIGIT;
        else
            charClass = UNKNOWN;
    }
    else {
        charClass = EOF_TOKEN;
    }
}
//skips blanks
void getNonBlank() {
    while (isspace(nextChar))
        getChar();
}
// do the lexical analysis based on chars class
int lex() {
    lexLen = 0; //reset length 
    getNonBlank(); //skips blanks
    switch (charClass) {
    case LETTER: //if letter
        addChar();
        getChar();
        while (charClass == LETTER || charClass == DIGIT) {
            addChar();
            getChar();
        }
        nextToken = IDENT;
        break;

    case DIGIT: //if int literal
        addChar();
        getChar();
        while (charClass == DIGIT) {
            addChar();
            getChar();
        }
        nextToken = INT_LIT;
        break;

    case UNKNOWN: // if op or parens
        lookup(nextChar);
        getChar();
        break;

    case EOF_TOKEN: //the end of the statement 
        nextToken = EOF_TOKEN;
        lexeme[0] = 'E';
        lexeme[1] = 'O';
        lexeme[2] = 'F';
        lexeme[3] = '\0';
        break;
    }

    cout << "Next token is: " << nextToken << ", Next lexeme is " << lexeme << endl;
    return nextToken;
}

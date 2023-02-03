#ifndef DATALOGPROJECT_TOKEN_H
#define DATALOGPROJECT_TOKEN_H
#pragma once
#include <string>
#include <sstream>
#include <utility>
using namespace std;

enum TokenType {
    COMMA,
    PERIOD,
    Q_MARK,
    LEFT_PAREN,
    RIGHT_PAREN,
    COLON,
    COLON_DASH,
    MULTIPLY,
    ADD,
    SCHEMES,
    FACTS,
    RULES,
    QUERIES,
    ID,
    STRING,
    COMMENT,
    UNDEFINED,
    ENDOFFILE,
};

class Token {
private:
    TokenType type;
    string value;
    int tline = 1;

public:
    Token(TokenType type, string value, int line) : type(type), value(std::move(value)), tline(line) { }
    Token() {type = UNDEFINED; value = ""; tline = 1;}


    string toString() const;
    string typeName(TokenType type) const;
    int valueLength();
    TokenType getType() const;
    string getValue() const;
};

string Token::toString() const {
    stringstream out;
    out << "(" << typeName(type) << "," << "\"" << value << "\"" << "," << tline << ")";
    return out.str();
}

string Token::typeName(TokenType type) const {
    if (type == COMMA) {return "COMMA";}
    if (type == PERIOD) {return "PERIOD";}
    if (type == Q_MARK) {return "Q_MARK";}
    if (type == LEFT_PAREN) {return "LEFT_PAREN";}
    if (type == RIGHT_PAREN) {return "RIGHT_PAREN";}
    if (type == COLON) {return "COLON";}
    if (type == COLON_DASH) {return "COLON_DASH";}
    if (type == MULTIPLY) {return "MULTIPLY";}
    if (type == ADD) {return "ADD";}
    if (type == SCHEMES) {return "SCHEMES";}
    if (type == FACTS) {return "FACTS";}
    if (type == RULES) {return "RULES";}
    if (type == QUERIES) {return "QUERIES";}
    if (type == ID) {return "ID";}
    if (type == STRING) {return "STRING";}
    if (type == COMMENT) {return "COMMENT";}
    if (type == UNDEFINED) {return "UNDEFINED";}
    if (type == ENDOFFILE) {return "EOF";}
    return "UNKNOWN";
}

int Token::valueLength(){
    return value.size();
}

TokenType Token::getType() const {
    return type;
}

string Token::getValue() const {
    return value;
}

#endif //DATALOGPROJECT_TOKEN_H

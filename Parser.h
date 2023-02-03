#ifndef DATALOGPROJECT_PARSER_H
#define DATALOGPROJECT_PARSER_H
#include <vector>
#include <iostream>
#include "Token.h"
#include "Scanner.h"
#include "Predicate.h"
#include "Parameter.h"

class Parser {
private:
    vector<Token> tokens;
public:
    Parser(const vector<Token>& tokens) :tokens(tokens) {}
    TokenType tokenType() const;

    void advanceToken();
    void throwError();
    void match(TokenType t);
    void datalogProgram();
    void schemeList();
    void factList();
    void ruleList();
    void queryList();
    void scheme();
    void fact();
    void rule();
    void query();
    void headPredicate();
    void predicate();
    void predicateList();
    void parameterList();
    void stringList(Predicate& predicate);
    void idList();
    void parameter();
};

TokenType Parser::tokenType() const {
    return tokens.at(0).getType();
}

void Parser:: advanceToken() {
    tokens.erase(tokens.begin());
}

void Parser::throwError() {
    std::cout << "error" << endl;
}

void Parser::match(TokenType t) {
    cout << "match: " << t << endl;
    if (tokens.at(0).getType() == t) {
        advanceToken();
    } else {
        throwError();
    }
}

void Parser::datalogProgram() {
    match(SCHEMES);
    match(COLON);
    scheme();
    schemeList();
    match(FACTS);
    match(COLON);
    factList();
    match(RULES);
    match(COLON);
    ruleList();
    match(QUERIES);
    match(COLON);
    query();
    queryList();
    match(ENDOFFILE);
}

void Parser::schemeList() {
    if (tokenType() == ID) { //Maybe can get rid of if statement? IDK
        scheme();
        schemeList();
    } else {
        //lambda
    }
}

void Parser::factList() {
    if (tokenType() == ID) { //Maybe can get rid of if statement? IDK
        fact();
        factList();
    } else {
        //lambda
    }
}

void Parser::ruleList() {
    if (tokenType() == ID) { //Maybe can get rid of if statement? IDK
        rule();
        ruleList();
    } else {
        //lambda
    }
}

void Parser::queryList() {
    if (tokenType() == ID) { //Maybe can get rid of if statement? IDK
        query();
        queryList();
    } else {
        //lambda
    }
}

void Parser::scheme() {
        match(ID);
        match(LEFT_PAREN);
        match(ID);
        idList();
        match(RIGHT_PAREN);

}

void Parser::fact() {
    if (tokenType() == ID) {
        Predicate fact = Predicate(FACT, tokens.at(0).getValue());
        match(ID);
        match(LEFT_PAREN);
        if (tokenType() == STRING) {
            fact.addParameter(tokens.at(0).getValue());
            match(STRING);
            stringList(fact);
            match(RIGHT_PAREN);
            match(PERIOD);
        }
        std::cout << fact.toString() << endl;
    }
}

void Parser::rule() {
        headPredicate();
        match(COLON_DASH);
        predicate();
        predicateList();
        match(PERIOD);
}

void Parser::query() {
        predicate();
        match(Q_MARK);
}

void Parser::headPredicate() {
        match(ID);
        match(LEFT_PAREN);
        match(ID);
        idList();
        match(RIGHT_PAREN);
}

void Parser::predicate() {
        match(ID);
        match(LEFT_PAREN);
        parameter();
        parameterList();
        match(RIGHT_PAREN);
}

void Parser::predicateList() {
    if (tokenType() == COMMA) {
        match(COMMA);
        predicate();
        predicateList();
    } else {
        //lambda
    }
}

void Parser::parameterList() {
    if (tokenType() == COMMA) {
        match(COMMA);
        parameter();
        parameterList();
    } else {
        //lambda
    }
}

void Parser::stringList(Predicate& predicate) {
    if (tokenType() == COMMA) {
        match(COMMA);
        if (tokenType() == STRING) {
            predicate.addParameter(tokens.at(0).getValue());
            match(STRING);
            stringList(predicate);
        }
    } else {
        //lambda
    }
}

void Parser::idList() {
    if (tokenType() == COMMA) {
        match(COMMA);
        match(ID);
        idList();
    } else {
        //lambda
    }
}

void Parser::parameter() {
    if(tokenType() == STRING) {
        match(STRING);
    } else if (tokenType() == ID) {
        match(ID);
    } else {
        //lambda
    }
}


#endif //DATALOGPROJECT_PARSER_H

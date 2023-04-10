#ifndef DATALOGPROJECT_PARSER_H
#define DATALOGPROJECT_PARSER_H
#include <vector>
#include <iostream>
#include "Token.h"
#include "Scanner.h"
#include "Predicate.h"
#include "Parameter.h"
#include "Rule.h"
#include "DatalogProgram.h"

class Parser {
private:
    vector<Token> tokens;
    DatalogProgram datalogProgram1;

public:
    explicit Parser(const vector<Token>& tokens) :tokens(tokens) {}
    TokenType tokenType() const;

    DatalogProgram getDatalogProgram(){return datalogProgram1;}
    void advanceToken();
    static void throwError(const Token& errorToken);
    void match(TokenType t);
    void commentChecker();
    void datalogProgram();
    void schemeList();
    void factList();
    void ruleList();
    void queryList();
    void scheme();
    void fact();
    void rule();
    void query();
    void headPredicate(Rule& rule);
    void rulepredicate(Rule& rule);
    void querypredicate();
    void predicateList(Rule& rule);
    void parameterList(Predicate& predicate);
    void stringList(Predicate& predicate);
    void idList(Predicate& predicate);
    void parameter(Predicate& predicate);
};

TokenType Parser::tokenType() const {
    return tokens.at(0).getType();
}

void Parser:: advanceToken() {
    tokens.erase(tokens.begin());
}

void Parser::throwError(const Token& errorToken) {
    std::cout << "Failure!\n  " << errorToken.toString() << std::endl;
    exit(0);
}

void Parser::match(TokenType t) {
    commentChecker();
    if (tokens.at(0).getType() == t) {
        advanceToken();
    } else {
        throwError(tokens.at(0));
    }
}

void Parser::commentChecker() {
    if (tokens.at(0).getType() == COMMENT) {advanceToken(); commentChecker();}
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
    datalogProgram1.fillDomain();
    //std::cout << "Success Parsing!\n";
    //datalogProgram1.toString();
}

void Parser::schemeList() {
    commentChecker();
    if (tokenType() == ID) { //Maybe can get rid of if statement? IDK
        scheme();
        schemeList();
    } else {
        //lambda
    }
}

void Parser::factList() {
    commentChecker();
    if (tokenType() == ID) { //Maybe can get rid of if statement? IDK
        fact();
        factList();
    } else {
        //lambda
    }
}

void Parser::ruleList() {
    commentChecker();
    if (tokenType() == ID) { //Maybe can get rid of if statement? IDK
        rule();
        ruleList();
    } else {
        //lambda
    }
}

void Parser::queryList() {
    commentChecker();
    if (tokenType() == ID) { //Maybe can get rid of if statement? IDK
        query();
        queryList();
    } else {
        //lambda
    }
}

void Parser::scheme() {
    if (tokenType() == FACTS) {throwError(tokens.at(0));}
    if (tokenType() == ID) {
        Predicate scheme = Predicate(tokens.at(0).getValue());
        match(ID);
        match(LEFT_PAREN);
        if (tokenType() == ID) {
            scheme.addParameter(tokens.at(0).getValue());
            match(ID);
            idList(scheme);
            match(RIGHT_PAREN);
        }
        //std::cout << scheme.toString() << endl;
        datalogProgram1.addscheme(scheme);
    }

}

void Parser::fact() {
    if (tokenType() == ID) {
        Predicate fact = Predicate(tokens.at(0).getValue());
        match(ID);
        match(LEFT_PAREN);
        if (tokenType() == STRING) {
            fact.addParameter(tokens.at(0).getValue());
            match(STRING);
            stringList(fact);
            match(RIGHT_PAREN);
            match(PERIOD);
        }
        //std::cout << fact.toString() << endl;
        datalogProgram1.addfact(fact);
    }
}

void Parser::rule() {
        if (tokenType() == ID) {
            Rule rule;
            headPredicate(rule);
            match(COLON_DASH);
            rulepredicate(rule);
            predicateList(rule);
            match(PERIOD);
            //std::cout << rule.toString() << endl;
            datalogProgram1.addrule(rule);
        }
}

void Parser::query() {
    if (tokenType() == ENDOFFILE) {throwError(tokens.at(0));}
    querypredicate();
    match(Q_MARK);
}

void Parser::headPredicate(Rule& rule) {
    if (tokenType() == ID) {
        Predicate headpredi = Predicate(tokens.at(0).getValue());
        match(ID);
        match(LEFT_PAREN);
        if (tokenType() == ID) {
            headpredi.addParameter(tokens.at(0).getValue());
            match(ID);
            idList(headpredi);
            match(RIGHT_PAREN);
        }
        rule.setheadpredi(headpredi);
    }
}

void Parser::rulepredicate(Rule& rule) {
    if (tokenType() == ID) {
        Predicate predicate = Predicate(tokens.at(0).getValue());
        match(ID);
        match(LEFT_PAREN);
        parameter(predicate);
        parameterList(predicate);
        rule.addPredicate(predicate);
        match(RIGHT_PAREN);
    }
}

void Parser::querypredicate() {
    if (tokenType() == ID) {
        Predicate query = Predicate(tokens.at(0).getValue());
        match(ID);
        match(LEFT_PAREN);
        parameter(query);
        parameterList(query);
        match(RIGHT_PAREN);

        //std::cout << Query.toString() << std::endl;
        datalogProgram1.addquery(query);
    }
}

void Parser::predicateList(Rule& rule) {
    if (tokenType() == COMMA) {
        match(COMMA);
        rulepredicate(rule);
        predicateList(rule);
    } else {
        //lambda
    }
}

void Parser::parameterList(Predicate& predicate) {
    if (tokenType() == COMMA) {
        match(COMMA);
        parameter(predicate);
        parameterList(predicate);
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

void Parser::idList(Predicate& predicate) {
    if (tokenType() == COMMA) {
        match(COMMA);
        if (tokenType() == ID) {
            predicate.addParameter(tokens.at(0).getValue());
            match(ID);
            idList(predicate);
        }
    } else {
        //lambda
    }
}

void Parser::parameter(Predicate& predicate) {
    if (tokenType() == ID || tokenType() == STRING) {
        predicate.addParameter(tokens.at(0).getValue());
    }
    if(tokenType() == STRING) {
        match(STRING);
    } else if (tokenType() == ID) {
        match(ID);
    }
}


#endif //DATALOGPROJECT_PARSER_H

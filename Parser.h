#ifndef DATALOGPROJECT_PARSER_H
#define DATALOGPROJECT_PARSER_H

class Parser {
private:
    vactor<Token> tokens;
public:
    Parser(const vector<Token>& tokens) :tokens(tokens) {}
    TokenType tokenType() const;
    void advanceToken();
    void throwError();
};

TokenType Parser::tokenType() const {
    return tokens.at(0).getType();
}



#endif //DATALOGPROJECT_PARSER_H

#ifndef DATALOGPROJECT_SCANNER_H
#define DATALOGPROJECT_SCANNER_H
#include "Token.h"
#include <vector>
#include <cctype>

class Scanner {
private:
    string input;
    int line = 1;
    unsigned long tracker = 0;
    bool done = false;
    Token temp;
    vector<Token> tokens;

public:
    explicit Scanner(const string& input) : input(input) { }

    Token getToken(int i) {return tokens.at(i);}
    int getTokensSize() const {return tokens.size();}

    void scanInput();
    static void printToken(const Token& t);
    Token scanToken();
    void SpaceChecker();
//    Token scanUNDEFINED();
    Token scanCOMMA();
    Token scanPERIOD();
    Token scanQ_MARK();
    Token scanLEFT_PAREN();
    Token scanRIGHT_PAREN();
    Token scanCOLON();
    Token scanCOLON_DASH();
    Token scanMULTIPLY();
    Token scanADD();
    Token scanSCHEMES();
    Token scanFACTS();
    Token scanRULES();
    Token scanQUERIES();
    Token scanID();
    void IDhelper();
    Token scanSTRING();
    void STRINGhelper();
    Token scanCOMMENT();
    void COMMENThelper();

};

void Scanner::scanInput() {
    while (!input.empty()) {
        SpaceChecker();
        if (input.empty()) {break;}
        tokens.push_back(scanToken());
    }
    tokens.push_back(Token(ENDOFFILE,"",line));
    for (auto & token : tokens) {
        printToken(token);
    }
    std::cout << "Total Tokens = " << tokens.size() << endl;
}

void Scanner::printToken(const Token& t) {
    cout << t.toString() << endl;
}

Token Scanner::scanToken() {
    // shouldn't ever be needed as this is taken care of in scanInput if (input.empty()) {return {ENDOFFILE, "", line};}
    Token max;
    if (scanCOMMA().valueLength() > max.valueLength()) {max = scanCOMMA();}
    if (scanPERIOD().valueLength() > max.valueLength()) {max = scanPERIOD();}
    if (scanQ_MARK().valueLength() > max.valueLength()) {max = scanQ_MARK();}
    if (scanLEFT_PAREN().valueLength() > max.valueLength()) {max = scanLEFT_PAREN();}
    if (scanRIGHT_PAREN().valueLength() > max.valueLength()) {max = scanRIGHT_PAREN();}
    if (scanCOLON().valueLength() > max.valueLength()) {max = scanCOLON();}
    if (scanCOLON_DASH().valueLength() > max.valueLength()) {max = scanCOLON_DASH();}
    if (scanMULTIPLY().valueLength() > max.valueLength()) {max = scanMULTIPLY();}
    if (scanADD().valueLength() > max.valueLength()) {max = scanADD();}
    if (scanSCHEMES().valueLength() > max.valueLength()) {max = scanSCHEMES();}
    if (scanFACTS().valueLength() > max.valueLength()) {max = scanFACTS();}
    if (scanRULES().valueLength() > max.valueLength()) {max = scanRULES();}
    if (scanQUERIES().valueLength() > max.valueLength()) {max = scanQUERIES();}
    temp = scanID();
    if (temp.valueLength() > max.valueLength()) {max = temp;}
    temp = scanSTRING();
    if (temp.valueLength() > max.valueLength()) {max = temp;}
    temp = scanCOMMENT();
    if (temp.valueLength() > max.valueLength()) {max = temp;}
    input.erase(0, max.valueLength());
    if (max.valueLength() < 1) {
        string newval = "";
        newval.push_back(input.at(0));
        input.erase(0, 1);
        max = Token(UNDEFINED, newval, line);
    }
    return max;
}

void Scanner::SpaceChecker() {
    if (input.empty()) {return;}
    if (isspace(input.at(0))) {
        if (input.at(0) == '\n') {line++;}
        input.erase(0,1);
        SpaceChecker();
    }
}

//Token Scanner::scanUNDEFINED() {
//    if (!isspace(input.at(0))) {
//        tracker++;
//        scanUNDEFINED();
//    }
//}

Token Scanner::scanCOMMA() {
    if (input.at(0)==','){
        return {COMMA, ",", line};
    } else {return {UNDEFINED, "", line};}
}

Token Scanner::scanPERIOD() {
    if (input.at(0)=='.'){
        return {PERIOD, ".", line};
    } else {return {UNDEFINED, "", line};}
}

Token Scanner::scanQ_MARK() {
    if (input.at(0)=='?'){
        return {Q_MARK, "?", line};
    } else {return {UNDEFINED, "", line};}
}

Token Scanner::scanLEFT_PAREN() {
    if (input.at(0)=='('){
        return {LEFT_PAREN, "(", line};
    } else {return {UNDEFINED, "", line};}
}

Token Scanner::scanRIGHT_PAREN() {
    if (input.at(0)==')'){
        return {RIGHT_PAREN, ")", line};
    } else {return {UNDEFINED, "", line};}
}

Token Scanner::scanCOLON() {
    if (input.at(0)==':'){
        return {COLON, ":", line};
    } else {return {UNDEFINED, "", line};}
}

Token Scanner::scanCOLON_DASH() {
    if (input.at(0)==':'){
        if (input.size() > 1) {
            if (input.at(1)=='-') {
                return {COLON_DASH, ":-", line};
            }
        }
    }
    return {UNDEFINED, "", line};
}

Token Scanner::scanMULTIPLY() {
    if (input.at(0)=='*'){
        return {MULTIPLY, "*", line};
    } else {return {UNDEFINED, "", line};}
}

Token Scanner::scanADD() {
    if (input.at(0)=='+'){
        return {ADD, "+", line};
    } else {return {UNDEFINED, "", line};}
}

Token Scanner::scanSCHEMES() {
    if (input.size() >= 7) {
        if (input.substr(0,7) == "Schemes") {
            return {SCHEMES, "Schemes", line};
        }
    }
    return {UNDEFINED, "", line};
}

Token Scanner::scanFACTS() {
    if (input.size() >= 5) {
        if (input.substr(0,5) == "Facts") {
            return {FACTS, "Facts", line};
        }
    }
    return {UNDEFINED, "", line};
}

Token Scanner::scanRULES() {
    if (input.size() >= 5) {
        if (input.substr(0,5) == "Rules") {
            return {RULES, "Rules", line};
        }
    }
    return {UNDEFINED, "", line};
}

Token Scanner::scanQUERIES() {
    if (input.size() >= 7) {
        if (input.substr(0,7) == "Queries") {
            return {QUERIES, "Queries", line};
        }
    }
    return {UNDEFINED, "", line};
}

Token Scanner::scanID() {
    tracker = 0;
    IDhelper();
    string val = input.substr(0,tracker);
    return {ID,val,line};
}

void Scanner::IDhelper() {
    if (tracker >= input.size()) {return;}
    if (tracker == 0) {
        if (isalpha(input.at(0))) {
            tracker++;
            IDhelper();
        }
    } else {
        if (isdigit(input.at(tracker)) || isalpha(input.at(tracker))) {
            tracker++;
            IDhelper();
        }
    }
}

Token Scanner::scanSTRING() {
    tracker = 0;
    done = false;
    int templine = line;
    STRINGhelper();
    string val = input.substr(0,tracker);
    if (!done) {return {UNDEFINED,val,templine};}
    return {STRING,val,line};
}

void Scanner::STRINGhelper() {
    if (done) {return;}
    if (tracker >= input.size()) {return;}
    if (tracker == 0) {
        if (input.at(0) == '\'') {
            tracker++;
            STRINGhelper();
        }
    } else {
        if (input.at(tracker) != '\'') {
            if (input.at(tracker) == '\n') {line++;}
            tracker++;
            STRINGhelper();
        } else {
            tracker++;
            done = true;
        }
    }
}

Token Scanner::scanCOMMENT() {
    tracker = 0;
    done = false;
    COMMENThelper();
    string val = input.substr(0,tracker);
    return {COMMENT,val,line};
}

void Scanner::COMMENThelper() {
    if (done) {return;}
    if (tracker >= input.size()) {return;}
    if (tracker == 0) {
        if (input.at(0) == '#') {
            tracker++;
            COMMENThelper();
        }
    } else {
        if (input.at(tracker) != '\n') {
            tracker++;
            COMMENThelper();
        } else {
            done = true;
        }
    }
}

#endif //DATALOGPROJECT_SCANNER_H

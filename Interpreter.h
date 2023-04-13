#ifndef DATALOGPROJECT_INTERPRETER_H
#define DATALOGPROJECT_INTERPRETER_H
#include "DatalogProgram.h"
#include "Database.h"
#include "Node.h"
#include "Graph.h"

class Interpreter {
private:
    DatalogProgram datalogProgram;
    Database database;
    vector<Predicate> schemes = datalogProgram.getschemes();
    vector<Predicate> facts = datalogProgram.getfacts();
    vector<Predicate> queries = datalogProgram.getqueries();
    vector<Rule> rules = datalogProgram.getrules();
    bool isSpecific = true;
    int passes = 0;
    bool passagain = false;
    vector<vector<Rule>> SCCs;
    vector<int> SCCidentifiers;
public:
    Interpreter(DatalogProgram datalogProgram) : datalogProgram(datalogProgram) {}
    void loadDatabase();
    void evaluate();
    Relation evaluatePredicate(Predicate query);
    void evaluateRule(Rule rule);
    void evaluateAllR(vector<Rule> rules);
    void evaluateAllQ();
    void tester() {
        Relation r = database.getRelation(queries.at(0).getName());
        r = r.rename(0,"COLLIN");
        cout << r.toString();
    }
    void loadSCC() {
        Graph g = makeGraph(rules);
        cout << "Dependency Graph" << endl << g.toString();
        stack<int> postorder = g.reverse().dfsForest();
//        stack<int> temp = postorder;                                  //PRINTING THE STACK MADE BY dfsFOREST
//        for (long unsigned int i=0; i<postorder.size(); ++i) {
//            cout << temp.top() << endl;
//            temp.pop();
//        }
        for (long unsigned int i=0; i<rules.size(); ++i) {
            if (!g.at(postorder.top()).hasvisit()) {
                g.dfs(postorder.top());
                vector<int> nodesvisited = g.getnodesvisited();
                vector<Rule> SCCrules;
                for (long unsigned int j=0; j<nodesvisited.size(); ++j) {
                    SCCrules.push_back(rules.at(nodesvisited.at(j)));
                }
                SCCs.push_back(SCCrules);
                g.clearnodesvisited();
            }
            SCCidentifiers.push_back(postorder.top());
            postorder.pop();
        }
//        for (long unsigned int i=0; i<rules.size(); ++i) {
//            if (!g.at(postorder.top()).hasvisit()) {
//                g.clearVisit(); // almost works
//                g.at(postorder.top()).visited();
//                g.dfs(postorder.top());
//                vector<Rule> SCCrules;
//                for (long unsigned int j=0; j<rules.size(); ++j) {
//                    if (g.at(j).hasvisit()){
//                        SCCrules.push_back(rules.at(j));
//                    }
//                }
//                SCCs.push_back(SCCrules);
////                SCCs.push_back(makeGraph(SCCrules)); //making graph is causing issues.
//            }
//            postorder.pop();
//        }
//        cout << endl << "PRINTING SCCs" << endl;
//        for (long unsigned int i=0; i<SCCs.size(); ++i) {
//            cout << i << ": " << endl;
//            for (long unsigned int j=0; j<SCCs.at(i).size(); ++j) {
//                cout << SCCs.at(i).at(j).toString() << endl;
//            }
//        }
    }
    static Graph makeGraph(const vector<Rule>& rules) {
        Graph graph(rules.size()); // if a predicate name of current rule == rules.at(i).name, then add edge
        for (int i=0; i<rules.size(); ++i) {
            for (int j=0; j<rules.at(i).getpredicates().size(); ++j) {
                for (int h=0; h<rules.size(); ++h) {
                    if (rules.at(i).getpredicates().at(j).getName() == rules.at(h).getName()) {
                        graph.addEdge(i,h);
                    }
                }
            }
        }
        return graph;
    }
};

void Interpreter::evaluate() {
    loadDatabase();
    loadSCC();
    cout << endl << "Rule Evaluation" << endl;
    //do {passagain = false; evaluateAllR(rules);} while(passagain);
    for (long unsigned int i=0; i<SCCs.size(); ++i) {
        cout << "SCC: R" << SCCidentifiers.at(i) << endl;
        bool flag = false;
        for (long unsigned int j=0; j<SCCs.at(i).at(0).getpredicates().size(); ++j) {
            if (SCCs.at(i).at(0).getName() == SCCs.at(i).at(0).getpredicates().at(0).getName()) {
                flag = true;
            }
        }
        if (SCCs.at(i).size() == 1 && !flag) {
            evaluateAllR(SCCs.at(i));
            cout << passes << " passes: R" << SCCidentifiers.at(i) << endl;
            passes = 0;
            continue;
        }
        do {passagain = false; evaluateAllR(SCCs.at(i));} while(passagain);
        //evaluateAllR(SCCs.at(i));
        cout << passes << " passes: R" << SCCidentifiers.at(i) << endl;
        passes = 0;
    }
    cout << endl << "Query Evaluation" << endl;
    evaluateAllQ();
}

void Interpreter::evaluateRule(Rule rule) {
    //evaluatePredicate
    //join
    //project
    //rename
    //union
    vector<Predicate> predicates = rule.getpredicates();
    vector<Relation> relations;
    for (const auto& it : predicates) {
        relations.push_back(evaluatePredicate(it));
    }
    while (relations.size() > 1) {
        relations.at(0) = relations.at(0).join(relations.at(1));
        relations.erase(relations.begin()+1);
    } //tested with ints in main
    Relation r = relations.at(0); // DECLARE RELATION EARLIER SO IT HAS THE CORRECT NAME AND SCHEME?
    r.setname(rule.getheadpredi().getName());
    vector<int> indexes;
    vector<string> headscheme = rule.getheadpredi().getStrings();
    vector<string> bodyscheme = r.getScheme();
    for (auto & i : headscheme) {
        for (long unsigned int j=0; j<bodyscheme.size(); ++j) {
            if (i == bodyscheme.at(j)) {
                indexes.push_back(j);
            }
        }
    }
    r = r.project(headscheme,indexes);

    vector<string> renamescheme;
    for (auto& it : schemes) {
        if (rule.getheadpredi().getName() == it.getName()) {
            renamescheme = it.getStrings();
        }
    }
//    for (int i=0; i<renamescheme.size(); ++i) {
//        cout << renamescheme.at(i) << " : " << r.getScheme().at(i) << endl;
//        r.rename(i,renamescheme.at(i));
//    }
    r.rename2(renamescheme);

    Relation dr = database.getRelation(r.getName());
    //cout << "\n\n dr after " << passes << " pass:\n" << dr.toString();
    dr.unionize(r);
    if (!database.doesmatch(dr, r.getName())) {
        database.changeRelation(dr,r.getName());
        passagain = true;
    }
}

void Interpreter::evaluateAllR(vector<Rule> rules) {
    for (auto & rule : rules) {
        cout << rule.toString() << endl;
        evaluateRule(rule);
    }
    ++passes;
}

void Interpreter::evaluateAllQ() {
    for (auto & query : queries) {
        Relation r = evaluatePredicate(query);
        cout << query.toString() << "? ";
        if (r.isempty()) {cout << "No" << endl; continue;}
        if (isSpecific) {
            cout << "Yes(" << r.tuSize() << ")" << endl;
        } else {
            cout << "Yes(" << r.tuSize() << ")" << endl;
            cout << r.toString();
        }
    }
}

Relation Interpreter::evaluatePredicate(Predicate query) {
    bool flag = true;
    isSpecific = true;
    vector<int> indexes;
    map<string, int> map;
    vector<string> key;
    Relation r = database.getRelation(query.getName());
    vector<Parameter> qparams = query.getParameters();
    for (long unsigned int i=0; i<qparams.size(); ++i) {
        flag = true;
        if (qparams.at(i).isConstant()) {
            r = r.select1(i,qparams.at(i).toString());
        } else { isSpecific = false;
            if (key.empty()) {
                map.insert(pair<string,int> (qparams.at(i).toString(),i));
                key.push_back(qparams.at(i).toString());
            } else {
                for (auto & j : key){
                    if (j == qparams.at(i).toString()) {
                        r = r.select2(map.at(qparams.at(i).toString()),i);
                        flag = false;
                    }
                }
                if (flag) {
                    map.insert(pair<string,int> (qparams.at(i).toString(),i));
                    key.push_back(qparams.at(i).toString());
                }
            }
        }
    }
    for (auto & i : key) {
        indexes.push_back(map.at(i));
    }
    r = r.project(key,indexes);

//    for (auto & i : key) {
//        r = r.rename(map.at(i), i);
//    }

//    cout << query.toString() << "? ";
//    if (r.isempty()) {cout << "No" << endl; return r;}
//    if (isSpecific) {
//        cout << "Yes(" << r.tuSize() << ")" << endl;
//    } else {
//        cout << "Yes(" << r.tuSize() << ")" << endl;
//        cout << r.toString();
//    }
    return r;
}

void Interpreter::loadDatabase() {
    for (long unsigned int i=0; i<schemes.size(); ++i) {
        database.addRelation(Relation(schemes.at(i).getName(), schemes.at(i).getStrings()));
        //std::cout << schemes.at(i).getSchemeStrings().at(0);
    }
    for (long unsigned int i=0; i<facts.size(); ++i) {
        for (long unsigned int j=0; j<schemes.size(); ++j) {
            if (facts.at(i).getName() == schemes.at(j).getName()) {
                database.addTuple(facts.at(i).getName(), facts.at(i).getStrings());
            }
        }
    }
    //std::cout << "FULL DATABASE FOR REL 0:\n" << database.getRelation(facts.at(0).getName()).toString() << std::endl;

}

#endif //DATALOGPROJECT_INTERPRETER_H

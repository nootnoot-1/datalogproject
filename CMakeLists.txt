cmake_minimum_required(VERSION 3.20)
project(DatalogProject)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(DatalogProject
        main.cpp
        Token.h
        Scanner.h
        Parser.h
        Predicate.h
        Parameter.h
        Rule.h
        DatalogProgram.h
        Scheme.h
        Tuple.h
        Relation.h
        Database.h
        Interpreter.h
        Node.h
        Graph.h)

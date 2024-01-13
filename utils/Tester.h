#ifndef TESTER_H
#define TESTER_H

#define INT_MAX __INT_MAX__

#include <iostream>
#include "Timer.h"
#include <fstream>
#include "../Graph.h"
#include "RandomGenerator.h"
class Tester
{
public:
    Tester(int numOfTests);                        // constructor
    void generateGraph(Graph *graph);              // method for generating graph
    void printResultsToFile(std::string fileName); // method for printing results to file

    Graph* loadGraphFromFile(std::string fileName); // method for loading graph from file

private:
    int numOfTests;
    std::vector<std::vector<int>> paths;
    std::vector<int> totalWeights;
    std::vector<long> times;
};

#endif

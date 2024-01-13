#ifndef TESTER_H
#define TESTER_H

#define INT_MAX __INT_MAX__

#include <iostream>
#include "Timer.h"
#include <fstream>
#include "../Graph.h"
#include <string>
#include "RandomGenerator.h"
class Tester
{
public:
    Tester(int numOfTests);                        // constructor
    void generateGraph(Graph *graph);              // method for generating graph
    void printResultsToFile(std::string fileName); // method for printing results to file

    Graph* loadGraphFromFile(std::string fileName); // method for loading graph from file
    
    void runTests(std::string fileName, int stopTime, int crossoverMethod, int mutationMethod,  float crossoverFactor, float mutationFactor, int populationSize); // method for running tests
private:
    int numOfTests;
    std::vector<std::vector<int>> paths;
    std::vector<int> totalWeights;
    std::vector<long> times;
};

#endif

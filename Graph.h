#include <vector>
#include <string>
#include <iostream>
#include <limits.h>
#include <chrono>
#include "utils/NeighborhoodSolver.cpp"
#include "utils/RandomGenerator.h"
#include <unordered_map>

#ifndef GRAPH_H
#define GRAPH_H

class Graph
{
public:
    // constructor
    Graph(int numVertices);

    // destructor
    ~Graph();

    // method to add an edge between two vertices with a given weight
    void addEdge(int u, int v, int weight);

    // method to get the weight of an edge between two vertices
    int getEdgeWeight(int u, int v) const;

    // method to get the number of vertices in the graph
    int getNumVertices() const;

    // method to get the number of edges in the graph
    int getNumEdges() const;

    // method to get the stop time
    int getStopTime() const;

    // method to get the neighborhood choice
    int getNeighborhoodChoice() const;
    
    // method to get the mutation probability
    float getMutationProbability() const;

    // method to get the crossover probability
    float getCrossoverProbability() const;

    // method to get the population size
    int getPopulationSize() const;

    // method to get the crossover method
    int getCrossoverMethod() const;

    // method to get the mutation method
    int getMutationMethod() const;

    // method to set the mutation probability
    void setMutationFactor(float mutationProbability);

    // method to set the stop time
    void setStopTime(int stopTime);
    
    // method to convert the graph into a string
    std::string toString() const;

    // method to get the adjacency matrix
    std::vector<std::vector<int>> getAdjecencyMatrix() const;

    // method to get cost of a path
    int getPathCost(const std::vector<int> &path) const;

    // method to set the neighborhood choice
    void setNeighborhoodChoice(int neighborhoodChoice);

    // method to get path by using greedy algorithm (nearest neighbour)
    void getGreedyPath(std::vector<int> &path, int &totalWeight, int startVertex);

    // method to create initial population
    std::vector<std::vector<int>> createInitialPopulation(int populationSize, int& totalWeight);

    // method to calculate costs of paths in population
    std::vector<int> calculateCosts(std::vector<std::vector<int>> &population);

    // method to get the best path in population
    std::vector<int> getBestPath(std::vector<std::vector<int>> &population, std::vector<int> &costs);

    // method to sort population
    void sortPopulation(std::vector<std::vector<int>> &population);

    void setPopulationSize(int populationSize);

    void setCrossoverFactor(float crossoverProbability);

    void setCrossoverMethod(int crossoverMethod);

    void setMutationMethod(int mutationMethod);

std::vector<int> tournamentSelection(const std::vector<std::vector<int>>& population, int tournamentSize);

    // crossover method
    std::vector<int> crossover(std::vector<int> &path1, std::vector<int> &path2);

    // mutation method
    void mutation(std::vector<int> &path);

    // genetic mutation algorithm
    void geneticMutation(std::vector<int> &path, int &totalWeight, long &time);

    // print path
    void printPath(const std::vector<int> &path);


private:
    // store the weights of edges between vertices
    std::vector<std::vector<int>> adjacencyMatrix;

    // stop time for algorithms in seconds
    int stopTime;

    // neighborhood choice
    int neighborhoodChoice = 1;

    // mutationFactor
    float mutationFactor = 0.01;

    // crossover
    float crossoverFactor = 0.8;

    // population size
    int populationSize = 50;

    // method of crossover
    int crossoverMethod = 1;

    // method of mutation
    int mutationMethod = 1;

    // number of vertices
    int numVertices;

    // variable to store greedy path
    std::vector<int> greedyPath;

    // number of edges
    int numEdges;
};

#endif
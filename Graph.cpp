#include "Graph.h"
#include <algorithm>
#include <limits>
#include <random>
// graph constructor
Graph::Graph(int numVertices)
{
    this->numVertices = numVertices;
    this->numEdges = 0;
    adjacencyMatrix.resize(numVertices, std::vector<int>(numVertices, -1));
    greedyPath.reserve(numVertices);
    stopTime = 10;
}

// graph destructor
Graph::~Graph()
{
}

// adding edges
void Graph::addEdge(int u, int v, int weight)
{
    if (u >= 0 && u < numVertices && v >= 0 && v < numVertices)
    {
        adjacencyMatrix[u][v] = weight;
        numEdges++;
    }
}

// getting edge's weight
int Graph::getEdgeWeight(int u, int v) const
{
    if (u >= 0 && u < numVertices && v >= 0 && v < numVertices)
        return adjacencyMatrix[u][v];
    else
        return -1;
}
// returns number of vertices
int Graph::getNumVertices() const
{
    return numVertices;
}

// returns number of edges
int Graph::getNumEdges() const
{
    return numEdges;
}

// returns stop time
int Graph::getStopTime() const
{
    return stopTime;
}

int Graph::getNeighborhoodChoice() const
{
    return neighborhoodChoice;
}

float Graph::getMutationProbability() const
{
    return mutationFactor;
}

float Graph::getCrossoverProbability() const
{
    return crossoverFactor;
}

int Graph::getPopulationSize() const
{
    return populationSize;
}

int Graph::getCrossoverMethod() const
{
    return crossoverMethod;
}

// setting stop time
void Graph::setStopTime(int stopTime)
{
    this->stopTime = stopTime;
}

// setting neighborhood choice
void Graph::setNeighborhoodChoice(int neighborhoodChoice)
{
    this->neighborhoodChoice = neighborhoodChoice;
}

int Graph::getMutationMethod() const
{
    return mutationMethod;
}

// converting graph into string version
std::string Graph::toString() const
{
    std::string output = "";
    for (int i = 0; i < numVertices; i++)
    {
        for (int j = 0; j < numVertices; j++)
        {
            output += std::to_string(adjacencyMatrix[i][j]) + " ";
        }
        output += "\n";
    }
    return output;
}

// returns adjacency matrix
std::vector<std::vector<int>> Graph::getAdjecencyMatrix() const
{
    return adjacencyMatrix;
}

int Graph::getPathCost(const std::vector<int> &path) const
{
    int cost = 0;
    for (int i = 0; i < path.size() - 1; i++)
        cost += adjacencyMatrix[path[i]][path[i + 1]];
    return cost;
}

// sorts population
void Graph::sortPopulation(std::vector<std::vector<int>> &population)
{
    // write bubblesort to sort population
    for (int i = 0; i < population.size(); i++)
    {
        for (int j = 0; j < population.size() - i - 1; j++)
        {
            if (getPathCost(population[j]) > getPathCost(population[j + 1]))
            {
                std::swap(population[j], population[j + 1]);
            }
        }
    }
}

void Graph::setPopulationSize(int populationSize)
{
    this->populationSize = populationSize;
}

void Graph::setCrossoverFactor(float crossoverProbability)
{
    this->crossoverFactor = crossoverProbability;
}

void Graph::setCrossoverMethod(int crossoverMethod)
{
    this->crossoverMethod = crossoverMethod;
}

void Graph::setMutationMethod(int mutationMethod)
{
    this->mutationMethod = mutationMethod;
}

// mutation method - mutationMethod = 1 - swap mutation, mutationMethod = 2 - inversion mutation
void Graph::mutation(std::vector<int> &path)
{
    RandomGenerator randomGenerator;
    int mutationPoint1 = randomGenerator.generateRandomInt(1, path.size() - 2);
    int mutationPoint2 = randomGenerator.generateRandomInt(1, path.size() - 2);

    if (mutationPoint1 > mutationPoint2)
        std::swap(mutationPoint1, mutationPoint2);

    if (mutationMethod == 1)
        std::swap(path[mutationPoint1], path[mutationPoint2]);

    else if (mutationMethod == 2)
        std::reverse(path.begin() + mutationPoint1, path.begin() + mutationPoint2);
}

void Graph::printPath(const std::vector<int> &path)
{
    std::cout << "Path: ";
    for (auto &vertex : path)
        std::cout << vertex << ", ";
    std::cout << '\n';
    std::cout << "Total cost: " << getPathCost(path) << '\n';
}

// randomly generates population
std::vector<std::vector<int>> Graph::createInitialPopulation(int populationSize, int &totalWeight)
{
    RandomGenerator randomGenerator;
    std::vector<std::vector<int>> population;
    std::vector<int> path;

    for (int i = 0; i < numVertices; i++)
        path.push_back(i);

    for (int i = 0; i < populationSize; i++)
    {
        std::vector<int> newPath = randomGenerator.shuffleVector(path, 0, path.size() - 1);
        newPath.push_back(newPath[0]);
        population.push_back(newPath);
        if (totalWeight > getPathCost(newPath))
            totalWeight = getPathCost(newPath);
    }

    return population;
}

std::vector<int> Graph::calculateCosts(std::vector<std::vector<int>> &population)
{
    std::vector<int> costs;
    for (auto &path : population)
    {
        costs.push_back(getPathCost(path));
    }
    return costs;
}

std::vector<int> Graph::getBestPath(std::vector<std::vector<int>> &population, std::vector<int> &costs)
{
    int minCost = INT_MAX;
    int minCostIndex = 0;
    for (int i = 0; i < costs.size(); i++)
    {
        if (costs[i] < minCost)
        {
            minCost = costs[i];
            minCostIndex = i;
        }
    }
    return population[minCostIndex];
}

// crossover method - crossoverMethod = 1 - order crossover, crossoverMethod = 2 - partially mapped crossover
std::vector<int> Graph::crossover(std::vector<int> &path1, std::vector<int> &path2)
{
    int size = path1.size();
    std::vector<int> newPath(size, -1);
    RandomGenerator randomGenerator;

    // write order crossover that dont touch first and last vertex
    if (crossoverMethod == 1)
    {
        int crossoverPoint1 = randomGenerator.generateRandomInt(1, size - 2);
        int crossoverPoint2 = randomGenerator.generateRandomInt(1, size - 2);

        if (crossoverPoint1 > crossoverPoint2)
            std::swap(crossoverPoint1, crossoverPoint2);

        for (int i = crossoverPoint1; i <= crossoverPoint2; i++)
        {
            newPath[i] = path1[i];
        }

        int j = 0;
        for (int i = 0; i < size; i++)
        {
            if (j == crossoverPoint1)
                j = crossoverPoint2 + 1;
            if (std::find(newPath.begin(), newPath.end(), path2[i]) == newPath.end())
            {
                newPath[j] = path2[i];
                j++;
            }
        }

        newPath[size - 1] = newPath[0];
    }

    return newPath;
}
// greedy algorithm
void Graph::getGreedyPath(std::vector<int> &path, int &totalWeight, int startVertex)
{
    std::vector<bool> visited(numVertices, false);
    int nextVertex = -1;
    int minWeight = INT_MAX;
    int currentVertex = startVertex;

    path.push_back(currentVertex);
    visited[currentVertex] = true;
    // iterate until all vertices are visited
    while (path.size() < numVertices)
    {
        // iterate through all vertices
        for (int i = 0; i < numVertices; i++)
        {
            // if vertex is not visited and there is an edge between current vertex and i and weight of that edge is smaller than minWeight
            if (i != currentVertex && !visited[i] && adjacencyMatrix[currentVertex][i] != -1 && adjacencyMatrix[currentVertex][i] < minWeight)
            {
                minWeight = adjacencyMatrix[currentVertex][i];
                nextVertex = i;
            }
        }
        // if there is a vertex to visit
        if (nextVertex != -1)
        {
            path.push_back(nextVertex);
            visited[nextVertex] = true;
            totalWeight += minWeight;
            currentVertex = nextVertex;
            nextVertex = -1;
            minWeight = INT_MAX;
        }
    }
    // add weight of edge between last and first vertex
    totalWeight += adjacencyMatrix[currentVertex][startVertex];
    path.push_back(startVertex);
    greedyPath = path;
}

void Graph::setMutationFactor(float mutationProbability)
{
    this->mutationFactor = mutationProbability;
}

std::vector<int> Graph::tournamentSelection(const std::vector<std::vector<int>> &population, int tournamentSize)
{
    std::vector<std::vector<int>> tournament(tournamentSize);

    RandomGenerator randomGenerator;

    // Randomly select individuals for the tournament
    for (int i = 0; i < tournamentSize; i++)
    {
        int index = randomGenerator.generateRandomInt(0, population.size() - 1);
        tournament[i] = population[index];
    }

    // Find the best individual in the tournament
    std::vector<int> best = tournament[0];
    for (int i = 1; i < tournamentSize; i++)
    {
        if (getPathCost(tournament[i]) < getPathCost(best))
        {
            best = tournament[i];
        }
    }

    return best;
}

void Graph::geneticMutation(std::vector<int> &path, int &totalWeight, long &time)
{
    RandomGenerator randomGenerator;

    std::vector<std::vector<int>> population;
    std::vector<int> populationCosts;

    population = createInitialPopulation(populationSize, totalWeight);
    populationCosts = calculateCosts(population);

    std::vector<int> bestPath = getBestPath(population, populationCosts);
    totalWeight = getPathCost(bestPath);

    int tournamentSize = 5;

    int generation = 0;

    auto currentTime = std::chrono::high_resolution_clock::now();
    while (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - currentTime).count() < stopTime)
    {
        generation++;
        std::vector<std::vector<int>> newPopulation;

        for (int i = 0; i < populationSize; i++)
        {
            std::vector<int> parent1 = tournamentSelection(population, tournamentSize);
            newPopulation.push_back(parent1);
        }
        int numCrossover = static_cast<int>(newPopulation.size() * crossoverFactor);

        for (int i = 0; i < numCrossover; i++)
        {
            int index1 = randomGenerator.generateRandomInt(0, newPopulation.size() - 1);
            int index2 = randomGenerator.generateRandomInt(0, newPopulation.size() - 1);

            while (index1 == index2)
            {
                index2 = randomGenerator.generateRandomInt(0, newPopulation.size() - 1);
            }

            std::vector<int> offspring1 = crossover(newPopulation[index1], newPopulation[index2]);
            std::vector<int> offspring2 = crossover(newPopulation[index2], newPopulation[index1]);

            newPopulation[index1] = offspring1;
            newPopulation[index2] = offspring2;
        }

        int numMutation = static_cast<int>(newPopulation.size() * mutationFactor);

        for (int i = 0; i < numMutation; i++)
        {
            int index = randomGenerator.generateRandomInt(0, newPopulation.size() - 1);

            mutation(newPopulation[index]);
        }

        population = newPopulation;
        bestPath = getBestPath(population, populationCosts);

        path = bestPath;

        if (totalWeight > getPathCost(bestPath))
        {
            totalWeight = getPathCost(bestPath);
            time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - currentTime).count();
        //     printPath(bestPath);
        //      std::cout << "Time: " << time << '\n';
        //     std::cout << "Generation: " << generation << '\n';
         }
    }
}

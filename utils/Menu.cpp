#include "Menu.h"
#include "../Graph.h"
#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

Menu::Menu(std::string name, std::vector<MenuItem> menuItems, Graph *graph) : menuName(name), menuItems(menuItems), innerLoop(false), graph(graph)
{
}

// runs menu
bool Menu::run()
{
    while (true)
    {
        system(CLEAR);
        int i = 1;
        std::cout << std::setw(menuName.length() * 1.6) << menuName << '\n';

        std::cout << std::string(menuName.length() * 2, '=') << '\n';
        for (auto &item : menuItems)
        {
            if (item.str == "set stop time")
                std::cout << i++ << ". " << item.str << " (" << graph->getStopTime() << " seconds)" << '\n';
            else if (item.str == "set neighborhood")
                std::cout << i++ << ". " << item.str << " (" << graph->getNeighborhoodChoice() << ")" << '\n';
            else if (item.str == "set mutation factor")
                std::cout << i++ << ". " << item.str << " (" << graph->getMutationProbability() << ")" << '\n';
            else if (item.str == "set crossover factor")
                std::cout << i++ << ". " << item.str << " (" << graph->getCrossoverProbability() << ")" << '\n';
            else if (item.str == "set population size")
                std::cout << i++ << ". " << item.str << " (" << graph->getPopulationSize() << ")" << '\n';
            else if (item.str == "method of crossover")
                std::cout << i++ << ". " << item.str << " (" << graph->getCrossoverMethod() << ")" << '\n';
            else if (item.str == "method of mutation")
                std::cout << i++ << ". " << item.str << " (" << graph->getMutationMethod() << ")" << '\n';
            else
                std::cout << i++ << ". " << item.str << '\n';
        }

        int choice = getIntInput("Enter your choice: ");
        if (choice > 0 && choice <= menuItems.size())
        {
            MenuItem chosenItem = menuItems[choice - 1];
            if (chosenItem.menuItems.size() > 0)
            {
                innerLoop = true;
                while (innerLoop)
                {
                    Menu menu(chosenItem.str, chosenItem.menuItems, graph);
                    innerLoop = menu.run();
                }
            }
            else
            {
                std::string chosenItemString = chosenItem.str;
                if (chosenItemString == "exit")
                    return false;
                else if (chosenItemString == "read from file")
                {
                    std::ifstream file(getStringInput("Enter filename: "));
                    if (!file)
                    {
                        std::cout << "Unable to open file" << '\n';
                        waitForUser();
                    }
                    else
                    {
                        int numVertices;
                        file >> numVertices;
                        delete graph;
                        graph = new Graph(numVertices);
                        int weight;
                        for (int i = 0; i < numVertices; i++)
                        {
                            for (int j = 0; j < numVertices; j++)
                            {
                                file >> weight;
                                graph->addEdge(i, j, weight);
                            }
                        }
                        std::cout << graph->toString() << '\n';
                        file.close();
                        std::cout << "File read successfully - Graph loaded" << '\n';
                        waitForUser();
                    }
                }
                else if (chosenItemString == "display matrix")
                {
                    std::cout << graph->toString() << '\n';
                    waitForUser();
                }

                else if (chosenItemString == "generate graph")
                {
                    RandomGenerator random;
                    int numVertices = getIntInput("Enter number of vertices: ");
                    int minWeight = getIntInput("Enter minimum weight: ");
                    int maxWeight = getIntInput("Enter maximum weight: ");
                    delete graph;
                    graph = new Graph(numVertices);
                    for (int i = 0; i < numVertices; i++)
                        for (int j = 0; j < numVertices; j++)
                            if (i != j)
                                graph->addEdge(i, j, random.generateRandomInt(minWeight, maxWeight));
                }
                else if (chosenItemString == "create starting solution")
                {
                    std::vector<int> path;
                    int totalWeight = 0;
                    graph->getGreedyPath(path, totalWeight, 0);
                    std::cout << "Starting solution created" << '\n';
                    std::cout << "Total cost: " << totalWeight << '\n';
                    std::cout << "Path: ";
                    for (auto &vertex : path)
                        std::cout << vertex << " ";
                    std::cout << '\n';

                    waitForUser();
                }
                else if (chosenItemString == "set stop time")
                {
                    graph->setStopTime(getIntInput("Enter stop time in seconds: "));
                }
                else if (chosenItemString == "set neighborhood")
                {
                    int input = getIntInput("Enter neighborhood choice (1 - swap, 2 - insert, 3 - invert): ");
                    if (input < 1 || input > 3)
                        std::cout << "Invalid choice" << std::endl;
                    else
                        graph->setNeighborhoodChoice(input);
                }
                else if (chosenItemString == "set population size")
                {
                    graph->setPopulationSize(getIntInput("Enter population size: "));
                }
                else if (chosenItemString == "set mutation factor")
                {
                    graph->setMutationFactor(getFloatInput("Enter mutation factor: "));
                }
                else if (chosenItemString == "set crossover factor")
                {
                    graph->setCrossoverFactor(getFloatInput("Enter crossover factor: "));
                }
                else if (chosenItemString == "method of crossover")
                {
                    graph->setCrossoverMethod(getIntInput("Enter crossover method (1 - order, 2 - partially mapped): "));
                }
                else if (chosenItemString == "method of mutation")
                {
                    graph->setMutationMethod(getIntInput("Enter mutation method (1 - swap, 2 - inversion): "));
                }
                else if (chosenItemString == "run genetic algorithm")
                {
                    std::vector<int> path;
                    int totalWeight = 0;
                    long time = 0;
                    graph->geneticMutation(path, totalWeight, time);
                    std::cout << "Total cost: " << totalWeight << '\n';
                    std::cout << "Path: ";
                    for (auto &vertex : path)
                        std::cout << vertex << " ";
                    std::cout << '\n';

       
                    waitForUser();
                }
                
                else if (chosenItemString == "test genetic algorithm")
                {
                    Tester tester(5);
                    int populationSize = getIntInput("Enter population size: ");
                    tester.runTests("ftv47.atsp", 120, 1, 1, 0.8, 0.01, populationSize);
                    tester.runTests("ftv170.atsp", 240, 1, 1, 0.8, 0.01, populationSize);
                    tester.runTests("rbg403.atsp", 360, 1, 1, 0.8, 0.01, populationSize);
                }
    
                else if (chosenItemString == "display graph")
                {
                    std::cout << graph->toString() << '\n';
                    waitForUser();
                }
                else
                {
                    std::cout << "Not implemented yet" << std::endl;
                    waitForUser();
                }
            }
        }
        else
        {
            std::cout << "Invalid choice" << std::endl;
            waitForUser();
        }
    }
}

// waits for user to press enter
void Menu::waitForUser()
{
    std::cin.clear();
    std::cin.ignore(INT_MAX, '\n');
    std::cout << "Press any key to continue . . .\n";

    std::cin.get();
}
// gets int input from user
int Menu::getIntInput(std::string message)
{
    int x;
    std::cout << message;
    std::cin >> x;
    return x;
}
// gets float input from user
float Menu::getFloatInput(std::string message)
{
    float x;
    std::cout << message;
    std::cin >> x;
    return x;
}
// gets string input from user
std::string Menu::getStringInput(std::string message)
{
    std::string x;
    std::cout << message;
    std::cin >> x;
    return x;
}

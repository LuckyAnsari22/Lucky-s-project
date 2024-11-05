#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

// Function to calculate the Euclidean distance between two cities
double calculateDistance(pair<double, double> city1, pair<double, double> city2) {
    return sqrt(pow(city1.first - city2.first, 2) + pow(city1.second - city2.second, 2));
}

// Function to calculate the total distance of the tour
double calculateTourCost(const vector<int>& tour, const vector<pair<double, double>>& cities) {
    double totalCost = 0.0;
    for (size_t i = 0; i < tour.size(); ++i) {
        totalCost += calculateDistance(cities[tour[i]], cities[tour[(i + 1) % tour.size()]]);
    }
    return totalCost;
}

// Function to perform the simulated annealing algorithm
void simulatedAnnealing(vector<pair<double, double>>& cities) {
    int numCities = cities.size();
    vector<int> currentSolution(numCities);
    vector<int> bestSolution(numCities);
    
    // Initialize the current solution
    for (int i = 0; i < numCities; ++i) {
        currentSolution[i] = i;
    }
    random_shuffle(currentSolution.begin(), currentSolution.end());
    
    double currentCost = calculateTourCost(currentSolution, cities);
    bestSolution = currentSolution;
    double bestCost = currentCost;

    double temperature = 10000.0;
    double coolingRate = 0.995;

    for (int iteration = 0; iteration < 10000; ++iteration) {
        // Create a neighbor solution by swapping two cities
        vector<int> neighborSolution = currentSolution;
        int city1 = rand() % numCities;
        int city2 = rand() % numCities;
        swap(neighborSolution[city1], neighborSolution[city2]);

        double neighborCost = calculateTourCost(neighborSolution, cities);
        
        // Acceptance probability
        if (neighborCost < currentCost || (rand() / (RAND_MAX + 1.0)) < exp((currentCost - neighborCost) / temperature)) {
            currentSolution = neighborSolution;
            currentCost = neighborCost;

            // Update the best solution found
            if (currentCost < bestCost) {
                bestCost = currentCost;
                bestSolution = currentSolution;
            }
        }

        // Cool down the temperature
        temperature *= coolingRate;
    }

    // Output the best solution
    cout << "Final achieved cost: " << bestCost << endl;
    cout << "Best tour: ";
    for (int city : bestSolution) {
        cout << city << " ";
    }
    cout << endl;
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    // Example cities (coordinates)
    vector<pair<double, double>> cities = {
        {0.0, 0.0}, {1.0, 5.0}, {5.0, 2.0}, {6.0, 6.0}, {3.0, 1.0}
    };

    simulatedAnnealing(cities);

    return 0;
}
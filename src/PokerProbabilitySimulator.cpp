// PokerProbabilitySimulator.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include "tools.h"
#include "simulator.h"

using namespace std;

struct SimulationParameters
{
    vector<vector<string>> knownHands;
    vector<string> communityCards;
    int numOpponents;
    int numSimulations = 1000; // Default value
};

SimulationParameters requestNumberOfSimulations(SimulationParameters &params)
{
    cout << "Enter number of simulations: (Two Enters for default 1000) ";

    // Check if cin failed or if there's something in the buffer to ignore
    if (cin.fail() || cin.peek() == '\n')
    {
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer before getline
    }

    string input;
    getline(cin, input);
    if (!input.empty())
    {
        try
        {
            params.numSimulations = stoi(input);
        }
        catch (...)
        {
            cout << "Invalid input, using default value of 1000 simulations." << endl;
        }
    }
    return params;
}

SimulationParameters requestSimulationParameters(SimulationParameters *params = nullptr, int gameRound = 5)
{
    SimulationParameters localParams;
    if (!params)
    {
        params = &localParams;
    }

    vector<string> newCards;
    switch (gameRound)
    {
    case -1:
    {
        cout << endl;
        cout << "Simulation configuration: " << endl;
        *params = requestNumberOfSimulations(*params);
        break;
    }
    case 0:
    {
        cout << "Enter number of opponents: ";
        cin >> params->numOpponents;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
        break;
    }
    case 1:
    {
        // Pre-Flop
        cout << endl;
        cout << "PRE-FLOP" << endl;
        cout << "Enter your hand (e.g., Ah,Kh): ";
        params->knownHands = readKnownHands();
        break;
    }
    case 2:
    {
        // Flop
        cout << endl;
        cout << "FLOP" << endl;
        cout << "Enter number of layers left: ";
        cin >> params->numOpponents;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
        cout << "Enter Flop cards (e.g., Jc,Qc,Kc): ";
        params->communityCards = readCommunityCards();
        break;
    }
    case 3:
    {
        // Turn
        cout << endl;
        cout << "TURN" << endl;
        cout << "Enter number of layers left: ";
        cin >> params->numOpponents;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
        cout << "Enter Turn card (e.g., Jc): ";
        newCards = readCommunityCards();
        params->communityCards.insert(params->communityCards.end(), newCards.begin(), newCards.end());
        break;
    }
    case 4:
    {
        // River
        cout << endl;
        cout << "RIVER" << endl;
        cout << "Enter number of layers left: ";
        cin >> params->numOpponents;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
        cout << "Enter River card (e.g., Jc): ";
        newCards = readCommunityCards();
        params->communityCards.insert(params->communityCards.end(), newCards.begin(), newCards.end());
        break;
    }
    default:
    {
        cout << endl;
        cout << "Configuration Parameters" << endl;
        *params = requestNumberOfSimulations(*params);
        cout << "Enter number of opponents: ";
        cin >> params->numOpponents;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
        cout << "Enter your hand (e.g., Ah,Kh): ";
        params->knownHands = readKnownHands();
        cout << "Enter community Cards (e.g., Jc,Qc,Kc): ";
        params->communityCards = readCommunityCards();
        break;
    }
    }
    cout << endl;
    return *params;
}

void singleSimulation(Simulator &sim, const SimulationParameters &params)
{
    vector<vector<int>> results = sim.compute_probabilities(params.numSimulations, params.communityCards, params.knownHands, params.numOpponents);
}

void gameSimulation(Simulator &sim)
{
    SimulationParameters params;
    params = requestSimulationParameters(&params, 0);
    for (int gameRound = 1; gameRound <= 5; gameRound++)
    {
        params = requestSimulationParameters(&params, gameRound);
        singleSimulation(sim, params);
    }

    // Add logic here to adjust parameters and repeat simulations as necessary
}

void testSimulation(Simulator &sim)
{
    vector<vector<string>> known_hands = {{"Ad", "Kh"}}; // Poker hand pairs for each player
    vector<string> comm_hand;                            // Between 0-5 cards available in the community hand

    int N = 100000; // Number of simulations to run

    cout << "Simulating..." << endl;

    // Last parameter is optionally including more players, whose hands are unknown (random)
    vector<vector<int>> results = sim.compute_probabilities(N, comm_hand, known_hands, 3);
}

int main()
{
    Simulator sim;
    string userInput;
    SimulationParameters params;

    while (true)
    {
        cout << "********************************" << endl;
        cout << "[S] o [Single] Single Simulation" << endl;
        cout << "[G] or [Game] Game Simulation" << endl;
        cout << "[T] or [TEST] to check everything works" << endl;
        cout << "[C] or [CONFIGURE] to set number of iterations for the simulation" << endl;
        cout << "[F] or [FINISH] to exit " << endl;
        cout << "Choose simulation mode:";
        getline(cin, userInput);

        if (userInput == "F" || userInput == "FINISH")
        {
            break; // Exit the program
        }
        else if (userInput == "S" || userInput == "Single")
        {
            params = requestSimulationParameters();
            singleSimulation(sim, params);
        }
        else if (userInput == "T" || userInput == "TEST")
        {
            testSimulation(sim);
        }
        else if (userInput == "G" || userInput == "Game")
        {
            gameSimulation(sim);
            cout << "Game simulation not implemented yet." << endl;
        }
        else if (userInput == "C" || userInput == "CONFIGURE")
        {
            SimulationParameters params;
            params = requestSimulationParameters(&params, -1);
        }
        else
        {
            cout << "Invalid option, please try again." << endl;
        }
    }

    return 0;
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln

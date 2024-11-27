#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// Struct to hold details
struct Pokemon {
    string name;
    vector<string> types;
    vector<pair<string, int>> pastEvolutions;  // old evolutions and levels
    vector<pair<string, int>> futureEvolutions; // future evolutions and levels
};

// Function to display details
void displayPokemon(const Pokemon& p) {
    cout << "Name: " << p.name << endl;

    cout << "Types: ";
    for (const string& type : p.types) {
        cout << type << " ";
    }
    cout << endl;

    if (!p.pastEvolutions.empty()) {
        cout << "Past Evolutions: ";
        for (const auto& evo : p.pastEvolutions) {
            cout << evo.first << " (Level " << evo.second << ") ";
        }
        cout << endl;
    }
    else {
        cout << "Past Evolutions: None" << endl;
    }

    if (!p.futureEvolutions.empty()) {
        cout << "Future Evolutions: ";
        for (const auto& evo : p.futureEvolutions) {
            cout << evo.first << " (Level " << evo.second << ") ";
        }
        cout << endl;
    }
    else {
        cout << "Future Evolutions: None" << endl;
    }
}

int main() {
    // Create the Pokédex
    unordered_map<int, Pokemon> pokedex = {
        {1, {"Bulbasaur", {"Grass", "Poison"}, {}, {{"Ivysaur", 16}}}},
        {2, {"Ivysaur", {"Grass", "Poison"}, {{"Bulbasaur", 16}}, {{"Venusaur", 32}}}},
        {3, {"Venusaur", {"Grass", "Poison"}, {{"Ivysaur", 32}}, {}}},
        {4, {"Charmander", {"Fire"}, {}, {{"Charmeleon", 16}}}},
        {5, {"Charmeleon", {"Fire"}, {{"Charmander", 16}}, {{"Charizard", 36}}}},
        {6, {"Charizard", {"Fire", "Flying"}, {{"Charmeleon", 36}}, {}}},
        {7, {"Squirtle", {"Water"}, {}, {{"Wartortle", 16}}}},
        {8, {"Wartortle", {"Water"}, {{"Squirtle", 16}}, {{"Blastoise", 36}}}},
        {9, {"Blastoise", {"Water"}, {{"Wartortle", 36}}, {}}},
        {10, {"Caterpie", {"Bug"}, {}, {{"Metapod", 7}}}},
        {11, {"Metapod", {"Bug"}, {{"Caterpie", 7}}, {{"Butterfree", 10}}}},
        {12, {"Butterfree", {"Bug", "Flying"}, {{"Metapod", 10}}, {}}},
        {13, {"Weedle", {"Bug", "Poison"}, {}, {{"Kakuna", 7}}}},
        {14, {"Kakuna", {"Bug", "Poison"}, {{"Weedle", 7}}, {{"Beedrill", 10}}}},
        {15, {"Beedrill", {"Bug", "Poison"}, {{"Kakuna", 10}}, {}}},
        {16, {"Pidgey", {"Normal", "Flying"}, {}, {{"Pidgeotto", 18}}}},
        {17, {"Pidgeotto", {"Normal", "Flying"}, {{"Pidgey", 18}}, {{"Pidgeot", 36}}}},
        {18, {"Pidgeot", {"Normal", "Flying"}, {{"Pidgeotto", 36}}, {}}},
        // Continue adding Pokémon up to 151...
    };

    int number;
    cout << "Welcome to the Pokedex!" << endl;
    cout << "Enter a Pokemon number (1-151): ";
    cin >> number;

    if (pokedex.find(number) != pokedex.end()) {
        displayPokemon(pokedex[number]);
    }
    else {
        cout << "Pokemon not found in the Pokedex!" << endl;
    }

    return 0;
}

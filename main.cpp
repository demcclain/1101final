#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

// Struct to hold Pokémon details
struct Pokemon {
    int number; // Pokédex number
    string name; // Pokémon name
};

// Function to display Pokémon details
void displayPokemon(const Pokemon& p) {
    cout << "Number: " << p.number << endl;
    cout << "Name: " << p.name << endl;
}

// Function to load Pokédex from a file
bool loadPokedex(const string& filename, vector<Pokemon>& pokedex) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return false;
    }

    string line;
    while (getline(file, line)) {
        // Skip empty lines
        if (line.empty()) continue;

        vector<string> fields;
        stringstream ss(line);
        string field;

        while (getline(ss, field, ',')) {
            fields.push_back(field);
        }

        if (fields.size() != 2) {
            cerr << "Warning: Incorrect format in line: " << line << endl;
            continue; // Skip malformed lines
        }

        Pokemon p;
        try {
            p.number = stoi(fields[0]); // Parse number
        }
        catch (invalid_argument&) {
            cerr << "Warning: Invalid number in line: " << line << endl;
            continue;
        }

        p.name = fields[1]; // Parse name
        pokedex.push_back(p);
    }

    file.close();
    return true;
}

// Bubble Sort: Sorts the Pokédex by Pokémon name in ascending order
void bubbleSort(vector<Pokemon>& pokedex) {
    int n = pokedex.size();
    bool swapped;
    for (int i = 0; i < n - 1; ++i) {
        swapped = false;
        for (int j = 0; j < n - i - 1; ++j) {
            if (pokedex[j].name > pokedex[j + 1].name) {
                swap(pokedex[j], pokedex[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break; // If no two elements were swapped, break
    }
}

// Binary Search: Searches for a Pokémon by name in the sorted Pokédex
int binarySearch(const vector<Pokemon>& pokedex, const string& target) {
    int left = 0;
    int right = pokedex.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (pokedex[mid].name == target) {
            return mid; // Found
        }
        else if (pokedex[mid].name < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return -1; // Not found
}

int main() {
    vector<Pokemon> pokedex;
    string filename = "pokedex.txt";

    if (!loadPokedex(filename, pokedex)) {
        return 1; // Exit if loading failed
    }

    bubbleSort(pokedex);

    cout << "Welcome to the Pokedex!" << endl;

    bool continueSearching = true;
    while (continueSearching) {
        int choice = 0;
        while (true) { // Loop until a valid choice is made
            cout << "How would you like to search for a Pokemon?" << endl;
            cout << "1. By Number" << endl;
            cout << "2. By Name" << endl;
            cout << "Enter your choice (1 or 2): ";

            if (cin >> choice && (choice == 1 || choice == 2)) {
                break; // Exit the loop on a valid numeric choice
            }
            else {
                cout << "Invalid input! Please enter 1 or 2." << endl;
                cin.clear(); // Clear the error flag on cin
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            }
        }

        if (choice == 1) {
            int number;
            while (true) { // Validate number input
                cout << "Enter a Pokémon number (1-151): ";
                if (cin >> number && number >= 1 && number <= 151) {
                    break; // Exit loop if valid number is entered
                }
                else {
                    cout << "Invalid input! Please enter a number between 1 and 151." << endl;
                    cin.clear(); // Clear the error flag on cin
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                }
            }

            bool found = false;
            for (const auto& p : pokedex) {
                if (p.number == number) {
                    displayPokemon(p);
                    found = true;
                    break;
                }
            }

            if (!found) {
                cout << "Pokémon not found in the Pokédex!" << endl;
            }
        }
        else if (choice == 2) {
            string name;
            cin.ignore(); // Clear the input buffer
            while (true) { // Validate name input
                cout << "Enter the Pokémon name: ";
                getline(cin, name);
                if (!name.empty() && isalpha(name[0])) { // Ensure name starts with a letter
                    break;
                }
                else {
                    cout << "Invalid input! Please enter a valid Pokémon name." << endl;
                }
            }

            int index = binarySearch(pokedex, name);

            if (index != -1) {
                displayPokemon(pokedex[index]);
            }
            else {
                cout << "Pokémon not found in the Pokédex!" << endl;
            }
        }

        // Ask if the user wants to search again
        cout << "Would you like to search for another Pokémon? (y/n): ";
        char response;
        cin >> response;
        cin.ignore(); // Clear the newline from the buffer
        continueSearching = (response == 'y' || response == 'Y');
    }

    cout << "Thank you for using the Pokedex! Goodbye!" << endl;
    return 0;
}

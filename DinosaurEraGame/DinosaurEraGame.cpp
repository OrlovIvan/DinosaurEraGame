// DinosaurEraGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <PlayTable.h>

using namespace std;

int main()
{
    cout << "Choose game difficulty: 1 - Easy, 2 - Medium, 3 - Hard" << endl;
    int diff = 0;
    while(diff <= 0 || diff > 3)
        cin >> diff;

    diff--; // correction to fit the DifficultyLevel enum members
    DifficultyLevel level{DifficultyLevel::Easy};
    if (diff == static_cast<int>(DifficultyLevel::Medium))
        level = DifficultyLevel::Medium;
    else
        level = DifficultyLevel::Hard;
    PlayTable table(level);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

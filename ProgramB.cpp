/*
    Programming Language and IDE:
    The programming language used is C++, and the IDE is Visual Studio Code.

    Compiling, Building, and Executing:
    Click the arrow next to the play button in the top right corner of the screen and select "Run Code" to compile and run the program.

    Programmer(s):
    Mary Lorenz

    Date of Program Creation:
    10/04/2024

    Program Explanation:
    This program looks for a specific user's time log file based on their first and last name.
    If the log file is found, the program reads the contents of the file and validates the format of the log entries.
    The program then checks the validity of the log file and detects any errors in the log entries.
    If no errors are found, the program creates a report based on how many minutes are spent on each activity.

    Course:
    CMP SCI 4500-001

    Central Data Structure(s):
    TODO

    External Files Used:
    LastnameFirstnameLog.csv

    Outside Resources:
    Listed inside of the code as comments.
*/

#include <iostream>
#include <limits>
#include <string>
#include <fstream>

using namespace std;

int main()
{
    // Output program description
    cout << "This program reads a user's time log file and validates the format of the log file entries." << endl;
    cout << "If no errors are found, it creates a report based on the time spent on each activity." << endl
         << endl;

    // Pause the program to view the description
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << endl;

    /* First and last name prompts inspired by TeamXLogEntryLater.Y from Phase 1*/

    // Ask the user for their first and last name to find their log file
    string firstName, lastName;

    // Enter the fields to find the file
    while (lastName.empty())
    {
        cout << "Enter your last name: ";
        getline(cin, lastName);
        if (lastName.empty())
        {
            cout << "Error: Please enter your last name." << endl;
        }
    }
    while (firstName.empty())
    {
        cout << "Enter your first name: ";
        getline(cin, firstName);
        if (firstName.empty())
        {
            cout << "Error: Please enter your first name." << endl;
        }
    }

    // Concatenate the name of the log
    cout << endl;

    string cat = lastName + firstName + "Log.csv";

    // Check if the file exists
    ifstream checkFile(cat.c_str());
    if (!checkFile.good())
    {
        cout << "Error: A file with the name '" << cat << "' does not exist.";
        return -1;
    }
    else
    {
        cout << "Your file has been found!" << endl
             << endl;
    }

    system("pause");
    return 0;
}
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

using namespace std;

int main()
{
    // Output program description
    cout << "This program reads a user's time log file and validates the format of the log file entries." << endl; 
    cout << "If no errors are found, it creates a report based on the time spent on each activity." << endl << endl;

    // Pause the program to view the description
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << endl;

    system("pause");
    return 0;
}
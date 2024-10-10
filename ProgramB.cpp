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

/*
    Description:
    Handle an error by displaying an error message and closing the log file if necessary.

    Global Variable Usage:
    None

    Parameters:
    errorType - the type of error
    errorMessage - the error message to display
    fileName - the name of the file where the error occurred
    lineNumber - the line number where the error occurred
    logFile - the log file to close if the error type is "Error"

    Return Value:
    None
*/
void handleError(const string &errorType, const string &errorMessage, const string &fileName, int lineNumber, ifstream &logFile)
{
    // Display error message
    string message = errorType + ": " + errorMessage + " in file " + fileName + " at line " + to_string(lineNumber);
    cout << message << endl;

    // Close the log file if error type is "Error"
    if (errorType == "Error")
    {
        logFile.close();
    }
}

/*
    Description:
    Main function to run the program.

    Global Variable Usage:
    None

    Parameters:
    None

    Return Value:
    int - the exit status of the program
*/
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

    string logFileName = lastName + firstName + "Log.csv";

    // Check if the file exists
    ifstream logFile(logFileName.c_str());
    if (!logFile.good())
    {
        cout << "Error: A file with the name '" << logFileName << "' does not exist.";
        return -1;
    }
    else
    {
        cout << "Your file has been found!" << endl
             << endl;
    }

    /* Validation of log files inspired by ProgramA.cpp */

    // Check if the log file is empty
    if (logFile.peek() == std::ifstream::traits_type::eof())
    {
        handleError("Error", "Log file is empty", logFileName, 0, logFile);
        system("pause");
        return 0;
    }

    // Read the first line
    string line; // Line read from the log file

    // Read the first line
    if (!getline(logFile, line))
    {
        handleError("Error", "Unable to read the first line of the log file", logFileName, 1, logFile);
        system("pause");
        return 0;
    }

    // Check if the first line has two strings separated by a comma
    size_t commaPos = line.find(',');
    if (commaPos == string::npos || commaPos == 0 || commaPos == line.length() - 1)
    {
        handleError("Error", "Invalid format in the first line of the log file", logFileName, 1, logFile);
        system("pause");
        return 1;
    }

    // Read the second line
    if (!getline(logFile, line))
    {
        handleError("Error", "Unable to read the second line of the log file", logFileName, 2, logFile);
        system("pause");
        return 1;
    }

    // Check if the second line is "CS 4500" exactly
    if (line != "CS 4500")
    {
        handleError("Error", "Invalid class ID in the second line of the log file", logFileName, 2, logFile);
        system("pause");
        return 1;
    }

    // Check for no additional lines in the log file
    if (logFile.peek() == std::ifstream::traits_type::eof())
    {
        handleError("Error", "No time log entries found in the log file", logFileName, 3, logFile);
        system("pause");
        return 1;
    }

    // Read additional lines and validate the time entries
    int lineNumber = 3; // Line number in the log file

    while (getline(logFile, line))
    {
        // Check for trailing comma immediately
        if (line.back() == ',')
        {
            handleError("Error", "Trailing comma at end of line", logFileName, lineNumber, logFile);
            system("pause");
            return 1;
        }
    }

    system("pause");
    return 0;
}
/*
    Programming Language and IDE:
    The programming language used is C++, and the IDE is Visual Studio Code.

    Compiling, Building, and Executing:
    Click the arrow next to the play button in the top right corner of the screen and select "Run Code" to compile and run the program.

    Programmer(s):
    Mary Lorenz
    Elroi Belete
    Tony Matthews

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
    - activityDescriptions: A map that stores activity codes and their corresponding descriptions.
    - activityMinutes: A map that stores activity codes and the total minutes spent on each activity.

    External Files Used:
    LastnameFirstnameLog.csv

    Outside Resources:
    ProgramA.cpp, TeamXLogEntryLater.Y
*/

#include <iostream>
#include <limits>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <iomanip>

using namespace std;

// Activity codes and their corresponding descriptions
map<char, string> activityDescriptions = {
    {'0', "Reading Canvas site or textbook"},
    {'1', "Studying using a practice quiz"},
    {'2', "Taking a scoring quiz"},
    {'3', "Participating in a Canvas discussion, DX"},
    {'4', "Meeting with your team"},
    {'5', "Working on documentation"},
    {'6', "Working on designs"},
    {'7', "Programming"},
    {'8', "Working on a test plan or doing testing"},
    {'9', "Studying for the final exam"},
    {'A', "Conferring with the instructor (outside team meeting)"},
    {'B', "Working on a mini-lecture video or reading"},
    {'C', "Viewing a video or website that is not a mini-lecture, but relevant to the course"},
    {'D', "Other"}};

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
    Check if the date format is valid.

    Global Variable Usage:
    None

    Parameters:
    date - the date to validate

    Return Value:
    bool - true if the date is valid, false otherwise
*/
bool isValidDate(const string &date)
{
    // Check if the date format is valid
    if (date.length() == 10 && date[2] == '/' && date[5] == '/')
    {
        // Split the date into month, day, and year
        string m = date.substr(0, 2);
        string d = date.substr(3, 2);
        string y = date.substr(6, 4);
        int m1 = stoi(m);
        int d1 = stoi(d);
        int y1 = stoi(y);

        // Date format is valid
        if (m1 <= 12 && d1 <= 31)
        {
            return true;
        }
        // Date format is invalid
        else
        {
            return false;
        }
    }
    // No date is recognized
    else
    {
        return false;
    }
}

/*
    Description:
    Check if the time format is valid.

    Global Variable Usage:
    None

    Parameters:
    time - the time to validate

    Return Value:
    bool - true if the time is valid, false otherwise
*/
bool isValidTime(const string &time)
{
    if (time.length() == 5 && time[2] == ':')
    {
        // Split the time into hours and minutes
        string h = time.substr(0, 2);
        string m = time.substr(3, 2);
        int h1 = stoi(h);
        int m1 = stoi(m);

        // Time format is valid
        if (h1 >= 0 && h1 <= 23 && m1 >= 0 && m1 <= 59)
        {
            return true;
        }
        // Time format is invalid
        else
        {
            return false;
        }
    }
    // No time is recognized
    else
    {
        return false;
    }
}

/*
    Description:
    Calculate the difference in minutes between two times.

    Global Variable Usage:
    None

    Parameters:
    startTime - the start time
    endTime - the end time

    Return Value:
    int - the difference in minutes between the two times
*/
int timeDifferenceInMinutes(const string &startTime, const string &endTime)
{
    // Split the start and end times into hours and minutes
    int startHour = stoi(startTime.substr(0, 2));
    int startMinute = stoi(startTime.substr(3, 2));
    int endHour = stoi(endTime.substr(0, 2));
    int endMinute = stoi(endTime.substr(3, 2));

    // Calculate the total minutes for the start and end times
    int startTotalMinutes = startHour * 60 + startMinute;
    int endTotalMinutes = endHour * 60 + endMinute;

    return endTotalMinutes - startTotalMinutes;
}

/*
    Description:
    Check if the number of people is valid.

    Global Variable Usage:
    None

    Parameters:
    numPeople - the number of people to validate

    Return Value:
    bool - true if the number of people is valid, false otherwise
*/
bool isValidNumberOfPeople(int numPeople)
{
    return numPeople >= 1 && numPeople <= 50;
}

/*
    Description:
    Check if the activity code is valid.

    Global Variable Usage:
    None

    Parameters:
    activityCode - the activity code to validate

    Return Value:
    bool - true if the activity code is valid, false otherwise
*/
bool isValidActivityCode(char activityCode)
{
    // Valid activity codes
    string validCodes = "0123456789ABCD";
    return validCodes.find(activityCode) != string::npos;
}

/*
    Description:
    Check if the note format is valid.

    Global Variable Usage:
    None

    Parameters:
    note - the note to validate

    Return Value:
    bool - true if the note is valid, false otherwise
*/
bool isValidNote(const string &note)
{
    // Trim any whitespace from the end of the note
    string trimmed = note;
    while (!trimmed.empty() && isspace(trimmed.back()))
        trimmed.pop_back();

    return trimmed.find(',') == string::npos &&
           trimmed.length() <= 80 &&
           !trimmed.empty() &&
           trimmed.back() != ',';
}

/*
    Description:
    Generate a report based on the minutes spent on each activity.

    Global Variable Usage:
    activityDescriptions - map of activity codes to descriptions

    Parameters:
    firstName - the first name of the user
    lastName - the last name of the user
    activityMinutes - map of activity codes to minutes spent on each activity

    Return Value:
    None
*/
void generateReport(const string &firstName, const string &lastName, const map<char, int> &activityMinutes)
{
    // Create a report file based on the user's name
    string reportFileName = lastName + firstName + "LogReport.txt";
    ofstream reportFile(reportFileName);

    // Create a string of valid activity codes
    string validCodes = "0123456789ABCD";

    // Format report for both file and screen output
    auto writeReport = [&](ostream &out)
    {
        out << "Name: " << firstName << " " << lastName << endl;
        out << "Class: " << "CS 4500" << endl
            << endl;
        out << "ACTIVITY" << endl;
        out << setw(2) << ' ' << "CODE" << setw(4) << ' ' << "MINUTES" << setw(10) << ' ' << "MEANING" << endl;

        // Output each activity code and its minutes
        for (char code : validCodes)
        {
            int minutes = activityMinutes.count(code) ? activityMinutes.at(code) : 0;
            out << setw(4) << ' ' << code << ":" << setw(5) << ' ' 
                << setw(4) << setfill('0') << minutes << setfill(' ') 
                << setw(6) << ' ' << activityDescriptions[code] << endl;
        }
    };

    // Write the report to the file and screen
    writeReport(reportFile);
    writeReport(cout);

    // Close the report file
    reportFile.close();

    cout << "\nReport has been written to " << reportFileName << endl;
    cout << "Goodbye!" << endl;
}

/*
    Description:
    Main function to run the program.

    Global Variable Usage:
    activityDescriptions - map of activity codes to descriptions

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
        system("pause");
        return 1;
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
        return 1;
    }

    // Read the first line
    string line; // Line read from the log file

    // Read the first line
    if (!getline(logFile, line))
    {
        handleError("Error", "Unable to read the first line of the log file", logFileName, 1, logFile);
        system("pause");
        return 1;
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
    int lineNumber = 3;             // Line number in the log file
    map<char, int> activityMinutes; // Minutes spent on each activity

    while (getline(logFile, line))
    {
        // Check for trailing comma immediately
        if (line.back() == ',')
        {
            handleError("Error", "Trailing comma at end of line", logFileName, lineNumber, logFile);
            system("pause");
            return 1;
        }

        istringstream iss(line); // Input string stream to split the line into items
        vector<string> items;    // Items in the line
        string item;             // Item read from the line

        // Split the line by commas
        while (getline(iss, item, ','))
        {
            items.push_back(item);
        }

        // Check if the line has the correct number of items immediately
        if (items.size() < 5 || items.size() > 6)
        {
            handleError("Error", "Invalid number of items in the time log entry", logFileName, lineNumber, logFile);
            system("pause");
            return 1;
        }

        // Check if the first item is a valid date
        if (!isValidDate(items[0]))
        {
            handleError("Error", "Invalid date format in the time log entry", logFileName, lineNumber, logFile);
            system("pause");
            return 1;
        }

        // Check if the second and third items are valid times
        if (!isValidTime(items[1]) || !isValidTime(items[2]))
        {
            handleError("Error", "Invalid time format in the time log entry", logFileName, lineNumber, logFile);
            system("pause");
            return 1;
        }

        // Check if the start time is earlier than the end time
        if (timeDifferenceInMinutes(items[1], items[2]) < 0)
        {
            handleError("Error", "Start time is later than end time in the time log entry", logFileName, lineNumber, logFile);
            system("pause");
            return 1;
        }

        // Check if the fourth item is a valid number of people
        try
        {
            int numPeople = stoi(items[3]);
            if (!isValidNumberOfPeople(numPeople))
            {
                handleError("Error", "Invalid number of people in the time log entry", logFileName, lineNumber, logFile);
                system("pause");
                return 1;
            }
        }
        catch (const invalid_argument &)
        {
            handleError("Error", "Non-numeric value for number of people in the time log entry", logFileName, lineNumber, logFile);
            system("pause");
            return 1;
        }
        catch (const out_of_range &)
        {
            handleError("Error", "Number of people value out of range in the time log entry", logFileName, lineNumber, logFile);
            system("pause");
            return 1;
        }

        // Check if the fifth item is a valid activity code
        if (items[4].length() != 1 || !isValidActivityCode(items[4][0]))
        {
            handleError("Error", "Invalid activity code in the time log entry", logFileName, lineNumber, logFile);
            system("pause");
            return 1;
        }

        // Check if the activity code is "D" and validate the note
        if (items[4][0] == 'D')
        {
            if (items.size() != 6)
            {
                handleError("Error", "Missing note in the time log entry", logFileName, lineNumber, logFile);
                system("pause");
                return 1;
            }

            if (!isValidNote(items[5]))
            {
                handleError("Error", "Invalid note format in the time log entry", logFileName, lineNumber, logFile);
                system("pause");
                return 1;
            }
        }
        // Check if the activity code is not "D" and there is no note
        else if (items.size() == 6)
        {
            // Check if the note is valid if there is one
            if (!isValidNote(items[5]))
            {
                handleError("Error", "Invalid note format in the time log entry", logFileName, lineNumber, logFile);
                system("pause");
                return 1;
            }
        }

        // Calculate and accumulate minutes for this activity
        char activityCode = items[4][0];
        int minutes = timeDifferenceInMinutes(items[1], items[2]);
        activityMinutes[activityCode] += minutes;

        lineNumber++;
    }

    // Tell the user that the log file is valid
    cout << "Success: Valid log file detected." << endl;

    // Close the log file
    logFile.close();

    // Create a report based on the minutes spent on each activity
    generateReport(firstName, lastName, activityMinutes);

    system("pause");
    return 0;
}
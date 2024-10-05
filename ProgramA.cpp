/*
    Programming Language and IDE:
    The programming language used is C++, and the IDE is Visual Studio Code.

    Compiling, Building, and Executing:
    Click the arrow next to the play button in the top right corner of the screen and select "Run Code" to compile and run the program.

    Programmer(s):
    Tony Matthews

    Date of Program Creation:
    10/03/2024

    Course Name:
    CMP SCI 4500-001

    Program Explanation:
    This program reads filenames from the current directory that match the pattern of "XLog.csv" and validates their format as time log files. It then outputs the results to the screen and an external file. Validity checks include ensuring the file is not empty, has correctly formatted entries, and doesn't contain invalid time entries.

    Central Data Structure(s):


    External Files Used:
    XLog.csv

    Outside Resources:

    Source: https://stackoverflow.com/questions/67273/how-do-you-iterate-through-every-file-directory-recursively-in-standard-c
    Information: This source provided information on how to iterate over files in a directory using the filesystem library in C++.

    Source: https://stackoverflow.com/questions/2390912/checking-for-an-empty-file-in-c
    Information: This source provided information on how to check if a file is empty in C++.
*/

#include <sstream>
#include <iostream>
#include <limits>
#include <filesystem>
#include <regex>
#include <fstream>
#include <cctype>

using namespace std;
namespace fs = filesystem;

/*
    Description:
    Check if the log file name format is valid.

    Global Variable Usage:
    None

    Parameters:
    fileName - the name of the log file to validate

    Return Value:
    bool - true if the file name is valid, false otherwise
*/
bool isValidFileName(const string &fileName)
{
    // Check if the file name matches the pattern "XLog.csv"
    regex pattern("^[A-Za-z]+\\.csv$", regex_constants::icase);
    return regex_match(fileName, pattern);
}

/*
    Description:
    Handle error messages.

    Global Variable Usage:
    None

    Parameters:
    errorType - the type of error
    errorMessage - the error message to display
    fileName - the name of the log file that caused the error
    lineNumber - the line number where the error was found
    outFile - the output file stream to write the error message
    logFile - the input file stream to close

    Return Value:
    None
*/
void handleError(const string &errorType, const string &errorMessage, const string &fileName, int lineNumber, ofstream &outFile, ifstream &logFile)
{
    // Display error message
    string message = errorType + ": " + errorMessage + " in file " + fileName + " at line " + to_string(lineNumber);
    cout << message << endl;
    outFile << message << endl;

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
    return note.find(',') == string::npos && note.length() <= 80 && note.back() != ',';
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
    cout << "This program validates the format of log files and outputs the results of the validation process to the screen and an external file" << endl
         << endl;

    // Output prompt to continue
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << endl;

    cout << "Checking for valid log files..." << endl
         << endl;

    vector<string> validFiles; // Vector to store valid log files

    // Iterate over files in the current directory and validate log files
    for (const auto &entry : fs::directory_iterator(fs::current_path()))
    {
        if (entry.is_regular_file())
        {
            string fileName = entry.path().filename().string();
            if (isValidFileName(fileName))
            {
                cout << "Valid log file found: " << fileName << endl;
                validFiles.push_back(fileName);
            }
        }
    }

    cout << endl;

    // Print error message if no log files are found and exit program
    if (validFiles.empty())
    {
        cout << "No valid log files found in the current directory." << endl;
        system("pause");
        return 1;
    }

    // Open a file to write the results of the validation process
    ofstream outFile("ValidityChecks.txt");
    if (!outFile)
    {
        cout << "Error: Unable to open output file." << endl;
        system("pause");
        return 1;
    }

    // Check first two lines of each log file for valid entries
    for (int i = 0; i < validFiles.size(); i++)
    {
        // Open log file for reading
        ifstream logFile(validFiles[i]);

        // Check if the log file still exists
        if (!logFile)
        {
            handleError("Error", "Unable to open log file", validFiles[i], 0, outFile, logFile);
        }

        // Check if the log file is empty
        if (logFile.peek() == std::ifstream::traits_type::eof())
        {
            handleError("Error", "Log file is empty", validFiles[i], 0, outFile, logFile);
        }

        // Read the first two lines of the log file
        string line; // Line read from the log file

        // Read the first line
        if (!getline(logFile, line))
        {
            handleError("Error", "Unable to read the first line of the log file", validFiles[i], 1, outFile, logFile);
            continue;
        }

        // Check if the first line has two strings separated by a comma
        size_t commaPos = line.find(',');
        if (commaPos == string::npos || commaPos == 0 || commaPos == line.length() - 1)
        {
            handleError("Error", "Invalid format in the first line of the log file", validFiles[i], 1, outFile, logFile);
            continue;
        }

        // Read the second line
        if (!getline(logFile, line))
        {
            handleError("Error", "Unable to read the second line of the log file", validFiles[i], 2, outFile, logFile);
            continue;
        }

        // Check if the second line is "CS 4500" exactly
        if (line != "CS 4500")
        {
            handleError("Error", "Invalid class ID in the second line of the log file", validFiles[i], 2, outFile, logFile);
            continue;
        }

        // Check for any additional lines in the log file
        if (logFile.peek() == std::ifstream::traits_type::eof())
        {
            logFile.close();
            continue;
        }

        // Read additional lines and validates the time entries
        int lineNumber = 3; // Line number in the log file
        while (getline(logFile, line))
        {
            istringstream iss(line); // Input string stream to split the line into items
            vector<string> items;    // Items in the line
            string item;             // Item read from the line

            // Read the first five items (date, start time, end time, number of people, activity code)
            for (int i = 0; i < 5; ++i)
            {
                if (!getline(iss, item, ','))
                {
                    handleError("Error", "Invalid number of items in the time log entry", validFiles[i], lineNumber, outFile, logFile);
                    continue;
                }
                items.push_back(item);
            }

            // Read the remaining part of the line as the note (if present)
            if (getline(iss, item))
            {
                items.push_back(item);
            }

            // Check if the line has the correct number of items
            if (items.size() != 5 && items.size() != 6)
            {
                handleError("Error", "Invalid number of items in the time log entry", validFiles[i], lineNumber, outFile, logFile);
                continue;
            }

            // Check if the first item is a valid date
            if (!isValidDate(items[0]))
            {
                handleError("Error", "Invalid date format in the time log entry", validFiles[i], lineNumber, outFile, logFile);
                continue;
            }

            // Check if the second and third items are valid times
            if (!isValidTime(items[1]) || !isValidTime(items[2]))
            {
                handleError("Error", "Invalid time format in the time log entry", validFiles[i], lineNumber, outFile, logFile);
                continue;
            }

            // Check if start time is earlier than end time
            int duration = timeDifferenceInMinutes(items[1], items[2]);
            if (duration < 0)
            {
                handleError("Error", "End time is earlier than start time in the time log entry", validFiles[i], lineNumber, outFile, logFile);
                continue;
            }

            // Warn if the duration is more than 240 minutes (4 hours)
            if (duration >= 240)
            {
                handleError("Warning", "Duration exceeds is at least 4 hours in the time log entry", validFiles[i], lineNumber, outFile, logFile);
            }

            // Check if the fourth item is a valid number of people
            try
            {
                int numPeople = stoi(items[3]);
                if (!isValidNumberOfPeople(numPeople))
                {
                    handleError("Error", "Invalid number of people in the time log entry", validFiles[i], lineNumber, outFile, logFile);
                    continue;
                }
            }
            catch (const invalid_argument &)
            {
                handleError("Error", "Non-numeric value for number of people in the time log entry", validFiles[i], lineNumber, outFile, logFile);
                continue;
            }
            catch (const out_of_range &)
            {
                handleError("Error", "Number of people value out of range in the time log entry", validFiles[i], lineNumber, outFile, logFile);
                continue;
            }

            // Check if the fifth item is a valid activity code
            if (items[4].length() != 1 || !isValidActivityCode(items[4][0]))
            {
                handleError("Error", "Invalid activity code in the time log entry", validFiles[i], lineNumber, outFile, logFile);
                continue;
            }

            // Check if the activity code is "D" and validate the note
            if (items[4][0] == 'D')
            {
                if (items.size() != 6)
                {
                    handleError("Error", "Missing note for activity code 'D' in the time log entry", validFiles[i], lineNumber, outFile, logFile);
                    continue;
                }
                if (!isValidNote(items[5]))
                {
                    handleError("Error", "Invalid note format in the time log entry", validFiles[i], lineNumber, outFile, logFile);
                    continue;
                }
            }
            // Check if the activity code is not "D" and there is no note
            else if (items.size() == 6)
            {
                if (!isValidNote(items[5]))
                {
                    handleError("Error", "Invalid note format in the time log entry", validFiles[i], lineNumber, outFile, logFile);
                    continue;
                }
            }

            lineNumber++;
        }

        // Close the log file
        logFile.close();
    }

    // Pauses the program in exe file to see the output
    system("pause");
    return 0;
}
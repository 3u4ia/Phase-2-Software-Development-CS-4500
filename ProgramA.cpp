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

    Source:
    Information:
*/

#include <iostream>
#include <limits>

using namespace std;

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
    cout << "This program validates the format of log files and outputs the results of the validation process to the screen and an external file" << endl << endl;

    // Output prompt to continue
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << endl;

    // Pauses the program in exe file to see the output
    system("pause");
    return 0;
}
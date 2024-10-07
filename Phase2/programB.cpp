// Programming language: C++

// IDE: Visual Studio Code

// Chief programmer(s) for ProgramB: Mary Lorenz, ...

// Group members: Elroi Belete, Mary Lorenz, Samuel Irvine, & Tony Matthews

// Team: Phase 2 small team 10.

// Course: CMP_SCI-4500-001

// Run, build, and compile the code: Click the arrow next to the play button in the top right corner of the screen and select "Run Code" to compile and run the program.

// To build an .exe file on your computer: 'g++ -o ProgramB.exe ProgramB.cpp'

// Date of program creation: 10/04/2024 

// Description of central data structures: TO DO****

// External sources used in preparing the program: Listed inside of the code as comments. 

#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

// Menu function
void menu() {
string input; 

cout << 
"This program prompts the user for a first and last name string. \n"
"User input is then used to find a corresponding file in the format: 'LastnameFirstnameLog.csv' \n"
"The program searches for a file in the same directory in which the project is located. \n" 
"When a valid file is located, the program will create a report. This report includes \n"
"the following categories: first name, last name, activity code, military time, and notes. \n"
"All information will be displayed to the user in a report format. \n";

cout << "\nWhen you are ready to continue, press 'c'." << endl;

do {

getline(cin, input);

// Rejects the following inputs: digits, strings, non-lowercase 'c' characters, the 'ENTER' key.
// Accepts: 'c'
if (input.empty() || (input[0] != 'c') || input.length() > 1) {
cout << "Invalid input. Please press 'c' to continue.";

}else{

break;

}
}

while(true);
}

// Error checking for input. (firstname) (lastname)
// Rejects the following inputs: the 'ENTER' key, single characters, & digits. 
// Accepts strings only. (2 or more characters)
bool validName (const string& name) {

if (name.empty() || name.length() == 1){
return false;
}

/*

1.) for (char character: name) 
- Iterates through each letter in 'name'.

2.) if (!isalpha(character))
-  Checks if 'character' is not a letter. (a-z), (A-Z)

3.) return false;
- Stop the function, reject the input.

*/

for (char character : name) {
if (!isalpha(character)){
return false;
    
}
}

return true;
}

// Split function
// Researched on StackOverflow.com
// Forum titled, 'How can I split a vector <string> and access what I need in it'
/*
1.) vector<string> split (const string& str, char delimiter)
- Takes 'str' and splits it into tokens.

2.) vector <string> tokens
- Initializes and empty vector called tokens.

3.) string token
- Declares an empty string called token.

4.) istringstream tokenStream(str)
- Creates an input stream object called 'tokenStream' based on 'str'.

5.) while (getline(tokenStream, token, delimiter))
- Extracts tokens from 'tokenStream' using 'getline'
- Loops while 'getline' can read tokens.

6.) tokens.push_back(token);
- Adds a token substring.

*/

vector<string> split(const string& str, char delimiter) {
vector<string> tokens;
string token;
istringstream tokenStream(str);
while (getline(tokenStream, token, delimiter)) {
tokens.push_back(token);
}
return tokens;
}

bool activityCodeOther (const string& code) {
return (code == "D");
}

// Search for a file based on the user-entered first/last name in the format 'LastnameFirstnameLog.csv'.
void fileSearch(string *firstname, string *lastname) {
string filename;
string line;

// Prompt user for a firstname (only takes strings - 2 or more characters)
// Rejects the following: the 'ENTER' key, single characters, & digits.
do {

cout << "Enter your first name: ";

getline (cin, *firstname);

if (!validName(*firstname)){

cout << "Invalid input. Please enter a string. " << endl;

}
} 
while (!validName(*firstname));

do {

// Prompt user for a lastname (only takes strings)
// Rejects the following: the 'ENTER' key, single characters, & digits.
cout << "Enter your lastname: ";

getline (cin, *lastname);

if (!validName(*lastname)){

cout << "Invalid input. Please enter a string. " << endl;

}
} 
while (!validName(*lastname));

// Combine the firstname and lastname with Log.csv
filename = *lastname + *firstname + "Log.csv";

// Open the file with the filename (lastname input + firstname input + 'Log.csv')
ifstream file(filename);

// Output the users' filename to the console.
if(!file.is_open()) {
cout << "File: '" << filename << "' does not exist in the project directory." << endl;
cout << "Press the 'ENTER' key to exit." << endl;
cin.ignore();
cin.get();

return;
}

cout << "File: " << filename << endl;

// Validate line1 (Does it contain two fields? 'Lastname, Firstname' ?)
if (getline(file,line)) {

// This line splits 'line' into separate tokens when a ',' appears. 
/* My issue (now fixed):
I was using the token method to split by comma. But many '.csv' files output
multiple commas, meaning I was creating an error in the code by only
checking for the existance of fields through the presence of a comma (e.g., too many fields).
Because of this, I decided to check if a field is truly 'empty' to check for true
validity. (e.g., is it more than just a comma present?)*/

vector<string> field = split (line, ',');

int notEmpty = 0;
string lastnameField;
string firstnameField;

// Assign the first nonEmpty field to 'lastnameField'.
// Assign the second nonEmpty field to 'firstnameField'.
// 'full' represents an individual string from the element 'field'.
for (const string& full : field) {
if (!full.empty()) {
if (notEmpty == 0) {
lastnameField = full;
}
else if (notEmpty == 1) {
firstnameField = full;
}
notEmpty ++;
}
}

// Checks if there are exactly two nonEmpty fields.
// If this is true, the function will continue.
if (notEmpty == 2 && lastnameField == *lastname && firstnameField == *firstname) {

}else{

cout << "Error. Line1 is invalid, it should contain two fields: 'lastname,firstname'. " << endl;
cout << "Press the 'ENTER' key to exit." << endl;
cin.ignore();
cin.get();
file.close();

return;

}
}else{

cout << "Error. The file is empty or it could not be opened." << endl;
cout << "Press the 'ENTER' key to exit. " << endl;
cin.ignore();
cin.get();
file.close();
return;

}

// validate line2 (Does it contain one field: 'classID' ?)
if (getline(file,line)) {
vector<string> field = split (line, ',');

int notEmpty = 0;
string classIdField;

// Assign the first nonEmpty element to classIdField.
for (const string& full : field){
if (!full.empty()){
classIdField = full;
notEmpty ++; 
break;
}
}

// If line2 has just one nonEmpty element (classID).
if (notEmpty == 1) {

}else{

cout << "Error. Line2 is invalid, it should contain one field: 'classID'." << endl;
cout << "Press the 'ENTER' key to exit. " << endl;
cin.ignore();
cin.get();
file.close();
return;

}
}else{

cout << "Error. The file is empty or it could not be opened." << endl;
cout << "Press the 'ENTER' key to exit. " << endl;
cin.ignore();
cin.get();
file.close();
return;

}

// validate the rest of the lines.
// If a line is invalid, print to screen the line number.
// Additionally, output why it is invalid. 
int lineNumber = 3;
while(getline(file,line)){
vector<string> field = split (line, ',');

// Required fields: date, start time, end time, number of people, & activity code.
// Optional field: notes
// Notes is not optional if the user selects 'D', which corresponds to 'other'.
int notEmpty = 0;
string dateField; // 0
string timeStartField; // 1
string timeEndField; // 2
string numberOfPeopleField; // 3
string activityCodeField; // 4
string notesField; // 5 
// 0-5 (equating to 6 fields)

for (const string& full : field) {
if (!full.empty()) {
if (notEmpty == 0) {
dateField = full;
} else if (notEmpty == 1) {
timeStartField = full;
} else if (notEmpty == 2) {
timeEndField = full;
} else if (notEmpty == 3) {
numberOfPeopleField = full;
} else if (notEmpty == 4) {
activityCodeField = full;
} else if (notEmpty == 5) {
notesField = full;
}
notEmpty++;
}
}

// IF it has less than five fields - or seven or more fields, there must be an error.
if ( notEmpty < 5 ) {
cout << "Line: '" << lineNumber << "' requires 5 fields: date, start time, end time, number of people, & activity code.\n";
cout << "There cannot be less than 5 fields.\n";
cout << "Press the 'ENTER' key to exit" << endl;
cin.ignore();
cin.get();
file.close();
return;
}
else if (notEmpty >= 7) {
cout << "Line: '" << lineNumber << "' can have a maximum of 6 fields. This row has too many fields." << endl;
cout << "Press the 'ENTER' key to exit." << endl;
cin.ignore();
cin.get();
file.close();
return;
}

// If the user has 'D' or other present in their '.csv' file, but they never input a 'note' in the already existing '.csv'.
// Checks if there are less than 6 sections, meaning there is no 'notes' section present, otherwise there would be 6 fields. 
// There cannot be more than 6 fields. If it is equal to or greater than seven there is an error.
if(activityCodeOther(activityCodeField)) {
if (notEmpty != 6) {
cout << "Line: '" << lineNumber << "' requires a 'note' field, because you entered activity code 'D'/'other'.\n";
cout << "You cannot have less than 6 fields.\n";
cout << "Press the 'ENTER' key to exit." << endl;
cin.ignore();
cin.get();
file.close();
return;
}
}
lineNumber++;
}

// 'file.close() not needed for later parts of the code.
// THIS IS TEMPORARY (DELETE FOR LATER SECTIONS)
file.close(); // temp
cout << "The file contains no errors.\n"; // please keep
}

int main () {
    string firstName;
    string lastName;

    // Call the menu.
    menu();

    // Call the fileSearch function. 
    fileSearch(&firstName, &lastName);

    return 0;

}
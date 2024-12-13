// ------------------------------------------------------------------
// Declaration of Authorship :
// Name : VENKATA BHUVAN KOSURU
// Roll No: 2301AI33
// --------------------------------------------------------------------

#include <bits/stdc++.h>
// some short forms for simplicity of code
#define PB push_back

using namespace std;

// start of the code
// some global variables :- location ; present line number in code ; program counter (PC) ;
int PC = 0;              // PC initialized to 0
int present_line_no = 1; // line number initialize to 1 (1st line)
int loc;
int literal_counter = 10000; // counter for literals (literal -  "like a number or a string, that is directly specified in the source code")

// FEW FUNCTIONS WHICH WE USE IN THE MAIN CODE

// A CODE CONTAINS 3 SEGMENTS :- Label ; mnemonic ; operand
struct Code_STRUCTURE
{
    string Label = "";
    string Mnemonic = ""; // INITIALIZE ALL TO ""
    string Operand = "";
    int pc;
};

// FUNCTION TO CHECK WETHER A STRING IS MNEMONIC OR NOT

bool IS_Mnemonic(unordered_map<string, int> mnemonic, string operand)
{ // compare the mnemonic with the mnemonics list we made in the int main
    int mne_count = 0;
    if (mnemonic.find(operand) == mnemonic.end())
    {
        mne_count += 0;
        return false;
    } // false ; if pointer is not present in the list
    mne_count++;
    return true; // true ; if pointer is present in the list
}

// FUNCTION TO CHECK WETHER A STRING IS LABEL OR NOT

bool IS_Label(string Label)
{ /*
      #CONDITIONS to check :-
         1] pointer must start with a an alphabet (not a number )
         2] last part of the Label must be an ":"
  */
    if (Label.length() < 2)
    {
        return false;
    }
    if ((Label[0] <= 'z' && Label[0] >= 'a') || (Label[0] <= 'Z' && Label[0] >= 'A'))
    {
        if (Label[Label.length() - 1] == ':')
        {
            return true;
        }
    }
    return false;
}

// A FUNCTION TO SEPARATE VARIOUS PARTS OF CODE THAT IS LABEL; MNE ; VALUE etc ;

string Separate(string s)
{                              // Pass by value
    string req_substring = ""; // String to store the extracted part

    // Skip leading whitespace
    while (loc < s.length() && isspace(s[loc]))
    {
        loc++;
    }

    // Extract the first "word" (either until whitespace or a colon)
    while (loc < s.length() && !isspace(s[loc]))
    {
        if (s[loc] == ':')
        { // Check for a Label with a colon
            req_substring += s[loc++];
            return req_substring; // Return immediately if a Label is detected
        }
        req_substring += s[loc++];
    }

    return req_substring; // Return the extracted "word"
}

// IF ITS A MNEMONIC THEN FUNCTIONS TO CHECK TYPE OF MNEMONIC

// 1 . VALUE TYPE MNEMONIC

bool Mnemonic_Type_Value(string temporary)
{
    // STORE VALUE- TYPE MNEMONICS IN A SEPARATE VALUE_MAP

    unordered_map<string, int> value_map;
    value_map["data"] = 1;
    value_map["ldc"] = 1;
    value_map["adc"] = 1;
    value_map["adj"] = 1;
    value_map["SET"] = 1;

    // CHECK IF THE MNEMONIC IS IN VALUE_MAP OR NOT

    if (value_map.find(temporary) != value_map.end())
        return true;

    return false;
}

// 2 . ONE - OPERAND TYPE MNEMONIC

bool One_Operand(string temporary)
{
    // STORE ONE_OPERAND - TYPE MNEMONICS IN A SEPARATE ONE_OPERAND_MAP

    unordered_map<string, int> one_operand_map;
    one_operand_map["ldc"] = 0;
    one_operand_map["adc"] = 1;
    one_operand_map["ldl"] = 2;
    one_operand_map["stl"] = 3;
    one_operand_map["ldnl"] = 4;
    one_operand_map["stnl"] = 5;
    one_operand_map["10"] = 6;
    one_operand_map["adj"] = 10;
    one_operand_map["call"] = 13;
    one_operand_map["brz"] = 15;
    one_operand_map["brlz"] = 16;
    one_operand_map["br"] = 17;
    one_operand_map["data"] = 19;
    one_operand_map["SET"] = 20;

    // CHECK IF THE MNEMONIC IS IN ONE_OPERAND_MAP OR NOT

    if (one_operand_map.find(temporary) != one_operand_map.end())
        return true;

    return false;
}

// 3 . ZERO - OPERAND TYPE MNEMONIC

bool Zero_Operand(string temporary)
{
    // STORE ZERO_OPERAND - TYPE MNEMONICS IN A SEPARATE ZERO_OPERAND_MAP

    unordered_map<string, int> zero_operand_map;
    zero_operand_map["add"] = 6;
    zero_operand_map["sub"] = 7;
    zero_operand_map["shl"] = 8;
    zero_operand_map["shr"] = 9;
    zero_operand_map["a2sp"] = 11;
    zero_operand_map["sp2a"] = 12;
    zero_operand_map["return"] = 14;
    zero_operand_map["HALT"] = 18;

    // CHECK IF THE MNEMONIC IS IN ZERO_OPERAND_MAP OR NOT

    if (zero_operand_map.find(temporary) != zero_operand_map.end())
        return true;

    return false;
}

// TO CHECK FOR THE ANY STRING WEATHER ITS A VALUE OR NOT !

bool Is_Digits(string input)

{
    if (input.empty()) // Check for empty string
        return false;

    size_t idx = 0; // Variable to track the current position in the string

    // NEGATIVE NUMBERS(DECIMAL)

    if (input[0] == '-' && input.length() > 1) // Check for negative numbers
        input = input.substr(1);               // Remove the negative sign for further checks

    // HEXA DECIMAL NUMBERS

    if (input[0] == '0' && input.length() > 1 && input[1] == 'x')
    {            // Check for hexadecimal
        idx = 2; // Skip "0x" prefix
        while (idx < input.length())
        {
            if (isdigit(input[idx]) || (input[idx] <= 'f' && input[idx] >= 'a') || (input[idx] <= 'F' && input[idx] >= 'A'))
                idx++;
            else
                return false;
        }
        return true;
    }

    if (input[0] == '0' && input.length() == 1) // Special case for "0"
        return true;

    // OCTAL NUMBER

    if (input[0] == '0')
    {            // Check for octal
        idx = 1; // Skip "0" prefix
        while (idx < input.length())
        {
            if (input[idx] >= '0' && input[idx] <= '7')
                idx++;
            else
                return false;
        }
        return true;
    }

    // DECIMAL NUMBER

    while (idx < input.length())
    {
        if (!isdigit(input[idx]))
            return false;
        idx++;
    }

    return true;
}

// AFTER MAKING SURE THAT THE VALUE IS DIGIT ; WE NEED TO CHECK FOR TYPE OF DIGIT
// FUNCTIONS TO CHECK FOR TYPE OF DIGITS !

// 1 . DECIMAL - NUMBER

bool Is_Decimal(string value)

{
    if (value.empty()) // Check for empty string
        return false;

    size_t index = 0; // Variable to track the current position in the string

    // Check for optional leading '+' or '-'

    if (value[index] == '-' || value[index] == '+')
    {
        index++; // Skip the sign character
    }

    // Handle the case where the string is a single '0'

    if (value[index] == '0' && value.length() == 1 + index)
    {
        return true;
    }

    // Handle the case where the string starts with '0' but is longer than 1 character

    else if (value[index] == '0')
    {
        return false;
    }

    // Check if all characters are digits (decimal number)

    while (index < value.length())
    {
        if (!isdigit(value[index]))
        {
            return false;
        }
        index++;
    }

    return true;
}

// 2 . OCTAL - NUMBER

bool Is_Octal(string value)

{
    if (value.empty()) // Check for empty string
        return false;

    size_t index = 0; // Variable to track the current position in the string

    // Check if the string starts with '0'

    if (value[index] == '0')
    {
        index++; // Skip the '0' prefix

        // Check if all characters are valid octal digits (0-7)

        while (index < value.length())
        {
            if (value[index] >= '0' && value[index] <= '7')
            {
                index++;
            }
            else
            {
                return false;
            }
        }
        return true;
    }

    // Return false if the string does not start with '0'

    return false;
}

// 3 . HEXA - DECIMAL - NUMBER

bool Is_Hexadecimal(string value)

{
    if (value.empty()) // Check for empty string
        return false;

    size_t index = 0; // Variable to track the current position in the string

    // Check if the string starts with "0x" or "0X" (optional for hexadecimals)

    if (value[index] == '0' && (value[index + 1] == 'x' || value[index + 1] == 'X'))
    {
        index += 2; // Skip the "0x" or "0X" prefix

        // Check if all characters are valid hexadecimal digits (0-9, a-f, A-F)

        while (index < value.length())
        {
            if ((value[index] >= '0' && value[index] <= '9') ||
                (value[index] >= 'a' && value[index] <= 'f') ||
                (value[index] >= 'A' && value[index] <= 'F'))
            {
                index++;
            }
            else
            {
                return false;
            }
        }
        return true;
    }

    // Return false if the string does not start with "0x" or "0X"

    return false;
}

//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - MAIN CODE GOES HERE - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

int main(int arg_count, char **arg_values)
{

    if (arg_count != 2)
    {
        cout << "Error: Incorrect format. Usage: ./asm <filename>.asm" << endl;
        return 0;
    }

    // LIST OF ALL MNEMONIC GIVING IN OUR PROJECTS TABLE

    unordered_map<string, int> mnemonic;
    // ALL 20 mnemonics
    mnemonic["ldc"] = 0;
    mnemonic["adc"] = 1;
    mnemonic["ldl"] = 2;
    mnemonic["stl"] = 3;
    mnemonic["ldnl"] = 4;
    mnemonic["stnl"] = 5;
    mnemonic["add"] = 6;
    mnemonic["sub"] = 7;
    mnemonic["shl"] = 8;
    mnemonic["shr"] = 9;
    mnemonic["adj"] = 10;
    mnemonic["a2sp"] = 11;
    mnemonic["sp2a"] = 12;
    mnemonic["call"] = 13;
    mnemonic["return"] = 14;
    mnemonic["brz"] = 15;
    mnemonic["brlz"] = 16;
    mnemonic["br"] = 17;
    mnemonic["HALT"] = 18;
    mnemonic["data"] = 19;
    mnemonic["SET"] = 20;

    string base_name = "";
    int t = 0;
    // Extract base file name (remove extension)
    while (arg_values[1][t] != '.' && arg_values[1][t] != '\0') // CHECK TILL LAST CHAR
    {
        base_name += arg_values[1][t];
        t++;
    }

    fstream source_file;
    string file_name = base_name;
    string source_file_name = base_name + ".asm";

    source_file.open(source_file_name, ios::in);

    int line_count = 0;
    int count = 0;
    vector<string> cleaned_code; // Holds cleaned lines without comments and empty lines
    vector<string> error_log;    // Holds Error_signal messages
    vector<int> operand_count;
    vector<string> warning_log;            // Holds warning messages
    vector<Code_STRUCTURE> processed_code; // Holds structured representation of parsed code lines

    // NOW GO THROUGH THE ASM CODE AND STORE THE CODE IN PROPER FORMAT

    if (source_file.is_open())
    {
        string line; // Temporary variable to hold each line from the file

        // Read each line from the input file
        while (getline(source_file, line))
        {
            string processed_line = ""; // Stores the line without comments
            int i = 0;

            // Process each character in the line until a comment character ';' is found
            while (i < line.size())
            {
                char current_char = line[i];
                if (current_char == ';') // Stop at comment character ';'
                    break;

                processed_line += current_char; // Append character to processed_line if pointer's not a comment
                i++;                            // Move to the next character
            }

            cleaned_code.push_back(processed_line); // Add the processed line to the code vector
        }

        source_file.close(); // Close the file after reading
    }
    else
    {
        string Error_signal = "Empty File"; // Error message for an empty file or file not found
        error_log.push_back(Error_signal);
        return 0;
    }

    // NOW CREATE 2 NEW VARIABLES :-
    // 1] LITERAL TABLE -> to store all the literals encountered while we traverse the code .
    // 2] SYMBOL TABLE -> to store all the symbols encountered while we traverse the code .

    vector<pair<string, int>> literal_table; // literal table 1st is value and 2nd is address

    unordered_map<string, int> symbol_table; // symbol table

    // Here we make symbol table and literal table by traversing whole code

    for (string s : cleaned_code)
    {
        struct Code_STRUCTURE demo_code;
        loc = 0;
        demo_code.pc = PC;

        string temporary = Separate(s); // USE SEPARATE FXN ;
        if (temporary == "")
        {
            present_line_no++; // BLANK LINE MOVE FORWARD
            continue;
        }

        //  If the 1st string is a Label

        if (IS_Label(temporary))
        {
            demo_code.Label = temporary;                            // STORE LABEL PART OF DEMO CODE TO BE TEMPORARY
            if (symbol_table.find(temporary) == symbol_table.end()) // Here we add labels to symbol table
            {
                symbol_table[temporary] = PC;
            } // NEW ENTRY
            else if (symbol_table.find(temporary) != symbol_table.end() && symbol_table[temporary] != -1)
            {
                // ITS REPEATED LABEL AS ITS ALDREADY PRESENT IN SYMBOL TABLE
                string Error_signal = "ERROR:Label Repeated at line ";
                Error_signal += to_string(present_line_no);
                error_log.push_back(Error_signal);
            }
            else if (symbol_table.find(temporary) != symbol_table.end() && symbol_table[temporary] == -1)
                symbol_table[temporary] = PC; // Here adding conditions end
            temporary = "";                   // TEMPORARY IS CLEARED OF THE PREVIOUS VALUE
            temporary = Separate(s);          // here we check 2nd string

            // IF THERE IS NO 2ND STRING [ ONLY A LABEL THAT SIT THEN :- ]

            if (temporary.length() == 0)
            {
                string Warning_signal = "Warning: Unused Label at line ";
                Warning_signal += to_string(present_line_no);
                warning_log.PB(Warning_signal); // STORING WARNING SIGNAL IN WARNING LOG
                processed_code.PB(demo_code);   // STORING DEMO CODE IN PROCESSED CODE
                present_line_no++;
                continue;
            }

            // IF 2ND STRING EXISTS AND IS A MNEMONIC THEN

            else if (IS_Mnemonic(mnemonic, temporary))
            {
                demo_code.Mnemonic = temporary; // STORE MNEMONIC PART OF DEMO CODE TO BE TEMPORARY
                string Mnemonic = temporary;    // store mnemonic in string Mnemonic
                temporary = "";                 // TEMPORARY IS CLEARED OF THE PREVIOUS VALUE
                temporary = Separate(s);        // load 3rd string in temporary [OPERAND]
                string temporary_1 = "";
                temporary_1 = Separate(s); // load 4th string in temporary 1

                // IF EXTRA OPERAND EXISTS

                if (temporary_1.length() > 0)
                {
                    string Error_signal = "ERROR:Extra operand at line ";
                    Error_signal += to_string(present_line_no);
                    error_log.PB(Error_signal);
                    present_line_no++;
                    PC++;
                    continue;
                } // Here checking ends

                // CHECK FOR THE TYPE OF MNEMONIC WE HAVE ENCOUNTERED !

                // ZERO OPERAND TYPE MNEMONIC

                if (Zero_Operand(Mnemonic))
                {
                    if (temporary.length() > 0) // IF OPERAND IF GIVEN
                    {
                        string Error_signal = "ERROR:Extra Operand at line "; // GIVE OUT ERROR
                        Error_signal += to_string(present_line_no);
                        error_log.PB(Error_signal);
                        present_line_no++; // MOVE FORWARD
                        PC++;              // MOVE PC FORWARD

                        continue;
                    }
                }

                // ONE OPERAND TYPE MNEMONIC

                else if (One_Operand(Mnemonic))
                {
                    demo_code.Operand = temporary; // STORE OPERAND PART OF DEMO CODE TO BE TEMPORARY

                    // IF NO OPERAND IS GIVEN

                    if (temporary.length() == 0)
                    {
                        string Error_signal = "ERROR:Missing operand at line ";
                        Error_signal += to_string(present_line_no); // GIVE OUT ERROR
                        error_log.PB(Error_signal);
                    }

                    // IF THE OPERAND IS LABEL (FOR br , etc.....)

                    else if (IS_Label(temporary))
                    {
                        string Error_signal = "ERROR:Label declared after mnemonic";
                        Error_signal += to_string(present_line_no);
                        error_log.PB(Error_signal);
                    }

                    // new Label -> INSERT IT INTO THE SYMBOL TABLE WITH TEMP VALUE -1 ; to show that its not yet decleared

                    else if (symbol_table.find(temporary + ":") == symbol_table.end() && ((temporary[0] <= 'Z' && temporary[0] >= 'A') || (temporary[0] <= 'z' && temporary[0] >= 'a'))) // if Label is used after mnemonic then insert in map
                    {
                        symbol_table[temporary + ":"] = -1;

                    } // new Label found

                    else if (symbol_table.find(temporary + ":") != symbol_table.end() && ((temporary[0] <= 'Z' && temporary[0] >= 'A') || (temporary[0] <= 'z' && temporary[0] >= 'a')))
                    {
                        processed_code.PB(demo_code);
                        present_line_no++;
                        PC++; // Label already in table
                        continue;
                    }

                    // IF THE OPERAND IS A NEGATIVE OR POSITIVE DIGIT

                    else if (Is_Digits(temporary) || ((temporary[0] == '-' || temporary[0] == '+') && Is_Digits(temporary.substr(1, temporary.length())))) // literal table
                    {
                        literal_table.PB({temporary, literal_counter++});
                        // INSERT IT IN LITERAL TABLE
                    }

                    // IF THE OPERAND IS NONE OF THE ABOVE TYPE

                    else
                    {
                        string Error_signal = "ERROR:Wrong Syntax at line ";
                        Error_signal += to_string(present_line_no); // GIVE OUT AN ERROR MESSAGE
                        error_log.PB(Error_signal);
                    }
                }
            }

            // IF 2ND STRING IS NOT A MNEMONIC :- A SYNTAX ERROR

            else
            {
                string Error_signal = "ERROR:Wrong Syntax at line ";
                Error_signal += to_string(present_line_no); // GIVE OUT AN ERROR MESSAGE
                error_log.PB(Error_signal);
            }
        }

        // IF THE 1ST STRING IS MNEMONIC NOT LABEL THEN :-

        else if (IS_Mnemonic(mnemonic, temporary))
        {

            demo_code.Mnemonic = temporary; // STORE MNEMONIC PART OF DEMO CODE TO BE TEMPORARY
            string Mnemonic = temporary;    // store mnemonic in string Mnemonic
            temporary = "now_go_to_next_str";
            temporary = "";          // TEMPORARY IS CLEARED OF THE PREVIOUS VALUE
            temporary = Separate(s); // load 2rd string in temporary [OPERAND]
            string temporary_1 = "";
            temporary_1 = Separate(s); // load 3th string in temporary 1
            // IF EXTRA OPERAND EXISTS

            if (temporary_1.length() > 0)
            {
                string Error_signal = "ERROR:Extra operand at line ";
                Error_signal += to_string(present_line_no);
                error_log.PB(Error_signal);
                // --
                present_line_no++;
                PC++;
                continue;
            } // Here checking ends

            // CHECK FOR THE TYPE OF MNEMONIC WE HAVE ENCOUNTERED !

            // ZERO OPERAND TYPE MNEMONIC

            if (Zero_Operand(Mnemonic))
            {
                if (temporary.length() > 0) // IF OPERAND IF GIVEN
                {
                    string Error_signal = "ERROR:Extra Operand at line "; // GIVE OUT ERROR
                    Error_signal += to_string(present_line_no);
                    error_log.PB(Error_signal);
                    present_line_no++; // MOVE FORWARD
                    PC++;              // MOVE PC FORWARD
                    continue;
                }
            }

            // ONE OPERAND TYPE MNEMONIC

            else if (One_Operand(Mnemonic))
            {
                demo_code.Operand = temporary; // STORE OPERAND PART OF DEMO CODE TO BE TEMPORARY
                string temporary_2 = "";
                // IF NO OPERAND IS GIVEN

                if (temporary.length() == 0)
                {
                    string Error_signal = "ERROR:Missing operand at line ";
                    Error_signal += to_string(present_line_no); // GIVE OUT ERROR
                    error_log.PB(Error_signal);
                }

                // IF THE OPERAND IS LABEL (FOR br , etc.....)

                else if (IS_Label(temporary))
                {
                    string Error_signal = "ERROR:Label declared after mnemonic";
                    Error_signal += to_string(present_line_no);
                    error_log.PB(Error_signal);
                }

                // new Label -> INSERT IT INTO THE SYMBOL TABLE WITH TEMP VALUE -1 ; to show that its not yet decleared

                else if (symbol_table.find(temporary + ":") == symbol_table.end() && ((temporary[0] <= 'Z' && temporary[0] >= 'A') || (temporary[0] <= 'z' && temporary[0] >= 'a'))) // if Label is used after mnemonic then insert in map
                {
                    symbol_table[temporary + ":"] = -1;
                } // new Label found

                else if (symbol_table.find(temporary + ":") != symbol_table.end() && ((temporary[0] <= 'Z' && temporary[0] >= 'A') || (temporary[0] <= 'z' && temporary[0] >= 'a')))
                {
                    processed_code.PB(demo_code);
                    present_line_no++;
                    PC++; // Label already in table
                    continue;
                }

                // IF THE OPERAND IS A NEGATIVE OR POSITIVE DIGIT

                else if (Is_Digits(temporary) || ((temporary[0] == '-' || temporary[0] == '+') && Is_Digits(temporary.substr(1, temporary.length())))) // literal table
                {
                    literal_table.PB({temporary, literal_counter++});
                    // INSERT IT IN LITERAL TABLE
                }

                // IF THE OPERAND IS NONE OF THE ABOVE TYPE

                else
                {
                    string Error_signal = "ERROR:Wrong Syntax at line ";
                    Error_signal += to_string(present_line_no); // GIVE OUT AN ERROR MESSAGE
                    error_log.PB(Error_signal);
                }
            }
        }

        // IF 1ST TERM IS NEITHER LABEL NOR MNEMONIC  ; THEN IT MUST BE AN ERROR IF ITS NON EMPTY

        else
        {
            if (temporary[temporary.length() - 1] == ':') // ITS A LABEL
            {
                string Error_signal = "ERROR:Wrong Format of Label at line "; // GIVE OUT AN ERROR MESSAGE
                Error_signal += to_string(present_line_no);
                error_log.PB(Error_signal);
            }
            else
            {
                string Error_signal = "ERROR:Wrong Syntax at line "; // ERROR IN SYNTAX
                Error_signal += to_string(present_line_no);          // GIVE OUT AN ERROR MESSAGE
                error_log.PB(Error_signal);
            }
        }
        processed_code.PB(demo_code);
        present_line_no++;
        PC++;
    }

    // NOW CHECK FOR ALL UNDECLEARED TERMS IN SYMBOL TABLE; THE ONCE WITH VALUE "-1"

    for (auto pointer : symbol_table)
        if (pointer.second == -1)
        {
            string Error_signal = "ERROR:Undeclared Label " + pointer.first.substr(0, pointer.first.length() - 1); // GIVE OUT AN ERROR SIGNAL AS UNDECLEARED LABELS
            error_log.PB(Error_signal);
        }

    // CREATE NEW VARIABLE FOR DATA

    unordered_map<string, int> data;

    // TRAVERSE THROUGH PROCESSED CODE TO SEARCH FOR DATA TERM OR SET TERM  ;

    for (auto pointer : processed_code)
        if ((pointer.Mnemonic == "data" || pointer.Mnemonic == "SET") && pointer.Label != "")
            if (pointer.Mnemonic == "data")
                data[pointer.Label] = 1; // ALLOCATE VALUE "1" TO DATA
            else
                data[pointer.Label] = 2; // ALLOCATE VALUE "2" TO SET

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - PASS 1 COMPLETED  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - PASS 2 BEGINS - - - - - - - - - - - - - - - - - -  - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - - - - CREATING A LOG FILE - - - - - - - - -- - - - - - - - - - - - - - - - - - - - -  - - - - - - - - - - - - - - -

    string LOG_FILE_NAME = base_name + ".log"; // new log file creation
    ofstream LOG_FILE;
    LOG_FILE.open(LOG_FILE_NAME); // opening file

    int Error_number = 1; // initialize error number to 1

    // WRITE ALL THE ERRORS IN THE LOG FILE ; BY ITERATING IN THE ERROR LOG

    for (auto pointer : error_log)
    {
        LOG_FILE << Error_number << ". " << pointer << endl; // print line by linee
        Error_number++;                                      // increment error number
    }

    // WRITE ALL THE WARNINGS IN THE LOG FILE ; BY ITERATING IN THE ERROR LOG

    for (auto pointer : warning_log)
    {
        LOG_FILE << Error_number << ". " << pointer << endl; // print line by linee
        Error_number++;                                      // increment error number
    }

    LOG_FILE.close(); // close log filee

    // IF ERROR EXIST IN THE CODE THEN

    if (error_log.size() > 0)
    {
        string LIST_FILE_NAME = base_name + ".lst"; // CREATE A LIST FILE
        ofstream LIST_FILE;
        LIST_FILE.open(LIST_FILE_NAME);
        // RETURN 0 ; STOP AS NO NEED TO GIVE LIST FILE AND O FILE AS ERROR HAS OCCURED IN CODE !
        return 0;
    }

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - - - - - LOG FILE COMPLETED  - - - - - - - - - - - - - - - - - -  - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - - - - - CREATING LIST FILE  - - - - - - - - - - - - - - - - - -  - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    string LIST_FILE_NAME = base_name + ".lst"; // new list file creation
    ofstream LIST_FILE;
    LIST_FILE.open(LIST_FILE_NAME); // opening file

    // new variable to store the 8 bit machine code !

    vector<string> MACHINE_CODE;

    // Iterate through each entry in the PROCESSED_code vector
    for (auto entry : processed_code)
    {
        stringstream addr_stream;              // Create stringstream for hexadecimal address
        addr_stream << hex << entry.pc;        // Convert the program counter to hex
        string address_hex(addr_stream.str()); // Store the hex address as a string
        int addr_len = address_hex.length();   // Get the length of the hex address

        // Add padding to align address to 8 characters
        int pad = 0;
        while (pad < 8 - addr_len)
        {
            LIST_FILE << "0"; // Add leading zeroes
            ++pad;
        }
        LIST_FILE << address_hex << " "; // Write the address to the listing file

        if (!entry.Mnemonic.empty())
        {
            stringstream mne_stream;                       // Stringstream to convert mnemonic to hex
            mne_stream << hex << mnemonic[entry.Mnemonic]; // Convert mnemonic to hex
            string mne_hex(mne_stream.str());              // Store hex representation of mnemonic

            // Handle cases based on operand type for the mnemonic
            if (Zero_Operand(entry.Mnemonic))
            {
                // Pad and write zero-operand mnemonic
                pad = 0;
                while (pad < 8 - mne_hex.length())
                {
                    LIST_FILE << "0"; // Add leading zeroes
                    ++pad;
                }
                LIST_FILE << mne_hex << " "; // Write mnemonic to file
            }
            else
            {
                // Handle one-type operand case
                if (Is_Digits(entry.Operand) || Is_Digits(entry.Operand.substr(1)))
                {
                    // If the operand is a number
                    if (Is_Decimal(entry.Operand))
                    {
                        int dec_value = stoi(entry.Operand); // Convert operand to decimal
                        stringstream dec_stream;
                        dec_stream << hex << dec_value; // Convert decimal to hex
                        string dec_hex(dec_stream.str());

                        if (entry.Mnemonic == "data" || entry.Mnemonic == "SET")
                        {
                            // Pad and write if mnemonic is data or SET
                            pad = 0;
                            while (pad < 8 - dec_hex.length())
                            {
                                LIST_FILE << "0"; // Add leading zeroes
                                ++pad;
                            }
                            LIST_FILE << dec_hex << " "; // Write hex value
                        }
                        else
                        {
                            if (dec_value < 0)
                                dec_hex = dec_hex.substr(2); // Remove sign if negative
                            pad = 0;
                            while (pad < 6 - dec_hex.length())
                            {
                                LIST_FILE << "0"; // Add leading zeroes
                                ++pad;
                            }
                            LIST_FILE << dec_hex; // Write the decimal in hex form
                            pad = 0;
                            while (pad < 2 - mne_hex.length())
                            {
                                LIST_FILE << "0"; // Pad mnemonic to align
                                ++pad;
                            }
                            LIST_FILE << mne_hex << " "; // Write mnemonic
                        }
                    }
                    else if (Is_Octal(entry.Operand))
                    {
                        int oct_value; // Variable to hold octal value
                        stringstream oct_stream(entry.Operand);
                        oct_stream >> oct >> oct_value; // Convert operand to octal

                        stringstream hex_stream;
                        hex_stream << hex << oct_value; // Convert octal to hex
                        string oct_hex(hex_stream.str());

                        if (entry.Mnemonic == "data" || entry.Mnemonic == "SET")
                        {
                            pad = 0;
                            while (pad < 8 - oct_hex.length())
                            {
                                LIST_FILE << "0"; // Pad to 8 characters
                                ++pad;
                            }
                            LIST_FILE << oct_hex << " "; // Write operand as hex
                        }
                        else
                        {
                            pad = 0;
                            while (pad < 6 - oct_hex.length())
                            {
                                LIST_FILE << "0"; // Pad operand
                                ++pad;
                            }
                            LIST_FILE << oct_hex; // Write hex value
                            pad = 0;
                            while (pad < 2 - mne_hex.length())
                            {
                                LIST_FILE << "0"; // Pad mnemonic
                                ++pad;
                            }
                            LIST_FILE << mne_hex << " "; // Write mnemonic
                        }
                    }
                    else
                    {
                        string hex_value = entry.Operand.substr(2); // Extract hex from operand

                        if (entry.Mnemonic == "data" || entry.Mnemonic == "SET")
                        {
                            pad = 0;
                            while (pad < 8 - hex_value.length())
                            {
                                LIST_FILE << "0"; // Pad to 8 characters
                                ++pad;
                            }
                            LIST_FILE << hex_value << " "; // Write hex value
                        }
                        else
                        {
                            pad = 0;
                            while (pad < 6 - hex_value.length())
                            {
                                LIST_FILE << "0"; // Pad hex value
                                ++pad;
                            }
                            LIST_FILE << hex_value;
                            pad = 0;
                            while (pad < 2 - mne_hex.length())
                            {
                                LIST_FILE << "0"; // Pad mnemonic
                                ++pad;
                            }
                            LIST_FILE << mne_hex << " "; // Write mnemonic
                        }
                    }
                }
                else if (data.find(entry.Operand + ":") != data.end())
                {
                    // If operand is a variable, get the value from symbol_table
                    stringstream var_stream;
                    var_stream << hex << symbol_table[entry.Operand + ":"];
                    string var_hex(var_stream.str());

                    pad = 0;
                    while (pad < 6 - var_hex.length())
                    {
                        LIST_FILE << "0"; // Pad variable address
                        ++pad;
                    }
                    LIST_FILE << var_hex;
                    pad = 0;
                    while (pad < 2 - mne_hex.length())
                    {
                        LIST_FILE << "0"; // Pad mnemonic
                        ++pad;
                    }
                    LIST_FILE << mne_hex << " "; // Write mnemonic
                }
                else
                {
                    // Label handling for relative address calculation
                    if (Mnemonic_Type_Value(entry.Mnemonic))
                    {
                        stringstream label_stream;
                        label_stream << hex << symbol_table[entry.Operand + ":"];
                        string label_hex(label_stream.str());

                        pad = 0;
                        while (pad < 6 - label_hex.length())
                        {
                            LIST_FILE << "0"; // Pad Label address
                            ++pad;
                        }
                        LIST_FILE << label_hex;
                        pad = 0;
                        while (pad < 2 - mne_hex.length())
                        {
                            LIST_FILE << "0"; // Pad mnemonic
                            ++pad;
                        }
                        LIST_FILE << mne_hex << " "; // Write mnemonic
                    }
                    else
                    {
                        stringstream offset_stream;
                        offset_stream << hex << (symbol_table[entry.Operand + ":"] - entry.pc - 1);
                        string offset_hex(offset_stream.str());

                        if (symbol_table[entry.Operand + ":"] - entry.pc - 1 < 0)
                            offset_hex = offset_hex.substr(2); // Remove negative sign if present

                        pad = 0;
                        while (pad < 6 - offset_hex.length())
                        {
                            LIST_FILE << "0"; // Pad offset
                            ++pad;
                        }
                        LIST_FILE << offset_hex;
                        pad = 0;
                        while (pad < 2 - mne_hex.length())
                        {
                            LIST_FILE << "0"; // Pad mnemonic
                            ++pad;
                        }
                        LIST_FILE << mne_hex << " "; // Write mnemonic
                    }
                }
            }
        }
        else
        {
            // Add spaces if there's no mnemonic
            pad = 0;
            while (pad < 8)
            {
                LIST_FILE << " ";
                ++pad;
            }
        }

        // Write Label, mnemonic, and operand fields if they exist
        if (!entry.Label.empty())
            LIST_FILE << entry.Label << " ";
        if (!entry.Mnemonic.empty())
            LIST_FILE << entry.Mnemonic << " ";
        if (!entry.Operand.empty())
            LIST_FILE << entry.Operand << " ";
        LIST_FILE << endl; // End line for current entry
    }

    LIST_FILE.close(); // Close listing file

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - - - - - LIST FILE COMPLETED  - - - - - - - - - - - - - - - - - -  - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - - - - - CREATING MACHINE FILE  - - - - - - - - - - - - - - - - - -  - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    fstream MACHINE_FILE;
    MACHINE_FILE.open(LIST_FILE_NAME, ios::in); // Open in read mode
    if (MACHINE_FILE.is_open())
    {
        string line_content; // Temporary variable for line content
        while (getline(MACHINE_FILE, line_content))
        {
            loc = 0; // Reset location for parsing each new line from the file

            string instruction = Separate(line_content); // Extract a potential instruction from the line
            instruction = "";                            // Reset instruction variable for potential reuse
            instruction = Separate(line_content);        // Parse line content again to retrieve the next segment

            // Check if the instruction is not present in the symbol table
            // If not, add the instruction to the machine code vector
            if (symbol_table.find(instruction) == symbol_table.end())
            {
                MACHINE_CODE.push_back(instruction); // Append the instruction to MACHINE_CODE
            }
        }
    }
    MACHINE_FILE.close(); // Close the listing file

    // Create a binary file to store machine code
    string binary_file_name = base_name + ".o";                  // Name for the output file
    FILE *binary_file_pointer;                                   // File pointer for binary output file
    binary_file_pointer = fopen(binary_file_name.c_str(), "wb"); // Open file in write-binary mode
    int machine_code_size = MACHINE_CODE.size();                 // Size of the machine code vector
    int instruction_array[machine_code_size];                    // Array to hold machine code in decimal format

    int index = 0; // Initialize index
    while (index < machine_code_size)
    {                                                                           // Loop through each instruction
        unsigned int instruction_decimal_value;                                 // Decimal representation of instruction
        stringstream ss_instruction_value;                                      // Stringstream for hexadecimal conversion
        ss_instruction_value << hex << MACHINE_CODE[index];                     // Convert instruction to hex
        ss_instruction_value >> instruction_decimal_value;                      // Extract as decimal
        instruction_array[index] = static_cast<int>(instruction_decimal_value); // Store in array
        index++;                                                                // Move to the next instruction
    }

    // Write the decimal array to the binary file
    fwrite(instruction_array, sizeof(int), machine_code_size, binary_file_pointer);
    fclose(binary_file_pointer); // Close binary file

    return 0; // Indicate successful execution
}

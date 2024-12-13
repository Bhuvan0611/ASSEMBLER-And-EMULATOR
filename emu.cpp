// ------------------------------------------------------------------
// Declaration of Authorship :
// Name : VENKATA BHUVAN KOSURU
// Roll No: 2301AI33
// --------------------------------------------------------------------
#include <bits/stdc++.h>
using namespace std;

#define MAX_MEMORY 16777216 // Memory size for 24-bit addressing
// 2 ^24

// Global state variables
vector<int> programMemory;
int memory[MAX_MEMORY];
int registers[4] = {0}; // {A, B, PC, SP}
int instructionCount = 0;
pair<int, int> memoryLog; // Stores memory log information

// Function prototypes (Declared here)
void setValue(int value);
void addConstant(int value);
void loadStack(int offset);
void storeStack(int offset);
void loadIndirect(int offset);
void storeIndirect(int offset);
void addRegisters();
void subtractRegisters();
void shiftLeft();
void shiftRight();
void adjustStackPointer(int value);
void moveToStackPointer();
void moveFromStackPointer();
void functionCall(int offset);
void returnFromFunction();
void branchIfZero(int offset);
void branchIfNegative(int offset);
void unconditionalBranch(int offset);
void haltExecution();
void logMemoryRead();
void logMemoryWrite();
void displayMemoryBeforeExecution();
void displayMemoryAfterExecution();
void resetRegisters();
void displayISA();
bool executeInstruction(int instruction, int flag);
void runProgram(int flag);
void loadProgram(string filename);
void executeCommand(string command);
string toHex(int num);
void initializeOpCodeTable();
void handleError();

// Instruction Set Architecture
map<string, pair<string, int>> opTab; // {mnemonic, {opcode, operand type}}

// Main program logic
int main(int argc, char *argv[]) // COMMAND PROMT INPUT => EXPECTED ./emu -isa filename.o ; argc=3!
{
    if (argc <= 2)
    {
        cout << "Invalid input format!" << endl;
        cout << "Expected syntax: ./emu [command] filename.o" << endl;
        cout << "Available commands: " << endl;
        cout << "-trace  Show the trace of execution" << endl;
        cout << "-read   Display memory read operations" << endl;
        cout << "-write  Display memory write operations" << endl; // show all the tasks our emulator could perform !
        cout << "-before Show memory state before execution" << endl;
        cout << "-after  Show memory state after execution" << endl;
        cout << "-wipe   Reset registers" << endl;
        cout << "-isa    Display ISA (Instruction Set Architecture)" << endl;
        return 0;
    }

    string filename = argv[2];
    initializeOpCodeTable();
    loadProgram(filename);

    string command = argv[1];
    executeCommand(command);

    return 0;
}

// Function Definitions

void setValue(int val)
{
    registers[0] = val; // A register
}

void addConstant(int val)
{
    registers[0] += val; // Add value to A register
}

void loadStack(int offset)
{
    registers[1] = registers[0];                  // Store A in B
    registers[0] = memory[registers[3] + offset]; // Load from memory at (SP + offset)
    memoryLog = {registers[3] + offset, 0};
}

void storeStack(int offset)
{
    memoryLog = {registers[3] + offset, memory[registers[3] + offset]}; // Log memory state
    memory[registers[3] + offset] = registers[0];                       // Store A in memory at (SP + offset)
    registers[0] = registers[1];                                        // Restore A from B
}

void loadIndirect(int offset)
{
    registers[0] = memory[registers[0] + offset]; // Indirect memory access
    memoryLog = {registers[3] + offset, 0};
}

void storeIndirect(int offset)
{
    memoryLog = {registers[3] + offset, memory[registers[3] + offset]}; // Log memory state
    memory[registers[0] + offset] = registers[1];                       // Store B at (A + offset)
}

void addRegisters()
{
    registers[0] += registers[1]; // A += B
}

void subtractRegisters()
{
    registers[0] = registers[1] - registers[0]; // A = B - A
}

void shiftLeft()
{
    registers[0] = registers[1] << registers[0]; // A = B << A
}

void shiftRight()
{
    registers[0] = registers[1] >> registers[0]; // A = B >> A
}

void adjustStackPointer(int value)
{
    registers[3] += value; // Adjust stack pointer
}

void moveToStackPointer()
{
    registers[3] = registers[0]; // Move A to SP
    registers[0] = registers[1]; // Move B to A
}

void moveFromStackPointer()
{
    registers[1] = registers[0]; // Move A to B
    registers[0] = registers[3]; // Move SP to A
}

void functionCall(int offset)
{
    registers[1] = registers[0]; // Store A in B
    registers[0] = registers[2]; // Store PC in A
    registers[2] += offset;      // Increment PC by offset
}

void returnFromFunction()
{
    registers[2] = registers[0]; // Restore PC from A
    registers[0] = registers[1]; // Restore A from B
}

void branchIfZero(int offset)
{
    if (registers[0] == 0)
    {
        registers[2] += offset; // Increment PC by offset
    }
}

void branchIfNegative(int offset)
{
    if (registers[0] < 0)
    {
        registers[2] += offset; // Increment PC by offset
    }
}

void unconditionalBranch(int offset)
{
    registers[2] += offset; // Increment PC by offset
}

void haltExecution()
{
    // Halt the program
    cout << "Program halted!" << endl;
    exit(0);
}

void logMemoryRead()
{
    cout << "Reading memory[" << toHex(memoryLog.first) << "] found " << toHex(registers[0]) << endl;
}

void logMemoryWrite()
{
    cout << "Writing memory[" << toHex(memoryLog.first) << "] was " << toHex(memoryLog.second) << " now " << toHex(memory[memoryLog.first]) << endl;
}

void displayMemoryBeforeExecution()
{
    cout << "Memory dump before execution:" << endl;
    for (int i = 0; i < programMemory.size(); i += 4)
    {
        cout << toHex(i) << " ";
        for (int j = i; j < min(int(programMemory.size()), i + 4); ++j)
        {
            cout << toHex(programMemory[j]) << " ";
        }
        cout << endl;
    }
}

void displayMemoryAfterExecution()
{
    cout << "Memory dump after execution:" << endl;
    for (int i = 0; i < programMemory.size(); i += 4)
    {
        cout << toHex(i) << " ";
        for (int j = i; j < min(int(programMemory.size()), i + 4); ++j)
        {
            cout << toHex(memory[j]) << " ";
        }
        cout << endl;
    }
}

void resetRegisters()
{
    fill(begin(registers), end(registers), 0); // Reset registers
}

void displayISA()
{
    cout << "Opcode Mnemonic Operand" << endl;
    cout << "00    ldc    value" << endl;
    cout << "01    adc    value" << endl;
    cout << "02    ldl    offset" << endl;
    cout << "03    stl    offset" << endl;
    cout << "04    ldnl   offset" << endl;
    cout << "05    stnl   offset" << endl;
    cout << "06    add" << endl;
    cout << "07    sub" << endl;
    cout << "08    shl" << endl;
    cout << "09    shr" << endl;
    cout << "0A    adj    value" << endl;
    cout << "0B    a2sp" << endl;
    cout << "0C    sp2a" << endl;
    cout << "0D    call   offset" << endl;
    cout << "0E    return" << endl;
    cout << "0F    brz    offset" << endl;
    cout << "10    brlz   offset" << endl;
    cout << "11    br     offset" << endl;
    cout << "12    HALT" << endl;
}

bool executeInstruction(int instruction, int flag)
{
    int opcode = instruction & 0xFF;
    int value = (instruction - opcode) >> 8;

    ++instructionCount;

    // Log for trace
    if (flag == 0)
    {
        cout << "PC = " << toHex(registers[2]) << " ";
        cout << "Instruction: " << toHex(instruction) << " ";
        cout << "Executing: ";
    }

    // Call function based on opcode
    switch (opcode)
    {
    case 0:
        setValue(value);
        break;
    case 1:
        addConstant(value);
        break;
    case 2:
        loadStack(value);
        break;
    case 3:
        storeStack(value);
        break;
    case 4:
        loadIndirect(value);
        break;
    case 5:
        storeIndirect(value);
        break;
    case 6:
        addRegisters();
        break;
    case 7:
        subtractRegisters();
        break;
    case 8:
        shiftLeft();
        break;
    case 9:
        shiftRight();
        break;
    case 10:
        adjustStackPointer(value);
        break;
    case 11:
        moveToStackPointer();
        break;
    case 12:
        moveFromStackPointer();
        break;
    case 13:
        functionCall(value);
        break;
    case 14:
        returnFromFunction();
        break;
    case 15:
        branchIfZero(value);
        break;
    case 16:
        branchIfNegative(value);
        break;
    case 17:
        unconditionalBranch(value);
        break;
    case 18:
        haltExecution();
        break;
    }

    if (flag == 0)
    {
        cout << endl; // End of trace for this instruction
    }
    else if (flag == 1 && (opcode == 2 || opcode == 4))
    {
        logMemoryRead();
    }
    else if (flag == 2 && (opcode == 3 || opcode == 5))
    {
        logMemoryWrite();
    }

    return false;
}

void runProgram(int flag)
{
    while (registers[2] < programMemory.size())
    {
        int currentInstruction = programMemory[registers[2]++];
        if (executeInstruction(currentInstruction, flag))
        {
            break;
        }
    }
}

void loadProgram(string filename)
{
    ifstream file(filename, ios::in | ios::binary);
    unsigned int currentWord;
    int counter = 0;
    while (file.read((char *)&currentWord, sizeof(int)))
    {
        programMemory.push_back(currentWord);
        memory[counter++] = currentWord;
    }
}

void executeCommand(string command)
{
    if (command == "-trace")
    {
        runProgram(0);
    }
    else if (command == "-read")
    {
        runProgram(1);
    }
    else if (command == "-write")
    {
        runProgram(2);
    }
    else if (command == "-before")
    {
        displayMemoryBeforeExecution();
    }
    else if (command == "-after")
    {
        displayMemoryAfterExecution();
    }
    else if (command == "-wipe")
    {
        resetRegisters();
    }
    else if (command == "-isa")
    {
        displayISA();
    }
    else
    {
        cout << "Invalid command" << endl;
    }
}

string toHex(int num)
{
    stringstream ss;
    ss << hex << uppercase << num;
    return ss.str();
}

void initializeOpCodeTable()
{
    opTab = {
        {"ldc", {"00", 1}},
        {"adc", {"01", 1}},
        {"ldl", {"02", 2}},
        {"stl", {"03", 2}},
        {"ldnl", {"04", 2}},
        {"stnl", {"05", 2}},
        {"add", {"06", 0}},
        {"sub", {"07", 0}},
        {"shl", {"08", 0}},
        {"shr", {"09", 0}},
        {"adj", {"0A", 1}},
        {"a2sp", {"0B", 0}},
        {"sp2a", {"0C", 0}},
        {"call", {"0D", 2}},
        {"return", {"0E", 0}},
        {"brz", {"0F", 2}},
        {"brlz", {"10", 2}},
        {"br", {"11", 2}},
        {"HALT", {"12", 0}}};
}

void handleError()
{
    cout << "An error occurred!" << endl;
    exit(1);
}

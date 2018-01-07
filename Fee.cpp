//PROJECT SCHOOL FEE ENQUIRY

#include <iostream>
#include <windows.h> // for using sleep()
#include <fstream>
#include <sstream>
#include <cstring>
#include <cstdlib> // for using printf(), scanf()
#include <cstdio>
#include <cctype>  // for using character functions
#include <conio.h> // for console functions like position(), getch()
#include <ctime>
#include <dos.h>
#include <iomanip>
#include <string>
#include <algorithm> 
#include <locale>
#include <functional>

// trim from start
static inline std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
            std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
            std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}


using namespace std;

void startAnimation();
void homeAnimation(bool);
void home();
void position(int, int);
bool studentFind(int, string);
void registerStudent();

// Global Variables
char ch, choice;
int i, j, valid;
bool firstRun = false;
string clear = "                                       ";
string clear_s = "      ";
COORD coord = {0, 0}; // Defines the coordinates of a character cell in a console screen buffer

// To draw lines, boxes
class DRAW
{
  public:
    void LINE_HOR(int, int, int, char);
    void LINE_VER(int, int, int, char);
    void BOX(int, int, int, int, char);
};

// Draws a horizontal line between 2 points
void DRAW::LINE_HOR(int column1, int column2, int row, char c)
{
    for (column1; column1 <= column2; column1++)
    {
        position(column1, row);
        cout << c;
    }
}

// Draws a vertical line between 2 points
void DRAW::LINE_VER(int row1, int row2, int column, char c)
{
    for (row1; row1 <= row2; row1++)
    {
        position(column, row1);
        cout << c;
    }
}

// Draws a box between 2 diagonally opposite points
void DRAW::BOX(int column1, int row1, int column2, int row2, char c)
{
    ch = 218;
    char c1, c2, c3, c4;
    char l1 = 196, l2 = 179;
    if (c == ch)
    {
        c1 = 218;
        c2 = 191;
        c3 = 192;
        c4 = 217;
        l1 = 196;
        l2 = 179;
    }
    else
    {
        c1 = c;
        c2 = c;
        c3 = c;
        c4 = c;
        l1 = c;
        l2 = c;
    }
    position(column1, row1);
    cout << c1;
    position(column2, row1);
    cout << c2;
    position(column1, row2);
    cout << c3;
    position(column2, row2);
    cout << c4;
    column1++;
    column2--;
    LINE_HOR(column1, column2, row1, l1);
    LINE_HOR(column1, column2, row2, l1);
    column1--;
    column2++;
    row1++;
    row2--;
    LINE_VER(row1, row2, column1, l2);
    LINE_VER(row1, row2, column2, l2);
}

// This class contains all the essential functions and variables for fee management
class FEE
{
  private:
    int Class;
    float tuition, library, lab, computer, activity;
    void DISPLAY(int);
    void INSERT_FEES(int, float, float, float, float, float);

  public:
    void ADD(void);
    void MODIFY(void);
    void SLIP(void);
    bool LIST(void);
    void HELP(void);
} fee;

// Function to add default values of fee structure
void FEE::ADD(void)
{

    fstream file;
    file.open("FEE.TXT", ios::out | ios::trunc);
    file.close();

    INSERT_FEES(1, 250, 50, 0, 40, 40);
    INSERT_FEES(2, 250, 50, 0, 40, 40);
    INSERT_FEES(3, 250, 50, 0, 40, 40);
    INSERT_FEES(4, 250, 50, 0, 40, 40);
    INSERT_FEES(5, 250, 50, 0, 40, 40);
    INSERT_FEES(6, 300, 50, 20, 40, 50);
    INSERT_FEES(7, 300, 50, 20, 40, 50);
    INSERT_FEES(8, 300, 50, 20, 40, 50);
    INSERT_FEES(9, 350, 50, 20, 60, 50);
    INSERT_FEES(10, 350, 50, 30, 60, 50);
    INSERT_FEES(11, 450, 50, 60, 60, 50);
    INSERT_FEES(12, 450, 50, 60, 60, 50);
}

// Function to insert the fee structure into the file
void FEE::INSERT_FEES(int tclass, float ttuition, float tlibrary,
                      float tlab, float tcomputer, float tactivity)
{
    ofstream file;

    file.open("FEE.TXT", ios::app);
    if (file.fail())
    {
        exit(0);
    }

    Class = tclass;
    tuition = ttuition;
    library = tlibrary;
    lab = tlab;
    computer = tcomputer;
    activity = tactivity;

    file.write((char *)this, sizeof(FEE));

    file.close();
}

// Function to list all the fee structures of all classes
bool FEE::LIST()
{
    system("cls");

    DRAW d;
    d.BOX(36, 2, 76, 24, 218);

    position(50, 3);
    cout << "ALL CLASSES";

    d.LINE_HOR(37, 75, 4, 196);

    position(43, 5);
    cout << " CLASS           TOTAL FEES";

    d.LINE_HOR(37, 75, 6, 196);
    d.LINE_HOR(37, 75, 22, 196);

    float total = 0;
    int row = 8;

    fstream file;
    file.open("FEE.TXT", ios::in);

    while (file.read((char *)this, sizeof(FEE)))
    {
        total = tuition + library + lab + computer + activity;
        position(46, row);
        cout << Class;
        position(63, row);
        cout << total;
        row++;
    }

    file.close();

    position(41, 26);
    cout << "Press <Enter> to return HOME..";

    position(38, 23);
    cout << "Enter class to view Fee Structure : ";

    char input[3];
    int tclass, cInput;

    do
    {
        valid = 1;
        position(74, 23);
        gets(input);
        cInput = atoi(input);
        tclass = cInput;

        if (tclass < 1 || tclass > 12)
        {
            valid = 0;
        }

        if (strlen(input) == 0)
        {
            return false;
        }

        if (!valid)
        {
            position(37, 25);
            cout << "Wrong Value Entered, Please Enter Again";
            position(74, 23);
            cout << clear;
            d.BOX(36, 2, 76, 24, 218);
        }

    } while (!valid);

    if (strlen(input) != 0)
    {
        system("cls");

        DISPLAY(tclass);

        position(42, 18);
        cout << "Press <Enter> to go back..";
        getch();

        return true;
    }
    return false;
}

// Function to display fee structure for a given class
void FEE::DISPLAY(int tclass)
{
    DRAW d;

    fstream file;
    file.open("FEE.TXT", ios::in);

    float total = 0;

    while (file.read((char *)this, sizeof(FEE)))
    {

        if (Class == tclass)
        {

            position(50, 2);
            cout << "Class : " << Class;

            d.LINE_HOR(43, 65, 3, 196);

            position(43, 4);
            cout << "Tuition fees       " << tuition;
            total = total + tuition;

            position(43, 5);
            cout << "Library fees       " << library;
            total = total + library;

            position(43, 6);
            cout << "Lab fees           " << lab;
            total = total + lab;

            position(43, 7);
            cout << "Computer fees      " << computer;
            total = total + computer;

            position(43, 8);
            cout << "Activity fees      " << activity;
            total = total + activity;

            d.LINE_HOR(43, 65, 9, 196);

            char tt[15];
            sprintf(tt, "%f", total);

            position(43, 10);
            cout << "Total              " << total;
        }
    }
    file.close();
}

// Function to modify fee structure of a given class
void FEE::MODIFY(void)
{

    system("cls");

    DRAW d;

    char input[5];
    int tclass = 0;
    float cInput = 0;

    position(42, 15);
    cout << "Press any key to return HOME..";

    do
    {
        valid = 1;
        position(49, 3);
        cout << "Enter Class : ";
        gets(input);
        cInput = atoi(input);
        tclass = cInput;

        if (strlen(input) == 0)
        {
            return;
        }

        if (tclass < 1 || tclass > 12)
        {
            valid = 0;
        }

        if (!valid)
        {
            position(42, 15);
            cout << "Wrong Value Entered, Please Enter Again";
            position(49, 3);
            cout << clear;
        }

    } while (!valid);

    system("cls");

    d.BOX(25, 1, 84, 24, 218);

    DISPLAY(tclass);
    fee.Class = tclass;

    do
    {
        position(31, 13);
        cout << "Do you want to modify the fee structure (y/n) : ";
        ch = getch();
        cout << ch;
        getch();
        ch = toupper(ch);
    } while (ch != 'N' && ch != 'Y');

    if (ch == 'N')
        return;

    float ttuition = 0.0, tlibrary = 0.0, tlab = 0.0, tcomputer = 0.0, tactivity = 0.0;

    position(40, 16);
    cout << "Revised Tuition Fees :           ";

    int modified = 5;

    do
    {
        valid = 1;

        position(66, 16);
        gets(input);
        cInput = atof(input);
        ttuition = cInput;

        if (strlen(input) == 0)
            valid = 0;

        if (ttuition > 1000)
        {
            valid = 0;
        }

        if (!valid)
        {
            position(36, 23);
            cout << "Wrong Value Entered, Please Enter Again";
            position(66, 16);
            cout << clear_s;
        }
    } while (!valid);

    position(36, 23);
    cout << clear;

    modified--;
    fee.tuition = ttuition;

    position(40, 17);
    cout << "Revised Library Fees :                  ";

    do
    {
        valid = 1;

        position(66, 17);
        gets(input);
        cInput = atof(input);
        tlibrary = cInput;

        if (strlen(input) == 0)
            valid = 0;

        if (tlibrary > 1000)
        {
            valid = 0;
        }

        if (!valid)
        {
            position(36, 23);
            cout << "Wrong Value Entered, Please Enter Again";
            position(66, 17);
            cout << clear_s;
        }
    } while (!valid);

    position(36, 23);
    cout << clear;
    modified--;
    fee.library = tlibrary;

    position(40, 18);
    cout << "Revised Lab Fees :             ";

    do
    {
        valid = 1;

        position(66, 18);
        gets(input);
        cInput = atof(input);
        tlab = cInput;

        if (strlen(input) == 0)
            valid = 0;

        if (tlab > 1000)
        {
            valid = 0;
        }

        if (!valid)
        {
            position(36, 23);
            cout << "Wrong Value Entered, Please Enter Again";
            position(66, 18);
            cout << clear_s;
        }
    } while (!valid);

    position(36, 23);
    cout << clear;
    modified--;
    fee.lab = tlab;

    position(40, 19);
    cout << "Revised Computer Fees :              ";

    do
    {
        valid = 1;

        position(66, 19);
        gets(input);
        cInput = atof(input);
        tcomputer = cInput;

        if (strlen(input) == 0)
            valid = 0;

        if (tcomputer > 1000)
        {
            valid = 0;
        }

        if (!valid)
        {
            position(36, 23);
            cout << "Wrong Value Entered, Please Enter Again";
            position(66, 19);
            cout << clear_s;
        }
    } while (!valid);

    position(36, 23);
    cout << clear;
    modified--;
    fee.computer = tcomputer;

    position(40, 20);
    cout << "Revised Activity Fees :          ";

    do
    {
        valid = 1;
        position(66, 20);
        gets(input);
        cInput = atof(input);
        tactivity = cInput;

        if (strlen(input) == 0)
            valid = 0;

        if (tactivity > 1000)
        {
            valid = 0;
        }

        if (!valid)
        {
            position(36, 23);
            cout << "Wrong Value Entered, Please Enter Again";
            position(66, 20);
            cout << clear_s;
        }
    } while (!valid);

    position(36, 23);
    cout << clear;
    modified--;
    fee.activity = tactivity;

    do
    {
        position(38, 23);
        cout << "Do you want to save this (y/n) : ";
        ch = getch();
        cout << ch;
        ch = toupper(ch);
        getch();
    } while (ch != 'N' && ch != 'Y');

    if (ch == 'N')
    {
        return;
        // home();
    }

    if (ch == 'Y')
    {
        fstream file;
        file.open("FEE.TXT", ios::out | ios::in);

        if (tclass <= 10)
        {
            file.seekp((tclass - 1) * sizeof(FEE));
        }
        else
        {
            file.seekp(((tclass - 1) * sizeof(FEE)) + 1);
        }

        file.write((char *)&fee, sizeof(FEE));
        file.close();
        getch();
    }

    system("cls");

    DISPLAY(tclass);

    position(40, 13);
    printf("The new fee structure for class %d", tclass);

    position(42, 17);
    printf("Press <Enter> to return HOME..");
    getch();
}

// Function to display the Fee Slip
void FEE::SLIP(void)
{
    system("cls");

    char input[3];
    int cInput = 0, tclass = 0;
    float total = 0;

    do
    {
        valid = 1;
        position(41, 20);
        cout << "Press <ENTER> to return Home               ";
        position(41, 4);
        cout << "CLASS : ";
        gets(input);
        cInput = atoi(input);
        tclass = cInput;

        if (strlen(input) == 0)
            return;

        if (tclass < 1 || tclass > 12)
        {
            valid = 0;
            position(41, 19);
            cout << "Wrong Value Entered, Please Enter Again";
            position(41, 4);
            cout << clear;
        }
    } while (!valid);

    position(41, 20);
    cout << clear;

    string name;

    do
    {
        valid = 1;
        position(41, 6);
        cout << "STUDENT NAME : ";
        getline(cin, name);
        if (strlen(name.c_str()) < 1)
        { // or name.length()
            valid = 0;
            position(41, 20);
            cout << "Please Enter a valid Name     ";
            position(41, 6);
            cout << clear;
        }
        else if (!studentFind(tclass, name))
        {
            valid = 0;
            position(41, 20);
            cout << "Name is not registered with us";
            position(41, 6);
            cout << clear;
        }
    } while (!valid);

    system("cls");

    DRAW d;

    d.BOX(36, 2, 77, 24, 989);

    position(40, 3);
    cout << "    DAV PUBLIC SCHOOL, BURLA      ";

    int d1, m1, y1;
    time_t td = time(0);
    struct tm *now = localtime(&td);
    d1 = now->tm_mday;
    m1 = (now->tm_mon + 1);
    y1 = (now->tm_year + 1900);

    position(60, 4);
    cout << "Date: " << d1 << "/" << m1 << "/" << y1;

    d.LINE_HOR(37, 76, 5, 196);

    position(38, 6);
    cout << "STUDENT NAME  : " << name;

    position(38, 7);
    cout << "CLASS : " << tclass;

    d.LINE_HOR(37, 76, 8, 196);

    position(39, 9);
    cout << "PARTICULARS                AMOUNT";

    d.LINE_HOR(37, 76, 10, 196);

    d.LINE_HOR(37, 76, 22, 196);

    d.LINE_HOR(62, 76, 20, 196);

    position(41, 21);
    cout << "TOTAL";

    position(70, 23);
    cout << "CASHIER";

    fstream file;
    file.open("FEE.TXT", ios::in);

    while (file.read((char *)this, sizeof(FEE)))
    {

        if (Class == tclass)
        {

            total = 0.00;

            position(39, 12);
            cout << "Tuition fees               " << tuition;
            total = total + tuition;

            position(39, 13);
            cout << "Library fees               " << library;
            total = total + library;

            position(39, 14);
            cout << "Science fees               " << lab;
            total = total + lab;

            position(39, 15);
            cout << "Computer fees              " << computer;
            total = total + computer;

            position(39, 16);
            cout << "Activity fees              " << activity;
            total = total + activity;
        }
    }

    file.close();

    d.LINE_VER(9, 21, 62, 179);

    position(66, 21);
    cout << total;

    position(41, 27);
    cout << "Press any key to return HOME..";
    getch();
}

// Function to proovide help
void FEE::HELP()
{
    system("cls");

    DRAW d;

    d.BOX(21, 2, 96, 19, 218);

    position(41, 3);
    cout << "Welcome to FEE MANAGEMENT SYSTEM";
    position(26, 6);
    cout << "Following functions are available:";
    position(26, 8);
    cout << "1. LIST - It lists total fees for all the classes";
    position(26, 10);
    cout << "2. FEE SLIP - It generates the Fee Slip of a Student";
    position(26, 12);
    cout << "3. MODIFY - It lets you modify the fees structure for a class";
    position(26, 14);
    cout << "4. EXIT - It exits the program and returns to the command line";
    position(41, 18);
    cout << "Press any key to return home..";
    getch();
}

// HOME FUNCTION
void home()
{
    system("cls");

    homeAnimation(firstRun);

    position(55, 25);
    choice = getch();
    ch = toupper(choice);
    cout << ch;
    getch();

    firstRun = true;

    int processing = 3; // for entering default values
    bool back = true;   // for returning back from list

    switch (ch)
    {
    case 'F':
        fee.SLIP();
        break;

    case 'M':
        fee.MODIFY();
        break;

    case 'L':
        while (back)
        {
            back = fee.LIST();
        }
        break;

    case 'H':
        fee.HELP();
        break;

    case 'R':
        registerStudent();
        break;

    case 'E':
        system("cls");
        exit(0);
        break;

    case 'D':
        system("cls");
        position(30, 4);
        cout << "Entering all the default values for all classes fees";
        processing = 3;
        while (processing--)
        {
            for (i = 0; i < 3; i++)
            {
                position(54 + i, 5);
                cout << ".";
                Sleep(500);
            }
            position(54, 5);
            cout << clear_s;
        }
        fee.ADD();
        system("cls");
        position(54, 7);
        cout << "DONE!";
        position(43, 12);
        cout << "Press <Enter> to return HOME..";
        getch();
        break;

    default:
        system("cls");
        position(50, 13);
        cout << "ILLEGAL CHOICE!!";
        position(44, 24);
        cout << "Press any key to return to HOME";
        getch();
    }
}

// Main Function from the program runs
int main()
{
    system("cls");

    firstRun = false;

    startAnimation();

    getch();

    while (true)
    {
        home();
    }
}

void startAnimation()
{
    for (i = 26; i < 87; i++)
    {
        position(i, 3);
        // Sleep(10);
        printf("/");
    }
    for (i = 86; i >= 26; i--)
    {
        position(i, 7);
        // Sleep(10);
        printf("/");
    }
    for (j = 4; j <= 6; j++)
    {
        position(26, j);
        // Sleep(100);
        printf("-");
    }
    for (j = 6; j >= 4; j--)
    {
        position(86, j);
        // Sleep(100);
        printf("-");
    }

    position(45, 5);
    printf("FEE MANAGEMENT SYSTEM");

    position(43, 25);
    printf("Press Any Key To Continue..");
}

void homeAnimation(bool firstRun)
{

    DRAW d;

    position(53, 3);
    printf("HOME");

    // Following four loops are for animation of Home Screen
    for (i = 45; i <= 65; i++)
    {
        position(i, 5);
        if (!firstRun)
        {
            // Sleep(30);
        }
        printf("*");
    }
    for (i = 65; i >= 45; i--)
    {
        position(i, 21);
        if (!firstRun)
        {
            // Sleep(30);
        }
        printf("*");
    }
    for (j = 6; j < 21; j++)
    {
        position(45, j);
        if (!firstRun)
        {
            // Sleep(70);
        }
        printf("|");
    }
    for (j = 20; j >= 6; j--)
    {
        position(65, j);
        if (!firstRun)
        {
            // Sleep(70);
        }
        printf("|");
    }

    position(52, 7);
    printf("L: LIST");

    position(50, 10);
    printf("F: FEE SLIP");

    position(51, 13);
    printf("M: MODIFY");

    position(52, 16);
    printf("H: HELP");

    position(52, 19);
    printf("E: EXIT");

    position(32, 23);
    printf("Enter your choice for the corresponding action");

    d.BOX(29, 2, 82, 26, 218);
}

// Function positions the cursor according to the co-ordinates
void position(int x, int y)
{
    COORD coord = {x, y}; // coord is a structure defined in windows.h
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

bool studentFind(int tclass, string studentName)
{
    string line;
    stringstream nm;
    nm << tclass;
    string classString;
    nm >> classString;
    string fileLookup = "Students\\CLASS" + classString + ".TXT";
    fstream tt;
    tt.open(fileLookup.c_str());
    unsigned int curLine = 0;
    nm.clear();
    nm.str(string());
    nm << studentName;
    string firstName, lastName;
    nm >> firstName;
    nm >> lastName;
    while (getline(tt, line))
    {
        curLine++;
        if (strcmpi(line.c_str(), (firstName+" "+lastName).c_str()) == 0)
        {
            studentName = line;
            tt.close();
            return true;
        }
    }
    tt.close();
    return false;
}

void registerStudent()
{
    system("cls");

    int tclass;
    char input[3];
    int cInput = 0;
    int valid = 1;

    do
    {
        valid = 1;
        position(41, 20);
        cout << "Press <ENTER> to return Home               ";
        position(41, 4);
        cout << "CLASS : ";
        gets(input);
        cInput = atoi(input);
        tclass = cInput;

        if (strlen(input) == 0)
            return;

        if (tclass < 1 || tclass > 12)
        {
            valid = 0;
            position(41, 19);
            cout << "Wrong Value Entered, Please Enter Again";
            position(41, 4);
            cout << clear;
        }
    } while (!valid);

    position(41, 20);
    cout << clear;

    string firstName, lastName;

    do
    {
        valid = 1;
        position(41, 6);
        cout << "FIRST NAME : ";
        getline(cin, firstName);
        if (strlen(firstName.c_str()) < 1)
        { 
            valid = 0;
            position(41, 20);
            cout << "Please Enter a valid Name";
            position(41, 6);
            cout << clear;
        }
    } while (!valid);

    do
    {
        valid = 1;
        position(41, 8);
        cout << "LAST NAME : ";
        getline(cin, lastName);
        if (strlen(lastName.c_str()) < 1)
        { 
            valid = 0;
            position(41, 20);
            cout << "Please Enter a valid Name";
            position(41, 8);
            cout << clear;
        }
    } while (!valid);

    trim(firstName);
    trim(lastName);

    stringstream nm;
    nm << tclass;
    string classString;
    nm >> classString;
    string fileLookup = "Students\\CLASS" + classString + ".TXT";
    ofstream tt;
    tt.open(fileLookup.c_str(), ios::app);
    string fullName = firstName+" "+lastName;
    tt << (fullName.c_str()) << endl;
    tt.close();

    system("cls");
    position(50, 8);
    cout << "Thank You!";
    position(35, 10);
    cout << fullName << " is now Registered with us";
    position(43, 22);
    cout << "Press any key to return to HOME";
    getch();
}
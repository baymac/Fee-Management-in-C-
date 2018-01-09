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

using namespace std;

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

void startAnimation();
void homeAnimation();
void home();
void position(int, int);
void customAnimation(int, int, int, int, bool, bool, string, string);

// Global Variables
char ch;
int i, j, valid;
string clear = "                                       ";
string clear_s = "      ";
COORD coord = {0, 0}; // Defines the coordinates of a character cell in a console screen buffer

// To draw lines, boxes
class DRAW
{
  public:
    void hLine(int, int, int, char);
    void vLine(int, int, int, char);
    void box(int, int, int, int, char);
};

// Draws a horizontal line between 2 points
void DRAW::hLine(int column1, int column2, int row, char c)
{
    for (column1; column1 <= column2; column1++)
    {
        position(column1, row);
        cout << c;
    }
}

// Draws a vertical line between 2 points
void DRAW::vLine(int row1, int row2, int column, char c)
{
    for (row1; row1 <= row2; row1++)
    {
        position(column, row1);
        cout << c;
    }
}

// Draws a box between 2 diagonally opposite points
void DRAW::box(int column1, int row1, int column2, int row2, char c)
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
    hLine(column1, column2, row1, l1);
    hLine(column1, column2, row2, l1);
    column1--;
    column2++;
    row1++;
    row2--;
    vLine(row1, row2, column1, l2);
    vLine(row1, row2, column2, l2);
}

// This class contains all the essential functions and variables for fee management
class FEE
{
  private:
    int Class;
    float tuition, library, lab, computer, activity;
    void display(int);
    void insertFees(int, float, float, float, float, float);

  public:
    void addDefault(void);
    bool modifyFees(void);
    bool feeSlip(void);
    bool feeStructure(void);
    void showHelp(void);
} fee;

class STUDENT 
{
    private:
      int Class;
      string rollno, firstName, lastName;
      void display(string);

    public:
      bool studentFind(int, string);
      bool registerStudent(void);
      bool showStudents();
      void flushStudents();
} s;

// Function to add default values of fee structure
void FEE::addDefault(void)
{

    fstream file;
    file.open("FEE.TXT", ios::out | ios::trunc);
    file.close();

    insertFees(1, 250, 50, 0, 40, 40);
    insertFees(2, 250, 50, 0, 40, 40);
    insertFees(3, 250, 50, 0, 40, 40);
    insertFees(4, 250, 50, 0, 40, 40);
    insertFees(5, 250, 50, 0, 40, 40);
    insertFees(6, 300, 50, 20, 40, 50);
    insertFees(7, 300, 50, 20, 40, 50);
    insertFees(8, 300, 50, 20, 40, 50);
    insertFees(9, 350, 50, 20, 60, 50);
    insertFees(10, 350, 50, 30, 60, 50);
    insertFees(11, 450, 50, 60, 60, 50);
    insertFees(12, 450, 50, 60, 60, 50);
}

// Function to insert the fee structure into the file
void FEE::insertFees(int tclass, float ttuition, float tlibrary,
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


// Function to display fee structure for a given class
void FEE::display(int tclass)
{
    DRAW d;

    fstream file;
    file.open("FEE.TXT", ios::in);

    float total = 0;
    
    while (file.read((char *)this, sizeof(FEE)))
    {
        if (Class == tclass)
        {
            position(52, 2);
            cout << "Class : " << Class;

            d.hLine(45, 67, 3, 196);

            position(45, 4);
            cout << "Tuition fees       " << tuition;
            total = total + tuition;

            position(45, 5);
            cout << "Library fees       " << library;
            total = total + library;

            position(45, 6);
            cout << "Lab fees           " << lab;
            total = total + lab;

            position(45, 7);
            cout << "Computer fees      " << computer;
            total = total + computer;

            position(45, 8);
            cout << "Activity fees      " << activity;
            total = total + activity;

            d.hLine(45,67, 9, 196);

            position(45, 10);
            cout << "Total              " << total;
            d.hLine(45, 67, 11, 196);
        }
    }
    file.close();
}

// Function to list all the fee structures of all classes
bool FEE::feeStructure()
{
    system("cls");

    DRAW d;
    d.box(36, 1, 76, 23, 218);

    position(48, 2);
    cout << "ALL CLASSES FEES";

    d.hLine(37, 75, 3, 196);

    position(43, 4);
    cout << " CLASS           TOTAL FEES";

    d.hLine(37, 75, 5, 196);
    d.hLine(37, 75, 21, 196);

    float total = 0;
    int row = 7;

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

    position(38, 22);
    cout << "Enter class to view Fee Structure : ";

    char input[3];
    int tclass;

    do
    {
        valid = 1;
        position(74, 22);
        gets(input);
        tclass = atoi(input);

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
            position(37, 24);
            cout << "Wrong Value Entered, Please Enter Again";
            position(74, 22);
            cout << clear;
            d.box(36, 1, 76, 23, 218);
        }

    } while (!valid);

    if (strlen(input) != 0)
    {
        system("cls");

        d.box(37, 1, 75, 18, 218);

        display(tclass);

        position(44, 16);
        cout << "Press <Enter> to go back..";
        getch();

        return true;
    }
    return false;
}

// Function to modify fee structure of a given class
bool FEE::modifyFees(void)
{
    system("cls");

    DRAW d;

    position(52, 2);
    cout << "MODIFY FEES";
    d.hLine(36, 79, 3, 196);    
    
    d.box(35, 1, 80, 22, 218);

    char input[5];
    int tclass = 0;

    position(42, 18);
    cout << "Enter <d> to enter default fees";
    position(44, 20);
    cout << "Press <Enter> to return HOME..";

    do
    {
        valid = 1;
        position(50, 6);
        cout << "Enter Class : ";
        gets(input);
        if(*input == 'd' | *input == 'D')
        {
            system("cls");
            d.box(38, 1, 76, 18, 218);
            position(51, 3);
            cout << "Default Fees";
            addDefault();
            position(47, 9);
            cout << "All fees set to default.";
            position(43, 16);
            cout << "Press <Enter> to return HOME..";
            getch();
            return false;
        }
        tclass = atoi(input);

        if (strlen(input) == 0)
        {
            return false;
        }
        
        if (tclass < 1 || tclass > 12)
        {
            valid = 0;
        }

        if (!valid)
        {
            position(38, 16);
            cout << "Wrong Value Entered, Please Enter Again";
            position(49, 4);
            cout << clear;
            d.box(35, 1, 80, 22, 218);
        }

    } while (!valid);

    system("cls");

    d.box(27, 1, 86, 24, 218);

    display(tclass);
    Class = tclass;

    do
    {
        position(77, 13);
        cout << clear_s;
        position(33, 13);
        cout << "Do you want to modify the fee structure (y/n) : ";
        ch = getch();
        cout << ch;
        getch();
        ch = toupper(ch);
    } while (ch != 'N' && ch != 'Y');

    if (ch == 'N')
        return true;

    float ttuition = 0.0, tlibrary = 0.0, tlab = 0.0, tcomputer = 0.0, tactivity = 0.0;

    position(42, 16);
    cout << "Revised Tuition Fees : ";
    position(42, 17);
    cout << "Revised Library Fees : ";
    position(42, 18);
    cout << "Revised Lab Fees : ";
    position(42, 19);
    cout << "Revised Computer Fees : ";
    position(42, 20);
    cout << "Revised Activity Fees : ";

    int modified = 5;
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

    file.read((char *)&fee, sizeof(FEE));

    position(38, 23);
    cout << "Press Enter to keep this fee unmodified";
    do
    {
        valid = 1;

        position(68, 16);
        gets(input);
        ttuition = atof(input);

        if (strlen(input) == 0){
            modified++;
            break;
        }
            
        if (ttuition > 1000)
        {
            valid = 0;
        }

        if (!valid)
        {
            position(38, 23);
            cout << "Wrong Value Entered, Please Enter Again";
            position(68, 16);
            cout << clear_s;
        }
    } while (!valid);

    position(38, 23);
    cout << clear;

    modified--;
    if(modified < 5){
        tuition = ttuition;
    } else {
        position(68, 16);
        cout << fee.tuition;
        tuition = fee.tuition;
        modified--;
    }

    position(38, 23);
    cout << "Press Enter to keep this fee unmodified";
    do
    {
        valid = 1;

        position(68, 17);
        gets(input);
        tlibrary = atof(input);

        if (strlen(input) == 0)
        {
            modified++;
            break;
        }

        if (tlibrary > 1000)
        {
            valid = 0;
        }

        if (!valid)
        {
            position(38, 23);
            cout << "Wrong Value Entered, Please Enter Again";
            position(68, 17);
            cout << clear_s;
        }
    } while (!valid);

    position(38, 23);
    cout << clear;
    modified--;
    if(modified < 4)
    {
        library = tlibrary;
    } else {
        position(68, 17);
        cout << fee.library;
        library = fee.library;
        modified--;
    }

    position(38, 23);
    cout << "Press Enter to keep this fee unmodified";
    do
    {
        valid = 1;

        position(68, 18);
        gets(input);
        tlab = atof(input);

        if (strlen(input) == 0)
        {
            modified++;
            break;
        }

        if (tlab > 1000)
        {
            valid = 0;
        }

        if (!valid)
        {
            position(38, 23);
            cout << "Wrong Value Entered, Please Enter Again";
            position(68, 18);
            cout << clear_s;
        }
    } while (!valid);

    position(38, 23);
    cout << clear;
    modified--;
    if(modified < 3)
    {
        lab = tlab;
    } else {
        position(68, 18);
        cout << fee.lab;
        lab = fee.lab;
        modified--;
    }

    position(38, 23);
    cout << "Press Enter to keep this fee unmodified";
    do
    {
        valid = 1;

        position(68, 19);
        gets(input);
        tcomputer = atof(input);

        if (strlen(input) == 0)
        {
            modified++;
            break;
        }


        if (tcomputer > 1000)
        {
            valid = 0;
        }

        if (!valid)
        {
            position(38, 23);
            cout << "Wrong Value Entered, Please Enter Again";
            position(68, 19);
            cout << clear_s;
        }
    } while (!valid);

    position(38, 23);
    cout << clear;
    modified--;
    if(modified < 2)
    {
        computer = tcomputer;
    } else {
        position(68, 19);
        cout << fee.computer;
        computer = fee.computer;
        modified--;
    }

    position(38, 23);
    cout << "Press Enter to keep this fee unmodified";
    do
    {
        valid = 1;
        position(68, 20);
        gets(input);
        tactivity = atof(input);

        if (strlen(input) == 0)
        {
            modified++;
            break;
        }


        if (tactivity > 1000)
        {
            valid = 0;
        }

        if (!valid)
        {
            position(38, 23);
            cout << "Wrong Value Entered, Please Enter Again";
            position(68, 20);
            cout << clear_s;
        }
    } while (!valid);

    position(38, 23);
    cout << clear;
    modified--;
    if(modified < 1)
    {
        activity = tactivity;
    } else {
        position(68, 20);
        cout << fee.activity;
        activity = fee.activity;
        modified--;
    }

    do
    {   
        position(70, 23);
        cout << clear_s;
        position(40, 23);
        cout << "Do you want to save this (y/n) : ";
        ch = getch();
        cout << ch;
        ch = toupper(ch);
        getch();
    } while (ch != 'N' && ch != 'Y');

    if (ch == 'N')
    {
        return true;
    }

    if (ch == 'Y')
    {
        if (tclass <= 10)
        {
            file.seekp((tclass - 1) * sizeof(FEE));
        }
        else
        {
            file.seekp(((tclass - 1) * sizeof(FEE)) + 1);
        }
        file.write((char *)this, sizeof(FEE));
        file.close();
        getch();
    }

    system("cls");

    d.box(37, 1, 75, 22, 218);

    display(tclass);

    position(39, 17);
    printf("The new fee structure for class %d", tclass);

    position(43, 19);
    printf("Press <Enter> to go back..");
    getch();
    return true;
}

// Function to display the Fee Slip
bool FEE::feeSlip(void)
{
    system("cls");

    DRAW d;

    position(49, 2);
    cout << "GENERATE FEE SLIP";
    d.hLine(33, 82, 3, 196);

    char input[3];
    int tclass = 0;
    float total = 0;

    position(44, 6);
    cout << "CLASS : ";

    position(44, 8);
    cout << "STUDENT NAME : ";

    do
    {
        valid = 1;
        position(44, 20);
        cout << "Press <ENTER> to return Home               ";
        d.box(32, 1, 83, 22, 218);
        position(44, 6);
        cout << "CLASS : ";
        gets(input);
        tclass = atoi(input);
        Class = tclass;
        
        if (strlen(input) == 0)
            return false;

        if (tclass < 1 || tclass > 12)
        {
            valid = 0;
            position(38, 18);
            cout << "Wrong Value Entered, Please Enter Again";
            position(44, 6);
            cout << clear;
        }
    } while (!valid);
    position(38, 18);
    cout << clear;
    string name;

    do
    {
        valid = 1;
        position(44, 8);
        cout << "STUDENT NAME : ";
        getline(cin, name);
        if (name.length() == 0) {
            return false;
        }
        else if (!s.studentFind(tclass, name))
        {
            valid = 0;
            position(43, 16);
            cout << "Name is not registered with us";
            do
            {   
                position(80, 18);
                cout << " ";
                position(36, 18);
                cout << "Do you want to register the student (y/n) : ";
                ch = getch();
                cout << ch;
                ch = toupper(ch);
                getch();
            } while (ch != 'N' && ch != 'Y');
            bool b = true;
            if (ch == 'Y')
            {
                while(b)
                {
                    b = s.registerStudent();
                }
                return true;
            }
            position(44, 8);
            cout << clear;
            position(43, 16);
            cout << clear;
            position(36, 18);
            cout << clear + "       ";
        }
    } while (!valid);

    system("cls");

    d.box(36, 1, 77, 24, 989);

    position(40, 2);
    cout << "    DAV PUBLIC SCHOOL, BURLA      ";

    int d1, m1, y1;
    time_t td = time(0);
    struct tm *now = localtime(&td);
    d1 = now->tm_mday;
    m1 = (now->tm_mon + 1);
    y1 = (now->tm_year + 1900);

    position(60, 3);
    cout << "Date: " << d1 << "/" << m1 << "/" << y1;

    d.hLine(37, 76, 4, 196);

    position(38, 5);
    cout << "STUDENT NAME  : " << name;

    position(38, 6);
    cout << "CLASS : " << tclass;

    d.hLine(37, 76, 7, 196);

    position(39, 8);
    cout << "PARTICULARS                AMOUNT";

    d.hLine(37, 76, 9, 196);

    d.hLine(37, 76, 21, 196);

    d.hLine(62, 76, 19, 196);

    position(41, 20);
    cout << "TOTAL";

    position(70, 22);
    cout << "CASHIER";

    fstream file;
    file.open("FEE.TXT", ios::in);

    while (file.read((char *)this, sizeof(FEE)))
    {

        if (Class == tclass)
        {

            total = 0.0;

            position(39, 11);
            cout << "Tuition fees               " << tuition;
            total = total + tuition;

            position(39, 12);
            cout << "Library fees               " << library;
            total = total + library;

            position(39, 13);
            cout << "Science fees               " << lab;
            total = total + lab;

            position(39, 14);
            cout << "Computer fees              " << computer;
            total = total + computer;

            position(39, 15);
            cout << "Activity fees              " << activity;
            total = total + activity;
        }
    }

    file.close();

    d.vLine(8, 20, 62, 179);

    position(66, 20);
    cout << total;

    position(42, 26);
    cout << "Press <Enter> to go back..";
    getch();
    return true;
}

// Function to proovide help
void FEE::showHelp()
{
    system("cls");

    DRAW d;

    d.box(16, 1, 102, 26, 218);

    position(40, 2);
    cout << "Welcome to FEE MANAGEMENT SYSTEM";
    position(21, 5);
    cout << "Following functions are available:";
    position(21, 7);
    cout << "1. Fees Structure - You can view fees structure of any class";
    position(21, 9);
    cout << "2. Fee Slip - You can generate the Fee Slip of a Student(if registered)";
    position(21, 11);
    cout << "3. Admit Students - You can register a student with a name and a roll no";
    position(21, 13);
    cout << "4. Registered Students - You can view the list of reg. students acc. to class";
    position(21, 15);
    cout << "5. Modify - You can modify the fees structure for a class";
    position(21, 17);
    cout << "H. Help - You can see information about all functions";
    position(21, 19);
    cout << "E. EXIT - To Exit the program and return to the command line";
    position(21, 21);
    cout << "F. FLUSH - To delete all the registered students from the database";
    position(43, 24);
    cout << "Press any key to return home..";
    getch();
}

// HOME FUNCTION
void home()
{
    DRAW d;
    system("cls");

    homeAnimation();

    position(55, 24);
    ch = getch();
    ch = toupper(ch);
    cout << ch;
    position(55, 24);
    getch();

    int tclass;
    bool back = true;   // for returning back from list

    switch (ch)
    {
        case '1':
            while (back)
            {
                back = fee.feeStructure();
            }
            break;

        case '2':
            while (back)
            {
                back = fee.feeSlip();
            }
            break;

        case '3':
            while(back) {
                back = s.registerStudent();
            }
            break;

        case '4':
            while(back){
                back = s.showStudents();
            }
            break;

        case '5':
            while(back) {
                back = fee.modifyFees();
            }            
            break;

        case 'H':
            fee.showHelp();
            break;

        case 'F':
            s.flushStudents();
            break;

        case 'E':
            system("cls");
            exit(0);
            break;

        default:
            system("cls");
            d.box(38, 1, 76, 18, 218);
            position(49, 3);
            cout << "ILLEGAL CHOICE!!";
            position(42, 16);
            cout << "Press any key to return to HOME";
            getch();
    }
}

// Main Function from the program runs
int main()
{
    system("cls");

    fstream file("FEE.TXT", ios::in);
    if(!file.read((char *)&fee, sizeof(FEE))) {
        fee.addDefault();
    }
    file.close();

    startAnimation();

    getch();

    while (true)
    {
        home();
    }
}

void startAnimation()
{
    j = 86;
    for (i = 26; i < 87; i++, j--)
    {
        position(i, 1);
        printf("/");
        position(j, 5);
        printf("/");
        Sleep(10);
        
    }
    for (j = 2; j <= 4; j++)
    {
        position(26, j);
        printf("/");
        position(86, j);
        printf("/");
        position(1, 1);
        Sleep(50);
        
    }
    
    position(45, 3);
    printf("FEE MANAGEMENT SYSTEM");

    for (j = 6; j <= 22; j++)
    {
        position(26, j);
        printf("/");
        position(86, j);
        printf("/");
        position(1, 1);
        Sleep(50);
    }
    j = 86;
    for (i = 26; i <= 56; i++, j--)
    {
        position(i, 23);
        printf("/");
        position(j, 23);
        printf("/");
        position(1, 1);
        Sleep(50);
    }

    position(43, 21);
    printf("Press Any Key To Continue..");
}

void homeAnimation()
{
    DRAW d;

    position(54, 2);
    printf("HOME");

    d.hLine(35, 77, 3, 218);

    position(35, 5);
    printf("1: Fees Structure");

    position(35, 7);
    printf("2: Fee Slip");

    position(35, 9);
    printf("3: Admit Students");

    position(35, 11);
    printf("4: Registered Students");

    position(35, 13);
    printf("5: Modify Fees");
    
    position(70, 5);
    printf("H: HELP");

    position(70, 7);
    printf("F: FLUSH");

    position(70, 9);
    printf("E: EXIT");

    position(33, 22);
    printf("Enter your choice for the corresponding action");

    d.box(29, 1, 82, 25, 218);
    d.vLine(2, 24, 30, '*');
    d.vLine(2, 24, 81, '*');
}

void customAnimation(int row1, int row2, int col1, int col2, bool choice, bool back, string title, string msg)
{
    DRAW d;

    int padding = 0;
    padding = ((col2 - col1)/2) - (title.length()/2);
    position(padding, row1+1);
    printf(title);

    d.hLine(col1+1, col2-1, row1+2, 218);

    padding = (col2 - col1 - msg.length())/2;

    if(choice) {
        if(col2 > 25) {
            position(col1 + padding, row2 - 3);
            printf(msg);
        } else {
            position(col1 + padding, 18);
            printf(msg);
        }
    }
    if (!back) 
    {
        if(col2 > 25) {
            padding = (col2 - col1 - 31)/2;
            position(col1 + padding, row2 - 3);
            printf("Press <Enter> to return HOME..");
        } else {
            padding = (col2 - col1 - 27)/2;
            position(col1 + padding, 22);
            printf("Press <Enter> to go back..");
        }
    }
    else {
        if(col2 > 25) {
            padding = (col2 - col1 - 31)/2;
            position(col1 + padding, row2 - 3);
            printf("Press <Enter> to return HOME..");
        } else {
            padding = (col2 - col1 - 27)/2;
            position(col1 + padding, 22);
            printf("Press <Enter> to go back..");
        }
    }
    d.box(col1, row1, col2, row2, 218);
    d.vLine(row1+1, row2-1, col1+1, '*');
    d.vLine(row1+1, row2-1, col2-1, '*');
}

// Function positions the cursor according to the co-ordinates
void position(int x, int y)
{
    COORD coord = {x, y}; // coord is a structure defined in windows.h
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

bool STUDENT::studentFind(int tclass, string studentName)
{
    stringstream nm;
    nm << tclass;
    string classString;
    nm >> classString;
    string fileLookup = "Students\\CLASS" + classString + ".TXT";
    fstream tt;
    tt.open(fileLookup.c_str(), ios::in);
    
    nm.clear();
    nm.str(string());

    nm << studentName;
    string fName, lName;
    nm >> fName;
    nm >> lName;

    while (tt.read((char *)this, sizeof(STUDENT)))
    {
        if (strcmpi((firstName + " " + lastName).c_str(), (fName + " " + lName).c_str()) == 0)
        {
            tt.close();
            return true;
        }
    }
    
    tt.close();
    return false;
}

bool STUDENT::registerStudent()
{
    DRAW d;

    system("cls");

    d.box(34, 1, 77, 22, 218);

    position(45, 2);
    cout << "Student Registration";
    d.hLine(36, 72, 3, 196);

    int tclass;
    char input[3];
    int valid = 1;

    position(41, 4);
    cout << "CLASS : ";

    position(41, 6);
    cout << "Roll No. : ";

    position(41, 8);
    cout << "FIRST NAME : ";

    position(41, 10);
    cout << "LAST NAME  : ";

    do
    {
        valid = 1;
        position(41, 20);
        cout << "Press <ENTER> to return Home";
        position(41, 4);
        cout << "CLASS : ";
        gets(input);
        tclass = atoi(input);
        Class = tclass;

        if (strlen(input) == 0)
            return false;

        if (tclass < 1 || tclass > 12)
        {
            valid = 0;
            position(37, 18);
            cout << "Wrong Value Entered, Please Enter Again";
            position(41, 4);
            cout << clear;
            d.box(34, 1, 77, 22, 218);
        }
    } while (!valid);

    position(37, 18);
    cout << clear;
    d.box(34, 1, 77, 22, 218);

    do
    {
        valid = 1;
        position(41, 6);
        cout << "Roll No. : ";
        getline(cin, rollno);
        if(strlen(rollno.c_str()) == 0) 
        {
            return false;
        }

        if (strlen(rollno.c_str()) >= 10)
        {
            valid = 0;
            position(37, 18);
            cout << "Wrong Value Entered, Please Enter Again";
            position(41, 6);
            cout << clear;
            d.box(34, 1, 77, 22, 218);
        }
    } while (!valid);

    position(37, 18);
    cout << clear;
    d.box(34, 1, 77, 22, 218);

    do
    {
        valid = 1;
        position(41, 8);
        cout << "FIRST NAME : ";
        getline(cin, firstName);

        if (firstName.length() == 0) {
            return false;
        }
        if (firstName.length() < 2)
        { 
            valid = 0;
            position(41, 18);
            cout << "Please Enter a valid Name";
            position(41, 8);
            cout << clear;
            d.box(34, 1, 77, 22, 218);
        }
    } while (!valid);

    position(41, 18);
    cout << clear;
    d.box(34, 1, 77, 22, 218);

    do
    {
        valid = 1;
        position(41, 10);
        cout << "LAST NAME  : ";
        getline(cin, lastName);

        if (lastName.length() == 0) {
            return false;
        }
        if (lastName.length() < 2 || (lastName.length() + firstName.length()) >= 46)
        { 
            valid = 0;
            position(41, 18);
            cout << "Please Enter a valid Name";
            position(41, 10);
            cout << clear;
            d.box(34, 1, 77, 22, 218);
        }
    } while (!valid);

    position(41, 18);
    cout << clear;

    trim(firstName);
    trim(lastName);

    do
    {   
        position(70, 18);
        cout << clear_s;
        d.box(34, 1, 77, 22, 218);
        position(38, 18);
        cout << "Do you want to save this (y/n) : ";
        ch = getch();
        cout << ch;
        ch = toupper(ch);
        getch();
    } while (ch != 'N' && ch != 'Y');

    if (ch == 'N')
    {
        return true;
    }

    if (ch == 'Y')
    {
        stringstream nm;
        nm << tclass;
        string classString;
        nm >> classString;
        string fileLookup = "Students\\CLASS" + classString + ".TXT";
        fstream tt;
        tt.open(fileLookup.c_str(), ios::app);
        tt.write((char *)this, sizeof(STUDENT));
        tt.close();

        system("cls");
        d.box(32, 1, 79, 22, 218);
        position(44, 2);
        cout << "Registration Successful!";
        position(47, 8);
        cout << "Congratulations!";
        int padding = (47 - (firstName.length() + lastName.length() + 1))/2;
        position(32 + padding, 10);
        cout << firstName << " " << lastName;
        position(41, 12);
        cout << "You are now registered with us.";
        padding = (47 - (10 + rollno.length()))/2;
        position(32 + padding, 14);
        cout << "Roll No : " << rollno;
        position(44, 20);
        cout << "Press <Enter> to go back..";
        getch();
    }
    return true;
}

bool STUDENT::showStudents() 
{
    system("cls");

    int tclass;
    char input[3];
    int valid = 1;

    DRAW d;

    position(46, 2);
    cout << "REGISTERED STUDENTS";

    d.hLine(36, 76, 3, 196);

    

    do
    {
        valid = 1;
        position(43, 20);
        cout << "Press <ENTER> to return Home";
        d.box(35, 1, 77, 22, 218);
        position(50, 7);
        cout << "CLASS : ";
        gets(input);
        tclass = atoi(input);

        if (strlen(input) == 0)
            return false;

        if (tclass < 1 || tclass > 12)
        {
            valid = 0;
            position(37, 18);
            cout << "Wrong Value Entered, Please Enter Again";
            position(50, 7);
            cout << clear;
            d.box(35, 1, 77, 22, 218);
        }
    } while (!valid);

    stringstream nm;
    nm << tclass;
    string classString;
    nm >> classString;
    string fileLookup = "Students\\CLASS" + classString + ".TXT";
    system("cls");
    display(fileLookup);
    return true;
}

void STUDENT::display(string file) 
{
    DRAW d;
    int padding;
    fstream tt;
    tt.open(file.c_str(), ios::in);
    bool found = false;
    int line = 4;
    position(40, 2);
    cout << "Roll No";
    position(54, 2);
    cout << "Student Name";
    d.hLine(37, 80, 3, 196);
    
    while(tt.read((char *)this, sizeof(STUDENT))) {
        found = true;
        position(40, line);
        cout << rollno;
        position(54, line);
        cout << firstName << " " << lastName << "\n";
        line++;
    }
    tt.close();
    if(!found) {
        position(38, line);
        cout << "No Students have registered for this class!";
    }
    if(line < 7) {
        d.box(36, 1, 81, 12, 218);
        position(45, 10);
        cout << "Press <Enter> to go back..";
        getch();
    } else {
        d.box(36, 1, 81, line + 4, 218);
        position(45, line + 2);
        cout << "Press <Enter> to go back..";
        getch();
    }
    
}

void STUDENT::flushStudents() 
{
    DRAW d;
    int tclass = 1;
    stringstream nm;
    while(tclass <= 12) 
    {
        nm << tclass;
        string classString;
        nm >> classString;
        string fileLookup = "Students\\CLASS" + classString + ".TXT";
        fstream tt(fileLookup.c_str(), ios::out | ios::trunc);
        tt.close();
        nm.clear();
        nm.str(string());
        tclass++;
    }
    system("cls");
    d.box(37, 1, 75, 18, 218);
    position(45, 3);
    cout << "Removing Students Name";
    position(47, 9);
    cout << "All Names Cleared!";
    position(41, 16);
    cout << "Press any key to return to HOME";
    getch();
}
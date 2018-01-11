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
// To draw lines, boxes
class DRAW
{
  public:
    void hLine(int, int, int, char);
    void vLine(int, int, int, char);
    void box(int, int, int, int, char);
} d;

// This class contains all the essential functions and variables for fee management
class FEE
{
  private:
    int Class;
    float tuition, library, lab, computer, activity;
    void display(int);
    void defaultFees(string);
    FEE readFees(int);
    void writeFees(int, FEE);
    void getRevisedFees(FEE &);
    void printSlip(int, string, string);

  public:
  void addDefault(void);
    void setClass(int tclass) {
        Class = tclass;
    }
    void setTuition(float ttuition) {
        tuition = ttuition;
    }
    void setLibrary(float tlibrary) {
        library = tlibrary;
    }
    void setLab(float tlab) {
        lab = tlab;
    }
    void setComputer(float tcomputer) {
        computer = tcomputer;
    }
    void setActivity(float tactivity) {
        activity = tactivity;
    }
    bool feeStructure(void);
    bool modifyFees(void);
    bool feeSlip(void);
    void showHelp(void);
} fee;

class STUDENT 
{
    private:
      int Class;
      string rollno, firstName, lastName;
      int display(int);
      int search(string, string, int);
      void registrationSuccess(int);

    public:
      void secondaryRegistration(int);
      bool studentFind(int, string);
      bool registerStudent(void);
      bool searchStudent(bool &);
      void flushStudents();
      bool listByClass();
      bool searchByRoll();
      bool searchByName();
      bool deleteStudent();
} s;


// Global Variables
char ch;
int i, j, valid;
string clear_s = "      ";
COORD coord = {0, 0}; // Defines the coordinates of a character cell in a console screen buffer

void startAnimation();
void homeAnimation();
void customAnimation(int, int, int, int, bool, bool, string, string);
void home(bool &);
bool illegalChoice(int, int, int, int);
void insertFees(int, float, float, float, float, float, FEE);
int getClass(int, int, int, int);
int getFees(int, int, int, int, int &);
string getRoll(int, int, int, int);
string getName(int, int, int, int);

// Function positions the cursor according to the co-ordinates
static inline void position(int x, int y)
{
    COORD coord = {x, y}; // coord is a structure defined in windows.h
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// trim from start
static inline string &ltrim(string &s) {
    s.erase(s.begin(), find_if(s.begin(), s.end(),
            not1(ptr_fun<int, int>(isspace))));
    return s;
}

// trim from end
static inline string &rtrim(string &s) {
    s.erase(find_if(s.rbegin(), s.rend(),
            not1(ptr_fun<int, int>(isspace))).base(), s.end());
    return s;
}

// trim from both ends
static inline string &trim(string &s) {
    return ltrim(rtrim(s));
}

static inline string clear(int n) {
    string clear;
    while(n--) {
        clear+= " ";
    }
    return clear;
}

// Function to insert the fee structure into the file
void insertFees(int tclass, float ttuition, float tlibrary,
                      float tlab, float tcomputer, float tactivity, FEE f)
{
    ofstream file;

    file.open("FEE.TXT", ios::app);
    if (file.fail())
    {
        exit(0);
    }

    f.setClass(tclass);
    f.setTuition(ttuition);
    f.setLibrary(tlibrary);
    f.setLab(tlab);
    f.setComputer(tcomputer);
    f.setActivity(tactivity);

    file.write((char *)&f, sizeof(FEE));

    file.close();
}

int getClass(int col1, int row1, int col2, int row2) 
{
    int valid = 0;
    char input[3]; 
    int tclass;
    do
    {
        valid = 1;
        position(col1, row1);
        gets(input);
        tclass = atoi(input);

        if (strlen(input) == 0)
            return 0;

        if(*input == 'd' | *input == 'D') {
            return 71;
        }

        if (tclass < 1 || tclass > 12)
        {
            valid = 0;
            position(col2, row2);
            cout << "Wrong Value Entered, Please Enter Again";
            position(col1, row1);
            cout << clear(8);
        }
    } while (!valid);
    
    position(37, 18);
    cout << clear(40);
    return tclass;
}

string getRoll(int col1, int row1, int col2, int row2)
{   
    string roll;
    int valid = 0;
    do
    {
        valid = 1;
        position(col1, row1);        
        getline(cin, roll);
        if(roll.length() == 0) 
        {
            return "";
        }

        if (roll.length() >= 10)
        {
            valid = 0;
            position(col2, row2);
            cout << "Wrong Value Entered, Please Enter Again";
            position(col1, row1);
            cout << clear(20);
        }
    } while (!valid);

    position(col2, row2);
    cout << clear(40);
    return roll;
}

string getName(int col1, int row1, int col2, int row2)
{   
    int valid = 0;
    string name;
    do
    {
        valid = 1;
        position(col1, row1);
        cout << clear(30);
        position(col1, row1);
        getline(cin, name);

        if (name.length() == 0) {
            return "";
        }
        if (name.length() < 2)
        { 
            valid = 0;
            position(col2, row2);
            cout << "Please Enter a valid Name";
            position(col1, row1);
            cout << clear(20);
        }
    } while (!valid);

    position(col2, row2);
    cout << clear(26);
    return name;
}
 

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

// Function to add default values of fee structure
void FEE::addDefault(void)
{

    fstream file;
    file.open("FEE.TXT", ios::out | ios::trunc);
    file.close();

    insertFees(1, 250, 50, 0, 40, 40, *this);
    insertFees(2, 250, 50, 0, 40, 40, *this);
    insertFees(3, 250, 50, 0, 40, 40, *this);
    insertFees(4, 250, 50, 0, 40, 40, *this);
    insertFees(5, 250, 50, 0, 40, 40, *this);
    insertFees(6, 300, 50, 20, 40, 50, *this);
    insertFees(7, 300, 50, 20, 40, 50, *this);
    insertFees(8, 300, 50, 20, 40, 50, *this);
    insertFees(9, 350, 50, 20, 60, 50, *this);
    insertFees(10, 350, 50, 30, 60, 50, *this);
    insertFees(11, 450, 50, 60, 60, 50, *this);
    insertFees(12, 450, 50, 60, 60, 50, *this);
}


// Function to display fee structure for a given class
void FEE::display(int tclass)
{
    fstream file;
    file.open("FEE.TXT", ios::in);

    float total = 0;
    
    while (file.read((char *)this, sizeof(FEE)))
    {   
        int line = 5;
        if (Class == tclass)
        {
            position(45, line++);
            cout << "Class : " << Class;

            d.hLine(45, 67, line++, 196);

            position(45, line++);
            cout << "Tuition fees       " << tuition;
            total = total + tuition;

            position(45, line++);
            cout << "Library fees       " << library;
            total = total + library;

            position(45, line++);
            cout << "Lab fees           " << lab;
            total = total + lab;

            position(45, line++);
            cout << "Computer fees      " << computer;
            total = total + computer;

            position(45, line++);
            cout << "Activity fees      " << activity;
            total = total + activity;

            d.hLine(45, 67, line++, 196);

            position(45, line++);
            cout << "Total              " << total;
            
            d.hLine(45, 67, line++, 196);
        }
    }
    file.close();
}

// Function to list all the fee structures of all classes
bool FEE::feeStructure()
{
    system("cls");

    string title = "FEES STRUCTURE";
    string msg = "Enter class to view Fee Structure : ";
    customAnimation(29, 1, 83, 27, true, false, title, msg);

    int line = 5;

    position(44, line);
    cout << "CLASS";
    position(59, line++);
    cout << "TOTAL FEES";

    float total = 0;

    fstream file;
    file.open("FEE.TXT", ios::in);

    while (file.read((char *)this, sizeof(FEE)))
    {
        total = tuition + library + lab + computer + activity;
        position(46, ++line);
        cout << Class;
        position(63, line);
        cout << total;
    }

    file.close();

    int tclass;

    tclass = getClass(55, 26, 36, 20);
    if(tclass == 0) {
        return false;
    }

    system("cls");
     
    customAnimation(29, 1, 83, 25, false, true, title, "");

    display(tclass);
    position(69, 24);
    getch();

    return true;
}

int getFees(int col1, int row1, int col2, int row2, int &modified) 
{
    int valid = 0;
    char input[3]; 
    float feeVal;
    do
    {
        valid = 1;
        position(col1, row1);
        gets(input);
        feeVal = atof(input);

        if (strlen(input) == 0)
            modified++;
            break;

        if (feeVal > 1000)
        {
            valid = 0;
        }

        if (!valid)
        {
            position(col2, row2);
            cout << "Wrong Value Entered, Please Enter Again";
            position(col1, row1);
            cout << clear(8);
        }
    } while (!valid);
    
    position(col2, row2);
    cout << clear(40);
    return feeVal;
}

char yesno(int col1, int row1)
{
    char ch;
    do
    {
        position(col1, row1);
        cout << clear(4);
        position(col1, row1);
        ch = getch();
        cout << ch;
        getch();
        ch = toupper(ch);
    } while (ch != 'N' && ch != 'Y' && ch == '\n' && isspace(ch));
    return ch;
}

void FEE::defaultFees(string title) {
    system("cls");
    customAnimation(29, 1, 83, 25, false, true, title, "");

    addDefault();

    position(44, 5);
    cout << "All fees set to default.";
    position(69, 24);
    getch();
}

FEE FEE::readFees(int tclass) {
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

    file.read((char *)this, sizeof(FEE));
    file.close();
    return *this;
}

void FEE::writeFees(int tclass, FEE f) 
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
        file.write((char *)&f, sizeof(FEE));
        file.close();
}

void FEE::getRevisedFees(FEE &f)
{   
    float ttuition = 0.0, tlibrary = 0.0, tlab = 0.0, tcomputer = 0.0, tactivity = 0.0;

    int modified = 5;

    position(43, 16);
    cout << "Revised Tuition Fees  : ";
    position(43, 17);
    cout << "Revised Library Fees  : ";
    position(43, 18);
    cout << "Revised Lab Fees      : ";
    position(43, 19);
    cout << "Revised Computer Fees : ";
    position(43, 20);
    cout << "Revised Activity Fees : ";

    position(38, 23);
    cout << "Press Enter to keep this fee unmodified";

    ttuition = getFees(67, 16, 38, 24, modified);

    modified--;
    if(modified < 5){
        f.tuition = ttuition;
    } else {
        position(67, 16);
        cout << f.tuition;
        modified--;
    }
    
    tlibrary = getFees(67, 17, 38, 24, modified);
    
    modified--;
    if(modified < 4)
    {
        f.library = tlibrary;
    } else {
        position(67, 17);
        cout << f.library;
        modified--;
    }

    tlab = getFees(67, 18, 38, 24, modified);
    modified--;
    if(modified < 3)
    {
        f.lab = tlab;
    } else {
        position(67, 18);
        cout << f.lab;
        modified--;
    }

    tcomputer = getFees(67, 19, 38, 24, modified);
    modified--;
    if(modified < 2)
    {
        f.computer = tcomputer;
    } else {
        position(67, 19);
        cout << f.computer;
        modified--;
    }

    tactivity = getFees(67, 20, 38, 24, modified);
    
    modified--;
    if(modified < 1)
    {
        f.activity = tactivity;
    } else {
        position(67, 20);
        cout << f.activity;
        modified--;
    }

    position(32, 23);
    cout << clear(50);
}

// Function to modify fee structure of a given class
bool FEE::modifyFees(void)
{
    system("cls");

    string title = "MODIFY FEES";
    customAnimation(29, 1, 83, 25, false, false, title, "");

    int tclass = 0;
    char ch ='N';

    position(40, 22);
    cout << "Enter <d> to enter default fees";
    
    position(35, 5);
    cout << "CLASS : ";

    tclass = getClass(43, 5, 36, 20);
    
    if(tclass == 71)
    {
        defaultFees(title);
        return true;
    } else if(tclass == 0) {
        return false;
    }
    
    *this = readFees(tclass);

    system("cls");
    title = "MODIFY FEES";
    string msg = "Do you want to modify the fee structure (y/n)";

    customAnimation(29, 1, 83, 25, true, true, title, msg);

    display(tclass);

    ch = yesno(55, 24);
    
    if(ch == '\n' || isspace(ch) || ch == 'N') {
        return true;
    }
    
    position(31, 20);
    cout << clear(50);
    position(31, 22);
    cout << clear(50);
    position(55, 24);
    cout << " ";
    
    getRevisedFees(*this);

    position(40, 23);
    cout << "Do you want to save this (y/n) : ";
    
    ch = yesno(73, 23);
    
    if(ch == '\n' || isspace(ch) || ch == 'N') {
        return true;
    }

    if (ch == 'Y')
    {
        writeFees(tclass, *this);
    }

    system("cls");  

    char prompt[34];
    // itoa(tclass, prompt, 10);
    sprintf(prompt, "The new fee structure for class %d", tclass);

    customAnimation(29, 1, 83, 25, true, true, title, prompt);

    display(tclass);

    position(69, 20);
    getch();
    return true;
}

// Function to display the Fee Slip
bool FEE::feeSlip(void)
{
    system("cls");

    string title = "FEE SLIP";
    customAnimation(29, 1, 83, 25, false, false, title, "");

    int tclass = 0;
    char ch;

    position(37, 5);
    cout << "CLASS        : ";

    position(37, 7);
    cout << "STUDENT NAME : ";

    tclass = getClass(52, 5, 36, 22);

    if(tclass == 0) 
    {
        return false;
    }

    string name;

    name = getName(52, 7, 43, 22);

    if (name.length() == 0) 
    {
        return false;
    }
    
    if (!s.studentFind(tclass, name))
    {
        s.secondaryRegistration(20);
        return true;;
    }
    
    printSlip(tclass, name, title);

    return true;
}

void STUDENT::secondaryRegistration(int line) 
{
    position(40, line);
    cout << "Name is not registered with us";
    position(33, line+2);
    cout << "Do you want to register the student (y/n) : ";
    ch = yesno(77, line+2);
    if (ch == 'Y')
    {
        bool b = registerStudent();
        
    }
}
void FEE::printSlip(int tclass, string name, string title) 
{
    system("cls");

    int line = 5;
    float total = 0;

    customAnimation(29, 1, 83, 30, false, true, title, "");

    d.box(36, line++, 77, 27, 989);

    int d1, m1, y1;
    time_t td = time(0);
    struct tm *now = localtime(&td);
    d1 = now->tm_mday;
    m1 = (now->tm_mon + 1);
    y1 = (now->tm_year + 1900);

    position(61, line++);
    cout << "Date: " << d1 << "/" << m1 << "/" << y1;

    position(40, line++);
    cout << "    DAV PUBLIC SCHOOL, BURLA      ";

    d.hLine(37, 76, line++, 196);

    position(38, line++);
    cout << "CLASS : " << tclass;
    
    position(38, line++);
    cout << "STUDENT NAME : " << name;

    d.hLine(37, 76, line++, 196);

    position(39, line++);
    cout << "PARTICULARS                AMOUNT";

    d.hLine(37, 76, line++, 196);

    d.hLine(37, 76, 25, 196);

    d.hLine(62, 76, 23, 196);

    position(41, 24);
    cout << "TOTAL";

    position(70, 26);
    cout << "CASHIER";

    fstream file;
    file.open("FEE.TXT", ios::in);

    while (file.read((char *)this, sizeof(FEE)))
    {
        if (Class == tclass)
        {
            total = 0.0;

            position(39, ++line);
            cout << "Tuition fees               " << tuition;
            total = total + tuition;

            position(39, ++line);
            cout << "Library fees               " << library;
            total = total + library;

            position(39, ++line);
            cout << "Science fees               " << lab;
            total = total + lab;

            position(39, ++line);
            cout << "Computer fees              " << computer;
            total = total + computer;

            position(39, ++line);
            cout << "Activity fees              " << activity;
            total = total + activity;
        }
    }
    file.close();

    d.vLine(12, 24, 62, 179);

    position(66, 24);
    cout << total;

    position(69, 29);
    getch();
}
// Function to proovide help
void FEE::showHelp()
{
    system("cls");

    string title = "FEE MANAGEMENT SYSTEM";
    customAnimation(16, 1, 102, 25, false, false, title, "");
    
    int line = 3;
    position(21, line+2);
    cout << "Following functions are available:";
    position(21, line+4);
    cout << "1. Fees Structure - You can view fees structure of any class";
    position(21, line+6);
    cout << "2. Fee Slip - You can generate the Fee Slip of a Student(if registered)";
    position(21, line+8);
    cout << "3. Admit Students - You can register a student with a name and a roll no";
    position(21, line+10);
    cout << "4. Registered Students - You can view the list of reg. students acc. to class";
    position(21, line+12);
    cout << "5. Modify - You can modify the fees structure for a class";
    position(21, line+14);
    cout << "H. Help - You can see information about all functions";
    position(21, line+16);
    cout << "E. EXIT - To Exit the program and return to the command line";
    position(21, line+18);
    cout << "F. FLUSH - To delete all the registered students from the database";
    position(73, 24);
    getch();
}

// HOME FUNCTION
void home(bool &ill)
{
    DRAW d;
    system("cls");

    homeAnimation();

    if(ill == true) {
        position(48, 20);
        cout << "ILLEGAL CHOICE!!";
    }
    
    position(55, 24);
    ch = getch();
    ch = toupper(ch);
    cout << ch;
    position(55, 24);
    getch();

    ill = false;
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
                back = s.searchStudent(ill);
            }
            ill = false;
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
            ill = illegalChoice(29, 1, 85, 25);
    }
}

bool illegalChoice(int col1, int row1, int col2, int row2) {
    position(col1 + 2, row2 - 1);
    cout << clear(50);
    int padding = (col2 - col1 - 16) / 2;
    position(col1 + padding, row2 - 7);
    cout << "ILLEGAL CHOICE!!";
    return true;  
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

    // startAnimation();

    bool ill = false;
    while (true)
    {
        home(ill);
    }
}

void startAnimation()
{
    j = 83;
    for (i = 29; i <= 83; i++, j--)
    {
        position(i, 1);
        printf("/");
        position(j, 5);
        printf("/");
        Sleep(10);
        
    }
    for (j = 2; j <= 4; j++)
    {
        position(29, j);
        printf("/");
        position(83, j);
        printf("/");
        position(1, 1);
        Sleep(50);
        
    }
    
    position(45, 3);
    printf("FEE MANAGEMENT SYSTEM");

    for (j = 6; j <= 25; j++)
    {
        position(29, j);
        printf("/");
        position(83, j);
        printf("/");
        position(1, 1);
        Sleep(50);
    }
    j = 83;
    for (i = 29; i <= 56; i++, j--)
    {
        position(i, 25);
        printf("/");
        position(j, 25);
        printf("/");
        position(1, 1);
        Sleep(20);
    }

    position(43, 23);
    printf("Press Any Key To Continue..");
    getch();
}

void homeAnimation()
{
    DRAW d;

    position(54, 2);
    printf("HOME");

    d.hLine(35, 77, 3, 218);

    position(35, 5);
    printf("1: FEES STRUCTURE");

    position(35, 7);
    printf("2: FEE SLIP");

    position(35, 9);
    printf("3: STUDENT REGISTRATION");

    position(35, 11);
    printf("4: SEARCH STUDENTS");

    position(35, 13);
    printf("5: MODIFY FEES");
    
    position(70, 5);
    printf("H: HELP");

    position(70, 7);
    printf("F: FLUSH");

    position(70, 9);
    printf("E: EXIT");

    position(33, 22);
    printf("Enter your choice for the corresponding action");

    d.box(29, 1, 83, 25, 218);
    d.vLine(2, 24, 30, '*');
    d.vLine(2, 24, 82, '*');
}

void customAnimation(int col1, int row1, int col2, int row2, bool choice, bool back, string title, string msg)
{
    int padding = 0, offset = 0;
    if(choice == false){
        offset += 4;
    }
    padding = (col2 - col1 - title.length()) / 2;
    position(col1+padding, row1+1);
    cout << title;

    d.hLine(col1+6, col2-6, row1+2, 218);

    if (!back) 
    {
        if(col2 > 25) {
            padding = (col2 - col1 - 29)/2;
            position(col1 + padding, row2 - 5 + offset);
            printf("Press <Enter> to return HOME..");
        } else {
            padding = (col2 - col1 - 29)/2;
            position(col1 + padding, 20 + offset);
            printf("Press <Enter> to return HOME..");
        }
    }
    else {
        if(col2 > 25) {
            padding = (col2 - col1 - 26)/2;
            position(col1 + padding, row2 - 5 + offset);
            printf("Press <Enter> to go back..");
        } else {
            padding = (col2 - col1 - 26)/2;
            position(col1 + padding, 20 + offset);
            printf("Press <Enter> to go back..");
        }
    }
    d.box(col1, row1, col2, row2, 218);
    d.vLine(row1+1, row2-1, col1+1, '*');
    d.vLine(row1+1, row2-1, col2-1, '*');
    padding = (col2 - col1 - msg.length())/2;
    if(choice) {
        if(col2 > 25) {
            position(col1 + padding, row2 - 3);
            cout << msg;
        } else {
            position(col1 + padding, 22);
            cout << msg;
        }
    }
}

bool STUDENT::studentFind(int tclass, string info)
{
    stringstream nm;
 
    char fileLookup[25];
    sprintf(fileLookup,"Students\\CLASS%d.TXT", tclass);
    fstream tt;
    tt.open(fileLookup, ios::in);

    nm << info;
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
    system("cls");

    string title = "STUDENT REGISTRATION";
    customAnimation(29, 1, 83, 25, false, false, title, "");

    position(35, 5);
    cout << "CLASS      : ";

    position(35, 7);
    cout << "ROLL NO    : ";

    position(35, 9);
    cout << "FIRST NAME : ";

    position(35, 11);
    cout << "LAST NAME  : ";
    
    Class = getClass(49, 5, 36, 22);
    if(Class == 0) {
        return false;
    }

    rollno = getRoll(49, 7, 36, 22);
    if(rollno.length() == 0) {
        return false;
    }

    do{
        firstName = getName(49, 9, 43, 22);
        if(firstName.length() == 0) {
            return false;
        }
        lastName = getName(49, 11, 43, 22);
        if(lastName.length() == 0) {
            return false;
        }
    } while((lastName.length() + firstName.length()) >= 46);
    
    trim(firstName);
    trim(lastName);

    do
    {   
        position(71, 22);
        cout << clear(5);
        position(38, 22);
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
        system("cls");
        customAnimation(29, 1, 83, 25, false, true, title, "");
        registrationSuccess(Class);    
    }
    return true;
}

void STUDENT::registrationSuccess(int tclass) 
{
    char fileLookup[25];
    sprintf(fileLookup,"Students\\CLASS%d.TXT", tclass);
    fstream tt;
    tt.open(fileLookup, ios::app);
    tt.write((char *)this, sizeof(STUDENT));
    tt.close();

    position(44, 5);
    cout << "Registration Successful!";
    position(48, 10);
    cout << "Congratulations!";
    int padding = (54 - (firstName.length() + lastName.length() + 1))/2;
    position(29 + padding, 12);
    cout << firstName << " " << lastName;
    position(40, 14);
    cout << "You are now registered with us.";
    padding = (54 - (11 + rollno.length() ) )/2;
    position(29 + padding, 16);
    cout << "ROLL NO : " << rollno;
    position(69, 24);
    getch();
}

bool STUDENT::searchStudent(bool &ill) 
{
    system("cls");

    string title = "SEARCH STUDENTS";
    string msg = "Enter your choice for the corresponding action";

    position(35, 5);
    printf("1: List By Class");

    position(35, 7);
    printf("2: Search by Roll");

    position(35, 9);
    printf("3: Search by Name");

    customAnimation(29, 1, 83, 25, true, false, title, msg);

    if(ill == true){
        position(48, 18);
        cout << "ILLEGAL CHOICE!!";
    }

    position(55, 24);    
    ch = getch();
    if(isspace(ch) || ch == '\n') {
        return false;
    }
    ch = toupper(ch);
    cout << ch;
    getch();
    bool back = true;
    ill = false;

    switch(ch) {
        case '1':
            while(back) {
                back = listByClass();
            }
            break;
        case '2':
            while(back) {
                back = searchByRoll();
            }
            break;
        case '3':
            while(back) {
                back = searchByName();
            }
            break;
        default:
            ill = illegalChoice(29, 1, 83, 25);
    }
    return true;
}

bool STUDENT::listByClass()
{
    system("cls");

    string title = "LIST BY CLASS";
    string msg = "Enter Class to view the registered students";

    customAnimation(29, 1, 83, 25, true, true, title, msg);

    position(35, 5);
    cout << "CLASS : ";

    int tclass = getClass(43, 5, 36, 18);

    if(tclass == 0) {
        return false;
    }

    char fileLookup[25];
    sprintf(fileLookup, "Students\\CLASS%d.TXT", tclass);
    
    fstream tt;
    tt.open(fileLookup);
    
    system("cls");
    
    position(35, 7);
    cout << "Roll No";
    position(50, 7);
    cout << "Student Name";
    int line = 9;
    while(tt.read((char *)this, sizeof(STUDENT))) {
        position(35, line);
        cout << rollno;
        position(50, line++);
        cout << firstName << " " << lastName;
    }

    if(line == 9) {
        position(35, 9);
        cout << "No Records Found!";
    }
    
    if(line > 17){
        customAnimation(29, 1, 83, 25 + (line - 17), false, true, title, "");
        position(35, 5);
        cout << "CLASS : " << tclass;
        position(68, 24 + (line - 21));
        getch();
    } else {
        customAnimation(29, 1, 83, 25, false, true, title, "");
        position(35, 5);
        cout << "CLASS : " << tclass;
        position(68, 24); 
        getch();
    }
    return true;
}

bool STUDENT::searchByRoll() {
    system("cls");

    string title = "SEARCH BY ROLL";
    string msg = "Enter Roll No to search for students";

    customAnimation(29, 1, 83, 25, true, true, title, msg);

    string roll;

    position(35, 5);
    cout << "ROLL : ";

    roll = getRoll(43, 5, 36, 18);

    if (roll.length() == 0)
        return false;
    
    int line = 7;

    system("cls");
    line = search("roll", roll, line);
    
    if(line > 21) {
        customAnimation(29, 1, 83, 23 + (line - 21), false, true, title, "");
        position(68, 22 + (line - 17));
        position(35, 5);
        cout << "Search Results for : " << roll;
        position(68, 22 + (line - 21));
        getch();
    } else {
        customAnimation(29, 1, 83, 25, false, true, title, msg);
        position(35, 5);
        cout << "Search Results for : " << roll;
        position(68, 24);
        getch();
    }
    
    return true;
}
bool STUDENT::searchByName() {
    system("cls");

    string title = "SEARCH BY NAME";
    string msg = "Enter Name to search for students";

    customAnimation(29, 1, 83, 25, true, true, title, msg);

    string name;

    position(35, 5);
    cout << "Name : ";
    name = getName(43, 5, 36, 18);
    if (name.length() == 0){
        return false;
    }

    system("cls");

    int line = 7;

    line = search("name", name, line);

    if(line > 21) {
        customAnimation(29, 1, 83, 23 + (line - 21), false, true, title, "");
        position(35, 5);
        cout << "Search Results for : " << name;
        position(68, 22 + (line - 21));
        getch();
    } else {
        customAnimation(29, 1, 83, 25, false, true, title, msg);
        position(35, 5);
        cout << "Search Results for : " << name;
        position(68, 24);
        getch();
    }
    
    return true;
}

int STUDENT::search(string type, string info, int line) {
    int tclass = 1;
    bool found = false;
    char fileLookup[25];
    stringstream nm;

    if(strcmpi(type.c_str(), "roll") == 0)
    {    
        while(tclass <= 12) 
        {
            sprintf(fileLookup, "Students\\CLASS%d.TXT",tclass);
            fstream tt(fileLookup);
            
            while(tt.read((char *)this, sizeof(STUDENT))) 
            {
                if(strcmpi(rollno.c_str(), info.c_str()) == 0) 
                {
                    if(found == false) {
                        position(35, line);
                        found = true;
                    }
                    line = display(line++);
                }
            }
            tclass++;
        }
    } else if(strcmpi(type.c_str(), "name") == 0) 
    {
        while(tclass <= 12) 
        {
            nm << info;
            string fName, lName;
            nm >> fName;
            nm >> lName;

            sprintf(fileLookup,"Students\\CLASS%d.TXT", tclass);
            fstream tt(fileLookup);

            if(lName != "\0") 
            {
                while (tt.read((char *)this, sizeof(STUDENT)))
                {
                    if (strcmpi((firstName + " " + lastName).c_str(), (fName + " " + lName).c_str()) == 0)
                    {
                        line = display(line++);
                        found = true;
                    }
                }
            } else {
                while(tt.read((char *)this, sizeof(STUDENT))) 
                {
                    if(strcmpi(firstName.c_str(), fName.c_str()) == 0) 
                    {
                        line = display(line++);
                        found = true;
                    }
                }
            }
            tt.close();
            nm.clear();
            nm.str(string());
            tclass++;   
        }
    }
    if(!found) {
        position(35, line);
        cout << "NOT FOUND!";
    } 
    return line;
}   

int STUDENT::display(int line) 
{   
    position(35, line++);
    cout << "Class : " << Class;
    position(35, line++);
    cout << "Roll : "<< rollno;
    position(35, line++);
    cout << "Name : "<< firstName << " " << lastName;    
    return line;
}

void STUDENT::flushStudents() 
{
    system("cls");

    string title = "REMOVE ALL STUDENTS";
    
    customAnimation(29, 1, 83, 25, false, false, title, "");
    
    int tclass = 1;
    char fileLookup[25];
    while(tclass <= 12) 
    {
        sprintf(fileLookup, "Students\\CLASS%d.TXT", tclass);
        fstream tt(fileLookup, ios::out | ios::trunc);
        tt.close();
        tclass++;
    }

    position(48, 12);
    cout << "All Names Removed!";
    position(71, 24);
    getch();
}
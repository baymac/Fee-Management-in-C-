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
void home(bool &);
void position(int, int);
void customAnimation(int, int, int, int, bool, bool, string, string);
void illegalChoice(int, int, int, int);

string clear(int n) {
    string clear;
    while(n--) {
        clear+= " ";
    }
    return clear;
}
// Global Variables
char ch;
int i, j, valid;
string clear_s = "      ";
COORD coord = {0, 0}; // Defines the coordinates of a character cell in a console screen buffer

// To draw lines, boxes
class DRAW
{
  public:
    void hLine(int, int, int, char);
    void vLine(int, int, int, char);
    void box(int, int, int, int, char);
}d;

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
      int display(int);
      int search(string, string, int);
    public:
      bool studentFind(int, string);
      bool registerStudent(void);
      bool searchStudent(bool &);
      void flushStudents();
      bool listByClass();
      bool searchByRoll();
      bool searchByName();
      bool deleteStudent();
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

    char input[3];
    int tclass;
    int padding = 0;
    do
    {
        valid = 1;
        position(55, 26);
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
            position(36, 20);
            cout << "Wrong Value Entered, Please Enter Again";
            position(55, 26);
            cout << clear(8);
        }

    } while (!valid);

    trim(string(input));

    system("cls");
     
    customAnimation(29, 1, 83, 25, false, true, title, "");

    display(tclass);
    position(69, 24);
    getch();

    return true;
}

// Function to modify fee structure of a given class
bool FEE::modifyFees(void)
{
    system("cls");

    string title = "MODIFY FEES";
    customAnimation(29, 1, 83, 25, false, false, title, "");

    char input[5];
    int tclass = 0;

    position(40, 22);
    cout << "Enter <d> to enter default fees";
    

    do
    {
        valid = 1;
        position(35, 5);
        cout << "Class : ";
        gets(input);
        if(*input == 'd' | *input == 'D')
        {
            system("cls");
            customAnimation(29, 1, 83, 25, false, true, title, "");
        
            addDefault();

            position(44, 5);
            cout << "All fees set to default.";
            position(69, 24);
            getch();
            return true;
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
            position(36, 20);
            cout << "Wrong Value Entered, Please Enter Again";
            position(43, 5);
            cout << clear(5);
        }

    } while (!valid);

    system("cls");
    title = "MODIFY FEES";
    string msg = "Do you want to modify the fee structure (y/n)";

    customAnimation(29, 1, 83, 25, true, true, title, msg);

    display(tclass);

    Class = tclass;

    do
    {
        position(55, 24);
        cout << clear(4);
        position(55, 24);
        ch = getch();
        if(ch == '\n' || isspace(ch)) {
            return true;
        }
        cout << ch;
        getch();
        ch = toupper(ch);
    } while (ch != 'N' && ch != 'Y');

    if (ch == 'N')
        return true;

    float ttuition = 0.0, tlibrary = 0.0, tlab = 0.0, tcomputer = 0.0, tactivity = 0.0;
    position(31, 20);
    cout << clear(50);
    position(31, 22);
    cout << clear(50);
    position(55, 24);
    cout << clear(1);

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

        position(67, 16);
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
            position(38, 24);
            cout << "Wrong Value Entered, Please Enter Again";
            position(67, 16);
            cout << clear(8);
        }
    } while (!valid);

    position(38, 24);
    cout << clear(40);

    modified--;
    if(modified < 5){
        tuition = ttuition;
    } else {
        position(67, 16);
        cout << fee.tuition;
        tuition = fee.tuition;
        modified--;
    }

    do
    {
        valid = 1;

        position(67, 17);
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
            position(38, 24);
            cout << "Wrong Value Entered, Please Enter Again";
            position(67, 17);
            cout << clear(8);
        }
    } while (!valid);

    position(38, 24);
    cout << clear(40);
    modified--;
    if(modified < 4)
    {
        library = tlibrary;
    } else {
        position(67, 17);
        cout << fee.library;
        library = fee.library;
        modified--;
    }

    do
    {
        valid = 1;

        position(67, 18);
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
            position(38, 24);
            cout << "Wrong Value Entered, Please Enter Again";
            position(67, 18);
            cout << clear(8);
        }
    } while (!valid);

    position(38, 24);
    cout << clear(40);
    modified--;
    if(modified < 3)
    {
        lab = tlab;
    } else {
        position(67, 18);
        cout << fee.lab;
        lab = fee.lab;
        modified--;
    }

    do
    {
        valid = 1;

        position(67, 19);
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
            position(38, 24);
            cout << "Wrong Value Entered, Please Enter Again";
            position(67, 19);
            cout << clear(8);
        }
    } while (!valid);

    position(38, 24);
    cout << clear(40);
    modified--;
    if(modified < 2)
    {
        computer = tcomputer;
    } else {
        position(67, 19);
        cout << fee.computer;
        computer = fee.computer;
        modified--;
    }

    do
    {
        valid = 1;
        position(67, 20);
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
            position(38, 24);
            cout << "Wrong Value Entered, Please Enter Again";
            position(67, 20);
            cout << clear_s;
        }
    } while (!valid);

    position(38, 24);
    cout << clear(40);
    modified--;
    if(modified < 1)
    {
        activity = tactivity;
    } else {
        position(67, 20);
        cout << fee.activity;
        activity = fee.activity;
        modified--;
    }

    position(32, 23);
    cout << clear(50);

    do
    { 
        position(70, 23);
        cout << clear(5); 
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

    char input[3];
    int tclass = 0;
    float total = 0;

    position(37, 5);
    cout << "CLASS        : ";

    position(37, 7);
    cout << "STUDENT NAME : ";

    do
    {
        valid = 1;
        position(52, 5);
        gets(input);
        tclass = atoi(input);
        Class = tclass;
        
        if (strlen(input) == 0)
            return false;

        if (tclass < 1 || tclass > 12)
        {
            valid = 0;
            position(38, 22);
            cout << "Wrong Value Entered, Please Enter Again";
            position(52, 5);
            cout << clear(8);
        }
    } while (!valid);

    position(38, 22);
    cout << clear(40);

    string name;

    do
    {
        valid = 1;
        position(52, 7);
        getline(cin, name);
        if (name.length() == 0) {
            return false;
        }
        else if (!s.studentFind(tclass, name))
        {
            valid = 0;
            position(40, 20);
            cout << "Name is not registered with us";
            do
            {   
                position(87, 22);
                cout << " ";
                position(33, 22);
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
            position(52, 7);
            cout << clear(25);
            position(40, 20);
            cout << clear(31);
            position(33, 22);
            cout << clear(47);
        }
    } while (!valid);

    system("cls");

    int line = 5;

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
    return true;
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
            ill = false;
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
            illegalChoice(29, 1, 85, 25);
            ill = true;
    }
}

void illegalChoice(int col1, int row1, int col2, int row2) {
    position(col1 + 2, row2 - 1);
    cout << clear(50);
    int padding = (col2 - col1 - 16) / 2;
    position(col1 + padding, row2 - 7);
    cout << "ILLEGAL CHOICE!!";  
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
    printf("1: Fees Structure");

    position(35, 7);
    printf("2: Fee Slip");

    position(35, 9);
    printf("3: Student Registration");

    position(35, 11);
    printf("4: Search Students");

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
    padding = ((col2 - col1)/2) - (title.length()/2);
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
    system("cls");

    string title = "STUDENT REGISTRATION";
    customAnimation(29, 1, 83, 25, false, false, title, "");


    int tclass;
    char input[3];
    int valid = 1;

    position(35, 5);
    cout << "CLASS      : ";

    position(35, 7);
    cout << "ROLL NO    : ";

    position(35, 9);
    cout << "FIRST NAME : ";

    position(35, 11);
    cout << "LAST NAME  : ";

    do
    {
        valid = 1;
        position(49, 5);
        gets(input);
        tclass = atoi(input);
        Class = tclass;

        if (strlen(input) == 0)
            return false;

        if (tclass < 1 || tclass > 12)
        {
            valid = 0;
            position(36, 22);
            cout << "Wrong Value Entered, Please Enter Again";
            position(49, 5);
            cout << clear(8);
        }
    } while (!valid);

    position(36, 22);
    cout << clear(40);

    do
    {
        valid = 1;
        position(49, 7);        
        getline(cin, rollno);
        if(strlen(rollno.c_str()) == 0) 
        {
            return false;
        }

        if (strlen(rollno.c_str()) >= 10)
        {
            valid = 0;
            position(36, 22);
            cout << "Wrong Value Entered, Please Enter Again";
            position(49, 7);
            cout << clear(20);
        }
    } while (!valid);

    position(36, 22);
    cout << clear(40);

    do
    {
        valid = 1;
        position(49, 9);
        getline(cin, firstName);

        if (firstName.length() == 0) {
            return false;
        }
        if (firstName.length() < 2)
        { 
            valid = 0;
            position(43, 22);
            cout << "Please Enter a valid Name";
            position(49, 9);
            cout << clear(20);
        }
    } while (!valid);

    position(43, 22);
    cout << clear(26);

    do
    {
        valid = 1;
        position(49, 11);
        getline(cin, lastName);

        if (lastName.length() == 0) {
            return false;
        }
        if (lastName.length() < 2 || (lastName.length() + firstName.length()) >= 46)
        { 
            valid = 0;
            position(43, 22);
            cout << "Please Enter a valid Name";
            position(49, 11);
            cout << clear(20);
        }
    } while (!valid);

    position(43, 22);
    cout << clear(26);

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
        
        customAnimation(29, 1, 83, 25, false, true, title, "");
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
    return true;
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
            illegalChoice(29, 1, 83, 25);
            ill = true;
    }
    return true;
}

bool STUDENT::listByClass()
{
    system("cls");

    string title = "LIST BY CLASS";
    string msg = "Enter Class to view the registered students";

    customAnimation(29, 1, 83, 25, true, true, title, msg);

    int tclass;
    char input[3];
    int valid = 1;

    do
    {
        valid = 1;
        position(35, 5);
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
            position(58, 5);
            cout << clear(5);
        }
    } while (!valid);

    stringstream nm;
    nm << tclass;
    string classString;
    nm >> classString;
    string fileLookup = "Students\\CLASS" + classString + ".TXT";
    fstream tt;
    tt.open(fileLookup.c_str());
    
    system("cls");
    
    position(35, 7);
    cout << "Roll No";
    position(50, 7);
    cout << "Student Name";
    int line = 9;
    while(tt.read((char *)this, sizeof(STUDENT))) {
        position(35, line);
        cout << rollno;
        position(50, line);
        cout << firstName << " " << lastName;
        line++;
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

    do
    {
        valid = 1;
        position(35, 5);
        cout << "ROLL NO : ";
        getline(cin, roll);
        if (roll.length() == 0)
            return false;
    } while (!valid);
    
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
    string msg = "Enter First Name to search for students";

    customAnimation(29, 1, 83, 25, true, true, title, msg);

    string fName;

    position(35, 5);
    cout << "First Name : ";
    getline(cin, fName);
    if (fName.length() == 0){
        return false;
    }

    system("cls");

    int line = 7;

    line = search("name", fName, line);

    if(line > 21) {
        customAnimation(29, 1, 83, 23 + (line - 21), false, true, title, "");
        position(35, 5);
        cout << "Search Results for : " << fName;
        position(68, 22 + (line - 21));
        getch();
    } else {
        customAnimation(29, 1, 83, 25, false, true, title, msg);
        position(35, 5);
        cout << "Search Results for : " << fName;
        position(68, 24);
        getch();
    }
    
    return true;
}

int STUDENT::search(string type, string info, int line) {
    int tclass = 1;
    bool found = false;
    stringstream nm;
    if(strcmpi(type.c_str(), "roll") == 0){
        
        while(tclass <= 12) 
        {
            nm << tclass;
            string classString;
            nm >> classString;
            string fileLookup = "Students\\CLASS" + classString + ".TXT";
            fstream tt(fileLookup.c_str());
            
            while(tt.read((char *)this, sizeof(STUDENT))) {
                if(strcmpi(rollno.c_str(), info.c_str()) == 0) {
                    if(found == false) {
                        position(35, line);
                    }
                    line = display(line++);
                    found = true;
                }
            }
            tt.close();
            nm.clear();
            nm.str(string());
            tclass++;
        }
    } else if(strcmpi(type.c_str(), "name") == 0) {
        while(tclass <= 12) 
        {
            nm << tclass;
            string classString;
            nm >> classString;
            string fileLookup = "Students\\CLASS" + classString + ".TXT";
            fstream tt(fileLookup.c_str());
            
            while(tt.read((char *)this, sizeof(STUDENT))) {
                if(strcmpi(firstName.c_str(), info.c_str()) == 0) {
                    if(found == false) {
                        position(35, line);
                    }
                    line = display(line++);
                    found = true;
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

    position(48, 12);
    cout << "All Names Removed!";
    position(71, 24);
    getch();
}
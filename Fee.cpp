//PROJECT SCHOOL FEE ENQUIRY

#include <iostream>
#include <windows.h> // for using sleep()
#include <fstream>
#include <cstring>
#include <cstdlib> // for using printf(), scanf()
#include <cstdio>
#include <cctype> // for using character functions 
#include <conio.h> // for console functions like position(), getch()
#include <ctime>
#include <dos.h>
#include <iomanip>
#include <string>

using namespace std;

void help(); // function definition for help

void position(int x, int y) // positions the cursor according to the co-ordinates
{
    COORD coord = {x, y}; // coord is a structure defined in windows.h
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//**************************************
//  GLOBAL VARIABLE DECLARATIONS
//**************************************

char ch, choice;
int i, j, li, lp, rec, valid;
string clear = "                                       ";
string clear_s = "      ";
COORD coord = {0, 0}; // Defines the coordinates of a character cell in a console screen buffer

//**************************** ********
// THIS CLASS DRAWS LINES, BOXES, ETC.
//**************************** ********

class DRAW
{
  public:
    void LINE_HOR(int, int, int, char);
    void LINE_VER(int, int, int, char);
    void BOX(int, int, int, int, char);
};

//**********************************************************
// THIS CLASS CONTROLS ALL THE FUNCTIONS RELATED TO FEES
//**********************************************************

class FEE
{
  private:
    int Class;
    float tuition, library, lab , computer, activity;
    void DISPLAY(int);
    void INSERT_FEES(int, float, float, float, float, float);


  public:
    void ADD(void);
    void MODIFY(void);
    void SLIP(void);
    void LIST(void);
    void HELP(void);
} fee;

//****************************************
//                  MAIN MENU FUNCTION
//****************************************
bool firstRun = false;
void home()
{
    system("cls");

    DRAW d;

    position(53, 3);
    printf("HOME");

    for (li = 45; li <= 65; li++)
    {
        position(li, 5);
        if(!firstRun) {
            // Sleep(30);
        }
        printf("*");
    }
    for (li = 65; li >= 45; li--)
    {
        position(li, 21);
        if(!firstRun) {
            // Sleep(30);
        }
        printf("*");
    }
    for (lp = 6; lp < 21; lp++)
    {
        position(45, lp);
        if(!firstRun) {
            // Sleep(100);
        }
        printf("|");
    }
    for (lp = 20; lp >= 6; lp--)
    {
        position(65, lp);
        if(!firstRun) {
            // Sleep(100);
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

    position(55, 25);
    choice = getch();
    ch = toupper(choice);   
    cout << ch;
    getch();

    firstRun = true;
    switch (ch)
    {
    case 'F':
        fee.SLIP();
        break;
    case 'M':
        fee.MODIFY();
        break;
    case 'L':
        fee.LIST();
        break;
    case 'H':
        fee.HELP();
        break;
    case 'E':
        system("cls");
        exit(0);
        break;
    default:
        system("cls");
        position(50, 13);
        cout << "ILLEGAL CHOICE!!";
        position(44, 24);
        cout << "Press any key to return to HOME";
        getch();
        home();
    }
}
//Main Menu Function End

//************************************
// FUNCTION TO DRAW HORIZONTAL LINE
//************************************

void DRAW::LINE_HOR(int column1, int column2, int row, char c)
{
    for (column1; column1 <= column2; column1++)
    {
        position(column1, row);
        cout << c;
    }
}

//**********************************************************
// FUNCTION TO DRAW VERTICAL LINE
//**********************************************************

void DRAW::LINE_VER(int row1, int row2, int column, char c)
{
    for (row1; row1 <= row2; row1++)
    {
        position(column, row1);
        cout << c;
    }
}

//**********************************************************
// FUNCTION TO DRAW BOX LINE
//**********************************************************

void DRAW::BOX(int column1, int row1, int column2, int row2, char c)
{
    char ch = 218;
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

//**********************************************************
// FUNCTION TO ADD FEE STRUCTURE IN FEE FILE
//**********************************************************

void FEE::ADD(void)
{
    fstream file;
    file.open("FEE.TXT", ios:: out | ios::trunc);
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

//**********************************************************
// FUNCTION TO MODIFY THE FEE RECORD FOR THE GIVEN DATA
//**********************************************************

void FEE::INSERT_FEES(int tclass, float ttuition, float tlibrary, 
                        float tlab, float tcomputer, float tactivity)
{
    ofstream file;

    file.open("FEE.TXT", ios::app);
    if (file.fail()){
        exit(0);
    }

    FEE f;
    
    f.Class = tclass;
    f.tuition = ttuition;
    f.library = tlibrary;
    f.lab  = tlab;
    f.computer = tcomputer;
    f.activity = tactivity;
    file.write((char*)&f, sizeof(f));
    
    file.close();
}

//**********************************************************
// FUNCTION TO DISPLAY TOTAL FEE AS LIST
//**********************************************************

void FEE::LIST()
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
 
    float total;
    int row = 8;
    
    fstream file;
    file.open("FEE.TXT", ios::in);
    while (file.read((char *)this, sizeof(FEE)))
    {
        total = tuition + library + lab  + computer + activity;
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

    char t1[10];
    int tclass, t2;

    do {
        valid = 1;
        position(74,23);
        gets(t1);
        t2 = atoi(t1);
        tclass = t2;

        if (tclass < 1 || tclass > 12) {
            valid = 0;
        }

        if(strlen(t1) == 0) {
            home();
        }

        if(!valid){
            position(37, 25);
            cout << "Wrong Value Entered, Please Enter Again";
            position(74, 23);
            cout << clear;
            d.BOX(36, 2, 76, 24, 218);
        }
    }while(!valid);
    
    if(strlen(t1) != 0) {
        system("cls");

        DISPLAY(tclass);

        position(42, 18);
        cout << "Press <Enter> to go back..";

        getch();

        LIST();
    }
    
}

//**********************************************************
// FUNCTION TO DISPLAY THE RECORD FOR THE GIVEN CLASS
//**********************************************************

void FEE::DISPLAY(int tclass) {
    DRAW d;

    fstream file;
    file.open("FEE.TXT", ios::in);
    
    float total  = 0;
    
    while (file.read((char *)this, sizeof(FEE))) {
        if (Class == tclass) {

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
            cout << "Lab fees           " << lab ;
            total = total + lab ;
            
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
            cout << "Total              "  << total;
        }
    }
    file.close();
}

//**********************************************************
// FUNCTION TO GIVE DATA TO MODIFY THE FEE RECORD
//**********************************************************

void FEE::MODIFY(void) {
    
    system("cls");
    
    FEE f;
    
    DRAW d;
    

    char ch, t1[10];
    int valid = 0, tclass = 0;
    float t2 = 0;

    position(42, 15);
    cout << "Press any key to return HOME..";
    
    do
    {
        valid = 1;
        position(49, 3);
        cout << "Enter Class : ";
        gets(t1);
        t2 = atoi(t1);
        tclass = t2;

        if(strlen(t1) == 0){
            home();
        }

        if (tclass < 1 || tclass > 12) {
            valid = 0;
        }

        if(!valid){
            position(42, 15);
            cout << "Wrong Value Entered, Please Enter Again";
            position(49, 3);
            cout << clear;
        }

    } while (!valid);

    system("cls");

    d.BOX(25, 1, 84, 24, 218);

    DISPLAY(tclass);
    f.Class = tclass;
    
    do {
        position(31, 13);
        cout << "Do you want to modify the fee structure (y/n) : ";
        ch = getch();
        cout << ch;
        getch();
        ch = toupper(ch);
    } while (ch != 'N' && ch != 'Y');

    if (ch == 'N')
        home();
    

    float ttuition = 0.0, tlibrary = 0.0, tlab  = 0.0, tcomputer = 0.0, tactivity = 0.0;
    
    position(40, 16);
    cout << "Revised Tuition Fees :           ";
    
    int modified = 5;

    do {
        valid = 1;

        position(66, 16);
        gets(t1);
        t2 = atof(t1);
        ttuition = t2;

        if (strlen(t1) == 0)
            valid = 0;

        if (ttuition > 1000){
            valid = 0;
        }

        if(!valid){
            position(36, 23);
            cout << "Wrong Value Entered, Please Enter Again";
            position(66, 16);
            cout << clear_s;
        }
    } while (!valid);

    position(36, 23);
    cout << clear;
    
    modified--;
    f.tuition  = ttuition;
    
    
    position(40, 17);
    cout << "Revised Library Fees :                  ";

    do {
        valid = 1;
        
        position(66, 17);
        gets(t1);
        t2 = atof(t1);
        tlibrary = t2;
        if (t1[0] == '0')
            return;
        if (strlen(t1) == 0)
            valid = 0;

        if (tlibrary > 1000){
            valid = 0;
        }

        if(!valid){
            position(36, 23);
            cout << "Wrong Value Entered, Please Enter Again";
            position(66, 17);
            cout << clear_s;
        }
    } while (!valid);

    position(36, 23);
    cout << clear;
    modified--;
    f.library  = tlibrary;

    position(40, 18);
    cout << "Revised Lab Fees :             ";

    do {
        valid = 1;
        
        position(66, 18);
        gets(t1);
        t2 = atof(t1);
        tlab  = t2;
        if (t1[0] == '0')
            return;
        if (strlen(t1) == 0)
            valid = 0;

        if (tlab > 1000){
            valid = 0;
        }

        if(!valid){
            position(36, 23);
            cout << "Wrong Value Entered, Please Enter Again";
            position(66, 18);
            cout << clear_s;
        }
    } while (!valid);

    position(36, 23);
    cout << clear;
    modified--;
    f.lab = tlab;

    position(40, 19);
    cout << "Revised Computer Fees :              ";

    do {
        valid = 1;
        
        position(66, 19);
        gets(t1);
        t2 = atof(t1);
        tcomputer = t2;

        if (t1[0] == '0')
            return;
        if (strlen(t1) == 0)
            valid = 0;

        if (tcomputer > 1000){
            valid = 0;
        }

        if(!valid){
            position(36, 23);
            cout << "Wrong Value Entered, Please Enter Again";
            position(66, 19);
            cout << clear_s;
        }
    } while (!valid);

    position(36, 23);
    cout << clear;
    modified--;
    f.computer = tcomputer;

    position(40, 20);
    cout << "Revised Activity Fees :          ";
    
    do {
        valid = 1;
        position(66, 20);
        gets(t1);
        t2 = atof(t1);
        tactivity = t2;
        
        if (t1[0] == '0')
            return;
        if (strlen(t1) == 0)
            valid = 0;

        // for(char *p = t1; p != t1 + sizeof(t1) / sizeof(t1[0]); ++p){
        //     if(!isdigit(*p)){
        //         valid = 0;
        //         break;
        //     }
        // }

        if (tactivity > 1000){
            valid = 0;
        }

        if(!valid){
            position(36, 23);
            cout << "Wrong Value Entered, Please Enter Again";
            position(66, 20);
            cout << clear_s;
        }
    } while (!valid);

    position(36, 23);
    cout << clear;
    modified--;
    f.activity = tactivity;

    do {
        position(38, 23);
        cout << "Do you want to save this (y/n) : ";
        ch = getch();
        cout << ch;
        ch = toupper(ch);
        getch();
    } while (ch != 'N' && ch != 'Y');

    if (ch == 'N')
        home();

    if (ch == 'Y'){
        fstream file;
        file.open("FEE.TXT", ios::out | ios::in);
        file.seekp((tclass-1)*sizeof(FEE));
        file.write((char *)&f, sizeof(FEE));
        file.close();
        getch();
    }
    
    home();
    
}

//**********************************************************
// FUNCTION TO DISPLAY THE FEE SLIP FOR THE CLASS
//**********************************************************

void FEE::SLIP(void) {
    system("cls");

    char ch, t1[10];
    int valid = 0, t = 0, tclass = 0;
    do
    {
        valid = 1;
        position(41, 20);
        cout << "Press <ENTER> to return Home               ";
        position(41, 4);
        cout << "CLASS : ";
        gets(t1);
        t = atoi(t1);
        tclass = t;
        if (strlen(t1) == 0)
            home();
        if (tclass < 1 || tclass > 12)
        {
            valid = 0;
            position(41, 20);
            cout << "Wrong Value Entered, Please Enter Again";
            position(41, 4);
            cout << clear;
        }
    } while (!valid);
    position(41, 20);
    cout << clear;

    char name[26];
    do {
        valid = 1;
        position(41, 6);
        cout << "STUDENT NAME : ";
        gets(name);
        if (strlen(name) < 1 || strlen(name) > 25)
        {
            valid = 0;
            position(41, 20);
            cout << "Please Enter a valid Name";
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

    while (!file.eof())
    {
        file.read((char *)this, sizeof(FEE));
        if (Class == tclass) {
            break;
        }
        file.close();
    }

    float total = 0.0;

    position(39, 12);
    cout << "Tuition fees               "  << tuition;
    total = total + tuition;
    
    position(39, 13);
    cout << "Library fees               "  << library;
    total = total + library;
    
    position(39, 14);
    cout << "Science fees               "  << lab ;
    total = total + lab ;
    
    position(39, 15);
    cout << "Computer fees              "  << computer;
    total = total + computer;
    
    position(39, 16);
    cout << "Activity fees              "  << activity;
    total = total + activity;
    
    d.LINE_VER(9, 21, 62, 179);
    char tt[15];
    sprintf(tt, "%f", total);
    position(65, 21);
    cout << tt;

    position(41, 27);
    cout << "Press any key to return HOME..";
    getch();
    home();
}

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
    
    home();
}

//**********************************************************
// MAIN FUNCTION TO CREATE MENU AND CALL OTHER FUNCTIONS
//**********************************************************

int main()
{
    FEE fee;
    fee.ADD();
    system("cls");

    firstRun = false;

    for (i = 26; i < 87; i++)
    {
        position(i, 3);
        // Sleep(30);
        printf("/");
    }
    for (i = 86; i >= 26; i--)
    {
        position(i, 7);
        // Sleep(30);
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
    getch();
    home();

    return 0;
}
# Fee-Management-in-C++-

-> Definition of COORD inside windows.h

    typedef struct _COORD {
    SHORT X;
    SHORT Y;
    } COORD, *PCOORD;

-> Compilation Process (works only on windows due to windows C++ libraries used)

    1. Install 'mingw.exe'(the C++ compiler for windows). 
    2. Open "Visual C++ 2008 Compiler" and head over to the code folder(using cd)
    3. Type "cl /EHsc Fee.cpp" and press enter
    4. Run the Fee.exe file generated
    
This is a very basic terminal software using the C++ methods and libraries taught in High School. This was my first project with more than a thousand lines. It has been designed and optimised overtime. The main challenge was in organising the functions to make them reusable because of the numerous input types it was checking. I worked hard that time to accomplish this but now as I look back I feel I could have done a web app instead which could have been way simpler. Although if you are in high school and you need a project this is ideal, you can make changes and further improve it. And also need someone who could help me refractor them into files. If you try this in your system then please give me a review on the UI. 


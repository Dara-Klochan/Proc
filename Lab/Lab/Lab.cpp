#include "Header.h"
#include <iostream>

int main(int argc, char* argv[])
{
    if (argc != 3) {
        cout << "incorrect command line! "
            "Waited: command in_file out_file"
            << endl;
        exit(1);
    }

    ifstream ifst(argv[1]);
    ofstream ofst(argv[2]);

    cout << "Start" << endl;

    Container* Head = new Container;

    Init_Container(Head);

    In_Container(Head, ifst);

    Sort(Head);

    ofst << "Filled and sorted container. " << endl;

    Out_Container(Head, ofst);

    Out_Only_Two_Dim(Head, ofst);

    Clear_Container(Head);

    ofst << "Empty container. " << endl;

    Out_Container(Head, ofst);

    cout << "Stop" << endl;

    system("pause");
    return 0;
}
//Simple encryption/decryption utility, based on seeds specified by the user
//By Katie Rector, written April 7-8, 2017

#include "includes.h"

//Gets file name
string getname(string& filename, string& ext)
{
    string name;
    cout << "File name:\n";
    cin >> name;

    //Ensures that file name is valid
    while (name.rfind(".") == -1)
    {
        cout << "Invalid file name.\n";
        cout << "File name:\n";
        cin >> name;
    }

    //Gets position of '.' in file name and creates two strings based on file name without extension and file extension
    int pos = name.rfind(".");
    filename = name.substr(0, pos);
    ext = name.substr(pos, name.size() - pos);

    return name;
}

//Gets encryption/decryption key
int getkey(bool choice)
{
    //Prints correct text based on choice
    string type;
    if (choice)
        type = " decryption";
    else
        type = "n encryption";

    int key = 0;
    cout << "Enter a" + type + " key (integer): \n";
    cin >> key;
    
    //Ensures that entered key is an integer
    while (cin.fail())
    {
        cout << "Invalid key.\n";
        cout << "Enter a" + type + " key (integer): \n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> key;
    }
    return key;
}

//Encrypts specified file
void encr()
{
    string filename, ext;
    string name = getname(filename, ext);

    //Gets encryption key, uses key as seed for rand()
    int key = getkey(0);
    srand(key);
    
    //Reads input file in binary instead of as an ASCII character. This is necessary because of the ASCII character 0x1A,
    //which Windows interprets as an EOF character. This does not occur on Unix-based systems.
    ifstream infile(name, ios::in|ios::binary);
    ofstream outfile(filename + "_e" + ext, ios::out|ios::binary);
    
    //Reads input file one character at a time, adding a random integer to each byte. This is the actual encryption.
    char ch;
    while (infile.get(ch))
    {
        int che = ch + rand();
        outfile.put(che);
    }
    infile.close();
    outfile.close();
}

//Decrypts specified file
void decr()
{
    string filename, ext;
    string name = getname(filename, ext);

    //Gets decryption key
    int key = getkey(1);
    srand(key);

    ifstream infile(name, ios::in | ios::binary);
    ofstream outfile(filename + "_d" + ext, ios::out | ios::binary);
    
    //Subtracts same random integer as was added by encryption, undoing it
    char ch;
    while (infile.get(ch))
    {
        char che = ch - rand();
        outfile.put(che);
    }
    infile.close();
    outfile.close();
}

int main()
{
    char choice;
    cout << "(E)ncrypt or (d)ecrypt?\n";
    cin >> choice;
    while (!(toupper(choice) == 'E' || toupper(choice) == 'D'))
    {
        cout << "Invalid input.\n";
        cout << "(e)ncrypt or (d)ecrypt?\n";
        cin >> choice;
    }

    if (toupper(choice) == 'E')
        encr();
    else
        decr();
    cout << "Operation complete.";
    sleep_for(milliseconds(2000));
    return 0;
}

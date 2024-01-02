#include <iostream>  //predefined library for input and output
#include <fstream>   //predefined library for file handling
#include <string>    // library for strings
#include <iomanip>   //for output manipulation
using namespace std; // to declare std namespace;

void menu();
void addFlight();
void viewFlight();
void checkFlight();
void delFlight();
void editFlight();
void add_id();
void add_time();
string data;

int main()
{
    cout << "--------------------------------------------------------------------------" << endl
         << "\t\t\tFLIGHT MANAGEMENT SYSTEM\n--------------------------------------------------------------------------" << endl;

    while (true)
    {
        menu();
    }

    return 0;
}

void menu()
{
    cout << "1. Add Flight \n2. View Flight \n3. Check Flight \n4. Delete Flight Record \n5. Edit Flight Record \n6. Exit" << endl;
    cout<<"\nEnter the option: ";
    int option;
    cin >> option;

    switch (option)
    {
    case 1:
        cout << "--------------------------------------------------------------------------" << endl
             <<"\t\t\t    ADD A NEW FLIGHT \n--------------------------------------------------------------------------" << endl;
        addFlight();
        break;
    case 2:
        cout << "Flight Record: " << endl;
        viewFlight();
        break;
    case 3:
        cout << "--------------------------------------------------------------------------" << endl
             << "\t\t\tCHECK EXISTING FLIGHT \n--------------------------------------------------------------------------" << endl;
        checkFlight();
        break;
    case 4:
        cout << "--------------------------------------------------------------------------" << endl
             << "\t\t\tDELETE A FLIGHT RECORD \n--------------------------------------------------------------------------" << endl;
        delFlight();
        break;
    case 5:
        cout << "--------------------------------------------------------------------------" << endl
             << "\t\t\tEDIT A FLIGHT RECORD \n--------------------------------------------------------------------------" << endl;
        editFlight();
        break;

    case 6:
        cout << "\nProgram Terminated.";
        exit(0);
        break;
    default:
        cout << "Invalid Option!\n";
    }
}

void add_id()
{
    int counter = 0;
    bool isValid = true;
    bool printed = false;

    cout << "Enter the flight ID \n(Pattern: XY-1234) " << endl;

    for (int i = 0; i < 7; i++)
    {
        char id;
        cin >> id;

        if (counter == 0 || counter == 1)
        {
            if ((id < 'A' || id > 'Z') && (id < 'a' || id > 'z'))
            {
                isValid = false;
            }
        }
        else if (counter == 2)
        {
            if (id != '-')
            {
                isValid = false;
            }
        }
        else if (counter > 2)
        {
            if (id < '0' || id > '9')
            {
                isValid = false;
            }
        }
        if (!isValid)
        {
            if (!printed)
            {
                cout << "Invalid ID. Please Use the pattern XY-1234 \nEnter the flight ID \n(Pattern: XY-1234) " << endl;
                printed = true;
            }
            i = -1;
            data = "";
            isValid = true;
            continue;
        }
        data += id;
        if (counter == 6)
        {
            break;
        }
        counter++;
    }
}

void addFlight()
{
    data = "";
    string id, departure, arrival, time;
    ofstream fout;
    fout.open("Flights Record.txt", ios::app);

    add_id();
    id = data;

    cout << "Enter Flight Departure Place: " << endl;
    cin >> departure;

    cout << "Enter Flight Arrival Place: " << endl;
    cin >> arrival;

    add_time();
    time = data;

    fout << setw(20) << left << id << setw(20) << left << departure << setw(20) << left << arrival << setw(15) << left << time << endl;
    fout.close();
}

void viewFlight()
{
    ifstream fin;
    fin.open("Flights Record.txt");
    try
    {
        if (fin.fail())
        {
            throw 101;
        }
    }
    catch (int error)
    {
        cout << "Error opening the file!\nError Number: " << error << endl;
        return;
    }
    string data;
    cout << "----------------------------------------------------------------------" << setw(20) << left << "\nID" << setw(20) << left << " Departure" << setw(20) << left << " Arrival" << setw(15) << left << " Time" << endl
         << "----------------------------------------------------------------------" << endl
         << endl;

    while (getline(fin, data))
    {
        cout << data << endl;
    }
    cout << "----------------------------------------------------------------------" << endl;
    fin.close();
}

void checkFlight()
{
    string id1, id2;
    bool check = false;
    cout << "Enter flight ID: " << endl;
    cin >> id1;
    ifstream fin;
    fin.open("Flights Record.txt");

    try
    {
        if (fin.fail())
        {
            throw 101;
        }
    }
    catch (int error)
    {
        cout << "Error opening the file!\nError Number: " << error;
        return;
    }
    while (fin >> id2)
    {
        if (id1 == id2)
        {
            check = true;
            break;
        }
    }

    if (check)
    {
        cout << "Flight Number " << id1 << " exists in the record." << endl;
    }
    else
    {
        cout << "Flight Number " << id1 << " does not exist!" << endl;
    }

    fin.close();
}

void delFlight()
{
    string filename = "Flights Record.txt";
    string id;
    cout << "Enter Flight ID you want to delete: ";
    cin >> id;
    ifstream fin;
    fin.open(filename);
    try
    {
        if (fin.fail())
        {
            throw runtime_error("Error opening file");
        }
    }
    catch (runtime_error &e)
    {
        cout << e.what();
    }
    ofstream fout;
    fout.open("temp.txt");
    string line;
    bool deleted = false;
    while (getline(fin, line))
    {
        if (line.find(id) != line.npos)
        {
            deleted = true;
            continue;
        }
        fout << line << endl;
    }
    fin.close();
    fout.close();

    if (deleted)
    {
        if (remove(filename.c_str()) != 0)
        {
            cout << "Error removing the original file." << endl;
        }
        if (rename("temp.txt", filename.c_str()) != 0)
        {
            cout << "Error renaming temporary file." << endl;
        }
        cout << "Flight number " << id << " has been deleted from the file." << endl;
    }
    else
    {
        cout << "No matching record found with Flight ID " << id << "." << endl;
    }
}

void add_time()
{
    data = "";
    bool isValid = true;
    bool printed = false;
    int counter = 0;
    cout << "Enter Departure Time: \n(Format: XX:XX:XX)" << endl;
    while (true)
    {
        char time;
        cin >> time;
        if ((counter == 2 || counter == 5) && time != ':')
        {
            isValid = false;
        }
        else if ((counter != 2 && counter != 5) && (time < '0' || time > '9'))
        {
            isValid = false;
        }
        if (!isValid)
        {
            if (!printed)
            {
                cout << "\nIncorrect format. Please use 00:00:00 format." << endl;
                cout << "\nEnter Departure Time:" << endl;
                printed = true;
                cin.clear();
            }
            counter = 0;
            isValid = true;
            data = "";
            continue;
        }
        data += time;
        if (counter == 7)
        {
            break;
        }
         if (isValid && counter == 8)
        {
            break;
        }
        counter++;
     
    }
}

void editFlight()
{
    string filename = "Flights Record.txt";
    string id;
    cout << "Enter Flight ID of the flight you want to edit: ";
    cin >> id;
    ifstream fin;
    fin.open(filename);
    try
    {
        if (fin.fail())
        {
            throw runtime_error("Error opening file");
        }
    }
    catch (runtime_error &e)
    {
        cout << e.what();
    }
    ofstream fout;
    fout.open("temp.txt");
    string line;
    bool deleted = false;
    while (getline(fin, line))
    {
        if (line.find(id) != line.npos)
        {
            deleted = true;
            addFlight();
            continue;
        }
        fout << line << endl;
    }
    fin.close();
    fout.close();

    if (deleted)
    {
        if (remove(filename.c_str()) != 0)
        {
            cout << "Error removing the original file." << endl;
        }
        if (rename("temp.txt", filename.c_str()) != 0)
        {
            cout << "Error renaming temporary file." << endl;
        }
        cout << "Flight number " << id << " has been edited in the file." << endl;
    }
    else
    {
        cout << "No matching record found with Flight ID " << id << "." << endl;
    }
}
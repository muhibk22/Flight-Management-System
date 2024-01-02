#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;

struct passenger
{
    string passengerId;
    string name;
    string nationality;
    int age;
};

void addPassenger(passenger *passengers, int &currentIndex, int maxRecords);
void viewPassenger(const passenger *passengers, int currentIndex);
void checkPassenger(const passenger *passengers, int currentIndex);
void editPassenger(passenger *passengers, int currentIndex);
void deletePassenger(passenger *passengers, int &currentIndex, int maxRecords);
void readPassengerFile(passenger *passengers, int &currentIndex, int maxRecords);
void writePassengerFile(passenger *passengers, int currentIndex);

void passengerRecord()
{
    const int maxRecords = 300;
    passenger *passengers = new passenger[maxRecords];
    int currentIndex = 0;
    readPassengerFile(passengers, currentIndex, maxRecords);

    while (currentIndex < maxRecords)
    {
        cout << "\n1. Add Passenger \n2. View Passenger \n3. Check Passenger \n4. Edit Passenger Record \n5. Delete Passenger Record \n6. Back" << endl;

        cout << "\nEnter the option: ";
        int option;
        cin >> option;

        switch (option)
        {
        case 1:
            cout << "--------------------------------------------------------------------------" << endl
                 << "\t\t\t    ADD A NEW PASSENGER \n--------------------------------------------------------------------------" << endl;
            addPassenger(passengers, currentIndex, maxRecords);
            break;

        case 2:
            cout << "Passenger Record: " << endl;
            viewPassenger(passengers, currentIndex);
            break;

        case 3:
            cout << "--------------------------------------------------------------------------" << endl
                 << "\t\t\tCHECK EXISTING PASSENGER \n--------------------------------------------------------------------------" << endl;
            checkPassenger(passengers, currentIndex);
            break;

        case 4:
            cout << "--------------------------------------------------------------------------" << endl
                 << "\t\t\tEDIT A PASSENGER RECORD \n--------------------------------------------------------------------------" << endl;
            editPassenger(passengers, currentIndex);
            break;

        case 5:
            cout << "--------------------------------------------------------------------------" << endl
                 << "\t\t\tDELETE A PASSENGER RECORD \n--------------------------------------------------------------------------" << endl;
            deletePassenger(passengers, currentIndex, maxRecords);
            break;

        case 6:
            cout << "\nExiting Passenger Record Menu" << endl;
            writePassengerFile(passengers, currentIndex);
            return;

        default:
            cout << "Invalid Option!\n";
            break;
        }
    }
    writePassengerFile(passengers, currentIndex);
}

void addPassenger(passenger *passengers, int &currentIndex, int maxRecords)
{
    if (currentIndex < maxRecords)
    {
        cout << "Enter Passenger ID: ";
        cin >> passengers[currentIndex].passengerId;
        cout << "Enter Passenger Name: ";
        cin >> passengers[currentIndex].name;
        cout << "Enter Passenger Nationality: ";
        cin >> passengers[currentIndex].nationality;
        cout << "Enter Passenger Age: ";
        cin >> passengers[currentIndex].age;

        currentIndex++;
    }
    else
    {
        cout << "Maximum Records Reached";
    }
}

void viewPassenger(const passenger *passengers, int currentIndex)
{
    cout << "----------------------------------------------------------------------" << setw(20) << left << "\nID" << setw(20) << left << " Name" << setw(20) << left << " Nationality" << setw(15) << left << " Age" << endl
         << "----------------------------------------------------------------------" << endl
         << endl;

    for (int i = 0; i < currentIndex; i++)
    {
        cout << setw(20) << left << passengers[i].passengerId << setw(20) << left << passengers[i].name
             << setw(20) << left << passengers[i].nationality << setw(15) << left << passengers[i].age << endl;
    }

    cout << "----------------------------------------------------------------------" << endl;
}

void checkPassenger(const passenger *passengers, int currentIndex)
{
    string passengerCheck;
    cout << "Enter the Passenger ID you want to check: " << endl;
    cin >> passengerCheck;
    bool exists = false;
    int i = 0;
    for (i = 0; i < currentIndex; i++)
    {
        if (passengerCheck == passengers[i].passengerId)
        {
            exists = true;
            break;
        }
    }
    if (exists)
    {
        cout << "Passenger with ID: " << passengerCheck << " exists in record: \n"
             << endl;
        cout << setw(20) << left << passengers[i].passengerId << setw(20) << left << passengers[i].name << setw(20) << left << passengers[i].nationality << setw(15) << left << passengers[i].age << "\n"
             << endl;
    }
    else
    {
        cout << "Passenger with ID: " << passengerCheck << " does not exist in record.\n"
             << endl;
    }
}

void editPassenger(passenger *passengers, int currentIndex)
{
    string passengerCheck;
    cout << "Enter the Passenger ID you want to edit: " << endl;
    cin >> passengerCheck;
    bool edited = false;
    int i = 0;
    for (i = 0; i < currentIndex; i++)
    {
        if (passengerCheck == passengers[i].passengerId)
        {
            edited = true;
            break;
        }
    }
    if (edited)
    {
        cout << "Enter Passenger ID: ";
        cin >> passengers[i].passengerId;
        cout << "Enter Passenger Name: ";
        cin >> passengers[i].name;
        cout << "Enter Passenger Nationality: ";
        cin >> passengers[i].nationality;
        cout << "Enter Passenger Age: ";
        cin >> passengers[i].age;
        cout << "Passenger Record Successfully edited" << endl;
    }
    else
    {
        cout << "Passenger with ID: " << passengerCheck << " does not exist in record.\n"
             << endl;
    }
}

void deletePassenger(passenger *passengers, int &currentIndex, int maxRecords)
{
    string passengerCheck;
    bool deleted = false;
    cout << "Enter the Passenger ID you want to delete: ";
    cin >> passengerCheck;

    for (int i = 0; i < currentIndex; i++)
    {
        if (passengerCheck == passengers[i].passengerId)
        {
            deleted = true;
            for (int j = i; j < currentIndex - 1; j++)
            {
                passengers[j] = passengers[j + 1];
            }
        }
    }

    if (deleted)
    {
        currentIndex--;
        cout << "Passenger with ID: " << passengerCheck << " successfully deleted from records. " << endl;
    }
    else
    {
        cout << "Failed to delete Passenger with ID: " << passengerCheck << ". " << endl;
    }
}

void readPassengerFile(passenger *passengers, int &currentIndex, int maxRecords)
{
    ifstream fin;
    fin.open("Passengers.txt");
    try
    {
        if (fin.fail())
            throw runtime_error("Error opening File. Please create file 'Passengers.txt' and try again. ");
    }
    catch (runtime_error &e)
    {
        cout << e.what() << endl;
        return;
    }
    while (!fin.eof())
    {
        fin >> passengers[currentIndex].passengerId >> passengers[currentIndex].name >> passengers[currentIndex].nationality >> passengers[currentIndex].age;
        if (!fin.eof())
        {
            currentIndex++;
        }
    }
    fin.close();
}

void writePassengerFile(passenger *passengers, int currentIndex)
{
    ofstream fout;
    fout.open("Passengers.txt");
    try
    {
        if (fout.fail())
            throw runtime_error("Error creating file 'Passengers.txt'");
    }
    catch (runtime_error &e)
    {
        cout << e.what() << endl;
        return;
    }
    for (int i = 0; i < currentIndex; i++)
    {
        fout << setw(20) << left << passengers[i].passengerId << setw(20) << left << passengers[i].name
             << setw(20) << left << passengers[i].nationality << setw(15) << left << passengers[i].age << endl;
    }
    fout.close();
}
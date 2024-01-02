#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;
const int attributes = 4;

void menu(string **passengers, int &currentIndex, int maxRecords);
void addPassenger(string **passengers, int &currentIndex, int maxRecords);
void viewPassenger(string **passengers, int currentIndex);
void checkPassenger(string **passengers, int currentIndex);
void delPassenger(string **passengers, int &currentIndex);
void editPassenger(string **passengers, int currentIndex);
void readFile(string **passengers, int &currentIndex, int maxRecords);
void writeFile(string **passengers, int currentIndex);
int main()
{
    cout << "--------------------------------------------------------------------------" << endl
         << "\t\t\tPASSANGER DETAILS\n--------------------------------------------------------------------------" << endl;

    const int maxRecords = 500;
    string **passengers;
    passengers = new string *[maxRecords];
    for (int i = 0; i < maxRecords; i++)
    {
        passengers[i] = new string[attributes];
    }
    int currentIndex = 0;
    readFile(passengers, currentIndex, maxRecords);
    while (true)
    {
        menu(passengers, currentIndex, maxRecords);
    }
    writeFile(passengers, currentIndex);
    return 0;
}

void menu(string **passengers, int &currentIndex, int maxRecords)
{
    cout << "1. Add Passenger \n2. View Passenger \n3. Check Passengers \n4. Delete Passenger Record \n5. Edit Passenger Record \n6. Exit" << endl;
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
        cout << "Passengers Record: " << endl;
        viewPassenger(passengers, currentIndex);
        break;
    case 3:
        cout << "--------------------------------------------------------------------------" << endl
             << "\t\t\tCHECK EXISTING PASSENGERS \n--------------------------------------------------------------------------" << endl;
        checkPassenger(passengers, currentIndex);
        break;
    case 4:
        cout << "--------------------------------------------------------------------------" << endl
             << "\t\t\tDELETE A PASSENGER RECORD \n--------------------------------------------------------------------------" << endl;
        delPassenger(passengers, currentIndex);
        break;
    case 5:
        cout << "--------------------------------------------------------------------------" << endl
             << "\t\t\tEDIT A PASSENGER RECORD \n--------------------------------------------------------------------------" << endl;
        editPassenger(passengers, currentIndex);
        break;

    case 6:
        writeFile(passengers, currentIndex);
        cout << "\nProgram Terminated.";
        exit(0);

    default:
        cout << "Invalid Option!\n";
    }
}

void addPassenger(string **passengers, int &currentIndex, int maxRecords)
{
    string passportID, name, nationality, age;
    cout << "Enter Passenger's Passport ID: " << endl;
    cin >> passportID;
    cout << "Enter Passenger's Name: " << endl;
    cin >> name;
    cout << "Enter Passenger's Nationality: " << endl;
    cin >> nationality;
    do
    {
        cout << "Enter Passenger's Age: " << endl;
        cin >> age;
        if (!isdigit(age[0]))
        {
            cout << "Please enter a number for age, try again. " << endl;
        }
    } while (!isdigit(age[0]) || !isdigit(age[1]));

    if (currentIndex < maxRecords)
    {
        passengers[currentIndex][0] = passportID;
        passengers[currentIndex][1] = name;
        passengers[currentIndex][2] = nationality;
        passengers[currentIndex][3] = age;

        currentIndex++;
    }
    else
    {
        cout << "Maximum numbers of Passengers reached! ";
    }
}

void viewPassenger(string **passengers, int currentIndex)
{
    cout << "----------------------------------------------------------------------" << setw(20) << left << "\nPassport ID" << setw(20) << left << " Name" << setw(20) << left << " Nationality" << setw(15) << left << " Age" << endl
         << "----------------------------------------------------------------------" << endl
         << endl;

    for (int i = 0; i < currentIndex; ++i)
    {
        cout << setw(20) << left << passengers[i][0] << setw(20) << left << passengers[i][1] << setw(20) << left << passengers[i][2] << setw(15) << left << passengers[i][3] << endl;
    }

    cout << "----------------------------------------------------------------------" << endl;
}

void checkPassenger(string **passengers, int currentIndex)
{
    string passportCheck;
    int index;
    cout << "Enter the Passport ID of the passenger you want to check: " << endl;
    cin >> passportCheck;
    bool exists = false;
    for (int i = 0; i < currentIndex; i++)
    {
        if (passportCheck == passengers[i][0])
        {
            exists = true;
            index = i;
            break;
        }
    }
    if (exists)
    {
        cout << "Passenger with Passport ID: " << passportCheck << " exists in record: \n"
             << endl;
        cout << setw(20) << left << passengers[index][0] << setw(20) << left << passengers[index][1] << setw(20) << left << passengers[index][2] << setw(15) << left << passengers[index][3] << "\n"
             << endl;
    }
    else
    {
        cout << "Passenger with Passport ID: " << passportCheck << " does not exist in record.\n"
             << endl;
    }
}

void delPassenger(string **passengers, int &currentIndex)
{
    string passportCheck;
    bool deleted = false;
    cout << "Enter the Passport ID of the passenger you want to delete: ";
    cin >> passportCheck;
    for (int i = 0; i < currentIndex; i++)
    {
        if (passportCheck == passengers[i][0])
        {
            deleted = true;
            for (int j = i; j < currentIndex - 1; j++)
            {
                for (int k = 0; k < attributes; k++)
                {
                    passengers[j][k] = passengers[j + 1][k];
                }
            }

            currentIndex--;
            break;
        }
    }
    if (deleted)
    {
        cout << "Passenger with Passport ID: " << passportCheck << " successfully deleted from records. " << endl;
    }
    else
    {
        cout << "Failed to delete passenger with Passport ID: " << passportCheck << ". " << endl;
    }
}

void editPassenger(string **passengers, int currentIndex)
{
    string passportCheck;
    cout << "Enter the Passport ID of passenger you want to edit: " << endl;
    cin >> passportCheck;
    bool edited = false;
    for (int i = 0; i < currentIndex; i++)
    {
        if (passportCheck == passengers[i][0])
        {
            string passportID, name, nationality, age;
            cout << "Enter Passenger's Passport ID: " << endl;
            cin >> passportID;
            cout << "Enter Passenger's Name: " << endl;
            cin >> name;
            cout << "Enter Passenger's Nationality: " << endl;
            cin >> nationality;
            do
            {
                cout << "Enter Passenger's Age: " << endl;
                cin >> age;
                if (!isdigit(age[0]))
                {
                    cout << "Please enter a number for age, try again. " << endl;
                }
            } while (!isdigit(age[0]) || !isdigit(age[1]));

            passengers[i][0] = passportID;
            passengers[i][1] = name;
            passengers[i][2] = nationality;
            passengers[i][3] = age;
            edited = true;
            break;
        }
    }
    if (edited)
    {
        cout << "Record of Passenger with Passport ID: " << passportCheck << " successfully edited. " << endl;
    }
    else
    {
        cout << "Failed to edit record of the Passenger! " << endl;
    }
}

void readFile(string **passengers, int &currentIndex, int maxRecords)
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
    while (currentIndex < maxRecords && fin >> passengers[currentIndex][0] >> passengers[currentIndex][1] >> passengers[currentIndex][2] >> passengers[currentIndex][3])
    {
        currentIndex++;
    }
    fin.close();
}
void writeFile(string **passengers, int currentIndex)
{
    ofstream fout;
    fout.open("Passengers.txt");
    for (int i = 0; i < currentIndex; i++)
    {
        fout << passengers[i][0] << " " << passengers[i][1] << " " << passengers[i][2] << " " << passengers[i][3] << endl;
    }
    fout.close();
}
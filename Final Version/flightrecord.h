#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;

struct flight
{
    string flightId;
    string departure;
    string arrival;
    string time;
};

void addFlight(flight *flights, int &currentIndex, int maxRecords);
void viewFlight(const flight *flights, int currentIndex);
void checkFlight(const flight *flights, int currentIndex);
void editFlight(flight *flights, int currentIndex);
void delFlight(flight *flights, int &currentIndex, int maxRecords);
void readFlightFile(flight *flights, int &currentIndex, int maxRecords);
void writeFlightFile(flight *flights, int currentIndex);
bool isValidFlightIdFormat(const string &flightId);
bool isValidTimeFormat(const string &time);

void flightRecord()
{
    const int maxRecords = 100;
    flight *flights = new flight[maxRecords];
    int currentIndex = 0;
    readFlightFile(flights, currentIndex, maxRecords);
    while (currentIndex < maxRecords)
    {

        cout << "\n1. Add Flight \n2. View Flight \n3. Check Flight \n4. Edit Flight Record \n5. Delete Flight Record  \n6. Back" << endl;
        cout << "\nEnter the option: ";
        int option;
        cin >> option;  // To take input from the user and store it in the 'option' variable
        switch (option) // using a switch statement to display menu to the user
        {
        case 1: // The case that would run if the user's input was 1
            cout << "--------------------------------------------------------------------------" << endl
                 << "\t\t\t    ADD A NEW FLIGHT \n--------------------------------------------------------------------------" << endl; // To print out the message
            addFlight(flights, currentIndex, maxRecords);                                                                              // Calling the addFlight function
            break;                                                                                                                     // To exit the switch and prevent the execution of other cases
        case 2:                                                                                                                        // The case that would run if the user's input was 2
            cout << "Flight Record: " << endl;                                                                                         // To print out the message i.e. flight record
            viewFlight(flights, currentIndex);                                                                                         // Calling the viewFlight function
            break;                                                                                                                     // To exit the switch and prevent the execution of other cases
        case 3:                                                                                                                        // The case that would run if the user's input was 3
            cout << "--------------------------------------------------------------------------" << endl
                 << "\t\t\tCHECK EXISTING FLIGHT \n--------------------------------------------------------------------------" << endl; // To print out the message for the user
            checkFlight(flights, currentIndex);                                                                                         // Calling the checkFlight function
            break;                                                                                                                      // To exit the switch and prevent the execution of other cases
        case 4:
            cout << "--------------------------------------------------------------------------" << endl
                 << "\t\t\tEDIT A FLIGHT RECORD \n--------------------------------------------------------------------------" << endl;
            editFlight(flights, currentIndex); // Calling the editFlight function
            break;                             // To exit the switch and prevent the execution of other cases
        case 5:
            cout << "--------------------------------------------------------------------------" << endl
                 << "\t\t\tDELETE A FLIGHT RECORD \n--------------------------------------------------------------------------" << endl;
            delFlight(flights, currentIndex, maxRecords); // Calling the delFlight function
            break;                                        // To exit the switch and prevent the execution of other cases
        case 6:
            cout << "\nGoing Back To Menu" << endl; // To print out the termination message
            writeFlightFile(flights, currentIndex);
            return; // To go back to main menu
        default:
            cout << "Invalid Option!\n"; // To print out a message for an invalid option
        }
    }
    writeFlightFile(flights, currentIndex);
}

void addFlight(flight *flights, int &currentIndex, int maxRecords)
{
    if (currentIndex < maxRecords)
    {
        do
        {
            cout << "Enter flight ID: ";
            cin >> flights[currentIndex].flightId;

            if (!isValidFlightIdFormat(flights[currentIndex].flightId))
            {
                cout << "Invalid flight ID format. Please enter in the format xx-0000." << endl;
            }
            else
            {
                break;
            }
        } while (true);
        cout << "Enter flight Departure Place: ";
        cin >> flights[currentIndex].departure;
        cout << "Enter Flight Arrival Place: ";
        cin >> flights[currentIndex].arrival;
        do
        {
            cout << "Enter Flight Departure Time: ";
            cin >> flights[currentIndex].time;

            if (!isValidTimeFormat(flights[currentIndex].time))
            {
                cout << "Invalid time format. Please enter in the format 00:00:00." << endl;
            }
            else
            {
                break;
            }
        } while (true);

        currentIndex++;
    }
    else
    {
        cout << "Maximum Records Reached";
    }
}

void viewFlight(const flight *flights, int currentIndex)
{
    cout << "----------------------------------------------------------------------" << setw(20) << left << "\nID" << setw(20) << left << " Departure" << setw(20) << left << " Arrival" << setw(15) << left << " Time" << endl
         << "----------------------------------------------------------------------" << endl
         << endl;

    for (int i = 0; i < currentIndex; i++)
    {
        cout << setw(20) << left << flights[i].flightId << setw(20) << left << flights[i].departure
             << setw(20) << left << flights[i].arrival << setw(15) << left << flights[i].time << endl;
    }

    cout << "----------------------------------------------------------------------" << endl;
}

void checkFlight(const flight *flights, int currentIndex)
{
    string flightCheck;
    cout << "Enter the Flight ID of the passenger you want to check: " << endl;
    cin >> flightCheck;
    bool exists = false;
    int i = 0;
    for (i = 0; i < currentIndex; i++)
    {
        if (flightCheck == flights[i].flightId)
        {
            exists = true;
            break;
        }
    }
    if (exists)
    {
        cout << "Flight with Flight ID: " << flightCheck << " exists in record: \n"
             << endl;
        cout << setw(20) << left << flights[i].flightId << setw(20) << left << flights[i].departure << setw(20) << left << flights[i].arrival << setw(15) << left << flights[i].time << "\n"
             << endl;
    }
    else
    {
        cout << "Flight with Flight ID: " << flightCheck << " does not exist in record.\n"
             << endl;
    }
}

void editFlight(flight *flights, int currentIndex)
{
    string flightCheck;
    cout << "Enter the Flight ID of the passenger you want to edit: " << endl;
    cin >> flightCheck;
    bool edited = false;
    int i = 0;
    for (i = 0; i < currentIndex; i++)
    {
        if (flightCheck == flights[i].flightId)
        {
            edited = true;
            break;
        }
    }
    if (edited)
    {
        cout << "Enter flight ID: ";
        cin >> flights[i].flightId;
        cout << "Enter flight Departure Place: ";
        cin >> flights[i].departure;
        cout << "Enter Flight Arrival Place: ";
        cin >> flights[i].arrival;
        cout << "Enter Flight Departure Time: ";
        cin >> flights[i].time;
        cout << "Flight Record Successfully edited" << endl;
    }
    else
    {
        cout << "Flight with Flight ID: " << flightCheck << " does not exist in record.\n"
             << endl;
    }
}

void delFlight(flight *flights, int &currentIndex, int maxRecords)
{
    string flightCheck;
    bool deleted = false;
    cout << "Enter the Flight ID of the flight you want to delete: ";
    cin >> flightCheck;
    for (int i = 0; i < currentIndex; i++)
    {
        if (flightCheck == flights[i].flightId)
            deleted = true;
        {
            for (int j = i; j < maxRecords - 1; j++)
            {
                flights[i] = flights[i + 1];
            }
        }
        currentIndex--;
        break;
    }
    if (deleted)
    {
        cout << "Flight with Flight ID: " << flightCheck << " successfully deleted from records. " << endl;
    }
    else
    {
        cout << "Failed to delete Flight with Flight ID: " << flightCheck << ". " << endl;
    }
}

void readFlightFile(flight *flights, int &currentIndex, int maxRecords)
{
    ifstream fin;
    fin.open("Flights.txt");
    try
    {
        if (fin.fail())
            throw runtime_error("Error opening File. Please create file 'Flights.txt' and try again. ");
    }
    catch (runtime_error &e)
    {
        cout << e.what() << endl;
        return;
    }
    while (!fin.eof())
    {
        fin >> flights[currentIndex].flightId >> flights[currentIndex].departure >> flights[currentIndex].arrival >> flights[currentIndex].time;
        if (!fin.eof())
        {
            currentIndex++;
        }
    }
    fin.close();
}

void writeFlightFile(flight *flights, int currentIndex)
{
    ofstream fout;
    fout.open("Flights.txt");
    try
    {
        if (fout.fail())
            throw runtime_error("Error creating file 'Flights.txt'");
    }
    catch (runtime_error &e)
    {
        cout << e.what() << endl;
        return;
    }
    for (int i = 0; i < currentIndex; i++)
    {
        fout << setw(20) << left << flights[i].flightId << setw(20) << left << flights[i].departure << setw(20) << left << flights[i].arrival << setw(15) << left << flights[i].time << endl;
    }
    fout.close();
}

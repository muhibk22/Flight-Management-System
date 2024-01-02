#include "flightrecord.h"
#include "passengerrecord.h"

using namespace std;

struct seat
{
    string passengerId;
    string flightId;
    int seatNo;
};

void reserveSeat(seat *seats, int &seatIndex, flight *flights, int flightIndex, passenger *passengers, int passengerIndex, int maxSeats);
bool isPassengerValid(const passenger *passengers, int passengerIndex, const string passengerId);
bool isFlightValid(flight *flights, int flightIndex, const string flightId);
bool isSeatReserved(seat *seats, int seatIndex, string flightId, int seatNo);
void viewReservations(const seat *seats, int seatIndex);
void readSeatFile(seat *seats, int &seatIndex, int maxSeats);
void writeSeatFile(seat *seats, int seatIndex);

void seatReservation()
{
    const int maxFlights = 100;
    int flightIndex = 0;
    flight *flights = new flight[maxFlights];
    readFlightFile(flights, flightIndex, maxFlights);

    const int maxPassengers = 100;
    int passengerIndex = 0;
    passenger *passengers = new passenger[maxPassengers];
    readPassengerFile(passengers, passengerIndex, maxPassengers);

    const int maxSeats = 100;
    int seatIndex = 0;
    seat *seats = new seat[maxSeats];
    readSeatFile(seats, seatIndex, maxSeats);

    while (seatIndex < maxSeats)
    {
        cout << "1. Reserve Seat \n2. View Reservations \n3. Back" << endl;
        cout << "\nEnter the option: ";
        int option;
        cin >> option;

        switch (option)
        {
        case 1:
            cout << "--------------------------------------------------------------------------" << endl
                 << "\t\t\t    RESERVE A SEAT\n--------------------------------------------------------------------------" << endl;
            reserveSeat(seats, seatIndex, flights, flightIndex, passengers, passengerIndex, maxSeats);
            break;
        case 2:
            cout << "--------------------------------------------------------------------------" << endl
                 << "\t\t\tVIEW RESERVATIONS\n--------------------------------------------------------------------------" << endl;
            viewReservations(seats, seatIndex);
            break;
        case 3:
            cout << "\nGoing Back To Menu" << endl;
            writeSeatFile(seats, seatIndex);
            return;
            break;
        default:
            cout << "Invalid Option!\n";
        }
    }
    cout << "Maximum Seat Records Reached" << endl;

    writeSeatFile(seats, seatIndex);
}

void reserveSeat(seat *seats, int &seatIndex, flight *flights, int flightIndex, passenger *passengers, int passengerIndex, int maxSeats)
{
    if (seatIndex < maxSeats)
    {
        string passengerId;
        cout << "\nEnter Passenger ID: ";
        cin >> passengerId;
        if (isPassengerValid(passengers, passengerIndex, passengerId))
        {
            string flightId;
            cout << "\nEnter Flight ID: ";
            cin >> flightId;
            if (isFlightValid(flights, flightIndex, flightId))
            {
                int seatNo;
                cout << "\nEnter Seat Number: ";
                cin >> seatNo;
                if (!isSeatReserved(seats, seatIndex, flightId, seatNo))
                {
                    seats[seatIndex].passengerId = passengerId;
                    seats[seatIndex].flightId = flightId;
                    seats[seatIndex].seatNo = seatNo;
                    seatIndex++;
                    cout << "\nSeat Number: " << seatNo << " allotted to Passenger: " << passengerId << " on Flight Number: " << flightId << " successfully" << endl;
                }
                else
                {
                    cout << "\nSeat Number: " << seatNo << " in Flight Number: " << flightId << " is already reserved." << endl;
                }
            }
            else
            {
                cout << "\nFlight with Flight ID: " << flightId << " does not exist." << endl;
            }
        }
        else
        {
            cout << "\nPassenger with Passenger ID: " << passengerId << " does not exist." << endl;
        }
    }
    else
    {
        cout << "\nMaximum Seats Reached. " << endl;
    }
}

bool isPassengerValid(const passenger *passengers, int passengerIndex, const string passengerId)
{
    for (int i = 0; i < passengerIndex; i++)
    {
        if (passengers[i].passengerId == passengerId)
        {
            return true;
        }
    }

    return false;
}

bool isFlightValid(flight *flights, int flightIndex, const string flightId)
{
    for (int i = 0; i < flightIndex; i++)
    {
        if (flights[i].flightId == flightId)
        {
            return true;
        }
    }
    return false;
}

bool isSeatReserved(seat *seats, int seatIndex, string flightId, int seatNo)
{
    for (int i = 0; i < seatIndex; i++)
    {
        if (seats[i].seatNo == seatNo && seats[i].flightId == flightId)
        {
            return true;
        }
    }
    return false;
}

void viewReservations(const seat *seats, int seatIndex)
{
    cout << "--------------------------------------------------------------------------" << endl
         << setw(30) << left << "Passenger ID" << setw(30) << left << "Flight ID"
         << "Seat Number" << endl
         << "--------------------------------------------------------------------------" << endl
         << endl;

    for (int i = 0; i < seatIndex; i++)
    {
        cout << setw(30) << left << seats[i].passengerId << setw(30) << left << seats[i].flightId << seats[i].seatNo << endl;
    }

    cout << "--------------------------------------------------------------------------" << endl;
}

void readSeatFile(seat *seats, int &seatIndex, int maxSeats)
{
    ifstream fin("Seats.txt");
    try
    {
        if (fin.fail())
        {
            throw runtime_error("Failed to open 'Seats.txt'.\n");
        }
    }
    catch (runtime_error &e)
    {
        cout << e.what() << endl;
        return;
    }

    while (!fin.eof())
    {
        fin >> seats[seatIndex].passengerId >> seats[seatIndex].flightId >> seats[seatIndex].seatNo;
        if (!fin.eof())
        {
            seatIndex++;
        }
    }

    fin.close();
}

void writeSeatFile(seat *seats, int seatIndex)
{
    ofstream fout("Seats.txt");
    try
    {
        if (fout.fail())
        {
            throw runtime_error("Failed to open/create file 'Seats.txt' \n");
        }
    }
    catch (runtime_error &e)
    {
        cout << e.what() << endl;
        return;
    }

    for (int i = 0; i < seatIndex; i++)
    {
        fout << setw(20) << left << seats[i].passengerId << setw(30) << left << seats[i].flightId << setw(15) << left << seats[i].seatNo << endl;
    }
    fout.close();
}

bool isValidFlightIdFormat(const string &flightId)
{
    if (flightId.length() != 7 || !isalpha(flightId[0]) || !isalpha(flightId[1]) ||
        flightId[2] != '-' || !isdigit(flightId[3]) || !isdigit(flightId[4]) ||
        !isdigit(flightId[5]) || !isdigit(flightId[6]))
    {
        return false;
    }
    return true;
}

bool isValidTimeFormat(const string &time)
{
    if (time.length() != 8 || !isdigit(time[0]) || !isdigit(time[1]) ||
        time[2] != ':' || !isdigit(time[3]) || !isdigit(time[4]) ||
        time[5] != ':' || !isdigit(time[6]) || !isdigit(time[7]))
    {
        return false;
    }
    return true;
}

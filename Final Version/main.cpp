#include "seatreservation.h"  

using namespace std;

int main()
{
    int option;
    while (true)
    {
        cout << "--------------------------------------------------------------------------" << endl
             << "\t\t\tFLIGHT MANAGEMENT SYSTEM\n--------------------------------------------------------------------------" << endl;
        cout << "1. Flights Record \n2. Passengers Record \n3. Seat Reservation \n4. Exit \n"
             << endl;
        cout << "\nEnter your option: ";
        cin >> option;
        switch (option)
        {
        case 1:
            cout << "\n--------------------------------------------------------------------------" << endl // To print out text
                 << "\t\t\t      FLIGHTS RECORD\n--------------------------------------------------------------------------" << endl;
            flightRecord(); // calling the flightRecord function
            break;
        case 2:
            cout << "\n--------------------------------------------------------------------------" << endl // To print out text
                 << "\t\t\t    PASSENGERS RECORD\n--------------------------------------------------------------------------" << endl;
            passengerRecord(); // calling the passengerRecord function
            break;
        case 3:
            cout << "\n--------------------------------------------------------------------------" << endl // To print out text
                 << "\t\t\t      SEAT RESERVATION\n--------------------------------------------------------------------------" << endl;
            seatReservation();  //calling the seatResrvation function
            break;
        case 4:
            cout << "Program Terminated!";
            exit(0);

        default:
            cout << "Invalid Option!";
            break;
        }
    }
    return 0;
}
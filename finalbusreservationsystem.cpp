#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
ofstream out("passenger_receipt.txt");
void printLine(char ch, int len = 60)
{
    cout << string(len, ch) << endl;
}
void printline(char ch, int len = 30)
{
    cout << string(len, ch);
}
void printLine1(char ch, int len = 60)
{
    out << string(len, ch) << endl;
}
void printline1(char ch, int len = 30)
{
    out << string(len, ch);
}
int seats[30] = {0};

void displaySeatMap()
{
    printLine('-');
    cout << "SEAT MAP: [O] = Available  [X] = Booked" << endl;
    printLine('-');
    for (int i = 0; i < 30; i++)
    {
        if (seats[i] == 0)
        {
            cout << "[O]";
        }
        else
        {
            cout << "[X]";
        }
        if (i + 1 < 10)
            cout << "0";
        cout << i + 1 << "  ";
        if ((i + 1) % 6 == 0)
            cout << endl;
    }
    cout << endl;
    printLine('-');
}

class Passenger
{
protected:
    string name, gmail, phone_number;
    int age, no_of_passengers;
    char gender;
    vector<int> bookedSeats;

public:
    void input()
    {
        cout << "Enter Your Name: ";
        getline(cin, name);

        cout << "Enter Your Age: ";
        cin >> age;

        cout << "Enter Your Gender(M/F/OTHERS): ";
        cin >> gender;

        cout << "Enter Your Phone Number: +91 ";
        cin >> phone_number;

        cout << "Enter The No Of Passengers To Travel: ";
        cin >> no_of_passengers;
        cin.ignore();

        cout << "Enter Your Gmail ID: ";
        getline(cin, gmail);
    }

    bool selectSeats()
    {
        displaySeatMap();
        cout << "Select " << no_of_passengers << " seat(s):" << endl;
        for (int i = 0; i < no_of_passengers; i++)
        {
            int seatNo;
            cout << "Enter Seat No for Passenger " << i + 1 << " (1-30): ";
            cin >> seatNo;

            if (seatNo < 1 || seatNo > 30)
            {
                cout << "Invalid seat number. Booking cancelled." << endl;
                return false;
            }
            if (seats[seatNo - 1] == 1)
            {
                cout << "Seat " << seatNo << " is already booked! Booking cancelled." << endl;
                return false;
            }
            for (int s : bookedSeats)
            {
                if (s == seatNo)
                {
                    cout << "You already selected seat " << seatNo << ". Booking cancelled." << endl;
                    return false;
                }
            }
            bookedSeats.push_back(seatNo);
        }
        for (int s : bookedSeats)
            seats[s - 1] = 1;
        cin.ignore();
        return true;
    }

    void display()
    {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Gender: " << gender << endl;
        cout << "Phone: +91 " << phone_number << endl;
        cout << "Passengers: " << no_of_passengers << endl;
        cout << "Gmail: " << gmail << endl;
        cout << "Seats: ";
        for (int s = 0; s <= bookedSeats.size(); s++)
        {
            out << bookedSeats[s] << " ";
        }
        cout << endl;
    }

    void receipt()
    {
        printLine1('=');
        out << "--------------PASSENGER DETAILS---------------" << endl;
        printLine1('=');
        out << "Name: " << name << endl;
        out << "Age: " << age << endl;
        out << "Gender: " << gender << endl;
        out << "Phone Number: +91 " << phone_number << endl;
        out << "No Of Passengers: " << no_of_passengers << endl;
        out << "Gmail Id: " << gmail << endl;
        out << "Booked Seats: ";
        for (int s = 0; s <= bookedSeats.size(); s++)
        {
            out << bookedSeats[s] << " ";
        }
        out << endl;
        out.close();
        cout << "Receipt saved as passenger_receipt.txt" << endl;
    }
};

class Bus
{
protected:
    string boarding_station, destination_station,time;
    vector<Passenger> p;

public:
    void step1()
    {
        cout << "Enter the Boarding Station: ";
        cin >> boarding_station;
        cout << "Enter the Destination: ";
        cin >> destination_station;
        cin.ignore();
    }

    void admin_input()
    {
        cout << "Enter Boarding Station: ";
        cin >> boarding_station;
        cout << "Enter Destination: ";
        cin >> destination_station;
        cin.ignore();
        cout << "Enter Departure Time: ";
        getline(cin,time);
        
    }

    void display()
    {
        cout << "Route: " << boarding_station << " --> " << destination_station << endl;
        cout << "Time : " << time << endl;
    }
};

void passengerPortal(vector<Passenger> &p, vector<Bus> &c)
{
    printLine('=');
    printline('-', 26);
    cout << "PASSENGER MENU";
    printLine('-', 30);
    printLine('=');
    cout << "1. Book A Bus Seat" << endl;
    cout << "2. Check Status" << endl;
    cout << "3. Print / Download Bus Ticket" << endl;
    cout << "4. Back" << endl;

    int choice;
    cout << "Enter Your Choice: ";
    cin >> choice;
    cin.ignore();

    if (choice == 1)
    {
        if (c.empty())
        {
            cout << "No buses available at the moment. Please try again later." << endl;
            return;
        }
        printLine('-');
        cout << "---- AVAILABLE BUSES ----" << endl;
        printLine('-');
        for (int i = 0; i < (int)c.size(); i++)
        {
            cout << "\nBus " << i + 1 << ":" << endl;
            c[i].display();
        }
        printLine('-');
int busChoice;
cout << "Enter Bus Number To Book: ";
cin >> busChoice;
cin.ignore();
if (busChoice < 1 || busChoice > (int)c.size())
{
    cout << "Invalid bus number." << endl;
    return;
}
Passenger p1;
p1.input();
if (!p1.selectSeats())
{
    return;
}
p1.receipt();
p.push_back(p1);
cout << "\nBooking Successful!" << endl;
}
else if (choice == 2)
    {
        if (p.empty())
        {
            cout << "No bookings found." << endl;
        }
        else
        {
            printLine('-');
            cout << "---- ALL BOOKINGS ----" << endl;
            printLine('-');
            for (int i = 0; i < (int)p.size(); i++)
            {
                cout << "\nPassenger " << i + 1 << ":" << endl;
                p[i].display();
                printLine('-');
            }
        }
    }
    else if (choice == 3)
    {
        if (p.empty())
        {
            cout << "No bookings to print." << endl;
        }
        else
        {
            p[p.size() - 1].receipt();
        }
    }
    else if (choice == 4)
    {
        cout << "Going back..." << endl;
    }
    else
    {
        cout << "Invalid choice." << endl;
    }
}

void adminPortal(vector<Bus> &c)
{
    string password;
    cout << "Enter Admin Password: ";
    cin >> password;
    cin.ignore();

    if (password == "190707")
    {
    cout << "Authentication Completed!!" << endl;
    printLine('=');
    printline('-', 26);
    cout << "ADMIN MENU";
    printLine('-', 30);
    printLine('=');
    cout << "1. Add Bus" << endl;
    cout << "2. Remove Bus" << endl;
    cout << "3. View All Buses" << endl;
    cout << "4. Back" << endl;

    int des;
    cout << "Enter Your Choice: ";
    cin >> des;
    cin.ignore();

    if (des == 1)
    {
        Bus s1;
        s1.admin_input();
        c.push_back(s1);
        cout << "Bus added successfully!" << endl;
    }
    else if (des == 2)
    {
        if (c.empty())
        {
            cout << "No buses to remove." << endl;
        }
        else
        {
            printLine('-');
            for (int i = 0; i < (int)c.size(); i++)
            {
                cout << "\nBus " << i + 1 << ":" << endl;
                c[i].display();
            }
            printLine('-');
            int index;
            cout << "Enter Bus Number To Remove: ";
            cin >> index;
            cin.ignore();
            if (index >= 1 && index <= (int)c.size())
            {
                c.erase(c.begin() + index - 1);
                cout << "Bus removed successfully!" << endl;
            }
            else
            {
                cout << "Invalid bus number." << endl;
            }
        }
    }
    else if (des == 3)
    {
        if (c.empty())
        {
            cout << "No buses available." << endl;
        }
        else
        {
            printLine('-');
            cout << "---- ALL BUSES ----" << endl;
            printLine('-');
            for (int i = 0; i < (int)c.size(); i++)
            {
                cout << "\nBus " << i + 1 << ":" << endl;
                c[i].display();
                printLine('-');
            }
        }
    }
    else if (des == 4)
    {
        cout << "Going back..." << endl;
    }
    else
    {
        cout << "Invalid choice." << endl;
    }
        return;
    }
    else
    {
        cout << "Access Denied! Wrong Password." << endl;
    }
}

int main()
{
    vector<Passenger> p;
    vector<Bus> c;

    while (true)
    {
        printLine('=');
        cout << "   BUS RESERVATION SYSTEM" << endl;
        printLine('=');
        cout << "1. Passenger Portal" << endl;
        cout << "2. Admin Portal" << endl;
        cout << "3. Exit" << endl;
        printLine('-');

        int person_type;
        cout << "Enter Your Choice: ";
        cin >> person_type;
        cin.ignore();

        if (person_type == 1)
        {
            passengerPortal(p, c);
        }
        else if (person_type == 2)
        {
            adminPortal(c);
        }
        else if (person_type == 3)
        {
            cout << "Goodbye!" << endl;
            break;
        }
        else
        {
            cout << "Invalid option." << endl;
        }
        cout << "\nPress Enter To Continue...";
        cin.get();
    }
    return 0;
}
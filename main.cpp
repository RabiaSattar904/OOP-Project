#include <iostream>
#include <vector>
#include <fstream>
#include <stdexcept>
using namespace std;

// ================= BASE CLASS =================
class Vehicle
{
protected:
    string ownerName;
    string vehicleNo;

public:
    virtual void input()
    {
        cout << "\nEnter Owner Name: ";
        cin >> ownerName;

        cout << "Enter Vehicle Number: ";
        cin >> vehicleNo;
    }

    virtual void display() const
    {
        cout << "\nOwner Name   : " << ownerName;
        cout << "\nVehicle No   : " << vehicleNo;
    }

    string getNumber() const { return vehicleNo; }
    string getOwner() const { return ownerName; }

    virtual string getType() const { return "Vehicle"; }
    virtual int calculateFee() const { return 0; }

    virtual ~Vehicle() {}
};

// ================= VALIDATION =================
void validateHours(int hours)
{
    if(hours <= 0)
        throw invalid_argument("Invalid parking hours!");
}

// ================= CAR =================
class Car : public Vehicle
{
private:
    int hours;

public:
    void input() override
    {
        Vehicle::input();

        cout << "Enter Parking Hours: ";
        cin >> hours;

        validateHours(hours);
    }

    void display() const override
    {
        Vehicle::display();
        cout << "\nType         : Car";
        cout << "\nHours        : " << hours;
        cout << "\nFee          : " << calculateFee();
        cout << "\n-------------------------";
    }

    int calculateFee() const override
    {
        return hours * 50;
    }

    string getType() const override
    {
        return "Car";
    }
};

// ================= BIKE =================
class Bike : public Vehicle
{
private:
    int hours;

public:
    void input() override
    {
        Vehicle::input();

        cout << "Enter Parking Hours: ";
        cin >> hours;

        validateHours(hours);
    }

    void display() const override
    {
        Vehicle::display();
        cout << "\nType         : Bike";
        cout << "\nHours        : " << hours;
        cout << "\nFee          : " << calculateFee();
        cout << "\n-------------------------";
    }

    int calculateFee() const override
    {
        return hours * 20;
    }

    string getType() const override
    {
        return "Bike";
    }
};

// ================= SYSTEM FUNCTIONS =================
void saveData(const vector<Vehicle*>& v)
{
    ofstream file("parking.txt");

    for(auto x : v)
        file << x->getOwner() << " "
             << x->getNumber() << " "
             << x->getType() << endl;

    file.close();
}

void searchVehicle(const vector<Vehicle*>& v)
{
    string num;
    cout << "\nEnter Vehicle Number: ";
    cin >> num;

    bool found = false;

    for(auto x : v)
    {
        if(x->getNumber() == num)
        {
            x->display();
            found = true;
        }
    }

    if(!found)
        cout << "Not Found!\n";
}

void removeVehicle(vector<Vehicle*>& v)
{
    string num;
    cout << "\nEnter Vehicle Number to Remove: ";
    cin >> num;

    for(int i = 0; i < v.size(); i++)
    {
        if(v[i]->getNumber() == num)
        {
            delete v[i];
            v.erase(v.begin() + i);
            cout << "Removed Successfully!\n";
            return;
        }
    }

    cout << "Vehicle Not Found!\n";
}

// ================= TEMPLATE =================
template<typename T>
void showCount(T count)
{
    cout << "\nTotal Vehicles: " << count << endl;
}

// ================= MAIN =================
int main()
{
    vector<Vehicle*> parking;
    int choice;

    do
    {
        cout << "\n===== SMART PARKING SYSTEM =====";
        cout << "\n1. Park Car";
        cout << "\n2. Park Bike";
        cout << "\n3. Display All";
        cout << "\n4. Search";
        cout << "\n5. Remove";
        cout << "\n6. Save";
        cout << "\n7. Exit";
        cout << "\nEnter choice: ";
        cin >> choice;

        try
        {
            if(choice == 1)
            {
                Vehicle* v = new Car();
                v->input();
                parking.push_back(v);
            }

            else if(choice == 2)
            {
                Vehicle* v = new Bike();
                v->input();
                parking.push_back(v);
            }

            else if(choice == 3)
            {
                if(parking.empty())
                    cout << "Empty!\n";
                else
                {
                    for(auto x : parking)
                        x->display();

                    showCount(parking.size());
                }
            }

            else if(choice == 4)
                searchVehicle(parking);

            else if(choice == 5)
                removeVehicle(parking);

            else if(choice == 6)
            {
                saveData(parking);
                cout << "Saved!\n";
            }
        }
        catch(exception &e)
        {
            cout << "Error: " << e.what();
        }

    } while(choice != 7);

    for(auto x : parking)
        delete x;

    return 0;
}

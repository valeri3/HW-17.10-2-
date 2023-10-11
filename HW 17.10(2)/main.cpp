#include <iostream>
#include <string>
using namespace std;

class Base 
{
public:
    static int people_on_base;
    static int vehicles_on_base;
    static double petrol_on_base;
    static double goods_on_base;
};

int Base::people_on_base = 0;
int Base::vehicles_on_base = 0;
double Base::petrol_on_base = 10000.0; 
double Base::goods_on_base = 500.0;   

class Vehicle 
{
protected:
    double petrol_amount;
    double tank_volume;

public:
    Vehicle(double petrol_amount, double tank_volume)
        : petrol_amount(petrol_amount), tank_volume(tank_volume) {}
    
    double getPetrolAmount() 
    {
        return petrol_amount;
    }

    double getTankVolume() 
    {
        return tank_volume;
    }

    virtual void arrive()
    {
        Base::people_on_base++;
        Base::vehicles_on_base++;
    }

    virtual bool leave() 
    {
        if (petrol_amount < tank_volume && Base::people_on_base == 0) 
        {
            return false; 
        }

        petrol_amount = tank_volume;
     
        Base::people_on_base--;
        Base::vehicles_on_base--;

        return true;
    }
};

class Bus : public Vehicle 
{
    int people;
    int max_people;

public:
    Bus(int people, int max_people, double petrol, double max_petrol)
        : Vehicle(petrol, max_petrol), people(people), max_people(max_people) {}

    int getPeopleCount() 
    {
        return people;
    }

    int getMaxPeople() 
    {
        return max_people;
    }

    void arrive() override 
    {
        Base::people_on_base += people;
        Base::vehicles_on_base++;
    }

    bool leave() override 
    {
        if (!Vehicle::leave()) 
        {
            return false; 
        }

        Base::people_on_base -= people;

        return true;
    }
};

class Truck : public Vehicle 
{
    double load;
    double max_load;

public:
    Truck(double load, double max_load, double petrol, double max_petrol)
        : Vehicle(petrol, max_petrol), load(load), max_load(max_load) {}

    double getCurrentLoad()
    {
        return load;
    }

    double getMaxLoad()
    {
        return max_load;
    }

    void arrive() override
    {
        Base::vehicles_on_base++;
        Base::goods_on_base += load;
    }

    bool leave() override 
    {
        if (!Vehicle::leave()) 
        {
            return false; 
        }

        Base::goods_on_base -= load;

        return true;
    }
};

int main() 
{
    Vehicle car(30.0, 50.0);
    Bus bus(20, 50, 20.0, 100.0);
    Truck truck(10.0, 20.0, 15.0, 80.0);

    car.arrive();
    bus.arrive();
    truck.arrive();

    if (car.leave()) 
    {
        cout << "Car left the base" << endl;
    }
    else
    {
        cout << "Car couldn't leave the base" << endl;
    }

    if (bus.leave()) 
    {
        cout << "Bus left the base" << endl;
    }
    else 
    {
        cout << "Bus couldn't leave the base" << endl;
    }

    if (truck.leave()) 
    {
        cout << "Truck left the base" << endl;
    }
    else 
    {
        cout << "Truck couldn't leave the base" << endl;
    }

    return 0;
}

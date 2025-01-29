// ConsoleApplication6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
using namespace std;

enum Fuel {
    GAS,DIESEL,ELECTRIC,OTHER
};


ostream& operator<<(ostream& out, Fuel f) {
    if (f == Fuel::GAS) {
        out << "gas";
    }
    else if (f == Fuel::DIESEL) {
        out << "diesel";
    }
    else if (f == Fuel::ELECTRIC) out << "electric";
    else out << "other";
    return out;
}




class Engine {
    int power;
    int torque;
    int engineDisplacement;
    Fuel fuel;
    const int id;
    static int enginesNumber;
    char* name;
    static int minPower;

public:
    Engine() :id(0 + Engine::enginesNumber++) {
        this->name = new char[strlen("unnamed") + 1];
        strcpy(this->name, "unnamed");
        this->power = 0;
        this->torque =0;
        this->engineDisplacement=0;
        this->fuel = Fuel::OTHER;
    }

    Engine(const char* _name, int _power, int _torque, int _engineDisplacement, Fuel _fuel):id(0+Engine::enginesNumber++) {
        this->name = new char[strlen(_name) + 1];
        strcpy(this->name, _name);
        if (_power > Engine::minPower) {
            this->power = _power;
        }
        else {
            this->power = Engine::minPower;
        }
        this->torque = _torque;
        this->engineDisplacement = _engineDisplacement;
        this->fuel = _fuel;


    }

    Engine(const Engine& e) :id(0 + Engine::enginesNumber++) {
        this->name = new char[strlen(e.name) + 1];
        strcpy(this->name, e.name);
        if (e.power > Engine::minPower) {
            this->power = e.power;
        }
        else {
            this->power = Engine::minPower;
        }
        this->torque = e.torque;
        this->engineDisplacement = e.engineDisplacement;
        this->fuel = e.fuel;
    }
   

    Engine& operator=(const Engine& e) {
        if (this != &e) {
            if (this->name != nullptr) {
                delete[] this->name;
                this->name = nullptr;
            }
            this->name = new char[strlen(e.name) + 1];
            strcpy(this->name, e.name);
            if (e.power > Engine::minPower) {
                this->power = e.power;
            }
            else {
                this->power = Engine::minPower;
            }
            this->torque = e.torque;
            this->engineDisplacement = e.engineDisplacement;
            this->fuel = e.fuel;
      

           
        }
        return *this;
    }

    Engine& operator+=(int power) {
        this->power += power;
        return *this;
    }

    bool operator==(const Engine& e) {
        if (strcmp(this->name, e.name) != 0)
            return false;
        if (this->power != e.power)
            return false;
        if (this->torque != e.torque)
            return false;
        if (this->engineDisplacement != e.engineDisplacement) {
            return false;
        }
        if (this->fuel != e.fuel)
            return false;
        return true;
    }

    bool operator!=(const Engine& e) {
        if (!(this->operator==(e)))
            return false;
        return true;
            
    }


    Engine& operator++() {
        this->power++;
        return *this;
   }
    Engine& operator++(int) {
        Engine copy=*this;
        this->power++;
        return copy;

    }
    
    Fuel getFuel() {
        return this->fuel;
    }
    const char* getName() {
        return this->name;
    }
    void setName(const char* _name) {
        if (this->name != nullptr) {
            delete[] this->name;
            this->name = nullptr;
        }

        this->name = new char[strlen(_name) + 1];
        strcpy(this->name, _name);
    }

    static int getMinPower() {
        return Engine::minPower;
    }


    ~Engine() {
        if (this->name != nullptr) {
            delete[] this->name;
            this->name = nullptr;
        }

    }
    void writeToFile(fstream& f) {
        int nameLen = strlen(name) + 1;
        f.write((char*)&nameLen, sizeof(int));
        f.write(name, nameLen);

        f.write((char*)&power, sizeof(int));
        f.write((char*)&torque, sizeof(int));
        f.write((char*)&engineDisplacement, sizeof(int));

        f.write((char*)&fuel, sizeof(Fuel));
    }

    void readFromFile(fstream& f) {
        int nameLen;
        f.read((char*)&nameLen, sizeof(int));

        char* buffer = new char[nameLen];
        f.read(buffer, nameLen);
        setName(buffer);
        delete[] buffer;

        f.read((char*)&power, sizeof(int));
        f.read((char*)&torque, sizeof(int));
        f.read((char*)&engineDisplacement, sizeof(int));

        f.read((char*)&fuel, sizeof(Fuel));
    }

   
    void display() const {
        cout << "Engine: " << name << ", Power: " << power << " HP, Torque: " << torque
            << " Nm, Displacement: " << engineDisplacement << " cc, Fuel Type: "
            << fuel << endl;
    }



    friend ostream& operator<< (ostream& out, const Engine& e) {
        out << "id " << e.id << "\nname: " << e.name << "\npower " << e.power << "\ntorque " << e.torque 
            << "\nengine displacement " << e.engineDisplacement << "\nfuel type " << e.fuel;
        return out;
    }
    friend istream& operator>>(istream& in, Engine& e) {
        cout << "Type the engine's name ";
        if (e.name != nullptr) {
            delete[] e.name;
            e.name = nullptr;
        }
        string buffer;
        in >> buffer;
        e.name = new char[buffer.size() + 1];
        strcpy_s(e.name, buffer.size() + 1, buffer.data());
        cout << "Type the engine's power ";
        in >> e.power;
        cout << "Type the engine's torque ";
        in >> e.torque;
        cout << "Type the engine displacement ";
        in >> e.engineDisplacement;
        cout << "Type the engine's fuel(gas,diesel,electric,other) ";
        string fuelType;
        in >> fuelType;
        if (fuelType == "gas")
            e.fuel = Fuel::GAS;
        else if (fuelType == "diesel")
            e.fuel = Fuel::DIESEL;
        else if (fuelType == "electric")
            e.fuel = Fuel::ELECTRIC;
        else e.fuel = Fuel::OTHER;
        return in;

    }
}; int Engine::enginesNumber = 0;
int Engine::minPower = 20;

class Vehicle {
protected:
    string name = "unnamed";
    int maxSpeed=0;
 
public:
    Vehicle() {
       
    }

    Vehicle(string _name, int _maxSpeed) {
        this->name = _name;
        this->maxSpeed = _maxSpeed;
    }

    Vehicle(const Vehicle& v) {
        this->name = v.name;
        this->maxSpeed = v.maxSpeed;
    }

    Vehicle& operator=(const Vehicle& v) {
        if (this != &v) {
            this->name = v.name;
            this->maxSpeed = v.maxSpeed;
            
        }
        return *this;

    }


    friend ostream& operator<<(ostream& out, const Vehicle& v) {
        out << "Name " << v.name;
        out << "\nMaximum speed " << v.maxSpeed;
        return out;

    }

    friend istream& operator>>(istream& in,  Vehicle& v) {
        cout << "Type the vehicle's name ";
        in >> v.name;
        cout << "Type the vehicle's max speed ";
        in >> v.maxSpeed;
        return in;
    }



    ~Vehicle() {

    }

    bool operator==(const Vehicle& v) {
        if (this->name != v.name) {
            return false;
        }
        if (this->maxSpeed != v.maxSpeed) {
            return false;
        }
        return true;
    }
}; 

class Car :public Vehicle {
    Engine** engineList;
    int seats;
    int year;
    float* prices;
    int possibleEngines;
    int possiblePrices;

public:
    Car() {
        this->engineList = nullptr;
        this->seats = 0;
        this->year = 0;
        this->prices = nullptr;
        this->possibleEngines = 0;
        this->possiblePrices = 0;
        
    }
    Car(string _name, int _maxSpeed,const Engine** _engineList, int _seats, int _year, const float* _prices, int _possibleEngines,int _possiblePrices) {
        this->name = _name;
        this->maxSpeed = _maxSpeed;
        if (_possibleEngines > 0 && _engineList != nullptr) {
            this->possibleEngines = _possibleEngines;
            this->engineList = new Engine*[_possibleEngines];
            for (int i = 0; i < this->possibleEngines; i++) {
                this->engineList[i] = new Engine(*_engineList[i]);
            }
        }
        else {
            this->engineList = nullptr;
            this->possibleEngines = 0;
        }
        if (_seats > 1) {
            this->seats = _seats;
        }
        else
            this->seats = 1;
        this->year = _year;

        if (_possiblePrices > 0 && _prices != nullptr) {
            this->possiblePrices = _possiblePrices;
            this->prices = new float[this->possiblePrices];
            for (int i = 0; i < this->possiblePrices; i++) {
                this->prices[i] = _prices[i];
            }
        }
        else {
            this->prices = nullptr;
            this->possiblePrices = 0;
        }
        
    }
    Car(const Car& c) {
        this->name = c.name;
        this->maxSpeed = c.maxSpeed;
        if (c.possibleEngines > 0 && c.engineList != nullptr) {
            this->possibleEngines = c.possibleEngines;
            this->engineList = new Engine * [c.possibleEngines];
            for (int i = 0; i < this->possibleEngines; i++) {
                this->engineList[i] = new Engine(*c.engineList[i]);
            }
        }
        else {
            this->engineList = nullptr;
            this->possibleEngines = 0;
        }
        if (c.seats > 1) {
            this->seats = c.seats;
        }
        else
            this->seats = 1;
        this->year = c.year;

        if (c.possiblePrices > 0 && c.prices != nullptr) {
            this->possiblePrices = c.possiblePrices;
            this->prices = new float[this->possiblePrices];
            for (int i = 0; i < this->possiblePrices; i++) {
                this->prices[i] = c.prices[i];
            }
        }
        else {
            this->prices = nullptr;
            this->possiblePrices = 0;
        }

    }

    Car& operator=(const Car& c) {
        if (this != &c) {
            this->name = c.name;
            this->maxSpeed = c.maxSpeed;
            if (c.possibleEngines > 0 && c.engineList != nullptr) {
                this->possibleEngines = c.possibleEngines;
                this->engineList = new Engine * [c.possibleEngines];
                for (int i = 0; i < this->possibleEngines; i++) {
                    this->engineList[i] = new Engine(*c.engineList[i]);
                }
            }
            else {
                this->engineList = nullptr;
                this->possibleEngines = 0;
            }
            if (c.seats > 1) {
                this->seats = c.seats;
            }
            else
                this->seats = 1;
            this->year = c.year;

            if (c.possiblePrices > 0 && c.prices != nullptr) {
                this->possiblePrices = c.possiblePrices;
                this->prices = new float[this->possiblePrices];
                for (int i = 0; i < this->possiblePrices; i++) {
                    this->prices[i] = c.prices[i];
                }
            }
            else {
                this->prices = nullptr;
                this->possiblePrices = 0;
            }
        } return *this;

    }

    friend ostream& operator<<(ostream& out, const Car& c) {
        out << (Vehicle)c;  
        out << "\nSeats: " << c.seats;
        out << "\nYear: " << c.year;
        out << "\nPossible Engines: " << c.possibleEngines;
        out << endl;
        if (c.possibleEngines > 0 && c.engineList != nullptr) {
            for (int i = 0; i < c.possibleEngines; i++)
                out << *c.engineList[i] << " ";
        }
       
        out << "\nPossible Prices: " << c.possiblePrices << " ";
        if (c.possiblePrices > 0 && c.prices != nullptr) {
            for (int i = 0; i < c.possiblePrices; i++) {
                out << *c.prices << " ";
            }
        }

        return out;


      }

    friend istream& operator>>(istream& in, Car& c) {
        cout << "Enter car name: ";
        in >> c.name;

        cout << "Enter max speed: ";
        in >> c.maxSpeed;

        cout << "Enter number of seats: ";
        in >> c.seats;

        cout << "Enter manufacturing year: ";
        in >> c.year;

     
        cout << "Enter the number of available engines: ";
        in >> c.possibleEngines;

       
        if (c.engineList != nullptr) {
            for (int i = 0; i < c.possibleEngines; i++) {
                delete c.engineList[i];
            }
            delete[] c.engineList;
        }

        if (c.possibleEngines > 0) {
            c.engineList = new Engine * [c.possibleEngines];
            for (int i = 0; i < c.possibleEngines; i++) {
                c.engineList[i] = new Engine();
                cout << "Enter details for engine " << i + 1 << ":\n";
                in >> *c.engineList[i]; 
            }
        }
        else {
            c.engineList = nullptr;
        }

      
        cout << "Enter the number of available prices: ";
        in >> c.possiblePrices;

       
        if (c.prices != nullptr) {
            delete[] c.prices;
        }

        if (c.possiblePrices > 0) {
            c.prices = new float[c.possiblePrices];
            for (int i = 0; i < c.possiblePrices; i++) {
                cout << "Enter price " << i + 1 << ": ";
                in >> c.prices[i];
            }
        }
        else {
            c.prices = nullptr;
        }

        return in;
    }
   

   const float& operator  [](int index) const {
        if (index >= 0 && index < possiblePrices)
                return prices[index];
   }

 

  
    ~Car() {
        if (this -> engineList != nullptr) {
            for (int i = 0; i < this->possibleEngines; i++) {
                delete this->engineList[i];
                this->engineList[i] = nullptr;
            }
            delete[] this->engineList;
            this->engineList = nullptr;
        }

        if (this->prices != nullptr) {
            delete[] this->prices;
            this->prices = nullptr;
        }
    }

};



int main()
{
    Vehicle v1;
    Car c1;
    Engine* e1 = new Engine("V8 Turbo", 400, 500, 4000, Fuel::GAS);
    Engine* e2 = new Engine("Electric Motor", 300, 400, 0, Fuel::ELECTRIC);
    const Engine* engineList[1] = {  e2 };
    float prices[] = { 30000 };
    Car myCar("Tesla Model S", 250, engineList, 5, 2023, prices, 1, 1);
    
   // cout << myCar[0];
   // cout << myCar << endl;
   // cin >> c1;
    //cout<< c1;
    //cout << endl;
    Engine* e3 = new Engine();
    fstream fileOut("engine.dat", ios::out | ios::binary);
    if (fileOut.is_open()) {
        e1->writeToFile(fileOut);  
        fileOut.close();
        
    }
    else {
        cout << "An error occurred while opening the file for writing!\n";
    }

   
    delete e1;
    fstream fileIn("engine.dat", ios::in | ios::binary);
    if (fileIn.is_open()) {
        e3->readFromFile(fileIn);  
        fileIn.close();
      
    }
    else {
        cout << "An error occurred while reading from the file\n";
    }

   
    e2->display();

    cout << *e3;
    delete e3;

    
  
    //cout << myCar;
   
    //delete e1;
    delete e2;

    return 0;
   
}



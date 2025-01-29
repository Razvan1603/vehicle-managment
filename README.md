# vehicle-managment
Vehicle Management System
This C++ application is designed to model vehicles, engines, and cars, including serialization and deserialization functionality for engine objects.

Project Overview
The program demonstrates basic object-oriented principles such as inheritance, encapsulation, and polymorphism. It includes:

Engine class: Represents an engine, with properties like power, torque, fuel type, and engine displacement.
Vehicle class: A base class for general vehicle properties like name and maximum speed.
Car class: Inherits from Vehicle, adding engine options, seating capacity, year, and pricing.
Serialization: Ability to save engine data to a binary file and load it back.
Key Features
Engine Class: Represents an engine with various attributes like power, torque, engine displacement, and fuel type. It supports serialization (saving to and loading from a file).
Vehicle Class: Defines basic vehicle properties, such as name and max speed.
Car Class: Inherits from Vehicle, with additional attributes such as available engines, seats, year, and prices.
Operator Overloading: Multiple operator overloads such as <<, >>, +=, ==, !=, etc., are used for efficient object handling.
Classes Overview
Engine
The Engine class contains:

Attributes: power, torque, engineDisplacement, fuel, id, name.
Methods: Constructors, assignment operator overload, comparison operators, and file I/O methods for serialization.
Vehicle
The Vehicle class contains:

Attributes: name, maxSpeed.
Methods: Constructors, assignment operator overload, and stream operators for input/output.
Car
The Car class extends Vehicle and contains:

Attributes: engineList (array of engines), seats, year, prices, possibleEngines, possiblePrices.
Methods: Constructors, assignment operator overload, input/output stream operators, and more.
File Serialization
The engine's data can be saved to and loaded from a binary file (engine.dat), showcasing serialization.

#pragma once
#include <string>
#include <iostream>

class Employee {
protected:
    int id;
    std::string name;
    int age;
    char gender;
    std::string position;

public:
    Employee(int id, std::string name, int age, char gender, std::string position);
    virtual ~Employee() = default;

    virtual double calculateSalary() const = 0;
    virtual void displayInfo() const;

    int getId() const;
};

class Manager : virtual public Employee {
public:
    Manager(int id, std::string name, int age, char gender);
    double calculateSalary() const override;
};

class Technician : public Employee {
private:
    double work_hours;

public:
    Technician(int id, std::string name, int age, char gender, double hours);
    double calculateSalary() const override;
    void displayInfo() const override;
};

class Salesperson : virtual public Employee {
protected:
    double sales_amount;

public:
    Salesperson(int id, std::string name, int age, char gender, double sales);
    double calculateSalary() const override;
    void displayInfo() const override;
};

class SalesManager : public Manager, public Salesperson {
private:
    double department_sales;

public:
    SalesManager(int id, std::string name, int age, char gender, double dept_sales);
    double calculateSalary() const override;
    void displayInfo() const override;
};

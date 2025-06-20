#include "employee.h"
#include <iostream>

Employee::Employee(int id, std::string name, int age, char gender, std::string position)
    : id(id), name(name), age(age), gender(gender), position(position) {}

void Employee::displayInfo() const {
    std::cout << "ID: " << id << ", Name: " << name << ", Age: " << age << ", Gender: " << gender
              << ", Position: " << position;
}

int Employee::getId() const {
    return id;
}

Manager::Manager(int id, std::string name, int age, char gender)
    : Employee(id, name, age, gender, "Manager") {}

double Manager::calculateSalary() const {
    return 8000.0;
}

Technician::Technician(int id, std::string name, int age, char gender, double hours)
    : Employee(id, name, age, gender, "Technician"), work_hours(hours) {}

double Technician::calculateSalary() const {
    return work_hours * 100;
}

void Technician::displayInfo() const {
    Employee::displayInfo();
    std::cout << ", Work Hours: " << work_hours;
}

Salesperson::Salesperson(int id, std::string name, int age, char gender, double sales)
    : Employee(id, name, age, gender, "Salesperson"), sales_amount(sales) {}

double Salesperson::calculateSalary() const {
    return sales_amount * 0.04;
}

void Salesperson::displayInfo() const {
    Employee::displayInfo();
    std::cout << ", Sales Amount: " << sales_amount;
}

SalesManager::SalesManager(int id, std::string name, int age, char gender, double dept_sales)
    : Employee(id, name, age, gender, "Sales Manager"), Manager(id, name, age, gender), Salesperson(id, name, age, gender, 0), department_sales(dept_sales) {}

double SalesManager::calculateSalary() const {
    return 5000 + department_sales * 0.005;
}

void SalesManager::displayInfo() const {
    Employee::displayInfo();
    std::cout << ", Department Sales: " << department_sales;
}

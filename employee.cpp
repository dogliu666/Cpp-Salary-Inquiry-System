#include "employee.h"
#include <iostream>
#include <sstream>

Employee::Employee(int id, std::string name, int age, char gender, std::string position)
    : id(id), name(name), age(age), gender(gender), position(position) {}

void Employee::displayInfo() const {
    std::cout << "ID: " << id << ", Name: " << name << ", Age: " << age << ", Gender: " << gender
              << ", Position: " << position;
}

int Employee::getId() const {
    return id;
}

std::string Employee::getName() const {
    return name;
}

// --- 序列化实现 ---
std::string Manager::serialize() const {
    std::ostringstream oss;
    oss << "Manager," << id << "," << name << "," << age << "," << gender;
    return oss.str();
}

std::string Technician::serialize() const {
    std::ostringstream oss;
    oss << "Technician," << id << "," << name << "," << age << "," << gender << "," << work_hours;
    return oss.str();
}

std::string Salesperson::serialize() const {
    std::ostringstream oss;
    oss << "Salesperson," << id << "," << name << "," << age << "," << gender << "," << sales_amount;
    return oss.str();
}

std::string SalesManager::serialize() const {
    std::ostringstream oss;
    oss << "SalesManager," << id << "," << name << "," << age << "," << gender << "," << department_sales;
    return oss.str();
}

// --- 反序列化实现 ---
std::unique_ptr<Employee> Employee::deserialize(const std::string& line) {
    std::istringstream iss(line);
    std::string type, name;
    int id, age;
    char gender;
    getline(iss, type, ',');
    if (type == "Manager") {
        iss >> id; iss.ignore();
        getline(iss, name, ',');
        iss >> age; iss.ignore();
        iss >> gender;
        return std::make_unique<Manager>(id, name, age, gender);
    } else if (type == "Technician") {
        double hours;
        iss >> id; iss.ignore();
        getline(iss, name, ',');
        iss >> age; iss.ignore();
        iss >> gender; iss.ignore();
        iss >> hours;
        return std::make_unique<Technician>(id, name, age, gender, hours);
    } else if (type == "Salesperson") {
        double sales;
        iss >> id; iss.ignore();
        getline(iss, name, ',');
        iss >> age; iss.ignore();
        iss >> gender; iss.ignore();
        iss >> sales;
        return std::make_unique<Salesperson>(id, name, age, gender, sales);
    } else if (type == "SalesManager") {
        double dept_sales;
        iss >> id; iss.ignore();
        getline(iss, name, ',');
        iss >> age; iss.ignore();
        iss >> gender; iss.ignore();
        iss >> dept_sales;
        return std::make_unique<SalesManager>(id, name, age, gender, dept_sales);
    }
    return nullptr;
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

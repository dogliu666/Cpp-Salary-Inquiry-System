#include <iostream>
#include <vector>
#include <memory>
#include "employee.h"

void showMenu() {
    std::cout << "\n--- Employee Salary Inquiry System ---" << std::endl;
    std::cout << "1. Add Employee" << std::endl;
    std::cout << "2. Display All Employees" << std::endl;
    std::cout << "3. Calculate Total Salary" << std::endl;
    std::cout << "4. Exit" << std::endl;
    std::cout << "Enter your choice: ";
}

void addEmployee(std::vector<std::unique_ptr<Employee>>& employees) {
    int id, age, type;
    std::string name;
    char gender;

    std::cout << "Enter ID: ";
    std::cin >> id;
    std::cout << "Enter Name: ";
    std::cin >> name;
    std::cout << "Enter Age: ";
    std::cin >> age;
    std::cout << "Enter Gender (M/F): ";
    std::cin >> gender;

    std::cout << "Enter Employee Type (1: Manager, 2: Technician, 3: Salesperson, 4: Sales Manager): ";
    std::cin >> type;

    switch (type) {
        case 1:
            employees.push_back(std::make_unique<Manager>(id, name, age, gender));
            break;
        case 2: {
            double hours;
            std::cout << "Enter Work Hours: ";
            std::cin >> hours;
            employees.push_back(std::make_unique<Technician>(id, name, age, gender, hours));
            break;
        }
        case 3: {
            double sales;
            std::cout << "Enter Sales Amount: ";
            std::cin >> sales;
            employees.push_back(std::make_unique<Salesperson>(id, name, age, gender, sales));
            break;
        }
        case 4: {
            double dept_sales;
            std::cout << "Enter Department Sales Amount: ";
            std::cin >> dept_sales;
            employees.push_back(std::make_unique<SalesManager>(id, name, age, gender, dept_sales));
            break;
        }
        default:
            std::cout << "Invalid employee type." << std::endl;
            break;
    }
}

void displayAllEmployees(const std::vector<std::unique_ptr<Employee>>& employees) {
    if (employees.empty()) {
        std::cout << "No employees to display." << std::endl;
        return;
    }
    for (const auto& emp : employees) {
        emp->displayInfo();
        std::cout << ", Calculated Salary: " << emp->calculateSalary() << std::endl;
    }
}

void calculateTotalSalary(const std::vector<std::unique_ptr<Employee>>& employees) {
    double total_salary = 0.0;
    for (const auto& emp : employees) {
        total_salary += emp->calculateSalary();
    }
    std::cout << "Total salary of all employees: " << total_salary << std::endl;
}

int main() {
    std::vector<std::unique_ptr<Employee>> employees;
    int choice;

    do {
        showMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                addEmployee(employees);
                break;
            case 2:
                displayAllEmployees(employees);
                break;
            case 3:
                calculateTotalSalary(employees);
                break;
            case 4:
                std::cout << "Exiting program." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 4);

    return 0;
}

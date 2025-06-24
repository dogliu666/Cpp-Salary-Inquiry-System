#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include <cstdlib>
#include "employee.h"

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void waitForEnter() {
    std::cout << "\n按回车键继续...";
    std::cin.ignore();
    std::cin.get();
    clearScreen();
}

void showMenu() {
    std::cout << R"(
  ____              __     __ _                 
 |  _ \  __ _  _   _\ \   / /(_)  ___ __      __
 | |_) |/ _` || | | |\ \ / / | | / _ \\ \ /\ / /
 |  __/| (_| || |_| | \ V /  | ||  __/ \ V  V / 
 |_|    \__,_| \__, |  \_/   |_| \___|  \_/\_/  
               |___/                            
    )" << std::endl;
    std::cout << "==== 员工薪资管理系统 ====" << std::endl;
    std::cout << "1. 添加员工" << std::endl;
    std::cout << "2. 显示所有员工" << std::endl;
    std::cout << "3. 查询员工" << std::endl;
    std::cout << "4. 修改员工信息" << std::endl;
    std::cout << "5. 删除员工" << std::endl;
    std::cout << "6. 计算总薪资" << std::endl;
    std::cout << "7. 退出" << std::endl;
    std::cout << "请输入您的选择: ";
}

void addEmployee(std::vector<std::unique_ptr<Employee>>& employees) {
    int id, age, type;
    std::string name;
    char gender;

    std::cout << "=== 添加员工 ===" << std::endl;
    
    // 检查ID是否已存在
    std::cout << "请输入员工ID: ";
    std::cin >> id;
    for (const auto& emp : employees) {
        if (emp->getId() == id) {
            std::cout << "错误：员工ID " << id << " 已存在！" << std::endl;
            return;
        }
    }

    std::cout << "请输入姓名: ";
    std::cin >> name;
    std::cout << "请输入年龄: ";
    std::cin >> age;
    std::cout << "请输入性别 (M/F): ";
    std::cin >> gender;

    std::cout << "请选择员工类型:" << std::endl;
    std::cout << "1: 经理" << std::endl;
    std::cout << "2: 技术员" << std::endl;
    std::cout << "3: 销售员" << std::endl;
    std::cout << "4: 销售经理" << std::endl;
    std::cout << "请输入选择: ";
    std::cin >> type;

    switch (type) {
        case 1:
            employees.push_back(std::make_unique<Manager>(id, name, age, gender));
            std::cout << "经理添加成功！" << std::endl;
            break;
        case 2: {
            double hours;
            std::cout << "请输入工作小时数: ";
            std::cin >> hours;
            employees.push_back(std::make_unique<Technician>(id, name, age, gender, hours));
            std::cout << "技术员添加成功！" << std::endl;
            break;
        }
        case 3: {
            double sales;
            std::cout << "请输入销售额: ";
            std::cin >> sales;
            employees.push_back(std::make_unique<Salesperson>(id, name, age, gender, sales));
            std::cout << "销售员添加成功！" << std::endl;
            break;
        }
        case 4: {
            double dept_sales;
            std::cout << "请输入部门销售额: ";
            std::cin >> dept_sales;
            employees.push_back(std::make_unique<SalesManager>(id, name, age, gender, dept_sales));
            std::cout << "销售经理添加成功！" << std::endl;
            break;
        }
        default:
            std::cout << "无效的员工类型！" << std::endl;
            break;
    }
}

void displayAllEmployees(const std::vector<std::unique_ptr<Employee>>& employees) {
    std::cout << "=== 所有员工信息 ===" << std::endl;
    if (employees.empty()) {
        std::cout << "暂无员工信息。" << std::endl;
        return;
    }
    
    std::cout << "序号\n";
    for (int i = 0; i < employees.size(); ++i) {
        std::cout << (i + 1) << ". ";
        employees[i]->displayInfo();
        std::cout << ", 计算薪资: " << employees[i]->calculateSalary() << std::endl;
    }
}

void calculateTotalSalary(const std::vector<std::unique_ptr<Employee>>& employees) {
    std::cout << "=== 薪资统计 ===" << std::endl;
    if (employees.empty()) {
        std::cout << "暂无员工，总薪资为: 0" << std::endl;
        return;
    }
    
    double total_salary = 0.0;
    for (const auto& emp : employees) {
        total_salary += emp->calculateSalary();
    }
    std::cout << "员工总数: " << employees.size() << std::endl;
    std::cout << "所有员工总薪资: " << total_salary << std::endl;
    std::cout << "平均薪资: " << total_salary / employees.size() << std::endl;
}

const std::string DATA_FILE = "employees.txt";

void saveEmployees(const std::vector<std::unique_ptr<Employee>>& employees) {
    std::ofstream ofs(DATA_FILE);
    for (const auto& emp : employees) {
        ofs << emp->serialize() << std::endl;
    }
}

void loadEmployees(std::vector<std::unique_ptr<Employee>>& employees) {
    std::ifstream ifs(DATA_FILE);
    std::string line;
    while (std::getline(ifs, line)) {
        auto emp = Employee::deserialize(line);
        if (emp) employees.push_back(std::move(emp));
    }
}

void searchEmployee(const std::vector<std::unique_ptr<Employee>>& employees) {
    std::cout << "=== 查询员工 ===" << std::endl;
    if (employees.empty()) {
        std::cout << "暂无员工信息。" << std::endl;
        return;
    }
    
    int choice;
    std::cout << "请选择查询方式:" << std::endl;
    std::cout << "1. 按ID查询" << std::endl;
    std::cout << "2. 按姓名查询" << std::endl;
    std::cout << "请输入选择: ";
    std::cin >> choice;
    
    bool found = false;
    
    if (choice == 1) {
        int id;
        std::cout << "请输入员工ID: ";
        std::cin >> id;
        
        for (const auto& emp : employees) {
            if (emp->getId() == id) {
                std::cout << "找到员工:" << std::endl;
                emp->displayInfo();
                std::cout << ", 计算薪资: " << emp->calculateSalary() << std::endl;
                found = true;
                break;
            }
        }    } else if (choice == 2) {
        std::string name;
        std::cout << "请输入员工姓名: ";
        std::cin >> name;
        
        for (const auto& emp : employees) {
            if (emp->getName() == name) {
                std::cout << "找到员工:" << std::endl;
                emp->displayInfo();
                std::cout << ", 计算薪资: " << emp->calculateSalary() << std::endl;
                found = true;
            }
        }
    } else {
        std::cout << "无效的选择！" << std::endl;
        return;
    }
    
    if (!found) {
        std::cout << "未找到匹配的员工。" << std::endl;
    }
}

void deleteEmployee(std::vector<std::unique_ptr<Employee>>& employees) {
    std::cout << "=== 删除员工 ===" << std::endl;
    if (employees.empty()) {
        std::cout << "暂无员工信息。" << std::endl;
        return;
    }
    
    int id;
    std::cout << "请输入要删除的员工ID: ";
    std::cin >> id;
    
    for (auto it = employees.begin(); it != employees.end(); ++it) {
        if ((*it)->getId() == id) {
            std::cout << "找到员工: ";
            (*it)->displayInfo();
            std::cout << std::endl;
            
            char confirm;
            std::cout << "确认删除此员工？(y/n): ";
            std::cin >> confirm;
            
            if (confirm == 'y' || confirm == 'Y') {
                employees.erase(it);
                std::cout << "员工删除成功！" << std::endl;
            } else {
                std::cout << "删除操作已取消。" << std::endl;
            }
            return;
        }
    }
    
    std::cout << "未找到ID为 " << id << " 的员工。" << std::endl;
}

void modifyEmployee(std::vector<std::unique_ptr<Employee>>& employees) {
    std::cout << "=== 修改员工信息 ===" << std::endl;
    if (employees.empty()) {
        std::cout << "暂无员工信息。" << std::endl;
        return;
    }
    
    int id;
    std::cout << "请输入要修改的员工ID: ";
    std::cin >> id;
    
    for (auto it = employees.begin(); it != employees.end(); ++it) {
        if ((*it)->getId() == id) {
            std::cout << "找到员工: ";
            (*it)->displayInfo();
            std::cout << std::endl;
            
            std::cout << "注意：修改员工信息将删除原记录并创建新记录" << std::endl;
            char confirm;
            std::cout << "确认修改此员工？(y/n): ";
            std::cin >> confirm;
            
            if (confirm == 'y' || confirm == 'Y') {
                // 删除原员工
                employees.erase(it);
                std::cout << "原员工记录已删除，请输入新的员工信息:" << std::endl;
                
                // 添加新员工信息
                addEmployee(employees);
            } else {
                std::cout << "修改操作已取消。" << std::endl;
            }
            return;
        }
    }
    
    std::cout << "未找到ID为 " << id << " 的员工。" << std::endl;
}

int main() {
    std::vector<std::unique_ptr<Employee>> employees;
    int choice;

    loadEmployees(employees);
    clearScreen();

    do {
        showMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                addEmployee(employees);
                saveEmployees(employees);
                waitForEnter();
                break;
            case 2:
                displayAllEmployees(employees);
                waitForEnter();
                break;
            case 3:
                searchEmployee(employees);
                waitForEnter();
                break;
            case 4:
                modifyEmployee(employees);
                saveEmployees(employees);
                waitForEnter();
                break;
            case 5:
                deleteEmployee(employees);
                saveEmployees(employees);
                waitForEnter();
                break;
            case 6:
                calculateTotalSalary(employees);
                waitForEnter();
                break;
            case 7:
                std::cout << "正在保存数据并退出程序..." << std::endl;
                saveEmployees(employees);
                break;
            default:
                std::cout << "无效的选择，请重新输入。" << std::endl;
                waitForEnter();
        }
    } while (choice != 7);

    return 0;
}

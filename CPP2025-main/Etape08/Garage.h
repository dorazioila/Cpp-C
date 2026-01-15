#ifndef GARAGE_H
#define GARAGE_H

#include <set>
#include <list>
#include <string>
#include <iostream>

#include "Client.h"
#include "Employee.h"
#include "Model.h"
#include "Option.h"
#include "Car.h"  

class Garage
{
private:
    std::set<Client> clients;
    std::set<Employee> employees;
    std::list<carconfig::Model> models;
    std::list<carconfig::Option> options;
    
    // SINGLETON CORRIGÉ
    static Garage instance;
    static carconfig::Car currentProject;  // ← STATIC + NAMESPACE
    

    Garage(const Garage&) = delete;
    Garage& operator=(const Garage&) = delete;

public:
    ~Garage() = default;  // OK public
     Garage() = default;
    static Garage& getInstance();
    static carconfig::Car& getCurrentProject();
    static void resetCurrentProject();
    
    // Models
    void addModel(const carconfig::Model& m);
    void displayAllModels() const;
    carconfig::Model getModel(int index) const;

    // Options
    void addOption(const carconfig::Option& o);
    void displayAllOptions() const;
    carconfig::Option getOption(int index) const;  // ← const ajouté

    // Clients
    int addClient(const std::string& ln, const std::string& fn, const std::string& gsm);
    void displayClients() const;
    void deleteClientByIndex(int index);
    void deleteClientById(int id);
    Client findClientByIndex(int index) const;
    Client findClientById(int id) const;

    // Employees
    int addEmployee(const std::string& ln, const std::string& fn, const std::string& login, const std::string& role);
    void displayEmployees() const;
    void deleteEmployeeByIndex(int index);
    void deleteEmployeeById(int id);
    Employee findEmployeeByIndex(int index) const;
    Employee findEmployeeById(int id) const;
};

#endif

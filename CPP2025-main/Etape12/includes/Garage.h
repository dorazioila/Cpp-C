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
    
    
    static Garage instance;
    static carconfig::Car currentProject;  
    

    Garage(const Garage&) = delete;
    Garage& operator=(const Garage&) = delete;

public:
    ~Garage() = default;
    Garage()= default;
    static Garage& getInstance();
    static carconfig::Car& getCurrentProject();
    static void resetCurrentProject();
    
    void addModel(const carconfig::Model& m);
    void displayAllModels() const;
    carconfig::Model getModel(int index) const;
    int getNbModels() const;
    
    void addOption(const carconfig::Option& o);
    void displayAllOptions() const;
    carconfig::Option getOption(int index) const;  
    int getNbOptions() const;
    
    int addClient(const std::string& ln, const std::string& fn, const std::string& gsm);
    void displayClients() const;
    void deleteClientByIndex(int index);
    void deleteClientById(int id);
    Client findClientByIndex(int index) const;
    Client findClientById(int id) const;
    const std::set<Client>& getClients() const;

    
    int addEmployee(const std::string& ln, const std::string& fn, const std::string& login, const std::string& role);
    void displayEmployees() const;
    void deleteEmployeeByIndex(int index);
    void deleteEmployeeById(int id);
    Employee findEmployeeByIndex(int index) const;
    Employee findEmployeeById(int id) const;
    const std::set<Employee>& getEmployees() const;

    void importModelsFromCsv(std::string filename);
    void importOptionsFromCsv(std::string filename);
    void updateEmployee(const Employee& e);
    int getNbEmployees() const;
    void save();
    void load();
    static int idLoggedEmployee;


};

#endif

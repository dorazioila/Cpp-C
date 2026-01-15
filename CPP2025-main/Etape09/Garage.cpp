#include "Garage.h"
#include <stdexcept>
#include <iterator>

// ===============================================
// MODELS
// ===============================================

void Garage::addModel(const carconfig::Model& m)
{
    models.push_back(m);
}

void Garage::displayAllModels() const
{
    for (const auto& m : models)
        std::cout << m << std::endl;
}

carconfig::Model Garage::getModel(int index) const
{
    auto it = models.begin();
    std::advance(it, index);
    return *it;
}

// ===============================================
// OPTIONS
// ===============================================

void Garage::addOption(const carconfig::Option& o)
{
    options.push_back(o);
}

void Garage::displayAllOptions() const
{
    for (const auto& o : options)
        std::cout << o << std::endl;
}

carconfig::Option Garage::getOption(int index) const
{
    auto it = options.begin();
    std::advance(it, index);
    return *it;
}

// ===============================================
// CLIENTS
// ===============================================

int Garage::addClient(const std::string& ln, const std::string& fn, const std::string& gsm)
{
    int id = ++Actor::currentId;
    Client c(ln, fn, id, gsm);
    clients.insert(c);
    return id;
}

void Garage::displayClients() const
{
    for (const auto& c : clients)
        std::cout << c << std::endl;
}

void Garage::deleteClientByIndex(int index)
{
    auto it = clients.begin();
    std::advance(it, index);
    clients.erase(it);
}

void Garage::deleteClientById(int id)
{
    for (auto it = clients.begin(); it != clients.end(); ++it)
    {
        if (it->getId() == id)
        {
            clients.erase(it);
            return;
        }
    }
}

Client Garage::findClientByIndex(int index) const
{
    auto it = clients.begin();
    std::advance(it, index);
    return *it;
}

Client Garage::findClientById(int id) const
{
    for (const auto& c : clients)
    {
        if (c.getId() == id)
            return c;
    }
    throw std::invalid_argument("Client ID introuvable");
}

// ===============================================
// EMPLOYEES
// ===============================================

int Garage::addEmployee(const std::string& ln, const std::string& fn, const std::string& login, const std::string& role)
{
    int id = ++Actor::currentId;
    Employee e(ln, fn, id, login, role);
    employees.insert(e);
    return id;
}

void Garage::displayEmployees() const
{
    for (const auto& e : employees)
        std::cout << e << std::endl;
}

void Garage::deleteEmployeeByIndex(int index)
{
    auto it = employees.begin();
    std::advance(it, index);
    employees.erase(it);
}

void Garage::deleteEmployeeById(int id)
{
    for (auto it = employees.begin(); it != employees.end(); ++it)
    {
        if (it->getId() == id)
        {
            employees.erase(it);
            return;
        }
    }
}

Employee Garage::findEmployeeByIndex(int index) const
{
    auto it = employees.begin();
    std::advance(it, index);
    return *it;
}

Employee Garage::findEmployeeById(int id) const
{
    for (const auto& e : employees)
    {
        if (e.getId() == id)
            return e;
    }
    throw std::invalid_argument("Employee ID introuvable");
}

// SINGLETON IMPLEMENTATION
Garage Garage::instance;
carconfig::Car Garage::currentProject;

Garage& Garage::getInstance() {
    return instance;
}

carconfig::Car& Garage::getCurrentProject() {
    return currentProject;
}

void Garage::resetCurrentProject() {
    currentProject = carconfig::Car();  // reset
}

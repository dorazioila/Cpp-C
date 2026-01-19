#include "Garage.h"
#include <stdexcept>
#include <iterator>
#include <fstream>
#include <sstream>
#include "OptionException.h"
using namespace carconfig;


Garage::Garage()
{
    int id = ++Actor::currentId;
    Employee admin("ADMIN", "ADMIN", id, "admin", "Administratif");
    employees.insert(admin);
}


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
const std::set<Client>& Garage::getClients() const
{
    return clients;
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

const std::set<Employee>& Garage::getEmployees() const
{
    return employees;
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


Garage Garage::instance;
carconfig::Car Garage::currentProject;

Garage& Garage::getInstance() {
    return instance;
}

carconfig::Car& Garage::getCurrentProject() {
    return currentProject;
}

void Garage::resetCurrentProject() {
    currentProject = carconfig::Car();  
}

void Garage::importModelsFromCsv(std::string filename)
{   


    std::ifstream file(filename);
    if (!file)
    {
        std::cout << "ERREUR: models.csv introuvable\n";
        return;
    }

    std::string line;
    std::getline(file, line); 

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string name, powerStr, engineStr, image, priceStr;

        std::getline(ss, name, ';');
        std::getline(ss, powerStr, ';');
        std::getline(ss, engineStr, ';');
        std::getline(ss, image, ';');
        std::getline(ss, priceStr, ';');

        int power = std::stoi(powerStr);
        float price = std::stof(priceStr);

        Engine engine = Petrol;
        if (engineStr == "diesel") engine = Diesel;
        else if (engineStr == "electrique") engine = Electric;
        else if (engineStr == "hybride") engine = Hybrid;

        Model m(name.c_str(), power, engine, price);
        m.setImage(image);

        addModel(m);
    }

    file.close();
}

void Garage::importOptionsFromCsv(std::string filename)
{
    std::ifstream file(filename);
    if (!file)
        return;

    std::string line;
    std::getline(file, line); 

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string code, label, priceStr;

        std::getline(ss, code, ';');
        std::getline(ss, label, ';');
        std::getline(ss, priceStr, ';');

        float price = std::stof(priceStr);

        try
        {
            Option o;
            o.setCode(code);
            o.setLabel(label);
            o.setPrice(price);
            addOption(o);
        }
        catch (OptionException&)
        {
            
        }
    }

    file.close();
}

int Garage::getNbModels() const
{
    return models.size();
}

int Garage::getNbOptions() const
{
    return options.size();
}
int Garage::idLoggedEmployee = -1;

int Garage::getNbEmployees() const
{
    return employees.size();
}

void Garage::updateEmployee(const Employee& e)
{
    auto it = employees.find(e);
    if (it != employees.end())
    {
        employees.erase(it);
        employees.insert(e);
    }
}
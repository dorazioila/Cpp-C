#include "Garage.h"
#include <stdexcept>
#include <iterator>
#include <fstream>
#include <sstream>
#include "OptionException.h"
#include "XmlFileSerializer.hpp"
#include "Credentials.h"
#include <cstring>
using namespace carconfig;




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
    for (const Contract& c : contracts)
    {
        if (c.getClientId() == id)
            throw std::logic_error("Impossible de supprimer ce client : un contrat existe");
    }

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
    for (const Contract& c : contracts)
    {
        if (c.getVendeurId() == id)
            throw std::logic_error("Impossible de supprimer ce vendeur : un contrat existe");
    }

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
int Garage::idLoggedEmployee = -1;
void Garage::save()
{
    std::cout << ">>> Garage::save() APPELEE <<<" << std::endl;
    XmlFileSerializer<Employee> empSer("employees.xml",XmlFileSerializer<Employee>::WRITE, "employees");
    for (const Employee& e : employees)
    {
        std::cout << ">>> ecriture employees.xml <<<" << std::endl;

        empSer.write(e);
    }

   XmlFileSerializer<Client> cliSer("clients.xml",XmlFileSerializer<Client>::WRITE, "clients");
    for (const Client& c : clients)
    {   
        std::cout << ">>> ecriture client.xml <<<" << std::endl;
        cliSer.write(c);
    }

    XmlFileSerializer<Contract> conSer("contracts.xml",XmlFileSerializer<Contract>::WRITE,"contracts");
    for (const Contract& c : contracts)
    {
        conSer.write(c);
    }

    std::ofstream f("config.dat", std::ios::binary);
    if (!f) return;

    f.write((char*)&Actor::currentId, sizeof(int));

    int nb = employees.size();
    f.write((char*)&nb, sizeof(int));

    for (const Employee& e : employees)
    {
    Credentials c{};
    
    strncpy(c.login, e.getLogin().c_str(), sizeof(c.login) - 1);
    c.login[sizeof(c.login) - 1] = '\0';
    try {
        std::string pwd = e.getPassword();
        strncpy(c.password, pwd.c_str(), sizeof(c.password) - 1);
        c.password[sizeof(c.password) - 1] = '\0';
    }
    catch (...) {
        c.password[0] = '\0';
    }

    c.crypt();
    f.write(reinterpret_cast<char*>(&c), sizeof(Credentials));
    }

    f.close();
}

void Garage::load()
{
    if (!std::ifstream("employees.xml") || !std::ifstream("clients.xml") || !std::ifstream("config.dat"))
    {
        employees.clear();
        clients.clear();
        contracts.clear();

        int id = ++Actor::currentId;
        Employee admin("ADMIN", "ADMIN", id, "admin", "Administratif");
        employees.insert(admin);
        return;
    }

    

    XmlFileSerializer<Employee> empSer("employees.xml",XmlFileSerializer<Employee>::READ, "employees");
    employees.clear();
    try
    {
        while (true)
        {
            Employee e = empSer.read();
            employees.insert(e);
        }
    }
    catch (...) {}
    
    XmlFileSerializer<Client> cliSer("clients.xml",XmlFileSerializer<Client>::READ, "clients");
    clients.clear();
    try
    {
        while (true)
        {
            Client c = cliSer.read();
            clients.insert(c);
        }
    }
    catch (...) {}

    XmlFileSerializer<Contract> conSer("contracts.xml",XmlFileSerializer<Contract>::READ,"contracts");
    contracts.clear();
    try
    {
        while (true)
        {
            Contract c = conSer.read();
            contracts.insert(c);
        }
    }
    catch (...) {}

    std::ifstream f("config.dat", std::ios::binary);
    if (!f) return;
    f.read((char*)&Actor::currentId, sizeof(int));
    int nb;
    f.read((char*)&nb, sizeof(int));
    auto it = employees.begin();
    for (int i = 0; i < nb && it != employees.end(); ++i)
    {
        Credentials c;
        f.read((char*)&c, sizeof(Credentials));
        c.decrypt();
        if (strlen(c.password) > 0)
        {
            Employee e = *it;
            e.setPassword(c.password);
            auto toErase = it;
            ++it;
            employees.erase(toErase);
            employees.insert(e);
        }
        else
        {
            ++it;
        }
    }

    f.close();
}

int Garage::addContract(int vendeurId, int clientId, const std::string& projectName)
{
    int id = ++Actor::currentId;
    Contract c(id, vendeurId, clientId, projectName);
    contracts.insert(c);
    return id;
}

void Garage::deleteContractByIndex(int index)
{
    auto it = contracts.begin();
    std::advance(it, index);
    contracts.erase(it);
}

Contract Garage::findContractByIndex(int index) const
{
    auto it = contracts.begin();
    std::advance(it, index);
    return *it;
}

const std::set<Contract>& Garage::getContracts() const
{
    return contracts;
}

int Garage::getNbContracts() const
{
    return contracts.size();
}

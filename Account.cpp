#include "Account.h"
#include "client.h"

int Account::nextId = 1;

Account::Account(double balance, Client* owner) : id(nextId++), balance(balance), owner(owner) {}

Account::~Account() {}

int Account::getId() const 
{
    return id;
}

double Account::getBalance() const 
{
    return balance;
}

string Account::getOwnerName() const 
{
    return owner ? owner->getName() : "Неизвестно";
}

bool Account::deposit(double amount) 
{
    if (amount <= 0) return false;
    balance += amount;
    return true;
}

bool Account::withdraw(double amount) 
{
    if (amount <= 0 || amount > balance) return false;
    balance -= amount;
    return true;
}

void Account::save(ofstream& out) const 
{
    out << id << " " << balance << " ";
    out << (owner ? owner->getName() : "") << " ";
}

void Account::load(ifstream& in, vector<Client*>& clients) 
{
    in >> balance;
    string ownerName;
    in.ignore(); 
    getline(in, ownerName);

    owner = nullptr;
    for (size_t i = 0; i < clients.size(); i++) 
    {
        if (clients[i]->getName() == ownerName) 
        {
            owner = clients[i];
            break;
        }
    }
}
#include "Account.h"
#include "client.h"
#include "Savingsaccount.h"
#include <iostream>
#include <string>
#include <fstream>



int Account::nextId = 1;

void Account::LoadBase(ifstream& in, vector<Client*>& clients)
{
    in >> id >> balance;
    in >> ws;
    string ownerName;
    getline(in, ownerName);
    owner = nullptr;
    for (Client* client : clients)
    {
        if (client->getName() == ownerName)
        {
            owner = client;
            break;
        }
    }
}


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

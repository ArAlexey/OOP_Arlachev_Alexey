#pragma once
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Client;

class Account 
{
public:
    int id;
    double balance;
    Client* owner;
    static int nextId;
public:
    Account(double balance, Client* owner);
    virtual ~Account();

    int getId() const;
    double getBalance() const;
    string getOwnerName() const;

    virtual bool deposit(double amount);
    virtual bool withdraw(double amount);
    virtual void monthlyUpdate() = 0;
    virtual string getType() const = 0;
    virtual void save(ofstream& out) const;
    virtual void load(ifstream& in, vector<Client*>& clients);
};
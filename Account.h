#pragma once
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Client;

class Account 
{
protected:
    int id;
    double balance;
    Client* owner;
    void LoadBase(ifstream& in, vector<Client*>& clients);

public:

    static int nextId;
    Account(double balance, Client* owner);
    virtual ~Account();

    int getId() const;
    double getBalance() const;
    string getOwnerName() const;

    bool deposit(double amount);
    virtual bool withdraw(double amount);
    virtual void monthlyUpdate() = 0;
    virtual string getType() const = 0;
    virtual void save(ofstream& out) const = 0;
    virtual void load(ifstream& in, vector<Client*>& clients) = 0;
};

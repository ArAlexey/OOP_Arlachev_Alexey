#include "savingsaccount.h"

SavingsAccount::SavingsAccount(double balance, Client* owner, double interestRate) : Account(balance, owner), interestRate(interestRate) {}

void SavingsAccount::monthlyUpdate() 
{
    balance += balance * interestRate;
}

string SavingsAccount::getType() const 
{
    return "Накопительный";
}

void SavingsAccount::save(ofstream& out) const 
{
    out << "S ";
    Account::save(out);
    out << interestRate << endl;
}

void SavingsAccount::load(ifstream& in, vector<Client*>& clients) 
{
    Account::load(in, clients);
    in >> interestRate;
}
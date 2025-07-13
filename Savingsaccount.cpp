#include "savingsaccount.h"
#include "client.h"

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
    out << "S " << id << " " << balance << " " << owner->getName() << " " << interestRate << "\n"; // ИЗМЕНЕНО
}

void SavingsAccount::load(ifstream& in, vector<Client*>& clients) 
{
    in >> id >> balance;
    string ownerName;
    in >> ownerName >> interestRate;

    owner = nullptr;
    for (Client* c : clients) {
        if (c->getName() == ownerName) {
            owner = c;
            break;
        }
    }
}

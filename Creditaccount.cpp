#include "creditaccount.h"
#include "client.h"

CreditAccount::CreditAccount(double balance, Client* owner, double commissionRate, double creditLimit) : Account(balance, owner), commissionRate(commissionRate), creditLimit(creditLimit) {}

bool CreditAccount::withdraw(double amount) 
{
    if (amount <= 0 || amount > (balance + creditLimit)) return false;
    balance -= amount;
    return true;
}

void CreditAccount::monthlyUpdate() 
{
    if (balance < 0) {
        double commission = -balance * commissionRate;
        balance -= commission;
    }
}

string CreditAccount::getType() const 
{
    return "Кредитный";
}

void CreditAccount::save(ofstream& out) const 
{
    out << "C " << id << " " << balance << " " << owner->getName() << " "
        << commissionRate << " " << creditLimit << "\n"; // ИЗМЕНЕНО
}

void CreditAccount::load(ifstream& in, vector<Client*>& clients) 
{
    in >> id >> balance;
    string ownerName;
    in >> ownerName >> commissionRate >> creditLimit;

    owner = nullptr;
    for (Client* c : clients) {
        if (c->getName() == ownerName) {
            owner = c;
            break;
        }
    }
}

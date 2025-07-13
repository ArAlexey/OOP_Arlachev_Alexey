#pragma once
#include "account.h"

class CreditAccount : public Account 
{
    double commissionRate;
    double creditLimit;
public:
    CreditAccount(double balance, Client* owner, double commissionRate = 0.02, double creditLimit = 10000);
    bool withdraw(double amount) override;
    void monthlyUpdate() override;
    string getType() const override;
    void save(ofstream& out) const override;
    void load(ifstream& in, vector<Client*>& clients) override;
};
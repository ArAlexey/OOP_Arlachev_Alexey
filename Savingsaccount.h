#pragma once
#include "account.h"

class SavingsAccount : public Account 
{
    double interestRate;
public:
    SavingsAccount(double balance, Client* owner, double interestRate = 0.05);
    void monthlyUpdate() override;
    string getType() const override;
    void save(ofstream& out) const override;
    void load(ifstream& in, vector<Client*>& clients) override;
};
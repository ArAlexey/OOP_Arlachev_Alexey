#pragma once
#include <vector>
#include <string>

using namespace std;

class Client;
class Account;

class BankSystem 
{
    vector<Client*> clients;
    vector<Account*> accounts;

    void saveToFile(const string& filename);
    void loadFromFile(const string& filename);
    Account* findAccount(int id);

public:
    BankSystem();
    ~BankSystem();

    void createClient();
    void createSavingsAccount();
    void createCreditAccount();
    void deposit();
    void withdraw();
    void viewAllAccounts() const;
    void monthlyUpdate();
    void findClientAccounts() const;
};
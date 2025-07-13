#include "banksystem.h"
#include "client.h"
#include "Account.h"
#include "savingsaccount.h"
#include "creditaccount.h"
#include <iostream>
#include <fstream>
#include <limits>

BankSystem::BankSystem() 
{
    loadFromFile("bank_data.txt");
}

BankSystem::~BankSystem() 
{
    saveToFile("bank_data.txt");

    for (size_t i = 0; i < accounts.size(); i++) 
    {
        delete accounts[i];
    }

    for (size_t i = 0; i < clients.size(); i++) 
    {
        delete clients[i];
    }
}

void BankSystem::saveToFile(const string& filename)
{
    ofstream out(filename);
    if (!out)
    {
        cerr << "������ �������� ����� ��� ������\n";
        return;
    }

    out << clients.size() << endl;
    for (size_t i = 0; i < clients.size(); i++)
    {
        out << clients[i]->getName() << endl;
    }

    out << accounts.size() << endl;
    for (size_t i = 0; i < accounts.size(); i++)
    {
        accounts[i]->save(out);
    }

    out.close();
}


void BankSystem::loadFromFile(const string& filename)
{
    ifstream in(filename);
    if (!in) 
    {
        cerr << "��� ����������� ������\n";
        return;
    }

    for (size_t i = 0; i < accounts.size(); i++) delete accounts[i];
    for (size_t i = 0; i < clients.size(); i++) delete clients[i];
    clients.clear();
    accounts.clear();

    int clientCount;
    in >> clientCount;
    in.ignore(); 
    for (int i = 0; i < clientCount; ++i) 
    {
        string name;
        getline(in, name);
        if (!name.empty()) 
        {
            clients.push_back(new Client(name));
        }
    }

    int accountCount;
    in >> accountCount;
    in.ignore(); 
    int maxId = 0;
    for (int i = 0; i < accountCount; ++i) {
        char type;
        in >> type;
        in.ignore();

        Account* account = nullptr;
        if (type == 'S') 
        {
            account = new SavingsAccount(0, nullptr);
        }
        else if (type == 'C') 
        {
            account = new CreditAccount(0, nullptr);
        }

        if (account) 
        {
            account->load(in, clients);
            accounts.push_back(account);
            if (account->getId() > maxId) 
            {
                maxId = account->getId();
            }
        }
    }

    if (maxId > 0) 
    {
        Account::nextId = maxId + 1;
    }

    in.close();
    cout << "������ ������� ���������\n";
}


void BankSystem::createClient() 
{
    cout << "������� ��� �������: ";
    string name;
    cin.ignore();
    getline(cin, name);

    clients.push_back(new Client(name));
    cout << "������ ������� ������\n";
}

void BankSystem::createSavingsAccount() 
{
    if (clients.empty()) 
    {
        cout << "��� ��������� ��������. ������� �������� �������.\n";
        return;
    }

    cout << "�������� �������:\n";
    for (size_t i = 0; i < clients.size(); ++i) 
    {
        cout << i + 1 << ". " << clients[i]->getName() << endl;
    }

    int clientChoice;
    cin >> clientChoice;

    if (clientChoice < 1 || clientChoice >(int)clients.size()) 
    {
        cout << "�������� ����� �������\n";
        return;
    }

    cout << "������� ��������� �������: ";
    double amount;
    cin >> amount;

    if (amount <= 0) 
    {
        cout << "�������� �����\n";
        return;
    }

    accounts.push_back(new SavingsAccount(amount, clients[clientChoice - 1]));
    cout << "������������� ���� ������� ������. ID �����: " << accounts.back()->getId() << endl;
}

void BankSystem::createCreditAccount() 
{
    if (clients.empty()) 
    {
        cout << "��� ��������� ��������. ������� �������� �������.\n";
        return;
    }

    cout << "�������� �������:\n";
    for (size_t i = 0; i < clients.size(); ++i) 
    {
        cout << i + 1 << ". " << clients[i]->getName() << endl;
    }

    int clientChoice;
    cin >> clientChoice;

    if (clientChoice < 1 || clientChoice >(int)clients.size()) 
    {
        cout << "�������� ����� �������\n";
        return;
    }

    cout << "������� ��������� ������: ";
    double amount;
    cin >> amount;

    accounts.push_back(new CreditAccount(amount, clients[clientChoice - 1]));
    cout << "��������� ���� ������� ������. ID �����: "
        << accounts.back()->getId() << endl;
}

void BankSystem::deposit() 
{
    cout << "������� ����� �����: ";
    int id;
    cin >> id;

    Account* account = findAccount(id);
    if (!account) 
    {
        cout << "���� �� ������\n";
        return;
    }

    cout << "������� ����� ��� ����������: ";
    double amount;
    cin >> amount;

    if (account->deposit(amount)) 
    {
        cout << "���������� �������. ����� ������: " << account->getBalance() << endl;
    }
    else 
    {
        cout << "�������� ����� ��� ����������\n";
    }
}

void BankSystem::withdraw() 
{
    cout << "������� ����� �����: ";
    int id;
    cin >> id;

    Account* account = findAccount(id);
    if (!account) 
    {
        cout << "���� �� ������\n";
        return;
    }

    cout << "������� ����� ��� ������: ";
    double amount;
    cin >> amount;

    if (account->withdraw(amount)) 
    {
        cout << "������ �������. ����� ������: " << account->getBalance() << endl;
    }
    else 
    {
        cout << "�������� ����� ��� ������ ��� ������������ �������\n";
    }
}

void BankSystem::viewAllAccounts() const 
{
    if (accounts.empty()) 
    {
        cout << "��� ��������� ������\n";
        return;
    }

    cout << "��� �����:\n";
    for (size_t i = 0; i < accounts.size(); i++) 
    {
        cout << "����� �����: " << accounts[i]->getId() << ", ���: " << accounts[i]->getType() << ", ��������: " << accounts[i]->getOwnerName() << ", ������: " << accounts[i]->getBalance() << endl;
    }
}

void BankSystem::monthlyUpdate() 
{
    for (size_t i = 0; i < accounts.size(); i++) 
    {
        accounts[i]->monthlyUpdate();
    }
    cout << "����������� ���������� ��������� ��� ���� ������\n";
}

void BankSystem::findClientAccounts() const 
{
    cout << "������� ��� �������: ";
    string name;
    cin.ignore();
    getline(cin, name);

    bool found = false;
    for (size_t i = 0; i < accounts.size(); i++) 
    {
        if (accounts[i]->getOwnerName() == name) 
        {
            cout << "����� �����: " << accounts[i]->getId()
                << ", ���: " << accounts[i]->getType()
                << ", ������: " << accounts[i]->getBalance() << endl;
            found = true;
        }
    }

    if (!found) 
    {
        cout << "�� ������� ������ ��� �������: " << name << endl;
    }
}

Account* BankSystem::findAccount(int id) 
{
    for (size_t i = 0; i < accounts.size(); i++) 
    {
        if (accounts[i]->getId() == id) 
        {
            return accounts[i];
        }
    }
    return nullptr;
}
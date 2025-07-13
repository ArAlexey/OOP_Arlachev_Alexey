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
        cerr << "Ошибка открытия файла для записи\n";
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
        cerr << "Нет сохраненных данных\n";
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
    cout << "Данные успешно загружены\n";
}


void BankSystem::createClient() 
{
    cout << "Введите имя клиента: ";
    string name;
    cin.ignore();
    getline(cin, name);

    clients.push_back(new Client(name));
    cout << "Клиент успешно создан\n";
}

void BankSystem::createSavingsAccount() 
{
    if (clients.empty()) 
    {
        cout << "Нет доступных клиентов. Сначала создайте клиента.\n";
        return;
    }

    cout << "Выберите клиента:\n";
    for (size_t i = 0; i < clients.size(); ++i) 
    {
        cout << i + 1 << ". " << clients[i]->getName() << endl;
    }

    int clientChoice;
    cin >> clientChoice;

    if (clientChoice < 1 || clientChoice >(int)clients.size()) 
    {
        cout << "Неверный выбор клиента\n";
        return;
    }

    cout << "Введите начальный депозит: ";
    double amount;
    cin >> amount;

    if (amount <= 0) 
    {
        cout << "Неверная сумма\n";
        return;
    }

    accounts.push_back(new SavingsAccount(amount, clients[clientChoice - 1]));
    cout << "Накопительный счет успешно создан. ID счета: " << accounts.back()->getId() << endl;
}

void BankSystem::createCreditAccount() 
{
    if (clients.empty()) 
    {
        cout << "Нет доступных клиентов. Сначала создайте клиента.\n";
        return;
    }

    cout << "Выберите клиента:\n";
    for (size_t i = 0; i < clients.size(); ++i) 
    {
        cout << i + 1 << ". " << clients[i]->getName() << endl;
    }

    int clientChoice;
    cin >> clientChoice;

    if (clientChoice < 1 || clientChoice >(int)clients.size()) 
    {
        cout << "Неверный выбор клиента\n";
        return;
    }

    cout << "Введите начальный баланс: ";
    double amount;
    cin >> amount;

    accounts.push_back(new CreditAccount(amount, clients[clientChoice - 1]));
    cout << "Кредитный счет успешно создан. ID счета: "
        << accounts.back()->getId() << endl;
}

void BankSystem::deposit() 
{
    cout << "Введите номер счета: ";
    int id;
    cin >> id;

    Account* account = findAccount(id);
    if (!account) 
    {
        cout << "Счет не найден\n";
        return;
    }

    cout << "Введите сумму для пополнения: ";
    double amount;
    cin >> amount;

    if (account->deposit(amount)) 
    {
        cout << "Пополнение успешно. Новый баланс: " << account->getBalance() << endl;
    }
    else 
    {
        cout << "Неверная сумма для пополнения\n";
    }
}

void BankSystem::withdraw() 
{
    cout << "Введите номер счета: ";
    int id;
    cin >> id;

    Account* account = findAccount(id);
    if (!account) 
    {
        cout << "Счет не найден\n";
        return;
    }

    cout << "Введите сумму для снятия: ";
    double amount;
    cin >> amount;

    if (account->withdraw(amount)) 
    {
        cout << "Снятие успешно. Новый баланс: " << account->getBalance() << endl;
    }
    else 
    {
        cout << "Неверная сумма для снятия или недостаточно средств\n";
    }
}

void BankSystem::viewAllAccounts() const 
{
    if (accounts.empty()) 
    {
        cout << "Нет доступных счетов\n";
        return;
    }

    cout << "Все счета:\n";
    for (size_t i = 0; i < accounts.size(); i++) 
    {
        cout << "Номер счета: " << accounts[i]->getId() << ", Тип: " << accounts[i]->getType() << ", Владелец: " << accounts[i]->getOwnerName() << ", Баланс: " << accounts[i]->getBalance() << endl;
    }
}

void BankSystem::monthlyUpdate() 
{
    for (size_t i = 0; i < accounts.size(); i++) 
    {
        accounts[i]->monthlyUpdate();
    }
    cout << "Ежемесячное обновление выполнено для всех счетов\n";
}

void BankSystem::findClientAccounts() const 
{
    cout << "Введите имя клиента: ";
    string name;
    cin.ignore();
    getline(cin, name);

    bool found = false;
    for (size_t i = 0; i < accounts.size(); i++) 
    {
        if (accounts[i]->getOwnerName() == name) 
        {
            cout << "Номер счета: " << accounts[i]->getId()
                << ", Тип: " << accounts[i]->getType()
                << ", Баланс: " << accounts[i]->getBalance() << endl;
            found = true;
        }
    }

    if (!found) 
    {
        cout << "Не найдено счетов для клиента: " << name << endl;
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
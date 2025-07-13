#include "banksystem.h"
#include <iostream>
#include <limits>

using namespace std;

void displayMenu() 
{
    cout << "Меню банковской системы:" << endl;
    cout << "1. Создать клиента" << endl;
    cout << "2. Открыть накопительный счет" << endl;
    cout << "3. Открыть кредитный счет" << endl;
    cout << "4. Пополнить счет" << endl;
    cout << "5. Снять средства" << endl;
    cout << "6. Просмотреть все счета" << endl;
    cout << "7. Ежемесячное обновление" << endl;
    cout << "8. Найти счета клиента" << endl;
    cout << "0. Выход" << endl;
    cout << "Введите ваш выбор: " << endl;
}

int main() 
{
    setlocale(LC_ALL, "RU");
    BankSystem bank;
    int choice;

    do 
    {
        displayMenu();
        cin >> choice;

        if (choice < 0 || choice > 8) 
        {
            cin.clear();
            cout << "Неверный ввод. Пожалуйста, введите число.\n";
            continue;
        }

        switch (choice) 
        {
            case 1: 
            {
                bank.createClient(); 
                break;
            }
            case 2: 
            {
                bank.createSavingsAccount(); 
                break;
            }
            case 3: 
            {
                bank.createCreditAccount(); 
                break;
            }
            case 4: 
            {
                bank.deposit(); 
                break;
            }
            case 5: 
            {
                bank.withdraw(); 
                break;
            }
            case 6: 
            {
                bank.viewAllAccounts(); 
                break;
            }
            case 7: 
            {
                bank.monthlyUpdate(); 
                break;
            }
            case 8: 
            {
                bank.findClientAccounts(); 
                break;
            }
            case 0: 
            {
                cout << "Выход...\n"; 
                break;
            }
            default: 
            {
                cout << "Неверный выбор. Попробуйте снова.\n";
            }
        }
    } while (choice != 0);

return 0;
}
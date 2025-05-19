typedef unsigned long long int ull;

#include <iostream>
#include <vector>
#include <string>
#include <limits>

class Account
{
private:
    std::string login;
    unsigned int accountNumber;
    double balance;
    ull passwordHashed;

    static ull hashPassword(unsigned int password)
    {
        return password * 2654435761;
    }

public:
    Account(std::string login, unsigned int accountNumber, unsigned int password, double balance = 0.0)
    {
        this->login = login;
        this->accountNumber = accountNumber;
        this->passwordHashed = hashPassword(password);
        this->balance = balance;
    }

    bool checkPassword(unsigned int password) const
    {
        return hashPassword(password) == passwordHashed;
    }

    std::string getLogin() const
    {
        return login;
    }
    unsigned int getAccountNumber() const
    {
        return accountNumber;
    }
    double getBalance() const
    {
        return balance;
    }
    void deposit(double amount)
    {
        balance += amount;
    }
    bool withdraw(double amount)
    {
        if (amount > balance)
            return false;
        balance -= amount;
        return true;
    }
};

class AccountDatabase
{
private:
    std::vector<Account> accounts;

public:
    void addAccount(const Account &account)
    {
        accounts.push_back(account);
    }

    Account *findAccountByLogin(const std::string &login)
    {
        for (Account &account : accounts)
        {
            if (account.getLogin() == login)
            {
                return &account;
            }
        }
        return 0;
    }

    Account *findAccountByNumber(unsigned int accountNumber)
    {
        for (Account &account : accounts)
        {
            if (account.getAccountNumber() == accountNumber)
            {
                return &account;
            }
        }
        return 0;
    }

    bool validClient(const std::string &login, unsigned int password)
    {
        Account *account = findAccountByLogin(login);
        if (account == 0)
            return false;
        return account->checkPassword(password);
    }

    void personalCabinet(Account *account)
    {
        while (true)
        {
            std::cout << "\nЛичный кабинет: " << account->getLogin() << std::endl;
            std::cout << "1. Показать баланс\n";
            std::cout << "2. Пополнить счет\n";
            std::cout << "3. Перевести деньги\n";
            std::cout << "4. Выйти из аккаунта\n";
            std::cout << "5. Завершить сеанс\n";
            std::cout << "Выберите действие: ";

            int choice;
            std::cin >> choice;

            switch (choice)
            {
            case 1:
            {
                std::cout << "Ваш баланс: " << account->getBalance() << std::endl;
                break;
            }
            case 2:
            {
                std::cout << "Введите сумму для пополнения: ";
                double amount;
                std::cin >> amount;
                if (amount > 0)
                {
                    account->deposit(amount);
                    std::cout << "Счет успешно пополнен. Новый баланс: " << account->getBalance() << std::endl;
                }
                else
                {
                    std::cout << "Неверная сумма!" << std::endl;
                }
                break;
            }
            case 3:
            {
                std::cout << "Введите номер счета получателя: ";
                unsigned int recipientNumber;
                std::cin >> recipientNumber;

                if (recipientNumber == account->getAccountNumber())
                {
                    std::cout << "Нельзя переводить деньги на свой же счет!" << std::endl;
                    break;
                }

                Account *recipient = findAccountByNumber(recipientNumber);
                if (recipient == 0)
                {
                    std::cout << "Счет получателя не найден!" << std::endl;
                    break;
                }

                std::cout << "Введите сумму для перевода: ";
                double amount;
                std::cin >> amount;

                if (amount <= 0)
                {
                    std::cout << "Неверная сумма!" << std::endl;
                }
                else if (account->withdraw(amount))
                {
                    recipient->deposit(amount);
                    std::cout << "Перевод успешно выполнен. Новый баланс: " << account->getBalance() << std::endl;
                }
                else
                {
                    std::cout << "Недостаточно средств на счете!" << std::endl;
                }
                break;
            }
            case 4:
            {
                return;
            }
            case 5:
            {
                exit(0);
            }
            default:
            {
                std::cout << "Неверный выбор!" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            }
        }
    }
};

void generateTestData(AccountDatabase &db, int count)
{
    for (int i = 0; i < count; i++)
    {
        std::string login = "user" + std::to_string(i);
        unsigned int accountNumber = 9000 + i;
        unsigned int password = i + 9900;
        double balance = (i + 1) * 1000;

        db.addAccount(Account(login, accountNumber, password, balance));
    }
}

int main()
{
    AccountDatabase MMFBank;

    generateTestData(MMFBank, 5); // юзеры генерируются в формате "user${i}" + password(9900 + i)

    while (true)
    {
        std::cout << "Логин: ";
        std::cout << "\nМеfMat Bank - Вход в систему\n";
        std::cout << "Логин: ";
        std::string login;
        std::cin >> login;

        std::cout << "Пароль: ";
        unsigned int password;
        std::cin >> password;

        if (MMFBank.validClient(login, password))
        {
            Account *account = MMFBank.findAccountByLogin(login);
            MMFBank.personalCabinet(account);
        }
        else
        {
            std::cout << "Неверный логин или пароль!" << std::endl;
        }
    }

    return 0;
}
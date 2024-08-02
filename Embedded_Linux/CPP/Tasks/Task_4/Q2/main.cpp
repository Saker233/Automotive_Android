#include "Account.h"
#include <iostream>

int main()
{
    std::cout << "Initial account information:" << std::endl;
    Account::displayAccountInfos();

    std::cout << "\nCreating first account with an initial deposit of 1000:" << std::endl;
    Account account1(1000);
    account1.displayStatus();
    Account::displayAccountInfos();

    std::cout << "\nCreating second account with an initial deposit of 500:" << std::endl;
    Account account2(500);
    account2.displayStatus();
    Account::displayAccountInfos();

    std::cout << "\nMaking a deposit of 200 to the first account:" << std::endl;
    account1.makeDeposit(200);
    account1.displayStatus();
    Account::displayAccountInfos();

    std::cout << "\nMaking a withdrawal of 300 from the second account:" << std::endl;
    if (account2.makeWithdrawal(300))
    {
        std::cout << "Withdrawal successful." << std::endl;
    }
    else
    {
        std::cout << "Withdrawal failed." << std::endl;
    }
    account2.displayStatus();
    Account::displayAccountInfos();

    std::cout << "\nAttempting to withdraw 1500 from the first account (should fail):" << std::endl;
    if (account1.makeWithdrawal(1500))
    {
        std::cout << "Withdrawal successful." << std::endl;
    }
    else
    {
        std::cout << "Withdrawal failed." << std::endl;
    }
    account1.displayStatus();
    Account::displayAccountInfos();

    std::cout << "\nClosing the accounts." << std::endl;

    return 0;
}
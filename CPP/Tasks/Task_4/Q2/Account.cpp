#include "Account.h"
#include <iostream>

int Account::m_noOfAccounts = 0;
int Account::m_totalAmount = 0;
int Account::m_totalNbDeposits = 0;
int Account::m_totalNbWithdrawals = 0;

Account::Account(int initial_deposit)
    : m_accountIndex(m_noOfAccounts++), m_amount(initial_deposit), m_noOfDeposits(0), m_noOfWithdrawals(0)
{
    m_totalAmount += initial_deposit;
    std::cout << "Account created with initial deposit: " << initial_deposit << std::endl;
}

Account::~Account()
{
    m_totalAmount -= m_amount;
    m_noOfAccounts--;
    std::cout << "Account closed" << std::endl;
}

// Static member functions
int Account::getNoOfAccounts(void)
{
    return m_noOfAccounts;
}

int Account::getTotalAmount(void)
{
    return m_totalAmount;
}

int Account::getNbDeposits(void)
{
    return m_totalNbDeposits;
}

int Account::getNoOfWithdrawal(void)
{
    return m_totalNbWithdrawals;
}

void Account::displayAccountInfos(void)
{
    std::cout << "Accounts: " << m_noOfAccounts << std::endl;
    std::cout << "Total Amount: " << m_totalAmount << std::endl;
    std::cout << "Total Deposits: " << m_totalNbDeposits << std::endl;
    std::cout << "Total Withdrawals: " << m_totalNbWithdrawals << std::endl;
}

// Member functions
void Account::makeDeposit(int deposit)
{
    m_amount += deposit;
    m_noOfDeposits++;
    m_totalAmount += deposit;
    m_totalNbDeposits++;
    std::cout << "Deposit made: " << deposit << std::endl;
}

bool Account::makeWithdrawal(int withdrawal)
{
    if (withdrawal > m_amount)
    {
        std::cout << "Withdrawal failed: insufficient funds" << std::endl;
        return false;
    }
    m_amount -= withdrawal;
    m_noOfWithdrawals++;
    m_totalAmount -= withdrawal;
    m_totalNbWithdrawals++;
    std::cout << "Withdrawal made: " << withdrawal << std::endl;
    return true;
}

int Account::checkAmount() const
{
    return m_amount;
}

void Account::displayStatus(void) const
{
    std::cout << "Account " << m_accountIndex << std::endl;
    std::cout << "Amount: " << m_amount << std::endl;
    std::cout << "Deposits: " << m_noOfDeposits << std::endl;
    std::cout << "Withdrawals: " << m_noOfWithdrawals << std::endl;
}

// Private default constructor
Account::Account()
{
}

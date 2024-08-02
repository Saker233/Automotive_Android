#ifndef _ACCOUNT_H_
#define _ACCOUNT_H_

class Account
{
    static int m_noOfAccounts;
    static int m_totalAmount;
    static int m_totalNbDeposits;
    static int m_totalNbWithdrawals;

    int m_accountIndex;
    int m_amount;
    int m_noOfDeposits;
    int m_noOfWithdrawals;

    Account();

public:
    static int getNoOfAccounts(void);
    static int getTotalAmount(void);
    static int getNbDeposits(void);
    static int getNoOfWithdrawal(void);
    static void displayAccountInfos(void);

    Account(int initial_deposit);
    ~Account();

    void makeDeposit(int deposit);
    bool makeWithdrawal(int withdrawal);
    int checkAmount() const;
    void displayStatus(void) const;
};

#endif // !_ACCOUNT_H_
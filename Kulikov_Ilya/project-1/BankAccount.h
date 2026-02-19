#ifndef BANKACCOUNT_h
#define BANKACCOUNT_h

#include "useful-types.h"

class IBankAccount {
  protected:
    enum BankType {
        NoType,
        Giro,
        Deposit,
    };
    virtual const BankType type() = 0;

    String bank_name;
    RUB_Kopecks value;

  public:
    virtual void update_account() = 0;

    String get_bank_name() const { return bank_name; }
    RUB_Kopecks &get_account() { return value; }
    RUB_Kopecks account() const { return value; }

    virtual ~IBankAccount() = 0;
};

class Giro : public IBankAccount {
  private:
    void update_account() {}

  public:
    const BankType type() { return BankType::Giro; }

    Giro(String name_of_bank, RUB_Kopecks initial) {
        bank_name = name_of_bank;
        value = initial;
    }

    ~Giro() {}
};

class Deposit : public IBankAccount {
    Percent interest;

  public:
    const BankType type() { return BankType::Deposit; }

    Deposit(String name_of_bank, RUB_Kopecks initial, Percent interest)
        : interest(interest) {
        bank_name = name_of_bank;
        value = initial;
    }

    void update_account() { value *= 1 + interest / 100.0; }

    ~Deposit() {}
};

#endif

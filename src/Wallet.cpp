#include <limits>

#include "Wallet.hpp"

Wallet::Wallet(int64_t balance) : balance_(balance)
{
}

bool Wallet::debit(int64_t amount)
{
    if (amount < 0)
    {
        return false;
    }

    if (amount > balance_)
    {
        return false;
    }

    balance_ -= amount;

    return true;
}

bool Wallet::credit(int64_t amount)
{
    if (amount < 0)
    {
        return false;
    }

    if (amount > std::numeric_limits<int64_t>::max() - balance_)
    {
        return false;
    }

    balance_ += amount;

    return true;
}

int64_t Wallet::getBalance() const
{
    return balance_;
}

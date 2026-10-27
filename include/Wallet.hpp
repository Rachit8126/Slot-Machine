#pragma once

#include <cstdint>

class Wallet
{
private:
    int64_t balance_;

public:
    explicit Wallet(int64_t balance);

    bool debit(int64_t amount);
    bool credit(int64_t amount);

    int64_t getBalance() const;
};

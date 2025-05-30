#include "Account.h"

Account::Account(Customer *customer, Bank::AccountType type)
{
}

Bank::AccountType Account::accountType(std::string accountId)
{
}

Account::~Account()
{
}

std::string Account::getId() const
{
}

float Account::getBalance() const
{
}

void Account::transact(float amount)
{
}

Poco::JSON::Object::Ptr Account::toJson() const
{
}

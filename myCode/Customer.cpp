#include "Customer.h"

Customer::Customer(unsigned int number) : number{number}
{
}

unsigned int Customer::getNumber() const
{
    return number;
}

std::string Customer::getId() const
{
}

Customer* Customer::setPersonalData(std::string lastName, std::string firstName, Poco::Data::Date dateOfBirth)
{
}

const Poco::Data::Date& Customer::getDateOfBirth() const
{
}

const std::string& Customer::getFirstName() const
{
}

const std::string& Customer::getLastName() const
{
}

Account* Customer::createAccount(Bank::AccountType type)
{
}

std::vector<Account*> Customer::allAccounts() const
{
}

Account* Customer::lookupAccount(std::string id) const
{
}

void Customer::deleteAccount(std::string id)
{
}

std::ostream& operator <<(std::ostream &out, const Customer &customer)
{
}

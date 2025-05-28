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
    std::string id;
    int digits = 0;
    while(number != 0)
    {
        number/=10;
        digits++;
    }
    //get the number of digits in number attribute
    while(id.length() <= (10-digits) )
    {
        id+= "0";
    }

    id+= std::to_string(number);
    return id;
}

Customer* Customer::setPersonalData(std::string lastName, std::string firstName, Poco::Data::Date dateOfBirth) : lastName{lastName}, firstName{firstName}, dateOfBirth{dateOfBirth}
{
}

const Poco::Data::Date& Customer::getDateOfBirth() const
{
    return dateOfBirth;
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

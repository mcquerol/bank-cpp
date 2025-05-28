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

Customer* Customer::setPersonalData(std::string lastName, std::string firstName, Poco::Data::Date dateOfBirth)
{
    this->lastName = lastName;
    this->firstName = firstName;
    this->dateOfBirth = dateOfBirth;

    return this;
}

const Poco::Data::Date& Customer::getDateOfBirth() const
{
    return dateOfBirth;
}

const std::string& Customer::getFirstName() const
{
    return firstName;
}

const std::string& Customer::getLastName() const
{
    return lastName;
}

Account* Customer::createAccount(Bank::AccountType type)
{
    Account* acc(this,type);
    return acc;
}

std::vector<Account*> Customer::allAccounts() const
{
    std::vector<Account*> accountsVector;
    for(auto account : accounts)
    {
        accountsVector.emplace_back(account.second.get());
    }
    return accountsVector;
}

Account* Customer::lookupAccount(std::string id) const
{
    if(accounts[id] == nullptr)
    {
        throw std::invalid_argument("id does not exist!");
    }
    return accounts[id];
}

void Customer::deleteAccount(std::string id)
{
    auto it = accounts.find(id);

    if(it == nullptr)
    {
        throw std::invalid_argument("id does not exist!");
    }
    if(it->second->getBalance() != 0)
    {
        throw std::logic_error("Balance is not 0!");
    }
    else
    {
        it = nullptr;
    }
}

std::ostream& operator <<(std::ostream &out, const Customer &customer)
{
}

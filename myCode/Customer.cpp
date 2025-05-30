#include "Customer.h"
#include "Account.h"

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
    int tempNumber = number;
    while(tempNumber != 0)
    {
        tempNumber/=10;
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
    auto acc = std::make_unique<Account>(this, type);  // create unique_ptr
    Account* rawPtr = acc.get();                       // get raw pointer before moving
    accounts[rawPtr->getId()] = std::move(acc);        // store in map
    return rawPtr;
}

std::vector<Account*> Customer::allAccounts() const
{
    std::vector<Account*> accountsVector;
    for(const auto& account : accounts)
    {
        accountsVector.emplace_back(account.second.get());
    }
    return accountsVector;
}

Account* Customer::lookupAccount(std::string id) const
{
    auto accountPtr = accounts.at(id).get();

    if(accountPtr == nullptr)
    {
        throw std::invalid_argument("id does not exist!");
    }
    return accountPtr;
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
        *it = nullptr;
    }
}

std::ostream& operator<<(std::ostream &out, const Customer &customer)
{
    out << customer.getId() << ": "
        << customer.getLastName() << ", "
        << customer.getFirstName() << " ("
        << customer.getDateOfBirth().day() << "/"
        << customer.getDateOfBirth().month() << "/"
        << customer.getDateOfBirth().year() << ")\n";

    return out;
}

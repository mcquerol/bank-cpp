#include "Bank.h"
#include "Customer.h"

Customer* Bank::createCustomer()
{
    auto customer = std::make_unique<Customer>(nextCustomerNumber);
    customers.emplace(customer);
    nextCustomerNumber++;
    return customer;
}

Customer* Bank::lookupCustomer(std::string id) const
{
    return customers.at(id).get();
}

std::vector<Customer*> Bank::allCustomers() const
{
    std::vector<Customer*> customerVector;
    for(const auto &customer : customers)
    {
        customerVector.emplace_back(customer.second.get());
    }
    return customerVector;
}

#include "Bank.h"

Customer* Bank::createCustomer()
{
    Customer* customer(nextCustomerNumber);
    std::unique_ptr<Customer> customerPtr = std::make_unique<Customer>(customer);
    customers.emplace(customerPtr);
    nextCustomerNumber++;
    return customer;
}

Customer* Bank::lookupCustomer(std::string id) const
{
    return customers[id];
}

std::vector<Customer*> Bank::allCustomers() const
{
    std::vector<Customer*> customerVector;
    for(auto customer : customers)
    {
        customerVector.emplace_back(customer.second.get());
    }
    return customerVector;
}

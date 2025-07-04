
#include <iostream>
#include <sstream>
#include <set>
#include <Poco/JSON/Stringifier.h>

using namespace std;

#include "Bank.h"
#include "Customer.h"
#include "Account.h"
#include "CurrentAccount.h"
#include "SavingsAccount.h"
#include "CDAccount.h"

/**
 * Outputs the failedMessage on the console if condition is false.
 *
 * @param condition the condition
 * @param failedMessage the message
 */
void assertTrue(bool condition, string failedMessage) {
    if (!condition) {
        cout << failedMessage << endl;
    }
}

/**
 * Initializes a bank with customers with different account
 * types. Can be used as data for various tests.
 */
void setupBank(Bank& bank) {
    // The following code has been commented out to keep
    // the start project buildable. Remove the comments
    // when you have implemented the required methods.

    /********* reactivate later *********
    Customer* c = bank.createCustomer()->setPersonalData
            ("Angel", "Alice", Poco::Data::Date(1991, 1, 1));
    c->createAccount(Bank::AccountType::Current)->transact(100);
    c->createAccount(Bank::AccountType::Savings)->transact(500);
    c->createAccount(Bank::AccountType::CD)->transact(1000);
    c->createAccount(Bank::AccountType::CD)->transact(2000);
    c->createAccount(Bank::AccountType::CD)->transact(3000);
    bank.createCustomer()->setPersonalData
            ("Billings", "Bob", Poco::Data::Date(1992, 2, 2));
    bank.createCustomer()->setPersonalData
            ("Chase", "Caesar", Poco::Data::Date(1993, 3, 3));
    ************************************/
}

void bankTests () {
    /**
     * Create a bank and initialize it with setupBank.
     */
    // Add your code here:
        Bank bank;
        setupBank(bank);

    /*
     * (1) Assert that the bank has three customers.
     */
    // Add your code here:
        auto customerCountQuery = bank.allCustomers().size();
        assertTrue(customerCountQuery == 3, "bank does not have 3 customers");

   /*
    * (2) Assert that the customer with id 0000000002 can be looked up.
    */
    // Add your code here:
        auto customerIdLookupQuery = bank.lookupCustomer("0000000002");
        assertTrue(customerIdLookupQuery != nullptr, "customer with id 0000000002 cannot be looked up");

   /*
    * (3) Assert that there is no customer with id 0000000042.
    */
    // Add your code here:
        auto customerSearchQuery = find(bank.allCustomers().begin(), bank.allCustomers().end(), bank.lookupCustomer("0000000042"));
        bool customerFound = false;
        if(customerSearchQuery != bank.allCustomers().end())
        {
            customerFound = true;
        }
        assertTrue(customerFound, "Customer with id 0000000042 not found");


}

void customerTests () {
    /*
     * (1) Create a Customer with sample data. Assert that
     * invoking the overloaded left shift operator produces the
     * expected result. (Hint: use a stringstream.)
     */
    // Add your code here:

}

void accountTests () {
    /**
     * Create a bank and initialize it with setupBank.
     */
    // Add your code here:
        Bank Bank2;
        setupBank(Bank2);
    /*
     * (1) Lookup Customer 0000000001 (Alice), assert that she is found.
     */
    // Add your code here:
        auto AliceLookupQuery = Bank2.lookupCustomer("0000000001");
        auto AliceSearchQuery = find(Bank2.allCustomers().begin(), Bank2.allCustomers().end(), AliceLookupQuery);
        bool AliceFound = false;
        if(AliceSearchQuery != Bank2.allCustomers().end())
        {
            AliceFound = true;
        }
        assertTrue(AliceFound, "Alice was not found in the bank");

    /*
     * (2) Assert that Alice has 5 accounts.
     */
    // Add your code here:
        auto AliceAccountCount = AliceLookupQuery->allAccounts().size();
        assertTrue(AliceAccountCount == 5, "Alice does not have 5 accounts");

    /**
     * (3) Assert that the C++-types of Alice's accounts and the
     * types derived from the account id (see Account::accountType)
     * match.
     */
    // Add your code here:
        auto AliceAccounts = AliceLookupQuery->allAccounts();
        for(const auto& account : AliceAccounts)
        {
            assertTrue(account->accountType(AliceLookupQuery->getId()) == Account::accountType(AliceLookupQuery->getId()), "Account types do not match");
        }

    /**
     * (4) Assert that Alice has 3 accounts of type CD
     * and that these accounts have the ids "3010000001",
     * "3020000001" and "3030000001". The check must not
     * rely on accounts being returned in a specific sequence.
     *
     * In order to check this, proceed as follows:
     *  * Obtain the ids
     *  * Filter out the CD accounts and count them
     *  * Out the ids in a set and assert that the set contains
     *    the expected ids.
     */
    // Add your code here:
        set<string> CDAccountIDsSet;
        for(const auto& account : AliceAccounts)
        {
            string AccountID = account->getId();
            if(account->accountType(AccountID) == Bank::AccountType::CD)
            {
                CDAccountIDsSet.emplace(AccountID);
            }
        }

        bool firstIDFound = CDAccountIDsSet.find("3010000001") != CDAccountIDsSet.end();
        bool SecondIDFound = CDAccountIDsSet.find("3020000001") != CDAccountIDsSet.end();
        bool ThirdIDFound = CDAccountIDsSet.find("3030000001") != CDAccountIDsSet.end();

        assertTrue(firstIDFound && SecondIDFound && ThirdIDFound, "Set does not contain specific IDs");

    /**
     * (5) Assert that an attempt to delete account 3040000001
     * throws an invalid_argument exception.
     */
    // Add your code here:
        bool deleteAttempt = true;
        try
        {
           AliceLookupQuery->deleteAccount("3040000001");
        }
        catch (const std::invalid_argument &e)
        {
            deleteAttempt = false;
            assertTrue(deleteAttempt, "Failed to delete account 3040000001, invalid argument exception");
        }

     /**
      * (6) Assert that an attempt to delete account 3020000001
      * throws a logic_error exception.
      */
    // Add your code here:
        bool deleteAttempt = true;
        try
        {
           AliceLookupQuery->deleteAccount("3020000001");
        }
        catch (const std::logic_error &e)
        {
            deleteAttempt = false;
            assertTrue(deleteAttempt, "Failed to delete account 3040000001, logic error exception");
        }

      /**
       * (7) Withdraw the deposit from account 3010000001,
       * delete the account and assert that Alice has only
       * 4 accounts left
       */
    // Add your code here:
        auto accountToWithdraw = AliceLookupQuery->lookupAccount("3010000001");
        float amountToWithdraw = accountToWithdraw->getBalance();
        accountToWithdraw->transact(amountToWithdraw);
        AliceLookupQuery->deleteAccount("3010000001");
        assertTrue(AliceAccountCount == 4, "Alice does not have 4 accounts");

      /**
       * (8) Lookup Alice's account 1010000001, create
       * the JSON object representing its data and assert
       * that the account type is "Current" and the balance
       * is 100.
       */
    // Add your code here:
        auto accountToCreateJsonObject = AliceLookupQuery->lookupAccount("1010000001");
        auto JsonObject = accountToCreateJsonObject->toJson();

        Bank::AccountType JsonObjectAccountType = JsonObject->getValue<Bank::AccountType>("Type");
        float JsonObjectAccountBalance = JsonObject->getValue<float>("Balance");

        assertTrue(JsonObjectAccountType == "Current" && JsonObjectAccountBalance == 100.0 , "Account type is not current and the balance is not 100");
}

void allTests() {
    bankTests();
    customerTests();
    accountTests();
}

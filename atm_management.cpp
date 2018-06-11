#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

class AutoTellerMachine {         //Object to represent each customer                  who uses the ATM program
    public:
    void CreateNewAccount(string newUsername, string newPassword);
    void AccountLogin(string loginUsername, string loginPassword);
    void DepositMoney(double depositAmount);
    void WithdrawMoney(double withdrawalAmount);
    void SetAccountLogin(int setAccountLocation);
    void SetLastMoneyMovement(int accountID, double amount);
    void SetBeginningBalance(int accountID);
    void SetLastOperation(int accountID, char userInput);
    void AccountMenu();
    int GetAccountLogin() const;
    double GetLastMoneyMovement(int accountID) const;
    double GetAccountBalance(int accountID) const;
    double GetBeginningBalance(int accountID) const;
    char GetLastOperation(int accountID) const;
    string GetUsername(int accountID) const;

    private:
    int loggedInAccountLocation;
    double accountBalance;
    double beginningBalance;
    double lastMoneyMovement;
    char lastOperation;
    string username;
    string password;
};

AutoTellerMachine account;

vector<AutoTellerMachine> AccountList;  //This vector allows for multiple accounts to be stored so that if more than one person uses the account, all information is retained

void AccountMenu();
void UserMenu();

void AutoTellerMachine:: SetAccountLogin(int setAccountLocation) {

    loggedInAccountLocation = setAccountLocation;

    return;
}

int AutoTellerMachine::GetAccountLogin() const {

    return loggedInAccountLocation;
}

void AutoTellerMachine::CreateNewAccount(string newUsername, string newPassword) {    //Adds the new information to the vector to give the account personalized info

    int accountListSize = AccountList.size();

    AccountList.at(accountListSize - 1).accountBalance = 0.0;
    AccountList.at(accountListSize - 1).username = newUsername;
    AccountList.at(accountListSize - 1).password = newPassword;

}

void AutoTellerMachine::AccountLogin(string loginUsername, string loginPassword) {

    int accountListSize = AccountList.size();
    bool successfulLogin = false;
    int accountLocation = 0;

    for(int i = 0; i < accountListSize; i++) {

        if(loginUsername == AccountList.at(i).username) {

            if(loginPassword == AccountList.at(i).password) {

                successfulLogin = true;
                accountLocation = i;
            }
        }                
    }

    if(successfulLogin != true) {

        cout << endl << "******** LOGIN FAILED! ********" << endl << endl;
        UserMenu();
    }

    else if(successfulLogin == true) {

        SetAccountLogin(accountLocation);
        cout << endl << "Access Granted - " << AccountList.at(loggedInAccountLocation).username << endl;
        AccountMenu();
    }

    return;
}

void AutoTellerMachine::DepositMoney(double depositAmount) {

    AccountList.at(loggedInAccountLocation).accountBalance += depositAmount;

    return;
}

void AutoTellerMachine::WithdrawMoney(double withdrawalAmount) {

    AccountList.at(loggedInAccountLocation).accountBalance -= withdrawalAmount;

    return;
}

double AutoTellerMachine::GetAccountBalance(int accountID) const {

    return AccountList.at(loggedInAccountLocation).accountBalance;
}

void AutoTellerMachine::SetLastMoneyMovement(int accountID, double amount) {

    AccountList.at(accountID).lastMoneyMovement = amount;
}

void AutoTellerMachine::SetBeginningBalance(int accountID) {

    AccountList.at(accountID).beginningBalance = AccountList.at(loggedInAccountLocation).accountBalance;
}

void AutoTellerMachine::SetLastOperation(int accountID, char userInput) {

    AccountList.at(accountID).lastOperation = userInput;
}

double AutoTellerMachine::GetLastMoneyMovement(int accountID) const {

    return AccountList.at(accountID).lastMoneyMovement;
}

double AutoTellerMachine::GetBeginningBalance(int accountID) const {

    return AccountList.at(accountID).beginningBalance;
}

char AutoTellerMachine::GetLastOperation(int accountID) const {

    return AccountList.at(accountID).lastOperation;
}

string AutoTellerMachine::GetUsername(int accountID) const {

    return AccountList.at(GetAccountLogin()).username;
}

void UserMenu() {   //Implements a user interface that allows the user to make selections based on what they want to do

    char userSelection;
    string createUserId;
    string createUserPass;
    string usernameCheck;
    string passwordCheck;

    cout << "l -> Login" << endl;
    cout << "c -> Create New Account" << endl;
    cout << "q -> Quit" << endl << endl << ">";
    cin >> userSelection;

    if((userSelection == 'l') || (userSelection == 'L')) {  //Checks to make sure the login is valid and if not, couts an error statement

        cout << endl << "Please enter your user name: " << endl;
        cin >> usernameCheck;
        cout << "Please enter your password: " << endl;
        cin >> passwordCheck;

        account.AccountLogin(usernameCheck, passwordCheck);

    }

    else if((userSelection == 'c') || (userSelection == 'C')) {  //Captures info for a new account

        cout << endl << "Please enter your user name: " << endl;
        cin >> createUserId;
        cout << "Please enter your password: " << endl;
        cin >> createUserPass;

        AccountList.push_back(account);            //This creates a new object in the vector to be filled with the information gathered

        account.CreateNewAccount(createUserId, createUserPass);

        cout << endl << "Thank You! Your account has been created!" << endl << endl;

        UserMenu();
    }

    else if((userSelection == 'q') || (userSelection == 'Q')) {   //Exits the entire program

        cout << endl << "You selected quit!" << endl << endl;
    }

    else {

        cout << endl << "Invalid selection." << endl;
        UserMenu();
    }

    return;
}

void AutoTellerMachine::AccountMenu() {         //This is a separate menu from the user menu because it deals with all options available to a logged in customer

    char userInput;
    double amountOfDeposit;
    double amountOfWithdrawal;

    cout << endl << "d -> Deposit Money" << endl;   //This has a couple more options than indicated in our project overview, but I feel they make this a more useable program
    cout << "w -> Withdraw Money" << endl;
    cout << "r -> Request Balance" << endl;
    cout << "z -> Logout" << endl;
    cout << "q -> Quit" << endl;
    cout << endl << ">";
    cin >> userInput;

    if((userInput == 'd') || (userInput == 'D')) {      //Deposit function that changes the balance of the account user and sets the last money movement for later use

        SetBeginningBalance(GetAccountLogin());
        cout << endl <<  "Amount of deposit: " << endl;
        cin >> amountOfDeposit;
        SetLastMoneyMovement(GetAccountLogin(), amountOfDeposit);
        SetLastOperation(GetAccountLogin(), userInput);
        DepositMoney(amountOfDeposit);
        AccountMenu();
    }        

    else if((userInput == 'w') || (userInput == 'W')) {   //Withdraw function makes sure that enough funds are present for the operation before removing money

        cout << endl << "Amount of withdrawal: " << endl;
        cin >> amountOfWithdrawal;

        if(amountOfWithdrawal > GetAccountBalance(GetAccountLogin())) {

            cout << endl << "******Insfficient Funds!*******" << endl;
        }

        else {

           SetBeginningBalance(GetAccountLogin());
           SetLastMoneyMovement(GetAccountLogin(), amountOfWithdrawal);
           SetLastOperation(GetAccountLogin(), userInput);
           WithdrawMoney(amountOfWithdrawal);
        }

        AccountMenu();
    }

    else if((userInput == 'r') || (userInput == 'R')) {   //Simply prints the balance before the last transaction, what type and amount the last transaction was then the current balance

        cout << endl << "Beginning balance: $" << fixed << setprecision(2) << GetBeginningBalance(GetAccountLogin()) << endl;

        if(GetLastOperation(GetAccountLogin()) == 'd') {

            cout << "Deposit amount: $" << fixed << setprecision(2) << GetLastMoneyMovement(GetAccountLogin()) << endl;
        }

        else if(GetLastOperation(GetAccountLogin()) == 'w') {

            cout << "Withdrawal amount: $" << fixed << setprecision(2) << GetLastMoneyMovement(GetAccountLogin()) << endl;
        }

        cout << "Your balance is $" << fixed << setprecision(2) << GetAccountBalance(GetAccountLogin()) << endl;

        AccountMenu();
    }

    else if((userInput == 'z') || (userInput == 'Z')) {   //Allows the user to logout of their account and brings them back to the user menu so they can log in with a different account

        cout << endl << "You have successfully logged out, " << GetUsername(GetAccountLogin()) << "!" << endl << endl;
        UserMenu();
    }

    else if((userInput == 'q') || (userInput == 'Q')) {  //Exits the entire program

        cout << endl << "Thanks for banking , " << GetUsername(GetAccountLogin()) << "!" << endl;
    }

    else {

        cout << endl << "Invalid selection." << endl;
        AccountMenu();
    }

    return;
}

int main() { 

    cout<< "\t\t\t\t\tWELCOME TO BANK OF BARODA \n\n\t\t\t\t\tATM AND BANKING SERVICES"<< endl << endl;
    cout<< "\n\n\t\t\tPlease select an option from the menu below: " << endl << endl;

    UserMenu();

}
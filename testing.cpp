#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits> 
using namespace std;

class BankAccount{
    private:
    string name;
    string accNumber;
    int PIN;
    int balance;
    public:
    BankAccount(){
        name = "undefined";
        accNumber = "AL00000000";
        PIN = 0000;
        balance = 0;
    }
    BankAccount(string name, string AccNumber, int PIN, int balance){
        this->name = name;
        this->accNumber = accNumber;
        this->PIN = PIN;
        this->balance = balance;
    }
    string getName(){
        return name;
    }
    void setName(string name){
        this->name = name;
    }

    string getAccNumber(){
        return accNumber;
    }
    void setAccNumber(string accNumber){
        this->accNumber = accNumber;
    }

    int getPIN(){
        return PIN;
    }
    void setPIN(int PIN){
        this->PIN = PIN;
    }   
    
    int getBalance (){
        return balance;
    }
    void setBalance( int balance){
        this->balance = balance;
    }

    void withdraw(int amount){
        if (amount > balance || amount < 0){
            cout << "Insufficient funds !"<<"\n";
            return;
        }
        this->balance = this->balance - amount;
        cout << "Withdrawl successfull !"<<"\n";

    }
    void deposit(int amount){
        if (amount < 0){
            cout << "Not stealing from the bankkk !"<<"\n";
            return;
        }
        this->balance = this->balance + amount;
        cout << "Deposit successfull !"<<"\n"; 
               
    }

    string toString(){
        return name + " " + accNumber + " " + to_string(PIN) + " " + to_string(balance);
    }
};

class Bank{
    private:
    vector <BankAccount> accounts;
    public:

    Bank(){
        getFromFile();
    }

    vector <BankAccount> getAccounts(){
        return accounts;
    }
    int findAccount(string accNumber){
        //returns index when acc foumd, -1 when otherwise
        for (int i = 0; i < accounts.size(); i++){
            if (accNumber == accounts.at(i).getAccNumber()){
                return i;
            }
        }
        return -1;
    }

    void getFromFile(){
        ifstream file("input.txt");
        if (!file.is_open()){
            cout << "Could not read from file"<<"\n";
        }
        else{
            string data;
            while (getline(file, data)){
                BankAccount newAcc;
                istringstream wordData(data);            
                vector<string> vectorData;
                string word;
                while (wordData >> word){
                    vectorData.push_back(word);
                }
                newAcc.setName(vectorData.at(0));
                newAcc.setAccNumber(vectorData.at(1));
                newAcc.setPIN(stoi(vectorData.at(2)));
                newAcc.setBalance(stoi(vectorData.at(3)));
                accounts.push_back(newAcc);
            }
        }    }
    void updateFile(){
        ofstream file("input.txt");
        if(!file.is_open()){
            cout << "Couldn't write to file" << "\n";
        }
        else{
            for (int i = 0; i < accounts.size(); i++){
                file << accounts.at(i).toString() << "\n";
            } 
        }
        file.close();
    }
    void createAccount(string name, string accNumber, int PIN, int balance){
        BankAccount newAcc;
        newAcc.setName(name);
        newAcc.setAccNumber(accNumber);
        newAcc.setPIN(PIN);
        newAcc.setBalance(balance);
        accounts.push_back(newAcc);
        updateFile();
    }

    void transfer(BankAccount from, BankAccount to, int amount){
        if(from.getBalance() < amount){
            return;
            cout << "Insufficient founds !"<<"\n";
        };
        from.withdraw(amount);
        to.deposit(amount);
        updateFile();
        cout << "Transfer successfull !"<< "\n";
    }

};



void login(Bank bank);
void enterAccount(Bank bank, int accountIndex);

int main(){
    bool endBankLoop = false;
    while (!endBankLoop){
    
        Bank bank;
        bank.getAccounts().at(0).withdraw(300);
        cout << bank.getAccounts().at(0).getBalance();
        cout <<"           _______ ___ _______ _______ _______ __    _ ___   _            "<<"\n";
        cout <<"          |       |   |       |  _    |   _   |  |  | |   | | |           "<<"\n";
        cout <<" ____ ____|    ___|   |_     _| |_|   |  |_|  |   |_| |   |_| |____ ____  "<<"\n";
        cout <<"|____|____|   | __|   | |   | |       |       |       |      _|____|____| "<<"\n";
        cout <<"          |   ||  |   | |   | |  _   ||       |  _    |     |_            "<<"\n";
        cout <<"          |   |_| |   | |   | | |_|   |   _   | | |   |    _  |           "<<"\n";
        cout <<"          |_______|___| |___| |_______|__| |__|_|  |__|___| |_|  "<<"\n";

        cout << "                       ┬ ┬┌─┐┬  ┌─┐┌─┐┌┬┐┌─┐"<<"\n";
        cout << "-----------------------│││├┤ │  │  │ ││││├┤ ------------------------------"<<"\n";
        cout << "                       └┴┘└─┘┴─┘└─┘└─┘┴ ┴└─┘"<<"\n";
        cout << "             ------------               -------------"<< "\n";
        cout<< "              | 1.Log In |               | 2.Register|" << "\n";
        cout << "             ------------               -------------"<< "\n";
        cout << "Input : "<<"\n";
        int input;
        cin >> input;
        if (!cin.fail()){
            if (input == 1){
                //login function
                login(bank);
            }
            else if(input == 2){
                //register function
            }
        }
        else{
            cout << "This input is incorrect. Please try again! "<< "\n";
            cin.clear(); // clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }
    }
    return 0;
}

void login(Bank bank){
    bool endLoginLoop = false;
    while (!endLoginLoop){
        cout << "--------------------------------------------------------------------------"<<"\n";
        cout << "Please enter your IBAN                  or                 type (exit) to exit "<< "\n";
        cout << "--------------------------------------------------------------------------"<<"\n";
        string input;
        cin >> input;
        if (!cin.fail()){
            if( input == "exit"){
                endLoginLoop = true;
            }
            else{
                int accountIndex = bank.findAccount(input);
                if ( accountIndex != -1){
                    int passCounter = 3;
                    while (passCounter > 0){
                        cout << "--------------------------------------------------------------------------"<<"\n";
                        cout << "Please enter your PIN  "<< "                            Remaining tries : "<< passCounter<<"\n";
                        cout << "--------------------------------------------------------------------------"<<"\n";
                        int pin;
                        cin >> pin;
                        if(!cin.fail()){
                            if (bank.getAccounts().at(accountIndex).getPIN() == pin){
                                //redirect to account
                                enterAccount(bank, accountIndex);
                                endLoginLoop = true;
                                passCounter = 0;
                            }
                            else{
                                passCounter--;
                                cout << "This PIN is incorrect, " << passCounter <<" tries remaining"<< "\n";
                            }
                        }
                        else{
                            passCounter--;
                            cout << "This input is incorrect. Please try again! "<< "\n";
                        }
                    }             
                }
                else{
                    cout << "This account does not exist !. Please try again !"<< "\n";
                }
                
            }

        }
        else{
            cout << "This IBAN is incorrect. Please try again !"<< "\n";
            cin.clear(); // clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }
    }
        
}

void enterAccount (Bank bank, int accountIndex){
    bool endEnteredAccLoop = false;
    while (!endEnteredAccLoop){
        bool endTransferLoop = false;

        
        cout <<"           _______ ___ _______ _______ _______ __    _ ___   _            "<<"\n";
        cout <<"          |       |   |       |  _    |   _   |  |  | |   | | |           "<<"\n";
        cout <<" ____ ____|    ___|   |_     _| |_|   |  |_|  |   |_| |   |_| |____ ____  "<<"\n";
        cout <<"|____|____|   | __|   | |   | |       |       |       |      _|____|____| "<<"\n";
        cout <<"          |   ||  |   | |   | |  _   ||       |  _    |     |_            "<<"\n";
        cout <<"          |   |_| |   | |   | | |_|   |   _   | | |   |    _  |           "<<"\n";
        cout <<"          |_______|___| |___| |_______|__| |__|_|  |__|___| |_|  "<<"\n";

        cout << "                       ┬ ┬┌─┐┬  ┌─┐┌─┐┌┬┐┌─┐"<<"\n";
        cout << "-----------------------│││├┤ │  │  │ ││││├┤ ------------------------------"<<"\n";
        cout << "                       └┴┘└─┘┴─┘└─┘└─┘┴ ┴└─┘"<<"\n";
        cout << "                             "<<bank.getAccounts().at(accountIndex).getName() <<"\n";
        cout << "              --------------               ------------"<< "\n";
        cout << "              | 1.Withdraw |               | 2.Deposit|" << "\n";
        cout << "              --------------               ------------"<< "\n";
        cout << "              --------------               ------------"<< "\n";
        cout << "              | 3.Balance  |               | 4.Transfer|" << "\n";
        cout << "              --------------               ------------"<< "\n";
        cout << "                             -------------     "<< "\n";
        cout << "                             | 5.Log Out |     "<< "\n";
        cout << "                             -------------     "<< "\n";

        int input;
        cin >> input;
        if (!cin.fail()){
            switch (input){
            case  1:{
                cout << "--------------------------------------------------------------------------"<<"\n";
                cout << "Please enter amount to withdraw : "<< "\n";
                cout << "--------------------------------------------------------------------------"<<"\n";
                int amount;
                cin >> amount;
                if(!cin.fail()){
                    bank.getAccounts().at(accountIndex).withdraw(amount);
                    bank.updateFile();
                }
                else{
                    cout << "This input is incorrect. Please try again !"<< "\n";
                    cin.clear(); // clear the error state
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                }
                break;
                }
            case  2:{
                cout << "--------------------------------------------------------------------------"<<"\n";
                cout << "Please enter amount to deposit : "<< "\n";
                cout << "--------------------------------------------------------------------------"<<"\n";
                int amountDeposit;
                cin >> amountDeposit;
                if(!cin.fail()){
                    bank.getAccounts().at(accountIndex).deposit(amountDeposit);
                    bank.updateFile();
                }
                else{
                    cout << "This input is incorrect. Please try again !"<< "\n";
                    cin.clear(); // clear the error state
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                }
                break;
                }
            case  3:{
                cout << "--------------------------------------------------------------------------"<<"\n";
                cout << "Current Balance : "<< bank.getAccounts().at(accountIndex).getBalance()  << " ALL\n";
                cout << "--------------------------------------------------------------------------"<<"\n";
                break;
                }
            case  4:{
                while (!endTransferLoop){
                    cout << "--------------------------------------------------------------------------"<<"\n";
                    cout << "Please enter the IBAN of the reciver :          or            type (exit) to exit "<< "\n";
                    cout << "--------------------------------------------------------------------------"<<"\n";
                    string inputIBAN;
                    cin >> inputIBAN;
                    if (!cin.fail()){
                        if( inputIBAN == "exit"){
                            endTransferLoop = true;
                        }
                        else{
                            int accountIndex = bank.findAccount(inputIBAN);
                            if (accountIndex != -1){
                                endTransferLoop = true;
                                cout << "--------------------------------------------------------------------------"<<"\n";
                                cout << "Please enter the amount to transfer : "<< "\n";
                                cout << "--------------------------------------------------------------------------"<<"\n";
                                int amount;
                                cin >> amount;
                                bank.transfer(bank.getAccounts().at(accountIndex), bank.getAccounts().at(accountIndex), amount);
                            }
                            else{
                                cout << "This account does not exist !. Please try again !"<< "\n";
                            }
                        }
                    }
                    else{
                        cout << "This input is incorrect. Please try again !"<< "\n";
                        cin.clear(); // clear the error state
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                    }
                }
                break;
                }
            case  5:{
                endEnteredAccLoop = true;
                break;
                }
            }                                                       
        }
        else{
            cout << "This input is incorrect. Please trye again !" << "\n";
            cin.clear(); // clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }
        
    }
    
}
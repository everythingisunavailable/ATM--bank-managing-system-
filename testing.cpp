#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;



/*
    ATM
    -account nr and password(4 digit pin) to login
    -personal menu (welkome John Doe heres what u can do 1 2 3 4 5)
        -check balance
        -withdraw
        -deposit
        -transfer to another acc
        -exit
    -create an account (0 money at first)
        
*/
class BankAccount{
    private:
    string name;
    string accNumber;
    int PIN;
    double balance;
    public:
    BankAccount(){
        name = "undefined";
        accNumber = "AL00000000000000000000000000";
        PIN = 0000;
    }
    BankAccount(string name, string AccNumber, int PIN){
        this->name = name;
        this->accNumber = accNumber;
        this->PIN = PIN;
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
    
    double getBalance (){
        return balance;
    }
    void setBalance( double balance){
        this->balance = balance;
    }

    void withdraw(int amount){
        if (amount > balance || amount < 0){
            cout << "Insufficient founds !"<<"\n";
            return;
        }
        balance =- amount;
        cout << "Withdrawl successfull !"<<"\n";

    }
    void deposit(int amount){
        if (amount < 0){
            cout << "Not stealing from the bankkk !"<<"\n";
            return;
        }
        balance =+  amount;
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
                newAcc.setBalance(stod(vectorData.at(3)));
                accounts.push_back(newAcc);
            }
        }
    }
    void updateFile(){
             ofstream file("input.txt");
        if(!file.is_open()){
            cout << "Couldn't write to file" << "\n";
        }
        else{
            for (int i = 0; i < accounts.size(); i++){
                file << accounts.at(i).toString() + "\n";
            } 
        }
    }

    void createAccount(string name, string accNumber, int PIN, double balance){
        BankAccount newAcc;
        newAcc.setName(name);
        newAcc.setAccNumber(accNumber);
        newAcc.setPIN(PIN);
        newAcc.setBalance(balance);
        accounts.push_back(newAcc);
        updateFile();
    }
};




int main(){
    bool endBankLoop = false;
    while (!endBankLoop){
    
        Bank bank;
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
        }
    return 0;
    }
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
        }
    }
        
}

void enterAccount (Bank bank, BankAccount currAcc){
    bool endEnteredAccLoop = false;
    while (!endEnteredAccLoop){
        
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
        cout << "                        "<<currAcc.getName() <<"\n";
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
            case  1:
                cout << "--------------------------------------------------------------------------"<<"\n";
                cout << "Please enter amount to withdraw : "<< "\n";
                cout << "--------------------------------------------------------------------------"<<"\n";
                int amount;
                cin >> amount;
                if(!cin.fail()){
                    currAcc.withdraw(amount);
                    bank.updateFile();
                }
                else{
                    cout << "This input is incorrect. Please try again !"<< "\n";
                }
                break;
            case  2:
                cout << "--------------------------------------------------------------------------"<<"\n";
                cout << "Please enter amount to deposit : "<< "\n";
                cout << "--------------------------------------------------------------------------"<<"\n";
                int amount;
                cin >> amount;
                if(!cin.fail()){
                    currAcc.deposit(amount);
                    bank.updateFile();
                }
                else{
                    cout << "This input is incorrect. Please try again !"<< "\n";
                }
                break;
            case  3:
                cout << "--------------------------------------------------------------------------"<<"\n";
                cout << "Current Balance : "<< currAcc.getBalance()  << " ALL\n";
                cout << "--------------------------------------------------------------------------"<<"\n";
                break;
            case  4:
                break;
            case  5:
                break;                                                        
            default:
                break;
            }
        }
        else{
            cout << "This input is incorrect. Please trye again !" << "\n";
        }
        
    }
    
}
#include <bits/stdc++.h>
#include <windows.h> 
using namespace std;
class Account{
    private:
    string AccountNo, Password;
    int Balance;
    public:
    Account():AccountNo(""), Password(""), Balance(0) {}
    void setAccountNo(string id) {
        AccountNo = id;
    }
    void setPassword(string pass) {
        Password = pass;
    }
    void setBalance(int bal) {
        Balance = bal;
    }
    string getAccountNo() {
        return AccountNo;
    }
    string getPassword() {
        return Password;
    }
    int getBalance() {
        return Balance;
    }
};

void openAccount(Account &user) {
    string id, pass;
    cout <<"\tEnter your account number: ";
    cin>>id;
    user.setAccountNo(id);
    cout <<"\tEnter your password: ";
    cin>>pass;
    user.setPassword(pass);
    user.setBalance(0);
    ofstream outfile("C:/Users/Abc/Desktop/Pject/Account.txt", ios::app);
    if(!outfile) {
        cout<<"\tError opening file!"<<endl;
    }
    else{
        outfile << user.getAccountNo() << ":" << user.getPassword() << ":" << user.getBalance() << endl;
        cout<<"\tAccount created successfully!"<<endl;
    }
    outfile.close();
    Sleep(5000);
}

void addCash(Account &user) {
    system("cls");
    string id, pass;
    cout <<"\tEnter your account number: ";
    cin>>id;
    cout <<"\tEnter your password: ";
    cin>>pass;
    ifstream infile("C:/Users/Abc/Desktop/Pject/Account.txt");
    ofstream outfile("C:/Users/Abc/Desktop/Pject/tempTemp.txt", ios::app);
    if(!infile || !outfile) {
        cout<<"\tError opening file!"<<endl;
    }
    string line;
    bool found = false;
    while(getline(infile, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string userId, userPass, balanceStr;
        getline(ss, userId, ':');
        getline(ss, userPass, ':');
        getline(ss, balanceStr, ':');
        if (userId.empty() || userPass.empty() || balanceStr.empty()) {
            // skip malformed lines
            continue;
        }
        int userBalance = 0;
        try {
            userBalance = stoi(balanceStr);
        } catch (...) {
            // skip lines with invalid balance
            continue;
        }
        if(userId == id && userPass == pass) {
            found = true;
            int amount;
            cout <<"\tEnter amount to add: ";
            cin >> amount;
            int newBalance = userBalance + amount;
            user.setBalance(newBalance);
            outfile << userId << ":" << userPass << ":" << newBalance << endl;
            cout << "\tAmount added successfully! New balance: " << newBalance << endl;
        }
        else{
            outfile << userId << ":" << userPass << ":" << balanceStr << endl;
        }
    }
    if(!found) {
        cout << "\tAccount not found or incorrect password!" << endl;
    }
    outfile.close();
    infile.close();
    remove("C:/Users/Abc/Desktop/Pject/Account.txt");
    rename("C:/Users/Abc/Desktop/Pject/tempTemp.txt", "C:/Users/Abc/Desktop/Pject/Account.txt");
    Sleep(5000);
}
void withdraw(Account &user) {
    system("cls");
    string id, pass;
    cout <<"\tEnter your account number: ";
    cin >> id;
    cout <<"\tEnter your password: ";
    cin >> pass;
    ifstream infile("C:/Users/Abc/Desktop/Pject/Account.txt");
    ofstream outfile("C:/Users/Abc/Desktop/Pject/tempTemp.txt", ios::app);
    if(!infile || !outfile) {
        cout << "\tError opening file!" << endl;
    }
    string line;
    bool found = false;
    while(getline(infile, line)) {
        if (line.empty()) continue; // skip empty lines
        stringstream ss(line);
        string userId, userPass, balanceStr;
        getline(ss, userId, ':');
        getline(ss, userPass, ':');
        getline(ss, balanceStr, ':');
        if (userId.empty() || userPass.empty() || balanceStr.empty()) {
            // skip malformed lines
            continue;
        }
        int userBalance = 0;    
        try {
            userBalance = stoi(balanceStr);
        }   catch (...) {
            // skip lines with invalid balance
            continue;
        }
        if(userId == id && userPass == pass) {
            found = true;
            int amount;
            cout <<"\tEnter amount to withdraw: ";
            cin >> amount;
            if(amount > userBalance) {
                cout << "\tInsufficient balance!" << endl;
            } else {
                int newBalance = userBalance - amount;
                user.setBalance(newBalance);
                outfile << userId << ":" << userPass << ":" << newBalance << endl;
                cout << "\tAmount withdrawn successfully! New balance: " << newBalance << endl;
            }
        } else {
            outfile << userId << ":" << userPass << ":" << balanceStr << endl;
        }
    }
    if(!found) {
        cout << "\tAccount not found or incorrect password!" << endl;
    }
    outfile.close();
    infile.close();
    remove("C:/Users/Abc/Desktop/Pject/Account.txt");
    rename("C:/Users/Abc/Desktop/Pject/tempTemp.txt", "C:/Users/Abc/Desktop/Pject/Account.txt");
    Sleep(5000);
}

int main() {
    Account user;
    bool isValid = false;
    while (!isValid) {
        system("cls");
        int val;
        cout <<"\tWelcome to the Bank Management System"<<endl;
        cout <<"\t*********************************************"<<endl;
        cout <<"\t1.Open new account"<<endl;
        cout <<"\t2.Add cash"<<endl;
        cout <<"\t3.Withdraw cash"<<endl;
        cout <<"\t4.Exit"<<endl;
        cout <<"\t*********************************************"<<endl;
        cout <<"\tEnter your choice: ";
        cin >> val;

        if(val == 1){
            openAccount(user);
        }
        else if(val == 2){
            addCash(user);
        }
        else if(val == 3){
            withdraw(user);
        }
        else if(val == 4){
            cout << "\tThank you for using the Bank Management System!" << endl;
            isValid = true;
        }
        Sleep(3000);
    }
    return 0;
}
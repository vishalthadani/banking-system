#include <iostream>
#include <vector>
#include <memory>
using namespace std;

int currentUser{-1};
string currentUsername;

//Creating Customer Object
struct Customer {
    Customer(string n, int ac, string p, int b = 0):name(n),accountNumber(ac),password(p),balance(b){}
    string name;
    int accountNumber;
    string password;
    double balance;
};

//Creating Banking System
class BankingSystem{
    vector<shared_ptr<Customer>> db; //Creating Database which is in form of Map

    void Insert(const int &ac, const shared_ptr<Customer> obj){
        db.push_back(obj);
    }

public:
    int SignUp(const string &name, const string &password) {
        auto newCustomer = make_shared<Customer> (name, db.size()+1, password);
        Insert(newCustomer->accountNumber, newCustomer);
        return db.size();
    }

    bool Login(const int &ac,const string &password){
        bool isValidACNum = ac > 0 && ac <= db.size();
        if(isValidACNum) {
            bool passwordMatches = (db[ac-1]->password == password);
            if(passwordMatches){
                currentUser = ac;
                currentUsername = db[ac-1]->name;
                return true;
            }
        }
        return false;
    }

    void Deposit(const double &amount) {
        db[currentUser-1]->balance += amount;
        cout<<"Amount deposited Successfully."<<endl;
        cout<<"Current Balance: "<< db[currentUser-1]->balance;
    }

    void Withdraw(const double &amount) {
        db[currentUser-1]->balance -= amount;
        cout<<"Amount withdrawn Successfully."<<endl;
        cout<<"Current Balance: "<< db[currentUser-1]->balance;
    }
    
    void Transfer(const double &amount, const int recepient) {
        if(recepient>0 && recepient<=db.size()){
            db[currentUser-1]->balance -= amount;
            db[recepient-1]->balance += amount;
            cout<<"Amount transfered Successfully."<<endl;
            cout<<"Current Balance: "<< db[currentUser-1]->balance;
        } else {
            cout<<"No such recepient found. Transfer Failed."<<endl;
        }
    }

    void CheckBalance(){
        cout<<"Your current balance is: Rs. "<< db[currentUser-1]->balance <<"/-"<<endl;
    }

    void Logout() {
        currentUser = -1;
        currentUsername = "";
    }
    
}myBank;

//Deposit Page
void DepositPage(){
    while(true){
        system("cls");
        cout<<" ==== Hello "<< currentUsername << ", Welcome To Paise ki Duniya ===="<<endl<<endl;
        double amount;
        cout<<"Enter Deposit Amount: ";
        cin>> amount;
        if(!amount){
            cout<< "Failed to deposit. Try again!";
            system("timeout /t 3");
        }
        else{
            myBank.Deposit(amount);
            system("timeout /t 3");
            return;
        }
    }
}

//Withdraw Page
void WithdrawPage(){
    while(true){
        system("cls");
        cout<<" ==== Hello "<< currentUsername << ", Welcome To Paise ki Duniya ===="<<endl<<endl;
        double amount;
        cout<<"Enter Withdrawal Amount: ";
        cin>> amount;
        if(!amount){
            cout<< "Failed to withdraw. Try again!";
            system("timeout /t 3");
        }
        else{
            myBank.Withdraw(amount);
            system("timeout /t 3");
            return;
        }
    }
}

//TransferPage
void TransferPage(){
    while(true){
        system("cls");
        cout<<" ==== Hello "<< currentUsername << ", Welcome To Paise ki Duniya ===="<<endl<<endl;
        int recepient;
        double amount;
        cout<<"Enter Transfer Amount: ";
        cin>> amount;
        cout<<"Enter Recepient Account Number: ";
        cin>> recepient;
        if(!amount || !recepient){
            cout<< "Failed to transfer. Try again!";
            system("timeout /t 3");
        }
        else{
            myBank.Transfer(amount,recepient);
            system("timeout /t 3");
            return;
        }
    }
}

//Check Balance Page
void CheckBalancePage() {
    system("cls");
    cout<<" ==== Hello "<< currentUsername << ", Welcome To Paise ki Duniya ===="<<endl<<endl;
    myBank.CheckBalance();
    system("timeout /t 3");
    return;
}

//Main Menu
void MainMenu() {
    while(true){
        system("cls");
        cout<<" ==== Hello "<< currentUsername << ", Welcome To Paise ki Duniya ===="<<endl<<endl;
        cout<<"Enter your Choice"<<endl;
        cout<<"1. Deposit"<<endl;
        cout<<"2. Withdraw"<<endl;
        cout<<"3. Transfer"<<endl;
        cout<<"4. Check Balance"<<endl;
        cout<<"5. Logout"<<endl;
        int choice {0};
        cin >> choice;
        
        switch (choice) {
            case 1:
                DepositPage();
                break;
            case 2:
                WithdrawPage();
                break;
            case 3:
                TransferPage();
                break;
            case 4:
                CheckBalancePage();
                break;
            case 5:
                myBank.Logout();
                return;
                break;
            default:
                cout<< "Enter valid choice!";
                system("timeout /t 3");
        }
    }
}

//SignUp Page
void SignUpPage(){
    system("cls");

    string name, password;

    cout << "Enter your name: ";
    cin >> name;
    cout << "Enter Password: ";
    cin >> password;

    auto accNum = myBank.SignUp(name, password);

    system("cls");
    cout<<"Sign Up Successful!"<< endl;
    cout<<"Your Account Number is: "<< accNum << endl;
    system("timeout /t 5");
    return;
}

//Login Page
void LoginPage() {
    while(true){
        system("cls");

        int ac;
        string password;

        cout << "Enter your Account number: ";
        cin >> ac;
        cout << "Enter Password: ";
        cin >> password;
        if(static_cast<bool>(ac) && password!=""){
            bool Login = myBank.Login(ac,password);
            if(Login) {
                cout<<" Login Successful!";
                system("timeout /t 3");
                MainMenu();
                return;
            }
            else {
                cout << endl<< "Invalid Username or Password. Try Again!"<<endl;
                system("timeout /t 3");
                return;
            }
        } else{
            cout << endl<< "Invalid Username or Password. Try Again!"<<endl;
            system("timeout /t 3");
            return;
        }
    }
}

//Home Page for SignUp/Login
void HomePage(){
    while(true){
        system("cls");
        cout<<" ==== Welcome To Paise ki Duniya ===="<<endl<<endl;
        cout<<"Enter your Choice"<<endl;
        cout<<"1. Sign Up"<<endl;
        cout<<"2. Login"<<endl;
        cout<<"3. Exit"<<endl;
        int choice {0};
        cin >> choice;
        
        switch (choice) {
            case 1:
                SignUpPage();
                break;
            case 2:
                LoginPage();
                break;
            case 3:
                return;
                break;
            default:
                cout<< "Enter valid choice!";
                system("timeout /t 3");
        }
    }
}

int main(){
    HomePage();
    return 0;
}

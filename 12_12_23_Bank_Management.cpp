#include <iostream>
#include <vector>
#include <memory>
using namespace std;

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
}myBank;

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
    cout<<"Press any key to return back to Home Screen";

    getchar();
    return;
}

//Login Page
void LoginPage() {

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
        }
    }
}

int main(){
    HomePage();
    return 0;
}

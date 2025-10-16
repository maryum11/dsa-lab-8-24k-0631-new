// 24K-0631
#include<iostream>
#include<string>
#include<stack>
using namespace std;
class Transaction{
public:
    int id;
    double amount;
    string description;
    int flag;
    Transaction* next;
    Transaction(int tid,double amt,string desc,int f){
        id=tid;
        amount=amt;
        description=desc;
        flag=f;
        next=nullptr;
    }
};
class TransactionStack{
private:
    Transaction* top;
    int idCounter;
public:
    TransactionStack(){
        top=nullptr;
        idCounter=1;
    }
    string shortenDesc(string desc){
        if(desc.length()>20)
            return desc.substr(0, 17) + "...";
        return desc;
    }
    double applyDiscount(double amt){
        if(amt>=1500)
            amt*=0.70;
        else if(amt>=1000)
            amt*=0.85;
        else if(amt>=500)
            amt*=0.95;
        return amt;
    }
    void push(double amt,string desc){
        int flag=(amt>=0)?1:0;
        desc=shortenDesc(desc);
        if(flag==1)
            amt=applyDiscount(amt);
        Transaction* newNode=new Transaction(idCounter++, amt, desc, flag);
        newNode->next=top;
        top=newNode;
    }
    Transaction* pop(){
        if (top==nullptr){
            cout<<"Stack Underflow — No transaction to pop.\n";
            return nullptr;
        }
        Transaction* temp=top;
        top=top->next;
        temp->amount *=-1;
        temp->description +=" [REVERSED]";
        temp->flag=2;
        temp->next=nullptr;
        return temp;
    }
    void display(){
        if(top==nullptr){
            cout<<"No transactions in stack.\n";
            return;
        }
        cout.setf(ios::fixed);
        cout.precision(2);
        cout << "\nFinal Stack Output:\n";
        Transaction* temp = top;
        cout << "Top → ";
        while (temp != nullptr) {
            cout <<"[id=" <<temp->id
                 <<", amt=" <<temp->amount
                 <<", desc=\"" <<temp->description
                 <<"\", flag=" <<temp->flag << "]\n";
            temp=temp->next;
        }
        cout<<"Bottom\n";
    }
};
int precedence(char op) {
    if(op=='+'||op=='-') return 1;
    if (op=='*'||op== '/') return 2;
    return 0;
}
double applyOp(double a, double b, char op) {
    if (op=='+') return a+b;
    if (op=='-') return a-b;
    if (op=='*') return a*b;
    if (op=='/') return a/b;
    return 0;
}
bool isDigitOrDot(char c) {
    return (c >= '0' && c <= '9') || c == '.';
}

string infixToPostfix(string infix){
    stack<char> st;
    string postfix="";
    for (int i=0; i<(int)infix.length();i++){
        char c=infix[i];
        if(isDigitOrDot(c)){
            postfix+=c;
        }else if(c==' ') {
            continue;
        } else {
            postfix += ' ';
            if (c == '(')
                st.push(c);
            else if (c == ')') {
                while (!st.empty() && st.top() != '(') {
                    postfix += st.top();
                    postfix += ' ';
                    st.pop();
                }
                if (!st.empty()) st.pop();
            } else {
                while (!st.empty() && precedence(st.top()) >= precedence(c)) {
                    postfix += st.top();
                    postfix += ' ';
                    st.pop();
                }
                st.push(c);
            }
        }
    }
    while (!st.empty()) {
        postfix += ' ';
        postfix += st.top();
        st.pop();
    }
    return postfix;
}

double evaluatePostfix(string postfix) {
    stack<double> st;
    string num = "";
    for (int i = 0; i < (int)postfix.length(); i++) {
        char c = postfix[i];
        if (isDigitOrDot(c)) {
            num += c;
        } else if (c == ' ' && num != "") {
            st.push(stod(num));
            num = "";
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            double b = st.top(); st.pop();
            double a = st.top(); st.pop();
            st.push(applyOp(a, b, c));
        }
    }
    return st.top();
}

int main() {
    unsigned int seed = (unsigned int)time(0);
    int randSeed = (seed % 1000) + 1;

    struct Predefined {
        double amt;
        string desc;
    } list[7] = {
        {1200, "Sale: Blue Jacket"},
        {450, "Sale: Cotton Socks"},
        {-300, "Refund: Defective Shirt"},
        {1700, "Sale: Leather Jacket"},
        {600, "Sale: Jeans"},
        {-150, "Refund: Wrong Item"},
        {2500, "Sale: Winter Coat"}
    };

    TransactionStack stackObj;

    cout << "Pushed Transactions:\n";
    for (int i = 0; i < 4; i++) {
        int r = (randSeed + i * 37) % 7;
        stackObj.push(list[r].amt, list[r].desc);
        cout << i + 1 << ". " << list[r].desc << " (" << list[r].amt << ")\n";
    }

    string infix = "(100 + 20) * 0.9 - 5";
    cout << "\nIntermediate Expression Calculation:\n";
    cout << "Infix: " << infix << endl;
    string postfix = infixToPostfix(infix);
    cout << "Postfix: " << postfix << endl;
    double result = evaluatePostfix(postfix);
    cout.setf(ios::fixed);
    cout.precision(2);
    cout << "Evaluated Result: " << result << endl;

    cout << "\nPop (remove) one transaction:\n";
    Transaction* popped = stackObj.pop();
    if (popped != nullptr) {
        cout << "Popped Transaction: " << popped->description << endl;
        cout << "Amount changed to " << popped->amount << endl;
        cout << "Flag updated to " << popped->flag << endl;
    }

    stackObj.display();
    return 0;
}

// 24K-0631 Maryum Faisal
// Task 1
// Implement and insert the values “BORROWROB” in the stack and identify if it’s a palindrome or not.
// Using arrays with push() and pop() functions.

#include<iostream>
using namespace std;
class Stack{
private:
    char arr[100];
    int top;   
public:
    Stack(){
        top=-1;
    }
    void push(char ch) {
        if(top>=100-1){
            cout<<"Stack Overflow\n";
        }else{
            top++;
            arr[top]=ch;
        }
    }
    char pop(){
        if(top<0){
            cout<<"Stack Underflow\n";
            return'\0';
        }else{
            char ch=arr[top];
            top--;
            return ch;
        }
    }
    bool isEmpty(){
        return top==-1;
    }
};
int main(){
    Stack s;
    string word="BORROWROB";
    cout<<"Original Word: "<<word<<endl;
    for(int i=0;i<word.length();i++){
        s.push(word[i]);
    }
    string reversed="";
    while(!s.isEmpty()){
        reversed+=s.pop();
    }
    cout<<"Reversed Word: "<<reversed<<endl;
    if(word==reversed)
        cout<<"It is a palindrome"<<endl;
    else
        cout<< "It is NOT a palindrome"<<endl;
    return 0;
}
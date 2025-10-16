// 24K-0631 Maryum Faisal-Task 3
#include <iostream>
using namespace std;
struct Order{
    int orderID;
    string itemName;
    int quantity;
};
class OrderQueue{
private:
    static const int MAX=5;
    Order orders[MAX];
    int front, rear;
public:
    OrderQueue(){
        front=-1;
        rear=-1;
    }
    bool isFull(){
        return(rear==MAX-1);
    }
    bool isEmpty(){
        return(front==-1||front>rear);
    }
    void enqueue(int id, string name, int qty) {
        if(isFull()){
            cout<<"Queue Overflow! Cannot add more orders.\n";
            return;
        }
        if(front==-1) front=0;
        rear++;
        orders[rear].orderID=id;
        orders[rear].itemName=name;
        orders[rear].quantity=qty;
        cout << "Order #" <<id<<" added: "<<name<< " x" <<qty<<endl;
    }
    void dequeue(){
        if(isEmpty()){
            cout<<"Queue Underflow! No orders to process.\n";
            return;
        }
        cout<<"Processing Order #" <<orders[front].orderID << ": "
             <<orders[front].itemName << " x" << orders[front].quantity << endl;
        front++;
    }
    void displayProcessedOrders(){
        if(isEmpty()){
            cout<<"No orders to display.\n";
            return;
        }
        cout<<"\n Processed Orders in Order \n";
        for(int i=front;i<=rear;i++){
            cout<<"Order #"<<orders[i].orderID << ": "
                 <<orders[i].itemName << " x"<<orders[i].quantity<<endl;
        }
    }
};
int main(){
    OrderQueue q;
    q.enqueue(1,"Burger",2);
    q.enqueue(2,"Pizza",1);
    q.enqueue(3,"Pasta",3);
    q.dequeue();
    q.dequeue();
    q.displayProcessedOrders();
    return 0;
}
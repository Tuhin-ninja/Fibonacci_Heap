#include "priority_queue.h"

void test(Priority_Queue &pq){
    fstream f1,f2; 
    f1.open("out.txt",ios::in);
    f2.open("out2.txt",ios::in);
    while(true){ 
        string s; 
        cin >> s;
        if(s == "insert"){
            int key, value;
            cin >> key >> value;
            pq.insert(key, value);
        }
        else if(s == "find"){
            int value;
            cin >> value;
            Node* n = pq.find(value);
            if(n == NULL){
                cout << "Value not found" << endl;
            }
            else{
                cout << "Value found" << endl;
            }
        }
        else if(s == "extract_max"){
            Node* n = pq.Extract_Max();
            if(n == NULL){
                cout << "Heap is empty" << endl;
            }
            else{
                cout << "Max value pair is : " << "("<<n->key<<","<<n->data<<")"<< endl;
            }
        }
        else if(s == "find_max"){
            Node* n = pq.find_max();
            if(n == NULL){
                cout << "Heap is empty" << endl;
            }
            else{
                cout << "Max value pair is : " << "("<<n->key<<","<<n->data<<")"<< endl;
            }
        }
        else if(s == "new_heap"){
            string s2; 
            Priority_Queue pq1;
            while(true){ 
                cin>>s2;
                if(s2 == "insert"){
                    int key, value;
                    cin >> key >> value;
                    pq1.insert(key, value);
                }
                else if(s2 == "find"){
                    int value;
                    cin >> value;
                    Node* n = pq1.find(value);
                    if(n == NULL){
                        cout << "Value not found" << endl;
                    }
                    else{
                        cout << "Value found" << endl;
                    }
                }
                else if(s2 == "extract_max"){
                    Node* n = pq1.Extract_Max();
                    if(n == NULL){
                        cout << "Heap is empty" << endl;
                    }
                    else{
                        cout << "Max value pair is : " << "("<<n->key<<","<<n->data<<")"<< endl;
                    }
                }
                else if(s2 == "find_max"){
                    Node* n = pq1.find_max();
                    if(n == NULL){
                        cout << "Heap is empty" << endl;
                    }
                    else{
                        cout << "Max value pair is : " << "("<<n->key<<","<<n->data<<")"<< endl;
                    }
                }

                else if(s2 =="delete_key"){
                    int key;
                    cin>>key;
                    pq1.delete_key(key);
                }

                else if(s2 == "print"){ 
                    pq1.print(); 
                }

                else if(s2 == "increase_key"){
                    int key, value;
                    cin >> key >> value;
                    pq1.increase_key(key, value);
                }
                else if(s2 == "is_empty"){
                    if(pq1.is_empty()){
                        cout << "Heap is empty" << endl;
                    }
                    else{
                        cout << "Heap is not empty" << endl;
                    }
                }
                else if(s2 == "meld"){
                    pq.meld(pq1); 
                    break; 
                }

                
            }
        }
        else if(s == "is_empty"){
            if(pq.is_empty()){
                cout << "Heap is empty" << endl;
            }
            else{
                cout << "Heap is not empty" << endl;
            }
        }
        else if(s == "print"){
            pq.print();
        }
        else if(s == "increase_key"){
            int key, value;
            cin >> key >> value;
            pq.increase_key(key, value);
        }
        else if(s == "delete_key"){
            int key;
            cin >> key;
            pq.delete_key(key);
        }
        else{
            break;
        }
    }

    string s1, s2;
    bool flag = true;
    while(true){
        s1 = f1.get();
        s2 = f2.get(); 
        if(s1 != s2){
            flag = false;
            break;
        }

        if(f1.eof() && f2.eof()){
            break;
        }
    }

    if(flag){
        cout << "Passed" << endl;
    }
    else{
        cout << "Failed" << endl;
    }

    f1.close();
    f2.close();

}

int main(){ 
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    Priority_Queue pq; 
    test(pq);
}
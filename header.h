#include<bits/stdc++.h>
using namespace std;

#define INF 1000000000


class Node{
    public : 
    int key;
    int data;
    Node* left; 
    Node* right;
    Node* child; 
    Node* parent; 
    int degree;
    bool mark;
    Node(int key = 0, int data = 0, Node* left = NULL, Node* right = NULL, Node* child = NULL, Node* parent = NULL, int degree = 0, bool mark = false){
        this->key = key;
        this->data = data;
        this->left = left;
        this->right = right;
        this->child = child;
        this->parent = parent;
        this->degree = degree;
        this->mark = mark;
    }
};


class fibonacciHeap{
    public : 
       Node* H;
       int n; 
       unordered_map<int, Node*> m;
        fibonacciHeap(){
            make_heap(); 
         }

         Node* make_heap(){ 
                H = NULL;
                n = 0;
                return H;
         }

       Node* find(Node* root, int value){
              Node* t = root;
              if(root == NULL){
                return NULL;
              }
              do{
                if(t->key == value){
                     return t;
                }
                else{
                     Node* temp = find(t->child, value);
                     if(temp != NULL){
                          return temp;
                     }
                }
                t = t->right;
              }while(t != root);
              return NULL;
       }

       void insert(int key, int value){ 
                Node* x = new Node(key, value);
                x->left = x;
                x->right = x;
                if(H != NULL){
                    (H->left)->right = x;
                    x->right = H;
                    x->left = H->left;
                    H->left = x;
                    if(x->key > H->key){
                         H = x;
                    }
                }
                else{
                    H = x;
                }
                n++;
                m[key] = x;
       }

       bool is_empty(){ 
            return H == NULL;
       }

       Node* find_max(){
        return H; 
       }

       Node* Extract_Max(){ 
         Node* z = H; 
            if(z != NULL){
                Node* x = z->child;
                Node* temp;
                if(x != NULL){
                    do{
                        temp = x->right;
                        (z->left)->right = x;
                        x->right = z;
                        x->left = z->left;
                        z->left = x;
                        if(x->key > z->key){
                            H = x;
                        }
                        x->parent = NULL;
                        x = temp;
                    }while(temp != x);
                }
                (z->left)->right = z->right;
                (z->right)->left = z->left;
                H = z->right;
                if(z == z->right){
                    H = NULL;
                }
                else{
                    H = z->right;
                    consolidate();
                }
                n--;
                m.erase(z->key);
            }

            return z; 
       }

       void consolidate(){ 
        unordered_map<int, Node*> A; 
        vector<Node*> nodes;
        Node* w = H;
        do{
            nodes.push_back(w);
            w = w->right;
        }while(w != H);

        for(Node* x : nodes){
            int d = x->degree;
            while(A.find(d) != A.end()){
                Node* y = A[d];
                if(x->key < y->key){
                    Node* temp = x;
                    x = y;
                    y = temp;
                }
                link(y, x);
                A.erase(d);
                d++;
            }
            A[d] = x;
        }
       }


       void link(Node* y, Node* x){
            (y->left)->right = y->right;
            (y->right)->left = y->left;
            if(x->right == x){
                H = x;
            }
            y->left = y;
            y->right = y;
            y->parent = x;
            if(x->child == NULL){
                x->child = y;
            }
            y->right = x->child;
            y->left = (x->child)->left;
            ((x->child)->left)->right = y;
            (x->child)->left = y;
            if(y->key > (x->child)->key){
                x->child = y;
            }
            x->degree++;
       }

       void increase_key(int key, int new_key) {
            Node* x = find(H,key);
            if(x == NULL){
                cout<<"Key not found"<<endl;
                return;
            }
            if(new_key < x->key){
                return;
            }

            x->key = new_key;
            Node* y = x->parent;
            if(y != NULL && x->key > y->key){
                cut(x, y);
                cascading_cut(y);
            }

            //cout<<"key"<<x->key<<endl;
            if(x->key > H->key){
                H = x;
            }
       }

       void cut(Node* x, Node* y){
            if(x->right == x){
                y->child = NULL;
            }
            else{
                (x->left)->right = x->right;
                (x->right)->left = x->left;
                if(y->child == x){
                    y->child = x->right;
                }
            }
            y->degree--;
            (H->left)->right = x;
            x->right = H;
            x->left = H->left;
            H->left = x;
            x->parent = NULL;
            x->mark = false;
       }

         void cascading_cut(Node* y){
                Node* z = y->parent;
                if(z != NULL){
                 if(y->mark == false){
                      y->mark = true;
                 }
                 else{
                      cut(y, z);
                      cascading_cut(z);
                 }
                }
         }


         void delete_key(int key){
            Node *p = find(H,key); 
            if(p == NULL){
                cout<<"Key not found"<<endl;
                return; 
            }
            increase_key(key, INF);
            Node* x = Extract_Max();
            delete x;
         }

         void meld(fibonacciHeap &f2){ 
            if(H == NULL){
                H = f2.H;
                return;
            }

            if(f2.H != NULL){ 
                Node* temp = H->right; 
                H->right = f2.H; 
                f2.H->left->right = temp; 
                temp->left = f2.H->left;
                f2.H->left = H;

            }

            if(f2.H != NULL && (H == NULL || f2.H->key > H->key)){
                H = f2.H;
            }

            n = n + f2.n;
            f2.n = 0; 
            f2.H = NULL; 
         }

         void print_tree(Node* x){ 
            if(x == NULL || x->child == NULL){ 
                cout<<endl;
                return; 
            }   
            Node* temp = x;
            //cout<<"("<<temp->key<<", "<<temp->data<<")";
            Node* temp2 = temp->child; 
            do{
                cout<<"("<<temp2->key<<", "<<temp2->data<<")";
                if(temp2->right != temp->child){
                    cout<<",";
                }
                temp2 = temp2->right;
            }while(temp2 != temp->child);

            cout<<endl;

            temp2 = temp->child;
            do{
                if(temp2->child != NULL){
                   cout<<"("<<temp2->key<<", "<<temp2->data<<")"<<"->";
                   print_tree(temp2);
                }
                temp2 = temp2->right;
            }while(temp2 != temp->child);

            //cout<<endl;
         }


         void print(){ 
            int treeNum = 1; 
            Node* temp = H;
            if(temp == NULL){
                cout<<"The heap is empty"<<endl;
                return;
            }

            do{
                cout<<"Tree "<<treeNum<<": ";
                cout<<"("<<temp->key<<", "<<temp->data<<")";
                if(temp->child != NULL){
                    cout<<"->";
                }
                print_tree(temp);
                temp = temp->right; 
                //cout<<endl;
                treeNum++;
            }while(temp != H);
         }

};
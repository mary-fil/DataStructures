#pragma once
#include <iostream>
#include <fstream>

using namespace std;

template <typename Key, typename Info>
class Dictionary{

    struct Node{

        Key key;
        Info info;

        Node *left;
        Node *right;

    };

    Node* newNode(Key new_key, Info new_info) 
    { 
        Node* node = new Node();

        node->key = new_key; 
        node->info = new_info; 
        node->left = nullptr; 
        node->right = nullptr; 
                         
        return(node); 
    } 

    Node *root = nullptr;
    int numOfNodes = 0;

    public:

    //constructor
    Dictionary(){
        root = nullptr;
    };

    //destructor
    ~Dictionary(){
        removeAll(root);
    };

    //copy constructor
    Dictionary(const Dictionary<Key,Info> &rhs){
        copy(rhs.root);
        numOfNodes = rhs.numOfNodes;
    }

    void copy(Node *n){

        if(n != nullptr){
            this->root = insert_no_balancing(this->root, n->key, n->info);
            copy(n->left);
            copy(n->right);
        }
        return;
    };

    //asignment operator
    Dictionary<Key,Info>& operator=(const Dictionary<Key,Info> &rhs){
        if(this == &rhs) return *this;
        removeAll();
        copy(rhs.root);
        numOfNodes = rhs.numOfNodes;
        return *this;
    };

    //returning height of a node
    int height(Node *n){
        return n == NULL ? 0 : 1 + max(height(n->left), height(n->right));
    };

    //returning balance of a node
    int getBalance(Node *n){
        return n == NULL ? 0 : height(n->left) - height(n->right);
    };

    //right rotate
    Node *rightRotate(Node *n) 
    { 
        Node *n1; 
        Node *n2;

        n1 = n->left; 
        n2 = n1->right; 

        n1->right = n; 
        n->left = n2; 

        return n1; 
    };

    //left rotate
    Node *leftRotate(Node *n) 
    { 
        Node *n1; 
        Node *n2;

        n1 = n->right; 
        n2= n1->left; 

        n1->left = n; 
        n->right = n2; 

        return n1; 
    }; 

    //balancing the dictionary
    void balanceTree(Node *n){

        if(n == nullptr) return;

        if(n != nullptr) balanceTree(n->left);
        if(n != nullptr) balanceTree(n->right);

        if(getBalance(n->left) > 1) n= rightRotate(n);

        if(getBalance(n->right) > 1) n = rightRotate(n);

        if(getBalance(n->left) < -1) n = leftRotate(n);

        if(getBalance(n->right) < -1) n= leftRotate(n);
        
        if(n == root && getBalance(n) < -1){
            if(getBalance(n->right) == 1) n->right = rightRotate(n->right); 
            root = leftRotate(n);
        } 
        if(n == root && getBalance(n) > 1) {
            cout << "rightleft" << endl;
            if(getBalance(n->left) == -1) n->left = leftRotate(n->left);
            root = rightRotate(n);
        }

        return;
    }

    //counting the nodes
    void countNode(){
        numOfNodes = 0;
        countNode(root);
    }
 
    void countNode(Node *n){

        if(n == nullptr) return;

        countNode(n->right);
        countNode(n->left);

        numOfNodes++;
        return;
    };

    //return length of tree
    int length()const{
        return numOfNodes;
    }

    //insert a node
    void insert(Key key, Info info){
        root = insert(root, key, info);
        countNode();
    };

    Node* insert(Node* node, Key new_key, Info new_info) 
    { 
        if (node == nullptr) return(newNode(new_key, new_info)); 

        if (new_key < node->key) node->left = insert(node->left, new_key, new_info); 
        else if (new_key > node->key) node->right = insert(node->right, new_key, new_info); 
        else return node; 

        int b = getBalance(node);

        if(b > 1){
            
            if (new_key < node->left->key) {                //left left case

                return rightRotate(node);

            } else if (new_key > node->left->key) {         //left right case

                node->left = leftRotate(node->left);
                return rightRotate(node);

            }
        }
        if(b < -1){
            if (new_key > node->right->key) {               //right right case

                return leftRotate(node);

            } else if (new_key < node->right->key) {        //right left case

                node->right = rightRotate(node->right);
                return leftRotate(node);

            }
        }
        
        return node; 
    };

    Node* insert_no_balancing(Node* node, Key new_key, Info new_info) 
    { 
        if (node == NULL) return(newNode(new_key, new_info)); 

        if (new_key < node->key) node->left = insert(node->left, new_key, new_info); 
        else if (new_key > node->key) node->right = insert(node->right, new_key, new_info); 
        else return node; 
        
        return node; 
    };

    //find node to be removed
    Node *nodeToBeRemoved(Node* n, Key k){

        if(n->key == k) return n;
        else if(k < n->key) return nodeToBeRemoved(n->left, k);
        else return nodeToBeRemoved(n->right, k);

    };

    //find previous node of node with given key
    Node *findPreviousNode(Key k) const{

        if(root->key == k) return nullptr;
        
        Node *x = root;
        Node *prev = nullptr;

        while(true){
            if(k > x->key){
                if(x->right->key == k){
                    prev = x;
                    return prev;
                }
                else{
                    prev = x;
                    x = x->right;
                }
            }
            else if(k < x->key){
                if(x->left->key == k){
                    prev = x;
                    return prev;
                }
                else{
                    prev = x;
                    x = x->left;               
                }
            } 
        }
    };

    //remove node
    bool removeNode(Key k){
        
        if(root == nullptr) return false;
        if(find(k) == false) return false; 

        Node *n = nodeToBeRemoved(root, k);
        Node *prev = findPreviousNode(k);

        //no children
        if(n->left == nullptr && n->right == nullptr){
            if(n == root) root = nullptr;
            if(prev->left->key == k) prev->left = nullptr;
            if(prev->right->key == k) prev->right = nullptr;
            delete n;
            balanceTree(root);
            numOfNodes--;
            return true;
        }

        //one child only
        if(n->left == nullptr && n->right != nullptr){
            Node *child = n->right;
            
            if(prev->left->key == k) prev->left = child;
            if(prev->right->key == k) prev->right = child;

            delete n;
            if(n == root) root = child;

            balanceTree(root);
            numOfNodes--;
            return true;
        }
        if(n->left != nullptr && n->right == nullptr){
            Node *child = n->left;
            
            if(prev->left->key == k) prev->left = child;
            if(prev->right->key == k) prev->right = child;

            delete n;
            if(n == root) root = child;

            balanceTree(root);
            numOfNodes--;
            return true;
        }

        //two children
        if(n->left != nullptr && n->right != nullptr){

            Node *succ = n->left; //first value before the node to be deleted

            //if n == root then there is no previous
            if(n == root){
                Node *minValRight = n->right;
                Node *toBeMoved = succ->right;

                while(minValRight->left != nullptr){
                    minValRight = minValRight->left;
                }

                succ->right == nullptr;
                minValRight->left = toBeMoved;

                Node *l = n->left;
                Node *r = n->right;
                delete n;

                root = l;
                root->right = r;

                balanceTree(root);
                numOfNodes--;
                return true;
            }

            if(prev->left->key == k) prev->left = succ;
            if(prev->right->key == k) prev->right = succ;

            //succesor has no children or only child on the left
            if(succ->left == nullptr && succ->right == nullptr || succ->left != nullptr && succ->right == nullptr){
                succ->right = n->right;
                delete n;

                balanceTree(root);
                numOfNodes--;
                return true;
            }

            //succ has child on the right
            if(succ->right != nullptr){
                
                Node *minValRight = n->right;
                Node *toBeMoved = succ->right;

                while(minValRight->left != nullptr){
                    minValRight = minValRight->left;
                }

                succ->right == nullptr;
                minValRight->left = toBeMoved;

                Node *left = succ;
                Node *right = n->right;

                delete n;
                left->right = right;

                balanceTree(root);
                numOfNodes--;
                return true;
            }

        }
    };

    //finding if a node with a given key is in the dictionary
    bool find(const Key &k){

        if(isEmpty()) return false;

        Node *curr = root;

        while(curr != nullptr){
            if(k > curr->key) curr = curr->right;
            else if(k < curr->key) curr = curr->left;
            else return true;
        }
        return false;

    };

    //checking if dictionary is empty
    bool isEmpty(){
        if(root == nullptr) return true;
        return false;
    };

    //printing node and its subtrees
    void printNode(Node *n, int gap){

        if(n == nullptr) return;
        gap += 3;

        printNode(n->right, gap);
        for (int i = 3; i < gap; i++) cout<<" ";

        cout<<n->key<<" "<<n->info<<endl;
        printNode(n->left, gap);

        return;
    };

    //printing the whole dictionary
    void print(){

        if(root == nullptr){
            cout << "Dictionary is empty." << endl;
            return;
        }

        printNode(root, 0);
        cout << endl;

        return;
    };

    //printing dictionary in order traversal
    void printInOrderTraversal(){
        cout << "In order traversal: " << endl;
        InOrderTraversal(root);
    };

    void InOrderTraversal(Node *n){

        if(n == nullptr) return;
        InOrderTraversal(n->left);
        cout << n->key << " " <<  n->info <<", ";
        InOrderTraversal(n->right);
    };

    //printing dictionary pre order traversal
    void printPreOrderTraversal(){
        cout << "Pre order traversal: " << endl;
        PreOrderTraversal(root);
    };

    void PreOrderTraversal(Node *n){

        if(n == nullptr) return;
        cout << n->key << " " <<  n->info <<", ";
        PreOrderTraversal(n->left);
        PreOrderTraversal(n->right);
    };

    //checking if tree is balanced
    bool isTreeBalanced(){
        return isNodeBalanced(root);
    };

    //checking if node is balanced
    bool isNodeBalanced(Node *n){
        
        int left_height;
        int right_height;

        if(n == nullptr) return true;

        left_height = height(n->left);
        right_height = height(n->right);

        if(abs(left_height - right_height) <= 1 && isNodeBalanced(n->left) && isNodeBalanced(n->right)) return true;

        return false;
    };

    //removing all nodes
    void removeAll(){
        removeAll(root);
    }

    void removeAll(Node *n){

        numOfNodes = 0;

        if(n == nullptr) return;
        if(n->left != nullptr) removeAll(n->left);
        if(n->right != nullptr) removeAll(n->right);
        
        if(n == root){
            n->left = nullptr;
            n->right = nullptr;
            delete n;
            root = nullptr;
            return;
        }
        
        Node *prev = findPreviousNode(n->key);

        if(prev->left == n) prev->left = nullptr;
        if(prev->right == n) prev->right = nullptr;

        n->left = nullptr;
        n->right = nullptr;
        delete n;
        
        return;
    }


    //returning node as most to the left of given node as possible
    Node* getLeftMost(Node *n)const{
        while(n->left != nullptr){
            n = n->left;
        }
        return n;   
    }

    //returning node as most to the left of a Dictionary as possible
    Node* getFirst()const{
        if(root == nullptr) return nullptr;
        else return getLeftMost(root);
    }

    //returning next node in order traversal
    Node* getNext(Node *n)const{
        if(n->right != nullptr){
            return getLeftMost(n->right);
        }
        else{
            while(findPreviousNode(n->key) != nullptr && n == findPreviousNode(n->key)->right){
                n = findPreviousNode(n->key);
            }
            return findPreviousNode(n->key);
        }
    }

    //iterating over a Dictionary
    void iterateOver(Key table_of_keys[], Info table_of_info[])const{

        // Key table_of_keys[numOfNodes];
        // Info table_of_info[numOfNodes];
        int i = 0;

        Node *n = getFirst();
        while(n != nullptr){

            table_of_keys[i] = n->key;
            table_of_info[i] = n->info;

            //cout << table_of_keys[i] << " " << table_of_info[i] << endl;
            i++;

            n = getNext(n);
        }
    }

};

//EXTERNAL FUNCTIONS

// Return a word extracted from an input file
bool inWord (string& word, ifstream& inFile){

    bool isWord(false);
    char c;
    if (inFile.is_open()){
        while (!inFile.eof()){ // first look for a word starting character
            inFile.get(c);
            if ((c>='a' && c<='z') || (c>='A' && c<='Z')){
                isWord= true;
                word= c;    // assign the word starting character
                c='\0';
                break;
            }
        }
        while (!inFile.eof()){ // then append remaining (following) characters to the word
            inFile.get(c);
            if ((c>='a' && c<='z') || (c>='A' && c<='Z')){
                word+= c;   // append the character to the word
                c='\0';
            } else {
                break;
            }
        }
    }
    return isWord;
}

//counting number of words from a file
int WordCount(const string& fileName){
    ifstream inFile(fileName);
    string  word;
    int wordCount = 0;
    
    if (inFile.is_open()){
        while (inWord(word, inFile)){
            wordCount++;
        };
    }else{
        cout << "Can not open file '" << fileName << "'" << endl;
    }

    return wordCount;
}

//the function "counter" creates a Dictionary of words read from a text file 
//(counts word occurrences), 
//the Dictionary being created contains all words encountered in the text file
//together with the word occurrence count, ordered lexically
Dictionary<string, int>& counter(const string &fileName){

    Dictionary<string, int> *d = new Dictionary<string, int>();

    ifstream inFile(fileName);
    string word;

    int count = WordCount(fileName);

    string Words[count];
    int occurrance[count] = {};

    int j = 0;

    if (inFile.is_open()){

        while (inWord(word, inFile)){

            bool found = false;
            
            for(int i = 0; i <= j; i++){
                if(Words[i] == word){
                    found = true;
                    occurrance[i]++;
                    break;
                }
            }
            if(found == false){
                Words[j] = word;
                occurrance[j]++;
                j++;
            }
            
        };

    }else{

        cout << "Can not open file '" << fileName << "'" << endl;

    }

    for(int i = 0; i < j; i++){
        d->insert(Words[i], occurrance[i]);
    }
    
    return *d;
};

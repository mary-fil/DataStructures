#pragma once
#include <iostream>
#include "tree2.h"

using namespace std;

template <typename Key, typename Info>
class Ring{

    struct Data{
        Key key;
        Info info;
    };

    struct Node{
        
        Node * prev;
        Node * next;
        Data data;
    };

    Node *head = nullptr;
    int num_of_nodes = 0;

    public:

    class iterator {

        friend class Ring;
        Node *any = nullptr;
        Ring<Key, Info> *owner = nullptr;

        iterator(Node *n, Ring<Key, Info> *o){
            any = n;
            owner = o;
        }

        public:

        iterator(){
            any = nullptr;
            owner = nullptr;
        }

        iterator& operator++(){
            if (any != nullptr){
                any = any->next;
            }
            return *this;
        }

        iterator operator++(int){
            iterator i_return = *this;
            if (any != nullptr) {
                any = any->next;
            }
            return i_return;
        }

        iterator& operator--(){
            if (any != nullptr) {
                any = any->prev;
            }
            return *this;
        }

        iterator operator--(int){
            iterator i_return = *this;
            if (any != nullptr) {
                any = any->prev;
            }
            return i_return;
        }

        Data* operator->() {
            if(owner == nullptr || any == nullptr) throw "Invalid operator";
            if(any == owner->head) throw "Invalid operator";
            return &(any->data);
        }

        bool operator==(const iterator& rhs){
            return (any == rhs.any) && (owner == rhs.owner);
        }

        bool operator!=(const iterator& rhs){
            return !operator==(rhs);
        }
    };

    class const_iterator{
        friend class Ring;
        Node *any = nullptr;
        const Ring<Key, Info> *owner = nullptr;

        const_iterator(Node *n, const Ring<Key, Info> *o){
            any = n;
            owner = o;
        };

        public:

        const_iterator(){
            any = nullptr;
            owner = nullptr;
        }

        const_iterator& operator++(){
            if (any != nullptr){
                any = any->next;
            }
            return *this;
        }

        const_iterator operator++(int){
            const_iterator i_return = *this;
            if (any != nullptr) {
                any = any->next;
            }
            return i_return;
        }

        const_iterator& operator--(){
            if (any != nullptr) {
                any = any->prev;
            }
            return *this;
        }

        const_iterator operator--(int){
            const_iterator i_return = *this;
            if (any != nullptr) {
                any = any->prev;
            }
            return i_return;
        }

        const Data* operator->() {
            if(owner == nullptr || any == nullptr) throw "Invalid operator";
            return &(any->data);
        }

        bool operator==(const const_iterator& rhs) const{
            return (any == rhs.any) && (owner == rhs.owner);
        }

        bool operator!=(const const_iterator& rhs) const{
            return !operator==(rhs);
        }
    };

    iterator begin();
    iterator end();

    const_iterator const_begin() const;
    const_iterator const_end() const;

    Ring();         //constructor
    ~Ring();        //destructor

    //copy constructor
    Ring(const Ring<Key, Info>& rhs);

    //operator =
    Ring<Key, Info>& operator=(const Ring<Key, Info> &rhs);

    //operator +=
    Ring<Key, Info>& operator+=(const Ring<Key, Info> &rhs);

    //operator -=
    Ring<Key, Info>& operator-=(const Ring<Key, Info> &rhs);

    //operator +
    Ring<Key, Info>& operator+(const Ring<Key, Info> &seq);

    //operator -
    Ring<Key, Info>& operator-(const  Ring<Key, Info> &seq);

    bool removeAll(); //removing all elements from the ring
    bool isEmpty()const; //checking if the ring is empty    
    int  length()const; //returning length of the ring
    void print(bool direct); //printing the ring

    //insert element at the front of the ring
    bool insertFront(const Key&k, const Info&i); 
    bool insertFront_iterator(const_iterator iter);

    //insert element at the end of the ring
    bool insertEnd(const Key&k, const Info&i); 
    bool insertEnd_iterator(const_iterator iter);
   
    //insert an element after the iterator
    bool insertAfterIterator(iterator pos, const Key & newKey, const Info & newInfo);

    //insert an element before the iterator 
    bool insertBeforeIterator(iterator pos, const Key & newKey, const Info & newInfo); 

    //insert element after given key and given occurance of that key while traversing in specified direction
    bool insertAfter(const int dir, const Key & newKey, const Info & newInfo,const Key & where, int occurence);

    //insert element before given key and given occurance of that key while traversing in specified direction
    bool insertBefore(const int dir, const Key & newKey, const Info & newInfo,const Key & where, int occurence);

    //searching for an element in the ring
    bool isInTheRing(const Key& k, const Info& i); 
    
    //removing an element of given key and info and occurance from the ring
    bool remove(const int dir, const Key & k, const Info & i, int occurence);

    //removing an element of position given by iterator
    bool remove_iterator(iterator it);

    //removing an element in the front of the ring
    bool removeFront(); 

    //removing an element in the end of the ring
    bool removeEnd(); 

    //how many times an element and info given by user occurs in the ring
    int count(const Key& k, const Info &i); 

    //returns index of an element and occurence given by users
    int return_index(const Key& k, int occurence) const;
    
};

template <typename Key, typename Info>
typename Ring<Key, Info>::iterator Ring<Key, Info>::begin(){
    auto it = iterator(head->next, this);
    return it;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::iterator Ring<Key, Info>::end() {
    auto it = iterator(head, this);
    return it;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::const_iterator Ring<Key, Info>::const_begin()const{
    auto it = const_iterator(head->next, this);
    return it;
}

template <typename Key, typename Info>
typename Ring<Key, Info>::const_iterator Ring<Key, Info>::const_end()const{
    auto it = const_iterator(head, this);
    return it;
}

template <typename Key, typename Info>
Ring<Key, Info>::Ring(){

    head = new Node;
    head->next = head;
    head->prev = head;
    head->data.key = Key();
    head->data.info = Info();

}

template <typename Key, typename Info>
Ring<Key, Info>::~Ring(){

    removeAll();
    delete head;
}

template <typename Key, typename Info>
Ring<Key, Info>::Ring(const Ring<Key, Info>& rhs){

    head = new Node;
    head->next = head;
    head->prev = head;

    for(auto it = rhs.const_begin(); it!=rhs.const_end(); it++){
        insertEnd(it->key, it->info);
    }
}

template <typename Key, typename Info>
Ring<Key, Info>& Ring<Key, Info>::operator=(const Ring<Key, Info> &rhs){

    if(this == &rhs) return *this;
    removeAll();

    for(auto it = rhs.const_begin(); it!=rhs.const_end(); it++){
        insertEnd(it->key, it->info);
    }
    return *this;

}

template <typename Key, typename Info>
Ring<Key, Info>& Ring<Key, Info>::operator+=(const Ring<Key, Info> &rhs){

    for(auto it = rhs.const_begin(); it!=rhs.const_end(); it++){
        insertEnd(it->key, it->info);
    }
    return *this;
}

template <typename Key, typename Info>
Ring<Key, Info>& Ring<Key, Info>::operator-=(const Ring<Key, Info> &rhs){

    int counter;

    for(auto it = rhs.const_begin(); it!=rhs.const_end(); it++){
        if(this->isInTheRing(it.any->data.key, it.any->data.info)){
            counter = this->count(it.any->data.key, it.any->data.info);
            while(counter > 0){
                this->remove(1,it.any->data.key, it.any->data.info,counter);
                counter--;
            }
        }
    }
    return *this;
}

template <typename Key, typename Info>
Ring<Key, Info>& Ring<Key, Info>::operator+(const Ring<Key, Info> &rhs){

    Ring<Key,Info> *new_ring = new Ring<Key,Info>;

    for(auto it = this->const_begin(); it!= this->const_end(); it++){
        new_ring->insertEnd(it->key, it->info);
    }

    for(auto it = rhs.const_begin(); it!=rhs.const_end(); it++){
        new_ring->insertEnd(it->key, it->info);
    }
    return *new_ring;
}

template <typename Key, typename Info>
Ring<Key, Info>& Ring<Key, Info>::operator-(const Ring<Key, Info> &rhs){

    Ring<Key,Info> *new_ring = new Ring<Key,Info>;
    for(auto it = this->const_begin(); it!= this->const_end(); it++){
        new_ring->insertEnd(it->key, it->info);
    }

    int counter;

    for(auto it = rhs.const_begin(); it!=rhs.const_end(); it++){
        if(new_ring->isInTheRing(it.any->data.key, it.any->data.info)){
            counter = new_ring->count(it.any->data.key, it.any->data.info);
            while(counter > 0){
                new_ring->remove(1,it.any->data.key, it.any->data.info,counter);
                counter--;
            }
        }
    }
    return *new_ring;
}

template <typename Key, typename Info>
bool Ring<Key, Info>::removeAll(){

    if (head == nullptr) return true;

    Node *curr = head->next;

    while(curr != head){
        Node *to_remove = curr;
        curr = curr->next;
        delete to_remove;
    }

    head->next = head;
    head->prev = head;

    num_of_nodes = 0;
    return true;
}

template <typename Key, typename Info>
bool Ring<Key, Info>::isEmpty() const{
    if(head->next == head) return true;
    return false;
}

template <typename Key, typename Info>
int Ring<Key, Info>::length() const{
    return num_of_nodes;
}

template <typename Key, typename Info>
bool Ring<Key, Info>::insertFront(const Key&k, const Info&i){

    auto it = this->begin();

    Node *new_node = new Node;
    new_node->data.key = k;
    new_node->data.info = i; 
    new_node->prev = it.any->prev;
    new_node->next = it.any;

    (--it).any->next = new_node;
    new_node->next->prev = new_node;
    
    num_of_nodes++;
    return true;
}

template <typename Key, typename Info>
bool Ring<Key, Info>::insertFront_iterator(const_iterator iter){

    auto it = this->const_begin();

    Node *new_node = new Node;
    new_node->data.key = iter.any->data.key;
    new_node->data.info = iter.any->data.info; 
    new_node->prev = it.any->prev;
    new_node->next = it.any;

    (--it).any->next = new_node;
    new_node->next->prev = new_node;

    num_of_nodes++;
    return true;
}

template <typename Key, typename Info>
bool Ring<Key, Info>::insertEnd(const Key&k, const Info&i){
   
    auto it = this->end();

    Node *new_node = new Node;
    new_node->data.key = k;
    new_node->data.info = i; 
    new_node->next = it.any;
    new_node->prev = it.any->prev;

    it.any->prev = new_node;
    new_node->prev->next = new_node;
    
    num_of_nodes++;
    return true;
}

template <typename Key, typename Info>
bool Ring<Key, Info>::insertEnd_iterator(const_iterator iter){

    auto it = this->const_end();

    Node *new_node = new Node;
    new_node->data.key = iter.any->data.key;
    new_node->data.info = iter.any->data.info; 
    new_node->next = it.any;
    new_node->prev = it.any->prev;

    it.any->prev = new_node;
    new_node->prev->next = new_node;
    
    num_of_nodes++;
    return true;
}

template <typename Key, typename Info>
bool Ring<Key, Info>::insertAfterIterator(iterator pos,const Key & newKey, const Info & newInfo){

    if(pos.owner != this) return false;

    Node *new_node = new Node;
    new_node->data.key = newKey;
    new_node->data.info = newInfo; 
    new_node->prev = pos.any;
    new_node->next = pos.any->next;

    pos.any->next->prev = new_node;
    pos.any->next = new_node;
    
    num_of_nodes++;
    return true;
}

template <typename Key, typename Info>
bool Ring<Key, Info>::insertBeforeIterator(iterator pos, const Key & newKey, const Info & newInfo){
    
    if(pos.owner != this) return false;

    Node *new_node = new Node;
    new_node->data.key = newKey;
    new_node->data.info = newInfo;
    new_node->prev = pos.any->prev;
    new_node->next = pos.any;

    pos.any->prev = new_node;
    new_node->prev->next = new_node;

    num_of_nodes++;
    return true;

}

template <typename Key, typename Info>
bool Ring<Key, Info>::insertAfter(const int dir, const Key & newKey, const Info & newInfo, const Key & where, int occurence){
    
    if(isEmpty()) return false;

    if(occurence < 1) return false;

    Node *new_node = new Node;
    new_node->data.key = newKey;
    new_node->data.info = newInfo;

    int counter = 0;
    
    if(dir == true){
        for(auto it = this->begin(); it != this->end(); it++)
        {
            if(it->key == where){
                counter++;
                if(counter == occurence){
                    insertAfterIterator(it, newKey, newInfo);
                }
            }
        }
    }else{
        auto it = this->end();
        it--;
        while(it != this->end())
        {
            if(it->key == where){
                counter++;
                if(counter == occurence){
                    insertBeforeIterator(it, newKey, newInfo);
                }
            }
            it--;
        }
    }
    return true;
}

template <typename Key, typename Info>
bool Ring<Key, Info>::insertBefore(const int dir, const Key & newKey, const Info & newInfo, const Key & where, int occurence){
    
    if(isEmpty()) return false;

    if(occurence < 1) return false;

    Node *new_node = new Node;
    new_node->data.key = newKey;
    new_node->data.info = newInfo;

    int counter = 0;
    
    if(dir == true){
        for(auto it = this->begin(); it != this->end(); it++)
        {
            if(it->key == where){
                counter++;
                if(counter == occurence){
                    insertBeforeIterator(it, newKey, newInfo);
                }
            }
        }
    }else{
        auto it = this->end();
        it--;
        while(it != this->end())
        {
            if(it->key == where){
                counter++;
                if(counter == occurence){
                    insertAfterIterator(it, newKey, newInfo);
                }
            }
            it--;
        }
    }
    return true;
}

template <typename Key, typename Info>
bool Ring<Key, Info>::isInTheRing(const Key& k, const Info& i){

    for(auto it = this->begin(); it != this->end(); it++)
    {
        if(it->key == k && it->info == i) return true;
    }
    
    return false;
}

template <typename Key, typename Info>
bool Ring<Key, Info>::remove(const int dir, const Key & k, const Info & i, int occurence){
    
    if(isEmpty()) return false;

    if(occurence < 1) return false;

    int counter = 0;

    if(dir == true){
        for(auto it = this->begin(); it != this->end(); it++)
        {
            if(it->key == k && it->info == i){
                counter++;
                if(counter == occurence){
                    remove_iterator(it);
                    return true;
                }
            }
        }
    }else{
        auto it = this->end();
        it--;
        while(it != this->end())
        {
            if(it->key == k && it->info == i){
                counter++;
                if(counter == occurence){
                    remove_iterator(it);
                    return true;
                }
            }
            it--;
        }
    }
    return true;
}

template <typename Key, typename Info>
bool Ring<Key, Info>::remove_iterator(iterator it){
    
    if(it.owner!=this) return false;
    if(it.any == head) return false;

    Node *curr = it.any;
    Node *prev = curr->prev;
    Node *next = curr->next;

    delete curr;
    prev->next = next;
    next->prev = prev;

    num_of_nodes--;
    return true;
}

template <typename Key, typename Info>
bool Ring<Key, Info>::removeFront(){
    auto it = this->begin();
    if(head == it.any) return false;
    remove_iterator(it);
    return true;
}

template <typename Key, typename Info>
bool Ring<Key, Info>::removeEnd(){
    auto it = this->end();
    --it;
    if(head == it.any) return false;
    remove_iterator(it);
    return true;
}

template <typename Key, typename Info>
int Ring<Key, Info>::count(const Key& k, const Info &i){
    
    int counter = 0;

    for(auto it = this->begin(); it != this->end(); it++)
    {
        if(it->key == k && it->info == i) counter++;
    }
    return counter;
}

template <typename Key, typename Info>
void Ring<Key, Info>::print(bool direct){

    if(isEmpty()){
        cout << "The ring is empty" << endl;
        return;
    }

    cout << "KEY" << "\t INFO" << endl;

    if(direct == true){
        for(auto it = this->begin(); it != this->end(); it++)
        {
            cout << it->key << "\t " << it->info << endl;
        }
        cout << endl;
    }else{
        auto it = this->end();
        it--;
        while(it != this->end()){
            cout << it->key << "\t " << it->info << endl;
            it--;
        }
        cout << endl;
    }
    
}

template <typename Key, typename Info>
int Ring<Key, Info>::return_index(const Key& k, int occurence)const{

    int counter = 0;
    int index = 0;

    auto it = this->const_begin();
    do{
        if(it->key == k) counter++;
        if(counter == occurence) return index;
        index++;
        it++;
        if(it == this->const_end()){ 
            it = this->const_begin();
            index = 0;
        }

    }while(it != this->const_end());

    return -1;
}

//EXTERNAL FUNCTIONS

template <typename Key, typename Info>
void split_pos (const Ring <Key, Info>& ring, int start_pos, bool direct, int count,
Ring <Key, Info>& ring1, bool direct1, int len1, 
Ring <Key, Info>& ring2, bool direct2, int len2){

    //checking if ring is empty
    if(ring.isEmpty()){
        cout << "Ring is empty, wrong input.";
        return;
    }
    //checking if start_pos goes beyond the indexes of ring
    int length = ring.length();
    if(start_pos > length){
        cout << "Starting position goes beyond the indexes of ring, wrong input.";
        return;
    }
    //checking count
    if(count < 1){
        cout << "Count cannot be lower than 1, wrong input.";
        return;
    }
    //checking if lenght of ring1 and ring2 are both equal to 0
    if(len1 < 1 && len2 < 1){
        cout << "Len1 and len2 are equal to 0, cannot split ring, wrong input.";
        return;
    }
    //checking if ring1 and ring2 are empty
    if(ring1.isEmpty() == 0 || ring2.isEmpty() == 0){
        cout << "Both ring1 and ring2 must be empty, wrong input.";
        return;
    }

    int index = 0;
    int counter1;
    int counter2;

    if(direct == true){
        for(auto it = ring.const_begin(); it != ring.const_end(); it++){
            
            if(index == start_pos){

                while(count > 0){

                    counter1 = 0;
                    counter2 = 0;

                    while(counter1 < len1){
                        
                        if(direct1 == true){
                            ring1.insertEnd_iterator(it);
                        }
                        else{
                            ring1.insertFront_iterator(it);
                        }
                        counter1++;
                        it++;
                        if(it == ring.const_end()) it = ring.const_begin();
                    }

                    while(counter2 < len2){
                        
                        if(direct2 == true){
                            ring2.insertEnd_iterator(it);
                        }
                        else{
                            ring2.insertFront_iterator(it);
                        }
                        counter2++;
                        it++;
                        if(it == ring.const_end()) it = ring.const_begin();
                    }

                    count--;
                }
                return;
            }
            index++;
        }
    }else{
        auto it = ring.const_end();
        it--;
        while(it != ring.const_end()){
            
            if(index == start_pos){

                while(count > 0){

                    counter1 = 0;
                    counter2 = 0;

                    while(counter1 < len1){
                        
                        if(direct1 == true){
                            ring1.insertEnd_iterator(it);
                        }
                        else{
                            ring1.insertFront_iterator(it);
                        }
                        counter1++;
                        it--;
                        if(it == ring.const_end()) it--;
                    }

                    while(counter2 < len2){
                        
                        if(direct2 == true){
                            ring2.insertEnd_iterator(it);
                        }
                        else{
                            ring2.insertFront_iterator(it);
                        }
                        counter2++;
                        it--;
                        if(it == ring.const_end()) it--;
                    }

                    count--;
                }
                return;
            }
            index++;
            it--;
        }
    }

}

template <typename Key, typename Info>
void split_key ( const Ring <Key, Info>& ring, const Key& start_key, int start_occ, bool direct, int count,
Ring <Key, Info>& ring1, bool direct1, int len1,
Ring <Key, Info>& ring2, bool direct2, int len2){

    //checking if ring is empty
    if(ring.isEmpty()){
        cout << "Ring is empty, wrong input.";
        return;
    }
    //checking start_occ is less than 1
    if(start_occ < 1){
        cout << "Wrong input of starting occurance.";
        return;
    }
    //checking count
    if(count < 1){
        cout << "Count cannot be lower than 1, wrong input.";
        return;
    }
    //checking if lenght of ring1 and ring2 are both equal to 0
    if(len1 < 1 && len2 < 1){
        cout << "Lenght of ring1 and ring2 is 0, cannot split into rings, wrong input.";
        return;
    }
    //checking if ring1 and ring2 are empty
    if(ring1.isEmpty() == 0 || ring2.isEmpty() == 0){
        cout << "Both ring1 and ring2 must be empty, wrong input.";
        return;
    }

    int index = 0;
    int counter1;
    int counter2;

    int start_pos = ring.return_index(start_key, start_occ);

    if(direct == true){
        for(auto it = ring.const_begin(); it != ring.const_end(); it++){
            
            if(index == start_pos){

                while(count > 0){

                    counter1 = 0;
                    counter2 = 0;

                    while(counter1 < len1){
                        
                        if(direct1 == true){
                            ring1.insertEnd_iterator(it);
                        }
                        else{
                            ring1.insertFront_iterator(it);
                        }
                        counter1++;
                        it++;
                        if(it == ring.const_end()) it = ring.const_begin();
                    }

                    while(counter2 < len2){
                        
                        if(direct2 == true){
                            ring2.insertEnd_iterator(it);
                        }
                        else{
                            ring2.insertFront_iterator(it);
                        }
                        counter2++;
                        it++;
                        if(it == ring.const_end()) it = ring.const_begin();
                    }

                    count--;
                }
                return;
            }
            index++;
        }
    }else{
        auto it = ring.const_end();
        it--;
        while(it != ring.const_end()){
            
            if(index == start_pos){

                while(count > 0){

                    counter1 = 0;
                    counter2 = 0;

                    while(counter1 < len1){
                        
                        if(direct1 == true){
                            ring1.insertEnd_iterator(it);
                        }
                        else{
                            ring1.insertFront_iterator(it);
                        }
                        counter1++;
                        it--;
                        if(it == ring.const_end()) it--;
                    }

                    while(counter2 < len2){
                        
                        if(direct2 == true){
                            ring2.insertEnd_iterator(it);
                        }
                        else{
                            ring2.insertFront_iterator(it);
                        }
                        counter2++;
                        it--;
                        if(it == ring.const_end()) it--;
                    }

                    count--;
                }
                return;
            }
            index++;
            it--;
        }
    }

}

//PART 3 OF TASK 3

//the function "listing" creats a Ring of words from a Dictionary 
//ordered by word occurrence count,
//words with the same counter value are ordered lexically within the listing
Ring<int, string>& listing (const Dictionary<string, int> &dict){
    
    Ring<int,string> *r = new Ring<int,string>();

    //find lenght of tree
    int n = dict.length();

    string table_of_keys[n];
    int table_of_info[n];

    dict.iterateOver(table_of_keys, table_of_info);

    //sorting arrays
    for(int i = 0; i < n; i++)
	{		
		for(int j = i+1; j < n; j++)
		{
			if( table_of_info[i] >  table_of_info[j] )
			{
				int temp = table_of_info[i];
				table_of_info[i] = table_of_info[j];
				table_of_info[j] = temp;

                string temp2 = table_of_keys[i];
                table_of_keys[i] = table_of_keys[j];
				table_of_keys[j] = temp2;
			}
		}
	}

    //inserting into ring
    for(int i = 0; i < n; i++){
        r->insertEnd(table_of_info[i], table_of_keys[i]);
    }

    return *r;
}
//
//  Sequence.h
//  CS32Homework1A
//
//  Created by Sophia Liu on 1/14/21.
//

#ifndef Sequence_h
#define Sequence_h
#include <string>

using ItemType = std::string;
class Sequence
{

    public:
    Sequence();
    ~Sequence(); //destructor
    Sequence(const Sequence& other); //copy constructor
    Sequence& operator=(const Sequence& other); //assignment operator
    bool empty() const;
    int size() const;
    int insert(int pos, const ItemType& value);
    int insert(const ItemType& value);
    bool erase(int pos);
    int remove(const ItemType& value);
    bool get(int pos, ItemType& value) const;
    bool set(int pos, const ItemType& value);
    int find(const ItemType& value) const;
    void swap(Sequence& other);
    void dump() const;
    
    private:
    struct node
    {
        ItemType data;
        node* next;
        node* prev;
    };
    node* head;
    node* e;
    node* target;
};

int subsequence(const Sequence& seq1, const Sequence& seq2);
void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result);


#endif /* Sequence_h */

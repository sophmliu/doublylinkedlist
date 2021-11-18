//
//  Sequence.cpp
//  CS32Homework1A
//
//  Created by Sophia Liu on 1/14/21.
//

#include <stdio.h>
#include "Sequence.h"
#include <iostream>
#include <cassert>
#include <cstdlib>

using namespace std;
int subsequence(const Sequence& seq1, const Sequence& seq2);
void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result);

Sequence::Sequence()
{
    head = new node;
    head->prev = head;
    head->next = head;
}

Sequence::~Sequence()
{
  node* current = head->next;
  node* Next;

  while (current != head) {
      Next = current->next;
      delete current;
      current = Next;}
    
  delete head;
}

Sequence::Sequence(const Sequence& other)//copy constructor
{
    node* n;
    n = new node;
    n->prev = n;
    n->next = n;
    head = n;
    // if other is empty the new sequence is empty too.
    if (other.size() > 0){
        int pos = 0;
        for (node* p = other.head->next; p!= other.head; p=p->next)
        {
          insert(pos, p->data);
          pos++;
        }
    }
}

Sequence& Sequence:: operator=(const Sequence& other) //assignment operator
{
    if (this != &other)
    {
        Sequence temp(other);
        swap(temp);
    }
    return *this;
}
 
bool Sequence::empty() const
{return size() == 0;}// Return true if the sequence is empty, otherwise false.

int Sequence::size() const
{//traverse list and count number of items
    int count = 0;
    for (node* p = head->next; p!= head; p=p->next)
        {count++;}
    return count;
}// Return the number of items in the sequence.

int Sequence::insert(int pos, const ItemType& value)
{
    int s_sizeBefore = size();
    if (pos >= 0 && pos <= size()){
        int count = 0;
        target = head; //default if pos=0;
        for (node* p = head->next; p != head && count<pos; p=p->next)
            {count++;
             target = p;
            } //target node is the node w next pointer to target pos
        node* n;
        n=new node;
        n->next=target->next;
        n->prev=target;
        n->data=value;
        target->next->prev=n;
        target->next=n;
        }
        
    if (size() > s_sizeBefore) //check if insertion succeeded
        return pos;
    
    
    return -1;
    
}
  // Insert value into the sequence so that it becomes the item at
  // position pos. The original item at position pos and those that
  // follow it end up at positions one higher than they were at before.
  // Return pos if 0 <= pos <= size() and the value could be
  // inserted. (It might not be, if the sequence has a fixed capacity,
  // e.g., because it's implemented using a fixed-size array.)  Otherwise,
  // leave the sequence unchanged and return -1.  Notice that
  // if pos is equal to size(), the value is inserted at the end.

int Sequence::insert(const ItemType& value)
{
    int sizeNow = size();
    if (sizeNow==0){insert(0,value); return 0;}
    if (sizeNow>0){
    int count = 0;
    for(node* p = head->next; p != head && count < size() && value > p->data; p=p->next)
        {count++;}
    if (insert(count, value) == count)
        return count;}
    return -1;
}
  // Let p be the smallest integer such that value <= the item at
  // position p in the sequence; if no such item exists (i.e.,
  // value > all items in the sequence), let p be size().  Insert
  // value into the sequence so that it becomes the item in position
  // p.  The original item at position p and those that follow it end
  // up at positions one higher than before.  Return p if the value
  // was actually inserted.  Return -1 if the value was not inserted
  // (perhaps because the sequence has a fixed capacity and is full).

bool Sequence::erase(int pos)
{
    int s_sizeBefore = size();
        
    if (0 <= pos && pos < size())
    {
    int count = 0;
    target = head; //default if pos = 0
    for (node* p = head->next; p!= head && count<pos; p=p->next)
        {count++;
         target = p;} //target node is the node w next pointer to target pos
    node *t=target->next; //copy pos
    target->next=t->next;
    target->next->prev=target;
    delete t; //delete pos
    }
    
    if(size()<s_sizeBefore)
        return true;
    
    return false;
}
  // If 0 <= pos < size(), remove the item at position pos from
  // the sequence (so that all items that followed that item end up at
  // positions one lower than they were at before), and return true.
  // Otherwise, leave the sequence unchanged and return false.

int Sequence::remove(const ItemType& value)
{
    int removed = 0; //count items removed
    int s_sizeBefore = size();
    for (int count = 0; count < s_sizeBefore; count++)
    {
        int c = 0;
    for (node* p = head->next; p != head && p->data != value; p=p->next)
        {c++;}
    if (c < size())
        {erase(c);
         removed++;}}
    
    return removed;
}
  // Erase all items from the sequence that == value.  Return the
  // number of items removed (which will be 0 if no item == value).
 

bool Sequence::get(int pos, ItemType& value) const
{
    node * target_ = nullptr;
    if (pos < size() && pos >= 0){ //can't get values from an empty sequence
    int count = 0;
    for (node* p = head->next; count < pos+1; p=p->next)
        {count++;
         target_ = p; //target at pos
        }
    if (target_ != nullptr)
        {value = target_->data;
        return true;}
    }
    return false;
}
  // If 0 <= pos < size(), copy into value the item at position pos
  // of the sequence and return true.  Otherwise, leave value unchanged
  // and return false.


bool Sequence::set(int pos, const ItemType& value)
{
    node * target_ = nullptr;
    if (pos < size() && pos >= 0){ //can't set value of head
    int count = 0;
    for (node* p = head->next; count < pos+1; p=p->next)
        {count++;
         target_ = p; //target at pos
        }
    if (target_ != nullptr) //can't set value that doesn't exist
        {target_->data = value;
        return true;}
    }
    return false;
}
  // If 0 <= pos < size(), replace the item at position pos in the
  // sequence with value and return true.  Otherwise, leave the sequence
  // unchanged and return false.

int Sequence::find(const ItemType& value) const
{
    int t = -1;
    int count = 0;
    for (node* p = head->next; p != head && count < size(); p=p->next)
        {
         if (p->data==value)
            {t = count;
             break;}
         count++;
        }
    return t;
}
  // Let p be the smallest integer such that value == the item at
  // position p in the sequence; if no such item exists, let p be -1.
  // Return p.

void Sequence::swap(Sequence& other)
{
    node * n = other.head;
    other.head = head;
    head = n;
}
  // Exchange the contents of this sequence with the other one.

///////NON MEMBER FUNCTIONS
int subsequence(const Sequence& seq1, const Sequence& seq2)
{
//initialize variables
int seq2size = seq2.size(); int seq1size = seq1.size();
ItemType value2; ItemType value1;
ItemType& v2 = value2; ItemType& v1 = value1;
ItemType valueTwo; ItemType& vTwo = valueTwo;
ItemType valueOne; ItemType& vOne = valueOne;
seq2.get(0, v2); //first value seq2
int pos1 = -1;
int q = 0;

//eliminate ineligible conditions
if (seq1size < seq2size)
    return -1;
if (seq2.empty())
    return -1;
if (seq1.find(v2) == -1)
    return -1;
if (seq1size < (seq1.find(v2)+seq2size))
    return -1;
    
for (int k = 0; k < seq1size; k++)
    {seq1.get(k,v1);
     if (v1==v2){
         q = 0;
        for(int n = 0; (k + n) < seq1size && n < seq2size; n++)
        {
            seq1.get(k+n, vOne); seq2.get(n,vTwo);
            if (vOne != vTwo)
                break;
            q++;
        }
        if (q == seq2size)
            {pos1 = k; break;}}
    }
return pos1;
}


void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result)
{
    int m = seq1.size(); int n = seq2.size();
    ItemType value2; ItemType value1;
    ItemType& v2 = value2; ItemType& v1 = value1;
    
    if (m==0 && n!= 0)
    {result = seq2;}
    
    if (n==0 && m!=0)
    {result = seq1;}
    
    if (m==n)
    {int k = 0;
     for (int j = 0; j < m; j++){
     seq1.get(j,v1); seq2.get(j,v2);
        if (k < 2*m){
        result.insert(k, v1); result.insert(k+1, v2);
        }
        k = k+2;
    }}
    
    if (m < n && m !=0)
    {int k = 0;
        for (int j = 0; j < m; j++){
        seq1.get(j,v1); seq2.get(j,v2);
           if (k < 2*m){
           result.insert(k, v1); result.insert(k+1, v2);
           }
           k = k+2;
       }
     
        for (int k = 0; k < n - m; k++){
        seq2.get(m+k, v2);
        result.insert(2*m + k, v2);
        }
    }
    
    if (m > n && n != 0)
    {int k = 0;
        for (int j = 0; j < n; j++){
        seq1.get(j,v1); seq2.get(j,v2);
           if (k < 2*n){
           result.insert(k, v1); result.insert(k+1, v2);
           }
           k = k+2;
       }
     
        for (int k = 0; k < m - n; k++){
        seq1.get(n+k, v1);
        result.insert(2*n + k, v1);
        }
    }
    
}

//HELPER FUNCTIONS

            
void Sequence::dump() const
{
    for (node* p = head->next; p!= head; p=p->next)
    cerr << p->data;}
    cerr << ";"<< size() << endl;
}

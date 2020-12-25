//NAME: ABHISHEK AMOL MISHRA AND NETID: AAM190011
#ifndef LLIST_H
#define LLIST_H
#include "Node.h"
#include<iostream>

/*Here, we have a forward class declaration so that we can appropriately account
for the overloaded << operator for the LList*/

class LList;

std::ostream& operator << (std::ostream&, LList &);


class LList
{
   public:
       /*In the public access, we create our constructors and destructors
        - a default constructor
        - a copy constructor that will copy a whole list
        - a constructor that takes in a Node pointer and sets that as the head of the linked list
        - a destructor
       */
      LList();
      LList(LList &putIN);
      LList(Node *&headInput);
      ~LList();

      /*We create setters and getters for our variables in LList object*/
      void setHead(Node *value)
         {head = value;}
      Node* getHead()
         {return head;}

      /*Additionally, we create these important functions
        - a sort function
        - an overloaded [] operator that will allow us to access the linked list through the [] operator
        - an overloaded >> operator that will insert a node into the head of the linked list
        - a friend function that is the overloaded << operator that will allow us to display the linked list
        - a derive function that derives the Nodes in a linked list*/
      void sort();
      const Node* operator[] (int position);
      void operator >> (Node*&);
      friend std::ostream& operator << (std::ostream&, LList &);
      void toDerive();
      void toClean();

   private:
       //here we create a Node pointer called head that stores the head of the linked list
      Node *head;
};

#endif // LLIST_H

//NAME: ABHISHEK AMOL MISHRA AND NETID: AAM190011
#ifndef NODE_H
#define NODE_H
#include<string>
#include<ostream>
#include<iostream>

/*We make a forward declaration so that we include our
overloaded Node << operator*/
class Node;

std::ostream& operator << (std::ostream&, const Node &);

class Node
{
   public:
      /*We make constructors and deconstructors
        - a default constructor
        - a constructor that uses a Node object to do a deep copy
        - an overloaded constructor which takes in all the inputs of a Node object
        - a destructor
      */
      Node();
      Node(Node *&copyNode);
      Node(float Couter, float Cinner, float Cexp, std::string Ctrig, Node *Cnext);
      ~Node();

      /*
      Here we make setters and getters for the instance variables in our Node class
      */
      void setOuter(float outerCoefficient)
         { outer=outerCoefficient; }
      float getOuter()const{ return outer; }

      void setInner(float innerCoefficient)
         { inner=innerCoefficient; }
      float getInner()const{ return inner; }

      void setExp(float exponent)
         { exp=exponent; }
      float getExp ()const{ return exp; }

      void setTrig(std::string trigID)
         { trig=trigID; }
      std::string getTrig()const{ return trig; }

      void setNext(Node *next_pointer)
         { next=next_pointer; }
      Node* getNext()const{ return next; }

      //Here we make a friend function that is an overloaded << that allows us to print out the contents of a node
      friend std::ostream& operator << (std::ostream&printO, const Node &newNode);

   private:
       /*
       Here we define our variables privately for the Node class
       */
      float outer;
      float inner;
      float exp;
      std::string trig;
      Node *next;
};
#endif

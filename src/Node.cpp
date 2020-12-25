//NAME: ABHISHEK AMOL MISHRA AND NETID: AAM190011
#include "Node.h"
#include<iostream>
#include<fstream>

Node::Node()
{
    /*In the default constructor, we set all of our numerical variables to 1 while we set our
    string variable to "" and next Node pointer to nullptr*/
    outer=1;
    inner=1;
    exp=1;
    trig="";
    next=nullptr;

}

Node::Node(Node *&copyNode)
{
    /*In one of our overloaded constructors, we take in a Node pointer passed in by reference
    and set our variables to the instance variables of the Node pointer passed in*/
    outer=copyNode->getOuter();
    inner=copyNode->getInner();
    exp=copyNode->getExp();
    trig=copyNode->getTrig();
    next=nullptr;
}

Node::Node(float Couter, float Cinner, float Cexp, std::string Ctrig, Node *Cnext)
{
    /*In this overloaded constructor, we pass 5 arguments and then proceed to make
    our class' instance variables equal to the arguments passed based on with respect to the order and data type of the variables*/
    outer=Couter;
    inner=Cinner;
    exp=Cexp;
    trig=Ctrig;
    next=Cnext;
}


std::ostream& operator << (std::ostream&printO, const Node &newNode)
{
    if(newNode.getTrig()=="sin" || newNode.getTrig()=="cos" || newNode.getTrig()=="tan" || newNode.getTrig()=="sec")
    {
        /*If we have a trig term, we first will showcase the outer-coefficients*/
        if(newNode.getOuter()<0)
        {
            /*If the outer coefficient is less than 0, then we negate the outer-coefficient and display
            that as the sign has already been taken care of in the LList << operator*/
            float temp= newNode.getOuter();
            temp = -1*temp;
            if(temp!=1)
            {
                /*if it is equal to one, then we don't show this outer coefficient as an absence of one implies that the
                outer-coefficient is equal to one*/
                printO<<temp;
            }
        }
        else if(newNode.getOuter()>0)
        {
            /*If it is greater than 0, then we simply follow print out the outer-coefficient for the exception of
            if the outer-coefficient is equal to one. if it is equal to one, then we don't show this
            outer coefficient as an absence of one implies that the outer-coefficient is equal to one*/
            if(newNode.getOuter()!=1)
            {
                printO<<newNode.getOuter();
            }
        }

        /*According to the trig term, we output the appropriate term with a space for better formatting*/
        if(newNode.getTrig()=="sin")
        {
            printO<<"sin ";
        }
        else if(newNode.getTrig()=="cos")
        {
            printO<<"cos ";
        }
        else if(newNode.getTrig()=="tan")
        {
            printO<<"tan ";
        }
        else if(newNode.getTrig()=="sec")
        {
            //if it is sec, then we insert the exponent as the output of a sec - in our case - has to be with the squared power
            printO<<"sec^"<<newNode.getExp()<<" ";
        }

        /*Next we display the inner coefficient and it is equal to one, then we don't show this
            outer coefficient as an absence of one implies that the outer-coefficient is equal to one*/
        if(newNode.getInner()!=1)
        {
            printO<<newNode.getInner();
        }

        /*We finally insert the x to finish the output for trig terms*/
        printO<<"x";
    }
    else
    {
        /*If the exponent is not equal to 0 and the outer variable is not equal to 0, then we know that we have
        our terms with a x in the term*/
        if(newNode.getExp() != 0 && newNode.getOuter() != 0)
        {
            /*If the outer coefficient is less than 0, then we negate the outer-coefficient and display
            that as the sign has already been taken care of in the LList << operator*/
            if(newNode.getOuter()<0)
            {
                float temp = newNode.getOuter();
                temp = -1*temp;
                if(temp!=1)
                {
                        printO<<temp;
                }
            }
            else if(newNode.getOuter()>0)
            {
                /*If it is greater than 0, then we simply follow print out the outer-coefficient for the exception of
                if the outer-coefficient is equal to one. if it is equal to one, then we don't show this
                outer coefficient as an absence of one implies that the outer-coefficient is equal to one*/
                if(newNode.getOuter()!=1)
                {
                    printO<<newNode.getOuter();
                }
            }

            /*  - If the exponent is just one, then we simply put out the x and we are done with the term.
                - However, other than that, we show the x with the ^ and then output the exponent terms*/
            if(newNode.getExp()==1){
                printO<<"x";
            }
            else{
                printO<<"x^"<<newNode.getExp();
            }
        }
        else
        {
            /*If we come here, then we know that we are simply outputting the constant*/

            /*If the outer coefficient is less than 0, then we negate the outer-coefficient and display
            that as the sign has already been taken care of in the LList << operator*/
            if(newNode.getOuter()<0)
            {
                float temp = newNode.getOuter();
                temp = -1*temp;
                printO<<temp;
            }
            else if(newNode.getOuter()>0)
            {
                 /*If it is greater than 0, then we simply follow print out the outer-coefficient for the exception of
                if the outer-coefficient is equal to one. if it is equal to one, then we don't show this
                outer coefficient as an absence of one implies that the outer-coefficient is equal to one*/
                printO<<newNode.getOuter();

            }
        }
    }
    return printO;
}

Node::~Node()
{
    //We don't do anything here as we don't have a dynamically allocated variable in the Node class
}

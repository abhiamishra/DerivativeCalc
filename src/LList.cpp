//NAME: ABHISHEK AMOL MISHRA AND NETID: AAM190011
#include "LList.h"
#include "Node.h"


LList::LList()
{
    //in the default constructor, we set the head as nullptr
    head = nullptr;
}

LList::LList(Node *&headInput)
{
    //we set the head as the Node pointer that is passed in and then, we set the Node variable passed in to nullptr
    head = headInput;
    headInput = nullptr;
}

LList::LList(LList &putIN)
{
    /*we create a new Node pointer that we set as the head of hte linked list that is put in as hte parameter*/
    Node *temp_head = putIN.getHead();

    /*we set head as a new Node by using the Node constructor and using the temp_head node. In essence,
    we copy the contents of the head of the linked list to the head variable in this constructor*/
    head = new Node(temp_head);

    /*we create an anchor Node pointer which will allow us to set back head to it's right place*/
    Node *anchor=head;

    while(temp_head->getNext()!=nullptr)
    {
        /*While the next Node pointer is not equal to nullptr, we
        move the temp_head pointer so that we can access the next elements in the linked list.*/
        temp_head=temp_head->getNext();

        /*We create a new Node pointer using the Node constructor passing in the Node pointer of the old linked
        list to copy it's contents into the new Node pointer*/
        Node *temp = new Node(temp_head);

        /*We start creating the new linked list by connecting the head's pointer to the temp pointer we created
        and then setting the head to that pointer so that we can continue building our lsit*/
        head->setNext(temp);
        head=head->getNext();
    }

    //Finally, we set the head back to its anchor allowing the head to the be the head of the new linked list that we created
    head=anchor;
}

void LList::sort()
{
    /*In this sort, we apply a bubble sort. To do this, we have
    a bubble_flag that is set to 0. We then make two Node pointers - one called head_move
    which will be used to traverse the list and one called left that is set as nullptr and represents
    the Node left of our traversal pointer*/
    int bubble_flag = 0;
    Node *head_move=head;
    Node *left=nullptr;

    do
    {
        //setting the flag to 0 every time we go so that we don't have any left-over mistakes
        bubble_flag = 0;

        /*We do this while the next isn't equal to nullptr because we are swaping the element
        ahead with our current one so to avoid swapping nulls, we set the while loop with
        this conditional*/
        while(head_move->getNext()!=nullptr)
        {
            //we make a temp Node here that access the Node next to our traversal node head_move
            Node *temp = head_move->getNext();

            if(( head_move->getExp() ) < ( temp->getExp() ) )
            {
                /*If the current node is smaller than the next node, we will swap!*/

                /*If left is nullptr, that means we are swapping on the left-end
                of the linked list*/
                if(left==nullptr)
                {
                    //We set the current Node's next pointer = the next Node's next pointer
                    head_move->setNext(temp->getNext());

                    //we set the next Node's next pointer = current Node
                    //now the two nodes have switched positions with the links all set up.
                    temp->setNext(head_move);

                    //we now set our head to head_move and then set our head_move to that value.
                    /*this allows our head to move allowing us to keep track of how we are moving
                    and then continue sorting offset from the first position*/
                    head=temp;
                    head_move=temp;

                    //we move our head_move to the next Node so that we can move up our list
                    head_move=head_move->getNext();

                    /*We then make our left pointer = to our temp pointer as we have moved forward,
                    our left pointer needs to move one*/
                    left=temp;

                    //we set the flag to 1 to indicate that we have swapped elements
                    bubble_flag = 1;
                }
                else if(temp==nullptr)
                {
                    /*We make a new node called right that is set to head.
                    From there, we have a while loop to get to the position before the left Node pointer
                    by swapping until the next Node of our right isn't equal to our left one*/
                    Node *right = head;
                    while((right->getNext())->getExp()!=left->getExp())
                    {
                        right=right->getNext();
                    }

                    /*There, we set this Node's next pointer to where our current Node pointer is
                    Then we make the current Node pointer's next pointer equal to our left.
                    Now those two have swapped*/
                    right->setNext(head_move);
                    head_move->setNext(left);

                    /*After this, the right is set to nullptr so that we don't mess up the list in any order.
                    Finally, we set the flag for the swap indicating that we have made a swap*/
                    right=nullptr;
                    bubble_flag = 1;
                }
                else
                {
                    /*Else, we are swapping Nodes in the middle:
                        - First, we set the left's next node pointer to the right-ward allowing those two
                            to get connected
                        - Then we set our current head_move Node pointer's next pointer to the right-ward's next
                            pointer
                        - Finally, we set the right-ward's next pointer to the current.
                        This way, we have made sure all the surrounding Node's relations have been left undisturbed*/
                    left->setNext(temp);
                    head_move->setNext(temp->getNext());
                    temp->setNext(head_move);

                    /*We make left equal to our rightward one so that we can move our left pointer up one
                    since our original Node pointer moved ahead*/
                    left=temp;

                    //Finally, we set our flag to 1 so that we indicate that we initiate a swap
                    bubble_flag = 1;
                }
            }
            else
            {
                /*If it is not less than, then we simply move our left pointer ahead by setting it
                to head_move and then, finally, move our own head_move ahead by setting it temp*/
                left=head_move;
                head_move=temp;
            }
        }

        /*After one pass, we set head_move to what head is allowing us to either reset or
        move one ahead of the swap we've done and finally, we make our left=nullptr so we
        can ensure that we can swap again safely*/
        head_move=head;
        left=nullptr;
    }
    while(bubble_flag==1);
    /*having a do while loop allows us greater and control and we set the condition that as long as
    the swap setting flap is set to 1, we kepe doing the sort*/

    /*Here is why we set the trig_exp to -20 and keep subtracting. By doing this, we are
    able to correctly put the trig terms at the end as the list sorts from greatest (at the front)
    to the smallest (at the end). By having very large negative numbers like -20 and subtracting
    one for every new one you add, we can correctly account for the trig terms wanting to be at the end of the list*/
}


const Node* LList::operator[] (int position)
{
    /*We create a Node pointer that will return the position that the user wanted through their
    numerical argument that they entered in*/
    Node *returNode=head;

    /*We loop the number of times the user wanted us to loop till. In that loop, we set the returNode to it's next node,
    allowing us to traverse through the linked list*/
    for(int i=0; i<position; i++)
    {
        returNode=returNode->getNext();
    }

    /*after the loop is done, we've accessed the correct Node position and we make a const Node variable which will be the actual
    variable that is returned. We do this as the return type of this function is a const Node * not a Node * */
    const Node *ret = returNode;
    return ret;
}

std::ostream& operator << (std::ostream&printL, LList &starter)
{
    /*We make a const Node * that is set to the head of the linked list*/
    const Node *traversal = starter[0];

    //we make a counter variable that will be used for identifying when to place -/+ signs
    int counter = 0;

    while(traversal!=nullptr)
    {
        /*If the counter is not equal to 0, we can display -/+ signs like this:  _-_ or _+_ where the _ signifies a space*/
        if(counter!=0)
        {
            /*If the outer variable of the node is less than 0, then we put out _-_ as the outer variable is less than
            0 which means they are negative. This means, they merit a - sign.*/
            if(traversal->getOuter()<0)
            {
                printL<<" - ";

            }

            /*If the outer variable of the node is greater than 0, then we put out _+_ as the outer variable is greater than
            0 which means they are positive. This means, they merit a + sign.*/
            else if(traversal->getOuter()>0)
            {
                /*Before we simply output a + sign, we first access the previous Node.
                If the previous Node isn't equal to 0 and the position of the previous Node isn't equal to 0,
                only then do we output a + sign

                The reasoning behind this is because we want to make sure when we have constants
                in the beginning or the middle. This allows us to safe-guard against those edge-cases*/
                    const Node *printing = starter[counter-1];
                    int backInt = counter-1;
                    if(printing->getOuter()!=0 || backInt != 0)
                    {
                        printL<<" + ";
                    }
            }
        }
        else
        {
            /*If we arrive here, then we are at the first Node position of the linked list where the output is slightly different*/

            /*If the outer variable is less than 0, we simply output a - sign without the spaces
            since the outer variable is negative.*/
            if(traversal->getOuter()<0)
            {
                printL<<"-";
            }

            /*In the beginning, we have a very interesting edge case if we only have a constant. This is why this
            case gets resolved here instead of the Node << as we have more control over here. We simply the access the next
            Node and if that is equal to nullptr, then we know there is only one constant in the Linked List. From there,
            we simply output a 0*/
            else if(traversal->getOuter()==0){
                const Node *printing = starter[counter+1];
                if(printing==nullptr){
                    printL<<0;
                }

            }
        }

        /*We make a new Const Node * equal to the dereference of the traversal Node pointer. This is because
        we pass the Const Node * into the overloaded Node << which accepts a const Node */
        const Node printer = *traversal;
        printL<<printer;

        //we aggregate the counter so that we can reflect that we've moved upward in the linked list
        counter++;

        // we set the traversal to the next pointer through the [] operator and the counter which allows us to access the next pointer
        traversal = starter[counter];
    }

    /*We use the printL ostream object to place a newline character and then return the ostream object so that we can link various
    overloaded LList << operators*/
    printL<<"\n";
    return printL;
}

void LList::operator >> (Node*&inNode)
{
    /*We create a temporary Node pointer that stores the address of head*/
    Node *temp = head;

    //we set the Node that is passed in's next pointer to the head address
    inNode->setNext(temp);

    /*we then set head to the Node pointer that is passed in. Now, the new node has been added to the starting of the linked list
    and the corresponding terms have accordingly shift rightward.*/
    head = inNode;
}

void LList::toDerive()
{
    /*Here we set an anchor Node pointer that is set to head. It will help us set head back to the beginning*/
    Node *traversal = head;
    while(head!=nullptr)
    {
        /*We will go through to the whole list until our current Node pointer isn't equal to nullptr*/
        if(head->getTrig()=="sin")
        {
            float derivedOuter = (head->getOuter()*head->getInner());
            /*If our trig term is sin, we:
                - set the trig term to "cos" since the derivative of sin is cos
                - set the outer coefficient to the product of the outer and inner coefficient
                    due to the chain rule*/
            head->setTrig("cos");
            head->setOuter(derivedOuter);
        }
        else if(head->getTrig()=="cos")
        {
            float derivedOuter = (head->getOuter()*head->getInner()*(-1));
            /*If our trig term is sin, we:
                - set the trig term to "sin" as the derivative of cos is -sin
                - set the outer coefficient to the product of the outer and inner coefficient
                    due to the chain rule and -1 due to the fact that the derivative of cos is -sin*/
            head->setTrig("sin");
            head->setOuter(derivedOuter);
        }
        else if(head->getTrig()=="tan")
        {
            float derivedOuter = (head->getOuter()*head->getInner());
            /*If our trig term is sin, we:
                - set the trig term to "sec" as the derivative of tan is sec^2
                - set the exponent term to 2 as the derivative of tan is sec^@
                - set the outer coefficient to the product of the outer and inner coefficient
                    due to the chain rule*/
            head->setTrig("sec");
            head->setOuter(derivedOuter);
            head->setExp(2);
        }
        else if(head->getExp()==0)
        {
            /*We set the outer coefficient to 0 due to the constant rule
            as the derivative of a constant is 0*/
            head->setOuter(0);
        }
        else if(head->getExp()>0 || head->getExp()<0)
        {
            float derivedOuter = (head->getOuter()*head->getExp());
            float derivedExp = (head->getExp()-1);
            /*  - We set the outer coefficient to the product of outer and exponent due to the exponent rule.
                - Then we set the exponent term to the original exponent term-1 due to the
                    exponent rule of derivatives*/
            head->setOuter(derivedOuter);
            head->setExp(derivedExp);
        }

        /*We access the next Node in the linked list so that we could do this again*/
        head=head->getNext();
    }
    /*Finally, we set head back to its anchor allowing us to get a fully derived linked list*/
    head=traversal;
}

void LList::toClean(){
     /*While the next node isn't nullptr, we create a new Node pointer that points to the next Node*/
    while(head->getNext()!=nullptr)
    {
        Node *temp=head->getNext();

        /*We then set our current node's next node to the next node of the temp Node pointer we created. In essence,
        we have set our current node's next node to the second element after it.*/
        head->setNext(temp->getNext());

        //we set the next node's next pointer to nullptr so that there is no back-alley entrance to the linked list
        temp->setNext(nullptr);

        /*We've made all of our connections connect to the right nodes so now, we can delete the next node*/
        delete temp;
    }

    /*Here, we make a Node pointer that points to head. we then delete the hold pointer and then set head nullptr ensuring that
    we don't have any nullptr*/
    Node *hold = head;
    delete hold;
    head=nullptr;
}

LList::~LList()
{
    /*At this point, we've deleted every other Node in front of the head of the linked list.
    Finally, we delete our head pointer*/
    delete head;
}

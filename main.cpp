//NAME: ABHISHEK AMOL MISHRA AND NETID: AAM190011
#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include<math.h>
#include "Node.h"
#include "LList.h"

using namespace std;

int main()
{
    /*Here, we input the name of the file by creating a string variable that will hold our input and then
    using cin>> to register that input into the variable*/
    string inputName;
    cout<<"Please the name of your file: ";
    cin>>inputName;

    /*Using the input provided, we open an ifstream called input that allows us to get the lines from the input file
    and then we open an ofstream called output with the name of the file being "derive.txt". Both are opened with the
    ios::binary flag to ensure that we output in Unix format*/
    ifstream input(inputName, ios::binary|ios::in);
    ofstream output("derive.txt", ios::binary|ios::out);

    //this variable will store each line of the file that we access
    string lineInput;

    //if the two filestreams are safe to open, then only do we process with the parsing
    if(input.good() && output.good())
    {
        //we make a new node pointer and set that as the head of the linked list.
        Node *initialHead = nullptr;
        LList ListOfEq(initialHead);

        //Here we make a new Node. This is our node that will house our parsing results
        Node *newNode = new Node;

        //while we keep getting input from the file, we're going to access each line and parse the lines appropriately
        while(getline(input,lineInput))
        {
            //we make another variable that will allow us to parse the nodes.
            string parseLine = lineInput;

            /*we make a float variable called trig_exp which allows us to place trig expressions at the
            back of the linked list when we will sort them. */
            float trig_exp=-20;

            /*we will do a loop while parseLine isn't equal to nothing. this allows us to capture
            one node and then substring the parseLine to access the other nodes. In this fashion, we
            can loop the number of times there are terms as the terms in a file aren't set in stone*/
            while(parseLine!="")
            {
                /*We have a variable called end_space which stores the position of the space between
                the term and the punctuation symbol. In some cases, there might not be a space in which
                case the end_space becomes the last position of the line*/
                int end_space=0;

                /*findX is a variable that records the position of the x variable in a term and helps us to
                have an anchor so that we can move left-ward/right-ward for recording exponents/inner/outer coefficients*/
                int findX=0;

                /*posneg is a variable that allows us to store whether the coefficient is positive or negative. Putting this in
                a variable allows for easier parsing as then you just have to take care of the coefficient*/
                float posneg=1;

                /*the variable numParse allows us to record the fact that we analyzed a number once. If there's a two digit
                or three digit coefficient, then it might record the actual number and then on the consequent loop,
                record the number again. This allows us to only analyze the number once*/
                int numParse=0;

                //we use the .find function to find the first space in the parseLine string
                end_space=(int)parseLine.find(' ');

                /*we store the boolean value if the next space is a punctuation (+/-). If it does,
                then we have the correct space. If it doesn't (spaces inside the trig terms,etc), we find
                the correct space*/
                bool cor_space = ispunct(parseLine.at(end_space+1));

                /*This counter variable allows us to keep track if we ever loop just too many times
                in case of single lines with constants*/
                int breaker=0;

                /*If the next space wasn't a punctuation, we initiate a while loop*/
                if(cor_space==false)
                {
                    /*While the cor_space remains not true, we:
                        - add one to our end_space
                        - find the new space from the location as indicated by the new value of end_space
                        - we set cor_space to T/F whether the next space is a punctuation
                        - we add one to the counter variable*/
                    while(cor_space != true)
                    {
                        end_space=end_space+1;
                        end_space = (int)parseLine.find(' ',(end_space));
                        cor_space = ispunct(parseLine.at(end_space+1));
                        breaker++;

                        /*If the breaker variable is more than the size of the string and the cor_space
                        variable just ends up false every time, we know we have a term with no space to execute our
                        normal substring. In that case, we set end_space to -1 (correct space not found) and cor_space
                        to true so that we can break out of the loop*/
                        if(breaker > (int)parseLine.size() && cor_space==false)
                        {
                            end_space=-1;
                            cor_space=true;
                        }
                    }

                }


                /*we make a string variable called term. this term is the substring of a parseLine housing one term and
                will be used for parsing*/
                string term="";

                if(end_space==-1)
                {
                    /*if end_space is -1, we substring from the starting of the string till the end and then set the parseLine
                    to "" as the only location where we don't have a correct space is the end of the line*/
                    term=parseLine.substr(0,(parseLine.size()));
                    parseLine="";
                }
                else
                {
                    /*Else, we simply substring from the start till the end_space and we modify our parseLine
                    to make it to the terms after that term till the end*/
                    term=parseLine.substr(0,end_space);
                    parseLine=parseLine.substr(end_space+1);
                }


                /*If the term isn't equal to "", then we can proceed ahead*/
                if(term != "")
                {
                    /*We set findX to the first time we find x*/
                    findX=(int)term.find('x');


                    float result=0;

                    /*We use the find function to see whether the term has a sin/cos/tan*/
                    if((int)term.find("sin") != -1 || (int)term.find("cos") != -1 || (int)term.find("tan") != -1)
                    {

                        /*trig is a variable that will record the position of the first letter of the trig term*/
                        int trig=0;
                        if((int)term.find("sin")!=-1)
                        {
                            /*If the term has sin, we set trig to the location of the first letter of sin
                            and then set our newNode's trig term as sin*/
                            trig=(int)term.find("sin");
                            newNode->setTrig("sin");
                        }
                        else if((int)term.find("cos")!=-1)
                        {
                            /*If the term has cos, we set trig to the location of the first letter of cos
                            and then set our newNode's trig term as cos*/
                            trig=(int)term.find("cos");
                            newNode->setTrig("cos");
                        }
                        else if((int)term.find("tan")!=-1)
                        {
                            /*If the term has tan, we set trig to the location of the first letter of tan
                            and then set our newNode's trig term as tan*/
                            trig=(int)term.find("tan");
                            newNode->setTrig("tan");
                        }

                        //we set numParse to 0 as a protective measure
                        numParse=0;

                        /*We have a for loop that goes from 0 till the first instance of finding the trig term*/
                        for(int i=0; i<trig; i++)
                        {
                            if(term.at(i) == '-')
                            {
                                //if we find a - anytime, we make posneg equal to -1. We have now accounted for the negative
                                posneg=-1;
                            }
                            if( isdigit(term.at(i)) && i==0 && numParse<1)
                            {
                                /*If the first instance of the loop gets a digit and it's the first time analyzing the
                                number (as indicated by numParse), we:
                                    - make a variable called temp that will store the coefficient
                                    - substring from the position we are at and the distance till the first trig term
                                    - convert that substring to an integer
                                    - store that coefficient and multiply it by our posneg modifidier
                                    - store the outer-coefficient result in the node
                                    - add to our numParse so that we don't accidentally come here again
                                        and analyze the coefficient again*/
                                float temp=0;
                                string toInt = term.substr( (i), (trig-(i)) );
                                /*We make a stringstream called parser that will convert string to integers*/
                                stringstream parser;
                                parser << toInt;
                                parser >> temp;
                                result = temp * posneg;
                                newNode->setOuter(result);
                                numParse++;
                            }
                            else if( isalpha(term.at(i+1)) && ispunct(term.at(i-1)) )
                            {
                                /*If we are in a place where the position ahead of us is a letter
                                and the position before us is a punctuation sign, then we know that
                                the coefficient is implied and we simply set the outer-coefficient as the posneg modifier*/
                                newNode->setOuter(posneg);
                            }
                            else if( isdigit(term.at(i+1)) && numParse < 1)
                            {
                                /*If the next position on the string is a digit and it's the first time analyzing the
                                number (as indicated by numParse), we:
                                    - make a variable called temp that will store the coefficient
                                    - substring from one plus the position we are at and the distance till the first trig term
                                    - convert that substring to an integer
                                    - store that coefficient and multiply it by our posneg modifidier
                                    - store the outer-coefficient result in the node
                                    - add to our numParse so that we don't accidentally come here again
                                        and analyze the coefficient again*/
                                float temp=0;
                                string s = term.substr( (i+1), (trig-(i)) );
                                /*We make a stringstream called parser that will convert string to integers*/
                                stringstream parser;
                                parser << s;
                                parser >> temp;
                                result = temp * posneg;
                                newNode->setOuter(result);
                                numParse++;
                            }
                        }


                        /*We have now gotten our outer coefficient. We set posneg to 1
                        to restore so that we can reuse it. Now, we can get our inner coefficient*/
                        posneg=1;
                        if(term.at(findX-1) == ' ')
                        {
                            /*if the position right before our x is a space, then we know the coefficient is implied
                            and set it to 1*/
                            newNode->setInner(1);
                        }
                        else if(term.at(findX-1) == '-')
                        {
                            /*if the position right before our x has a -, then we know a negative coefficient is implied
                            and set it to -1*/
                            newNode->setInner(-1);
                        }
                        else
                        {
                            /*Else, we go one back with our findX variable and make a variable
                            called ten that will store the powers of 10 as we climb upwards. We also reset
                            result to 0 so that we can correctly analyze our inner-coefficient*/
                            findX = findX-1;
                            int ten=0;
                            result=0;

                            while(term.at(findX) != ' ')
                            {
                                /*We make a stringstream called parser that will convert string to integers*/
                                stringstream parser;

                                /*If the position on the string is not a space, we:
                                    - make a variable called temp that will store the coefficient
                                    - get the string by using a substring of length 1 from the position we are at
                                    - convert that substring to an integer by using the pow() to account for the powers of ten
                                    - we add our ten variable so that we can take into account the powers of ten invovled and substract
                                        findX by one so that we can access the next location. If the position to the right has a negative,
                                        we make posneg -1
                                    - After the loop is over, we multiply the result by posneg and store the
                                        inner-coefficient result in the node*/
                                float temp = 0;
                                string toInt = term.substr(findX,1);
                                parser << toInt;
                                parser >> temp;
                                result = result + (temp * (float)pow(10,ten));
                                ten++;
                                findX=findX-1;
                                if(term.at(findX+1) == '-')
                                {
                                    posneg=-1;
                                }
                            }
                            result=result*posneg;
                            newNode->setInner(result);
                        }

                        /*here, since our trig terms have no exponents, we set the exponent as trig_exp so that we can place them at the end of the list
                        when we will sort them*/
                        newNode->setExp(trig_exp);
                    }
                    else if(findX != -1)
                    {
                        /*We reset the variables posneg, result, and numParse so that we can correctly
                        do the parsing*/
                        posneg=1;
                        result=0;
                        numParse = 0;
                        for(int i=0; i<findX; i++)
                        {
                            if(term.at(i) == '-')
                            {
                                //if we find a - anytime, we make posneg equal to -1. We have now accounted for the negative
                                posneg=-1;
                            }
                            if( isdigit(term.at(i)) && i==0 && numParse < 1 )
                            {
                                /*If the first instance of the loop gets a digit and it's the first time analyzing the
                                    number (as indicated by numParse), we:
                                        - make a variable called temp that will store the coefficient
                                        - substring from the position we are at and the distance till the first trig term
                                        - convert that substring to an integer
                                        - store that coefficient and multiply it by our posneg modifidier
                                        - store the outer-coefficient result in the node
                                        - add to our numParse so that we don't accidentally come here again
                                            and analyze the coefficient again*/
                                float temp=0;
                                string toInt = term.substr( (i), (findX-(i)) );
                                /*We make a stringstream called parser that will convert string to integers*/
                                stringstream parser;
                                parser << toInt;
                                parser >> temp;
                                result = temp * posneg;
                                newNode->setOuter(result);
                                numParse++;
                            }
                            else if( isalpha(term.at(i+1)) && ispunct(term.at(i-1)) )
                            {
                                /*If we are in a place where the position ahead of us is a letter
                                and the position before us is a punctuation sign, then we know that
                                the coefficient is implied and we simply set the outer-coefficient as the posneg modifier*/
                                newNode->setOuter(posneg);
                            }
                            else if( isdigit(term.at(i+1)) && numParse < 1 )
                            {
                                /*If the next position on the string is a digit and it's the first time analyzing the
                                    number (as indicated by numParse), we:
                                        - make a variable called temp that will store the coefficient
                                        - substring from one plus the position we are at and the distance till the first trig term
                                        - convert that substring to an integer
                                        - store that coefficient and multiply it by our posneg modifidier
                                        - store the outer-coefficient result in the node
                                        - add to our numParse so that we don't accidentally come here again
                                            and analyze the coefficient again*/
                                float temp=0;
                                string toInt = term.substr( (i+1), (findX-(i)) );
                                /*We make a stringstream called parser that will convert string to integers*/
                                stringstream parser;
                                parser << toInt;
                                parser >> temp;
                                result = temp * posneg;
                                newNode->setOuter(result);
                                numParse++;
                            }
                        }

                        /*We have now gotten our outer coefficient. We set posneg to 1 and result to 0
                        to restore so that we can reuse it. Now, we can get our inner coefficient.
                        We also add one to our findX so that we can start to find the exponent*/
                        posneg=1;
                        findX = findX+1;
                        result=0;
                        newNode->setExp(0);
                        string toInt="";
                        if((int)term.find('x')!= -1 && (int)term.find('^')==-1)
                        {
                            /*if no x is there and there is no ^, we have a constant and we set the exponent to 1*/
                            newNode->setExp(1);
                        }
                        else if(findX != (int)term.size() && term.at(findX) == '^')
                        {
                            /*Else, if the findX isn't equal to the size of the string and we do find a ^ character,
                            we know there is an exponent and we can parse for it. We add one so that we could get to
                            the first digit of the exponent*/
                            findX=findX+1;
                            if(term.at(findX)== '-')
                            {
                                /*If the first term has a - sign, we make posneg equal to -1
                                and then add one to findX so that we can actually get to the numbers in the
                                exponent*/
                                posneg=-1;
                                findX=findX+1;
                            }
                            while(findX != (int)term.size() && term.at(findX) != ' ')
                            {
                                /*Since we can have exponents in the middle and in the end,
                                we have a while loop that accounts for both conditions. While the string
                                at that location isn't equal to the size or isn't equal to a space, we continue
                                getting the first string of the exponent and adding to a string that will be
                                eventually converted to an integer.
                                    -We also add one to the findX so that we can move forward and access
                                        the rest of the exponents*/
                                toInt = toInt + term.at(findX);
                                findX=findX+1;
                            }

                            /*We make a stringstream called parser that will convert string to integers*/
                                stringstream parser;

                            /*At the ending, we put the toInt string through a stringstream and multiply
                            the result by our posneg modifier and place it in the Node's exponent*/
                            parser << toInt;
                            parser >> result;
                            result=result*posneg;
                            newNode->setExp(result);
                        }
                    }
                    else
                    {
                        /*We make a stringstream called parser that will convert string to integers*/
                        stringstream parser;

                        /*If we have arrived here, our term is a constant*/

                        if(term.at(0)=='-')
                        {
                            //if the first character is a -, we make posneg = -1 as the number is negative
                            posneg=-1;
                        }

                        /*we make result 0 so that we can correctly parse. In addition, we
                        redefine findX here to find the first space - regardless if it does - and add
                        one to it.
                            If it did, then we are at the first digit.
                            If it did not, we are at the 0th position which is again the first position*/
                        result=0;
                        findX=(int)term.find(' ');
                        findX++;
                        if(ispunct(term.at(findX)) && isdigit(term.at(findX+1)))
                        {
                            /*if the first term with findX is a punctuation and the next term is
                            a digit, we add one more to the findX to get around the edgecase of a negative
                            constant in the beginning*/
                            findX++;
                        }

                        /*We make a string called toInt that will store our constant*/
                        string toInt = "";
                        while(findX < (int)term.size() && (int)term.at(findX) != ' ')
                        {
                            /*While we are less than the line size and don't encounter a space,
                            we will continue adding so that we can build our constant string wise.
                            At the end, we add to findX so that we can access the next elements of the constant*/
                            toInt = toInt + term.at(findX);
                            findX++;
                        }

                        /*Finally, we parse the string through our stringstream and give it to result.
                        We multiply it by our posneg modifier and set our outer coefficient to result.
                        Finally, we set exponent to 0 since it's a constant*/
                        parser << toInt;
                        parser >> result;


                        result=result*posneg;
                        newNode->setOuter(result);
                        newNode->setExp(0);
                    }
                }

                /*Outside our parsing for each term, we add the finished parsed node to the linked list.
                We also subtract from our trig_exp so that we can eventually keep our trigs in order when we sort*/
                ListOfEq>>newNode;
                trig_exp=trig_exp-1;
                newNode = new Node;
            }

            /*After we've gone through the whole line, parsed, and added to our list, we:
                - sort the bubble list based on exponents
                - derive the list
                - we use an overloaded cout<< from the linked list class to output the linked list term by term
                - we finally use the output filestream to also output our derive.txt file*/
            ListOfEq.sort();
            ListOfEq.toDerive();
            cout<<ListOfEq;
            output<<ListOfEq;
            ListOfEq.toClean();
        }

        /*Here, we delete our dynamically allocated variables to ensure that we don't have any memory leaks*/
        delete initialHead;
        delete newNode;
    }

    /*After opening our files, we end this program by closing our files for the safety of our files*/
    input.close();
    output.close();
}

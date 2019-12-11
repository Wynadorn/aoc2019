#include <iostream>
#include <string>
#include <vector>
#include "aocUtil.h"
using namespace std;

void processVector(vector<int> input);
void processVector(vector<int> input, int noun, int verb);

// Main entry point
int main(void)
{
    string inputString = aocUtil::getChallangeInput(5);

    //inputString = "3,9,8,9,10,9,4,9,99,-1,8"; //euqal to
    //inputString = "3,9,7,9,10,9,4,9,99,-1,8"; //less than
    //inputString = "3,3,1108,-1,8,3,4,3,99"; //equal to
    //inputString = "3,3,1107,-1,8,3,4,3,99"; //less than

    vector<int> input = aocUtil::explodeInt(inputString, ',');

    //aocUtil::dumpVector(input);

    processVector(input);

    return 0;
}

void processVector(vector<int> input)
{
    int i = 0;
    while(i < input.size())
    {
        //registers
        int opcode = input.at(i)%100;
        int p1Mode = (input.at(i)/100)%10;
        int p2Mode = (input.at(i)/1000)%10;
        int p3Mode = (input.at(i)/10000)%10;
        int p1,p2,p3,i1 = 0;

        switch(opcode)
        {
            case 1:
                p1 = (p1Mode == 0) ? input.at(input.at(i+1)) : input.at(i+1);
                p2 = (p2Mode == 0) ? input.at(input.at(i+2)) : input.at(i+2);
                p3 = input.at(i+3);
                
                input.at(p3) = p1 + p2;
                i += 4;
                break;

            case 2:
                p1 = (p1Mode == 0) ? input.at(input.at(i+1)) : input.at(i+1);
                p2 = (p2Mode == 0) ? input.at(input.at(i+2)) : input.at(i+2);
                p3 = input.at(i+3);
                
                input.at(p3) = p1 * p2;
                i += 4;
                break;

            case 3:
                cout << "Please provide your input and press <Return>: ";
                cin >> i1;

                p1 = input.at(i+1);
                
                input.at(p1) = i1;
                i += 2;
                break;

            case 4:
                p1 = (p1Mode == 0) ? input.at(input.at(i+1)) : input.at(i+1);

                cout << p1 << endl;
                i += 2;
                break;

            case 5:
            case 6:
                p1 = (p1Mode == 0) ? input.at(input.at(i+1)) : input.at(i+1);
                p2 = (p2Mode == 0) ? input.at(input.at(i+2)) : input.at(i+2);

                if((opcode == 5 && p1 != 0) ||
                   (opcode == 6 && p1 == 0))
                {
                    i = p2;
                    break;
                }

                i += 3;
                break;

            case 7:
            case 8:
                p1 = (p1Mode == 0) ? input.at(input.at(i+1)) : input.at(i+1);
                p2 = (p2Mode == 0) ? input.at(input.at(i+2)) : input.at(i+2);
                p3 = input.at(i+3);

                if((opcode == 7 && p1 < p2) ||
                   (opcode == 8 && p1 == p2))
                {
                    input.at(p3) = 1;   
                }
                else
                {
                    input.at(p3) = 0;
                }
                
                i += 4;
                break;

            case 99:
                cout << "Program exited with state 99" << endl;
                return;

            default:
                cout << "Wtfbbq error at instruction " << i << endl;
                return;
        }

    }
    return;
}

void processVector(vector<int> input, int noun, int verb)
{
    input.at(1) = noun;
    input.at(2) = verb;

    return processVector(input);
}

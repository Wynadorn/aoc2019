#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "aocUtil.h"
#include "computer.h"
using namespace std;

// Main entry point
int main(void)
{
    string inputString = aocUtil::getChallangeInput(7);

    //inputString = "3,15,3,16,1002,16,10,16,1,16,15,15,4,15,99,0,0";
    //inputString = "3,26,1001,26,-4,26,3,27,1002,27,2,27,1,27,26,27,4,27,1001,28,-1,28,1005,28,6,99,0,0,5";

    vector<int> amplifierCode = aocUtil::explodeInt(inputString, ',');

    computer a1 = computer(amplifierCode);
    computer a2 = computer(amplifierCode);
    computer a3 = computer(amplifierCode);
    computer a4 = computer(amplifierCode);
    computer a5 = computer(amplifierCode);
    
    string o1, o2, o3, o4, o5;
   
    int highestOutput = 0;
    vector<string> x = vector<string>{"5", "6", "7", "8", "9"};
    while(next_permutation(x.begin(), x.end()))
    {   
		computer a1 = computer(amplifierCode);
		computer a2 = computer(amplifierCode);
		computer a3 = computer(amplifierCode);
		computer a4 = computer(amplifierCode);
		computer a5 = computer(amplifierCode);
        a1.addInput(x.at(0));
        a2.addInput(x.at(1));
        a3.addInput(x.at(2));
        a4.addInput(x.at(3));
        a5.addInput(x.at(4));
		o5 = "0\n";

        while(true)
        {
            a1.addInput(o5.substr(0, o5.find('\n')));
            o1 = a1.run();
            //cout << o1 << endl;
            
            a2.addInput(o1.substr(0, o1.find('\n')));
            o2 = a2.run();
            //cout << o2 << endl;
            
            a3.addInput(o2.substr(0, o2.find('\n')));
            o3 = a3.run();
            //cout << o3 << endl;

            a4.addInput(o3.substr(0, o3.find('\n')));
            o4 = a4.run();
            //cout << o4 << endl;

            a5.addInput(o4.substr(0, o4.find('\n')));
            o5 = a5.run();
            //cout << o5 << endl;
            
            if(!a5.isRunning())
            {
                break;
            }
        }
                
        if(stoi(o5) > highestOutput)
        {
            highestOutput = stoi(o5);
            cout << "New Record!! " << highestOutput << " with settings ";
            aocUtil::dumpVector(x);  
        }
    }

    return 0;
}

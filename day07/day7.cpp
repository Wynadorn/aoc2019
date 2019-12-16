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

    vector<int> amplifierCode = aocUtil::explodeInt(inputString, ',');

    computer a1 = computer(amplifierCode);
    computer a2 = computer(amplifierCode);
    computer a3 = computer(amplifierCode);
    computer a4 = computer(amplifierCode);
    computer a5 = computer(amplifierCode);
    
    string p1, p2, p3, p4, p5;
    string o1, o2, o3, o4, o5;
   
    int highestOutput = 0;

    vector<string> x = vector<string>{"0", "1", "2", "3", "4"};

    while(next_permutation(x.begin(), x.end()))
    {   
        p1 = x.at(0);
        p2 = x.at(1);
        p3 = x.at(2);
        p4 = x.at(3);
        p5 = x.at(4);


        a1.addInput(vector<string>{p1, "0"});
        o1 = a1.run();
        //cout << o1;
        
        a2.addInput(vector<string>{p2, o1.substr(0, o1.find('\n'))});
        o2 = a2.run();
        //cout << o2;
        
        a3.addInput(vector<string>{p3, o2.substr(0, o2.find('\n'))});
        o3 = a3.run();
        //cout << o3;

        a4.addInput(vector<string>{p4, o3.substr(0, o3.find('\n'))});
        o4 = a4.run();
        //cout << o4;

        a5.addInput(vector<string>{p5, o4.substr(0, o4.find('\n'))});
        o5 = a5.run();
        //cout << o5;
        
        if(stoi(o5) > highestOutput)
        {
            highestOutput = stoi(o5);
            cout << "New Record!! " << highestOutput << " with settings ";
            aocUtil::dumpVector(x);  
        }
    }

    return 0;
}

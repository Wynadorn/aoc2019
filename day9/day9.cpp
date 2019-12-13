#include <string>
#include <iostream>
#include "aocUtil.h"
#include "computer.h"
using namespace std;

int main()
{
    string input = aocUtil::getChallangeInput(9);
    //input = "109,1,204,-1,1001,100,1,100,1008,100,16,101,1006,101,0,99";    
    //input = "1102,34915192,34915192,7,4,7,99,0";
    //input = "104,1125899906842624,99";
    vector<long long> amplifierCode = aocUtil::explodeLonglong(input, ',');
  
    computer c1 = computer(amplifierCode);
    c1.addInput("1");
    string output = c1.run();

    cout << output;
    return 0;
}

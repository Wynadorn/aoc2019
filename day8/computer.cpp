#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <sstream>
#include "aocUtil.h"
#include "computer.h"
using namespace std;

vector<int> memory;
queue<string> inputQueue;
int ip = 0;
bool running = false;

computer::computer(vector<int> program)
{
    memory = program;
    ip = 0;
};

string computer::run()
{
    stringstream output;
    running = true;

    while(ip < memory.size())
    {
        //registers
        int opcode = memory.at(ip)%100;
        int p1Mode = (memory.at(ip)/100)%10;
        int p2Mode = (memory.at(ip)/1000)%10;
        int p3Mode = (memory.at(ip)/10000)%10;
        int p1,p2,p3,i1 = 0;

        switch(opcode)
        {
            case 1:
                p1 = (p1Mode == 0) ? memory.at(memory.at(ip+1)) : memory.at(ip+1);
                p2 = (p2Mode == 0) ? memory.at(memory.at(ip+2)) : memory.at(ip+2);
                p3 = memory.at(ip+3);
                
                memory.at(p3) = p1 + p2;
                ip += 4;
                break;

            case 2:
                p1 = (p1Mode == 0) ? memory.at(memory.at(ip+1)) : memory.at(ip+1);
                p2 = (p2Mode == 0) ? memory.at(memory.at(ip+2)) : memory.at(ip+2);
                p3 = memory.at(ip+3);
                
                memory.at(p3) = p1 * p2;
                ip += 4;
                break;

            case 3:
                if(!inputQueue.empty())
                {
                    i1 = stoi(inputQueue.front());
                    inputQueue.pop();
                }
                else
                {
                    return output.str();
                    //cout << "Please provide your input and press <Return>: ";
                    //cin >> i1;
                }
                
                p1 = memory.at(ip+1);
                
                memory.at(p1) = i1;
                ip += 2;
                break;

            case 4:
                p1 = (p1Mode == 0) ? memory.at(memory.at(ip+1)) : memory.at(ip+1);

                //cout << p1 << endl;
                
                output << p1 << endl;

                ip += 2;
                break;

            case 5:
            case 6:
                p1 = (p1Mode == 0) ? memory.at(memory.at(ip+1)) : memory.at(ip+1);
                p2 = (p2Mode == 0) ? memory.at(memory.at(ip+2)) : memory.at(ip+2);

                if((opcode == 5 && p1 != 0) ||
                   (opcode == 6 && p1 == 0))
                {
                    ip = p2;
                    break;
                }

                ip += 3;
                break;

            case 7:
            case 8:
                p1 = (p1Mode == 0) ? memory.at(memory.at(ip+1)) : memory.at(ip+1);
                p2 = (p2Mode == 0) ? memory.at(memory.at(ip+2)) : memory.at(ip+2);
                p3 = memory.at(ip+3);

                if((opcode == 7 && p1 < p2) ||
                   (opcode == 8 && p1 == p2))
                {
                    memory.at(p3) = 1;   
                }
                else
                {
                    memory.at(p3) = 0;
                }
                
                ip += 4;
                break;

            case 99:
                //cout << "Program exited with state 99" << endl;
                //output << "Program exited with state 99" << endl;
                ip = 0;
                running = false;
                return output.str();

            default:
                cout << "Wtfbbq error at instruction " << ip << endl;
                output << "Wtfbbq error at instruction " << ip << endl;
                running = false;
                return output.str();
        }
    }
    return output.str();
}

string computer::run(int noun, int verb)
{
    memory.at(1) = noun;
    memory.at(2) = verb;

    return run();
}

void computer::loadProgram(vector<int> program)
{
    memory = program;
}

void computer::addInput(string input)
{
    inputQueue.push(input);
}

void computer::addInput(vector<string> input)
{
    for(const auto& e: input)
    {
        inputQueue.push(e);
    }
}

queue<string> computer::getInputQueue()
{
    return inputQueue;
}

bool computer::isRunning()
{
    return running;
}

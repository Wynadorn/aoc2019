#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <sstream>
#include "aocUtil.h"
#include "computer.h"
using namespace std;

map<long long, long long> memory;
queue<string> inputQueue;
long long ip;
long long rel;
bool running;

computer::computer(vector<long long> program)
{
    loadProgram(program);
    ip = 0;
    rel = 0;
    running = false;
};

string computer::run()
{
    stringstream output;
    running = true;

    while(ip < memory.size())
    {
        //registers
        long long opcode = memory[ip]%100;
        long long p1Mode = (memory[ip]/100)%10;
        long long p2Mode = (memory[ip]/1000)%10;
        long long p3Mode = (memory[ip]/10000)%10;
        long long p1,p2,p3,i1 = 0;

        switch(opcode)
        {
            case 1:
            case 2:
            case 7:
            case 8:
                p1 = getParameter(p1Mode, ip+1);
                p2 = getParameter(p2Mode, ip+2);
                p3 = getWriteLocation(p3Mode, ip+3);

                switch(opcode)
                {
                    case 1:
                        memory[p3] = p1 + p2;
                        break;
                    case 2:
                        memory[p3] = p1 * p2;
                        break;
                    case 7:
                    case 8:
                        if((opcode == 7 && p1 < p2) ||
                           (opcode == 8 && p1 == p2))
                        {
                            memory[p3] = 1;   
                        }
                        else
                        {
                            memory[p3] = 0;
                        }
                        break;
                }

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
                
                p1 = getWriteLocation(p1Mode, ip+1);
                
                memory[p1] = i1;
                ip += 2;
                break;

            case 4:
                p1 = getParameter(p1Mode, ip+1);

                //cout << p1 << endl;
                output << p1 << endl;

                ip += 2;
                break;

            case 5:
            case 6:
                p1 = getParameter(p1Mode, ip+1);
                p2 = getParameter(p2Mode, ip+2);

                if((opcode == 5 && p1 != 0) ||
                   (opcode == 6 && p1 == 0))
                {
                    ip = p2;
                    break;
                }

                ip += 3;
                break;
            
            case 9:
                p1 = getParameter(p1Mode, ip+1);
                rel += p1;
                ip += 2;
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

string computer::run(long long noun, long long verb)
{
    memory[1] = noun;
    memory[2] = verb;

    return run();
}

void computer::loadProgram(vector<long long> program)
{
    for(int i = 0; i < program.size(); i++)
    {
        memory[i] = program.at(i);
    }
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

long long computer::getParameter(long long mode, long long pointer)
{
    switch(mode)
    {
        case 0: //position mode
            return memory[memory[pointer]];
        case 1: //immediate mode
            return memory[pointer];
        case 2: //relative mode
			//rel += ;
			return memory[rel+ memory[pointer]];

    }
    return -1;
}

long long computer::getWriteLocation(long long mode, long long pointer)
{
	switch (mode)
	{
		case 0:
			return memory[pointer];
		case 2:
			return rel + memory[pointer];
	}
	return -1;
}
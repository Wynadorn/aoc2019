#ifndef COMPUTER_H
#define COMPUTER_H

#include <string>
#include <vector>
#include <queue>

class computer
{
    public:
        computer(std::vector<int> program);

        std::string run();
        std::string run(int noun, int verb);
        void loadProgram(std::vector<int> program);
        void addInput(std::string input);
        void addInput(std::vector<std::string> input);
        std::queue<std::string> getInputQueue();
        bool isRunning();

    private:
        std::vector<int> memory;
        std::queue<std::string> inputQueue;
        bool running;
        int ip;
};

#endif

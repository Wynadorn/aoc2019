#ifndef COMPUTER_H
#define COMPUTER_H

#include <string>
#include <vector>
#include <map>
#include <queue>

class computer
{
    public:
        computer(std::vector<long long> program);

        std::string run();
        std::string run(long long noun, long long verb);
        void loadProgram(std::vector<long long> program);
        void addInput(std::string input);
        void addInput(std::vector<std::string> input);
        std::queue<std::string> getInputQueue();
        bool isRunning();

    private:
        long long getParameter(long long mode, long long pointer);
		long long getWriteLocation(long long mode, long long pointer);
        std::map<long long, long long> memory;
        std::queue<std::string> inputQueue;
        bool running;
        long long ip, rel;
};

#endif

#ifndef AOCUTIL_H
#define AOCUTIL_H

#include <string>
#include <vector>

class aocUtil
{
    public:
        static std::string getChallangeInput(int day);
        static size_t writeCallback(char* buf, size_t size, size_t nmemb, void* userdata);
        void dumpVector(std::vector<int> input);
        void dumpString(std::string input);
        std::vector<int> explode(std::string const & s, char delim);

    private:
        aocUtil();
};

#endif

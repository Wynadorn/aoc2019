#ifndef AOCUTIL_H
#define AOCUTIL_H

#include <string>
#include <vector>

class aocUtil
{
    public:
        static std::string getChallangeInput(int day);
        static size_t writeCallback(char* buf, size_t size, size_t nmemb, void* userdata);
        static void dumpVector(std::vector<std::string> input);
        static void dumpVector(std::vector<int> input);
        static void dumpString(std::string input);
        static std::vector<std::string> explode(std::string const & s, char delim);
        static std::vector<int> explodeInt(std::string const & s, char delim);

    private:
        aocUtil();
};

#endif

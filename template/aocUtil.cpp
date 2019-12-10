#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <curl/curl.h>
#include "aocUtil.h"
using namespace std;

static string callbackData;

string aocUtil::getChallangeInput(int day)
{
    string url = string("https://adventofcode.com/2019/day/") + to_string(day) + "/input";
    char const * cookie = "session=53616c7465645f5fcb20143fa368d39554798bbd269a387aaa98c7fdddca7f77c47ad0019e02f83e6f20c2623e688f7c;";
   
   CURL* curl;
   CURLcode result;
   curl = curl_easy_init();
   if(curl)
   {
       curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
       curl_easy_setopt(curl, CURLOPT_COOKIE, cookie);
       curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
       result = curl_easy_perform(curl);
   
       curl_easy_cleanup(curl);
   }
   return callbackData;
}

size_t aocUtil::writeCallback(char* buf, size_t size, size_t nmemb, void* userdata)
{
    for(int c = 0; c<size*nmemb; c++)
    {
        callbackData.push_back(buf[c]);
    }
    return size*nmemb;
}

void dumpVector(vector<int> input)
{
    for(vector<int>::const_iterator i = input.begin(); i != input.end(); ++i)
    {
        cout << *i << ',';
    }
    cout << endl;
    return;
}

void dumpString(string input)
{
   cout << input << endl;
}

std::vector<int> explode(std::string const & s, char delim)
{
    vector<int> result;
    istringstream iss(s);
    for(string token; getline(iss, token, delim); )
    {
        result.push_back(stoi(move(token)));

    }

    return result;
}

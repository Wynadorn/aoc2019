#include <iostream>
#include <curl/curl.h>
#include <string>
#include <sstream>
#include <cmath>
using namespace std;

//will hold the challange input contents
string callbackData;

char const *url = "https://adventofcode.com/2019/day/1/input";
char const *cookie = "session=53616c7465645f5fcb20143fa368d39554798bbd269a387aaa98c7fdddca7f77c47ad0019e02f83e6f20c2623e688f7c;";

// Set parameters for the curl callback function
// Buf is a pointer to the data that curl has for us
// Size*nmemb is the size of the buffer
size_t writeCallback(char* buf, size_t size, size_t nmemb, void* userdata)
{
    for(int c = 0; c<size*nmemb; c++)
    {
        callbackData.push_back(buf[c]);
    }
    // Tell curl how many bytes we've handled
    return size*nmemb;
}

// Gets the challange input through curl
string getChallangeInput()
{
    CURL* curl;
    CURLcode result;
    curl = curl_easy_init();
    if(curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url); 
        curl_easy_setopt(curl, CURLOPT_COOKIE, cookie);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
        result = curl_easy_perform(curl);

        curl_easy_cleanup(curl);
    }
    return callbackData;
}

int calcModuleFuel(int moduleRequirement)
{
    int total = 0;
    int requires = floor((float)(moduleRequirement/3))-2;
    if(requires > 0)
    {
        total += requires;
        total += calcModuleFuel(requires);
    }
    return total;
}

// Main entry point
int main(void)
{
    string input = getChallangeInput();

    istringstream inputStringStream(input);
    
    int total = 0;
    for(string line; getline(inputStringStream, line); )
    {   
        int i = stoi(line);
        total += calcModuleFuel(i);
    }

    cout << total << endl;
    return 0;
}

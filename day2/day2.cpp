#include <iostream>
#include <curl/curl.h>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>
#include <utility>
using namespace std;

// Method Header
size_t writeCallback(char* buf, size_t size, size_t nmemb, void* userdata);
string getChallangeInput();
vector<int> explode(string const & s, char delim);
void processVector(vector<int> input);

//will hold the challange input contents
string callbackData;

char const *url = "https://adventofcode.com/2019/day/2/input";
char const *cookie = "session=53616c7465645f5fcb20143fa368d39554798bbd269a387aaa98c7fdddca7f77c47ad0019e02f83e6f20c2623e688f7c;";

// Main entry point
int main(void)
{
    string input = getChallangeInput();

    istringstream inputStringStream(input);
    
    vector<int> inputVector = explode(input, ',');
    inputVector[1] = 12;
    inputVector[2] = 2;

    processVector(inputVector);

    return 0;
}

void dumpVector(vector<int> input)
{
    for(vector<int>::const_iterator i = input.begin(); i != input.end(); ++i)
    {
        cout << *i << ',';
    }
    cout << endl << endl;
}

void processVector(vector<int> input)
{
    cout << "initial optcodes";
    dumpVector(input);
    for(int i = 0; i<input.size(); i+=4)
    {
        if(input[i] == 1)
        {
            input[input[i+3]] = input[input[i+1]] + input[input[i+2]];
        }
        else if(input[i] == 2)
        {
            input[input[i+3]] = input[input[i+1]] * input[input[i+2]];
        }
        else if(input[i] == 99)
        {
            cout << "halt" << endl;
            cout << "pos 0 is: " << input[0] << endl;
            return;
        }
        else
        {
            cout << "wtf bbq error" << endl;
            return;
        }
        dumpVector(input);
    }
}

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

vector<int> explode(string const & s, char delim)
{
    vector<int> result;
    istringstream iss(s);
    for(string token; getline(iss, token, delim); )
    {
        result.push_back(stoi(move(token)));
    }

    return result;
}

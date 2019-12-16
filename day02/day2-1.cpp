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
int processVector(vector<int> input, int noun, int verb);

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
   
    int i = 0; 
    int answer = 0;
    while(answer != 19690720)
    {
        answer = processVector(inputVector, floor(i/100), i%100);
        i++;
        if(i/100>99)
        {
            break;
        }
    }

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

int processVector(vector<int> input, int noun, int verb)
{
    input.at(1) = noun;
    input.at(2) = verb;

    //cout << "initial optcodes" << endl;
    //dumpVector(input);
    for(int i = 0; i<input.size(); i+=4)
    {
        try
        {
            if(input.at(i) == 1)
            {
                input.at(input.at(i+3)) = input.at(input.at(i+1)) + input.at(input.at(i+2));
            }
            else if(input.at(i) == 2)
            {
                input.at(input.at(i+3)) = input.at(input.at(i+1)) * input.at(input.at(i+2));
            }
            else if(input.at(i) == 99)
            {
                cout << "halt  --  " << "Input: {" << noun << "," << verb << "}  --  Output: " << input[0] << endl;
                return input.at(0);
            }
            else
            {
                cout << "wtf bbq error" << endl;
                return -1;
            }
        }
        catch(out_of_range ex)
        {
            cout << "-1    --  " << "Input: {" << noun << "," << verb << "}  --  Output: " << input[0] << endl;
            return -1;
        }
    }
    return -1;
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

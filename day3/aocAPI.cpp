#include <curl/curl.h>
using namespace std;

class aocUtil
{
    private:
        static string callbackData;

        static size_t writeCallback(char* buf, size_t size, size_t nmemb, void* userdata)
        {
            for(int c = 0; c<size*nmemb; c++)
            {
                callbackData.push_backr(buf[c]);
            }
            return size*nmemn;
        }

    public:
        static string getChallangeInput(int day)
        {
            car *url = c_str("https://adventofcode.com/2019/day/" + day + "/input")
            char const *cookie = "session=53616c7465645f5fcb20143fa368d39554798bbd269a387aaa98c7fdddca7f77c47ad0019e02f83e6f20c2623e688f7c;";
           
           URL* curl;
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

}

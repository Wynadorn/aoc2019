#include <string>
#include <iostream>
#include <algorithm>
#include <climits>
#include <map>
#include "aocUtil.h"
using namespace std;

int main()
{
    string input = aocUtil::getChallangeInput(8);
    vector<string> imageLayers;
    map<int, int> finalImage;

    for(int i = 1; i <= (input.length()/(25*6)); i++)
    {
        imageLayers.push_back(input.substr((i-1) * (25 * 6),(25*6)));
    }
    
    reverse(imageLayers.begin(), imageLayers.end());

    //for each layer
    for(string imageLayer : imageLayers)
    {
        //for each pixel
        for (int i = 0; i < imageLayer.length(); i++)
        {
            int pixel = stoi(imageLayer.substr(i, 1));

            if (finalImage.count(i) == 0)
            {
                finalImage[i] = pixel;
            }
            else
            {
                switch (pixel)
                {
                    case 0: //back
                        finalImage[i] = pixel;
                        break;
                    case 1: //white
                        finalImage[i] = pixel;
                        break;
                    case 2: //transparant
                        break;
                }
            }
        }
        
    }

    map<int, int>::iterator it = finalImage.begin();
    
    for (int i = 0; i < finalImage.size(); i++)
    {
        cout << finalImage[i];
    }

    return 0;
}
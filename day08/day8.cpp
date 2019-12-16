#include <string>
#include <iostream>
#include <algorithm>
#include <climits>
#include "aocUtil.h"
using namespace std;

int main()
{
    string input = aocUtil::getChallangeInput(8);
    vector<string> imageLayers;

    for(int i = 1; i <= (input.length()/(25*6)); i++)
    {
        imageLayers.push_back(input.substr((i-1) * (25 * 6),(25*6)));
    }
    
    int i = 0; 
    int lowestLayer;
    int lowestLayerCount = INT_MAX;
    for(string imageLayer : imageLayers)
    {
        
        int counter = count(imageLayer.begin(), imageLayer.end(), '0');
        if(counter < lowestLayerCount)
        {
            
            lowestLayerCount = counter;
            lowestLayer = i;
        }
        cout << "Layer " << i << " has " << counter << " 0's " << endl;
        i++;
    }

    cout << lowestLayer << endl;
    cout << endl << endl << imageLayers.at(lowestLayer);

    return 0;
}
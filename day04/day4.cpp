#include <string>
#include <iostream>
#include <cstdio>
#include "aocUtil.h"

using namespace std;

bool isValid(int password);
bool containsAdjacent(int password);
bool neverDecreases(int password);

int main()
{
    string input = aocUtil::getChallangeInput(4);
    
    vector<int> range = aocUtil::explodeInt(input, '-');
    int validCount = 0;
    
    for(int i = range.at(0); i < range.at(1); i++)
    {
        if(isValid(i))
        {
            validCount++;
            cout << i << endl;
        }
    }

    cout << "There are " << validCount << " valid passwords." << endl;

    return 0;
}

bool isValid(int password)
{
    return neverDecreases(password) && containsAdjacent(password);
}

bool containsAdjacent(int password)
{
    int length = snprintf(nullptr, 0, "%d", password);
    int array[length];
    for (int i = length-1; i >= 0; i--)
    {
        array[i] = password % 10;
        password /= 10;
    }

    for(int i = 0; i<length; i++)
    {
        if(i == 0)
        {
            if(array[i] == array[i+1] &&
               array[i+1] != array[i+2])
            {
                return true;
            }
        }
        else if(i == length-1)
        {
            if(array[i] == array[i-1] &&
               array[i-1] != array[i-2])
            {
                return true;
            }
        }
        else if(i == 1)
        {
            if((array[i] == array[i+1] &&
                array[i] != array[i-1] &&
                array[i] != array[i+2]) ||
               (array[i] == array[i-1] &&
                array[i] != array[i+1]))
            {
                return true;    
            }
        }
        else if(i == length -2)
        {
            if((array[i] == array[i+1] &&
                array[i] != array[i-1]) ||
               (array[i] == array[i-1] &&
                array[i] != array[i+1] &&
                array[i] != array[i-2]))
            {
                return true;    
            }
        }
        else
        {
            if((array[i] == array[i+1] &&
                array[i] != array[i+2] &&
                array[i] != array[i-1]) ||
               (array[i] == array[i-1] &&
                array[i] != array[i-2] &&
                array[i] != array[i+1]))
            {
                return true;
            }

        }

    } 
    return false;
}

bool neverDecreases(int password)
{
    int previousNumber = password %10;
    password /= 10;

    for(int i = 5; i >= 0; i--)
    {
        int currentNumber = password %10;
        
        if(previousNumber < currentNumber)
        {
            return false;
        }

        previousNumber = currentNumber;
        password /= 10;
    }
    return true;

}

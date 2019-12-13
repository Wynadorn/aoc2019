#include <string>
#include <climits>
#include <iostream>
#include <vector>
#include <cmath>
#include "aocUtil.h"
using namespace std;

pair<int, int> calculateStep(pair<int, int> point, string step);
pair<int, int> calculateIntersect(pair<int, int> l1_OldPoint, pair<int, int> l2_OldPoint, pair<int, int> l1_NewPoint, pair<int, int> l2_NewPoint);
int calculateDistance(pair<int, int> intersect);

int main()
{
    //get the puzzle input
    string input = aocUtil::getChallangeInput(3);
    
    //find the linebreak
    int pos = input.find('\n');
    //split at the linebreak and store it in two seperate strings
    string line1s = input.substr(0,pos);
    string line2s = input.substr(pos+1, input.size()-pos-2);

    //line1s = "R75,D30,R83,U83,L12,D49,R71,U7,L72";
    //line2s = "U62,R66,U55,R34,D71,R55,D58,R83";
    //line1s = "R98,U47,R26,D63,R33,U87,L62,D20,R33,U53,R51";
    //line2s = "U98,R91,D20,R16,D67,R40,U7,R15,U6,R7";
    
    //line1s = "U10,L10,D20,R30,U15,L40,D10,L55";
    //line2s = "R25,U8,L30,D20,R20,U10,L10";
    
    //line1s = "R75,D30,R83,U83,L12,D49,R71,U7,L72";
    //line2s = "U62,R66,U55,R34,D71,R55,D58,R83";
    
    //explode the lines on ',' and store it in vectors
    vector<string> line1 = aocUtil::explode(line1s, ',');
    vector<string> line2 = aocUtil::explode(line2s, ',');
    
    //aocUtil::dumpVector(line1);
    
    //create points to store the lines current location
    pair<int, int> l1_OldPoint, l1_NewPoint;
    pair<int, int> l2_OldPoint, l2_NewPoint;
    pair<int, int> shortestIntersect;
    int shortestIntersectDistance = INT_MAX;

    int line1StepsTaken = 0;
    int line2StepsTaken = 0;
    int leastStepsTaken = INT_MAX;

    //for each step line 1 takes
    for(auto const& l1_Step: line1)
    {
        l1_NewPoint = calculateStep(l1_OldPoint, l1_Step);
        line1StepsTaken += stoi(l1_Step.substr(1));

        //for each step line 2 takes
        for(auto const& l2_Step: line2)
        {
            l2_NewPoint = calculateStep(l2_OldPoint, l2_Step);
            line2StepsTaken += stoi(l2_Step.substr(1));

            //cout << "Line 1\t{" << l1_OldPoint.first << "," << l1_OldPoint.second << "}";
            //cout << "\t" << l1_Step << "\t {" << l1_NewPoint.first << "," << l1_NewPoint.second << "}";
            //cout << "\t--\t Line 2\t{" << l2_OldPoint.first << "," << l2_OldPoint.second << "}";
            //cout << "\t" << l2_Step << "\t {" << l2_NewPoint.first << "," << l2_NewPoint.second << "}";
            //cout << endl;

            //cout << "Line 1 {" << l1_OldPoint.first << "," << l1_OldPoint.second << "}  " << l1_Step << "    --    Line 2 {" << l2_OldPoint.first << "," << l2_OldPoint.second << "}  " << l2_Step << endl;

            try
            {
                pair<int, int> intersect = calculateIntersect(l1_OldPoint, l2_OldPoint, l1_NewPoint, l2_NewPoint);

                //cout << "Intersect found at: {" << intersect.first << "," << intersect.second << "}" << endl;
                
                
                int line1StepsTakenFixed = 0;
                if(l1_OldPoint.first == intersect.first)
                {
                    line1StepsTakenFixed = line1StepsTaken  - stoi(l1_Step.substr(1)) + abs(l1_OldPoint.second - intersect.second);
                }
                else
                {
                    line1StepsTakenFixed = line1StepsTaken  - stoi(l1_Step.substr(1)) + abs(l1_OldPoint.first - intersect.first);
                }
            
               int line2StepsTakenFixed = 0;
                if(l2_OldPoint.first == intersect.first)
                {
                    line2StepsTakenFixed = line2StepsTaken  - stoi(l2_Step.substr(1)) + abs(l2_OldPoint.second - intersect.second);
                }
                else
                {
                    line2StepsTakenFixed = line2StepsTaken  - stoi(l2_Step.substr(1)) + abs(l2_OldPoint.first - intersect.first);
                }
 


                //cout << "Steps taken line1:" << line1StepsTakenFixed << " line2:" << line2StepsTakenFixed;
                //cout << "\t--\tTotal steps:" << line1StepsTakenFixed + line2StepsTakenFixed << endl;

                if((line1StepsTakenFixed + line2StepsTakenFixed) < leastStepsTaken)
                {
                    leastStepsTaken = line1StepsTakenFixed + line2StepsTakenFixed;
                    cout << "\tNEW RECCORD!!\t" << leastStepsTaken << endl;
                }

                int intersectDistance = calculateDistance(intersect);

                if(intersectDistance < shortestIntersectDistance)
                {
                    shortestIntersect = intersect;
                    shortestIntersectDistance = intersectDistance;
                    cout << "New shortest intersect of: " << shortestIntersectDistance << endl;
                }

            }
            catch(char const* ex)
            {}
            
            l2_OldPoint = l2_NewPoint;
        }
        l2_OldPoint = make_pair(0,0);
        line2StepsTaken = 0;   
        l1_OldPoint = l1_NewPoint;
    }

    cout << "The shortest point where the lines cross is {" << shortestIntersect.first << "," << shortestIntersect.second << "} and the distance is " << shortestIntersectDistance << "." << endl;
    cout << "The least steps to and intersect was " << leastStepsTaken << endl;
    return 0;
}

pair<int, int> calculateStep(pair<int, int> point, string step)
{
    switch(step.substr(0,1).at(0))
    {
        case 'U':
            point.second += stoi(step.substr(1));
            break;
        case 'D':
            point.second -= stoi(step.substr(1));
            break;
        case 'L':
            point.first -= stoi(step.substr(1));
            break;
        case 'R':
            point.first += stoi(step.substr(1));
            break;
    }
    return point;
}

pair<int, int> calculateIntersect(pair<int, int> l1_OldPoint, pair<int, int> l2_OldPoint,
                                  pair<int, int> l1_NewPoint, pair<int, int> l2_NewPoint)
{
    //If the line travels along the x axis
    if(l1_OldPoint.first != l1_NewPoint.first)
    {
        //If line 1 x falls between line 2 old x and new x
        if(l1_OldPoint.second >= min(l2_OldPoint.second, l2_NewPoint.second) &&
           l1_OldPoint.second <= max(l2_OldPoint.second, l2_NewPoint.second))
        {
            if(l2_OldPoint.first >= min(l1_OldPoint.first, l1_NewPoint.first) &&
               l2_OldPoint.first <= max(l1_OldPoint.first, l1_NewPoint.first))
            {
                if(l2_OldPoint.first != 0 || l1_OldPoint.second != 0)
                {
                    return make_pair(l2_OldPoint.first, l1_OldPoint.second);
                }
            }
        }

    }
    //If the line travels along the y axis
    else
    {

        //If line 1 x falls between line 2 old x and new x
        if(l1_OldPoint.first >= min(l2_OldPoint.first, l2_NewPoint.first) &&
           l1_OldPoint.first <= max(l2_OldPoint.first, l2_NewPoint.first))
        {
            if(l2_OldPoint.second >= min(l1_OldPoint.second, l1_NewPoint.second) &&
               l2_OldPoint.second <= max(l1_OldPoint.second, l1_NewPoint.second))
            {
                if(l1_OldPoint.first != 0 || l2_OldPoint.second != 0)
                {
                    return make_pair(l1_OldPoint.first, l2_OldPoint.second);
                }
            }
        }

    }
    throw "No Intersect";
}

int calculateDistance(pair<int, int> intersect)
{
    return abs(intersect.first) + abs(intersect.second);
}

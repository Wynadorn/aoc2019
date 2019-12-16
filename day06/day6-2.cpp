#include <string>
#include <sstream>
#include <iostream>
#include <map>
#include <list>
#include "aocUtil.h"
using namespace std;

class planet;
map<string, planet> universe;

class planet
{
    private:
    //planet *parentPointer = NULL;
	string parentString;
    list<string> childrenStrings;
    string planetId;

    public:
    planet(string id)
    {
        planetId = id;
    }

    planet()
    {}

    void setParent(string _parent)
    {
		parentString = _parent;
        universe[parentString].addChild(planetId);
    }

    string getParentString()
    {
        return parentString;
    }

    string getPlanetId()
    {
        return planetId;
    }


    void addChild(string childString)
    {
        childrenStrings.push_back(childString);
    }

    int countParents()
    {
        int counter = 0;

		planet parentPlanet = *this;

		while (true)
		{
			if (!parentPlanet.parentString.empty())
			{
				parentPlanet = universe[parentPlanet.parentString];
				counter++;
			}
			else
			{
				return counter;
			}
		}
    }

    void dumpParents()
    {
		planet parentPlanet = *this;

		while (true)
		{
			if (!parentPlanet.parentString.empty())
			{
                cout << parentPlanet.getPlanetId() << " - ";
				parentPlanet = universe[parentPlanet.parentString];
			}
			else
			{
				return;
			}
		}
    }

};


int main()
{
    string input = aocUtil::getChallangeInput(6);
   
    // for each entry on the list 
    istringstream inputStringStream(input);
    for(string line; getline(inputStringStream, line); )
    {
        string orbitingPlanetId = line.substr(4);
        string orbitingPlanetParentId = line.substr(0,3);

        planet orbitingPlanet, orbitingPlanetParent;

        // if the orbiting planet does not exist
        if(universe.count(orbitingPlanetId) == 0)
        {
            //create the orbiting planet
			orbitingPlanet = planet(orbitingPlanetId);
            universe[orbitingPlanetId] = orbitingPlanet;
        }

        //if the orbiting planet parent does not exist
        if(universe.count(orbitingPlanetParentId) == 0)
        {
			orbitingPlanetParent = planet(orbitingPlanetParentId);
            universe[orbitingPlanetParentId] = orbitingPlanetParent;
        }
        
        universe[orbitingPlanetId].setParent(orbitingPlanetParentId);
    }

    int totalCount = 0;

    map<string, planet>::iterator it = universe.begin();
    for(pair<string, planet> element : universe)
    {
		//planet das = *element.second.getParentPointer();
		//cout << das.getPlanetId();
        cout << "ID " << element.first << "\t";

        planet x = element.second;
        cout << "ID " << x.getPlanetId() << "\t";

        totalCount += x.countParents();
        cout << "Parents " << totalCount << endl;
    }

    cout << "--- Part Two ---" << endl;

    int myParents = universe["YOU"].countParents();
    int santaParents = universe["SAN"].countParents();
    
    cout << "My parents: " << myParents << endl;
    universe["YOU"].dumpParents();
    cout << "SantaParents: " << santaParents << endl;
    universe["SAN"].dumpParents();


    return 0;
};



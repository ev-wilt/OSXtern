/*
    This submission uses a map to pair each multiset of users with their respective group.
    A multiset was chosen so multiple people with the same name could be in the same group.
*/

#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <string>

int main () {

    std::map <std::string, std::multiset <std::string> > userGroupMap;
    std::map <std::string, std::multiset <std::string> >::iterator mapIter;
    std::multiset <std::string>::iterator multiSetIter;
    std::string input;
    size_t spacePosition;    

    // Get user and group from standard input.
    while (std::getline (std::cin, input)) {

        // Parse the input into user and group.
        spacePosition = input.find (' ', 0);
        std::string user = input.substr (0, spacePosition);
        std::string group = input.substr (spacePosition + 1);        

        // If the group key isn't in the map, make a new multiset containing the user that will act as the value.
        // Then pair the group and multiset of users and insert it into the map.
        if (userGroupMap.find (group) == userGroupMap.end ()) {
            std::multiset <std::string> userMultiSet;

            userMultiSet.insert (user);
            userGroupMap.insert (std::pair <std::string, std::multiset <std::string> > (group, userMultiSet));
        }

        // If the group already exists, add the user to the existing multiset paired with that group.
        else {
            userGroupMap.find (group)->second.insert (user);
        }
    }

    // Iterate through the map and print each key (group) along with their respective value (multiset of users).
    for (mapIter = userGroupMap.begin (); mapIter != userGroupMap.end (); ++mapIter) {
        std::cout << mapIter->first;
        for (multiSetIter = mapIter->second.begin (); multiSetIter != mapIter->second.end (); ++multiSetIter) {
            std::cout << ',' << *multiSetIter;                
        }
        std::cout << std::endl;                            
    }
    
    return 0;
}
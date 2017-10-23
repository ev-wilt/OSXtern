/*
    This submission uses a sorted vector to contain the current running processes.
    I chose a vector due to its ability to scale dynamically and I decided to sort
    it so I could do a binary search to check if a process is currently running.
*/

#include <algorithm>
#include <iostream>
#include <vector>

int main () {

    std::vector <unsigned short> runningProcesses;
    unsigned short input;    

    while (std::cin >> input) {

        // Check if input is already in vector using a binary search. If so, erase it based upon its value.
        if (std::binary_search (runningProcesses.begin (), runningProcesses.end (), input)) {
            runningProcesses.erase (std::remove (runningProcesses.begin (), runningProcesses.end (), input), runningProcesses.end ());
        }

        // Otherwise, push our input into the vector and sort it.
        else {
            runningProcesses.push_back (input);
            std::sort (runningProcesses.begin (), runningProcesses.end ());
        }
    }

    // Print the remaing process, if any. The prompt says we can assume only one process will be left running,
    // but this implementation allows us to print any processes left running.
    if (runningProcesses.size () != 0) {
        for (int i = 0; i < runningProcesses.size (); ++i) {
            std::cout << runningProcesses[i] << std::endl;            
        }
    }

    else {
        std::cout << '0' << std::endl;        
    }

    return 0;
}
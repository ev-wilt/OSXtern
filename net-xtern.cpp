/*
    This submission uses two stacks, one of which saves the history of the browser (back) while the other
    keeps track of any URLs that have been moved back from (forward).
*/

#include <exception>
#include <iostream>
#include <stack>
#include <string>

// clearStack is used to clear the forward stack if any input other than BACK or FORWARD is given.
void clearStack (std::stack <std::string> & stack) {
    while (!stack.empty ()) {
        stack.pop ();
    }
}

int main () {

    std::stack <std::string> back;
    std::stack <std::string> forward;
    std::string currentPage = "";
    std::string input;

    // Get the URL/path from standard input.
    while (std::cin >> input) {
        
        // If https:// is at the beginning of the input, assume this in an absolute URL and overwrite the 
        // current page.
        if (input.find ("https://") == 0) {
            clearStack (forward);
            if (currentPage != "") {
                back.push (currentPage);
            }
            currentPage = input;
        }

        // If the first character of input is /, assume this is an absolute path and append it to the current
        // page, erasing the current absolute path onward if necessary.
        else if (input[0] == '/') {
            clearStack (forward);            
            back.push (currentPage);            
            if (currentPage.find ('/', 8) != std::string::npos) {
                currentPage.erase (currentPage.find ('/', 8), std::string::npos);                
            }
            currentPage.append (input);
        }

        // If the input is BACK and the back stack isn't empty, push our current page onto the forward stack,
        // set our current page to the top element of the back stack, and pop the back stack.
        else if (input == "BACK") {
            try {                
                if (!back.empty ()) {
                    forward.push (currentPage);
                    currentPage = back.top ();            
                    back.pop ();    
                }

                // If the back stack is empty, throw an out of range exception.
                else {
                    throw std::out_of_range ("No previous history.");
                }
            }
            catch (std::exception & error) {
                std::cerr << error.what () << std::endl;
            }
        }

        // Repeat the same steps for BACK as forward, swapping any references between the two.
        else if (input == "FORWARD") {
            try {
                if (!forward.empty ()) {
                    back.push (currentPage);
                    currentPage = forward.top ();            
                    forward.pop ();
                }

                else {
                    throw std::out_of_range ("Cannot go forward.");                                    
                }
            }
            catch (std::exception & error) {
                std::cerr << error.what () << std::endl;
            }
        }

        // Assume any other input is a relative path and append it to our our current page.
        else {
            clearStack (forward);            
            back.push (currentPage);
            currentPage.append ("/");
            currentPage.append (input);
        }
        std::cout << currentPage << std::endl;
        
    }

    return 0;
}
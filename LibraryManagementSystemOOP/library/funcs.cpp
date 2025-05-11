#include <iostream>
using namespace std;

void wait_for_user_input() {
			// Wait for the user to press Enter
        cout << "Press Enter to continue...";
        cin.ignore();  // To clear the newline character left in the input buffer
        cin.get();     // Waits for the Enter key to be pressed
}
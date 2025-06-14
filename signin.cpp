#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <cmath>

using namespace std;

int main() {
    double counter = 0;
    string pass = "";
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    cout << "Welcome \n\n";
    cout << "Please enter your password below:\n";
    cin >> pass;

    // Move up two lines: one for input, one for the prompt
    cout << "\033[F"; // Move up to the password line
    cout << "\033[F"; // Move up to the prompt
    cout << "\rPlease enter your password below:\n"; // Reprint prompt

    cout << string(pass.length(), '*') << endl; // Replace input with stars


    const char* dots[] = {".", "..", "..."}; // different dots
    const int intervalMs = 500; // time between updates (in milliseconds)
    const int totalDurationMs = 5000; // total duration (5 seconds)
    const int steps = totalDurationMs / intervalMs;

    for (int i = 0; i < steps; ++i) {
        cout << "\rLoading" << dots[i % 3] << flush;
        this_thread::sleep_for(chrono::milliseconds(intervalMs));
    }
    bool pass_check = false;
    if (pass == "password")
    {
        cout << "\rPassword Correct.           \n\n" << endl;
        pass_check = true;

    } else {
        cout << "\rPassword Incorrect.         \n\n" << endl;
    }
    if (pass_check){
        for (int i = 0; i < steps; ++i) {
            cout << "\rLoading" << dots[i % 3] << flush;
            this_thread::sleep_for(chrono::milliseconds(intervalMs));
        }
        cout << "\rLoading Complete. Please Proceed.\n\n";
    }
    
    return 0;
}

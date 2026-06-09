#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <cmath>
#include <vector>
#include <windows.h>
//#include <SFML/Graphics.hpp>



using namespace std;

void setCursorVisible(bool visible) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = visible;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

const char* dots[] = {".  ", ".. ", "..."}; // different dots
const int intervalMs = 500; // time between updates (in milliseconds)
const int totalDurationMs = 5000; // total duration (5 seconds)
const int steps = totalDurationMs / intervalMs;

void dot_sequence(string text){
    setCursorVisible(false);
    for (int i = 0; i < steps; ++i) {
        cout << "\r" << text <<dots[i % 3] << flush;
        this_thread::sleep_for(chrono::milliseconds(intervalMs));
    }
    setCursorVisible(true);
}
void number_sequence(int max) {
    for (int i = 0; i <= max; i++){
        cout << i;
        cout << "\n";
        this_thread::sleep_for(chrono::milliseconds(10));
    }     
}
int main() {
    double counter = 0;
    string pass = "";
    cout << "\n\nWelcome \n\n";
    cout << "Please enter your password below:\n";
    getline (cin, pass);

    cout << "\033[F"; // Move up to the password line for replacing it

    cout << string(pass.length(), '*') << endl; // Replace input with stars
    dot_sequence("Verifying password entry");

    bool pass_check = false;
    cout << "\rVerification Complete          ";


    if (pass == "your password below")
    {
        cout << "\nPassword Correct.           \n\n" << endl;
        pass_check = true;
    } else {
        cout << "\nPassword Incorrect.         \n\n" << endl;
    }


    if (pass_check){
        dot_sequence("Loading Software");

        cout << "\rLoading Complete. Please Proceed.\n\n";
        number_sequence(100);
    }
    
    return 0;
}

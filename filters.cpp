#include <iostream>
using namespace std;
#include "Image_Class.h"

// Filters Function

void grayscaleFilter(Image& img) {
    // code block
}

void invertFilter(Image& img) {
    // code block
}

Image cropFilter(const Image& img, int x, int y, int w, int h) {
    Image result(w, h);
    // code block
    return result;
}



void displayMenu() {
    cout << "1. Load a new image\n";
    cout << "2. Grayscale\n";
    // ...
}




// main menu

int main() {
    Image currentImage;
    bool exit = false;

    while (!exit) {
        displayMenu();
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: /* load */ break;
            case 2: grayscaleFilter(currentImage); break;
            case 3: invertFilter(currentImage); break;
            // and so on 
        }
    }
    return 0;
}



// git add .
// git commit -m "your commit message"
// git push -u origin gehad

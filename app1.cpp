#include <iostream>
#include "Image_Class.h"
using namespace std;
int main() {
    string filename;
    cin >> filename; 
    Image image(filename);
    int newW,newH;
    cin >> newW >> newH;
    Image resized_image(newW,newH);
    float scaleW = (float)image.width / newW;
    float scaleH = (float)image.height / newH;
    for (int X = 0;X < newW;++X) {
        for (int Y = 0;Y < newH;++Y) {
            int orgX = (int)(X * scaleW);
            int orgY = (int)(Y * scaleH);
            if (orgX >= image.width) orgX = image.width -1;
            if (orgY >= image.height) orgY = image.height - 1;
            for (int k = 0;k < 3;++k) {
                resized_image(X,Y,k) = image(orgX,orgY,k);
            }
        }
    }
    resized_image.saveImage("filter8.jpg"); //filter8
}
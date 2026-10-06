#include "Image_Class.h"
using namespace std;
void filter16 (Image& image) {
    for(int i = 0;i < image.width;i++) {
        for (int j = 0;j < image.height;j++) {
            image(i,j,0) = 255;
            image(i,j,1) = 255 - image(i,j,1);
            image(i,j,2) = 255 - image(i,j,2);
        }
    }
}
int main() {
    string filename;
    cin >> filename; 
    Image image(filename);
    filter16(image);
    image.saveImage("filter16.jpg"); //filter16
}
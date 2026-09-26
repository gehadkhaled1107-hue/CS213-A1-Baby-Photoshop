#include "Image_Class.h"
using namespace std;
void filter2 (Image& image) {
    for (int i = 0;i < image.width;++i) {
        for (int j = 0;j < image.height;++j) {
            unsigned int avg = 0;
            for (int k = 0;k < 3;++k) {  
                avg += image(i,j,k);
            }
            avg = avg / 3;
            int value;
            if (avg >= 128) value = 255;
            else value = 0;
            for (int k = 0;k < 3;++k) {
                image(i,j,k) = value;
            }
        }
    }
}
int main() {
    string filename;
    cin >> filename; 
    Image image(filename);
    filter2(image);
    image.saveImage("filter2.jpg"); //filter2
}
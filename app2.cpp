#include "Image_Class.h"
using namespace std;
void filter1 (Image& image) {
    for (int i = 0;i < image.width;++i) {
        for (int j = 0;j < image.height;++j) {
            
            unsigned int avg = 0;
            for (int k = 0;k < 3;++k) {
                avg += image(i,j,k);
            }
            avg = avg / 3;
            for (int k = 0;k < 3;++k) {
                image(i,j,k) = avg;
            }
        }
    }
}
int main() {
    string filename;
    cin >> filename; 
    Image image(filename);
    filter1(image);
    image.saveImage("filter1.jpg"); //filter1
}
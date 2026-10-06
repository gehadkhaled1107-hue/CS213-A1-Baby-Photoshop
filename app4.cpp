#include "Image_Class.h"
using namespace std;
void filter12 (Image& image,Image& blurred_image) {
    for (int x = 0;x < image.width;x++) {
        for (int y = 0;y < image.height;y++) {
            for (int k = 0;k < 3;k++) {
                int sum = 0;
                int count = 0;
                for (int dx = -1;dx <= 1;dx++) {
                    for (int dy = -1;dy <= 1;dy++) {
                        int i = x + dx;
                        int j = y + dy;
                        if (i >= 0 && i < image.width && j >= 0 && j < image.height) {
                            sum += image(i,j,k);
                            count++;
                        }
                    }
                }
                blurred_image(x,y,k) = sum / count;
            }
        }
    }
}
int main() {
    string filename;
    cin >> filename; 
    Image image(filename);
    Image blurred_image(image.width,image.height);
    filter12(image,blurred_image);
    blurred_image.saveImage("filter12.jpg"); //filter12
}
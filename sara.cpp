#include <iostream>
#include "Image_Class.h" 
using namespace std;

int main(){
    string filename;
    cin >> filename;
    Image img(filename);
    for(int i = 0; i < img.width; i++){
        for(int j = 0; j < img.height; j++){
          img.setPixel(i,j,0,(255-img.getPixel(i,j,0)));
          img.setPixel(i,j,1,(255-img.getPixel(i,j,1)));
          img.setPixel(i,j,2,(255-img.getPixel(i,j,2)));
        }
    }
    img.saveImage("bsara.jpg");
    return 0;
}
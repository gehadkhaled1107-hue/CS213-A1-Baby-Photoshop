#include "Image_Class.h"
#include <iostream>

void makeframe (Image& img) {
    int s=20;
    for (int i=0 ; i<img.height ; ++i) {
        for (int j=0 ; j<img.width ; ++j) {
            if (i<20 || i>=img.height-20 || j<20 || j>=img.width-20) {
                for (int c=0 ; c<3 ; ++c) {
                    if (c==0) img.setPixel(j,i,c,128);
                    if (c==1) img.setPixel(j,i,c,127);
                    if (c==2) img.setPixel(j,i,c,127);
                }
            }
        }
    }
}

using namespace std;

int main()
{
   Image img;
   string name;
   cout << "Enter image name:" << endl;
   cin >> name;
   img.loadNewImage(name);
   makeframe(img);
   string newname;
   cout << "Enter image new name:" << endl;
   cin >> newname;
   img.saveImage(newname);
}


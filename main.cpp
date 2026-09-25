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
void rotation(Image& img , int degree) {
    if (degree==90) {
        Image newimg(img.height,img.width);
        for (int i=0 ; i<img.height ; ++i) {
            for (int j=0 ; j<img.width ; ++j) {
                for (int c=0 ; c<3 ; ++c) {
                    newimg.setPixel(img.height-1-i,j,c,img.getPixel(j,i,c));
                }
            }
        }
        img=newimg;
    }
    else if (degree==180) {
        Image newimg(img.width,img.height);
        for (int i=0 ; i<img.height ; ++i) {
            for (int j=0 ; j<img.width ; ++j) {
                for (int c=0 ; c<3 ; ++c) {
                    newimg.setPixel(img.width-1-j,img.height-1-i,c,img.getPixel(j,i,c));
                }
            }
        }
        img=newimg;
    }
    else if (degree==270) {
        Image newimg(img.height , img.width);
        for (int i=0 ; i<img.height ; ++i) {
            for (int j=0 ; j<img.width ; ++j) {
                for (int c=0 ; c<3 ; ++c) {
                    newimg.setPixel(i,img.width-1-j,c,img.getPixel(j,i,c));
                }
            }
        }
        img=newimg;
    }
}

using namespace std;

int main()
{
   int degree;
   Image img;
   string name;
   cout << "Enter image name:" << endl;
   cin >> name;
   cout << "Enter the degree:" << endl;
   cin >> degree;
   img.loadNewImage(name);
   string newname;
   cout << "Enter image new name" << endl;
   cin >> newname;
   rotation(img,degree);
   img.saveImage(newname);
}


#include "Image_Class.h"
#include <iostream>

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


void makeframe(Image& img) {
    for (int i=0 ; i<img.height ; ++i) {
        for (int j=0 ; j<img.width ; ++j) {
            for (int c=0 ; c<3 ; ++c) {
                if (i<15 || j<15 || i>=img.height-15 || j>=img.width-15 || (i<=41&&j<=41) || (i>=img.height-41&& j>=img.width-41))  {
                    if(c==0) img.setPixel(j,i,c,200);
                    if(c==1) img.setPixel(j,i,c,127);
                    if(c==2) img.setPixel(j,i,c,127);
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
    string newname;
    cout << "Enter image name:" << endl;
    cin >> name;
    cout << "Enter image new name:" << endl;
    cin >> newname;
    img.loadNewImage(name);
    makeframe(img);
    img.saveImage(newname);
}


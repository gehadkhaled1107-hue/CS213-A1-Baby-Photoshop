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


void makeframe(Image& img , int n) {
    if (n==1) {
        for (int i=0 ; i<img.height ; ++i) {
            for (int j=0 ; j<img.width ; ++j) {
                for (int c=0 ; c<3 ; ++c) {
                    if (i<15 || j<15 || i>=img.height-15 || j>=img.width-15 )  {
                       if(c==0) img.setPixel(j,i,c,img.width/(255*i));
                       if(c==1) img.setPixel(j,i,c,img.height/(255*j));
                       if(c==2) img.setPixel(j,i,c,255-(i+j));
                    }
                }

            }
       }
    }
    else {

    }
}

void edges(Image& img) {
    for (int i=0 ; i<img.height ; ++i) {
        for (int j=0 ; j<img.width ; ++j) {
            int a=(img.getPixel(j,i,0)+img.getPixel(j,i,1)+img.getPixel(j,i,2))/3;
            for (int c=0 ; c<3 ; ++c) {
                img.setPixel(j,i,c,a);
            }
        }
    }
    Image newimg=img;
    for (int i=1 ; i<img.height-1 ; ++i) {
        for (int j=1 ; j<img.width-1 ; ++j) {
            if (abs(newimg.getPixel(j,i,0)-newimg.getPixel(j-1,i,0))>=20 || abs(newimg.getPixel(j,i,0)-newimg.getPixel(j,i-1,0))>=20 ) {
                for (int c=0 ; c<3 ; ++c) {
                    img.setPixel(j,i,c,0);
                }
            }
            else {
                for (int c=0 ; c<3 ; ++c) {
                    img.setPixel(j,i,c,255);
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
    edges(img);
    img.saveImage(newname);
}


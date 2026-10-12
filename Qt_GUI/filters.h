#include "Image_Class.h"
#include <algorithm>
#include <vector>
using namespace std;

void grayscaleFilter(Image& img) {
    for (int column = 0; column < img.width; column++) {
        for (int row = 0; row < img.height; row++) {
            int channels_sum = 0;
            for (int channel = 0; channel < 3; channel++) {
                channels_sum += img(column, row, channel);
            }
            int turn_to_gray = channels_sum / 3;
            for (int channel = 0; channel < 3; channel++) {
                img(column, row, channel) = turn_to_gray;
            }
        }
    }
}

Image flipFilter(Image& img, string state) {
    Image flipped_img(img.width, img.height);
    for (int column = 0; column < img.width; column++) {
        for (int row = 0; row < img.height; row++) {
            if (state == "h") {
                int flip_col = img.width - 1 - column;
                for (int channel = 0; channel < 3; channel++) {
                    flipped_img(flip_col, row, channel) = img(column, row, channel);
                }
            } else if (state == "v") {
                int flip_row = img.height - 1 - row;
                for (int channel = 0; channel < 3; channel++) {
                    flipped_img(column, flip_row, channel) = img(column, row, channel);
                }
            }
        }
    }
    return flipped_img;
}

void rotation(Image& img, int degree) {
    if (degree == 1) {
        Image newimg(img.height, img.width);
        for (int i = 0; i < img.height; ++i)
            for (int j = 0; j < img.width; ++j)
                for (int c = 0; c < 3; ++c)
                    newimg.setPixel(img.height - 1 - i, j, c, img.getPixel(j, i, c));
        img = newimg;
    } else if (degree == 2) {
        Image newimg(img.width, img.height);
        for (int i = 0; i < img.height; ++i)
            for (int j = 0; j < img.width; ++j)
                for (int c = 0; c < 3; ++c)
                    newimg.setPixel(img.width - 1 - j, img.height - 1 - i, c, img.getPixel(j, i, c));
        img = newimg;
    } else if (degree == 3) {
        Image newimg(img.height, img.width);
        for (int i = 0; i < img.height; ++i)
            for (int j = 0; j < img.width; ++j)
                for (int c = 0; c < 3; ++c)
                    newimg.setPixel(i, img.width - 1 - j, c, img.getPixel(j, i, c));
        img = newimg;
    }
}

void den(Image& img) {
    for (int i = 0; i < img.height; ++i) {
        for (int j = 0; j < img.width; ++j) {
            if (i % 4 != 0) {
                for (int c = 0; c < 3; ++c) {
                    img.setPixel(j, i, c, img.getPixel(j, i, c) * 0.5);
                }
            }
        }
    }
}

void invertImage(Image& img) {
    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            img.setPixel(i, j, 0, (255 - img.getPixel(i, j, 0)));
            img.setPixel(i, j, 1, (255 - img.getPixel(i, j, 1)));
            img.setPixel(i, j, 2, (255 - img.getPixel(i, j, 2)));
        }
    }
}

void darkenImage(Image& img) {
    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            for (int k = 0; k < img.channels; k++) {
                int currentValue = img.getPixel(i, j, k);
                int newValue = currentValue * 0.5;
                newValue = max(0, newValue);
                img.setPixel(i, j, k, newValue);
            }
        }
    }
}

void lightenImage(Image& img) {
    for (int i = 0; i < img.width; i++) {
        for (int j = 0; j < img.height; j++) {
            for (int k = 0; k < img.channels; k++) {
                int currentValue = img.getPixel(i, j, k);
                int newValue = currentValue * 1.5;
                newValue = min(255, newValue);
                img.setPixel(i, j, k, newValue);
            }
        }
    }
}

void Black_and_White(Image& img) {
    for (int i = 0; i < img.width; ++i) {
        for (int j = 0; j < img.height; ++j) {
            unsigned int avg = 0;
            for (int k = 0; k < 3; ++k) avg += img(i, j, k);
            avg = avg / 3;
            int value = (avg >= 128) ? 255 : 0;
            for (int k = 0; k < 3; ++k) img(i, j, k) = value;
        }
    }
}

void Resizing_Images(Image& img, Image& resized_img, int newW, int newH) {
    float scaleW = (float)img.width / newW;
    float scaleH = (float)img.height / newH;
    for (int X = 0; X < newW; ++X) {
        for (int Y = 0; Y < newH; ++Y) {
            int orgX = (int)(X * scaleW);
            int orgY = (int)(Y * scaleH);
            if (orgX >= img.width) orgX = img.width - 1;
            if (orgY >= img.height) orgY = img.height - 1;
            for (int k = 0; k < 3; ++k) {
                resized_img(X, Y, k) = img(orgX, orgY, k);
            }
        }
    }
}

Image mergingPixels(Image& img1, Image& img2, float blend_factor){
    Image merged_image(img1.width , img1.height);
    for (int column = 0 ; column < img1.width ; column++ ){
        for (int row = 0 ; row < img1.height ; row++ ){
            for (int channel =0 ; channel<3 ; channel++){
                merged_image(column , row, channel) = (img1(column , row , channel )*blend_factor) + (img2(column , row , channel )*(1 - blend_factor));
            }
        }
    } 
    return merged_image;
}

Image mergeFilter(Image& img1, Image& img2, float blend_factor = 0.5){
    if ((img1.height == img2.height) && (img1.width == img2.width)){
        Image merged_image = mergingPixels(img1, img2, blend_factor);
        return merged_image;
    } else {
        int resize_width = min(img1.width, img2.width);
        int resize_height = min(img1.height, img2.height);
        
        Image resized_img1(resize_width , resize_height);
        Image resized_img2(resize_width , resize_height);
        
        Resizing_Images(img1, resized_img1 ,resize_width ,resize_height);
        Resizing_Images(img2, resized_img2 ,resize_width ,resize_height);
        Image merged_image = mergingPixels(resized_img1, resized_img2, blend_factor);
        return merged_image;
    }
}

void sunlightFilter(Image& img) {
    for (int column = 0 ; column < img.width ; column++ ){
        for (int row = 0 ; row < img.height ; row++ ){
            int red = img(column , row , 0 );
            int green = img(column , row , 1 );
            int blue = img(column , row , 2 );
            if (red + 30 <= 255){
                img(column , row , 0 ) += 30;
            } else {
                img(column , row , 0 ) = 255;
            }
            if (green + 30 <= 255){
                img(column , row , 1 ) += 30;
            } else {
                img(column , row , 1 ) = 255;
            }
            if (blue - 30 >= 0){
                img(column , row , 2 ) -= 30;
            } else {
                img(column , row , 2 ) = 0;
            }
        }
    }
}

void makeframe(Image& img , int n , int color) {
    if (n==1) {
        for (int i=0 ; i<img.height ; ++i) {
            for (int j=0 ; j<img.width ; ++j) {
                for (int c=0 ; c<3 ; ++c) {
                    if (i<15 || j<15 || i>=img.height-15 || j>=img.width-15 )  {
                       if (color==1) {
                          if(c==0) img.setPixel(j,i,c,190);
                          if(c==1) img.setPixel(j,i,c,150);
                          if(c==2) img.setPixel(j,i,c,110);
                       }
                       else if (color==2) {
                          if(c==0) img.setPixel(j,i,c,230);
                          if(c==1) img.setPixel(j,i,c,35);
                          if(c==2) img.setPixel(j,i,c,40);
                       }
                       else if (color==3) {
                          if(c==0) img.setPixel(j,i,c,25);
                          if(c==1) img.setPixel(j,i,c,95);
                          if(c==2) img.setPixel(j,i,c,210);
                       }
                       else if (color==4) {
                          if(c==0) img.setPixel(j,i,c,30);
                          if(c==1) img.setPixel(j,i,c,160);
                          if(c==2) img.setPixel(j,i,c,95);
                       }
                       else if (color==5) {
                          if(c==0) img.setPixel(j,i,c,0);
                          if(c==1) img.setPixel(j,i,c,0);
                          if(c==2) img.setPixel(j,i,c,0);
                       }
                    }
                }

            }
       }
    }
    else {
        for (int i=20 ; i<=img.height-21 ; ++i) {
            for (int j=20 ; j<40 ; ++j) {
                for (int c=0 ; c<3 ; ++c) {
                    if (color==1) {
                        if(c==0) img.setPixel(j,i,c,255);
                        if(c==1) img.setPixel(j,i,c,245);
                        if(c==2) img.setPixel(j,i,c,232);
                    }
                    else if (color==2) {
                        if(c==0) img.setPixel(j,i,c,250);
                        if(c==1) img.setPixel(j,i,c,135);
                        if(c==2) img.setPixel(j,i,c,140);
                    }
                    else if (color==3) {
                        if(c==0) img.setPixel(j,i,c,120);
                        if(c==1) img.setPixel(j,i,c,185);
                        if(c==2) img.setPixel(j,i,c,250);
                    }
                    else if (color==4) {
                        if(c==0) img.setPixel(j,i,c,115);
                        if(c==1) img.setPixel(j,i,c,220);
                        if(c==2) img.setPixel(j,i,c,168);
                    }
                }
            }
            for (int j=img.width-40 ; j<=img.width-21 ; ++j) {
                for (int c=0 ; c<3 ; ++c) {
                    if (color==1) {
                        if(c==0) img.setPixel(j,i,c,248);
                        if(c==1) img.setPixel(j,i,c,233);
                        if(c==2) img.setPixel(j,i,c,215);
                    }
                    else if (color==2) {
                        if(c==0) img.setPixel(j,i,c,255);
                        if(c==1) img.setPixel(j,i,c,170);
                        if(c==2) img.setPixel(j,i,c,175);
                    }
                    else if (color==3) {
                        if(c==0) img.setPixel(j,i,c,200);
                        if(c==1) img.setPixel(j,i,c,230);
                        if(c==2) img.setPixel(j,i,c,255);
                    }
                    else if (color==4) {
                        if(c==0) img.setPixel(j,i,c,160);
                        if(c==1) img.setPixel(j,i,c,238);
                        if(c==2) img.setPixel(j,i,c,200);
                    }
                }
            }
        }
        for (int j=20 ; j<img.width-21 ; ++j) {
            for (int i=20 ; i<40 ; ++i) {
                for (int c=0 ; c<3 ; ++c) {
                    if (color==1) {
                        if(c==0) img.setPixel(j,i,c,240);
                        if(c==1) img.setPixel(j,i,c,220);
                        if(c==2) img.setPixel(j,i,c,195);
                    }
                    else if (color==2) {
                        if(c==0) img.setPixel(j,i,c,255);
                        if(c==1) img.setPixel(j,i,c,200);
                        if(c==2) img.setPixel(j,i,c,203);
                    }
                    else if (color==3) {
                        if(c==0) img.setPixel(j,i,c,230);
                        if(c==1) img.setPixel(j,i,c,244);
                        if(c==2) img.setPixel(j,i,c,255);
                    }
                    else if (color==4) {
                        if(c==0) img.setPixel(j,i,c,198);
                        if(c==1) img.setPixel(j,i,c,248);
                        if(c==2) img.setPixel(j,i,c,222);
                    }
                }
            }
            for (int i=img.height-40 ; i<=img.height-21 ; ++i) {
                for (int c=0 ; c<3 ; ++c) {
                    if (color==1) {
                        if(c==0) img.setPixel(j,i,c,230);
                        if(c==1) img.setPixel(j,i,c,205);
                        if(c==2) img.setPixel(j,i,c,170);
                    }
                    else if (color==2) {
                        if(c==0) img.setPixel(j,i,c,255);
                        if(c==1) img.setPixel(j,i,c,225);
                        if(c==2) img.setPixel(j,i,c,227);
                    }
                    else if (color==3) {
                        if(c==0) img.setPixel(j,i,c,165);
                        if(c==1) img.setPixel(j,i,c,212);
                        if(c==2) img.setPixel(j,i,c,255);
                    }
                    else if (color==4) {
                        if(c==0) img.setPixel(j,i,c,228);
                        if(c==1) img.setPixel(j,i,c,253);
                        if(c==2) img.setPixel(j,i,c,240);
                    }
                }
            }
        }
        for (int i=10 ; i<img.height-11 ; ++i) {
            for (int j=10 ; j<21 ; ++j) {
                for (int c=0 ; c<3 ; ++c) {
                    if (color==1) {
                        if(c==0) img.setPixel(j,i,c,215);
                        if(c==1) img.setPixel(j,i,c,180);
                        if(c==2) img.setPixel(j,i,c,140);
                    }
                    else if (color==2) {
                        if(c==0) img.setPixel(j,i,c,245);
                        if(c==1) img.setPixel(j,i,c,90);
                        if(c==2) img.setPixel(j,i,c,95);
                    }
                    else if (color==3) {
                        if(c==0) img.setPixel(j,i,c,70);
                        if(c==1) img.setPixel(j,i,c,150);
                        if(c==2) img.setPixel(j,i,c,240);
                    }
                    else if (color==4) {
                        if(c==0) img.setPixel(j,i,c,70);
                        if(c==1) img.setPixel(j,i,c,195);
                        if(c==2) img.setPixel(j,i,c,130);
                    }
                }
            }
            for (int j=img.width-21 ; j<=img.width-11 ; ++j) {
                for (int c=0 ; c<3 ; ++c) {
                    if (color==1) {
                        if(c==0) img.setPixel(j,i,c,215);
                        if(c==1) img.setPixel(j,i,c,180);
                        if(c==2) img.setPixel(j,i,c,140);
                    }
                    else if (color==2) {
                        if(c==0) img.setPixel(j,i,c,245);
                        if(c==1) img.setPixel(j,i,c,90);
                        if(c==2) img.setPixel(j,i,c,95);
                    }
                    else if (color==3) {
                        if(c==0) img.setPixel(j,i,c,70);
                        if(c==1) img.setPixel(j,i,c,150);
                        if(c==2) img.setPixel(j,i,c,240);
                    }
                    else if (color==4) {
                        if(c==0) img.setPixel(j,i,c,70);
                        if(c==1) img.setPixel(j,i,c,195);
                        if(c==2) img.setPixel(j,i,c,130);
                    }
                }
            }
        }
        for (int j=10 ; j<=img.width-11 ; ++j) {
            for (int i=10 ; i<21 ; ++i) {
                for (int c=0 ; c<3 ; ++c) {
                    if (color==1) {
                        if(c==0) img.setPixel(j,i,c,215);
                        if(c==1) img.setPixel(j,i,c,180);
                        if(c==2) img.setPixel(j,i,c,140);
                    }
                    else if (color==2) {
                        if(c==0) img.setPixel(j,i,c,245);
                        if(c==1) img.setPixel(j,i,c,90);
                        if(c==2) img.setPixel(j,i,c,95);
                    }
                    else if (color==3) {
                        if(c==0) img.setPixel(j,i,c,70);
                        if(c==1) img.setPixel(j,i,c,150);
                        if(c==2) img.setPixel(j,i,c,240);
                    }
                    else if (color==4) {
                        if(c==0) img.setPixel(j,i,c,70);
                        if(c==1) img.setPixel(j,i,c,195);
                        if(c==2) img.setPixel(j,i,c,130);
                    }
                }
            }
            for (int i=img.height-21 ; i<=img.height-11 ; ++i) {
                for (int c=0 ; c<3 ; ++c) {
                    if (color==1) {
                        if(c==0) img.setPixel(j,i,c,215);
                        if(c==1) img.setPixel(j,i,c,180);
                        if(c==2) img.setPixel(j,i,c,140);
                    }
                    else if (color==2) {
                        if(c==0) img.setPixel(j,i,c,245);
                        if(c==1) img.setPixel(j,i,c,90);
                        if(c==2) img.setPixel(j,i,c,95);
                    }
                    else if (color==3) {
                        if(c==0) img.setPixel(j,i,c,70);
                        if(c==1) img.setPixel(j,i,c,150);
                        if(c==2) img.setPixel(j,i,c,240);
                    }
                    else if (color==4) {
                        if(c==0) img.setPixel(j,i,c,70);
                        if(c==1) img.setPixel(j,i,c,195);
                        if(c==2) img.setPixel(j,i,c,130);
                    }
                }
            }
        }
        for (int i=0 ; i<img.height ; ++i) {
            for (int j=0 ; j<10 ; ++j){
                for (int c=0 ; c<3 ; ++c) {
                    if (color==1) {
                        if(c==0) img.setPixel(j,i,c,190);
                        if(c==1) img.setPixel(j,i,c,150);
                        if(c==2) img.setPixel(j,i,c,110);
                    }
                    else if (color==2) {
                        if(c==0) img.setPixel(j,i,c,230);
                        if(c==1) img.setPixel(j,i,c,35);
                        if(c==2) img.setPixel(j,i,c,40);
                    }
                    else if (color==3) {
                        if(c==0) img.setPixel(j,i,c,25);
                        if(c==1) img.setPixel(j,i,c,95);
                        if(c==2) img.setPixel(j,i,c,210);
                    }
                    else if (color==4) {
                        if(c==0) img.setPixel(j,i,c,30);
                        if(c==1) img.setPixel(j,i,c,160);
                        if(c==2) img.setPixel(j,i,c,95);
                    }
                }
            }
            for (int j=img.width-10 ; j<img.width ; ++j) {
                for (int c=0 ; c<3 ; ++c) {
                    if (color==1) {
                        if(c==0) img.setPixel(j,i,c,190);
                        if(c==1) img.setPixel(j,i,c,150);
                        if(c==2) img.setPixel(j,i,c,110);
                    }
                    else if (color==2) {
                        if(c==0) img.setPixel(j,i,c,230);
                        if(c==1) img.setPixel(j,i,c,35);
                        if(c==2) img.setPixel(j,i,c,40);
                    }
                    else if (color==3) {
                        if(c==0) img.setPixel(j,i,c,25);
                        if(c==1) img.setPixel(j,i,c,95);
                        if(c==2) img.setPixel(j,i,c,210);
                    }
                    else if (color==4) {
                        if(c==0) img.setPixel(j,i,c,30);
                        if(c==1) img.setPixel(j,i,c,160);
                        if(c==2) img.setPixel(j,i,c,95);
                    }
                }
            }
        }
        for (int j=0 ; j<img.width ; ++j) {
            for (int i=0 ; i<10 ; ++i) {
                for (int c=0 ; c<3 ; ++c) {
                    if (color==1) {
                        if(c==0) img.setPixel(j,i,c,190);
                        if(c==1) img.setPixel(j,i,c,150);
                        if(c==2) img.setPixel(j,i,c,110);
                    }
                    else if (color==2) {
                        if(c==0) img.setPixel(j,i,c,230);
                        if(c==1) img.setPixel(j,i,c,35);
                        if(c==2) img.setPixel(j,i,c,40);
                    }
                    else if (color==3) {
                        if(c==0) img.setPixel(j,i,c,25);
                        if(c==1) img.setPixel(j,i,c,95);
                        if(c==2) img.setPixel(j,i,c,210);
                    }
                    else if (color==4) {
                        if(c==0) img.setPixel(j,i,c,30);
                        if(c==1) img.setPixel(j,i,c,160);
                        if(c==2) img.setPixel(j,i,c,95);
                    }
                }
            }
            for (int i=img.height-10 ; i<img.height ; ++i) {
                for (int c=0 ; c<3 ; ++c) {
                    if (color==1) {
                        if(c==0) img.setPixel(j,i,c,190);
                        if(c==1) img.setPixel(j,i,c,150);
                        if(c==2) img.setPixel(j,i,c,110);
                    }
                    else if (color==2) {
                        if(c==0) img.setPixel(j,i,c,230);
                        if(c==1) img.setPixel(j,i,c,35);
                        if(c==2) img.setPixel(j,i,c,40);
                    }
                    else if (color==3) {
                        if(c==0) img.setPixel(j,i,c,25);
                        if(c==1) img.setPixel(j,i,c,95);
                        if(c==2) img.setPixel(j,i,c,210);
                    }
                    else if (color==4) {
                        if(c==0) img.setPixel(j,i,c,30);
                        if(c==1) img.setPixel(j,i,c,160);
                        if(c==2) img.setPixel(j,i,c,95);
                    }
                }
            }
        }
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
            if (abs(newimg.getPixel(j,i,0)-newimg.getPixel(j-1,i,0))>=20 && abs(newimg.getPixel(j,i,0)-newimg.getPixel(j,i-1,0))>=20 ) {
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


bool cropImage(Image& image, int x, int y, int W, int H) {
    if (x < 0 || y < 0 || W <= 0 || H <= 0 || (x + W) > image.width || (y + H) > image.height) {
        return false;
    }

    Image croppedImage(W, H);
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            croppedImage.setPixel(j, i, 0, image.getPixel(x + j, y + i, 0));
            croppedImage.setPixel(j, i, 1, image.getPixel(x + j, y + i, 1));
            croppedImage.setPixel(j, i, 2, image.getPixel(x + j, y + i, 2));
        }
    }

    image = croppedImage;
    return true;
}

void PurpleImage(Image& image) {
    for (int i = 0; i < image.height; ++i) {
        for (int j = 0; j < image.width; ++j) {
            int red = image.getPixel(j, i, 0);
            int green= image.getPixel(j, i, 1);
            int blue  = image.getPixel(j, i, 2);

            red = min(255, max(0, red + 40));
            green = min(255, max(0, green - 30));
            blue = min(255, max(0, blue + 60));

            image.setPixel(j, i, 0, red);
            image.setPixel(j, i, 1, green);
            image.setPixel(j, i, 2, blue);
        }
    }
}

void oilImage(Image& img) {
    Image img2=img;
    for (int i=0 ; i<img.height ; ++i) {
        for (int j=0 ; j<img.width ; ++j) {
            int R,B,G;
            vector <int> v(100,0);
            vector <int> v1(100,0),v2(100,0),v3(100,0);
            for (int r=-1 ; r<=1 ; ++r) {
                for (int c=-1 ; c<=1 ; ++c) {
                    int ni=i+r;
                    int nj=j+c;
                    if (ni>=0 && ni<img.height && nj>=0 && nj<img.width) {
                        R=img2.getPixel(nj,ni,0);
                        G=img2.getPixel(nj,ni,1);
                        B=img2.getPixel(nj,ni,2);
                        int average=(R+G+B)/3;
                        int l=(average*100)/256;
                        ++v[l];
                        v1[l]+=R;
                        v2[l]+=G;
                        v3[l]+=B;
                    }
                }
            }
            int maxi=0;
            int level=0;
            for (int k=0 ; k<100 ; ++k) {
                if (v[k]>maxi) {
                    maxi=v[k];
                    level=k;
                }
            }
            int RED=v1[level]/v[level];
            int GREEN=v2[level]/v[level];
            int BLUE=v3[level]/v[level];
            img.setPixel(j,i,0,RED);
            img.setPixel(j,i,1,GREEN);
            img.setPixel(j,i,2,BLUE);

        }
    }
}

void Blur_Images(Image& img,Image& Blurred_Image) {
    for (int x = 0;x < img.width;x++) {
        for (int y = 0;y < img.height;y++) {
            for (int k = 0;k < 3;k++) {
                int sum = 0;
                int count = 0;
                for (int dx = -1;dx <= 1;dx++) {
                    for (int dy = -1;dy <= 1;dy++) {
                        int i = x + dx;
                        int j = y + dy;
                        if (i >= 0 && i < img.width && j >= 0 && j < img.height) {
                            sum += img(i,j,k);
                            count++;
                        }
                    }
                }
                Blurred_Image(x,y,k) = sum / count;
            }
        }
    }
}

void Infrared_Images(Image& img) {
    for(int i = 0;i < img.width;i++) {
        for (int j = 0;j < img.height;j++) {
            img(i,j,0) = 255;
            img(i,j,1) = 255 - img(i,j,1);
            img(i,j,2) = 255 - img(i,j,2);
        }
    }
}

void Skewed_Images(Image& img,Image& skewed_image,int org_width,int org_height,int new_width,double skew_factor) {
    for (int i = 0;i < new_width;++i) {
        for (int j = 0;j < org_height;++j) {
            for (int k = 0;k < 3;++k) {
                skewed_image(i,j,k) = 0;
            }
        }
    }
    for (int x = 0;x < org_width;++x) {
        for (int y = 0;y < org_height;++y) {
            int offset = (org_height - 1 - y) * skew_factor;
            int new_x = x + offset; 
            if (new_x >= 0 && new_x < new_width) {
                for (int k = 0;k < 3;++k) {
                    skewed_image(new_x,y,k) = img(x,y,k);
                }
            }
        }
    }
}


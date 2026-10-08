/*
    Gehad Khaled - 20250163 - S11
        - Filters 
        [1]Grayscale Conversion
        [5]Flip Image
        [9]Merge Images
        [13]Sunlight 

    Shahd Mohamed- 20250326 - S11
        - Filters 
        [4]Adding a Frame to the Picture
        [6]Rotate Image
        [10]Detect Image Edges
        [14]TV images

    Sara Yasser - 20250840 - S11
        - Filters 
        [3]Invert Image
        [7]Darken and Lighten Image
        [11]Purple Image
        [15]Crop Image 
        

    Sara Mostafa - 20251186- S11
        - Filters 
        [2]Black and White
        [8]Resizing Images
        [12]Blur Images
        [16]Infrared Image
*/

#include "Image_Class.h"
#include <algorithm>
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

void cropImage(Image& image) {
    int x, y, W, H;
    cout << "Enter x, y, W, H: ";
    cin >> x >> y >> W >> H;

    if (x < 0 || y < 0 || W <= 0 || H <= 0 || (x + W) > image.width || (y + H) > image.height) {
        cout << "Invalid crop dimensions!" << endl;
        return;
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

void applyPurpleImage(Image& current_Image) {
       purpleImage(current_Image);
        cout << "\nPurple filter applied!\n";
}

void applyCroppedImage(Image& current_Image) {
    cropImage(current_Image);
    cout << "\nCrop filter applied !\n";
}

void applymakeframe(Image& current_image) {
    int n;
    cout << "[1] Simple frame" << endl;
    cout << "[2] Fancy frame" << endl;
    cout << "Enter your choice: " << endl;
    cin >> n;
    int color;
    cout << "[1] Beige" << endl;
    cout << "[2] Red" << endl;
    cout << "[3] blue" << endl;
    cout << "[4] Green" << endl;
    cout << "Enter your choice: " << endl;
    cin >> color;
    if (n<1 && n>2 && color<1 && color>4) {
        cout << "Invalid choice" << endl;
        return;
    }
    makeframe(current_image,n,color);
    cout << "\nFrame filter applied\n";
}

void applyedges(Image& current_image) {
    edges(current_image);
    cout << "\nEdges filter applied\n";
}

void applyGrayscaleFilter(Image& current_image) {
    grayscaleFilter(current_image);
    cout << "\nGrayscale filter applied\n";
}

void applyFlipFilter(Image& currentImage) {
    int direction;
    cout << "Select Flipping Direction\n";
    cout << "[1] Vertical\n";
    cout << "[2] Horizontal\nEnter Your Choice : ";
    cin >> direction;

    if (direction == 1) {
        currentImage = flipFilter(currentImage, "v");
        cout << "\nFlip filter applied vertically\n";
    } else if (direction == 2) {
        currentImage = flipFilter(currentImage, "h");
        cout << "\nFlip filter applied horizontally\n";
    } else {
        cout << "Invalid choice\n";
    }
}

void applyRotation(Image& currentImage) {
    int degree;
    cout << "[1] 90" << endl;
    cout << "[2] 180" << endl;
    cout << "[3] 270" << endl;
    cout << "Enter a degree : ";
    cin >> degree;
    if (degree != 1 && degree != 2 && degree != 3) {
        cout << "Invalid degree\n";
        return;
    }
    rotation(currentImage, degree);
    cout << "\nRotation filter applied\n";
}

void applyDen(Image& currentImage) {
    den(currentImage);
    cout << "\nTelevision filter applied\n";
}

void applyInvertImage(Image& currentImage) {
    invertImage(currentImage);
    cout << "\nInvert filter applied\n";
}

void applyDarkLight(Image& currentImage) {
    cout << "[1] Darken (50%)\n";
    cout << "[2] Lighten (50%)\n";
    cout << "Choose option: ";
    int choice;
    cin >> choice;
    if (choice == 1) {
        darkenImage(currentImage);
        cout << "\nImage darkened\n";
    } else if (choice == 2) {
        lightenImage(currentImage);
        cout << "\nImage lightened\n";
    } else {
        cout << "Invalid choice!\n";
    }
}

void applyBlackAndWhite(Image& currentImage) {
    Black_and_White(currentImage);
    cout << "\nBlack & White filter applied\n";
}

void applyResizingImages(Image& currentImage) {
    int newW, newH;
    cout << "Enter new width and height: ";
    cin >> newW >> newH;
    Image resized(newW, newH);
    Resizing_Images(currentImage, resized, newW, newH);
    currentImage = resized;
    cout << "\nImage resized\n";
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

void applyBlurImages(Image& currentImage) {
    Image Blurred_Image(currentImage.width,currentImage.height);
    Blur_Images(currentImage,Blurred_Image);
    cout << "\nBlur filter applied\n";
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

void applyInfraredImages(Image& currentImage) {
    Infrared_Images(currentImage);
    cout << "\nInfrared filter applied\n";
}

void applyMergeFilter(Image& currentImage){
    string second_file;
    Image merge_image;
    while (true) {
        cout << "Enter image filename to merge\n[or < 0 > to Exit]: ";
        cin >> second_file;
        if (second_file == "0") {
            return;
        }
        try {
            merge_image.loadNewImage(second_file);
            break;
        } catch (...) {
            cout << "File not loaded\n";
        }
    }
    char answer;
    cout << "Want specific blend factor?(y/n) --> ";
    cin >> answer;
    if (answer == 'y' || answer == 'Y'){
        float blend_factor;
        while (true) {
        cout << "Enter your target blend factor (0 --> 1): \n[or < -1 > to return]: ";
        cin >> blend_factor;
        
        if (blend_factor == -1) {
            break;
        }
        if (blend_factor >= 0 && blend_factor <= 1){
            currentImage = mergeFilter(currentImage, merge_image, blend_factor);
            cout << "\nMerge filter applied\n";
            break;
            }else{
                cout << "Enter a value between 0 and 1\n";
            }
        }
    }else{
        currentImage = mergeFilter(currentImage, merge_image);
        cout << "\nMerge filter applied\n";
    }
}

void applySunlightFilter(Image& current_image){
    sunlightFilter(current_image);
    cout << "\nSunlight filter applied\n";
}

void saveCurrentImage(Image& current_image, string& current_file) {
    cout << "[1] Save with the same name\n";
    cout << "[2] Save with a new name\n";
    cout << "Enter Your Choice : ";

    int saveChoice;
    cin >> saveChoice;

    string target_image = current_file;
    if (saveChoice == 2) {
        cout << "Enter new file name : ";
        cin >> target_image;
    }

    try {
        current_image.saveImage(target_image);
        current_file = target_image;
        cout << "Saved as <" << target_image << ">\n";
    } catch (...) {
        cout << "\nCould not save the image\n";
    }
}

bool ask(const string& confirmation) {
    cout << confirmation << " (y/n): ";
    char answer;
    cin >> answer;
    return (answer == 'y' || answer == 'Y');
}


void displayMenu() {
    cout << "\nWELCOME TO BABY PHOTOSHOP\n";
    cout << "Select an option:\n";
    cout << "[1] Load a new image\n";
    cout << "[2] Grayscale Filter\n";
    cout << "[3] Flip Filter\n";
    cout << "[4] Rotation Filter\n";
    cout << "[5] Television Filter\n";
    cout << "[6] Invert Image Filter\n";
    cout << "[7] Darken and Lighten Filter\n";
    cout << "[8] Black and White Filter\n";
    cout << "[9] Resizing Images Filter\n";
    cout << "[10] Merge Images Filter\n";
    cout << "[11] Sunlight  Filter\n";
    cout << "[12] Blur Filter\n";
    cout << "[13] Infrared Filter\n";
    cout << "[14] Make Frame Filter\n";
    cout << "[15] Edges Filter\n";
    cout << "[16] Crop Image Filter\n";
    cout << "[17] Purple Image Filter\n";
    cout << "[18] Save current image\n";
    cout << "[0] Exit\n";
    cout << "Enter Your Choice : ";
}

int main() {
    string current_file;
    Image current_image;

    while (true) {
        cout << "Enter image filename\n[or < 0 > to Exit]: ";
        cin >> current_file;

        if (current_file == "0") {
            return 1;
        }

        try {
            current_image.loadNewImage(current_file);
            break;
        } catch (...) {
        }
    }


    while (true) {
        displayMenu();
        int choice;
        cin >> choice;

        if (choice == 0) {
            if (ask("Save before exiting")) {
                saveCurrentImage(current_image, current_file);
            }
            cout << "Thank You For Using <BABY PHOTOSHOP>!\n";
            break;
        }

        try {
            switch (choice) {
                case 1: {
                    if (ask("Save current image before loading a new one")) {
                        saveCurrentImage(current_image, current_file);
                    }
                    cout << "Enter new image filename to load: ";
                    string new_file;
                    cin >> new_file;
                    current_image.loadNewImage(new_file);
                    current_file = new_file;
                    cout << "Loaded <" << new_file  << ">\n";
                    break;
                }
                case 2:
                    applyGrayscaleFilter(current_image);
                    break;
                case 3:
                    applyFlipFilter(current_image);
                    break;
                case 4:
                    applyRotation(current_image);
                    break;
                case 5:
                    applyDen(current_image);
                    break;
                case 6:
                    applyInvertImage(current_image);
                    break;
                case 7:
                    applyDarkLight(current_image);
                    break;
                case 8:
                    applyBlackAndWhite(current_image);
                    break;
                case 9:
                    applyResizingImages(current_image);
                    break;
                case 10:
                    applyMergeFilter(current_image);
                    break;
                case 11:
                    applySunlightFilter(current_image);
                    break;
                case 12:
                    applyBlurImages(current_image);
                    break;
                case 13:;
                    applyInfraredImages(current_image);
                    break;
                case 14: 
                    applymakeframe(current_image);
                    break;
                case 15:
                    applyedges(current_image);
                    break;
                case 16:
                    applyCroppedImage(current_image);
                    break;
                case 17:
                    applyPurpleImage(current_Image);
                    break;
                case 18:
                    saveCurrentImage(current_image, current_file);
                    break;
                default:
                    cout << "Invalid choice\n";
                    break;
            }
        } catch (...) {
            cout << "\nPlease try again\n ";
        }
    }
    return 0;
}

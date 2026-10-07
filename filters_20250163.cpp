#include "Image_Class.h"
#include <algorithm>
using namespace std;


//            Filters Function             //

// Filter 1: Grayscale Conversion
void grayscaleFilter(Image& img) {
    // loop iterates -->  image pixel
    // col_idx < img.width not col_idx <= img.width 
    // max col_idx = 4 if img.width = 5 as the loop starts from 0

    for (int column = 0 ; column < img.width ; column++ ){
        for (int row = 0 ; row < img.height ; row++ ){
    
            // get the pixel values
            int channels_sum = 0;
            for (int channel =0 ; channel<3 ; channel++){
                channels_sum += img(column , row , channel );
            }

            // filter calculation --> avr --> Gray
            int turn_to_gray = channels_sum / 3;
    
            // Update pixel values
            for (int channel =0 ; channel < 3 ; channel++){
                img(column , row , channel ) = turn_to_gray ;
            }
        }
    }
}


// Filter 5: Flip Image
Image flipFilter(Image& img , string state) {
    // why not the same img ? --> conflict 
    // you may lose pixels you still need
    Image flipped_img(img.width , img.height);

        for (int column = 0 ; column < img.width ; column++ ){
            for (int row = 0 ; row < img.height ; row++ ){
                if (state == "h"){
                    // prepare the position
                    int flip_col = img.width - 1 - column ;

                    // pass the pixel to the new pos
                    for (int channel =0 ; channel < 3 ; channel++){
                        flipped_img(flip_col , row , channel) = img(column , row , channel);
                    }
                    
                } else if (state == "v"){
                    // prepare the position
                    int flip_row = img.height - 1 - row ;

                    // pass the pixel to the new pos
                    for (int channel =0 ; channel < 3 ; channel++){
                        flipped_img(column , flip_row , channel) = img(column , row , channel);
                }
            }
        }
    }
    return flipped_img;
}


// filter resize from sara's filters
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


// Filter 9: Merge Images
// Helping function merge the images only
// return the merged image
Image mergingPixels(Image& img1, Image& img2, float blend_factor){
    Image merged_image(img1.width , img1.height);
    for (int column = 0 ; column < img1.width ; column++ ){
        for (int row = 0 ; row < img1.height ; row++ ){
            for (int channel =0 ; channel<3 ; channel++){
                // manage trancpercity for the pixel 
                // depends on blend factor 0(img2) --> 1(img1)
                merged_image(column , row, channel) = (img1(column , row , channel )*blend_factor) + (img2(column , row , channel )*(1 - blend_factor));
            }
        }
    } 
    return merged_image;
}

// the actualyy function 
// process the images to validate the size
// then call mergingPixels to merge them
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



// Filter 13: Wano Sunlight Fix
// sunlightFilter --> high yello percentage 
// yello --> red + green
void sunlightFilter(Image& img) {
    for (int column = 0 ; column < img.width ; column++ ){
        for (int row = 0 ; row < img.height ; row++ ){

            int red = img(column , row , 0 );
            int green = img(column , row , 1 );
            int blue = img(column , row , 2 );

            // make sure we still 0 --> 255
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


/* GitHub Commands
        git checkout main
        git pull
        git checkout -b feature/grayscale
        git add .
        git commit -m "Add grayscale filter"
        git push -u origin feature/grayscale
*/

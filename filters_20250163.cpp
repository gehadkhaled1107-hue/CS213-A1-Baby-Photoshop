#include "Image_Class.h"
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
void filter8 (Image& image,Image& resized_image,int newW,int newH) {
    float scaleW = (float)image.width / newW;
    float scaleH = (float)image.height / newH;
    for (int X = 0;X < newW;++X) {
        for (int Y = 0;Y < newH;++Y) {
            int orgX = (int)(X * scaleW);
            int orgY = (int)(Y * scaleH);
            if (orgX >= image.width) orgX = image.width -1;
            if (orgY >= image.height) orgY = image.height - 1;
            for (int k = 0;k < 3;++k) {
                resized_image(X,Y,k) = image(orgX,orgY,k);
            }
        }
    }
}


// Filter 9: Merge Images
// Image mergeFilter(const Image& img1, const Image& img2) {
// }



// Filter 13: Wano Sunlight Fix
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




// void displayMenu() {
// }



// main menu --> testing only
int main() {
    string filename;
    // cout << "Enter image filename: ";
    // cin >> filename;

    Image img("luffy.png");
    // cout << "Image loaded: " << img.width << "x" << img.height << "\n";

    // Image flipped_result = flipFilter(img , "v");

    cout << "sunlightFilter filter applied.\n";
    sunlightFilter(img);

    img.saveImage("test_sunlightFilter_output.png");
    cout << "Saved as test_sunlightFilter_output.png\n";

    return 0;
}


/* GitHub Commands
        git checkout main
        git pull
        git checkout -b feature/grayscale
        git add .
        git commit -m "Add grayscale filter"
        git push -u origin feature/grayscale
*/

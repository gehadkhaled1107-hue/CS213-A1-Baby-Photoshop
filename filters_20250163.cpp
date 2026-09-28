#include "Image_Class.h"
using namespace std;

//                                     Filters Function                                           //

// Filter 1: Grayscale Conversion
void grayscaleFilter(Image& img) {
    // loop iterates -->  image pixel
    // col_idx < img.width not col_idx <= img.width 
    // max col_idx = 4 if img.width = 5 as the loop starts from 0
    for (int col_idx = 0 ; col_idx < img.width ; col_idx++ ){
        for (int row_idx = 0 ; row_idx < img.height ; row_idx++ ){
    
            // get the pixel values
            int red_pixels = img(col_idx , row_idx , 0 );
            int green_pixels = img(col_idx , row_idx , 1 );
            int blue_pixels = img(col_idx , row_idx , 2 );
    
            // filter calculation --> avr --> Gray
            int turn_to_gray = (red_pixels + green_pixels + blue_pixels) / 3;
    
            // Update pixel values
            img(col_idx , row_idx , 0 ) = turn_to_gray ;
            img(col_idx , row_idx , 1 ) = turn_to_gray ;
            img(col_idx , row_idx , 2 ) = turn_to_gray ;
        }
    }
}


// Filter 5: Flip Image
Image flipFilter(Image& img) {
    // why not the same img ? --> conflict 
    // you mat loose pixels you still need
    Image flipped_img(img.width , img.height);

    for (int col_idx = 0 ; col_idx < img.width ; col_idx++ ){
        for (int row_idx = 0 ; row_idx < img.height ; row_idx++ ){
    
            // prepare the position
            int flip_col_idx = img.width - 1 - col_idx ;
    
            // pass the pixel to the new pos
            flipped_img(flip_col_idx , row_idx , 0) = img(col_idx , row_idx , 0);
            flipped_img(flip_col_idx , row_idx , 1) = img(col_idx , row_idx , 1);
            flipped_img(flip_col_idx , row_idx , 2) = img(col_idx , row_idx , 2);
        }
    }
    return flipped_img;
}




// Filter 9: Merge Images
// Image mergeFilter(const Image& img1, const Image& img2) {
// }


// Filter 13: Wano Sunlight Fix
// void sunlightFilter(Image& img) {
// }




// void displayMenu() {
// }



// main menu --> testing only
int main() {
    string filename;
    cout << "Enter image filename: ";
    cin >> filename;

    Image img(filename);
    cout << "Image loaded: " << img.width << "x" << img.height << "\n";

    Image flipped_result = flipFilter(img);
    cout << "flipFilter filter applied.\n";

    flipped_result.saveImage("test_flip_output.png");
    cout << "Saved as test_flip_output.png\n";

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


// Library guide --> personal 

// isValidFilename --> check if there is a dot in image file name --> return T , F
// getExtensionType --> check the extention if png\jpg or jpeg \bmp\tga
// Public attributes  width  height  channels = 3(RBG)  unsigned char* imageData(Pointer)
// Image img --> Image img("file name.exe") --> Image newImg(width, Height)
// Image copy(originalImg);      // way
// Image copy = originalImg;     // another way
// Image imgA("cat.png");
// Image imgB("dog.png");
// imgB = imgA;  // copied
/*
 * ============================================================================
 *  Image_Class.h — QUICK REFERENCE 
 * ============================================================================
 *
 *  ATTRIBUTES (read directly, no function call needed):
 *  ----------------------------------------------------
 *  img.width      -> int   : image width in pixels  (number of COLUMNS)
 *  img.height     -> int   : image height in pixels (number of ROWS)
 *  img.channels   -> int   : always 3 in this library (Red, Green, Blue)
 *
 *
 *  CONSTRUCTORS — how to CREATE an Image object:
 *  -----------------------------------------------------------------------
 *  Image img;
 *      -> empty image, all zeros, no data yet.
 *
 *  Image img(std::string sourceFilePath);
 *      sourceFilePath : path/name of an existing image file to load
 *                       (e.g. "sheep.png"). Must end in .png/.bmp/.tga/.jpg/.jpeg
 *      -> THROWS std::invalid_argument if the file is missing, has no
 *         extension, or has an unsupported extension. Wrap in try/catch.
 *
 *  Image img(int newWidth, int newHeight);
 *      newWidth  : desired width  (columns) of the brand-new blank image
 *      newHeight : desired height (rows)    of the brand-new blank image
 *      -> pixel data is UNINITIALIZED GARBAGE. You must fill every pixel
 *         and every channel yourself before saving/using it.
 *
 *  Image img(const Image& sourceImage);
 *      sourceImage : an existing Image to deep-copy (fully independent copy)
 *
 *
 *  ASSIGNMENT (copying into an Image that already exists):
 *  -----------------------------------------------------------------------
 *  destinationImg = sourceImg;
 *      -> deep copy, sourceImg is left untouched, destinationImg gets an
 *         independent copy of its pixel data.
 *
 *
 *  LOADING / SAVING FILES:
 *  -----------------------------------------------------------------------
 *  bool ok = img.loadNewImage(std::string filePathToLoad);
 *      filePathToLoad : path/name of the image file to load INTO this
 *                       existing Image object (replaces whatever was in it)
 *      -> THROWS std::invalid_argument on missing file / bad extension.
 *
 *  bool ok = img.saveImage(std::string filePathToSaveAs);
 *      filePathToSaveAs : path/name to save to, MUST include a valid
 *                         extension (.png .bmp .tga .jpg .jpeg)
 *      -> THROWS std::invalid_argument on missing/bad extension.
 *
 *
 *  READING A PIXEL VALUE:
 *  -----------------------------------------------------------------------
 *  unsigned char value = img.getPixel(int columnIndex, int rowIndex, int colorChannel);
 *  unsigned char value = img(int columnIndex, int rowIndex, int colorChannel);   // shorthand, same thing
 *
 *      columnIndex  : which column (horizontal position), valid range: 0 .. width-1
 *      rowIndex     : which row    (vertical position),   valid range: 0 .. height-1
 *      colorChannel : which color, valid values only: 0 = Red, 1 = Green, 2 = Blue
 *      -> returns a number 0-255 representing that channel's intensity
 *      -> THROWS std::out_of_range if any argument is outside its valid range
 *
 *
 *  WRITING A PIXEL VALUE:
 *  -----------------------------------------------------------------------
 *  img.setPixel(int columnIndex, int rowIndex, int colorChannel, unsigned char newValue);
 *  img(int columnIndex, int rowIndex, int colorChannel) = newValue;   // shorthand, same thing
 *
 *      columnIndex  : which column, valid range: 0 .. width-1
 *      rowIndex     : which row,    valid range: 0 .. height-1
 *      colorChannel : 0 = Red, 1 = Green, 2 = Blue
 *      newValue     : the new intensity to store, must be 0-255
 *      -> THROWS std::out_of_range if columnIndex/rowIndex/colorChannel is invalid
 *
 *
 *  COMMON PATTERN — visiting every pixel of an image:
 *  -----------------------------------------------------------------------
 *  for (int columnIndex = 0; columnIndex < img.width; columnIndex++) {
 *      for (int rowIndex = 0; rowIndex < img.height; rowIndex++) {
 *          unsigned char redValue   = img(columnIndex, rowIndex, 0);
 *          unsigned char greenValue = img(columnIndex, rowIndex, 1);
 *          unsigned char blueValue  = img(columnIndex, rowIndex, 2);
 *          // ... compute something, then write back if needed ...
 *          img(columnIndex, rowIndex, 0) = redValue;
 *      }
 *  }
 *
 *  REMINDERS:
 *   - always use "<" not "<=" in the loops above (columnIndex < width, not <=)
 *   - sum multiple channel values in an int before dividing, to avoid
 *     unsigned char overflow (max 255)
 *   - wrap any constructor/loadNewImage/saveImage call in try/catch
 *   - a newly created Image(w, h) needs every pixel filled manually
 * ============================================================================
 * 
 * 
    Image img;                                    --> create empty image, no data yet
    Image img(filePath);                          --> create image, load from file
    Image img(newWidth, newHeight);               --> create new blank image (uninitialized pixels)
    Image img(sourceImage);                       --> create image, deep-copy from another Image

    destinationImg = sourceImg;                   --> deep-copy assignment

    img.loadNewImage(filePath);                   --> load image into existing object
    img.saveImage(outputFilePath);                --> save image (extension must be .png/.bmp/.tga/.jpg/.jpeg)

    img.getPixel(columnIndex, rowIndex, colorChannel);              --> read pixel value (0-255)
    img(columnIndex, rowIndex, colorChannel);                       --> same as getPixel, shorthand

    img.setPixel(columnIndex, rowIndex, colorChannel, newValue);    --> write pixel value
    img(columnIndex, rowIndex, colorChannel) = newValue;            --> same as setPixel, shorthand

    img.width                                     --> image width (columns)
    img.height                                    --> image height (rows)
    img.channels                                  --> always 3 (R, G, B)
 */

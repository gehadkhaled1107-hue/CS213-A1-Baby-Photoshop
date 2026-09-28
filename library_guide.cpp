/*
 * ============================================================================
 *  Image_Class_Demo.cpp
 * ============================================================================
 *  PURPOSE
 *  -------
 *  This is a STUDY / LEARNING file, NOT a submission file. It does not
 *  implement any of the 16 required filters. Its only job is to walk you
 *  through every public feature of "Image_Class.h" with heavy comments,
 *  so you understand exactly how the library works before you start
 *  writing your own filters.
 *
 *  Per the assignment's AI policy: the 16 filters + menu (Tasks 1-3) must
 *  be written by you, with NO AI-generated code. This file breaks no rule
 *  because it does not solve any task requirement - it's the same kind of
 *  thing as the "ImageProcessingDemo.cpp" sample file the course gave you,
 *  just more detailed. Read it, run it, then close it and write your own
 *  filter functions from scratch.
 *
 *  HOW TO COMPILE
 *  ---------------
 *  Put this file in the SAME folder as: Image_Class.h, stb_image.h,
 *  stb_image_write.h, and a test image (e.g. from the test_images folder).
 *  Then compile like any normal C++ file, e.g.:
 *      g++ Image_Class_Demo.cpp -o demo
 *      ./demo
 * ============================================================================
 */

#include <iostream>
using namespace std;

// This single include line pulls in the WHOLE library:
//   - Image_Class.h itself
//   - stb_image.h        (the actual pixel-loading engine)
//   - stb_image_write.h  (the actual pixel-saving engine)
// You never need to #include the stb files yourself - Image_Class.h does
// it for you via #define STB_IMAGE_IMPLEMENTATION / STB_IMAGE_WRITE_IMPLEMENTATION
// followed by #include "stb_image.h" / #include "stb_image_write.h".
// NOTE: because of that #define trick, Image_Class.h must be included
// in exactly ONE .cpp file in your whole project (never in two .cpp files,
// and never in another .h that gets included twice), or you'll get
// "multiple definition" linker errors. In your real project, #include it
// only in main.cpp, and just forward-declare/use "class Image;" elsewhere
// if you ever need to (usually you won't - just always include it in main.cpp
// and put all your filter functions in main.cpp or in headers that don't
// also include Image_Class.h).
#include "Image_Class.h"


int main() {

    // ========================================================================
    // SECTION 1: THE Image CLASS - WHAT IT ACTUALLY STORES
    // ========================================================================
    // An Image object is really just 4 things:
    //   int width, height        -> dimensions in pixels
    //   int channels             -> always forced to 3 (R, G, B) by this
    //                                library, even if the source file had
    //                                a 4th (alpha/transparency) channel
    //   unsigned char* imageData -> a big 1D array on the heap holding
    //                                every pixel's R,G,B values back to back
    //
    // So for a 4x3 image, imageData has 4*3*3 = 36 bytes laid out like:
    //   [R00,G00,B00, R10,G10,B10, R20,G20,B20, R30,G30,B30,   <- row y=0
    //    R01,G01,B01, R11,G11,B11, R21,G21,B21, R31,G31,B31,   <- row y=1
    //    R02,G02,B02, R12,G12,B12, R22,G22,B22, R32,G32,B32]   <- row y=2
    //
    // The class hides this math from you: instead of computing the index
    // yourself, you use getPixel/setPixel/operator() (see Section 3).


    // ========================================================================
    // SECTION 2: LOADING AN IMAGE (constructor + loadNewImage)
    // ========================================================================
    cout << "=== SECTION 2: Loading an image ===\n";

    string filename;
    cout << "Enter an image filename to load (e.g. sheep.png): ";
    cin >> filename;

    // Option A: load directly via the constructor.
    // Internally this just calls loadNewImage(filename) for you.
    Image img(filename);

    // What loadNewImage() does step by step (you don't call these yourself,
    // this is just so you understand what's happening under the hood):
    //   1. isValidFilename()  -> checks the string has a '.' in it at all.
    //      NOTE: it does NOT check that the extension is one of the 4
    //      supported ones - that check happens in the next step.
    //   2. getExtensionType() -> looks at the text AFTER the last '.' and
    //      returns PNG_TYPE / BMP_TYPE / TGA_TYPE / JPG_TYPE / UNSUPPORTED_TYPE.
    //      IMPORTANT: this comparison is case-sensitive and exact, so
    //      "photo.PNG" or "photo.Png" will be reported UNSUPPORTED_TYPE
    //      even though PNG is a supported format. Your menu code should
    //      probably lower-case the extension before relying on this, or at
    //      least warn the user to type it in lowercase.
    //   3. stbi_load() (from stb_image.h) actually reads the file bytes off
    //      disk, decodes the PNG/JPG/BMP/TGA format, and fills width,
    //      height, and allocates+fills imageData for you.
    //   4. channels is then FORCED to 3, even if stbi_load detected 4
    //      (e.g. a PNG with transparency). This is intentional - see the
    //      comment already in Image_Class.h about screenshot PNGs.
    //
    // If the file doesn't exist, or the extension is unsupported, this
    // constructor THROWS an exception (std::invalid_argument). It does NOT
    // return an error code. That means in your real menu code you MUST
    // wrap image loading in a try/catch, otherwise your whole program will
    // crash the instant the user mistypes a filename:
    try {
        Image test("this_file_does_not_exist.png");
    } catch (const std::exception& e) {
        cout << "(Demo) Caught expected error: " << e.what() << "\n";
    }

    cout << "Loaded '" << filename << "' successfully!\n";
    cout << "Width  = " << img.width  << " pixels\n";
    cout << "Height = " << img.height << " pixels\n";
    cout << "Channels = " << img.channels << " (always 3 = RGB in this library)\n\n";


    // ========================================================================
    // SECTION 3: READING PIXELS - THREE EQUIVALENT WAYS
    // ========================================================================
    cout << "=== SECTION 3: Reading pixels ===\n";

    // All three lines below read the EXACT same value - the Red channel of
    // the pixel at column x=0, row y=0 (the top-left pixel).
    unsigned char r1 = img.getPixel(0, 0, 0); // explicit method call
    unsigned char r2 = img(0, 0, 0);          // operator() overload - same thing, shorter
    // (there is no operator[] shortcut in this class, only getPixel/operator())

    cout << "Top-left pixel Red channel via getPixel(): " << (int)r1 << "\n";
    cout << "Top-left pixel Red channel via operator(): " << (int)r2 << "\n";
    // NOTE: we cast to (int) before printing. If you print an unsigned char
    // directly with cout, it prints it as a CHARACTER (like 'A'), not as a
    // number, because unsigned char IS the same type cout uses for text.
    // Always cast to int (or short) when you want to see the numeric value.

    // Reading a full pixel's RGB in one go:
    int x = 0, y = 0;
    unsigned char red   = img(x, y, 0);
    unsigned char green = img(x, y, 1);
    unsigned char blue  = img(x, y, 2);
    cout << "Pixel (0,0) = R:" << (int)red << " G:" << (int)green
         << " B:" << (int)blue << "\n";

    // getPixel()/operator() THROW std::out_of_range if x, y or c are outside
    // valid bounds. BUT be careful: the check inside Image_Class.h is
    //      if (x > width || x < 0)   ... same pattern for y ...
    // This means x == width (one past the last valid column) is NOT caught
    // and will read/write memory outside the array! Valid x is 0..width-1,
    // valid y is 0..height-1. ALWAYS loop with strict "<", never "<=":
    //   for (int x = 0; x < img.width; x++)   // correct
    //   for (int x = 0; x <= img.width; x++)  // WRONG - will go out of bounds
    cout << "\n";


    // ========================================================================
    // SECTION 4: WRITING/MODIFYING PIXELS
    // ========================================================================
    cout << "=== SECTION 4: Writing pixels ===\n";

    // Two equivalent ways to WRITE a pixel value:
    img.setPixel(0, 0, 0, 255);   // explicit method: set Red channel of (0,0) to 255
    img(0, 0, 1) = 255;           // operator() returns a REFERENCE, so you can
                                   // assign to it directly like a normal variable.
                                   // This works because operator() returns
                                   // "unsigned char&" (a reference), not a copy.

    cout << "Set pixel (0,0) Red and Green channels to 255 (max brightness).\n";
    cout << "New pixel (0,0) = R:" << (int)img(0,0,0) << " G:" << (int)img(0,0,1)
         << " B:" << (int)img(0,0,2) << "\n\n";

    // This "operator() returns a reference" trick is exactly how a real
    // grayscale filter works, roughly like this (shown here ONLY as a
    // read-along example of the mechanism - do not copy this into your own
    // grayscale filter, write your own from scratch per the AI policy):
    //
    //   for (int i = 0; i < img.width; i++) {
    //       for (int j = 0; j < img.height; j++) {
    //           int avg = (img(i,j,0) + img(i,j,1) + img(i,j,2)) / 3;
    //           img(i,j,0) = avg;
    //           img(i,j,1) = avg;
    //           img(i,j,2) = avg;
    //       }
    //   }
    //
    // Two easy-to-miss bugs students hit here:
    //   1. img(i,j,0) + img(i,j,1) + img(i,j,2) can be up to 255*3 = 765,
    //      which OVERFLOWS an unsigned char (max 255) if you don't store
    //      the sum in an int first. Always accumulate in an int, THEN
    //      divide by 3, THEN assign the small result back into the pixel.
    //   2. Loop order: this library indexes as img(x, y, channel), i.e.
    //      "column-index, row-index". Some students accidentally swap x
    //      and y in their nested loops, which still runs fine on a SQUARE
    //      image (width == height) but produces a sheared/rotated result
    //      on any non-square image. Double-check with a non-square test
    //      image (e.g. 600x400) to catch this bug early.


    // ========================================================================
    // SECTION 5: CREATING A BLANK IMAGE (for filters that change size)
    // ========================================================================
    cout << "=== SECTION 5: Creating a new blank image ===\n";

    // Filters like Resize, Rotate, Crop, and Merge don't modify the
    // original image in place - they build a NEW Image of a different
    // size and fill it pixel by pixel from the source.
    int newW = 200, newH = 100;
    Image blank(newW, newH);
    cout << "Created a new empty image, " << newW << "x" << newH << ".\n";

    // *** CRITICAL GOTCHA ***
    // This constructor allocates memory with malloc() but does NOT
    // initialize it to any value (not even to black/0). Every pixel starts
    // as GARBAGE data. If your filter creates a new Image and forgets to
    // write to some pixel, that pixel will look like TV static in the
    // saved file. ALWAYS make sure your loops that build a new image visit
    // every single pixel and every single channel (0,1,2) at least once.
    // A quick sanity habit: after creating a blank image, immediately fill
    // it (e.g. with black) before you start writing real values into it,
    // OR just be very careful your fill loop has no gaps.
    for (int i = 0; i < blank.width; i++) {
        for (int j = 0; j < blank.height; j++) {
            for (int c = 0; c < 3; c++) {
                blank(i, j, c) = 0; // pre-fill with black so nothing is garbage
            }
        }
    }
    cout << "Pre-filled the new image with black to avoid garbage pixels.\n\n";


    // ========================================================================
    // SECTION 6: COPYING AN IMAGE (copy constructor / operator=)
    // ========================================================================
    cout << "=== SECTION 6: Copying images ===\n";

    // Both of these make a DEEP copy - a brand new imageData array with the
    // same content, NOT just a pointer to the same memory. This matters:
    // if it were a shallow copy, both Image objects' destructors would try
    // to free the SAME memory, crashing your program (double free).
    Image copyA(img);      // copy constructor: "Image copyA = img;" also calls this
    Image copyB(1, 1);     // start as something else...
    copyB = img;           // ...then operator= makes it an independent deep copy of img

    cout << "copyA and copyB are independent deep copies of img.\n";
    copyA(0, 0, 2) = 0; // change ONLY copyA
    cout << "After modifying only copyA, original img Blue at (0,0) is still: "
         << (int)img(0, 0, 2) << " (unchanged, proving it's a real deep copy)\n\n";

    // Self-assignment safety: operator= checks "if (this == &image) return *this;"
    // first, so code like "img = img;" is safe and won't corrupt anything.


    // ========================================================================
    // SECTION 7: SAVING AN IMAGE
    // ========================================================================
    cout << "=== SECTION 7: Saving an image ===\n";

    string outFilename = "demo_output.png";
    // saveImage() looks at the extension the SAME way loading does
    // (isValidFilename + getExtensionType), and then calls the matching
    // stb_image_write function:
    //   .png  -> stbi_write_png(...)
    //   .bmp  -> stbi_write_bmp(...)
    //   .tga  -> stbi_write_tga(...)
    //   .jpg / .jpeg -> stbi_write_jpg(..., quality=90)
    // Just like loading, an unsupported/missing extension THROWS an
    // exception rather than returning false - wrap this in try/catch too
    // in your real menu code.
    try {
        img.saveImage(outFilename);
        cout << "Saved current image to '" << outFilename << "'.\n";
    } catch (const std::exception& e) {
        cout << "Save failed: " << e.what() << "\n";
    }


    // ========================================================================
    // SECTION 8: DESTRUCTION (automatic - but good to understand)
    // ========================================================================
    // You never call this yourself. When an Image object goes out of scope
    // (e.g. at the end of main(), or the end of any {} block it was
    // declared in), its destructor runs automatically and:
    //   - calls stbi_image_free(imageData) to release the pixel memory
    //   - resets width, height, imageData to 0/nullptr
    // This is why the copy constructor/operator= MUST make deep copies:
    // otherwise two Image objects would both try to free the same pointer
    // when they're destroyed, crashing the program.

    cout << "\n=== End of demo. All Image objects will now be destroyed "
            "automatically as they go out of scope. ===\n";

    return 0;
}

/*
 * ============================================================================
 *  QUICK-REFERENCE CHEAT SHEET
 * ============================================================================
 *  Image img("file.png");        Load an image from disk (throws on error)
 *  Image img(w, h);              Create a blank w x h image (UNINITIALIZED data!)
 *  Image copy(other);            Deep-copy constructor
 *  copy = other;                 Deep-copy assignment
 *  img.width / img.height        Dimensions (read-only in practice)
 *  img.channels                  Always 3 in this library
 *  img(x, y, c)                  Read/write pixel - c is 0=R, 1=G, 2=B
 *  img.getPixel(x, y, c)         Same as img(x,y,c), explicit method form
 *  img.setPixel(x, y, c, val)    Explicit write method
 *  img.saveImage("out.jpg");     Save (throws on bad/missing extension)
 *
 *  VALID RANGES:      0 <= x < width   |   0 <= y < height   |   0 <= c < 3
 *  SUPPORTED FORMATS:  .png  .bmp  .tga  .jpg  .jpeg   (lowercase only!)
 *
 *  COMMON BUGS TO AVOID:
 *   - Using "<=" instead of "<" in loops -> reads/writes out of bounds
 *   - Summing 3 unsigned char pixel values without an int accumulator -> overflow
 *   - Forgetting to fill EVERY pixel of a newly created Image(w,h) -> garbage pixels
 *   - Not wrapping loadNewImage/constructor/saveImage in try/catch -> crash on bad input
 *   - Mixing up (x,y) vs (row,col) order -> looks fine on square images, breaks on
 *     rectangular ones
 *   - #include "Image_Class.h" in more than one .cpp file -> linker errors
 * ============================================================================
 * 
 */
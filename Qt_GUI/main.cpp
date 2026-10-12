/*
    Project: Baby Photoshop
    Course: CS213 - OOP Programming
    Description: Loads images, applies filters, and saves results.
    Team and work distribution:
        Gehad Khaled - 20250163 - S11
            - Filters 
            [1]Grayscale Conversion
            [5]Flip Image
            [9]Merge Images
            [13]Sunlight 

        Shahd Mohamed- 20250326 - S11
            - Filters 
            [2]Black and White
            [6]Rotate Image
            [10]Detect Image Edges
            [14]TV images
    
        Sara Yasser - 20250840 - S11
            - Filters 
            [3]Invert Image
            [7]Darken and Lighten Image
            [11]Crop Image 
            [15]Purple Image 
    
        Sara Mostafa - 20251186- S11
            - Filters 
            [4]Adding a Frame to the Picture
            [8]Resizing Images
            [12]Blur Images
            [16]Infrared Image
    Shared team work:
        All four team members collaborated on:
            - Menu, image loading, and image saving.
            - Filter 17: Image Skewing.
            - Filter 18: Oil Painting.
            - GUI development and integration.
            - Integration and testing of all filters.
    Video demo: https://drive.google.com/file/d/1oKOljr7I7lT48hSryqmTCPZ3bc1FJVLj/view?usp=drivesdk
    Shared document: https://docs.google.com/document/d/1tuVbLy5fPn-VuRsbBsRED4HcbU98iCNy/edit?usp=drive_link&ouid=114385788039595595965&rtpof=true&sd=true
*/
#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}

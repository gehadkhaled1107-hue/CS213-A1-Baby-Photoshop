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
            GUI

        Shahd Mohamed- 20250326 - S11
            - Filters 
            [2]Black and White
            [6]Rotate Image
            [10]Detect Image Edges
            [14]TV images
            [18]oil painting
    
        Sara Yasser - 20250840 - S11
            - Filters 
            [3]Invert Image
            [7]Darken and Lighten Image
            [11]Crop Image 
            [15]Purple Image 
            GUI
            
    
        Sara Mostafa - 20251186- S11
            - Filters 
            [4]Adding a Frame to the Picture
            [8]Resizing Images
            [12]Blur Images
            [16]Infrared Image
            [17]Image Skewing Filter
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

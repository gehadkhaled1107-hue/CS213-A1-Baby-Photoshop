#include "Image_Class.h"
using namespace std;


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

void applyGrayscaleFilter(string file_name) {
    Image img(file_name);
    grayscaleFilter(img);
    cout << "\nGrayscale Filter applied successfully\n";
    string saving_name = "Grayscaled_" + file_name;
    img.saveImage(saving_name);
    cout << "Saved as " + saving_name + "\n";
}


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

void applyFlipFilter(string file_name){
    int direction;
    Image img(file_name);
    cout << "Select Flipping Direction\n";
    cout << "[1] Vertical\n";
    cout << "[2] Horizontal\nEnter Your Choice : ";
    cin >> direction;

    switch (direction) {
        case 1:{
            Image flipped_img = flipFilter(img , "v");
            cout << "\nFlip Filter applied Vertically\n";
            string saving_name = "Flipped_V_" + file_name;
            flipped_img.saveImage(saving_name);
            cout << "Saved as " + saving_name + "\n";
            break;
        }
        case 2:{
            Image flipped_img = flipFilter(img , "h");
            cout << "\nFlip Filter applied Horizontally\n";
            string saving_name = "Flipped_H_" + file_name;
            flipped_img.saveImage(saving_name);
            cout << "Saved as " + saving_name + "\n";
            break;
        }
        default:
            cout << "Invalid choice\n";
            break;
    }
}

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

void applyrotation(string file_name ) {
    Image img(file_name);
    int degree;
    cout << "Enter a degree 90,180,270 : " << endl;
    cin >> degree;
    img.loadNewImage( file_name);
    rotation(img,degree);
    string newname;
    cout << "Enter image new name : " << endl;
    cin >> newname;
    img.saveImage(newname);
    cout << "The image was saved!" << endl;
}

void den(Image& img) {
    for (int i=0 ; i<img.height ; ++i) {
        for (int j=0 ; j<img.width ; ++j) {
            if (i%4!=0) {
                for (int c=0 ; c<3 ; ++c) {
                    img.setPixel(j,i,c,img.getPixel(j,i,c)*0.5);
                }
            }
        }
    }
}

void applyden(string file_name) {
    Image img(file_name);
    string newname;
    cout << "Enter image new name : " << endl;
    cin >> newname;
    img.loadNewImage(file_name);
    den(img);
    img.saveImage(newname);
    cout << "The image was saved!" << endl;
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

void applyinvertImage( string file_name ){
    Image img(file_name);
    invertImage(img);

    img.saveImage("mario_yoshi_inverted.png");
    cout << "Inverted image saved!\n";
}

void darkenImage(Image& img) {
    for (int i = 0; i < img.width; i++) {
        for(int j = 0; j < img.height; j++) {
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

void applydark_light(string file_name){
    Image img(file_name);

    cout << "Choose option:\n1. Darken (50%)\n2. Lighten (50%)\n";

    int choice;
    cin >> choice;

    if (choice == 1) {
        darkenImage(img);
        img.saveImage("building_darkened.png");
        cout << "Darkened image saved!\n";
    }
    else if (choice == 2) {
        lightenImage(img);
        img.saveImage("building_lightened.png");
        cout << "Lightened image saved!\n";
    }
    else {
        cout << "Invalid choice!\n";
    }
}

void Black_and_White(Image& img) {
    for (int i = 0;i < img.width;++i) {
        for (int j = 0;j < img.height;++j) {
            unsigned int avg = 0;
            for (int k = 0;k < 3;++k) {  
                avg += img(i,j,k);
            }
            avg = avg / 3;
            int value;
            if (avg >= 128) value = 255;
            else value = 0;
            for (int k = 0;k < 3;++k) {
                img(i,j,k) = value;
            }
        }
    }
}

void applyBlack_and_White(string file_name) {
    Image img(file_name);
    Black_and_White(img);
    cout << "Enter image new name : " << endl;
    string newname;
    cin >> newname;
    img.saveImage(newname);
    cout << "The image was saved!" << endl;
}

void Resizing_Images(Image& img,Image& resized_img,int newW,int newH) {
    float scaleW = (float)img.width / newW;
    float scaleH = (float)img.height / newH;
    for (int X = 0;X < newW;++X) {
        for (int Y = 0;Y < newH;++Y) {
            int orgX = (int)(X * scaleW);
            int orgY = (int)(Y * scaleH);
            if (orgX >= img.width) orgX = img.width -1;
            if (orgY >= img.height) orgY = img.height - 1;
            for (int k = 0;k < 3;++k) {
                resized_img(X,Y,k) = img(orgX,orgY,k);
            }
        }
    }
}

void applyResizing_Images(string file_name,int newW,int newH) {
    Image img(file_name);
    Image resized_img(newW,newH);
    Resizing_Images(img,resized_img,newW,newH);
    cout << "Enter image new name : " << endl;
    string newname;
    cin >> newname;
    resized_img.saveImage(newname);
    cout << "The image was saved!" << endl;
}
void displayMenu() {
    cout << "\nWELCOME TO BABY PHOTOSHOP\n";
    cout << "Select Your Filter:\n";
    cout << "[1] Grayscale Filter\n";
    cout << "[2] Flip Filter\n";
    cout << "[3] Rotation Filter\n";
    cout << "[4] Television Filter\n";
    cout << "[5] Invert Image Filter\n";
    cout << "[6] Darken and Lighten Filter\n";
    cout << "[7] Black and White Filter\n";
    cout << "[8] Resizing Images Filter\n";
    
    cout << "[0] Exit\n";
}

int main(){
    string file_name;
    int choice;
    
    while (true) {
        displayMenu();
        cout << "Enter Your Choice : ";
        cin >> choice;

        if (choice == 0){
            cout << "Thank You For Using <BABY PHOTOSHOP>!\n";
            break;
        }

        cout << "Enter image filename: ";
        cin >> file_name;
        
        switch (choice) {
            case 1:{
                applyGrayscaleFilter(file_name);
                break;
            }
            case 2:{
                applyFlipFilter(file_name);
                break;
            }
            case 3:{
                applyrotation(file_name);
                break;
            }
            case 4:{
                applyden(file_name);
                break;
            }
            case 5:{
                applyinvertImage(file_name);
                break;
            }
            case 6:{
                applydark_light(file_name);
                break;
            }
            case 7:{
                applyBlack_and_White(file_name);
                break;
            }
            case 8:{
                int newW,newH;
                cin >> newW >> newH;
                applyResizing_Images(file_name,newW,newH);
                break;
            }
            default:
                cout << "Invalid choice\n";
                break;
        }
    }
    return 0;
}
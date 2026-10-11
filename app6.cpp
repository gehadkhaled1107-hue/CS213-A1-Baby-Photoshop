#include "Image_Class.h"
using namespace std;
void filter17 (Image& image) {
    double angle_degree;
    cout << "Enter the skew angle (in degrees): ";
    cin >> angle_degree;

    double angle_rad = (angle_degree * 3.14159265 / 180.0);
    double skew_factor = tan(angle_rad);

    int org_width = image.width;
    int org_height = image.height;

    int max_shift = abs(skew_factor * org_height);
    int new_width = org_width + max_shift;

    Image skewed_image(new_width,org_height);

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
                    skewed_image(new_x,y,k) = image(x,y,k);
                }
            }
        }
    }
    skewed_image.saveImage("filter17.jpg"); //filter17
}
int main() {
    string filename;
    cin >> filename; 
    Image image(filename);
    filter17(image);
} 
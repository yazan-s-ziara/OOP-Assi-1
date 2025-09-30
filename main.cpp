#include <bits/stdc++.h>
#include "Image_Class.h"
using namespace std;


void applyBlackAndWhite(Image& img) {
    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            unsigned char r = img.getPixel(x, y, 0);
            unsigned char g = img.getPixel(x, y, 1);
            unsigned char b = img.getPixel(x, y, 2);
            unsigned char gray = static_cast<unsigned char>(0.299*r + 0.587*g + 0.114*b);
            img.setPixel(x, y, 0, gray);
            img.setPixel(x, y, 1, gray);
            img.setPixel(x, y, 2, gray);
        }
    }
    cout << "Black & White filter applied.\n";
}


void applyInvert(Image& img) {
    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            for (int c = 0; c < 3; c++) {
                unsigned char oldValue = img.getPixel(x, y, c);
                img.setPixel(x, y, c, 255 - oldValue);
            }
        }
    }
    cout << "Invert Colors filter applied.\n";
}


void applyRotate(Image& img) {
    cout << "Rotate by (90 / 180 / 270): ";
    int angle; cin >> angle;

    Image rotated;
    if (angle == 90) {
        rotated = Image(img.height, img.width);
        for (int y = 0; y < img.height; y++) {
            for (int x = 0; x < img.width; x++) {
                for (int c = 0; c < 3; c++) {
                    unsigned char val = img.getPixel(x, y, c);
                    rotated.setPixel(img.height - 1 - y, x, c, val);
                }
            }
        }
    }
    else if (angle == 180) {
        rotated = Image(img.width, img.height);
        for (int y = 0; y < img.height; y++) {
            for (int x = 0; x < img.width; x++) {
                for (int c = 0; c < 3; c++) {
                    unsigned char val = img.getPixel(x, y, c);
                    rotated.setPixel(img.width - 1 - x, img.height - 1 - y, c, val);
                }
            }
        }
    }
    else if (angle == 270) {
        rotated = Image(img.height, img.width);
        for (int y = 0; y < img.height; y++) {
            for (int x = 0; x < img.width; x++) {
                for (int c = 0; c < 3; c++) {
                    unsigned char val = img.getPixel(x, y, c);
                    rotated.setPixel(y, img.width - 1 - x, c, val);
                }
            }
        }
    }
    else {
        cout << " Invalid angle. Use 90, 180 or 270.\n";
        return;
    }

    img = rotated;
    cout << " Rotate " << angle << " degrees applied.\n";
}


void saveImageFlow(Image& img, string& filename) {
    cout << "Save to same file? (y/n): ";
    char c;
    cin >> c;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

    string out = filename;
    if (c == 'n' || c == 'N') {
        cout << "Enter new filename (with extension, e.g. result.jpg): ";
        getline(cin, out);
    }

    try {
        img.saveImage(out);
        filename = out;
        cout << " Saved: " << out << "\n";
    } catch (exception& e) {
        cout << " Error while saving: " << e.what() << "\n";
    }
}


int main() {
    Image img;
    string filename;


    while (true) {
        cout << "Enter image file to load: ";
        getline(cin, filename);
        try {
            img.loadNewImage(filename);
            break;
        } catch (exception& e) {
            cout << "Error: " << e.what() << "\n";
        }
    }

    bool running = true;
    while (running) {
        cout << "\n--- MENU ---\n";
        cout << "1. Load new image\n";
        cout << "2. Apply Black & White filter\n";
        cout << "3. Apply Invert Colors filter\n";
        cout << "4. Apply Frame (simulation)\n";
        cout << "5. Apply Rotate filter\n";
        cout << "6. Save image\n";
        cout << "7. Exit\n";
        cout << "Choice: ";
        int ch; cin >> ch;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (ch == 1) {
            cout << "Save current before load? (y/n): ";
            char c; cin >> c;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (c == 'y' || c == 'Y') saveImageFlow(img, filename);

            cout << "Enter image file to load: ";
            getline(cin, filename);
            try { img.loadNewImage(filename); }
            catch (exception& e) { cout << "Error: " << e.what() << "\n"; }
        }
        else if (ch == 2) {
            applyBlackAndWhite(img);
        }
        else if (ch == 3) {
            applyInvert(img);
        }
        else if (ch == 4) {
            cout << "Frame filter (simulation only).\n";
        }
        else if (ch == 5) {
            applyRotate(img);
        }
        else if (ch == 6) {
            saveImageFlow(img, filename);
        }
        else if (ch == 7) {
            cout << "Save before exit? (y/n): ";
            char c; cin >> c;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (c == 'y' || c == 'Y') saveImageFlow(img, filename);
            running = false;
        }
        else {
            cout << "Invalid choice.\n";
        }
    }

    cout << "Goodbye.\n";
    return 0;
}

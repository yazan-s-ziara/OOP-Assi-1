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

void saveImageFlow(Image& img, string& filename) {
    cout << "Save to same file? (y/n): ";
    char c; cin >> c; cin.ignore();
    string out = filename;
    if (c == 'n' || c == 'N') {
        cout << "Enter new filename: ";
        getline(cin, out);
    }
    img.saveImage(out);
    filename = out;
    cout << "Saved: " << out << "\n";
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
        cout << "3. Apply Frame (simulation)\n";
        cout << "4. Apply Rotate (simulation)\n";
        cout << "5. Save image\n";
        cout << "6. Exit\n";
        cout << "Choice: ";
        int ch; cin >> ch; cin.ignore();

        if (ch == 1) {
            cout << "Save current before load? (y/n): ";
            char c; cin >> c; cin.ignore();
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
            cout << "Frame filter (simulation only).\n";
        }
        else if (ch == 4) {
            cout << "Rotate filter (simulation only).\n";
        }
        else if (ch == 5) {
            saveImageFlow(img, filename);
        }
        else if (ch == 6) {
            cout << "Save before exit? (y/n): ";
            char c; cin >> c; cin.ignore();
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


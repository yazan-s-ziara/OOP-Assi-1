#include <bits/stdc++.h>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

bool validExtension(const string& filename) {
    vector<string> exts = {".jpg", ".jpeg", ".bmp", ".png"};
    string ext = fs::path(filename).extension().string();
    transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
    return find(exts.begin(), exts.end(), ext) != exts.end();
}

bool fileExists(const string& filename) {
    return fs::exists(filename);
}

string loadImage() {
    string file;
    while (true) {
        cout << "Enter image file to load: ";
        getline(cin, file);
        if (!fileExists(file)) {
            cout << "File does not exist.\n";
            continue;
        }
        if (!validExtension(file)) {
            cout << "Invalid file extension.\n";
            continue;
        }
        break;
    }
    cout << "Image loaded: " << file << "\n";
    return file;
}

void applyFilter(string& currentImage, int filterChoice) {
    if (filterChoice == 1) {
        cout << "Applying grayscale filter...\n";
    } else if (filterChoice == 2) {
        cout << "Applying framing filter...\n";
        cout << "Choose type: 1) Simple 2) Fancy: ";
        int type; cin >> type; cin.ignore();
        cout << "Enter color: ";
        string color; getline(cin, color);
        cout << (type == 1 ? "Simple" : "Fancy") << " frame with color " << color << " applied.\n";
    } else if (filterChoice == 3) {
        cout << "Applying rotation filter...\n";
    } else {
        cout << "Unknown filter.\n";
    }
    currentImage += "_modified";
}

void saveImage(const string& currentImage) {
    cout << "Save current image.\n";
    cout << "Save to same file? (y/n): ";
    char c; cin >> c; cin.ignore();
    string saveFile = currentImage;
    if (c == 'n' || c == 'N') {
        cout << "Enter new filename: ";
        getline(cin, saveFile);
        if (!validExtension(saveFile)) {
            cout << "Invalid extension. Not saved.\n";
            return;
        }
    }
    cout << "Image saved to " << saveFile << "\n";
}

int main() {
    string currentImage = loadImage();
    bool running = true;
    while (running) {
        cout << "\n--- MENU ---\n";
        cout << "1. Load a new image\n";
        cout << "2. Apply Filter 1 (Grayscale)\n";
        cout << "3. Apply Filter 2 (Frame)\n";
        cout << "4. Apply Filter 3 (Rotate)\n";
        cout << "5. Save image\n";
        cout << "6. Exit\n";
        cout << "Choice: ";
        int choice; cin >> choice; cin.ignore();
        if (choice == 1) {
            cout << "Save current before loading new? (y/n): ";
            char c; cin >> c; cin.ignore();
            if (c == 'y' || c == 'Y') saveImage(currentImage);
            currentImage = loadImage();
        } else if (choice >= 2 && choice <= 4) {
            applyFilter(currentImage, choice - 1);
        } else if (choice == 5) {
            saveImage(currentImage);
        } else if (choice == 6) {
            cout << "Save before exit? (y/n): ";
            char c; cin >> c; cin.ignore();
            if (c == 'y' || c == 'Y') saveImage(currentImage);
            running = false;
        } else {
            cout << "Invalid choice.\n";
        }
    }
    cout << "Goodbye.\n";
}

// Names & IDs:
// 1. Mahmoud Ahmed Mohamed (ID: 20221134) – Grayscale, Merge
// 2. Ziad Alaa Mokhtar (ID: 20240216) – Invert, Rotate
// 3. Yazan Samir Mohammed (ID: 20243056) – Flip, Black & White
// All team members worked on the Menu



#include <bits/stdc++.h>
#include "Image_Class.h"
using namespace std;

Image resizeImage(const Image& img, int newW, int newH) {
    Image out(newW, newH);
    out.channels = img.channels;
    for (int y = 0; y < newH; y++) {
        for (int x = 0; x < newW; x++) {
            int srcX = x * img.width / newW;
            int srcY = y * img.height / newH;
            for (int c = 0; c < img.channels; c++) {
                unsigned char val = img.getPixel(srcX, srcY, c);
                out.setPixel(x, y, c, val);
            }
        }
    }
    return out;
}

Image mergeImages(Image& img1, Image& img2, bool resizeOption) {
    Image result;

    if (resizeOption) {
        int targetW = std::max(img1.width, img2.width);
        int targetH = std::max(img1.height, img2.height);

        Image resized1 = resizeImage(img1, targetW, targetH);
        Image resized2 = resizeImage(img2, targetW, targetH);

        result = Image(targetW, targetH);
        result.channels = img1.channels;

        for (int y = 0; y < targetH; y++) {
            for (int x = 0; x < targetW; x++) {
                for (int c = 0; c < img1.channels; c++) {
                    unsigned char p1 = resized1.getPixel(x, y, c);
                    unsigned char p2 = resized2.getPixel(x, y, c);
                    unsigned char merged = static_cast<unsigned char>((p1 + p2) / 2);
                    result.setPixel(x, y, c, merged);
                }
            }
        }
    } else {
        int targetW = std::min(img1.width, img2.width);
        int targetH = std::min(img1.height, img2.height);

        result = Image(targetW, targetH);
        result.channels = img1.channels;

        for (int y = 0; y < targetH; y++) {
            for (int x = 0; x < targetW; x++) {
                for (int c = 0; c < img1.channels; c++) {
                    unsigned char p1 = img1.getPixel(x, y, c);
                    unsigned char p2 = img2.getPixel(x, y, c);
                    unsigned char merged = static_cast<unsigned char>((p1 + p2) / 2);
                    result.setPixel(x, y, c, merged);
                }
            }
        }
    }

    return result;
}

void applyGrayscale(Image& img) {
    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            unsigned char r = img.getPixel(x, y, 0);
            unsigned char g = img.getPixel(x, y, 1);
            unsigned char b = img.getPixel(x, y, 2);
            unsigned char gray = static_cast<unsigned char>(0.299 * r + 0.587 * g + 0.114 * b);
            img.setPixel(x, y, 0, gray);
            img.setPixel(x, y, 1, gray);
            img.setPixel(x, y, 2, gray);
        }
    }
    cout << "Grayscale filter applied.\n";
}

void applyBlackAndWhite(Image& img) {
    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            unsigned char r = img.getPixel(x, y, 0);
            unsigned char g = img.getPixel(x, y, 1);
            unsigned char b = img.getPixel(x, y, 2);
            unsigned char gray = static_cast<unsigned char>(0.299*r + 0.587*g + 0.114*b);
            for (int c = 0; c < img.channels; c++) img.setPixel(x, y, c, gray);
        }
    }
    cout << "Black & White filter applied.\n";
}

void applyInvert(Image& img) {
    for (int y = 0; y < img.height; y++)
        for (int x = 0; x < img.width; x++)
            for (int c = 0; c < img.channels; c++)
                img.setPixel(x, y, c, 255 - img.getPixel(x, y, c));
    cout << "Invert filter applied.\n";
}

void flipHorizontal(Image& img) {
    for (int y = 0; y < img.height; y++)
        for (int x = 0; x < img.width/2; x++)
            for (int c = 0; c < img.channels; c++) {
                int oppX = img.width-1-x;
                unsigned char tmp = img.getPixel(x,y,c);
                img.setPixel(x,y,c,img.getPixel(oppX,y,c));
                img.setPixel(oppX,y,c,tmp);
            }
    cout << "Horizontal flip applied.\n";
}

void flipVertical(Image& img) {
    for (int y = 0; y < img.height/2; y++)
        for (int x = 0; x < img.width; x++)
            for (int c = 0; c < img.channels; c++) {
                int oppY = img.height-1-y;
                unsigned char tmp = img.getPixel(x,y,c);
                img.setPixel(x,y,c,img.getPixel(x,oppY,c));
                img.setPixel(x,oppY,c,tmp);
            }
    cout << "Vertical flip applied.\n";
}

void applyRotate(Image& img) {
    cout << "Rotate by (90 / 180 / 270): ";
    string s; getline(cin, s);
    int angle = stoi(s);
    Image rotated;
    if (angle == 90) {
        rotated = Image(img.height,img.width);
        for (int y=0;y<img.height;y++)
            for (int x=0;x<img.width;x++)
                for (int c=0;c<img.channels;c++)
                    rotated.setPixel(img.height-1-y,x,c,img.getPixel(x,y,c));
    }
    else if (angle == 180) {
        rotated = Image(img.width,img.height);
        for (int y=0;y<img.height;y++)
            for (int x=0;x<img.width;x++)
                for (int c=0;c<img.channels;c++)
                    rotated.setPixel(img.width-1-x,img.height-1-y,c,img.getPixel(x,y,c));
    }
    else if (angle == 270) {
        rotated = Image(img.height,img.width);
        for (int y=0;y<img.height;y++)
            for (int x=0;x<img.width;x++)
                for (int c=0;c<img.channels;c++)
                    rotated.setPixel(y,img.width-1-x,c,img.getPixel(x,y,c));
    }
    else { cout<<"Invalid angle\n"; return; }
    img = rotated;
    cout<<"Rotate "<<angle<<" applied.\n";
}

void saveImageFlow(Image& img,string& filename){
    cout<<"Save to same file? (y/n): ";
    string ans; getline(cin,ans);
    string out=filename;
    if(!ans.empty()&&(ans[0]=='n'||ans[0]=='N')){
        cout<<"Enter new filename: ";
        getline(cin,out);
    }
    img.saveImage(out);
    filename=out;
    cout<<"Saved: "<<out<<"\n";
}

int main(){
    Image img; string filename;
    while(true){
        cout<<"Enter image file to load: ";
        getline(cin,filename);
        try{img.loadNewImage(filename);break;}
        catch(exception&e){cout<<"Error: "<<e.what()<<"\n";}
    }
    bool running=true;
    while(running){
        cout<<"\n--- MENU ---\n";
        cout<<"1. Load new image\n";
        cout<<"2. Black & White\n";
        cout<<"3. Invert colors\n";
        cout<<"4. Rotate\n";
        cout<<"5. Flip\n";
        cout<<"6. Grayscale\n";
        cout<<"7. Merge\n";
        cout<<"8. Save\n";
        cout<<"9. Exit\n";
        cout<<"Choice: ";
        string s; getline(cin,s); if(s.empty()) continue;
        int ch=stoi(s);

        if(ch==1){
            cout<<"Save current before load? (y/n): ";
            string a; getline(cin,a);
            if(!a.empty()&&(a[0]=='y'||a[0]=='Y')) saveImageFlow(img,filename);
            cout<<"Enter image file: "; getline(cin,filename);
            try{img.loadNewImage(filename);}catch(exception&e){cout<<"Error: "<<e.what()<<"\n";}
        }
        else if(ch==2) applyBlackAndWhite(img);
        else if(ch==3) applyInvert(img);
        else if(ch==4) applyRotate(img);
        else if(ch==5){
            cout<<"Flip type? (h=horizontal, v=vertical): ";
            string a; getline(cin,a);
            if(!a.empty()&&(a[0]=='h'||a[0]=='H')) flipHorizontal(img);
            else if(!a.empty()&&(a[0]=='v'||a[0]=='V')) flipVertical(img);
            else cout<<"Invalid.\n";
        }
        else if(ch==6) applyGrayscale(img);
        else if(ch==7){
            string file2;
            cout << "Enter second image filename: ";
            getline(cin, file2);
            try {
                Image img2(file2);
                cout << "Resize to biggest size (1) or merge common area (0)? ";
                string opt; getline(cin, opt);
                bool resizeOption = (opt == "1");
                Image merged = mergeImages(img, img2, resizeOption);
                cout << "Save merged image to: (1) First image, (2) Second image? ";
                string choice; getline(cin, choice);
                if (choice == "1") {
                    merged.saveImage(filename);
                    img = merged;
                    cout << "Merged image saved (overwritten): " << filename << "\n";
                }
                else if (choice == "2") {
                    merged.saveImage(file2);
                    img = merged;
                    filename = file2;
                    cout << "Merged image saved (overwritten): " << file2 << "\n";
                }
                else {
                    cout << "Invalid choice! Nothing saved.\n";
                }
            } catch (exception& e) {
                cout << "Error merging: " << e.what() << "\n";
            }
        }
        else if(ch==8) saveImageFlow(img,filename);
        else if(ch==9){
            cout<<"Save before exit? (y/n): ";
            string a; getline(cin,a);
            if(!a.empty()&&(a[0]=='y'||a[0]=='Y')) saveImageFlow(img,filename);
            running=false;
        }
        else cout<<"Invalid choice\n";
    }
}

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
        cout<<"6. Save\n";
        cout<<"7. Exit\n";
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
        else if(ch==6) saveImageFlow(img,filename);
        else if(ch==7){
            cout<<"Save before exit? (y/n): ";
            string a; getline(cin,a);
            if(!a.empty()&&(a[0]=='y'||a[0]=='Y')) saveImageFlow(img,filename);
            running=false;
        }
        else cout<<"Invalid choice\n";
    }
}
            

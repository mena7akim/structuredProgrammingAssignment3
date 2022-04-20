#include <bits/stdc++.h>
#include "bmplib.cpp"
#define speedup  ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
using namespace std;

unsigned char image[SIZE][SIZE];

// Menu and load and save functions
void menu();
void loadImage();
void saveImage();

// Filters
void blackWhite();
void invertImage();
void mergeImage();
void flipImage();
void rotateImage();
void darkenLighten();
void detectImage();
void enlargeImage();
void shrinkImage();
void mirrorImage();
void shuffleImage();
void blurImage();

// Functions needed in filters
int arraySum(unsigned char arr[][SIZE],int n);
void arrayScale(unsigned char a[][SIZE], unsigned char b[][SIZE], int x, int y);
void arrayAssign(unsigned char a[][SIZE],unsigned char b[][SIZE]);
void arrayShrink(unsigned char a[][SIZE],unsigned char b[][SIZE],int n);
void arrangingImages(unsigned char a[][SIZE], unsigned char b[][SIZE], int order, int x, int y);
int blurAlgorithm(unsigned char a[][SIZE], int b, int c, int level);


int main() {
    loadImage();
    menu();
    saveImage();
}


// Menu and load and save functions

void menu(){
    int filter;
    cout << "which filter you would like to apply on the image:\n1-Invert image\n2-Rotate image\n3-Black and white image\n4-Flip image\n5-Merge image\n6-Darken or lighten image\n7-Detect image\n8-Enlarge image\n9-Shrink image\n10-mirror image\n11-Shuffle image\n12-Blur image\n";
    cin >> filter;
    switch (filter) {
        case 1:
            invertImage();
            break;
        case 2:
            rotateImage();
            break;
        case 3:
            blackWhite();
            break;
        case 4:
            flipImage();
            break;
        case 5:
            mergeImage();
            break;
        case 6:
            darkenLighten();
            break;
        case 7:
            detectImage();
            break;
        case 8:
            enlargeImage();
            break;
        case 9:
            shrinkImage();
            break;
        case 10:
            mirrorImage();
            break;
        case 11:
            shuffleImage();
            break;
        case 12:
            blurImage();
            break;
    }
}

void loadImage(){
    char imageName[100];
    cout << "Enter the name of the image" << endl;
    cin.getline(imageName, 100);
    strcat(imageName, ".bmp");
    readGSBMP(imageName, image);
}

void saveImage(){
    char imageName[100];
    cout << "Enter the name of the output image" << endl;
    cin.ignore();
    cin.getline(imageName, 100);
    strcat(imageName, ".bmp");
    writeGSBMP(imageName, image);
}


// Filters

void blackWhite()
{
    int average = arraySum(image, SIZE) / (SIZE * SIZE);
    for (int i = 0; i < SIZE ; i++)
    {
        for(int j = 0; j < SIZE ; j++)
        {
            if(image[i][j] > average)
            {
                image[i][j] = 255;
            }
            else if (image[i][j] <= average)
            {
                image[i][j] = 0;
            }
        }
    }
}

void invertImage()
{
    for (int i = 0; i < SIZE ; i++)
    {
        for(int j = 0; j < SIZE ; j++)
        {
            image[i][j] = 255 - image[i][j];
        }
    }
}

void mergeImage()
{
    char secondImageName[100];
    unsigned char secondImage[SIZE][SIZE];
    unsigned char mergedImage[SIZE][SIZE];
    cout << "Enter the name of the image" << endl;
    cin.ignore();
    cin.getline(secondImageName, 100);
    strcat(secondImageName, ".bmp");
    readGSBMP(secondImageName, secondImage);
    for (int i = 0; i < SIZE ; i++)
    {
        for(int j = 0; j < SIZE ; j++)
        {
            mergedImage[i][j] = (image[i][j] + secondImage[i][j]) / 2;
        }
    }
    arrayAssign(image, mergedImage);
}

void flipImage()
{
    unsigned char flipedImage[SIZE][SIZE];
    int flipType;
    cout << "1-vertical\n2-horizontal\n";
    cin >> flipType;
    switch (flipType)
    {
        case 1:
            for (int i = 0; i < SIZE ; i++)
            {
                for(int j = 0; j < SIZE ; j++)
                {
                    flipedImage[i][j] = image[255-i][j];
                }
            }
            break;
        case 2:
            for (int i = 0; i < SIZE ; i++)
            {
                for(int j = 0; j < SIZE ; j++)
                {
                    flipedImage[i][j] = image[i][255-j];
                }
            }
            break;
    }
    arrayAssign(image, flipedImage);
}

void rotateImage()
{
    int rotateDegree;
    unsigned char rotatedImage[SIZE][SIZE];
    cout <<"1-rotate 90 \n2-rotate 180\n3-rotate 270\n";
    cin >> rotateDegree;
    while(rotateDegree--){
        for (int i = 0; i < SIZE; i++)
        {
            for(int j = 0; j < SIZE; j++)
            {
                rotatedImage[i][j] = image[SIZE - (j + 1)][i];
            }
        }
        arrayAssign(image, rotatedImage);
    }
}

void darkenLighten()
{
    int operation;
    cout <<"1-Darken\n2-Lighten\n";
    cin >> operation;
    switch (operation)
    {
        case 1:
            for (int i = 0; i < SIZE ; i++)
            {
                for(int j = 0; j < SIZE ; j++)
                {
                    image[i][j] = (image[i][j] / 2);
                }
            }
            break;
        case 2:
            for (int i = 0; i < SIZE ; i++)
            {
                for(int j = 0; j < SIZE ; j++)
                {
                    image[i][j] = ((image[i][j] + 255) / 2);
                }
            }
            break;
    }
}

void detectImage(){
    unsigned char detectedImage[SIZE][SIZE];
    int GX,GY;
    for (int i = 0; i < SIZE ; i++){
        for(int j = 0; j < SIZE ; j++){
            GX = (image[i][j-1]*-1)+(image[i][j+1]*1);
            GY = (image[i-1][j]*-1) + (image[i+1][j]*1);
                detectedImage[i][j] = sqrt(GX*GX+GY*GY);
        }
    }
    arrayAssign(image,detectedImage);
    invertImage();
}

void enlargeImage(){
    unsigned char scaledImage[SIZE][SIZE];
    int scaleType;
    cout << "which part you want to scale 1, 2, 3, 4:" << endl;
    cin >> scaleType;
    switch (scaleType) {
        case 1:
            arrayScale(scaledImage,image,0,0);
            break;
        case 2:
            arrayScale(scaledImage,image,0,127);
            break;
        case 3:
            arrayScale(scaledImage,image,127,0);
            break;
        case 4:
            arrayScale(scaledImage,image,127,127);
            break;

    }
    arrayAssign(image, scaledImage);
}

void shrinkImage(){
    int shrink;
    unsigned char scaledImage[SIZE][SIZE];
    cout <<"1- 1/2\n2- 1/3\n3- 1/4\n";
    cin >> shrink;
    for (int i = 0; i < SIZE ; i++) {
        for (int j = 0; j < SIZE; j++) {
            scaledImage[i][j]=255;
        }
    }
    switch (shrink) {
        case 1:
            arrayShrink(scaledImage, image, 2);
            break;
        case 2:
            arrayShrink(scaledImage, image, 3);
            break;
        case 3:
            arrayShrink(scaledImage, image, 4);
            break;

    }
    arrayAssign(image, scaledImage);
}

void mirrorImage(){
    int mirrorType;
    unsigned char mirrorImage[SIZE][SIZE];
    cout << "1-Right\n2-Left\n3-upper\n4-lower\n";
    cin >> mirrorType;
    switch (mirrorType) {
        case 1:
            for (int i = 0; i < SIZE ; i++){
                for(int j = 0; j < SIZE ; j++){
                    mirrorImage[i][j]=image[i][abs(j-255)];
                }
            }
            for (int i = 0; i < SIZE ; i++){
                for(int j = 0; j < 128 ; j++){
                    image[i][j]=mirrorImage[i][j];
                }
            }
            break;
        case 2:
            for (int i = 0; i < SIZE ; i++){
                for(int j = 0; j < SIZE ; j++){
                    mirrorImage[i][j]=image[i][abs(j-255)];
                }
            }
            for (int i = 0; i < SIZE ; i++){
                for(int j = 128; j < SIZE ; j++){
                    image[i][j]=mirrorImage[i][j];
                }
            }
            break;
        case 3:
            for (int i = 0; i < SIZE ; i++){
                for(int j = 0; j < SIZE ; j++){
                    mirrorImage[i][j]=image[abs(i-255)][j];
                }
            }
            for (int i = 128; i < SIZE ; i++){
                for(int j = 0; j < SIZE ; j++){
                    image[i][j]=mirrorImage[i][j];
                }
            }
            break;
        case 4:
            for (int i = 0; i < SIZE ; i++){
                for(int j = 0; j < SIZE ; j++){
                    mirrorImage[i][j]=image[abs(i-255)][j];
                }
            }
            for (int i = 0; i < 128 ; i++){
                for(int j = 0; j < SIZE ; j++){
                    image[i][j]=mirrorImage[i][j];
                }
            }
            break;
    }

}

void shuffleImage(){
    int order,i=0;
    unsigned char refrenceImage[SIZE][SIZE];
    arrayAssign(refrenceImage, image);
    cout << "Enter the order you want to the quarter" << endl;
    while(i<4){
        cin >> order;
        switch (i+1) {
            case 1:
                arrangingImages(image,refrenceImage,order,0,0);
                break;
            case 2:
                arrangingImages(image,refrenceImage,order,0,128);
                break;
            case 3:
                arrangingImages(image,refrenceImage,order,128,0);
                break;
            case 4:
                arrangingImages(image,refrenceImage,order,128,128);
                break;

        }
        i++;
    }

}

void blurImage(){
    int blurLevel;
    unsigned char referenceImage[SIZE][SIZE];
    arrayAssign(referenceImage, image);
    cout << "Blur level:\n1-level 1\n2-level 2\n3-level 3\n";
    cin >> blurLevel;
    switch (blurLevel) {
        case 1:
            for (int i = 0; i < SIZE ; i++){
                for(int j = 0; j < SIZE ; j++){
                    int blur = blurAlgorithm(referenceImage,i,j,5);
                    image[i][j]=blur;
                }
            }
            break;
        case 2:
            for (int i = 0; i < SIZE ; i++){
                for(int j = 0; j < SIZE ; j++){
                    int blur = blurAlgorithm(referenceImage,i,j,7);
                    image[i][j]=blur;
                }
            }
            break;
        case 3:
            for (int i = 0; i < SIZE ; i++){
                for(int j = 0; j < SIZE ; j++){
                    int blur = blurAlgorithm(referenceImage,i,j,9);
                    image[i][j]=blur;
                }
            }
            break;

    }

}


// Functions needed in filters

int arraySum(unsigned char a[][SIZE],int n){
    int sum=0;
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            sum+=a[i][j];
        }
    }
    return sum;
}

void arrayScale(unsigned char a[][SIZE], unsigned char b[][SIZE], int x, int y){
    unsigned char temp[SIZE/2][SIZE/2];
    for (int i=0;i<SIZE/2;i++){
        for(int j=0;j<SIZE/2;j++){
            temp[i][j]=b[i+x][j+y];
        }
    }
    for (int i = 0; i < SIZE ; i++) {
        for (int j = 0; j < SIZE ; j++) {
            a[i][j]=temp[i/2][j/2];
        }
    }
}

void arrayAssign(unsigned char a[][SIZE],unsigned char b[][SIZE]){
    for (int i = 0; i < SIZE ; i++){
        for(int j = 0; j < SIZE ; j++){
            a[i][j] = b[i][j];
        }
    }
}

void arrayShrink(unsigned char a[][SIZE],unsigned char b[][SIZE],int n){
    for (int i = 0; i < SIZE ; i++) {
        for (int j = 0; j < SIZE ; j++) {
            a[i/n][j/n]=b[i][j];
        }
    }
}

void arrangingImages(unsigned char a[][SIZE], unsigned char b[][SIZE], int order, int x, int y){
    switch (order) {
        case 1:
            for (int i = 0; i < SIZE/2; i++){
                for(int j = 0; j < SIZE/2; j++){
                    a[i+x][j+y] = b[i][j];
                }
            }
            break;
        case 2:
            for (int i = 0; i < SIZE/2; i++){
                for(int j = 0; j < SIZE/2; j++){
                    a[i+x][j+y] = b[i][j+128];
                }
            }
            break;
        case 3:
            for (int i = 0; i < SIZE/2; i++){
                for(int j = 0; j < SIZE/2; j++){
                    a[i+x][j+y] = b[i+128][j];
                }
            }
            break;
        case 4:
            for (int i = 0; i < SIZE/2; i++){
                for(int j = 0; j < SIZE/2; j++){
                    a[i+x][j+y] = b[i+128][j+128];
                }
            }
            break;
    }
}

int blurAlgorithm(unsigned char a[][SIZE], int b, int c, int level){
    speedup
    int blur = 0;
    for (int i=b;i<(b+level);i++){
        for(int j=c;j<(c+level);j++){
            blur+=a[i-(level/2)][j-(level/2)];
        }
    }
    return blur/(level*level);
}
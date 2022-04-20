#include <bits/stdc++.h>
#include "bmplib.cpp"
#define speedup  ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
using namespace std;

unsigned char image[SIZE][SIZE][RGB];

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
//void darkenLighten();
//void detectImage();
void enlargeImage();
//void shrinkImage();
void mirrorImage();
//void shuffleImage();
void blurImage();

// Functions needed in filters
int arraySum(unsigned char arr[][SIZE][RGB],int n);
void arrayScale(unsigned char a[][SIZE][RGB], unsigned char b[][SIZE][RGB], int x, int y);
void arrayAssign(unsigned char a[][SIZE][RGB],unsigned char b[][SIZE][RGB]);
//void arrayShrink(unsigned char a[][SIZE],unsigned char b[][SIZE],int n);
//void arrangingImages(unsigned char a[][SIZE][RGB], unsigned char b[][SIZE][RGB], int order, int x, int y);
int blurAlgorithm(unsigned char a[][SIZE][RGB], int b, int c,int k, int i);


int main()
{
    loadImage();
    menu();
    saveImage();
}


// Menu and load and save functions

void menu()
{
    int filter;
    cout << "which filter you would like to apply on the image:\n1-Black and white image\n2-Invert image\n3-Merge image\n4-Flip image\n5-Rotate image\n6-Darken or lighten image\n7-Detect image\n8-Enlarge image\n9-Shrink image\n10-mirror image\n11-Shuffle image\n12-Blur image\n";
    cin >> filter;
    switch (filter)
    {
        case 1:
            blackWhite();
            break;
        case 2:
            invertImage();
            break;
        case 3:
            mergeImage();
            break;
        case 4:
            flipImage();
            break;
        case 5:
            rotateImage();
            break;
//        case 6:
//            darkenLighten();
//            break;
//        case 7:
//            detectImage();
//            break;
        case 8:
            enlargeImage();
            break;
//        case 9:
//            shrinkImage();
//            break;
        case 10:
            mirrorImage();
            break;
//        case 11:
//            shuffleImage();
//            break;
        case 12:
            blurImage();
            break;
    }
}

void loadImage()
{
    char imageName[100];
    cout << "Enter the name of the image" << endl;
    cin.getline(imageName, 100);
    strcat(imageName, ".bmp");
    readRGBBMP(imageName, image);
}

void saveImage()
{
    char imageName[100];
    cout << "Enter the name of the output image" << endl;
    cin.ignore();
    cin.getline(imageName, 100);
    strcat(imageName, ".bmp");
    writeRGBBMP(imageName, image);
}


//Filters
void blackWhite()
{
//    unsigned char newImage[SIZE][SIZE];
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                image[i][j][0] = (image[i][j][0] + image[i][j][1] + image[i][j][2])/3;
                image[i][j][2] = image[i][j][1] = image[i][j][0];
            }
        }
}

void invertImage()
{
    int operation;
    cout << "1-invert RGB\n2-invert black and white";
    cin >> operation;
    switch(operation){
        case 1:
            for (int i = 0; i < SIZE; i++)
            {
                for (int j = 0; j < SIZE; j++)
                {
                    image[i][j][0] = 255 - image[i][j][0];
                    image[i][j][1] = 255 - image[i][j][1];
                    image[i][j][2] = 255 - image[i][j][2];
                }
            }
            break;
        case 2:
            blackWhite();
            for (int i = 0; i < SIZE; i++)
            {
                for (int j = 0; j < SIZE; j++)
                {
                    image[i][j][2] = image[i][j][1] = image[i][j][0] = 255 - image[i][j][0];
                }
            }
            break;
    }
}

void mergeImage()
{

    unsigned char mergedImage[SIZE][SIZE][RGB];
    unsigned char secondImage[SIZE][SIZE][RGB];
    char secondImageName[100];
    cout << "Enter the name of the image" << endl;
    cin.ignore();
    cin.getline(secondImageName, 100);
    strcat(secondImageName, ".bmp");
    readRGBBMP(secondImageName, secondImage);

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for (int k = 0; k < RGB; k++)
            {
                mergedImage[i][j][k] = (image[i][j][k] + secondImage[i][j][k]) / 2;
            }
        }
    }

    arrayAssign(image, mergedImage);
}

void flipImage()
{
    unsigned char flipedImage[SIZE][SIZE][RGB];
    int flipType;
    cout << "1-vertical\n2-horizontal\n";
    cin >> flipType;
    switch (flipType)
    {
        case 1:
            for (int i = 0; i < SIZE; i++)
            {
                for(int j = 0; j < SIZE; j++)
                {
                    for (int k = 0; k < RGB ; k++)
                    {
                        flipedImage[i][j][k] = image[255-i][j][k];
                    }
                }
            }
            break;
        case 2:
            for (int i = 0; i < SIZE ; i++)
            {
                for(int j = 0; j < SIZE ; j++)
                {
                    for (int k = 0; k < RGB ; k++){

                        flipedImage[i][j][k] = image[i][255-j][k];
                    }
                }
            }
            break;
    }
    arrayAssign(image, flipedImage);
}


//Functions used in filters
void arrayAssign(unsigned char a[][SIZE][RGB],unsigned char b[][SIZE][RGB])
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            for (int k = 0; k < RGB; k++)
            {
                a[i][j][k] = b[i][j][k];
            }
        }
    }
}
void rotateImage() 
{
    int rotateDegree;
    unsigned char rotatedImage[SIZE][SIZE][RGB];
    cout << "1-rotate 90 \n2-rotate 180\n3-rotate 270\n";
    cin >> rotateDegree;
    while (rotateDegree--) {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                for (int k = 0; k < RGB; k++) {
                    rotatedImage[i][j][k] = image[SIZE - (j + 1)][i][k];
                }
            }
        }
        arrayAssign(image, rotatedImage);
    }
}
void enlargeImage(){
    unsigned char scaledImage[SIZE][SIZE][RGB];
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
void mirrorImage()
{
    int mirrorType;
    unsigned char mirrorImage[SIZE][SIZE][RGB];
    cout << "1-Right\n2-Left\n3-upper\n4-lower\n";
    cin >> mirrorType;
    switch (mirrorType) {
    case 1:
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < RGB; k++) {
                    mirrorImage[i][j][k] = image[i][abs(j - 255)][k];

                }
            }
        }
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < 128; j++) {
                    for (int k = 0; k < RGB; k++) {
                        image[i][j][k] = mirrorImage[i][j][k];

                    }
                }
            }
            break;
    case 2:
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < RGB; k++) {
                    mirrorImage[i][j][k] = image[i][abs(j - 255)][k];
                }
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 128; j < SIZE; j++) {
                for (int k = 0; k < RGB; k++) {
                    image[i][j][k] = mirrorImage[i][j][k];
                }
            }
        }

            break;
    case 3:
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < RGB; k++) {
                    mirrorImage[i][j][k] = image[abs(i - 255)][j][k];
                }
            }
        }
        for (int i = 128; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < RGB; k++) {
                    image[i][j][k] = mirrorImage[i][j][k];
                }
            }
        }
        break;
    case 4:
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < RGB; k++) {
                    mirrorImage[i][j][k] = image[abs(i - 255)][j][k];
                }
            }
        }
        for (int i = 0; i < 128; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < RGB; k++) {
                    image[i][j][k] = mirrorImage[i][j][k];
                }
            }
        }
        break;
        }

    }
void blurImage(){
    int blurLevel;
    unsigned char referenceImage[SIZE][SIZE][RGB];
    arrayAssign(referenceImage, image);
    cin >> blurLevel;
        for (int i = 0; i < SIZE ; i++) {
            for (int j = 0; j < SIZE; j++) {
                for (int k = 0; k < RGB; k++) {
                    int blur = blurAlgorithm(referenceImage, i, j,k,5);
                    image[i][j][k] = blur;
                }
            }
        }
}
void arrayScale(unsigned char a[][SIZE][RGB], unsigned char b[][SIZE][RGB], int x, int y){
    unsigned char temp[SIZE/2][SIZE/2][RGB];
    for (int i=0;i<SIZE/2;i++) {
        for (int j = 0; j < SIZE / 2; j++) {
            for (int k = 0; k < RGB; k++) {
                temp[i][j][k] = b[i + x][j + y][k];
            }
        }
    }
    for (int i = 0; i < SIZE ; i++) {
        for (int j = 0; j < SIZE ; j++) {
            for (int k = 0; k < RGB; k++){
            a[i][j][k]=temp[i/2][j/2][k];
        }
    }
}
}
int blurAlgorithm(unsigned char a[][SIZE][RGB], int b, int c,int k, int level){
    speedup
    int blur = 0;
    for (int i = b; i < (b + level); i++) {
        for (int j = c; j < (c + level); j++) {
                blur += a[i - (level / 2)][j - (level / 2)][k];
            }
        }

    return blur/(level*level);
}
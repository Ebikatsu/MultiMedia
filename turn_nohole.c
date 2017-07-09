#include <stdio.h>
#include "image.h"
#include <math.h>

void turn(ImageData *img, ImageData *outimg, int theta);

int main(){
    
    char *fname = "./SAMPLE.bmp";
    char *wname = "./turn_nohole.bmp";
    int theta;
    
    ImageData *img;
    ImageData *outimg;

    int size;

    readBMPfile(fname,&img);
    size = (int)(sqrt(img->width*img->width + img->height*img->height));
    outimg = createImage(size,size,img->depth);
    
    printf("read[%s]\n",fname);
    
    printf("回転する角度を入力してください>>"); scanf("%d", &theta);

    turn(img,outimg, theta);
    
    writeBMPfile(wname,outimg);
    
    printf("write[%s]\n",wname);
    disposeImage(img);
}

void turn(ImageData *img,ImageData *outimg, int theta){
    int i, j, x, y;
    int a, b;
    int x1_center = (int)(img->width/2), y1_center = (int)(img->height/2);
    int x2_center = (int)(outimg->width/2), y2_center = (int)(outimg->height/2);
    int x_move = x2_center-x1_center, y_move = y2_center-y1_center;
    double rad = ((double)theta/180)*M_PI;

    Pixel pix;
    Pixel black;
    black.r = 0; black.g = 0; black.b = 0;
    
    ImageData *tempimg;
    tempimg = createImage(outimg->width, outimg->height, outimg->depth);
    for(i=0; i<img->width; i++){
        for(j=0; j<img->height; j++){
            a = getPixel(img, i, j, &pix);
            b = setPixel(tempimg, i+x_move, j+y_move, &pix);
        }
    }

    for(i=0;i<outimg->height;i++){
        for(j=0;j<outimg->width;j++){
            x = (int)((j-x2_center)*cos(rad)-(i-y2_center)*sin(rad)+x1_center);
            y = (int)((j-x2_center)*sin(rad)+(i-y2_center)*cos(rad)+y1_center);
            if(x>=0 && x<img->width && y>=0 && y<img->height){
                a = getPixel(img, x, y, &pix);
                if (a == -1){
                    printf("getError(%d,%d)¥n",j,i);
                }
                b = setPixel(outimg,j,i,&pix);
                if (b == -1){
                    printf("setError(%d,%d)¥n",x,y);
                }
            } else {
                b = setPixel(outimg,j,i,&black);
                if (b == -1){
                    printf("setError(%d,%d)¥n",x,y);
                }
            }
        }
    }
}

#include <stdio.h>
#include "image.h"
#include <math.h>

void turn(ImageData *img, ImageData *outimg, int theta);

int main(){
    
    char *fname = "./SAMPLE.bmp";
    char *wname = "./turn.bmp";
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
    double rad = -1*((double)theta/180)*M_PI;

    Pixel pix;
    Pixel black;
    black.r = 0; black.g = 0; black.b = 0;
    
    for(i=0;i<img->height;i++){
        for(j=0;j<img->width;j++){
            a = getPixel(img, j, i, &pix);
            if (a == -1){
                printf("getError(%d,%d)¥n",j,i);
            }
//             printf("%f\n", (double)cos(30));
            x = (int)((j-x1_center)*cos(rad)-(i-y1_center)*sin(rad)+x2_center);
            y = (int)((j-x1_center)*sin(rad)+(i-y1_center)*cos(rad)+y2_center);
//             printf("%d %d\n", x,y);
            if(x>=0 && x<outimg->width && y>=0 && y<outimg->height){
                b = setPixel(outimg,x,y,&pix);
            } else {
                b = setPixel(outimg,x,y,&black);
            }
            if (b == -1){
                printf("setError(%d,%d)¥n",x,y);
            }
        }
    }
}

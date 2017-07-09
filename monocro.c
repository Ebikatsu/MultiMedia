#include <stdio.h>
#include "image.h"

void monocro(ImageData *img, ImageData *outimg);

int main(){
    
    char *fname = "./SAMPLE.bmp";
    char *wname = "./monocro.bmp";
    
    // int by = 3;
    
    ImageData *img;
    ImageData *outimg;
    
    readBMPfile(fname,&img);
    
    outimg = createImage(img->width,img->height,img->depth);
    
    printf("read[%s]\n",fname);
    
    monocro(img,outimg);
    
    writeBMPfile(wname,outimg);
    
    printf("write[%s]\n",wname);
    disposeImage(img);
}

void monocro(ImageData *img,ImageData *outimg){
    int x,y;
    int a,b;
    int set,get;
    Pixel pix;
    int mono_color;
    double p_r = 0.298912, p_g = 0.586611, p_b = 0.114478;


    for(x=0;x<img->width;x++){
        for(y=0;y<img->height;y++){
            a = getPixel(img,x,y,&pix);
            if (a == -1){
                printf("getError(%d,%d)¥n",x,y);
            }
            mono_color = (int)(p_r * pix.r + p_g * pix.g + p_b * pix.b);
            pix.r = mono_color;
            pix.g = mono_color;
            pix.b = mono_color;
            printf("%d %d %d\n", pix.r, pix.g, pix.b);
            b = setPixel(outimg,x,y,&pix);
            if (b == -1){
                printf("setError(%d,%d)¥n",x,y);
            }
        }
    }
}

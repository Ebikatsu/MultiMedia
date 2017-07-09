#include <stdio.h>
#include "image.h"

void anime_like(ImageData *img, ImageData *outimg);

int main(){
    
    char *fname = "./SAMPLE.bmp";
    char *wname = "./anime.bmp";
    
    // int by = 3;
    
    ImageData *img;
    ImageData *outimg;
    
    readBMPfile(fname,&img);
    
    outimg = createImage(img->width,img->height,img->depth);
    
    printf("read[%s]\n",fname);
    
    anime_like(img,outimg);
    
    writeBMPfile(wname,outimg);
    
    printf("write[%s]\n",wname);
    disposeImage(img);
}

void anime_like(ImageData *img,ImageData *outimg){
    int x,y;
    int a,b;
    int set,get;
    Pixel pix;
    int color_num = 64; // 色数を決める(色数 = (256/color_num)^3)

    for(x=0;x<img->width;x++){
        for(y=0;y<img->height;y++){
            a = getPixel(img,x,y,&pix);
            if (a == -1){
                printf("getError(%d,%d)¥n",x,y);
            }
            pix.r = pix.r/color_num * color_num;
            pix.g = pix.g/color_num * color_num;
            pix.b = pix.b/color_num * color_num;
            printf("%d %d %d\n", pix.r, pix.g, pix.b);
            b = setPixel(outimg,x,y,&pix);
            if (b == -1){
                printf("setError(%d,%d)¥n",x,y);
            }
        }
    }
}

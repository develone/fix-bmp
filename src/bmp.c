#include <stdio.h>
#include <stdlib.h>
// Source - https://stackoverflow.com/q/11129138
// Posted by Sanich, modified by community. See post 'Timeline' for change history
// Retrieved 2026-05-18, License - CC BY-SA 3.0

#pragma pack(push,1)
/* Windows 3.x bitmap file header */
typedef struct {
    char         filetype[2];   /* magic - always 'B' 'M' */
    unsigned int filesize;
    short        reserved1;
    short        reserved2;
    unsigned int dataoffset;    /* offset in bytes to actual bitmap data */
} file_header;

/* Windows 3.x bitmap full header, including file header */
typedef struct {
    file_header  fileheader;
    unsigned int headersize;
    int          width;
    int          height;
    short        planes;
    short        bitsperpixel;  /* we only support the value 24 here */
    unsigned int compression;   /* we do not support compression */
    unsigned int bitmapsize;
    int          horizontalres;
    int          verticalres;
    unsigned int numcolors;
    unsigned int importantcolors;
} bitmap_header;
#pragma pack(pop)

int main(int argc, char *argv[]) {
    argv[1];
    argv[2];
    printf("input %s output %s\n",argv[1],argv[2]);
    //variable dec:
    FILE *fp,*out;
    bitmap_header* hp;
    int n,loop;
    char *data;

    //Open input file:
    fp = fopen(argv[1], "rb");
    if(fp == NULL){
        //cleanup
    }


    //Read the input file headers:
    hp=(bitmap_header*)malloc(sizeof(bitmap_header));
    if(hp == NULL)
        return 3;

    n=fread(hp, sizeof(bitmap_header), 1, fp);
    printf("n %d \n",n);
    printf("sizeof(bitmap_header) %d \n",sizeof(bitmap_header));
     
    if(n<1){
        //cleanup
    }

    //Read the data of the image:
    data = (char*)malloc(sizeof(char)*hp->bitmapsize);
    //data = (char*)malloc(sizeof(hp->bitmapsize);
    printf("data %n \n",data);
    if(data == NULL){
        //cleanup
    }

    fseek(fp,sizeof(char)*hp->fileheader.dataoffset,SEEK_SET);
    n=fread(data,sizeof(char),hp->bitmapsize, fp);
    printf("number of data points %d \n",n);
    for(loop=0;loop<8;loop++) {
    	printf("loop %d data %x \n",loop,*data);
	data++;
    }
    printf("1st value %d \n",*data);
    printf("hp->bitmapsize %d \n",n);
    printf("width %d height %d \n", hp->width, hp->height);
    printf("hp->planes %d \n",hp->planes);
    printf("hp->bitsperpixel %d \n",hp->bitsperpixel);
    printf("hp->bitmapsize %d \n",hp->bitmapsize);
    
    
    printf("hp->horizontalres %d \n",hp->horizontalres);
    printf("hp->verticalres %d \n",hp->verticalres);
    printf("hp->numcolors %d \n",hp->numcolors); 
    printf("hp->importantcolors %d \n",hp->importantcolors);
    if(n<1){ 
        //cleanup
    }
        //Open output file:
    out = fopen(argv[2], "wb");
    if(out==NULL){
        //cleanup
    }

    n=fwrite(hp,sizeof(char),sizeof(bitmap_header),out);
    if(n<1){
        //cleanup
    }
    fseek(out,sizeof(char)*hp->fileheader.dataoffset,SEEK_SET);
    n=fwrite(data,sizeof(char),hp->bitmapsize,out);
    if(n<1){
        //cleanup
    }

    fclose(fp);
    fclose(out);
    free(hp);
    free(data);
    return 0;
}

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "image.h"

float get_pixel(image im, int x, int y, int c)
{
    //Checking boundry conditions
    if(x<0)x=0;
    if(y<0)y=0;
    if(x>im.w)x=im.w-1;
    if(y>im.h)y=im.h-1;
    // TODO Fill this in
    int pixel_location=x+y*im.w+c*im.w*im.h;

    return im.data[pixel_location];
}

void set_pixel(image im, int x, int y, int c, float v)
{
    if(x<0 || y<0 || x>im.w || y>im.h)
    {
        return;
    }else{
    // TODO Fill this in
    int pixel_location=x+y*im.w+c*im.w*im.h;
    float *pixel_value=&im.data[pixel_location];
    *pixel_value=v;
    }
}

image copy_image(image im)
{
    image copy = make_image(im.w, im.h, im.c);
    // TODO Fill this in
    //Using get_pixel and set_pixel
    /*for(int c=0;c<im.c;c++){
        for(int y=0;y<im.h;y++){
            for(int x=0;x<im.w;x++){
                float v=get_pixel(im,x,y,c);
                set_pixel(copy,x,y,c,v);
            }
        }
    }*/

    //Using memcpy
    memcpy(&copy,&im,sizeof(im));

    return copy;
}

image rgb_to_grayscale(image im)
{
    assert(im.c == 3);
    int i=1;
    image gray = make_image(im.w,im.h,i);
    // TODO Fill this in
    //Noob's(Brute Force) Approach
    /*for(int y=0;y<im.h;y++){
        for(int x=0;x<im.w;x++){
                float v=(0.299*get_pixel(im,x,y,0)+0.587*get_pixel(im,x,y,1)+0.114*get_pixel(im,x,y,2));
                set_pixel(gray,x,y,(i-1),v);
            }
        }*/


        //Creating a pointer to struct(gray image,image)
        image *ptr_gray, *ptr_im;
        ptr_gray=&gray;
        //float *gray_data=ptr_gray->data;
        float (*gray_data_matrix)[im.w][im.h]=ptr_gray->data;
        //Given Image
        ptr_im=&im;
        //float * im_data=ptr_im->data;
        float (*im_data_matrix)[im.w][im.h]=ptr_im->data;

        //Define the data member of gray to be that of im:
        ptr_gray->h=ptr_im->h;
        ptr_gray->w=ptr_im->w;

        float value;
        for(int c=0;c<im.c;c++){
            if(c==0){value=0.299;}
            else if(c==1){value=0.587;}
            else if(c==2){value=0.144;}
            for(int width=0;width<gray.w;width++){
                for(int height=0;height<gray.h;height++){
                        (*gray_data_matrix)[width][height]+=(*(*(*(im_data_matrix+c)+width)+height))*value;
            }
        }





        }

    return gray;
}

void shift_image(image im, int c, float v)
{
    // TODO Fill this in

    for(int y=0;y<im.h;y++){
        for(int x=0;x<im.w;x++){
                float shift=get_pixel(im,x,y,c)+v;
                if(shift>1){
                    shift=1;
                }else if(shift<0){
                    shift=0;
                }
                set_pixel(im,x,y,c,shift);

        }
    }

}

void clamp_image(image im)
{
    // TODO Fill this in
    /*
    for(int c=0;c<im.c;c++){
    for(int y=0;y<im.h;y++){
        for(int x=0;x<im.w;x++){
            //float pix
        }
    }
    }
    */
}


// These might be handy
float three_way_max(float a, float b, float c)
{
    return (a > b) ? ( (a > c) ? a : c) : ( (b > c) ? b : c) ;
}

float three_way_min(float a, float b, float c)
{
    return (a < b) ? ( (a < c) ? a : c) : ( (b < c) ? b : c) ;
}

void rgb_to_hsv(image im)
{
    // TODO Fill this in
    float R,G,B,V,m,C,S,H_dash,H;
        for(int y=0;y<im.h;y++){
            for(int x=0;x<im.w;x++){
                R=get_pixel(im,x,y,0);
                G=get_pixel(im,x,y,1);
                B=get_pixel(im,x,y,2);
                V=three_way_max(R,G,B);
                m=three_way_min(R,G,B);
                C=V-m;
                if(V==0){
                    S=0;
                }else{
                    S=C/V;
                }
                if(C==0){
                    H=0;
                }else{
                if(V==R){
                    H_dash=(G-B)/C;
                }else if(V==G){
                H_dash=((B-R)/C)+2;
                }else if(V==B){
                H_dash=((R-G)/C)+4;
                }
                }

                if(H_dash<0){
                    H = (H_dash/6)+1;
                }else{
                    H=(H_dash/6);
                }

            set_pixel(im,x,y,0,H);
            set_pixel(im,x,y,1,S);
            set_pixel(im,x,y,2,V);
            }

    }
}
void scale_image(image im,int c,float v){
for(int y=0;y<im.h;y++){
        for(int x=0;x<im.w;x++){
                float scale=get_pixel(im,x,y,c)*v;
                if(scale>1){
                    scale=1;
                }else if(scale<0){
                    scale=0;
                }
                set_pixel(im,x,y,c,scale);

        }
    }

}
void hsv_to_rgb(image im)
{
    // TODO Fill this in
    //X is the intermediate value for the second largest component of the color
    for(int y=0;y<im.h;y++){
        for(int x=0;x<im.w;x++){
             float R1=0,B1=0,G1=0,R=0,G=0,B=0;

            float H=get_pixel(im,x,y,0)*360;
            float S=get_pixel(im,x,y,1);
            float V=get_pixel(im,x,y,2);


                float C=S*V;
                float H_dash=H/60;
                float X=C*(1-abs((fmod(H_dash,2)-1)));

                if(H_dash<=0){
                    R1=0;G1=0;B1=0;
                }
                else if(H_dash>0 && H_dash<=1){
                    R1=C;
                    G1=X;
                    B1=0;
                }

                else if(H_dash>1 && H_dash<=2){
                    R1=X;
                    G1=C;
                    B1=0;
                }


                else if(H_dash>2 && H_dash<=3){
                    R1=0;
                    G1=C;
                    B1=X;
                }

                else if(H_dash>3 && H_dash<=4){
                    R1=0;
                    G1=X;
                    B1=C;
                }

                else if(H_dash>4 && H_dash<=5){
                    R1=X;
                    G1=0;
                    B1=C;
                }
                else if(H_dash>5 && H_dash<=6){
                    R1=C;
                    G1=0;
                    B1=C;
                }

                float m=V-C;
                R=R1+m;
                G=G1+m;
                B=B1+m;


            set_pixel(im,x,y,0,R);
            set_pixel(im,x,y,1,G);
            set_pixel(im,x,y,2,B);

        }
    }
}
/*
//Jalotra's code
void rgb_to_hsv(image im)
{
    // Started working on changing rgb to hsv
    // WE HAVE THREE VARIABLES HUE,SATURATION AND VALUE

    // FOR VALUE
    // V = max(r,g,b)

    // FOR SATURATION We see how far are the r,g,b are situation
    // m = min(r,g,b)
    // C = V - m
    // S = C/V          // except for the black pixel or (r,g,b) ={0,0,0}

    // FOR CALCULATING HUE
    // we ARE given the best descriptiin in readme.md
    // PLease have a look


    // CODE STARTS
    // wE START OFF WITH GETTING PIXELS FROM THE get_pixel method and
    // calculate the differnt values from the above formulas that are
    //given

    // FINALLY REmember to replace R channel with H, the G channel with S, B channel with V


    for(int column = 0 ; column < im.w ; column++)
    {
        for(int row = 0 ; row < im.h ; row ++)
        {
            // Get pixel
            float r = get_pixel(im, column, row, 0);
            float g = get_pixel(im, column, row, 1);
            float b = get_pixel(im, column, row, 2);

            // Calculate value, saturation and hue
            float value = calculate_value(r,g,b);
            float hue = calculate_hue(r,g,b);
            float saturation = calculate_saturation(r,g,b);


            // CHnage values respectively
            r = hue;
            g = saturation;
            b = value;

            // FInally set_pixel
            // definition set_pixel(image im, int x, int y, int c, float v)
            set_pixel(im, column, row, 0, r);
            set_pixel(im, column, row, 1, g);
            set_pixel(im, column, row, 2, b);
        }
    }




}

float calculate_value(float a, float b, float c)
{
    return three_way_max(a,b,c);
}

float calculate_saturation(float a, float b , float c)
{
    float S;
    if(a != 0 && b != 0 && c != 0)
    {
        S = (three_way_max(a,b,c) - three_way_min(a,b,c))/three_way_max(a,b,c);
    }
    else
    {
        S = 0;
    }

return S;
}

float calculate_hue(float r, float g, float b)
{
    float V = three_way_max(r, g, b);
    float H ;
    float C = three_way_max(r, g, b) - three_way_min(r, g, b);

    if(V == r) H =  (g-b)/C;
    else if(V == g) H = ((b-r)/C) + 2;
    else if(V == b) H = ((r-g)/C) + 4;
    else if (C == 0) H = 0;

    if(H < 0) H = H/6 + 1;
    else H = H/6;


return H;
}

// void see_the_value_image(im)
// {
//     // the value image is analogous to blue channel in the RGB image
//     // SO I have to start from
// }

void hsv_to_rgb(image im)
{
    // TODO Fill this in
    // Lets do this
    // ALgorithmic steps to take

    // I have (H,S,V) values and I want (R,G,B) values
    // My  H, S ,V lies bw (0,1]
    // Multily the H by 360 as the algorithm is given taken in consideration that
    // H represents angle

    // 1. fIND Chroma = V*S
    // 2. Define H' =  H/60;
    // 3. Find X = C*(  1-abs(H'mod2 - 1))

    // And R,G,B == One pair among 6 values
    // See this wiki page https://en.wikipedia.org/wiki/HSL_and_HSV#HSV_to_RGB
    // FInally add m = V - C to R,G,B produced


    // CODE starts
    for(int column = 0 ; column < im.w ; column++)
    {
        for(int row = 0 ; row < im.h ; row ++)
        {
            // varibles declaration
            float r = 0,b = 0,g = 0;
            // Get hsv values
            float hue = get_pixel(im, column, row, 0) * 360 ;
            float saturation = get_pixel(im, column, row, 1);
            float value = get_pixel(im, column, row, 2);

            // Calculate value, saturation and hue
            float C = value*saturation;
            hue = hue/60;
            float X = C*(1 - abs((int)hue % 2 -1 ));

            if(0<=hue<=1)
            {
                r = C;
                g = X;
            }
            else if(1<hue<=2)
            {
                r = X;
                g = C;

            }
            else if(2<hue<=3)
            {
                g = C;
                b = X;
            }
            else if(3<hue<=4)
            {
                g = X;
                b = C;
            }
            else if(4<hue<=5)
            {
                r = X;
                b = C;
            }
            else if(5<hue<=6)
            {
                r = C;
                b = C;
            }
            else if(hue < 0)
            {
                r = 0;
                g = 0;
                b = 0;
            }

            // Finally claculate m and add to all rbgs
            float m = value - C;
            r += m;
            b += m;
            g += m;


            // FInally set_pixel
            // definition set_pixel(image im, int x, int y, int c, float v)
            set_pixel(im, column, row, 0, r);
            set_pixel(im, column, row, 1, g);
            set_pixel(im, column, row, 2, b);
        }
    }


}

*/


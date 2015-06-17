#include <stdio.h>
#include <fstream>
#include "Q3EC2.h"
#include <cmath>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <sstream>
#define MAX_ITER 255
#define X_RES 640
#define Y_RES 480

using namespace std;

void array2D::setValue(int x, int y, float val)
{
    xtable[x][y] = val;
}

float array2D::getValue(int x, int y)
{
    return xtable[x][y];
}

void array2D::getSize(int& x, int& y)
{
    x = xRes;
    y = yRes;
};

array2D::array2D(int x, int y)
{
    xRes = x;
    yRes = y;
    xtable = new float*[yRes]; // NOTE how we do this!

    for(int i=0; i < yRes; i++)
    {
        xtable[i] = new float[xRes]; // each row points to xRes elements ("columns")
    }

    for(int i=0; i < yRes; i++)
    {
        for(int j=0; j < xRes; j++)
        {
            xtable[i][j]=45; // store 45 for pixel data, "for now"
        }
    }
}

array2D::~array2D()
{
    for(int i=0; i < yRes; i++)
    {
        delete[] xtable[i] ; // each row points to xRes elements ("columns")
    }
    delete[] xtable;
}


PGMImage::PGMImage(int x, int y, char* myfilename)
{
    xRes = x;
    yRes = y;
    strcpy(filename , myfilename);
    xtable = new float*[yRes]; // NOTE how we do this!

    for(int i=0; i < yRes; i++)
    {
        xtable[i] = new float[xRes]; // each row points to xRes elements ("columns")
    }

    for(int i=0; i < yRes; i++)
    {
        for(int j=0; j < xRes; j++)
        {
            xtable[i][j]=0; // store 45 for pixel data, "for now"
        }
    }
}

void PGMImage::writeFile()
{
    ofstream outFile(filename);

    if(!outFile)
    {
        cerr << "Error opening file.." << endl;
    }//end of file processing
    outFile <<"P2"<<endl;
    outFile <<xRes<< " " << yRes << endl;
    outFile << "255" << endl;

    for (int i = 0 ; i <yRes; i++)
    {
        for (int j = 0; j <xRes; j++)
        {
            outFile << xtable[i][j] << " ";
        }
        outFile << endl;
    }
    outFile.close();
}

void PGMImage::setFilename(const char* myfilename)
{
    strcpy(filename,myfilename);
}
void PGMImage::getFilename(char* myfilename)
{
    strcpy(myfilename,filename);
}


ComplexNumber::ComplexNumber(double i, double j)
{
    real = i;
    imag = j;
}

ComplexNumber ComplexNumber::add(ComplexNumber c2)
{
    return ComplexNumber(real + c2.getReal(), imag + c2.getImag());
}

ComplexNumber ComplexNumber::squared()
{
    return ComplexNumber(real*real - imag*imag,real*imag * 2.0);
}
double ComplexNumber::abs()
{
    return sqrt(real*real + imag*imag);
}
void ComplexNumber::prt()
{
    cout << real << "+" << imag <<"i"<<endl;
}
double ComplexNumber::getReal()
{
    return real;
}
double ComplexNumber::getImag()
{
    return imag;
}

void ComplexNumber::setReal(double val)
{
    real = val;
}

void ComplexNumber::setImag(double val)
{
    imag = val;
}



ComplexNumber ComplexNumber::operator+(ComplexNumber x)
{
    return ComplexNumber((double)real + x.getReal(),(double)imag + x.getImag());
}



////main



////main

void genMandelbrot()
{
    //genMandelBrat
    PGMImage mynewimage(640,480,"fractal_single.pgm");

    double cxmin=-2, cymin=-1,cxmax=1,  cymax=1;
    do{
    cout << "Input you cxmin, cymin, cxmax, cymax (separated by spaces)."<<endl;
    cout << "cxmin and cymin must be lower than cxmax and cymax:" << endl;
    cin >> cxmin >> cymin >> cxmax >> cymax;
    }while(cxmin >= cxmax || cymin >=cymax );

    cout << "Begin:"<<endl;

    for(int i = 0; i<480; i++)
    {
        for(int j = 0; j<640; j++)
        {
            ComplexNumber c(0,0);
            c.setReal(cxmin + (double)j/(X_RES-1.0)*(cxmax-cxmin)); //[maps x to cxmin..cxmax]
            c.setImag(cymin + (double)i/(Y_RES-1.0)*(cymax-cymin));// [maps y to cymin..cymax]
            ComplexNumber z(0,0);
            int k = 0;
            while(k < MAX_ITER && z.abs() < 2.0)
            {
                z = z.squared()+(c);
                k++;
            }
            //cout << k <<endl;
            if(k<MAX_ITER)
            {
                mynewimage.setValue(i,j,k);
            }
            else
            {
                mynewimage.setValue(i,j,0);
            }

        }
        //cout << "finished::line " << i+1 << "." <<endl;
    }
    mynewimage.writeFile();
}

void showComplexs()
{
    ComplexNumber c1(3,4), c2(-2,1);
    ComplexNumber c3 = c1.squared(), c4 = c3.squared().add(c2);
    c1.prt();
    c2.prt();
    c3.prt();
    c4.prt();
    //cout<< c4.abs()<<endl;
}

void genMandelbrotZoom(int ith)
{
    //genMandelBrat
    PGMImage * mynewimage = new PGMImage(640,480,"fractual.pgm");

    double cxmin=-2, cymin=-1,cxmax=1,  cymax=1;
    double xcen = -0.5, ycen = 0, scale = 1;
    cout << "This is the " << ith <<"th image"<<endl;
    cout << "Input the center:x, y, and Zoom-in scale (separated by spaces)."<<endl;
    cin >> xcen >> ycen >> scale;
    cxmin = xcen - 1.5 / scale;
    cxmax = xcen + 1.5 / scale;
    cymin = ycen - 1 / scale;
    cymax = ycen + 1 / scale;
    cout << "Begin:"<<endl;

    for(int i = 0; i<480; i++)
    {
        for(int j = 0; j<640; j++)
        {
            ComplexNumber c(0,0);
            c.setReal(cxmin + (double)j/(X_RES-1.0)*(cxmax-cxmin)); //[maps x to cxmin..cxmax]
            c.setImag(cymin + (double)i/(Y_RES-1.0)*(cymax-cymin));// [maps y to cymin..cymax]
            ComplexNumber z(0,0);
            int k = 0;
            while(k < MAX_ITER && z.abs() < 2.0)
            {
                z = z.squared()+(c);
                k++;
            }
            //cout << k <<endl;
            if(k<MAX_ITER)
            {
                mynewimage->setValue(i,j,k);
            }
            else
            {
                mynewimage->setValue(i,j,0);
            }

        }
        //cout << "finished::line " << i+1 << "." <<endl;
    }

    stringstream strtemp;
    strtemp <<"fractal_" << ith << ".pgm";
    mynewimage->setFilename(strtemp.str().c_str());
    mynewimage->writeFile();
    delete mynewimage;
}


void genMultiple()
{
    int num = 1;
    cout << "Input the number of image to generate:" <<endl;
    cin >> num;
    for (int i = 0;i< num;i++)
        genMandelbrotZoom(i+1);
}




int main()
{
    int opt = 1;
    cout <<"Please input your method:" <<endl;
    cout << "1 for single, 2 for multiple, other number for ending the program."<<endl;
    cout << "for more info please see ReadMe_Q3EC1.txt" <<endl;
    cin >> opt;

    if (opt == 1)
        genMandelbrot();
    else if (opt == 2)
        genMultiple();
    else
        return 0;
    return 0;
}



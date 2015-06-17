#include <stdio.h>
#include <fstream>
#include "Q3.h"
#include <cmath>
#include <iostream>
#include <string.h>
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

void PGMImage::setFilename(char* myfilename)
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

void genMandelbrot()
{
    //genMandelBrat
    PGMImage * mynewimage = new PGMImage(640,480,"fractual.pgm");

    double cxmin=-2, cymin=-1,cxmax=1,  cymax=1;

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
    mynewimage->writeFile();
    delete mynewimage;
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

void checkV()
{
    ComplexNumber c1(0,0), c2(3,4), c3(0,0);
    c1 = c1.squared().add(c2);
    cout << c1.getReal()<<":"<<c1.getImag()<<endl;
    cout<<c1.abs()<<endl;
}

int main()
{
    //checkV();
    genMandelbrot();
    return 0;
}


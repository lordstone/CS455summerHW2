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

void genMandelbrotZoom(int ith, double xcen, double ycen, double scale)
{
    //genMandelBrat
    PGMImage * mynewimage = new PGMImage(640,480,"fractual.pgm");

    double cxmin=-2, cymin=-1,cxmax=1,  cymax=1;

    cxmin = xcen - 1.5 / scale;
    cxmax = xcen + 1.5 / scale;
    cymin = ycen - 1 / scale;
    cymax = ycen + 1 / scale;

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



void genCenter(int choice, double& x, double& y){
    switch(choice){
    case 1:
        x = -0.75;
        y = 0.1;
        break;
    case 2:
        x = 0.275;
        y = 0;
        break;
    case 3:
        x = -0.088;
        y = 0.654;
        break;
    case 4:
        x = -0.274;
        y = 0.482;
        break;
    case 5:
        x = -1.36;
        y = 0.005;
        break;
    case 6:
        x = -1.108;
        y = 0.230;
        break;
    case 7:
        x = -0.1002;
        y = 0.8363;
        break;
    case 8:
        x = -1.75;
        y = 0;
        break;
    case 9:
        x = -0.1592;
        y = -1.0317;
        break;
    default:
        cout << "Input the center:x, y (separated by spaces)."<<endl;
        cin >> x >> y;
        break;
    }
}

void genSeriesF(){
    double xcen, ycen;
    double startScaling = 1, zoomInterval = 10, iterNum = 1;
    int choice;
    cout << "In this program, you can do Mandelbrot Fractals" <<endl;
    cout << "You can either choose from our built-in parameters about the center." << endl;
    cout << "or self define your own center." <<endl;
    cout << "We have the following built-in parameters:"<<endl;
    cout << "1: Seahorse Valley (-0.75, 0.1)." <<endl;
    cout << "2: Elephant Valley (0.275, 0)." <<endl;
    cout << "3: Triple Spiral Valley (-0.088, 0.654)." <<endl;
    cout << "4: Quad-Spiral Valley (-0.274, 0.482)." <<endl;
    cout << "5: Scepter Valley (-1.36, 0.005)." <<endl;
    cout << "6: Scepter Variant (-1.108, 0.230)." <<endl;
    cout << "7: Double Scepter Valley (-0.1002, 0.8383)." <<endl;
    cout << "8: Mini Mandelbrot (-1.75, 0)." <<endl;
    cout << "9: Another Mandelbrot (-0.1592, -1.0317)." <<endl;
    cout << "0: Self-Define Center(!)" << endl;
    cout << "(!): Self-Defined center might give you all black graphs" << endl;

    cout << "Now input your choice:"<<endl;
    cin >> choice;
    genCenter(choice,xcen,ycen);
    cout << "Now enter the start scaling point, zooming interval, and iteration number (>=1)"<<endl;
    cout << "Separated by spaces:"<<endl;
    cin >> startScaling >> zoomInterval >> iterNum;
    cout << "Now generating files (Could be long)..."<<endl;
    int j = 1;
    for(double i = startScaling;i<=startScaling + (iterNum-1) * zoomInterval;i=i+zoomInterval){
        cout <<"Now processing the " << j <<"th graph"<<endl;
        genMandelbrotZoom(j, xcen, ycen, i);
        j++;
    }
}

int main(){
    genSeriesF();
}

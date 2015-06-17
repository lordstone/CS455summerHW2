#include "Q2.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string.h>

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

array2D::~array2D(){
    for(int i=0;i < yRes;i++) {
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

void PGMImage::setFilename(char* myfilename){
    strcpy(filename,myfilename);
}
void PGMImage::getFilename(char* myfilename){
    strcpy(myfilename,filename);
}

int main()
{

    PGMImage mynewimage(640,480,"test.pgm");

    for(int i = 0; i<480; i++)
        for(int j = 0; j<640; j++)
            mynewimage.setValue(i,j,((i+j)/(640+480-2.0))*255);

    mynewimage.writeFile();

    return 0;
}

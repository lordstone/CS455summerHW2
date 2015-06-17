#include <stdio.h>
#include <fstream>

using namespace std;

class array2D
{
protected:
    float **xtable; // pointer to pointer[s]
    int xRes;
    int yRes;

public:
    array2D(int xres = 10, int yres = 10);
    ~array2D();
    void setValue(int x, int y, float val);
    float getValue(int x, int y);
    void getSize(int& x, int& y);
};

class PGMImage: public array2D
{
protected:
    char filename[2048];

public:
    PGMImage(int x,int y,char* myfilename);
    void writeFile();
    void setFilename(const char* myfilename);
    void getFilename(char* myfilename);
};

class ComplexNumber
{
protected:
    double real;
    double imag;
public:
    ComplexNumber(double i, double j);
    ComplexNumber add(ComplexNumber c2);
    ComplexNumber squared();
    double getReal();
    double getImag();
    double abs();
    void prt();
    void setReal(double val);
    void setImag(double val);
    ComplexNumber operator+(ComplexNumber x);
};


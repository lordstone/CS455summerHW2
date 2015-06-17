#include <iostream>
#include <stdlib.h>

//By Chengxi (Chen) Shi.

using namespace std;

class array2D{
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
void array2D::setValue(int x, int y, float val){
    xtable[x][y] = val;
}

float array2D::getValue(int x, int y){
    return xtable[x][y];
}

void array2D::getSize(int& x, int& y){
    x = xRes; y = yRes;
};

array2D::array2D(int x, int y){
    xRes = x; yRes = y;
    xtable = new float*[yRes]; // NOTE how we do this!

    for(int i=0;i < yRes;i++) {
      xtable[i] = new float[xRes]; // each row points to xRes elements ("columns")
    }

    for(int i=0;i < yRes;i++){
       for(int j=0;j < xRes;j++){
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


// main function
int main(){
    array2D *a = new array2D(320,240);
int xRes, yRes;
a->getSize(xRes,yRes);
for(int i=0;i < yRes;i++){
   for(int j=0;j < xRes;j++){
       a->setValue(i,j,100); // constant value of 100 at all locations
   }
}
for(int i=0;i < yRes;i++){
   for(int j=0;j < xRes;j++){
       cout << a->getValue(i,j) << " ";
   }
   cout << endl;
}

delete a;

}

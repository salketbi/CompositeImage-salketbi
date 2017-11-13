#include<iostream>
#include "bitmap.h"
#include <vector>
#include <string.h>
#define MAX 10

using namespace std;
bool checkDimension(vector <string>);
void combineImages(vector <string>,int, int d[10][2] );
int main()
{
string filename;
vector <string> fileVector;
string str = "DONE";
bool flag;
int i = 1;
cout<<"Enter File Names with extension .bmp (Max. 10) (DONE to stop) . "<<endl;
do
{
cout<<" File "<<i<< " : ";
getline (cin,filename);
if(filename != str)
{
fileVector.push_back(filename);
}
i++;
} while(i<=MAX && filename != str);

flag =  checkDimension(fileVector);
if(flag)
{
cout<<"Composite Image created successfully."<<endl;
}
else
{
cout<<"Composite Image can't be created"<<endl;
}
return 0;
}

bool checkDimension(vector <string> fileVector)
{
int dimens[10][2];
vector <string> validFiles;
int count = 0;
int valid = 1;
bool flag;
for (int i=0;i<fileVector.size();i++)
{
Bitmap image;
vector <vector <Pixel> > bmp;
int width = 0;  // width of image
int height = 0;  // height of image
image.open(fileVector[i]);
bool validBmp = image.isImage();
if ( validBmp == true )
{
bmp = image.toPixelMatrix();
height = bmp.size();
width = bmp[0].size();
dimens[count][0] = width;
dimens[count][1] = height;
validFiles.push_back(fileVector[i]);
count = count + 1;
}
}


if(count<2)
{
flag = false;
return flag;
}

if (count >= 2)
{
for(int i=0;i<count;i++)
{
if(dimens[0][0] == dimens[i+1][0] && dimens[0][1] == dimens[i+1][1])
{
flag = true;
valid = valid + 1;
}
}
}

combineImages(validFiles,valid, dimens);

for (int i = 1; i < valid; ++i)
{
std::cout << "Image "<<i <<" of "<<valid<<" done" <<std::endl;
}

return flag;
}


void combineImages(vector <string> fileVector,int valid, int dimens[10][2] )
{
Bitmap image[valid];
Pixel rgb[valid];
vector < vector < vector<Pixel> > > bmp;

Pixel px;
Pixel avg_px;
int rows,cols;
int k = 0;
int p = 0;
cols = dimens[k][0];
rows = dimens[k][1];

for(k=0;k<valid;k++)
{
image[k].open(fileVector[k]);
bmp.push_back(image[k].toPixelMatrix());
}

for(int i=0;i<rows;i++)
{
for(int j=0;j<cols;j++)
{
avg_px.red = 0;
avg_px.green = 0;
avg_px.blue = 0;
px.red = 0;
px.green = 0;
px.blue = 0;

for(p = 0; p<valid; p++)
{
rgb[p] = bmp[p][i][j];
}

for(p = 0; p<valid; p++)
{
px.red += rgb[p].red;
}

for(p = 0; p<valid; p++)
{
px.green += rgb[p].green;
}

for(p = 0; p<valid; p++)
{
px.blue += rgb[p].blue;
}

avg_px.red = px.red/valid;
avg_px.green = px.blue/valid;
avg_px.blue = px.blue/valid;
bmp[p-1][i][j] = avg_px;
}

}

image[k-1].fromPixelMatrix(bmp[k-1]);
//save the updated original image as oldtimey.bmp
image[k-1].save("composite-salketbi.bmp");

}


#include<iostream>
#include<string>
#include"bitmap.h"
using namespace std;

//getFilnames cins a file and if it is valid(depending on 1st file) adds it a vector of strings
vector<string> getFilenames(string,int, int);



int main()
{
  Bitmap firstImage;
  vector < vector <Pixel> > firstBMP;
  //ask user for filenames until limit (10) is reached or done is typed
  vector<string> files;
  string firstFile;
  cout << "Enter name of the first file to include. Note: All files after, must be same size as this file." << endl;
  cin>>firstFile;
  firstImage.open(firstFile);
  bool validFirstBMP = firstImage.isImage();
  if (validFirstBMP == true)
  {
    firstBMP = firstImage.toPixelMatrix();
  }
  else{
    do{
      cout << "File entered cannot be read as a bitmap image, the image must be a 24 bit depth BMP file. Enter a valid filename." << endl;
      cin >> firstFile;
      firstImage.open(firstFile);
      validFirstBMP = firstImage.isImage();
    }
    while(validFirstBMP == false);
  }
  firstBMP = firstImage.toPixelMatrix();
  cout << "First image loaded. It is " << firstBMP[0].size() << " pixels wide and " << firstBMP.size() << " pixels high." << endl;
  files = getFilenames(firstFile, firstBMP[0].size() , firstBMP.size() );


  //creates newBmp with same size as firstBMP
  vector<vector<Pixel> > newBmp;
  newBmp.resize(firstBMP.size() );
    for (int i=0; i<firstBMP.size(); i++)
    {
      newBmp[i].resize(firstBMP[i].size());
    } 
  for(int i=0; i<newBmp.size(); i++)
  {
    for( int j=0; j<newBmp[0].size(); j++)
    {
      newBmp[i][j].red = 0;
      newBmp[i][j].green = 0;
      newBmp[i][j].blue = 0;
    }
  }

//Assigns average RGB values to each pixel in newBmp
  Bitmap newImage;
  Pixel newRGB;
  for(int i=0; i < files.size(); i++)
  {
    newRGB.red = 0;
    newRGB.green = 0;
    newRGB.blue = 0;
    Bitmap bitmapImage;
    Pixel rgb;
    bitmapImage.open(files[i]);
    vector< vector<Pixel> > bmp;
    bmp = bitmapImage.toPixelMatrix();
    for ( int row = 0; row < bmp.size() ; row++)
    {
      for(int col = 0; col < bmp[0].size() ; col++)
      {
        rgb = bmp[row][col];
        newRGB.red = rgb.red / files.size();
        newRGB.green = rgb.green / files.size();
        newRGB.blue = rgb.blue / files.size();

        newBmp[row][col].red = newBmp[row][col].red + newRGB.red ;
        newBmp[row][col].green = newBmp[row][col].green + newRGB.green ;
        newBmp[row][col].blue = newBmp[row][col].blue + newRGB.blue;
      }
    }
    cout << "Image #" << i+1 << " done" << endl;
  }
  newImage.fromPixelMatrix(newBmp);
  newImage.save("composite-alopez167.bmp");
}


//getFilenames();


//open each image

//print error message and void that file if it has problems

//go through each image and go through each pixel, then use the average RGB values to assign to pixel in new bitmap

//let user know that each image is done loading

//save new bitmap image with name "composite-alopez167.bmp"




vector<string> getFilenames(string first, int columns, int rows)
{
  vector<string> names;
  names.push_back(first);
  do{
    Bitmap loopImage;
    vector< vector<Pixel> > loopBmp;
    cout<< "Please enter name of next BMP file you want to include. Type, DONE, when done." << endl;
    string nextFile;
    cin >> nextFile;
    if( nextFile == "DONE")
    {
      return names;
    }
    loopImage.open(nextFile);
    bool validBmp = loopImage.isImage();
    if( validBmp == true)
    {
      loopBmp = loopImage.toPixelMatrix();
      if( loopBmp[0].size() == columns && loopBmp.size() == rows)
      {
        names.push_back(nextFile);
      }
      else{
        cout << nextFile << " is not the same size as first image." << endl;
      }
    }
    else{
      cout << nextFile << " cannot be read properly as a bitmap image." << endl;
    }
  }
  while( names.size() < 10);

  return names;
}

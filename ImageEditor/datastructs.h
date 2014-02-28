#include<iostream>
using namespace std;

class palette
{
     char id[5];
     int value;
     public:    
     void define( char* , int);
     int getval();
     char* getid();
     palette& operator=( const palette& that)
     {
     	value=that.value;
	strcpy(id, that.id);
     } 
}; 

class image
{
    int w, h, n, c;
    palette* color;
    int** pixmpvl;
    char*** pixmpid;
    public:
    image()
    {
	w=h=n=0;
	color=NULL;
	pixmpvl=NULL;
	pixmpid=NULL;
    }
    ~image()
    {
	int i,j;
	for( i=0; i<h; ++i)
        {		
		for( j=0; j<w; ++j)
		delete[] pixmpid[i][j];
		delete[] pixmpid[i];
	}	
	for( i=0; i<h; ++i)
        {		 
		delete[] pixmpvl[i];
	} 
	delete[] color;
	delete[] pixmpid;
	delete[] pixmpvl;	
     }
    void define(int, int, int, int, palette*, int**, char***);
    int getw();
    int geth();
    int getn();
    int getc();
    palette* getcolor();
    int** getpmvl(); 
    char*** getpmid(); 
    image& operator=( const image& that);     
};      

void palette::define( char* m, int x)
{
	strcpy( id, m);
	value=x;
}

int palette::getval()
{
	return value;	
}

char* palette::getid()
{
	return id;
}

void image::define(int a, int b, int g, int d, palette* e, int** f, char*** id)
{
    w=a;
    h=b;
    n=g;
    c=d;
    color=e;
    pixmpvl=f;
    pixmpid=id;
}

image& image::operator=( const image& that)
{
	if(this != &that)
	{
	int i, j;
	if( this->color !=that.color)
	delete[] color;
	if( this->pixmpid !=that.pixmpid)
	{
		for( i=0; i<h; ++i)
        	{		
			for( j=0; j<w; ++j)
			delete[] pixmpid[i][j];
			delete[] pixmpid[i];
		}
		delete[] pixmpid;	
	}
	if( this->pixmpvl !=that.pixmpvl)
	{
		for( i=0; i<h; ++i)
        	{		 
			delete[] pixmpvl[i];
		}		
		delete[] pixmpvl;
	}
	w=that.w;	
	h=that.h;
	n=that.n;
	c=that.c;
	color=new palette[n];
	for( i=0; i<n; i++)				
	color[i]=that.color[i];        	
	pixmpvl=new int*[h];
        pixmpid=new char**[h];
        for( i=0; i<h; ++i)
        {
		pixmpvl[i]=new int[w];
		pixmpid[i]=new char*[w];
		for( j=0; j<w; ++j)
		pixmpid[i][j]=new char[5];
	}
	for( i=0; i<h; i++)
	{
		for( j=0; j<w; j++)
		{
			pixmpvl[i][j]=that.pixmpvl[i][j];
			strcpy(pixmpid[i][j],that.pixmpid[i][j]);
		}
	}
	}
	cout<<"Assigned1";
	return *(this);
}
	
int image::getw()
{
	return w;
}

int image::geth()
{
	return h;
}

int image::getn()
{
	return n;
}

int image::getc()
{
	return c;
}

palette* image::getcolor()
{
	return color;
}

int** image::getpmvl()
{
	return pixmpvl;
}

char*** image::getpmid()
{
	return pixmpid;
}

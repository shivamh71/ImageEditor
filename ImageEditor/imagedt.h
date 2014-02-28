using namespace std;

int zm=1, crop[2][2], gry=0;
float brigh=5.0, cont=-1;
image im1, im2, im3;

image& grayscale( image& m)
{	
	image mod;
	int i, j, k, w, h, n, c, val;
	double r,g,b;	
	w=m.getw();
	h=m.geth();
	n=m.getn();
	c=m.getc();
	palette* color=new palette[n];
        int** pixmpvl=new int*[h];
        char*** pixmpid=new char**[h];
        for( i=0; i<h; ++i)
        {
		pixmpvl[i]=new int[w];
		pixmpid[i]=new char*[w];
		for( j=0; j<w; ++j)
		pixmpid[i][j]=new char[5];
	}
	for( i=0; i<n; i++)
	{		
		val=m.getcolor()[i].getval();
		//gamma decoding
		r=pow(val/(256*256),2.2);
		g=pow(val/256-(val/(256*256))*256,2.2);
		b=pow(val%256,2.2);
		//changing color definition with gamma decoding
		val=int(pow(.3*r+.59*g+.11*b,1/2.2));
		val=val*256*256+val*256+val;				
		color[i].define(m.getcolor()[i].getid(),val);
	}
	for( i=0; i < h; ++i)
        {		
		for( j=0; j<w; ++j)
		{			
			k=bsrch(color, m.getpmid()[i][j], 0, n-1);			
			pixmpvl[i][j]=color[k].getval();
			strcpy(pixmpid[i][j], m.getpmid()[i][j]);			            			
		}		  		
	}
	mod.define( w, h, n, c, color, pixmpvl, pixmpid);
	m=mod;
	return m;
} 

image& flip( image& m, char Choice)
{	
	image mod;
	int i, j, w, h, n, c;
	w=m.getw();
	h=m.geth();
	n=m.getn();
	c=m.getc();
	palette* color=new palette[n];
	int** pixmpvl=new int*[h];
        char*** pixmpid=new char**[h];
        for( i=0; i<h; ++i)
        {
		pixmpvl[i]=new int[w];
		pixmpid[i]=new char*[w];
		for( j=0; j<w; ++j)
		pixmpid[i][j]=new char[5];
	}
	for( i=0; i<n; i++)				
	color[i].define(m.getcolor()[i].getid(),m.getcolor()[i].getval());	
	switch(Choice)
	{
		case 'V':		
		for(i=0; i<h; i++)
		{
			for(j=0; j<w; j++)
			{
				pixmpvl[i][j]=m.getpmvl()[i][w-1-j];
				strcpy(pixmpid[i][j], m.getpmid()[i][w-1-j]); 
			}
		}		
		break;

		case 'H':		
		for(i=0; i<w; i++)
		{
			for(j=0; j<h; j++)
			{
				pixmpvl[j][i]=m.getpmvl()[h-1-j][i];
				strcpy(pixmpid[j][i], m.getpmid()[h-1-j][i]); 
			}
		}		
		break;
		default:
		break;
	}
	mod.define( w, h, n, c, color, pixmpvl, pixmpid);
	m=mod;
	return m;
}

image& zoom( image& m, int index)
{	
	image mod;
	int i, j, w, h, n, c;
	w=index*m.getw();
	h=index*m.geth();
	n=m.getn();
	c=m.getc();
	palette* color=new palette[n];
	int** pixmpvl=new int*[h];
        char*** pixmpid=new char**[h];
        for( i=0; i<h; ++i)
        {
		pixmpvl[i]=new int[w];
		pixmpid[i]=new char*[w];
		for( j=0; j<w; ++j)
		pixmpid[i][j]=new char[5];
	}
	for( i=0; i<n; i++)				
	color[i].define(m.getcolor()[i].getid(),m.getcolor()[i].getval());		
	for( i=0; i<h; i++)
	{
		for( j=0; j<w; j++)
		{
			pixmpvl[i][j]=m.getpmvl()[i/index][j/index];
			strcpy(pixmpid[i][j],m.getpmid()[i/index][j/index]);
		}
	}
	mod.define( w, h, n, c, color, pixmpvl, pixmpid);
	m=mod;
	return m;	
}  

image& contrast( image& m, image& p, float Index)
{	
	int i, j, k, w, h, n, c, val, r=0, g=0, b=0, rav, gav, bav, size;
	float clvl, maxcoeff=10;
	int rmax=0, gmax=0, bmax=0, rmin=255, gmin=255, bmin=255;
	w=m.getw();
	h=m.geth();
	n=m.getn();
	c=m.getc();
	size=h*w;
	palette* color=new palette[n];
	int** pixmpvl=new int*[h];
  	char*** pixmpid=new char**[h];
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
				val=m.getpmvl()[i][j];
				r+=val/(256*256);
				g+=val/256-(val/(256*256))*256;
				b+=val%256;				
			}
	}
	rav=r/size;
	gav=g/size;
	bav=b/size;	
	for( i=0; i<n; i++)
	{		
		val=m.getcolor()[i].getval();					
		r=val/(256*256);
		g=val/256-(val/(256*256))*256;
		b=val%256;
		if( r > rmax)
		rmax=r;
		else
		if( r < rmin)
		rmin=r; 
		if( g > gmax)
		gmax=g;
		else
		if( g < gmin)
		gmin=g; 
		if( b > bmax)
		bmax=b;
		else
		if( b < bmin)
		bmin=b; 		
	}
	if((255.0-rav)/(rmax-rav) < maxcoeff)
	maxcoeff=(255.0-rav)/(rmax-rav);
	if((255.0-bav)/(bmax-bav) < maxcoeff)
	maxcoeff= (255.0-bav)/(bmax-bav);
	if((255.0-gav)/(gmax-gav) < maxcoeff)
	maxcoeff=(255.0-gav)/(gmax-gav); 
	if( float(rav)/(rav-rmin) < maxcoeff)
	maxcoeff=float(rav)/(rav-rmin); 
	if( float(bav)/(bav-bmin) < maxcoeff)
	maxcoeff=float(bav)/(bav-bmin);
	if( float(gav)/(gav-gmin) < maxcoeff)
	maxcoeff=float(gav)/(gav-gmin);
	if( Index!=-1)
	clvl=Index*maxcoeff;
	else
	clvl=1;
	for( i=0; i<n; i++)
	{		
		val=m.getcolor()[i].getval();					
		r=val/(256*256);
		g=val/256-(val/(256*256))*256;
		b=val%256;
		r=int((r-rav)*clvl+rav);
		g=int((g-rav)*clvl+rav);
		b=int((b-rav)*clvl+rav);
		val=r*256*256+g*256+b;
		color[i].define(m.getcolor()[i].getid(),val);
	}
	for( i=0; i<h; i++)
	{
			for( j=0; j<w; j++)
			{
				k=bsrch(color, m.getpmid()[i][j], 0, n-1);			
				pixmpvl[i][j]=color[k].getval();
				strcpy(pixmpid[i][j],m.getpmid()[i][j]);
			}
	}	
	image mod;
	mod.define( w, h, n, c, color, pixmpvl, pixmpid);
	p=mod;
	return p;
}

image& brightness( image& m, float Index)
{	
	int i, j, k, w, h, n, c, val, r, g, b;
	w=m.getw();
	h=m.geth();
	n=m.getn();
	c=m.getc();
	palette* color=new palette[n];
	int** pixmpvl=new int*[h];
  	char*** pixmpid=new char**[h];
  	for( i=0; i<h; ++i) 
  	{
		pixmpvl[i]=new int[w];
		pixmpid[i]=new char*[w];
		for( j=0; j<w; ++j)
		pixmpid[i][j]=new char[5];
	}	
	for( i=0; i<n; i++)
	{		
			val=m.getcolor()[i].getval();
			r=val/(256*256);
			g=val/256-(val/(256*256))*256;
			b=val%256;
			if( Index<5.0)
			{
				r-=int((5-Index)*(float(r)/5.0));
				g-=int((5-Index)*(float(g)/5.0));
				b-=int((5-Index)*(float(b)/5.0));	
			}
			else
			{
				r+=int((Index-5)*(float(255-r)/5.0));	
				g+=int((Index-5)*(float(255-g)/5.0));	
				b+=int((Index-5)*(float(255-b)/5.0));
			}
			val=r*256*256+g*256+b;		
			color[i].define(m.getcolor()[i].getid(),val);			
	}
	for( i=0; i<h; i++)
	{
			for( j=0; j<w; j++)
			{
				k=bsrch(color, m.getpmid()[i][j], 0, n-1);			
				pixmpvl[i][j]=color[k].getval();
				strcpy(pixmpid[i][j],m.getpmid()[i][j]);
			}
	}
	
	image mod;
	mod.define( w, h, n, c, color, pixmpvl, pixmpid);
	m=mod;
	return m;
}

image& rotate( image& m, int choice)
{	
	int i, j, k, w, h, n, c, val;	
	n=m.getn();
	c=m.getc();
	int** pixmpvl;
	char*** pixmpid;
	palette* color=new palette[n];  	 
	for( i=0; i<n; i++)
	{		
			val=m.getcolor()[i].getval();			
			color[i].define(m.getcolor()[i].getid(),val);			
	}
	switch( choice)
	{
	case 1:
		h=m.getw();
		w=m.geth();
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
				strcpy(pixmpid[i][j],m.getpmid()[j][h-i-1]);
				pixmpvl[i][j]=m.getpmvl()[j][h-i-1];
			}
		}
	break;
	case 2:
		h=m.getw();
		w=m.geth();
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
				strcpy(pixmpid[i][j],m.getpmid()[w-j-1][i]);
				pixmpvl[i][j]=m.getpmvl()[w-j-1][i];
			}
		}
	break;	
	case 3:
		h=m.geth();
		w=m.getw();
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
				strcpy(pixmpid[i][j],m.getpmid()[h-i-1][w-j-1]);
				pixmpvl[i][j]=m.getpmvl()[h-i-1][w-j-1];
			}
		}
	break;		
	}
	image mod;
	mod.define( w, h, n, c, color, pixmpvl, pixmpid);
	m=mod;
	return m;
}

image& negative( image& m)
{	
	int i, j, k, w, h, n, c, val, r, g, b;
	w=m.getw();
	h=m.geth();
	n=m.getn();
	c=m.getc();
	palette* color=new palette[n];
	int** pixmpvl=new int*[h];
  	char*** pixmpid=new char**[h];
  	for( i=0; i<h; ++i) 
  	{
		pixmpvl[i]=new int[w];
		pixmpid[i]=new char*[w];
		for( j=0; j<w; ++j)
		pixmpid[i][j]=new char[5];
	}	
	for( i=0; i<n; i++)
	{		
			val=m.getcolor()[i].getval();
			r=val/(256*256);
			g=val/256-(val/(256*256))*256;
			b=val%256;
			r=255-r;
			g=255-g;
			b=255-b;
			val=r*256*256+g*256+b;			
			color[i].define(m.getcolor()[i].getid(), val);			
	}
	for( i=0; i<h; i++)
	{
			for( j=0; j<w; j++)
			{
				k=bsrch(color, m.getpmid()[i][j], 0, n-1);			
				pixmpvl[i][j]=color[k].getval();
				strcpy(pixmpid[i][j],m.getpmid()[i][j]);
			}
		}
	
	image mod;
	mod.define( w, h, n, c, color, pixmpvl, pixmpid);
	m=mod;
	return m;
}

void im3proc()
{
	contrast( im2, im3, cont);
	brightness( im3, brigh);
	zoom( im3, zm);
}

void imsave()
{
	contrast( im2, im3, cont);
	brightness( im3, brigh);
}
	
			
	

 

using namespace std;


void write( image& m, char* name)
{
    int i, j, w, h, n, c;
    fstream f;
    f.open(name,ios::out);
    f<<"/* XPM */ \nstatic char *output[] = {\n/* columns rows colors chars-per-pixel */\n\"";
    w=m.getw();
    h=m.geth();
    n=m.getn();
    c=m.getc();
    f<<w<<" "<<h<<" "<<n<<" "<<c<<"\",\n";    
    f<<setfill('0');
    for(i=0; i<n; ++i)
    {
        f<<"\"";
        f<<m.getcolor()[i].getid();
        f<<" c #";
        f<<hex<<setw(6)<<m.getcolor()[i].getval();
        f<<"\",\n";
    }
    f<<"/* pixels */\n";
    for( i=0; i<h; ++i)
    {
    	f<<"\"";
    	for( j=0; j<w; ++j)
    	{
    		f<<m.getpmid()[i][j];
    	}
    	f<<"\",\n";
    }
    f.seekp(-2,ios::cur);
    f<<"\n};";    
    cout<<"Writing done";        
}    
    
int colorcomp (const void * a, const void * b)
{
  return ( strcmp((*(palette*)a).getid(), (*(palette*)b).getid()) );
}

    
void read( image& im, char* name)
{
   	fstream f;
        f.open(name,ios::in);        
        char ch, s[5], cl[15];
        int w, h, n, c, val, i, j, k;
        int **pixmpvl;
        char ***pixmpid;   
      	do
        f>>ch;
        while(ch!='"');        
        f>>w>>h>>n>>c;        
        palette* color=new palette[n];
        pixmpvl=new int*[h];
        pixmpid=new char**[h];
        for( i=0; i<h; ++i)
        {
		pixmpvl[i]=new int[w];
		pixmpid[i]=new char*[w];
		for( j=0; j<w; ++j)
		pixmpid[i][j]=new char[5];
	}
        while(ch!=',')
        {
        	f>>ch;        	
        }
	//reading colors
        for( i=0; i<n; ++i)
        {
                while(ch!='"')
                f>>ch;                
                f.read(s,c);
                s[c]=0;
                f>>ch;    //reads c                                           
                f>>ch;    //reads first char of color definition                                          
                if( ch=='#')             
                f>>hex>>val;
                else
                {                        
                        cl[0]=ch;
                        f.get(cl+1,15,'"');                        
                        val=colordef(cl);
                }
                color[i].define( s, val);                
                while(ch!=',')
                f>>ch;
        }        
        //sort colors
       qsort(color, n, sizeof(palette), colorcomp);       
        //reading pixmap
        for( i=0; i < h; ++i)
        {
		while( ch!='"')
		f>>ch;
		for( j=0; j<w; ++j)
		{
			f.read(s,c);
			s[c]=0;
			//search
			k=bsrch(color, s, 0, n-1);
			if(k!=-1)			
			{
				pixmpvl[i][j]=color[k].getval();
				strcpy(pixmpid[i][j],s);
			}
			else
			{
				cout<<"Error!";
				exit(0);
			}	            			
		}
		while( ch!=',' && ch!=';')
		f>>ch;        		
	}        
        image mod;
        mod.define(w, h, n, c, color, pixmpvl, pixmpid);
        im=mod;
        cout<<"Reading done"<<endl;  
}

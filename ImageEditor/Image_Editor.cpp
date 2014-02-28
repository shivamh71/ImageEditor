//~~~~~~~~~~~~~~~~~~~~~~~~~~~
// LIBRARIES INCLUDED IN CODE
//~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include<iostream>

#include<assert.h>

#include<cmath>

#include<cstdio>

#include<iomanip>

#include<fstream>

#include<cstdlib>

#include<cstring>

#include "datastructs.h"

#include "colordict.h"

#include "pltsrch.h"

#include "ioimage.h"

#include "imagedt.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~
// FILES LINKED TO THE CODE
//~~~~~~~~~~~~~~~~~~~~~~~~~

#include "ezwin.h"

#include "rect.h"

#include "position.h"

#include "bitmap.h"

#include "ellipse.h"

//~~~~~~~~~~~~~~~~~
// GLOBAL VARIABLES
//~~~~~~~~~~~~~~~~~

SimpleWindow Browser(" IMAGE EDITOR 6.2 ", 12.0 , 8.0 , Position(1.0,1.0));
SimpleWindow ImageEditor(" IMAGE EDITOR 6.2 ", 24.0 , 16.0 , Position(1.0,1.0));
SimpleWindow ToolBar(" EDITOR ", 24.0 , 4.0 , Position(1.0,17.0));

int S=0,i=0,flag=0,z=0;

float X1[3],Y1[3];

BitMap Photo(ImageEditor);
BitMap Photo1(Browser);

char FileName[80];

void im3proc();	

//~~~~~~~~~~~~~~~~~~~~
// Mouse Click Control
//~~~~~~~~~~~~~~~~~~~~

// This controls mouse clicks during normal image editing

int ImageEditorMouseClick(const Position &p)
{
	float X=p.GetXDistance();
	float Y=p.GetYDistance();	
	Photo.Erase();
	Photo.SetPosition(Position(1.0,1.0));
	RectangleShape R22(ImageEditor,Position(12.0,8.0),Black,24.0,16.0);
	R22.Draw();
	Photo.Draw();
	return 0;
}

// This controls mouse clicks during CROP operation

int ImageEditorMouseClick2(const Position &p)
{
		
	X1[i]=p.GetXDistance();
	Y1[i]=p.GetYDistance();
	z++;
	if(z==2)
	{
		AlertWindow(" ERROR "," some error occured , please try again ");
		i=0;
	}
	i++;	
	if((i==3))
	{
		i=0;
		flag=0;
		RectangleShape R23(ImageEditor,Position(12.0,(Y1[1]/2)),Black,24.0,Y1[1]);
		R23.Draw();
		RectangleShape R24(ImageEditor,Position(12.0,(Y1[2]+((16.0-Y1[2])/2))),Black,24.0,(16.0-Y1[2]));
		R24.Draw();
		RectangleShape R25(ImageEditor,Position((X1[1]/2),8.0),Black,X1[1],16.0);
		R25.Draw();
		RectangleShape R26(ImageEditor,Position((X1[2]+((24.0-X1[2])/2)),8.0),Black,(24.0-X1[2]),16.0);
		R26.Draw();		
		ImageEditor.SetMouseClickCallback(ImageEditorMouseClick);
		i=0;
	}
	if((z>5)&&(i==2))
	{
		RectangleShape R27(ImageEditor,Position(12.0,(Y1[0]/2)),Black,24.0,Y1[0]);
		R27.Draw();
		RectangleShape R28(ImageEditor,Position(12.0,(Y1[1]+((16.0-Y1[1])/2))),Black,24.0,(16.0-Y1[1]));
		R28.Draw();
		RectangleShape R29(ImageEditor,Position((X1[0]/2),8.0),Black,X1[0],16.0);
		R29.Draw();
		RectangleShape R30(ImageEditor,Position((X1[1]+((24.0-X1[1])/2)),8.0),Black,(24.0-X1[1]),16.0);
		R30.Draw();		
		ImageEditor.SetMouseClickCallback(ImageEditorMouseClick);
		i=0;	
	}
	return 0;
}

// This controls mouse clicks in ToolBar window

int ToolBarMouseClick(const Position &p)
{
	float X=p.GetXDistance();
	float Y=p.GetYDistance();
	if((X<=23.75)&&(X>=22.25)&&(Y<=1.5)&&(Y>=0.5))
	{
		imsave();
		write(im3, "Save.xpm");
		im3proc();
	}
	if((X<=23.75)&&(X>=22.25)&&(Y<=3.5)&&(Y>=2.5))
	{		
		remove("output.xpm");
		ImageEditor.Close();
		ToolBar.Close();
		return 0;
	}
	if((X<=11.7)&&(X>=8.7)&&(Y<=3.5)&&(Y>=2.5))
	{
		Photo.Erase();		
		rotate(im2, int (X-7.7));
		rotate(im3, int (X-7.7));
		write(im3, "output.xpm");
		Photo.Load("output.xpm");
		RectangleShape R38(ImageEditor,Position(12.0,8.0),Black,24.0,16.0);
		R38.Draw();
		Photo.SetPosition(Position(1.0,1.0));
		Photo.Draw();
	}
	if((X<=1.0)&&(X>=0.25)&&(Y<=3.8)&&(Y>=2.8))				
	{
		Photo.Erase();
		im2=flip(im2, 'V');
		im3=flip(im3, 'V');
		write(im3, "output.xpm");		
		Photo.Load("output.xpm");		
		Photo.SetPosition(Position(1.0,1.0));
		RectangleShape R31(ImageEditor,Position(12.0,8.0),Black,24.0,16.0);
		R31.Draw();
		Photo.Draw();	
	}
	if((X<=1.75)&&(X>=1.0)&&(Y<=3.8)&&(Y>=2.8))				
	{
		Photo.Erase();
		flip(im2, 'H');
		flip(im3, 'H');
		write(im3, "output.xpm");
		Photo.Load("output.xpm");		
		Photo.SetPosition(Position(1.0,1.0));
		RectangleShape R32(ImageEditor,Position(12.0,8.0),Black,24.0,16.0);
		R32.Draw();
		Photo.Draw();	
	}
	if((X<=8.9)&&(X>=7.1)&&(Y<=1.5)&&(Y>=0.5))
	{		
		Photo.Erase();
		zm=int((X-7.1)/.9+1);
		cout<<zm;
		im3proc();
		write(im3, "output.xpm");
		Photo.Load("output.xpm");						
		Photo.SetPosition(Position(1.0,1.0));
		RectangleShape R33(ImageEditor,Position(12.0,8.0),Black,24.0,16.0);
		R33.Draw();
		Photo.Draw();
	}
	if((X<=11.75)&&(X>=9.25)&&(Y<=1.5)&&(Y>=0.5))
	{
		Photo.Erase();
		negative(im2);
		negative(im3);		
		write(im3, "output.xpm");
		Photo.Load("output.xpm");						
		Photo.SetPosition(Position(1.0,1.0));
		RectangleShape R33(ImageEditor,Position(12.0,8.0),Black,24.0,16.0);
		R33.Draw();
		Photo.Draw();
	}
	if((X<=4.8)&&(X>=2.2)&&(Y<=1.5)&&(Y>=0.5))
	{		
		Photo.Erase();
		if( gry!= 1)
		{
			grayscale(im2);			
			grayscale(im3);
			gry=1;
		}
		write(im3, "output.xpm");
		Photo.Load("output.xpm");		
		Photo.SetPosition(Position(1.0,1.0));
		RectangleShape R34(ImageEditor,Position(12.0,8.0),Black,24.0,16.0);
		R34.Draw();
		Photo.Draw();		
	}
	if((X<=4.8)&&(X>=2.2)&&(Y<=3.5)&&(Y>=2.5))
	{
		Photo.Erase();		
		read( im1, FileName);
		im3=im2=im1;	
		gry=0;
		brigh=5;
		cont=-1;
		crop[0][0]=crop[0][1]=0;
		crop[1][0]=im1.geth();
		crop[1][1]=im1.getw();
		zm=1;
		Photo.Load(FileName);	
		Photo.SetPosition(Position(1.0,1.0));
		RectangleShape R35(ImageEditor,Position(12.0,8.0),Black,24.0,16.0);
		R35.Draw();
		Photo.Draw();
	}
	if((X>=15.5)&&(X<=21.0)&&(Y<=1.5)&&(Y>=0.5))
	{
		brigh=(X-15.5)/.55;		
		im3proc();		
		Photo.Erase();
		write(im3, "output.xpm");
		RectangleShape R36(ImageEditor,Position(12.0,8.0),Black,24.0,16.0);
		R36.Draw();
		Photo.Load("output.xpm");		
		Photo.SetPosition(Position(1.0,1.0));		
		Photo.Draw();
	}
	if((X>=15.5)&&(X<=21.0)&&(Y<=3.5)&&(Y>=2.5))
	{
		cont=(X-15.5)/5.5;
		im3proc();
		Photo.Erase();
		write(im3, "output.xpm");		
		RectangleShape R37(ImageEditor,Position(12.0,8.0),Black,24.0,16.0);
		R37.Draw();
		Photo.Load("output.xpm");
		Photo.SetPosition(Position(1.0,1.0));
		Photo.Draw();
	}
	if((X<=1.75)&&(X>=0.25)&&(Y<=1.5)&&(Y>=0.5))
	{		
		flag=1;
	}
	if(flag==1)
	{	
		ImageEditor.SetMouseClickCallback(ImageEditorMouseClick2);
		
	}
	return 0;
}

// This controls mouse clicks 

int BrowserMouseClick(const Position &p)
{
	int X=p.GetXDistance();
	int Y=p.GetYDistance();
	if((X<=11)&&(X>=1)&&(Y>=3)&&(Y<=4))
	{
		
		cout<<"\n enter name of file ";
		cin>>FileName;
		read( im1, FileName);
		im2=im3=im1;				
		crop[0][0]=crop[0][1]=0;
		crop[1][0]=im1.geth();
		crop[1][1]=im1.getw();
		Browser.Close();
		S=1;
	}
	if((X<=11)&&(X>=1)&&(Y>=5)&&(Y<=6))
	{
		Browser.Close();
		S=-1;
	}
	if(S==1)
	{
		
		// This opens the Image Editor window
	
		ImageEditor.Open();
		RectangleShape R8(ImageEditor,Position(12.0,8.0),Black,24.0,16.0);
		R8.Draw();
	
		// This opens the ToolBar
	
		ToolBar.Open();
		RectangleShape R9(ToolBar,Position(12.0,2.0),Black,24.0,4.0);
		R9.Draw();
		RectangleShape R10(ToolBar, Position(23.0,1.0), White, 1.6, 1.1);
		R10.Draw();
		RectangleShape R11(ToolBar, Position(23.0,1.0), Black, 1.5, 1.0);
		R11.Draw();
		RectangleShape R12(ToolBar, Position(23.0,3.0), White, 1.6, 1.1);
		R12.Draw();
		RectangleShape R13(ToolBar, Position(23.0,3.0), Black, 1.5, 1.0);
		R13.Draw();
		ToolBar.RenderText(Position(22.25,0.5), Position(23.75,1.5), "SAVE", Green, Black);
		ToolBar.RenderText(Position(22.25,2.5), Position(23.75,3.5), "QUIT", Green, Black);
		RectangleShape R14(ToolBar, Position(1.0,1.0), White, 1.6, 1.1);
		R14.Draw();
		RectangleShape R15(ToolBar, Position(1.0,1.0), Black, 1.5, 1.0);
		R15.Draw();
		ToolBar.RenderText(Position(0.25,0.5), Position(1.75,1.5), "CROP", Green, Black);
		RectangleShape R16(ToolBar, Position(1.0,2.8), White, 1.6, 2.1);
		R16.Draw();
		RectangleShape R17(ToolBar, Position(1.0,2.8), Black, 1.5, 2.0);
		R17.Draw();
		ToolBar.RenderText(Position(0.25,1.8), Position(1.75,2.8), "FLIP", Green, Black);
		ToolBar.RenderText(Position(0.25,2.8), Position(1.0,3.8), "V", Green, Black);
		ToolBar.RenderText(Position(1.0,2.8), Position(1.75,3.8), "H", Green, Black);
		RectangleShape R18(ToolBar, Position(3.5,1.0), White, 2.7, 1.1);
		R18.Draw();
		RectangleShape R19(ToolBar, Position(3.5,1.0), Black, 2.6, 1.0);
		R19.Draw();
		ToolBar.RenderText(Position(2.2,0.5), Position(4.8,1.5), "GRAYSCALE", Green, Black);
		RectangleShape R20(ToolBar, Position(3.5,3.0), White, 2.7, 1.1);
		R20.Draw();
		RectangleShape R21(ToolBar, Position(3.5,3.0), Black, 2.6, 1.0);
		R21.Draw();
		ToolBar.RenderText(Position(2.2,2.5), Position(4.8,3.5), "UNDO", Green, Black);
		RectangleShape R22(ToolBar, Position(7.1,1.0), White, 3.7, 1.1);
		R22.Draw();
		RectangleShape R23(ToolBar, Position(7.1,1.0), Black, 3.6, 1.0);
		R23.Draw();
		ToolBar.RenderText(Position(5.3,0.5), Position(7.1,1.5), "ZOOM", Green, Black);
		ToolBar.RenderText(Position(7.1,0.5), Position(8.0,1.5), "1x", Green, Black);
		ToolBar.RenderText(Position(8.0,0.5), Position(8.9,1.5), "2x", Green, Black);
		RectangleShape R41(ToolBar, Position(10.5,1.0), White, 2.5, 1.1);
		R41.Draw();
		RectangleShape R42(ToolBar, Position(10.5,1.0), Black, 2.4, 1.0);
		R42.Draw();
		ToolBar.RenderText(Position(9.25,0.5), Position(11.75,1.5), "NEG/POS", Green, Black);
		RectangleShape R24(ToolBar, Position(8.5,3.0), White, 6.5, 1.1);
		R24.Draw();
		RectangleShape R25(ToolBar, Position(8.5,3.0), Black, 6.4, 1.0);
		R25.Draw();
		ToolBar.RenderText(Position(5.3,2.5), Position(7.7,3.5), "ROTATE", Green, Black);
		ToolBar.RenderText(Position(8.7,2.5), Position(9.7,3.5), "90L", Green, Black);
		ToolBar.RenderText(Position(9.7,2.5), Position(10.7,3.5), "90R", Green, Black);
		ToolBar.RenderText(Position(10.7,2.5), Position(11.7,3.5), "180", Green, Black);
		RectangleShape R26(ToolBar, Position(17.0,1.0), White, 9.1, 1.1);
		R26.Draw();
		RectangleShape R27(ToolBar, Position(17.0,1.0), Black, 9.0, 1.0);
		R27.Draw();
		ToolBar.RenderText(Position(13.0,0.5), Position(15.0,1.5), "BRIGHTNESS", Green, Black);
		ToolBar.RenderText(Position(15.5,0.5), Position(16.0,1.5), "0", Green, Black);
		ToolBar.RenderText(Position(16.0,0.5), Position(16.5,1.5), "1", Green, Black);
		ToolBar.RenderText(Position(16.5,0.5), Position(17.0,1.5), "2", Green, Black);
		ToolBar.RenderText(Position(17.0,0.5), Position(17.5,1.5), "3", Green, Black);
		ToolBar.RenderText(Position(17.5,0.5), Position(18.0,1.5), "4", Green, Black);
		ToolBar.RenderText(Position(18.0,0.5), Position(18.5,1.5), "5", Green, Black);
		ToolBar.RenderText(Position(18.5,0.5), Position(19.0,1.5), "6", Green, Black);
		ToolBar.RenderText(Position(19.0,0.5), Position(19.5,1.5), "7", Green, Black);
		ToolBar.RenderText(Position(19.5,0.5), Position(20.0,1.5), "8", Green, Black);
		ToolBar.RenderText(Position(20.0,0.5), Position(20.5,1.5), "9", Green, Black);
		ToolBar.RenderText(Position(20.5,0.5), Position(21.0,1.5), "10", Green, Black);
		RectangleShape R28(ToolBar, Position(17.0,3.0), White, 9.1, 1.1);
		R28.Draw();
		RectangleShape R29(ToolBar, Position(17.0,3.0), Black, 9.0, 1.0);
		R29.Draw();
		ToolBar.RenderText(Position(13.0,2.5), Position(15.0,3.5), "CONTRAST", Green, Black);
		ToolBar.RenderText(Position(15.5,2.5), Position(16.0,3.5), "0", Green, Black);
		ToolBar.RenderText(Position(16.0,2.5), Position(16.5,3.5), "1", Green, Black);
		ToolBar.RenderText(Position(16.5,2.5), Position(17.0,3.5), "2", Green, Black);
		ToolBar.RenderText(Position(17.0,2.5), Position(17.5,3.5), "3", Green, Black);
		ToolBar.RenderText(Position(17.5,2.5), Position(18.0,3.5), "4", Green, Black);
		ToolBar.RenderText(Position(18.0,2.5), Position(18.5,3.5), "5", Green, Black);
		ToolBar.RenderText(Position(18.5,2.5), Position(19.0,3.5), "6", Green, Black);
		ToolBar.RenderText(Position(19.0,2.5), Position(19.5,3.5), "7", Green, Black);
		ToolBar.RenderText(Position(19.5,2.5), Position(20.0,3.5), "8", Green, Black);
		ToolBar.RenderText(Position(20.0,2.5), Position(20.5,3.5), "9", Green, Black);
		ToolBar.RenderText(Position(20.5,2.5), Position(21.0,3.5), "10", Green, Black);		
		Photo.Load(FileName);		
		Photo.SetPosition(Position(1.0,1.0));		
		Photo.Draw();		
		ToolBar.SetMouseClickCallback(ToolBarMouseClick);
		if(flag==0)
		{
			ImageEditor.SetMouseClickCallback(ImageEditorMouseClick);
		}		
		//next3:
		
		//label for goto statement
		
		S=0;
	}
	return 0;
}
				
// MAIN CODE

int ApiMain()
{
		
	// This opens the Browser Window 		
	
	Browser.Open();	
	RectangleShape R1(Browser,Position(6.0,4.0),Blue,12.0,8.0);	
	R1.Draw();	
	RectangleShape R2(Browser,Position(6.0,1.5),White,10.2,1.2);	
	R2.Draw();	
	RectangleShape R3(Browser,Position(6.0,1.5),Black,10.0,1.0);
	R3.Draw();	
	Browser.RenderText(Position(1.0,1.0),Position(11.0,2.0),"   WELCOME  TO  IMAGE  EDITING  WIZARD\n yo   ",Green,Black);	
	EllipseShape R4(Browser,Position(6.0,3.5),White,6.2,1.2);		
	R4.Draw();	
	EllipseShape R5(Browser,Position(6.0,3.5),Black,6.0,1.0);		
	R5.Draw();	
	Browser.RenderText(Position(1.0,3.0),Position(11.0,4.0)," CLICK TO BROWSE FILE ",Green,Black);	
	EllipseShape R6(Browser,Position(6.0,5.5),White,6.2,1.2);	
	R6.Draw();
	EllipseShape R7(Browser,Position(6.0,5.5),Black,6.0,1.0);
	R7.Draw();	
	Browser.RenderText(Position(1.0,5.0),Position(11.0,6.0)," CLICK TO QUIT WIZARD ",Green,Black);
	//RectangleShape
	Browser.SetMouseClickCallback(BrowserMouseClick);
	return 0;
}	

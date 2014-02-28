int colordef(char* colorname)
{
    	if( !strcmp(colorname,"black"))
    	return 0;
	if( !strcmp(colorname,"blue"))
	return 255; 
	if( !strcmp(colorname,"green"))
	return 255*256;
	if( !strcmp(colorname,"red"))
	return 255*256*256;

}
    
    

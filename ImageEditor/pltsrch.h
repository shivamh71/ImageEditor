

int bsrch(palette *c, char* s, int l, int h)
{
	if(l<=h)
	{
		int mid=(l+h)/2;
		if( !strcmp(c[mid].getid(),s) )
		{
			return mid;
		}
		else if( strcmp(c[mid].getid(),s) < 0) 
		{
			return bsrch(c, s, mid+1, h);
		}
		else
		{
			return bsrch(c, s, l, mid-1);
		}
	}
	else
	{
		return -1;
	}
} 

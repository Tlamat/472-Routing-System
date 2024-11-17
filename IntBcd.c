

int bcd(int dec)
{
	return ((dec/10)<<4)+(dec%10);
}
int unbcd(int bcd)
{
	return ((bcd>>4)*10)+bcd%16;
}
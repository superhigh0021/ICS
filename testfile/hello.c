#include<stdio.h>

void print(char* buf)
{
	printf("%s", buf);
}

int main()
{
	const void* buf = "hell0";
	void* buf1 = (void*)(buf);
	print(buf1);
}
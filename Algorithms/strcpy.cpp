#include <iostream>
#include <assert.h>

char* strcpy(char* target, const char* source)
{
	assert(target!=NULL && source!=NULL);
	char* copy = target;
	while((*target++ = *source++))
	{
		if(*target == '\0')
			break;
	}
	if(*source != '\0')
		return NULL;
	return copy;
}

int main(void)
{
	char str1[2] = {'a','\0'};
	char str2[3] = {'1','2','\0'};
	if(strcpy(str1,str2))
		std::cout << str1;
	else
		std::cout << NULL;
}
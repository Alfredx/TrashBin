#include <iostream>

char* strcpy(char* target, const char* source)
{
  if(target==NULL || source==NULL)
		return NULL;
	char* copy = target;
	while((*target++ = *source++));
	if(*(--target) != '\0')
		return NULL;
	return copy;
}

int main(void)
{
	char str1[5] = {'a','b','c','d','\0'};
	char str2[3] = {'1','2','\0'};
	strcpy(str1,str2);
	std::cout << str1;
}

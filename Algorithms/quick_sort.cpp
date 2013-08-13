#include <iostream>
#include <stdlib.h>
#include <time.h>

int get_anchor(int start, int end)
{
	return start+rand()%(end-start+1);
}

void switch_position(int* array, int left, int right)
{
	int temp = array[left];
	array[left] = array[right];
	array[right] = temp;
}


void quick_sort(int* array, int start, int end)
{
	if(end <= start)
		return;
	int anchor_position = get_anchor(start,end);
	int anchor = array[anchor_position];
	int pStart = start+1;
	int pEnd = end;
	switch_position(array,anchor_position,start);
	while(1)
	{
		while(array[pEnd] > anchor)
			--pEnd;
		while(array[pStart] < anchor && pStart < pEnd)
			++pStart;
		if(pStart >= pEnd)
			break;
		switch_position(array,pStart,pEnd);
		if(array[pStart] == anchor)
			--pEnd;
		else
			++pStart;
	}
	switch_position(array,pEnd,start);
	if(start < pStart-1)
		quick_sort(array, start, pStart-1);
	if(pEnd+1 < end)
		quick_sort(array, pEnd+1, end);
}

int main(void)
{
	srand((int)time(0));
	int array[100];
	for(int i = 0; i < 100; ++i)
	{
		array[i] = rand()%500;
	}
	quick_sort(array,0,99);
	for(int i = 0; i < 100; ++i)
	{
		std::cout<<array[i]<<std::endl;
	}
}
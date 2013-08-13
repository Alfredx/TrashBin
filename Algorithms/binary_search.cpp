#include <iostream>

int binary_search(int* array, int start, int end, int target)
{
	if(end < start)
		return -1;
	int t = array[(start+end)/2];
	if(t == target)
		return (start+end)/2;
	else if(t < target)
		return binary_search(array, (start+end)/2+1, end, target);
	else
		return binary_search(array, start, (start+end)/2-1, target);
}

int main(void)
{
	int array[10] = {1,2,3,4,5,6,7,8,9,10};
	std::cout << binary_search(array,0,9,9);
	return 0;
}

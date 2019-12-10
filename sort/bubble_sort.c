#include <stdio.h>

void bubble_sort(int *num, int len)
{
	int i = 0, j=0;
	int temp = 0;

	for(i = 0; i < len; i++)
	{
		for(j = 0; j < len-1-i; j++)
		{
			if(num[j] > num[j+1])
			{
				temp = num[j];
				num[j] = num[j+1];
				num[j+1] = temp; 
			}
		}
	}
}


int main(int argc, char const *argv[])
{
	int i = 0;
	int a[6] = {5,2,4,1,6,3};
	bubble_sort(a, 6);

	for(i=0; i < 6; i++)
		printf("%d ", a[i]);
	printf("\n");

	return 0;
}
#include <stdio.h>

void insert_sort(int *num, int len)
{
	int i = 0, j = 0;
	int temp = 0;

	for(i = 0; i < len; i++)
	{
		if(num[i] < num[i-1])
		{
			temp = num[i];
			for(j = i-1; j >=0; j--)
			{
				if(num[j] > temp)
					num[j+1] = num[j];
				else
					break;
			}

			num[j+1] = temp;
		}
	}
}


int main(int argc, char const *argv[])
{
	int i = 0;
	int a[6] = {5,2,4,1,6,3};
	insert_sort(a, 6);

	for(i=0; i < 6; i++)
		printf("%d ", a[i]);
	printf("\n");

	return 0;
}
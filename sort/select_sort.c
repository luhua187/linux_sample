#include <stdio.h>


void select_sort(int *num, int len)
{
	int i =0, j = 0, temp=0;
	int index = 0;

	for(i = 0; i< len-1; i++)
	{
		index = i;

		for(j = i+1; j < len; j++)
		{
			if(num[j] < num[index])
				index = j;
		}

		temp = num[index];
		num[index] = num[i];
		num[i] = temp;
	}

}



int main(int argc, char const *argv[])
{
	int i = 0;
	int a[6] = {5,2,4,1,6,3};
	select_sort(a,  6);

	for(i=0; i < 6; i++)
		printf("%d ", a[i]);
	printf("\n");

	return 0;
}
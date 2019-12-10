// 平均情况下：n*log n

#include <stdio.h>

void quick_sort(int *num, int left, int right)
{
	if(left < right)
	{
		int i=left, j = right, x=num[i];
		while(i < j)
		{
			while(i < j && num[j]>=x)
				j--;
			if(i < j)
				num[i] = num[j],i++;

			while(i<j && num[i] < x)
				i++;
			if(i < j)
				num[j]=num[i],j--;
		}

		num[i] = x;
		quick_sort(num, left, i-1);
		quick_sort(num, i+1, right);

	}
}



int main(int argc, char const *argv[])
{
	int i = 0;
	int a[6] = {5,2,4,1,6,3};
	quick_sort(a, 0, 5);

	for(i=0; i < 6; i++)
		printf("%d ", a[i]);
	printf("\n");

	return 0;
}
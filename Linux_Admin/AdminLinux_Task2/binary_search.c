// This is my first line with vim

#include <stdio.h>

int binarySearch(int arr[], int low, int high, int data)
{
	while(low <= high)
	{
		int mid = low + (high - low) / 2;

		//check whether data is in mid position or not
		if(arr[mid] == data)
		{
			return mid;
		}

		if(arr[mid] < data)
		{
			low = mid + 1;
		}
		else
		{
			high = mid - 1;
		}
	}
	return -1;
}



int main()
{
	int arr[] = {4, 6, 8, 9, 11, 23, 30};

	int n = sizeof(arr) / sizeof(arr[0]);

	int data = 23;

	int res = binarySearch(arr, 0, n - 1, data);

	if(res == -1)
	{
		printf("Element is not in the array\n");

	}
	else
	{
		printf("Element is exist and located at index %d\n", res);
	}

}

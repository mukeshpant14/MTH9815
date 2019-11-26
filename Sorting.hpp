#include <iostream>

template <typename T>
class Sort
{
public:
	virtual void sort(T* arr, int n) = 0;
	void print(T* arr, int n)
	{
		for (int i = 0; i<n; i++)
			std::cout << arr[i] << ", ";

		std::cout << std::endl;
	}

protected:
	void swap(T* arr, int i, int j)
	{
		T temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
	}
};

template <typename T>
class BubbleSort : public Sort<T>
{
public:
	void sort(T* arr, int n)
	{
		for (int i = 0; i < n - 1; i++)
			for (int j = 0; j < n - i - 1; j++)
				if (arr[j] > arr[j + 1])
					swap(arr, j, j + 1);
	}
};

template <typename T>
class SelectionSort : public Sort<T>
{
public:
	void sort(T* arr, int n)
	{
		for (int i = 0; i < n - 1; i++)
		{
			int min_index = i;
			for (int j = i+1; j < n; j++)
				if (arr[j] < arr[min_index])
					min_index = j;
			
			if(i != min_index)
				swap(arr, i, min_index);
		}
	}
};

template <typename T>
class InsertionSort : public Sort<T>
{
public:
	void sort(T* arr, int n)
	{
		for (int i = 0; i < n-1; i++)
		{
			// pick first element from right side
			T next_value = arr[i + 1];

			// find index where to next_value should be inserted
			int index=i+1;
			for(int j=0; j <= i; j++)
				if (arr[j] > next_value)
				{
					index = j;
					break;
				}

			// move all elements by one place starting from 'index' 
			for (int k = i; k >= index; k--)
				arr[k + 1] = arr[k];

			arr[index] = next_value;
		}
	}
};

template <typename T>
class MergeSort : public Sort<T>
{
public:
	void sort(T* arr, int n)
	{
		mergeSort(arr, 0, n-1);
	}

	void mergeSort(T* arr, int l, int r)
	{
		if (l >= r)
			return;

		int m = l + (r-l)/2;
		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);

		merge(arr, l, m, r);
	}

	// arr[l..m] --> sorted array
	// arr[m+1..r] --> sorted array
	void merge(T* arr, int l, int m, int r)
	{
		if (arr[m] < arr[m + 1])
			return;

		// copy
		int n1 = m - l + 1;
		int n2 = r - m;
		T* left = new T[n1];
		T* right = new T[n2];

		for (int i = 0; i < n1; i++)
			left[i] = arr[l+i];
		for (int i = 0; i < n2; i++)
			right[i] = arr[m + i + 1];

		// traverse from left to right index
		int i = 0, j = 0, k = l;
		while (i < n1 && j < n2)
		{
			if (left[i] <= right[j])
				arr[k++] = left[i++];
			else
				arr[k++] = right[j++];
		}

		while (i < n1) // copy remaining from left array
			arr[k++] = left[i++];
		while (j < n2) // copy remaining from right array
			arr[k++] = right[j++];

		delete left;
		delete right;
	}
};

template <typename T>
class HeapSort : public Sort<T>
{
public:
	void sort(T* arr, int n)
	{
		// build heap
		for (int i = n / 2 - 1; i >= 0; i--)
			heapify(arr, n, i);

		for (int i = n - 1; i >= 0; i--)
		{
			swap(arr, 0, i);
			heapify(arr, i, 0);
		}
	}

	// max heap
	void heapify(T* arr, int n, int i)
	{
		int left = 2 * i + 1;
		int right = 2 * i + 2;

		int smallest = i;
		if (left < n && arr[left] > arr[smallest])
			smallest = left;

		if (right < n && arr[right] > arr[smallest])
			smallest = right;

		if (smallest != i)
		{
			swap(arr, i, smallest);
			heapify(arr, n, smallest);
		}
	}
};

template <typename T>
class QuickSort : public Sort<T>
{
public:
	void sort(T* arr, int n)
	{
		quickSort(arr, 0, n - 1);
	}

	void quickSort(T* arr, int low, int high)
	{
		if (low < high)
		{
			int pi = partition(arr, low, high);

			quickSort(arr, low, pi-1);
			quickSort(arr, pi + 1, high);
		}
	}

	int partition(T* arr, int low, int high)
	{
		int pivot = arr[high]; // pivot  
		int i = (low - 1); // Index of smaller element  

		for (int j = low; j < high; j++)
		{
			// If current element is smaller than the pivot  
			if (arr[j] < pivot)
			{
				i++; // increment index of smaller element  
				swap(arr, i, j);
			}
		}
		swap(arr, i + 1, high);
		return (i + 1);
	}
};

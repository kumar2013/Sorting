/**
 * Program for various sorting algorithms
 * with profiler to record compute time,
 * number of Comparison and assignment
 * operations performed, written by mcs10kai
**/

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
 
using namespace std;
 
long arraySize = 1000;
const long max_arraySize = 300001;
int data[max_arraySize];
int temp[max_arraySize];
ofstream outputFile;
long long qComparison = 0, qCopies = 0;
long long rqComparison = 0, rqCopies = 0;
long long mComparison = 0, mCopies = 0;

void load_data()
{
	srand(time(NULL));
	for(long k = 0; k < arraySize; k++)
	{
		long randNumber = rand();
		randNumber *= RAND_MAX;
		randNumber += rand();
		randNumber %= 200000;
		data[k] = randNumber;
	}
}

void bubble_sort()
{
    int temp; 
	long long copies=0, comparison=0;
    for(long i = 0; i < arraySize; i++)
    {
        for(long j = 0; j < arraySize-1; j++)
        {
			if (data[j] > data[j+1])
            {
                temp        = data[j];
				copies++;
                data[j]     = data[j+1];
				copies++;
                data[j+1]   = temp;
				copies++;
            }
			comparison++;
        }
    }
	outputFile << "\nComparisons\t: " << comparison << '\n';
	cout << "Comparisons\t: " << comparison << '\n';
	outputFile << "Assignments\t: " << copies << '\n';
	cout << "Assignments\t: " << copies << '\n';
}

void mod_bubble_sort()
{
    int temp, flag = 0; 
	long long copies = 0, comparison = 0;
    for(long i = 0; i < arraySize; i++)
    {
        for(long j = 0; j < arraySize-i-1; j++)
        {
			if (data[j] > data[j+1])
            {
                temp        = data[j];
				copies++;
                data[j]     = data[j+1];
				copies++;
                data[j+1]   = temp;
				copies++;
				flag = 1;
            }
			comparison++;
        }
		if(flag == 0)
		{
			break;
		}
    }
	outputFile << "\nComparisons\t: " << comparison << '\n';
	cout << "Comparisons\t: " << comparison << '\n';
	outputFile << "Assignments\t: " << copies << '\n';
	cout << "Assignments\t: " << copies << '\n';
}
 
void selection_sort()
{
	long long copies=0, comparison=0;
	for(long i=0; i<arraySize-1; i++)
	{
		int iMin = i;
		for(int j=i+1; j<arraySize; j++)
		{
			if(data[j] < data[iMin])
			{
				iMin=j;
			}
			comparison++;
		}
		int temp = data[i];
		copies++;
		data[i] = data[iMin];
		copies++;
		data[iMin] = temp;
		copies++;
	}
	outputFile << "\nComparisons\t: " << comparison << '\n';
	cout << "Comparisons\t: " << comparison << '\n';
	outputFile << "Assignments\t: " << copies << '\n';
	cout << "Assignments\t: " << copies << '\n';
}

void insertion_sort()
{
    int temp; 
	long long copies=0, comparison=0;
    for(long i = 1; i < arraySize; i++)
    {
        temp = data[i];
		copies++;
        long j;
        for(j = i-1; j >= 0 && data[j] > temp; j--, comparison++)
        {
            data[j+1] = data[j];
			copies++;
        }
        data[j+1] = temp;
		copies++;
    }
	outputFile << "\nComparisons\t: " << comparison << '\n';
	cout << "Comparisons\t: " << comparison << '\n';
	outputFile << "Assignments\t: " << copies << '\n';
	cout << "Assignments\t: " << copies << '\n';
}

int partition (int start, int end)
{
	int pivot = data[end];
	qCopies++;
	int partitionIndex = start;
	for(int i = start; i < end; i++)
	{
		qComparison++;
		if(data[i] <= pivot)
		{
			swap(data[i], data[partitionIndex]);
			qCopies++;
			partitionIndex++;
		}
	}
	swap(data[partitionIndex], data[end]);
	qCopies++;
	return partitionIndex;
}

void quick_sort (int start, int end)
{
	if(start < end)
	{
		int partitionIndex = partition(start,end);
		quick_sort(start, partitionIndex-1);
		quick_sort(partitionIndex+1, end);
	}
}

int rand_partition (int start, int end)
{
	int pivot = data[start + (rand() % (end - start + 1))];
	rqCopies++;
	int partitionIndex = start;
	for(int i = start; i < end; i++, rqComparison++)
	{
		//rqComparison++;
		if(data[i] <= pivot)
		{
			swap(data[i], data[partitionIndex]);
			rqCopies++;
			partitionIndex++;
		}
	}
	swap(data[partitionIndex], data[end]);
	rqCopies++;
	return partitionIndex;
}

void rand_quick_sort (int start, int end)
{
	if(start < end)
	{
		int partitionIndex = rand_partition(start,end);
		rand_quick_sort(start, partitionIndex-1);
		rand_quick_sort(partitionIndex+1, end);
	}
}

void merge(int low, int pivot, int high)
{
    int h,i,j,k;
    h = low;
    i = low;
    j = pivot+1;

    while((h <= pivot)&&(j <= high)&&(mComparison++))
    {
        if(data[h] <= data[j])
        {
            temp[i] = data[h];
			mCopies++;
            h++;
        }
        else
        {
            temp[i] = data[j];
			mCopies++;
            j++;
        }
        i++;
    }
    if((h > pivot)&&(mComparison++))
    {
        for(k = j; k <= high; k++)
        {
            temp[i] = data[k];
			mCopies++;
            i++;
        }
    }
    else
    {
        for(k = h; k <= pivot; k++)
        {
            temp[i] = data[k];
			mCopies++;
            i++;
        }
    }
    for(k = low; k<=high; k++)
	{
		data[k] = temp[k];
		mCopies++;
	}
}

void merge_sort(int low, int high)
{
    int pivot;
    if(low < high)
    {
        pivot = (low+high)/2;
        merge_sort(low,pivot);
        merge_sort(pivot+1,high);
        merge(low,pivot,high);
    }
}

void shift_down(int low, int high)
{
    int root = low;
    while ((root*2)+1 <= high)
    {
        int leftChild = (root * 2) + 1;
        int rightChild = leftChild + 1;
        int swapIndex = root;
        if (data[swapIndex] < data[leftChild])
        {
            swapIndex = leftChild;
        }
        if ((rightChild <= high) && (data[swapIndex] < data[rightChild]))
        {
            swapIndex = rightChild;
        }
        if (swapIndex != root)
        {
            int temp = data[root];
            data[root] = data[swapIndex];
            data[swapIndex] = temp;
            root = swapIndex;
        }
        else
        {
            break;
        }
    }
    return;
}

void heapify(int low, int high)
{
    int midIndex = (high - low -1)/2;
    while (midIndex >= 0)
    {
        shift_down(midIndex, high);
        --midIndex;
    }
    return;
}

void heap_sort(int size)
{
	int copies = 0, comparison = 0;
    heapify(0, size-1);
    int high = size - 1;
    while (high > 0)
    {
		int temp = data[high];
		copies++;
        data[high] = data[0];
		copies++;
        data[0] = temp;
		copies++;
        --high;
        shift_down(0, high);
		comparison++;
    }
	comparison++;
	outputFile << "\nComparisons\t: " << comparison << '\n';
	cout << "Comparisons\t: " << comparison << '\n';
	outputFile << "Assignments\t: " << copies << '\n';
	cout << "Assignments\t: " << copies << '\n';
    return;
}

int main()
{
    double startTime, endTime;
	
	outputFile.open("computeBasedData.txt");
	outputFile << "Profiler for different Sorting Algorithms" << '\n';
 
    for (arraySize = 1000; arraySize < max_arraySize; )
    {
		outputFile << "--------------------------------" << '\n';
        outputFile << "\n    Array Size\t: " << arraySize << '\n';
		outputFile << "--------------------------------" << '\n';
		cout << "--------------------------------" << '\n';
        cout << "\n    Array Size\t: " << arraySize << '\n';
		cout << "--------------------------------" << '\n';
 
        load_data();
		outputFile << "##### BUBBLE SORT #####" << '\n';
		cout << "##### BUBBLE SORT #####" << '\n';
        startTime = clock();
        bubble_sort();
        endTime = clock();
        outputFile << "Compute Time\t: " << (endTime - startTime)/CLK_TCK << " sec\n";
		cout << "Compute Time\t: " << (endTime - startTime)/CLK_TCK << " sec\n";

		
		load_data();
		outputFile << "\n##### MOD BUBBLE SORT #####" << '\n';
		cout << "\n##### MOD BUBBLE SORT #####" << '\n';
        startTime = clock();
        mod_bubble_sort();
        endTime = clock();
        outputFile << "Compute Time\t: " << (endTime - startTime)/CLK_TCK << " sec\n";
		cout << "Compute Time\t: " << (endTime - startTime)/CLK_TCK << " sec\n";


		load_data();
		outputFile << "\n##### SELECTION SORT #####" << '\n';
		cout << "\n##### SELECTION SORT #####" << '\n';
        startTime = clock();
        selection_sort();
        endTime = clock();
        outputFile << "Compute Time\t: " << (endTime - startTime)/CLK_TCK << " sec\n";
		cout << "Compute Time\t: " << (endTime - startTime)/CLK_TCK << " sec\n";
		

        load_data();
		outputFile << "\n##### INSERTION SORT #####" << '\n';
		cout << "\n##### INSERTION SORT #####" << '\n';
        startTime = clock();
        insertion_sort();
        endTime = clock();
        outputFile << "Compute Time\t: " << (endTime - startTime)/CLK_TCK << " sec\n";
		cout << "Compute Time\t: " << (endTime - startTime)/CLK_TCK << " sec\n";


		load_data();
		outputFile << "\n##### QUICK SORT #####" << '\n';
		cout << "\n##### QUICK SORT #####" << '\n';
		startTime = clock();
		quick_sort(0, arraySize-1);
		endTime = clock();
		outputFile << "\nComparisons\t: " << qComparison << '\n';
		cout << "Comparisons\t: " << qComparison << '\n';
		outputFile << "Assignments\t: " << qCopies << '\n';
		cout << "Assignments\t: " << qCopies << '\n';
		outputFile << "Compute Time\t: " << (endTime - startTime)/CLK_TCK << " sec\n";
		cout << "Compute Time\t: " << (endTime - startTime)/CLK_TCK << " sec\n";
		qComparison = 0;
		qCopies = 0;


		load_data();
		outputFile << "\n##### RAND QUICK SORT #####" << '\n';
		cout << "\n##### RAND QUICK SORT #####" << '\n';
		startTime = clock();
		rand_quick_sort(0, arraySize-1);
		endTime = clock();
		outputFile << "\nComparisons\t: " << rqComparison << '\n';
		cout << "Comparisons\t: " << rqComparison << '\n';
		outputFile << "Assignments\t: " << rqCopies << '\n';
		cout << "Assignments\t: " << rqCopies << '\n';
		outputFile << "Compute Time\t: " << (endTime - startTime)/CLK_TCK << " sec\n";
		cout << "Compute Time\t: " << (endTime - startTime)/CLK_TCK << " sec\n";
		rqComparison = 0;
		rqCopies = 0;


		load_data();
		outputFile << "\n##### MERGE SORT #####" << '\n';
		cout << "\n##### MERGE SORT #####" << '\n';
		startTime = clock();
		merge_sort(0, arraySize-1);
		endTime = clock();
		outputFile << "\nComparisons\t: " << mComparison << '\n';
		cout << "Comparisons\t: " << mComparison << '\n';
		outputFile << "Assignments\t: " << mCopies << '\n';
		cout << "Assignments\t: " << mCopies << '\n';
		outputFile << "Compute Time\t: " << (endTime - startTime)/CLK_TCK << " sec\n";
		cout << "Compute Time\t: " << (endTime - startTime)/CLK_TCK << " sec\n";
		mComparison = 0;
		mCopies = 0;
		

		load_data();
		outputFile << "\n##### HEAP SORT #####" << '\n';
		cout << "\n##### HEAP SORT #####" << '\n';
        startTime = clock();
        heap_sort(arraySize);
        endTime = clock();
        outputFile << "Compute Time\t: " << (endTime - startTime)/CLK_TCK << " sec\n";
		cout << "Compute Time\t: " << (endTime - startTime)/CLK_TCK << " sec\n";

		
        switch (arraySize)
        {
        case 1000 :
            arraySize = 2000;
            break;
		case 2000 :
            arraySize = 3000;
			break;
		case 3000 :
            arraySize = 5000;
			break;
        case 5000 :
            arraySize = 10000;
            break;
        case 10000 :
            arraySize = 20000;
            break;
		case 20000 :
			arraySize = 30000;
			break;
		case 30000 :
			arraySize = 50000;
			break;
		case 50000 :
			arraySize = 100000;
			break;
		case 100000 :
			arraySize = 200000;
			break;
		case 200000 :
			arraySize = 300000;
			break;
		case 300000 :
			arraySize = 400000;
			break;
	   }
    }
	outputFile.close();
    return 0;
}

	
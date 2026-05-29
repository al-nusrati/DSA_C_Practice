#include <iostream>
using namespace std;

void printArr(int arr[], int size) {
	for (int i = 0; i < size; i++)
		cout << arr[i] << " ";
}

int RndNoInRange(int rgStart, int rgEnd)
{
	int offset = rand() % (rgEnd - rgStart + 1);
	return rgStart + offset;
}

bool NumberExistsInArr(int arr[], int size, int num) {
	for (int i = 0; i < size; i++)
	{
		if (arr[i] == num)
			return true;
	}
	return false;
}

void fillArrWithRndNumbers(int arr[], int size, bool isDuplAllowed = false, int strt = 1, int endP = 100) {
	for (int i = 0; i < size; i++) {
		int randNUM;


		//---------------------------
		// get good random number
		//---------------------------
		if (isDuplAllowed) {
			while (true)
			{
				randNUM = RndNoInRange(strt, endP);

				if (NumberExistsInArr(arr, i, randNUM) == false)
					break;
			}
		}
		else {
			randNUM = RndNoInRange(strt, endP);
		}

		/*
				while (true)
				{
					randNUM = RndNoInRange(strt, endP);
					if (isDuplAllowed) break;
					else if (!NumberExistsInArr(arr, i, randNUM)) break;
				}
		*/

		//---------------------------
		// save good random number
		//---------------------------
		arr[i] = randNUM;
	}
}

void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

void bubbleSort_singlePass(int arr[], int iStart, int iEnd) {
	for (int i = iStart; i <= iEnd; i++) {
		if (arr[i] > arr[i + 1]) {
			swap(arr[i], arr[i + 1]);
		}
	}
}

void selectionSort_singlePass(int arr[], int iStart, int iEnd) {
	int minIndex = iStart;
	// find index of smallest number in the range [iStart+1, iEnd]
	for (int i = iStart + 1; i <= iEnd; i++) {
		if (arr[i] < arr[minIndex]) {
			minIndex = i;
		}
	}
	// swap smallest number with the first number in the range
	swap(arr[iStart], arr[minIndex]);
}

void insertionSort_singlePass(int arr[], int iStart) {

	int i = iStart;
	// save [iStart]
	int val = arr[i];

	// shift values till required insert position
	while (arr[i - 1] > val)
	{
		arr[i] = arr[i - 1];
		i--;
	}

	// insert value
	arr[i] = val;

}

int linearSearch(int arr[],int iStart, int iEnd, int val){
	// if value is found, return index, else return -1
	for (int i = 0; i < iEnd; i++) {
		if(arr[i] == val)	return i;
	}
	

}

int main()
{
	srand(time(0));	// random seed once
	int size = 10;

	int arr[10] = { 10,14,19,26,27,31,33,35,42,46};
	cout << "Unsorted array: ";
	printArr(arr, size);

	cout << "\n\n";

	////--------Bubble Sort----------------
	//for (int i = 0; i < size; i++) {
	//	bubbleSort_singlePass(arr, 0, 5);
	//	cout << "Pass " << i+1 << ": ";
	//	printArr(arr, size);
	//	cout << endl;
	//}

	////--------Selection Sort----------------
	//for (int i = 0; i < size-1; i++) {
	//	selectionSort_singlePass(arr, i, size-1);
	//	cout << "Pass " << i + 1 << ": ";
	//	printArr(arr, size);
	//	cout << endl;
	//}

	////--------Insertion Sort----------------
	//for (int i = 1; i < size; i++) {
	//	insertionSort_singlePass(arr, i);
	//	cout << "Pass " << i << ": ";
	//	printArr(arr, size);
	//	cout << endl;
	//}

	//fillArrWithRndNumbers(arr, size);


	int temp = linearSearch(arr, 0, size - 1, 42);
	if (temp != -1) {
		cout << "Value found at index: " << temp;
	}
	else {
		cout << "Value not found in array.";
	}
	































	system("pause>0");
	return 0;
}


//===========================================
//++++--------EXTRA CODE SNIPPETS--------++++
//===========================================


// -----------------------
// Insertion Sort single pass alternative
// -----------------------
//while (arr[i - 1] > arr[i]) {
//	int temp = arr[i];		// save value to insert
//	arr[i] = arr[i - 1];
//	arr[i - 1] = temp;
//	i--; 
//}
////-----------------------
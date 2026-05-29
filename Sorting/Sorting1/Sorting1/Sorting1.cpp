//#include <iostream>
//using namespace std;
//
//void printArr(int arr[], int size) {
//	for (int i = 0; i < size; i++)
//		cout << arr[i] << " ";
//}
//
//int RndNoInRange(int rgStart, int rgEnd)
//{
//	int offset = rand() % (rgEnd - rgStart + 1);
//	return rgStart + offset;
//}
//
//bool NumberExistsInArr(int arr[], int size, int num) {	
//	for (int i = 0; i < size ; i++)
//	{
//		if (arr[i] == num)
//			return true;
//	}
//	return false;
//}
//
//void fillArrWithRndNumbers(int arr[], int size, bool isDuplAllowed = false, int strt = 1, int endP = 100) {
//	for (int i = 0; i < size; i++) {
//		int randNUM;
//
//
//		//---------------------------
//		// get good random number
//		//---------------------------
//		if (isDuplAllowed) {
//			while (true)
//			{
//				randNUM = RndNoInRange(strt, endP);
//		
//				if (NumberExistsInArr(arr, i, randNUM) == false)
//					break;
//			}
//		}
//		else {
//			randNUM = RndNoInRange(strt, endP);
//		}
//
///*
//		while (true)
//		{
//			randNUM = RndNoInRange(strt, endP);
//			if (isDuplAllowed) break;
//			else if (!NumberExistsInArr(arr, i, randNUM)) break;
//		}
//*/
//
//		//---------------------------
//		// save good random number
//		//---------------------------
//		arr[i] = randNUM;
//	}
//}
//
//void swap(int& a, int& b) {
//	int temp = a;
//	a = b;
//	b = temp;
//}
//
//void bubbleSort_singlePass(int arr[], int iStart, int iEnd) {
//	for (int i = iStart; i <= iEnd; i++) {
//		if (arr[i] > arr[i + 1]) {
//			swap(arr[i], arr[i + 1]);
//		}
//	}
//}
//
//void selectionSort_singlePass(int arr[], int iStart, int iEnd) {
//	int minIndex = iStart;
//	// find index of smallest number in the range [iStart+1, iEnd]
//	for (int i = iStart + 1; i <= iEnd; i++) {
//		if (arr[i] < arr[minIndex]) {
//			minIndex = i;
//		}
//	}
//	// swap smallest number with the first number in the range
//	swap(arr[iStart], arr[minIndex]);
//}
//
//void insertionSort_singlePass(int arr[], int iStart) {
//
//	int i = iStart;
//	// save [iStart]
//	int val = arr[i];
//
//	// shift values till required insert position
//	while (arr[i - 1] > val)
//	{
//		arr[i] = arr[i - 1];
//		i--;
//	}
//
//	// insert value
//	arr[i] = val;
//
//}
//
//int main()
//{
//	srand(time(0));	// random seed once
//	int size = 7;
//
//	int arr[7] = { 2, 8, 5, 3, 9, 4, 1 };
//	cout << "Unsorted array: ";
//	printArr(arr, size);
//
//	cout << "\n\n";
//
//	////--------Bubble Sort----------------
//	//for (int i = 0; i < size; i++) {
//	//	bubbleSort_singlePass(arr, 0, 5);
//	//	cout << "Pass " << i+1 << ": ";
//	//	printArr(arr, size);
//	//	cout << endl;
//	//}
//
//	////--------Selection Sort----------------
//	//for (int i = 0; i < size-1; i++) {
//	//	selectionSort_singlePass(arr, i, size-1);
//	//	cout << "Pass " << i + 1 << ": ";
//	//	printArr(arr, size);
//	//	cout << endl;
//	//}
//
//	////--------Insertion Sort----------------
//	for (int i = 1; i < size; i++) {
//		insertionSort_singlePass(arr, i);
//		cout << "Pass " << i << ": ";
//		printArr(arr, size);
//		cout << endl;
//	}
//
//	//fillArrWithRndNumbers(arr, size);
//	
//
//	system("pause>0");
//	return 0;
//}
//
//
////===========================================
////++++--------EXTRA CODE SNIPPETS--------++++
////===========================================
//
//
//// -----------------------
//// Insertion Sort single pass alternative
//// -----------------------
////while (arr[i - 1] > arr[i]) {
////	int temp = arr[i];		// save value to insert
////	arr[i] = arr[i - 1];
////	arr[i - 1] = temp;
////	i--; 
////}
//////-----------------------
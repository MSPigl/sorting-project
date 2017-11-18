/*
 * Header for serial-sorting-c
 */
 
void bubbleSort(int size, int* array);

void merge_up(int arr[], int n);

void merge_down(int arr[], int n);
 
void bitonicSort(int arr[], int size);

void swap(int* a, int* b);

int partition (int arr[], int low, int high);

void quickSort(int arr[], int low, int high);

void merge(int arr[], int left, int mid, int right);

void mergeSort(int arr[], int left, int right);

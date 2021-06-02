/*
 * hw12-sorting-hashing.c
 *
 *  Created on: May 22, 2021
 *
 *  Homework 12: Sorting & Hashing
 *  Department of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */		// 배열의 최대 크기를 13으로 지정
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);			// 배열을 초기화하는 함수
int freeArray(int *a);				// 배열에 할당된 메모리를 해제하는 함수
void printArray(int *a);			// 배열을 출력하는 함수

int selectionSort(int *a);			// 선택 정렬을 하게 해주는 함수
int insertionSort(int *a);			// 삽입 정렬을 하게 해주는 함수
int bubbleSort(int *a);				// 버블 정렬을 하게 해주는 함수
int shellSort(int *a);				// 셸 정렬을 하게 해주는 함수
/* recursive function으로 구현 */
int quickSort(int *a, int n);		// 퀵 정렬을 하게 해주는 함수


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));

	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&array);
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a)						// 배열을 초기화하는 함수
{
	int *temp = NULL;

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else
		temp = *a;

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

int freeArray(int *a)		// 할당된 배열을 메모리에서 해제하는 함수
{
	if(a != NULL)
		free(a);
	return 0;
}

void printArray(int *a)		// 배열을 출력하는 함수
{
	if (a == NULL) {
		printf("nothing to print.\n");
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)		// 배열의 인덱스를 출력
		printf("a[%02d] ", i);
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)		// 배열의 값을 출력
		printf("%5d ", a[i]);
	printf("\n");
}


int selectionSort(int *a)			// 선택 정렬을 실행하는 함수
{
	int min;						// 선택할 작은 값을 min이라는 변수로 선언
	int minindex;					// min의 인덱스 값 변수를 minindex로 선언
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);					// 정렬하기 전의 배열 출력

	for (i = 0; i < MAX_ARRAY_SIZE; i++)		// 13의 크기만큼 반복
	{
		minindex = i;				// 기준 위치의 인덱스 i를 minindex에 설정
		min = a[i];					// 기준 위치의 값 a[i]를 min에 설정
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)	// i+1번의 배열부터 마지막 배열까지 비교를 한다. 
		{
			if (min > a[j])
			{
				min = a[j];						// 가장 작은 a[j]를 min에 설정
				minindex = j;					// 가장 작은 값을 인덱스를 minindex에 설정
			}
		}
		a[minindex] = a[i];			// a[i]를 a[minindex]로 설정
		a[i] = min;					// min을 a[i]로 설정
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);					// 정렬된 배열을 출력
	return 0;
}

int insertionSort(int *a)			// 삽입 정렬을 하게 해주는 함수
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);					// 정렬하기 전의 배열 출력

	for(i = 1; i < MAX_ARRAY_SIZE; i++)		// 13 크기 만큼 반복
	{
		t = a[i];					// 아직 정렬하지 않은 배열의 첫번째 원소 a[i]를 t에 저장한다.
		j = i;						// 정렬 대상의 인덱스를 j에 저장한다.
		while (a[j-1] > t && j > 0)	// 정렬된 배열의 마지막 배열인 a[j-1]부터 정렬 대상의 원소가 저장된 t와 비교하여 a[j-1] < t < a[j]인 j를 찾을 때까지 반복
		{
			a[j] = a[j-1];			// a[j-1]을 a[j]에 설정
			j--;					// 인덱스를 1을 줄인다.
		}
		a[j] = t;					// a[j] 위치에 정렬 대상 배열t를 저장한다.
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);					// 삽입 정렬된 배열을 출력한다.

	return 0;
}

int bubbleSort(int *a)				// 버블 정렬을 하게 해주는 함수
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);					// 정렬하기 전의 배열 출력

	for(i = 0; i < MAX_ARRAY_SIZE; i++)		// 13 크기 만큼 반복
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++)	// 13 크기 만큼 반복
		{
			if (a[j-1] > a[j])		// 비교하려는 a[j]와 그 전 배열을 비교하여 전 배열값이 크다면 두 값을 변경
			{
				t = a[j-1];			// a[j-1]을 t에 저장
				a[j-1] = a[j];		// a[j]를 a[j-1]에 저장
				a[j] = t;			// t를 a[j]에 저장
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);					// 버블 정렬된 배열을 출력

	return 0;
}

int shellSort(int *a)
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)
	{
		for (i = 0; i < h; i++)
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)
			{
				v = a[j];
				k = j;
				while (k > h-1 && a[k-h] > v)
				{
					a[k] = a[k-h];
					k -= h;
				}
				a[k] = v;
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int quickSort(int *a, int n)
{
	int v, t;
	int i, j;

	if (n > 1)
	{
		v = a[n-1];
		i = -1;
		j = n - 1;

		while(1)
		{
			while(a[++i] < v);
			while(a[--j] > v);

			if (i >= j) break;
			t = a[i];
			a[i] = a[j];
			a[j] = t;
		}
		t = a[i];
		a[i] = a[n-1];
		a[n-1] = t;

		quickSort(a, i);
		quickSort(a+i+1, n-i-1);
	}


	return 0;
}

int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE;
}

int hashing(int *a, int **ht)
{
	int *hashtable = NULL;

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1;

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];
		hashcode = hashCode(key);
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1)
		{
			hashtable[hashcode] = key;
		} else 	{

			index = hashcode;

			while(hashtable[index] != -1)
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key;
		}
	}

	return 0;
}

int search(int *ht, int key)
{
	int index = hashCode(key);

	if(ht[index] == key)
		return index;

	while(ht[++index] != key)
	{
		index = index % MAX_HASH_TABLE_SIZE;
	}
	return index;
}



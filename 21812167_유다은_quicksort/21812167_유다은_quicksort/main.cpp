#include <iostream>
#include <time.h>
#include <Windows.h>


using namespace std;

#define SIZE 256000 //퀵정렬 실험을 진행할 배열 사이즈의 크기
int dataarray[SIZE] = { 0 }; //전역변수로 선언: 지역변수로 선언하면 스택 값이 초과될수도 있다.

void fill(int dataarray);//배열 data의 값을 0부터 1씩 차례로 증가하는 값으로 채워넣는 함수
void scramble(int dataarray[]); //data 배열 내의 값들을 무작위로 섞는 함수
void validata(int* dataarray);//data 배열을 정렬한 후에 값이 차례대로 정렬이 되었는지 확인하는 함수
void quicksort(int low, int high,int dataarray[]);//data 배열의 값들을 오름차순으로 정렬하는 함수
int partition(int low, int high, int dataarray[], int pivotpoint);//퀵정렬을 하기 위해서 분할 하는 함수
void quickquicksort(int low, int high, int* dataarray);//data 배열의 값들을 오름차순으로 정렬하는 개선된 함수
int improvepartition(int low, int high, int dataarray[], int pivotpoint);//퀵정렬을 하기 위해서 분할 하는 개선된 함수

int main()
{
	double elapsedTime;

	fill(SIZE);

	cout << "\n1. 안 섞은 배열의 퀵정렬을 실시합니다.(최악의 경우)" << endl;
	validata(dataarray);
	unsigned long startTime = clock();
	quicksort(0, SIZE - 1, dataarray);
	unsigned long endTime = clock();
	elapsedTime = endTime - startTime;
	cout<<"-> 안 섞은 배열의 퀵정렬 소요 시간(최악의 경우) : "<< elapsedTime/CLOCKS_PER_SEC;
	validata(dataarray);

	cout << ". . . .\n2. 섞은 배열의 퀵정렬을 실시합니다." << endl;
	scramble(dataarray); validata(dataarray);
	startTime = clock();
	quicksort(0, SIZE - 1, dataarray);
	endTime = clock();
	elapsedTime = endTime - startTime;
	cout << "-> 섞은 배열의 퀵정렬 소요 시간 : " << elapsedTime / CLOCKS_PER_SEC;
	validata(dataarray);
	
	cout << ". . . .\n3. 섞지 않은 배열의 개선된 퀵정렬을 실시합니다." << endl;
	validata(dataarray);
	startTime = clock();
	quickquicksort(0, SIZE - 1, dataarray);
	endTime = clock();
	elapsedTime = endTime - startTime;
	cout << "-> 섞지 않은 배열의 개선된 퀵정렬 소요 시간 : " << elapsedTime / CLOCKS_PER_SEC;
	validata(dataarray);

	cout << ". . . .\n4. 섞은 배열의 개선된 퀵정렬을 실시합니다." << endl;
	scramble(dataarray); validata(dataarray);
	startTime = clock();
	quickquicksort(0, SIZE - 1, dataarray);
	endTime = clock();
	elapsedTime = endTime - startTime;
	cout << "-> 섞은 배열의 개선된 퀵정렬 소요 시간 : " << elapsedTime / CLOCKS_PER_SEC;
	validata(dataarray);

	return 0;
}
void fill(int num) //배열 data의 값을 0부터 1씩 차례로 증가하는 값으로 채워넣는 함수
{
	for (int i = 0; i < num; i++) //배열 data에 0부터 1씩 증가하는 값으로 채운다. 
	{
		dataarray[i] = i;
	}
}
void scramble(int dataarray[])//data 배열 내의 값들을 무작위로 섞는 함수
{
	int temp, randnum;
	for (int i = 0; i < SIZE; i++)
	{
		randnum = rand() % SIZE; //난수생성
		temp = dataarray[i];
		dataarray[i] = dataarray[randnum];
		dataarray[randnum] = temp; //스와핑해주면서 값을 섞는다.
	}
}
void validata(int* dataarray) //data 배열을 정렬한 후에 값이 차례대로 정렬이 되었는지 확인하는 함수
//배열을 섞고 난 후에 제대로 섞였는지도 확인해준다.
{
	int check;
	for (int i = 0; i < SIZE; i++) {
		if (dataarray[i] == i) {
			check = 1; //True값: data[i]값이 1씩 증가되는 값이 맞으면 
		}
		else {
			check = 0; //False값: data[i]값이 1씩 증가되는 값이 아니라면 
		}

	}
	if (check == 1) { //제대로 정렬이 되었으면 check값은 1이 된다.
		cout << "\ndata 배열의 정렬이 완료되었습니다." << endl;
	}
	else {//제대로 정렬이 되지 않았으면 check값은 0이 된다.
		cout << "\ndata 배열의 정렬이 완료되지 않았습니다." << endl;
	}


}

void quicksort(int low, int high, int dataarray[])//data 배열의 값들을 오름차순으로 정렬하는 함수
{
	//퀵정렬 수도코드를 바탕으로 작성한 퀵정렬 함수
	int pivotpoint,pivotitem;

	if (low >= high) {
		return; //만약 배열의 갯수가 1개라면 반환한다.
	}
	else {
		pivotitem = dataarray[low];
	}

	if (high >= low)
	{
		pivotpoint = partition(low, high, dataarray,pivotitem); //분할한다.
		quicksort(low, pivotpoint - 1, dataarray); //왼쪽 부분을 정렬한다.
		quicksort(pivotpoint + 1, high, dataarray); //오른쪽 부분을 정렬한다.
	}
}

int partition(int low, int high, int dataarray[], int pivotpoint)//퀵정렬을 하기 위해서 분할 하는 함수
{
	//파티션 수도코드를 바탕으로 작성한 파티션 함수
	int i = 0;
	int j = 0;
	int pivot, temp;

	pivotpoint = dataarray[low]; //pivotpoint에 data배열의 low인덱스 값을 넣는다. data배열의 왼쪽 인덱스 값이 피봇값이 된다.
	j = low;
	for (i = low + 1; i <= high; i++) {
		if (dataarray[i] < pivotpoint) {// data 배열i값이 기준으로 정해둔 피봇값보다 작으면
			j++;
			temp = dataarray[i];
			dataarray[i] = dataarray[j];
			dataarray[j] = temp; //값을 바꿔치기 해준다.
			
		}
	}
	pivot = j;//pivot값에 j값을 넣는다.
	temp = dataarray[pivot];
	dataarray[pivot] = dataarray[low];
	dataarray[low] = temp; //data배열의 pivot인덱스 값과 data배열의 low값을 바꿔준다.

	return pivot; //pivot값을 반환
}
void quickquicksort(int low, int high, int* dataarray)//data 배열의 값들을 오름차순으로 정렬하는 개선된 함수
{
	int pivotpoint = (low + high) / 2; //피봇을 중간값으로 정한다.

	int pivot = improvepartition(low, high, dataarray, pivotpoint);


	if (low < pivot - 1) //피봇으로 정해둔 값의 이전 값들을 정렬한다.
		quickquicksort(low, pivot, dataarray);

	if (high > pivot + 1)//피봇으로 정해둔 값의 이후 값들을 정렬한다. 이렇게 구간을 나눔으로써 더 효율적으로 퀵정렬을 실행하게 한다.
		quickquicksort(pivot + 1, high, dataarray);
}
int improvepartition(int low, int high, int dataarray[], int pivotpoint)//퀵정렬을 하기 위해서 분할 하는 개선된 함수
{
	int i = 0;
	int j=0;
	int temp;

	int pivotitem = dataarray[pivotpoint]; //피봇포인트 값을 중간으로 정했는데 그 값을 피봇아이템 값으로 설정한다.
	j = low;
	//partition함수와 비교했을 때 추가 된 코드
	temp = dataarray[low];
	dataarray[low] = dataarray[pivotpoint];
	dataarray[pivotpoint] = temp; //스와핑으로 low인덱스 값과 pivotpoint인덱스 값을 바꿔준다.


	for (i = low + 1; i <= high; i++)
	{
		if (dataarray[i] < pivotitem) //만약 data배열의 값이 피봇값보다 작다면
		{
			++j;
			temp = dataarray[j];
			dataarray[j] = dataarray[i];
			dataarray[i] = temp; //스와핑
		}
	}
	pivotpoint = j;//피봇포인트에 j주소 값을 넣어준다.

	temp = dataarray[pivotpoint];
	dataarray[pivotpoint] = dataarray[low];
	dataarray[low] = temp; //스와핑으로 pivotpoint인덱스 값을 low 인덱스 값으로 바꿔준다.

	return j;//j값을 반환한다.

}
#include <iostream>
#include <time.h>
#include <Windows.h>


using namespace std;

#define SIZE 256000 //������ ������ ������ �迭 �������� ũ��
int dataarray[SIZE] = { 0 }; //���������� ����: ���������� �����ϸ� ���� ���� �ʰ��ɼ��� �ִ�.

void fill(int dataarray);//�迭 data�� ���� 0���� 1�� ���ʷ� �����ϴ� ������ ä���ִ� �Լ�
void scramble(int dataarray[]); //data �迭 ���� ������ �������� ���� �Լ�
void validata(int* dataarray);//data �迭�� ������ �Ŀ� ���� ���ʴ�� ������ �Ǿ����� Ȯ���ϴ� �Լ�
void quicksort(int low, int high,int dataarray[]);//data �迭�� ������ ������������ �����ϴ� �Լ�
int partition(int low, int high, int dataarray[], int pivotpoint);//�������� �ϱ� ���ؼ� ���� �ϴ� �Լ�
void quickquicksort(int low, int high, int* dataarray);//data �迭�� ������ ������������ �����ϴ� ������ �Լ�
int improvepartition(int low, int high, int dataarray[], int pivotpoint);//�������� �ϱ� ���ؼ� ���� �ϴ� ������ �Լ�

int main()
{
	double elapsedTime;

	fill(SIZE);

	cout << "\n1. �� ���� �迭�� �������� �ǽ��մϴ�.(�־��� ���)" << endl;
	validata(dataarray);
	unsigned long startTime = clock();
	quicksort(0, SIZE - 1, dataarray);
	unsigned long endTime = clock();
	elapsedTime = endTime - startTime;
	cout<<"-> �� ���� �迭�� ������ �ҿ� �ð�(�־��� ���) : "<< elapsedTime/CLOCKS_PER_SEC;
	validata(dataarray);

	cout << ". . . .\n2. ���� �迭�� �������� �ǽ��մϴ�." << endl;
	scramble(dataarray); validata(dataarray);
	startTime = clock();
	quicksort(0, SIZE - 1, dataarray);
	endTime = clock();
	elapsedTime = endTime - startTime;
	cout << "-> ���� �迭�� ������ �ҿ� �ð� : " << elapsedTime / CLOCKS_PER_SEC;
	validata(dataarray);
	
	cout << ". . . .\n3. ���� ���� �迭�� ������ �������� �ǽ��մϴ�." << endl;
	validata(dataarray);
	startTime = clock();
	quickquicksort(0, SIZE - 1, dataarray);
	endTime = clock();
	elapsedTime = endTime - startTime;
	cout << "-> ���� ���� �迭�� ������ ������ �ҿ� �ð� : " << elapsedTime / CLOCKS_PER_SEC;
	validata(dataarray);

	cout << ". . . .\n4. ���� �迭�� ������ �������� �ǽ��մϴ�." << endl;
	scramble(dataarray); validata(dataarray);
	startTime = clock();
	quickquicksort(0, SIZE - 1, dataarray);
	endTime = clock();
	elapsedTime = endTime - startTime;
	cout << "-> ���� �迭�� ������ ������ �ҿ� �ð� : " << elapsedTime / CLOCKS_PER_SEC;
	validata(dataarray);

	return 0;
}
void fill(int num) //�迭 data�� ���� 0���� 1�� ���ʷ� �����ϴ� ������ ä���ִ� �Լ�
{
	for (int i = 0; i < num; i++) //�迭 data�� 0���� 1�� �����ϴ� ������ ä���. 
	{
		dataarray[i] = i;
	}
}
void scramble(int dataarray[])//data �迭 ���� ������ �������� ���� �Լ�
{
	int temp, randnum;
	for (int i = 0; i < SIZE; i++)
	{
		randnum = rand() % SIZE; //��������
		temp = dataarray[i];
		dataarray[i] = dataarray[randnum];
		dataarray[randnum] = temp; //���������ָ鼭 ���� ���´�.
	}
}
void validata(int* dataarray) //data �迭�� ������ �Ŀ� ���� ���ʴ�� ������ �Ǿ����� Ȯ���ϴ� �Լ�
//�迭�� ���� �� �Ŀ� ����� ���������� Ȯ�����ش�.
{
	int check;
	for (int i = 0; i < SIZE; i++) {
		if (dataarray[i] == i) {
			check = 1; //True��: data[i]���� 1�� �����Ǵ� ���� ������ 
		}
		else {
			check = 0; //False��: data[i]���� 1�� �����Ǵ� ���� �ƴ϶�� 
		}

	}
	if (check == 1) { //����� ������ �Ǿ����� check���� 1�� �ȴ�.
		cout << "\ndata �迭�� ������ �Ϸ�Ǿ����ϴ�." << endl;
	}
	else {//����� ������ ���� �ʾ����� check���� 0�� �ȴ�.
		cout << "\ndata �迭�� ������ �Ϸ���� �ʾҽ��ϴ�." << endl;
	}


}

void quicksort(int low, int high, int dataarray[])//data �迭�� ������ ������������ �����ϴ� �Լ�
{
	//������ �����ڵ带 �������� �ۼ��� ������ �Լ�
	int pivotpoint,pivotitem;

	if (low >= high) {
		return; //���� �迭�� ������ 1����� ��ȯ�Ѵ�.
	}
	else {
		pivotitem = dataarray[low];
	}

	if (high >= low)
	{
		pivotpoint = partition(low, high, dataarray,pivotitem); //�����Ѵ�.
		quicksort(low, pivotpoint - 1, dataarray); //���� �κ��� �����Ѵ�.
		quicksort(pivotpoint + 1, high, dataarray); //������ �κ��� �����Ѵ�.
	}
}

int partition(int low, int high, int dataarray[], int pivotpoint)//�������� �ϱ� ���ؼ� ���� �ϴ� �Լ�
{
	//��Ƽ�� �����ڵ带 �������� �ۼ��� ��Ƽ�� �Լ�
	int i = 0;
	int j = 0;
	int pivot, temp;

	pivotpoint = dataarray[low]; //pivotpoint�� data�迭�� low�ε��� ���� �ִ´�. data�迭�� ���� �ε��� ���� �Ǻ����� �ȴ�.
	j = low;
	for (i = low + 1; i <= high; i++) {
		if (dataarray[i] < pivotpoint) {// data �迭i���� �������� ���ص� �Ǻ������� ������
			j++;
			temp = dataarray[i];
			dataarray[i] = dataarray[j];
			dataarray[j] = temp; //���� �ٲ�ġ�� ���ش�.
			
		}
	}
	pivot = j;//pivot���� j���� �ִ´�.
	temp = dataarray[pivot];
	dataarray[pivot] = dataarray[low];
	dataarray[low] = temp; //data�迭�� pivot�ε��� ���� data�迭�� low���� �ٲ��ش�.

	return pivot; //pivot���� ��ȯ
}
void quickquicksort(int low, int high, int* dataarray)//data �迭�� ������ ������������ �����ϴ� ������ �Լ�
{
	int pivotpoint = (low + high) / 2; //�Ǻ��� �߰������� ���Ѵ�.

	int pivot = improvepartition(low, high, dataarray, pivotpoint);


	if (low < pivot - 1) //�Ǻ����� ���ص� ���� ���� ������ �����Ѵ�.
		quickquicksort(low, pivot, dataarray);

	if (high > pivot + 1)//�Ǻ����� ���ص� ���� ���� ������ �����Ѵ�. �̷��� ������ �������ν� �� ȿ�������� �������� �����ϰ� �Ѵ�.
		quickquicksort(pivot + 1, high, dataarray);
}
int improvepartition(int low, int high, int dataarray[], int pivotpoint)//�������� �ϱ� ���ؼ� ���� �ϴ� ������ �Լ�
{
	int i = 0;
	int j=0;
	int temp;

	int pivotitem = dataarray[pivotpoint]; //�Ǻ�����Ʈ ���� �߰����� ���ߴµ� �� ���� �Ǻ������� ������ �����Ѵ�.
	j = low;
	//partition�Լ��� ������ �� �߰� �� �ڵ�
	temp = dataarray[low];
	dataarray[low] = dataarray[pivotpoint];
	dataarray[pivotpoint] = temp; //���������� low�ε��� ���� pivotpoint�ε��� ���� �ٲ��ش�.


	for (i = low + 1; i <= high; i++)
	{
		if (dataarray[i] < pivotitem) //���� data�迭�� ���� �Ǻ������� �۴ٸ�
		{
			++j;
			temp = dataarray[j];
			dataarray[j] = dataarray[i];
			dataarray[i] = temp; //������
		}
	}
	pivotpoint = j;//�Ǻ�����Ʈ�� j�ּ� ���� �־��ش�.

	temp = dataarray[pivotpoint];
	dataarray[pivotpoint] = dataarray[low];
	dataarray[low] = temp; //���������� pivotpoint�ε��� ���� low �ε��� ������ �ٲ��ش�.

	return j;//j���� ��ȯ�Ѵ�.

}
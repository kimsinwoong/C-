#include <stdio.h>
int main() {
	int su;
	int a=0;
	int in[100];
	int out[100];
	int nam[100];
	
	printf("��ǰ ���� �Է� : ");
	scanf_s("%d",&su);
	printf("�԰� ���� �Է� : ");
	for (a; a < su;a++) {
		scanf_s("%d", &in[a]);
	}
	printf("���� �Ǹ� ����");
	for (a; a < su;a++) {
		scanf_s("%d", &out[a]);
	}
	 

	return 0;
}
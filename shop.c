
#include <stdio.h>
int main() {
	int su;
	int id;
	int gungun;
	int pam=0;
	float pamper;
	int in[100];
	int out[100];
	int nam[100];

	printf("��ǰ ���� �Է� : ");
	scanf_s("%d", &su);

	printf("�԰� ���� �Է� : ");
	for (int a = 0; a < su; a++) {
		scanf_s("%d", &in[a]);
	}
	printf("���� �Ǹ� ���� : ");
	for (int a = 0; a < su; a++) {
		scanf_s("%d", &out[a]);
	}
	for (int a = 0; a < su; a++) {
		nam[a] = in[a] - out[a];
	}

	printf("ID �Է� : ");
	scanf_s("%d", &id);

	printf("%d\n", nam[id - 1]);
	for (int a = 0; a < su; a++) {
		printf("%d ", nam[a]);
		printf(" ");
	}
	printf("\n");
	for (int a = 0; a < su; a++) {
		gungun += in[a];
	}
	for (int a = 0; a < su; a++) {
		pam += out[a];
	}
	pamper = ((float)gungun / pam) * 100;

	printf("�� �Ǹŷ� : %d(�Ǹ��� : %.2f%%)", pam,pamper);

	return 0;
}

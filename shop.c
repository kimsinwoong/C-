#include <stdio.h>
int main() {
	int su;
	int id;
	int in[100];
	int out[100];
	int nam[100];

	printf("상품 개수 입력 : ");
	scanf_s("%d", &su);
	
	printf("입고 수량 입력 : ");
	for (int a = 0; a < su; a++) {
		scanf_s("%d", &in[a]);
	}
	printf("당일 판매 수량 : ");
	for (int a = 0; a < su; a++) {
		scanf_s("%d", &out[a]);
	}
	for (int a = 0; a < su; a++) {
		nam[a] = in[a] - out[a];
	}
	
	printf("ID 입력 : ");
	scanf_s("%d", &id);

	printf("%d\n", nam[id - 1]);
	for (int a = 0; a < su; a++) {
		printf("%d ", nam[a]);
		printf(" ");
	}
	printf("\n");

	return 0;
}

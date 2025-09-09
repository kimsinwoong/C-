#include <stdio.h>
int main() {
	int su;
	int a=0;
	int in[100];
	int out[100];
	int nam[100];
	
	printf("상품 개수 입력 : ");
	scanf_s("%d",&su);
	printf("입고 수량 입력 : ");
	for (a; a < su;a++) {
		scanf_s("%d", &in[a]);
	}
	printf("당일 판매 수량");
	for (a; a < su;a++) {
		scanf_s("%d", &out[a]);
	}
	 

	return 0;
}
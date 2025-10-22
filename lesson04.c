#include <stdio.h>

#define MAX_ITEMS 100


int  commandMenu(void);
int  commandSubMenu(const char *action);
int  commandId(int su);
int  commandQty(const char *label);
void updatenam(int in[], int out[], int nam[], int su);


void handleInbound(int in[], int out[], int nam[], int su);
void inboundAll(int in[], int out[], int nam[], int su);
void inboundSingle(int in[], int out[], int nam[], int su);

void handleSale(int in[], int out[], int nam[], int su);
void saleAll(int in[], int out[], int nam[], int su);
void saleSingle(int in[], int out[], int nam[], int su);

void showStatus(int in[], int out[], int nam[], int su);



int main(void) {
    int su = 5;                 
    int in[MAX_ITEMS]    = {0};    
    int out[MAX_ITEMS]   = {0};    
    int nam[MAX_ITEMS]= {0};   

    while (1) {
        int menu = commandMenu();

        if (menu == 1) {
            handleInbound(in, out, nam, su);
        } else if (menu == 2) {
            handleSale(in, out, nam, su);
        } else if (menu == 3) {
            showStatus(in, out, nam, su);
        } else if (menu == 4) {
            printf("프로그램을 종료합니다.\n");
            break;
        } else {
            printf("잘못된 메뉴입니다. 다시 선택하세요.\n");
        }
    }
    return 0;
}


int commandMenu(void) {
    int pam;
    printf("\n[쇼핑몰 관리 프로그램]\n");
    printf("원하는 메뉴를 선택하세요. (1. 입고, 2. 판매, 3. 상품현황, 4. 종료)\n> ");
    scanf("%d", &pam);
    return pam;
}

int commandSubMenu(const char *action) {
    int pam;
    printf("%s 수량 입력: 전체=1, 개별=2 를 선택하세요.\n> ", action);
    scanf("%d", &pam);
    return pam;
}

int commandId(int su) {
    int id;
    printf("상품ID 입력 (1~%d): ", su);
    scanf("%d", &id);
    if (id < 1) id = 1;
    if (id > su) id = su;
    return id;
}

int commandQty(const char *label) {
    int q;
    printf("%s 수량 입력: ", label);
    scanf("%d", &q);
    if (q < 0) q = 0; // 음수 방지
    return q;
}

void updatenam(int in[], int out[], int nam[], int su) {
    for (int i = 0; i < su; i++) {
        nam[i] = in[i] - out[i];
    }
}

void handleInbound(int in[], int out[], int nam[], int su) {
    int pam = commandSubMenu("입고");
    if (pam == 1) inboundAll(in, out, nam, su);
    else if (pam == 2) inboundSingle(in, out, nam, su);
    else printf("잘못된 선택입니다.\n");
}

void inboundAll(int in[], int out[], int nam[], int su) {
    printf("전체 상품 입고수량을 순서대로 입력하세요 (총 %d개):\n> ", su);
    for (int i = 0; i < su; i++) {
        int q; scanf("%d", &q);
        if (q < 0) q = 0;
        in[i] += q;
    }
    updatenam(in, out, nam, su);
}
void inboundSingle(int in[], int out[], int nam[], int su) {
    int id  = commandId(su);
    int qty = commandQty("입고");
    in[id - 1] += qty;
    updatenam(in, out, nam, su);
}

void handleSale(int in[], int out[], int nam[], int su) {
    int pam = commandSubMenu("판매");
    if (pam == 1) saleAll(in, out, nam, su);
    else if (pam == 2) saleSingle(in, out, nam, su);
    else printf("잘못된 선택입니다.\n");
}

void saleAll(int in[], int out[], int nam[], int su) {
    printf("전체 상품 판매수량을 순서대로 입력하세요 (총 %d개):\n> ", su);
    for (int i = 0; i < su; i++) {
        int q; scanf("%d", &q);
        if (q < 0) q = 0;
        out[i] += q;
        if (out[i] > in[i]) out[i] = in[i];
    }
    updatenam(in, out, nam, su);
}

void saleSingle(int in[], int out[], int nam[], int su) {
    int id  = commandId(su);
    int qty = commandQty("판매");
    out[id - 1] += qty;
    if (out[id - 1] > in[id - 1]) out[id - 1] = in[id - 1]; 
    updatenam(in, out, nam, su);
}

void showStatus(int in[], int out[], int nam[], int su) {
    printf("\n-- 상품 현황 --\n");

    printf("재고수량: ");
    for (int i = 0; i < su; i++) {
        printf("%d ", nam[i]);
    }
    printf("\n");

    int totalIn = 0, totalOut = 0;
    for (int i = 0; i < su; i++) {
        totalIn  += in[i];
        totalOut += out[i];
    }
    double percent = (totalIn == 0) ? 0 : (double)totalOut / totalIn * 100.0;
    printf("총 판매량: %d (판매율 %.2f%%)\n", totalOut, percent);

    int maxIdx = 0, minIdx = 0;
    for (int i = 1; i < su; i++) {
        if (out[i] > out[maxIdx]) maxIdx = i;
        if (out[i] < out[minIdx]) minIdx = i;
    }
    printf("가장 많이 판매된 상품: ID %d, 판매량 %d\n", maxIdx + 1, out[maxIdx]);
    printf("가장 적게 판매된 상품: ID %d, 판매량 %d\n", minIdx + 1, out[minIdx]);

    for (int i = 0; i < su; i++) {
        if (nam[i] <= 2) { 
            printf("상품 ID %d : 재고부족(%d)\n", i + 1, nam[i]);
        }
    }
}


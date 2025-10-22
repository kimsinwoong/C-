#include <stdio.h>

#define MAX_ITEMS 100
#define NAME_LEN  32

typedef struct {
    char name[NAME_LEN]; 
    int in;              
    int out;           
    int nam;        
} Item;


int  commandMenu(void);
int  commandSubMenu(const char *action);
int  commandId(int su);
int  commandQty(const char *label);
void updatenam(Item items[], int su);


void handleInbound(Item items[], int su);
void inboundAll(Item items[], int su);
void inboundSingle(Item items[], int su);

void handleSale(Item items[], int su);
void saleAll(Item items[], int su);
void saleSingle(Item items[], int su);

void showStatus(Item items[], int su);
void inputNames(Item items[], int su);



int main(void) {
    int su = 5;                 
   

    Item items[MAX_ITEMS];

    while (1) {
        int menu = commandMenu();

        if (menu == 1) {
            handleInbound(items, su);
        } else if (menu == 2) {
            handleSale(items, su);
        } else if (menu == 3) {
            showStatus(items, su);
        } else if (menu == 4) {
            inputNames(items, su);
        } else if (menu == 5) {
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
    printf("원하는 메뉴를 선택하세요. (1. 입고, 2. 판매, 3. 상품현황, 4. 상품명 입력, 5. 종료)\n> ");
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
    if (q < 0) q = 0; 
    return q;
}

void updatenam(Item items[], int su) {
    for (int i = 0; i < su; i++) {
        items[i].nam = items[i].in - items[i].out;
        if (items[i].nam < 0) items[i].nam = 0;
    }
}

void handleInbound(Item items[], int su) {
    int pam = commandSubMenu("입고");
    if (pam == 1) inboundAll(items, su);
    else if (pam == 2) inboundSingle(items, su);
    else printf("잘못된 선택입니다.\n");
}

void inboundAll(Item items[], int su) {
    printf("전체 상품 입고수량을 순서대로 입력하세요 (총 %d개):\n> ", su);
    for (int i = 0; i < su; i++) {
        int q; scanf("%d", &q);
        if (q < 0) q = 0;
        items[i].in += q;
    }
    updatenam(items, su);
}
void inboundSingle(Item items[], int su) {
    int id  = commandId(su);
    int qty = commandQty("입고");
    items[id - 1].in += qty;
    updatenam(items, su);
}

void handleSale(Item items[], int su) {
    int pam = commandSubMenu("판매");
    if (pam == 1) saleAll(items, su);
    else if (pam == 2) saleSingle(items, su);
    else printf("잘못된 선택입니다.\n");
}

void saleAll(Item items[], int su) {
    printf("전체 상품 판매수량을 순서대로 입력하세요 (총 %d개):\n> ", su);
    for (int i = 0; i < su; i++) {
        int q; scanf("%d", &q);
        if (q < 0) q = 0;
        items[i].out += q;
        if (items[i].out > items[i].in) items[i].out = items[i].in;
    }
    updatenam(items, su);
}

void saleSingle(Item items[], int su) {
    int id  = commandId(su);
    int qty = commandQty("판매");
    items[id - 1].out += qty;
    if (items[id - 1].out > items[id - 1].in) items[id - 1].out = items[id - 1].in;
    updatenam(items, su);
}

void inputNames(Item items[], int su) {
    printf("상품명 입력 메뉴 실행\n");
    for (int i = 0; i < su; i++) {
        printf("ID %d 상품명 : ", i + 1);
        scanf(" %31s", items[i].name);
    }
}

static const char* defaultName(Item *it, int idx) {
    if (it->name[0] == '\0') return "(미등록)";
    return it->name;
}

void showStatus(Item items[], int su) {
    printf("\n-- 상품 현황 --\n");

    printf("재고수량: ");
    for (int i = 0; i < su; i++) {
        printf("%d ", items[i].nam);
    }
    printf("\n");

    int totalIn = 0, totalOut = 0;
    for (int i = 0; i < su; i++) {
        totalIn  += items[i].in;
        totalOut += items[i].out;
    }
    double percent = (totalIn == 0) ? 0 : (double)totalOut / totalIn * 100.0;
    printf("총 판매량: %d (판매율 %.2f%%)\n", totalOut, percent);

    int maxIdx = 0, minIdx = 0;
    for (int i = 1; i < su; i++) {
        if (items[i].out > items[maxIdx].out) maxIdx = i;
        if (items[i].out < items[minIdx].out) minIdx = i;
    }
    printf("가장 많이 판매된 상품: ID %d, 상품명: %s, 판매량 %d\n",
       maxIdx + 1, defaultName(&items[maxIdx], maxIdx), items[maxIdx].out);
    printf("가장 적게 판매된 상품: ID %d, 상품명: %s, 판매량 %d\n",
        minIdx + 1, defaultName(&items[minIdx], minIdx), items[minIdx].out);

    for (int i = 0; i < su; i++) {
        if (items[i].nam <= 2) {
            printf("상품 ID %d : 상품명: %s 재고부족(%d)\n",
                i + 1, defaultName(&items[i], i), items[i].nam);
        }
    }
}
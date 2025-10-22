#include <stdio.h>
#include <string.h>

#define MAX_ITEMS 100
#define NAME_LEN  32
#define MAX_su 5   

typedef struct {
    char name[NAME_LEN]; 
    int price;           
    int in;             
    int out;            
    int nam;          
    int active;
} Item;

int  commandMenu(void);
int  commandId(int su);
int  commandQty(const char *label);
void updatenam(Item items[], int su);

void handleInbound(Item items[], int su);
void handleSale(Item items[], int su);

void showStatus(Item items[], int su);     // 전체현황
void showOne(Item items[], int su);        // 개별현황

int  countActive(Item items[], int su);
const char* defaultName(Item *it);
void checkNameLen(char *dest, const char *src, int maxChars);


int saveItems(const char *path, Item items[], int su);
int loadItems(const char *path, Item items[], int su);

int main(void) {
    int su = MAX_su;
    Item items[MAX_ITEMS];

    for (int i = 0; i < su; i++) {
        items[i].name[0] = '\0';
        items[i].price = 0;
        items[i].in = items[i].out = items[i].nam = 0;
        items[i].active = 0;
    }

    while (1) {
        int menu = commandMenu();

        if (menu == 1) {
            handleInbound(items, su);
        } else if (menu == 2) {
            handleSale(items, su);
        } else if (menu == 3) {
            showOne(items, su);
        } else if (menu == 4) {
            showStatus(items, su);
        } else if (menu == 5) {

            if (saveItems("items.txt", items, su)) {
                printf("저장 완료: items.txt\n");
            } else {
                printf("저장 실패\n");
            }
        } else if (menu == 6) {
            if (loadItems("items.txt", items, su)) {
                updatenam(items, su);
                printf("불러오기 완료: items.txt\n");
            } else {
                printf("불러오기 실패\n");
            }
        } else if (menu == 7) {
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
    printf("원하는 메뉴를 선택하세요. (1. 입고, 2. 판매, 3. 개별현황, 4. 전체현황, 5. 저장, 6. 가져오기, 7. 종료)\n> ");
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

int countActive(Item items[], int su) {
    int c = 0;
    for (int i = 0; i < su; i++) if (items[i].active) c++;
    return c;
}
const char* defaultName(Item *it) {
    return (it->name[0] == '\0') ? "(미등록)" : it->name;
}


void checkNameLen(char *dest, const char *src, int maxChars) {
    int len = 0;
    int i = 0, j = 0;
    
    while (src[i] && len < maxChars) {
        unsigned char c = (unsigned char)src[i];
        int charSize = 1;

        if (c < 0x80) {
            charSize = 1;         
        } else if ((c & 0xE0) == 0xC0) {
            charSize = 2;        
        } else if ((c & 0xF0) == 0xE0) {
            charSize = 3;          
        } else if ((c & 0xF8) == 0xF0) {
            charSize = 4;          
        }

        for (int k = 0; k < charSize; k++) {
            dest[j++] = src[i++];
        }
        len++;
    }
    dest[j] = '\0';
}

void handleInbound(Item items[], int su) {
    int id = commandId(su);
    char buf[101];

    if (!items[id - 1].active && countActive(items, su) >= MAX_su) {
        printf("최대 상품 개수(%d)를 초과할 수 없습니다.\n", MAX_su);
        return;
    }

    printf("상품명 (최대 4글자): ");
    scanf(" %99s", buf);
    checkNameLen(items[id - 1].name, buf, 4);

    {
        int qty = commandQty("입고");
        items[id - 1].in += qty;
    }

    printf("판매가격 : ");
    scanf("%d", &items[id - 1].price);

    items[id - 1].active = 1;
    updatenam(items, su);
}

void handleSale(Item items[], int su) {
    int id = commandId(su);
    if (!items[id - 1].active) {
        printf("오류: 해당 ID의 상품이 없습니다. 먼저 입고로 생성하세요.\n");
        return;
    }
    {
        int qty = commandQty("판매");
        items[id - 1].out += qty;
        if (items[id - 1].out > items[id - 1].in) items[id - 1].out = items[id - 1].in;
    }
    updatenam(items, su);
}

void showOne(Item items[], int su) {
    int id = commandId(su);
    if (!items[id - 1].active) {
        printf("오류: 해당 ID의 상품이 없습니다.\n");
        return;
    }
    Item *it = &items[id - 1];
    long long total = (long long)it->out * (long long)it->price;

    printf("\n[개별현황]\n");
    printf("상품 ID  : %d\n", id);
    printf("상품명    : %s\n", defaultName(it));
    printf("단가     : %d\n", it->price);
    printf("입고량    : %d\n", it->in);
    printf("판매량    : %d\n", it->out);
    printf("재고     : %d\n", it->nam);
    printf("총판매금액 : %lld\n", total);
}

void showStatus(Item items[], int su) {
    printf("\n=== 전체 현황 ===\n");

    printf("재고수량: ");
    for (int i = 0; i < su; i++) {
        printf("%d ", items[i].nam);
    }
    printf("\n");

    {
        int totalIn = 0, totalOut = 0;
        for (int i = 0; i < su; i++) {
            totalIn  += items[i].in;
            totalOut += items[i].out;
        }
        {
            double percent = (totalIn == 0) ? 0.0 : (double)totalOut / (double)totalIn * 100.0;
            printf("총 판매량: %d (판매율 %.2f%%)\n", totalOut, percent);
        }
    }

    {
        int maxIdx = 0, minIdx = 0;
        for (int i = 1; i < su; i++) {
            if (items[i].out > items[maxIdx].out) maxIdx = i;
            if (items[i].out < items[minIdx].out) minIdx = i;
        }
        printf("가장 많이 판매된 상품: ID %d, 상품명: %s, 판매량 %d\n",
               maxIdx + 1, defaultName(&items[maxIdx]), items[maxIdx].out);
        printf("가장 적게 판매된 상품: ID %d, 상품명: %s, 판매량 %d\n",
               minIdx + 1, defaultName(&items[minIdx]), items[minIdx].out);
    }

    printf("-----------------재고-----------------\n");
    for (int i = 0; i < su; i++) {
        printf(" %d | %11s | %2d | %2d | %5d |   %s\n", i+1 , defaultName(&items[i]), items[i].in, items[i].out, items[i].price, (items[i].nam <= 2)? "X" : "O" );
    }

    {
        long long totalRevenue = 0;
        for (int i = 0; i < su; i++) {
            if (items[i].active) {
                long long revenue = (long long)items[i].out * (long long)items[i].price;
                totalRevenue += revenue;
            }
        }
        printf("총 판매금액 합계: %lld\n", totalRevenue);
    }
}


int saveItems(const char *path, Item items[], int su) {
    FILE *fp = fopen(path, "w");
    if (!fp) return 0;
    for (int i = 0; i < su; i++) {
        fprintf(fp, "%d %s %d %d %d\n",
                items[i].active,
                (items[i].name[0] ? items[i].name : "-"),
                items[i].price,
                items[i].in,
                items[i].out);
    }
    fclose(fp);
    return 1;
}

int loadItems(const char *path, Item items[], int su) {
    FILE *fp = fopen(path, "r");
    if (!fp) return 0;

    for (int i = 0; i < su; i++) {
        int active=0, price=0, in=0, out=0;
        char name[NAME_LEN] = {0};
        int got = fscanf(fp, "%d %31s %d %d %d",
                         &active, name, &price, &in, &out);
        if (got == 5) {
            items[i].active = active;
            strncpy(items[i].name, (strcmp(name,"-")==0) ? "" : name, NAME_LEN-1);
            items[i].price = price;
            items[i].in = in;
            items[i].out = out;
            items[i].nam = 0; 
        } else {
            items[i].active = 0;
            items[i].name[0] = '\0';
            items[i].price = 0;
            items[i].in = items[i].out = items[i].nam = 0;
        }
    }
    fclose(fp);
    return 1;
}

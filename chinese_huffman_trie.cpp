/*************************************************************************
	> File Name: huffman.cpp
	> Author: sudingquan
	> Mail: 1151015256@qq.com
	> Created Time: 日  7/21 20:31:19 2019
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 1000  //最大词长
#define MAX_N 1000 //最大词数
#define swap(a, b) { \
    __typeof(a) temp = a; \
    a = b, b = temp; \
}

typedef struct Node {
    unsigned char ch;
    double p;
    struct Node *next[2];
} Node;

typedef struct Code {
    unsigned char ch;
    char *str;
} Code;

typedef struct HuffmanTree {
    Node *root;
    int n;
    Code *codes;
} HuffmanTree;

typedef struct Data {
    unsigned char ch;
    double p;
} Data;

struct 

Data arr[256];
int data[256];
unsigned char str[MAX_N][MAX_SIZE * 3];
int word_cnt = 0;
int character_cnt = 0;

Node *getNewNode(Data *obj) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->ch = obj ? obj->ch : 0;
    p->p = obj ? obj->p : 0;
    p->next[0] = p->next[1] = NULL;
    return p;
}

HuffmanTree *getNewTree(int n) {
    HuffmanTree *tree = (HuffmanTree *)malloc(sizeof(HuffmanTree));
    tree->root = NULL;
    tree->n = n;
    tree->codes = (Code *)malloc(sizeof(Code) * n);
    return tree;
}

void insertOnce(Node **arr, int n) {
    for (int j = n; j >= 1; j--) {
        if (arr[j]->p > arr[j - 1]->p) {
            swap(arr[j], arr[j - 1]);
            continue;
        }
        break;
    }
    return ;
}

int extractCodes(Node *root, Code *arr, int k, int l, char *buff) {
    buff[l] = 0;
    if (root->next[0] == NULL && root->next[1] == NULL) {
        arr[k].ch = root->ch;
        arr[k].str = strdup(buff);
        return 1;
    }
    int delta = 0;
    buff[l] = '0';
    delta += extractCodes(root->next[0], arr, k + delta, l + 1, buff);
    buff[l] = '1';
    delta += extractCodes(root->next[1], arr, k + delta, l + 1, buff);
    return delta;
}

HuffmanTree *build(Data * arr, int n) {
    Node **nodes = (Node **)malloc(sizeof(Node *) * n);
    for (int i = 0; i < n; i++) {
        nodes[i] = getNewNode(arr + i);
    }
    for (int i = 1; i < n; i++) {
        insertOnce(nodes, i);
    }
    for (int i = n - 1; i >= 1; i--) {
        Node *p = getNewNode(NULL);
        p->next[1] = nodes[i];
        p->next[0] = nodes[i - 1];
        p->p = p->next[0]->p + p->next[1]->p;
        nodes[i - 1] = p;
        insertOnce(nodes, i - 1);
    }
    char *buff = (char *)malloc(sizeof(char) * n);
    HuffmanTree *tree = getNewTree(n);
    tree->root = nodes[0];
    extractCodes(tree->root, tree->codes, 0, 0, buff);
    free(nodes);
    free(buff);
    return tree;
}

int main() {
    while (1) {
        scanf("%s", str[word_cnt]);
        if (strcmp((char *)str[word_cnt], "END") == 0) {
            break;
        }
        word_cnt++;
    }
    printf("输入了%d个词\n", word_cnt);
    for (int i = 0; i < word_cnt; i++) {
        for (int j = 0; str[i][j]; j++) {
            data[str[i][j]] += 1;
        }
    }
    for (int i = 0; i < 256; i++) {
        if (data[i] == 0) continue;
        printf("%d : %d\n", i, data[i]);
        character_cnt += 1;
    }
    printf("总字节个数:%d\n", character_cnt);
    printf("字节频次表:\n");
    for (int i = 0, j = 0; i < 256; i++) {
        if (data[i] == 0) continue;
        arr[j].ch = i;
        arr[j].p = data[i];
        j++;
    }
    HuffmanTree *tree = build(arr, character_cnt);
    for (int i = 0; i < tree->n; i++) {
        printf("%d : %s\n", tree->codes[i].ch, tree->codes[i].str);
    }
    return 0;
}

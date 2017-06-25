#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct _HashNode{
    int* pair;
    struct _HashNode* next;
} HashNode;

int _cache_len = 0;
const int _cache_size=64;
HashNode _cache[_cache_size];

void hash_init(){
    for(int i=0; i<_cache_size; i++){
        _cache[i].pair = NULL;
        _cache[i].next = NULL;
    }
}

bool hash_set(int* pair){
    int key = (pair[0] + pair[1]) % _cache_size;
    key = key < 0 ? key + 64 : key;
    HashNode* p = &_cache[key];
    while(p->pair!=NULL){
        if(p->pair[0] == pair[0] && p->pair[1] == pair[1]){
            return false;
        }
        if(p->next!=NULL){
            p = p->next;
        }
        else{
            HashNode* _next;
            _next = (HashNode*)malloc(sizeof(HashNode));
            _next->pair = NULL;
            _next->next = NULL;
            p->next = _next;
            p = p->next;
        }
    }
    p->pair = (int*)malloc(sizeof(int)*3);
    p->pair[0] = pair[0];
    p->pair[1] = pair[1];
    p->pair[2] = pair[2];
	_cache_len++;
    return true;
}


int** hash_get(int* returnSize){
    int** res, k=0;
    HashNode* p;
    *returnSize = _cache_len;
    res = (int**)malloc(sizeof(int*)*_cache_len);
    for(int i=0; i< _cache_size; i++){
        p = &_cache[i];
        while(p->pair!=NULL){
            res[k++] = p->pair;
            if(p->next!=NULL)
                p = p->next;
            else
                break;
        }
    }
    return res;
}


int main(int argc, char* argv[]){
    int pair[]={-2, -1, 3};
    int pair1[3]={-64, -3, 67};
	int** res, n;
    bool ok, ok1;
    hash_init();
    ok = hash_set(pair);
    ok1 = hash_set(pair1);
    printf("%d, %d\n", ok, ok1);
	res = hash_get(&n);
	for(int i=0;i<n;i++){
        printf("%d\t%d\t%d\n", res[i][0], res[i][1], res[i][2]);
    }
	return 0;
}


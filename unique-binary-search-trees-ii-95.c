#include<stdio.h>
#include<stdlib.h>
/**
 * Definition for a binary tree node.
 *
 */
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};



struct TreeNode** generateTreesN(int start, int end, int* returnSize, struct TreeNode**** dp, int** dpn) {
    struct TreeNode **ret=NULL;
    *returnSize = 0;
    if (start == end) {
        struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        root->val = start;
        root->left = NULL;
        root->right = NULL;
        *returnSize += 1;
        ret = realloc(ret, *returnSize * sizeof(void*));
        ret[*returnSize-1] = root;
        return ret;
    }
    for(int i = start; i <= end; i++) {
        if (!dp[start][i-1]) {
            dp[start][i - 1] = generateTreesN(start, i - 1, &dpn[start][i-1], dp, dpn);
        }
        else printf("cache used\n");
        if (!dp[i + 1][end]) {
            dp[i + 1][end] = generateTreesN(i + 1, end, &dpn[i + 1][end], dp, dpn);
        }
        else printf("cache used\n");
        // printf("process %d %d %d, get: %d, %d\n", start, i, end, dpn[start][i-1], dpn[i+1][end]);
        if (!dpn[start][i-1]) {
            for(int n=0;n<dpn[i+1][end];n++) {
                struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
                root->val = i;
                root->left = NULL;
                root->right = dp[i+1][end][n];
                *returnSize += 1;
                ret = realloc(ret, *returnSize * sizeof(void*));
                ret[*returnSize-1] = root;
            }
        }
        if (!dpn[i+1][end]) {
            for(int m=0;m<dpn[start][i-1];m++) {
                struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
                root->val = i;
                root->left = dp[start][i-1][m];
                root->right = NULL;
                *returnSize += 1;
                ret = realloc(ret, *returnSize * sizeof(void*));
                ret[*returnSize-1] = root;
            }
        }
        for (int m=0;m<dpn[start][i-1];m++) {
            for(int n=0;n<dpn[i+1][end];n++) {
                struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
                root->val = i;
                root->left = dp[start][i-1][m];
                root->right = dp[i+1][end][n];
                *returnSize += 1;
                ret = realloc(ret, *returnSize * sizeof(void*));
                ret[*returnSize-1] = root;
            }
        }
    }
    return ret;
}


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
struct TreeNode** generateTrees(int n, int* returnSize){
    struct TreeNode **ret;
    int n1 = n + 1;
    int n2 = n + 2;
    struct TreeNode ****dp = malloc(n2*sizeof(void*));
    int **dpn = malloc(n2*sizeof(void*));
    int i, j;
    for(i = 0;i<n2;i++){
        dp[i] = malloc(n1 * sizeof(void*));
        dpn[i] = malloc(n1 * sizeof(int));
        for(j=0;j<n1;j++){
            dp[i][j] = NULL;
            dpn[i][j] = 0;
        }
    }
    ret = generateTreesN(1, n, returnSize, dp, dpn);
    for(i = 0;i<n2;i++){
        free(dp[i]);
        free(dpn[i]);
    }
    free(dp);
    free(dpn);
    return ret;
}

int main() {
    int size;
    struct TreeNode ** ret = generateTrees(6, &size);
    printf("size: %d\n", size);
    for(int i=0;i<size;i++) {
        printf("tree head: %d\n", ret[i]->val);
    }
    return 0;
}

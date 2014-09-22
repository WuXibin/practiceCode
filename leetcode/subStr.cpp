#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

void genNext(char *str, int next[]) {
    int n = strlen(str);
    next[0] = -1;
    int i = 0, k = -1;
    while(i < n - 1) {
        if(k == -1 || str[i] == str[k]) {
            i++;
            k++;
            next[i] = k;
        } else
            k = next[k];
    }
}

char *KMPSearch(char *s, char *ss, int next[]) {
    int m = strlen(s), n = strlen(ss);
    int i = 0, j = 0;
    while(i < m && j < n) {
        if(j == -1 || s[i] == ss[j]) {
            i++;
            j++;
        } else 
            j = next[j];
    }
    if(j == n)
        return s + i - j;
    return NULL;
}

char *strStr(char *haystack, char *needle) {
    int n = (int)strlen(needle);
    int *next = new int[n];
    
    genNext(needle, next);
    return KMPSearch(haystack, needle, next);
}

int main() {
    char s[128], ss[128];
    
    scanf("%s %s", s, ss);
    //printf("%s %s\n", s, ss);
    char *res = strStr(s, ss);
    printf("%s\n", res);
    return 0;
}

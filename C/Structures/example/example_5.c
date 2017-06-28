/* 
 * File:   example_5.c
 * Author: changdi
 *
 * Created on 2016年7月25日, 下午1:29
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define BUFSIZE 100  
char buf[BUFSIZE];   /*用于ungetch函数的缓冲区*/
int bufp = 0;        /*buf中下一个空闲位置*/

struct tnode{
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *,int);

main() {
    struct tnode *root;
    char word[MAXWORD];
    
    root = NULL;
    
    while(getword(word,MAXWORD) != EOF){
        if(isalpha(word[0])){
            root = addtree(root, word);
        }
    }
    treeprint(root);
    return 0;
    
}

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

/*从输入中读取下一个单词或字符*/
int getword(char *word, int lim)
{
    int c;
    char *w = word;

    while (isspace(c = getch()))
    {
        ;
    }

    if (c != EOF)
        *w++ = c;
    if (!isalpha(c))
    {
        *w = '\0';
        return c;
    }

    for (; --lim > 0; w++)
    {
        if (!isalnum(*w = getch()))
        {
            ungetch(*w);
            break;
        }
    }
    *w = '\0';
    
    return word[0];
}

struct tnode *talloc(void);
//char *strdup(char *);

struct tnode *addtree(struct tnode *p, char *w)
{
    int cond;
    
    if(p == NULL){
        p = talloc();
        p->word = strdup(w);
        p->count = 1;
        p->left = p->right = NULL;
    }else if((cond = strcmp(w,p->word)) == 0){
        p->count++;
    }else if(cond < 0){
        p->left = addtree(p->left,w);
    } else{
        p->right = addtree(p->right, w);
    }

    return p;
}

//创建一个节点
struct tnode *talloc(void){
    return (struct tnode *)malloc(sizeof(struct tnode));
}

/*按序打印树p*/
void treeprint(struct tnode *p)
{
    if (p != NULL)
    {
        treeprint(p->left);
        printf("%4d %s\n", p->count, p->word);
        treeprint(p->right);
    }
}


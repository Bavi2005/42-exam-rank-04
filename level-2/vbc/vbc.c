#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
typedef struct n{int t,v;struct n*l,*r;}n;enum{ADD,MUL,VAL};
static n*new(n x){n*r=calloc(1,sizeof(*r));if(!r)return 0;*r=x;return r;}
static void del(n*x){if(!x)return; if(x->t!=VAL){del(x->l);del(x->r);}free(x);} 
static void bad(char c){if(c)printf("Unexpected token '%c'\n",c);else printf("Unexpected end of input\n");}
static int acc(char **s,char c){if(**s==c){(*s)++;return 1;}return 0;}
static int exp(char **s,char c){if(acc(s,c))return 1;bad(**s);return 0;}
static n*factor(char **s);static n*term(char **s);static n*exprr(char **s);
static n*factor(char **s){if(isdigit((unsigned char)**s)){n x={VAL,**s-'0',0,0};(*s)++;return new(x);}if(acc(s,'(')){n*e=exprr(s);if(!e)return 0;if(!exp(s,')')){del(e);return 0;}return e;}bad(**s);return 0;}
static n*term(char **s){n*l=factor(s);if(!l)return 0;while(acc(s,'*')){n*r=factor(s);if(!r){del(l);return 0;}n x={MUL,0,l,r};l=new(x);if(!l)return 0;}return l;}
static n*exprr(char **s){n*l=term(s);if(!l)return 0;while(acc(s,'+')){n*r=term(s);if(!r){del(l);return 0;}n x={ADD,0,l,r};l=new(x);if(!l)return 0;}return l;}
static n*parse_expr(char *s){char *p=s; n*r=exprr(&p); if(!r)return 0; if(*p){bad(*p);del(r);return 0;} return r;}
static int eval(n*t){return t->t==VAL?t->v:t->t==ADD?eval(t->l)+eval(t->r):eval(t->l)*eval(t->r);} 
int main(int ac,char **av){if(ac!=2)return 1; n*t=parse_expr(av[1]); if(!t)return 1; printf("%d\n",eval(t)); del(t); return 0;}

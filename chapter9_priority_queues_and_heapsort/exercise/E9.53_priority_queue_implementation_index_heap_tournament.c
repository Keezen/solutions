/*
** The implementation for index-item priority queue using an index heap tournament.
** The meaning of index heap tournament is given below: given an array data of N 
** elements, consider a complete binary tree of 2N (represented as an array pq) containing
** indices from the array with two properties, (1) for i from 0 to N-1, we have pq[N+i]=i; 
** and (2) for i from 1 to N-1, we have pq[i]=pq[2*i] if data[pq[2*i]]>data[pq[2*i+1]],
** and we have pq[i]=pq[2*i+1] otherwise. Such a structure is called an index heap tournament.
*/
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"pqueue_index.h"

static int *pq;
static int *qp;
static int N;

extern int compare_index(int index1,int index2);
extern void print_index(int index);
static void swap_index(int a,int b);

void pqueue_init(int Nmax)
{
	pq=malloc((2*Nmax)*sizeof(*pq));
	qp=malloc((2*Nmax)*sizeof(*qp));
	N=0;
}

int pqueue_empty(void)
{
	return(N==0);
}

void pqueue_construct(int left,int right)
{
	int i;

	N=right-left+1;

	for(i=2*N-1;i>=N;i--){
		pq[i]=i-N+left;
		qp[i-N+left]=i;
	}

	for(i=N-1;i>=1;i--){
		if(compare_index(pq[2*i],pq[2*i+1])>0){
			pq[i]=pq[2*i];
		}else{
			pq[i]=pq[2*i+1];
		}
	}
}

void pqueue_insert(int index)
{
	int i;

	if(pqueue_empty()){
		pq[1]=index;
		qp[index]=1;
		N++;
			
		return;
	}


	pq[2*N]=pq[N];
	qp[pq[2*N]]=2*N;

	pq[2*N+1]=index;
	qp[index]=2*N+1;

	N++;

	for(i=N-1;i>=1;i--){
		if(compare_index(pq[2*i],pq[2*i+1])>0){
			pq[i]=pq[2*i];
		}else{
			pq[i]=pq[2*i+1];
		}
	}
}

int pqueue_del_max(void)
{
	int index_max=pq[1];
	int position=qp[index_max];
	int i;

	assert(!pqueue_empty());

	swap_index(2*N-1,position);
	pq[N-1]=pq[2*N-2];
	qp[pq[N-1]]=N-1;
	N--;

	for(i=N-1;i>=1;i--){
		if(compare_index(pq[2*i],pq[2*i+1])>0){
			pq[i]=pq[2*i];
		}else{
			pq[i]=pq[2*i+1];
		}
	}

	return(index_max);
}

void pqueue_change(int index)
{
	int position=qp[index];
	int i;

	for(i=N-1;i>=1;i--){
		if(compare_index(pq[2*i],pq[2*i+1])>0){
			pq[i]=pq[2*i];
		}else{
			pq[i]=pq[2*i+1];
		}
	}	
}

void pqueue_delete(int index)
{
	int i;
	int position=qp[index];

	swap_index(2*N-1,position);
	pq[N-1]=pq[2*N-2];
	qp[pq[N-1]]=N-1;
	N--;

	for(i=N-1;i>=1;i--){
		if(compare_index(pq[2*i],pq[2*i+1])>0){
			pq[i]=pq[2*i];
		}else{
			pq[i]=pq[2*i+1];
		}
	}
}

void pqueue_print(void)
{
	int i;

	for(i=N;i<2*N;i++){
		print_index(pq[i]);
		putchar(' ');
	}
	putchar('\n');
}

static void swap_index(int a,int b)
{
	int indexa,indexb;

	indexa=pq[a];
	indexb=pq[b];

	pq[a]=indexb;
	pq[b]=indexa;

	qp[indexa]=b;
	qp[indexb]=a;
}

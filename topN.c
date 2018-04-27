/*
This program, given an arbitrarily large file and a number, N, containing individual numbers on each line (e.g. 200Gb file), 
will output the largest N numbers, highest first. 

"Usage : %s <Input filename> <Number of largest numbers>
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

long long N = 0;
long long *top;

//qsort compare function
int comp(const void * a, const void * b){
	return ( *(long long *)a > *( long long*)b);
}

//binary search and returns position of last checked
int b_search(long long *array, long long num, int start, int end){
int mid = start;
if(end>=start){
	mid = start+ (end-start)/2;
	if(array[mid] == num){
		printf("pos = %d\n",mid);
        	return mid;
	}
	if(array[mid] > num){
        	return b_search(array,num,start,mid-1);
	}
	else{
       		return b_search(array,num,mid+1,end);
	}
}
return mid;
}


//This function will be called only if top is full and sorted top[0] -> lowest top[N-1] -> highest 
//Checks if the num is present in the array top. 
//If not inserts in appropriate position after removing the lowest number in the array
int check_and_update(long long num){
int i;

if(num == top[N-1]){
	return 0;
}
if(num > top[N-1]){
	memmove(&top[0],&top[1],(N-1)*sizeof(long long));
	top[N-1] = num;
	return 0;
}
if(num <= top[0]){
	return 0;
}
if(num > top[0] && num < top[N-1]){
	//find position to insert
	
	int pos = 0;
	pos = b_search (top, num,0,N-1);

	if(top[pos] == num){
		//do nothing	
		return 0;
	}
	memmove(&top[0],&top[1],(pos-1)*sizeof(long long));
	top[pos-1] = num;

}
return 0;
}

int main(int argc, char *argv[]){
long long numLines = 0;
char buff[64];
long long i;
long long fill,last_pos;

FILE * fp = fopen(argv[1],"r");

if(argc < 3){
        printf("Usage : %s <Input filename> <Number of largest numbers>\n",argv[0]);
        exit(0);
}

if(fp == NULL){
	printf("Input file missing\n");
	exit(0);
}

N = atoll(argv[2]);
top = ( long long *)malloc(N * sizeof(long long));

for(fill = 0; fill < N; fill++)
	top[fill] = 0;

memset(buff,'\0',64);

fgets(buff,sizeof(buff),fp);

fill = 0; 

while(!feof(fp)){
	buff[strlen(buff)-1] = '\0';
	i = atoll(buff);	
	numLines++;
	if(numLines <= N){
		int pos = 0;
		if(numLines > 1){
			pos = b_search (top,i,0,fill);

			if(top[pos] == i){
				//number already present 
				continue;
			}
		}	
		last_pos = fill++;
		top[last_pos] = i;	
		if(numLines == N){
			//quick sort top before proceeding
			qsort(top, N, sizeof(long long), comp);
		}
	}
	else{
		check_and_update(i);
	}
	
	memset(buff,'\0',64);
	fgets(buff,sizeof(buff),fp);

	}
fclose(fp);
printf("Top N -----\n");
for(fill = N-1 ; fill >= 0; fill--)
	printf("%lld\n", top[fill]);

}

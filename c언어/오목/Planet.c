#include <stdio.h>
#include <stdlib.h>
	int plane[9][9];
	int u, v;
	int color = 0;
	int win = 0;
int InputPosition(){
        while(1){
        if (color == 0){
	printf("Black's turn\n input number(x,y) : ");
	} else {
	printf("White's turn\n input number(x,y) : ");
	}
	scanf("%d, %d",&u, &v);
	if (plane[v][u] == 0 && v<9 && u<9){
	break;
	}else{
	printf("Error!!!\n");
	}
	}
	plane[v][u] = color+1;
	int cnt = 0;
	int max = 0;
	//Horizontal Search 
	for(int i = 0; i<9; i++){
	if (plane[v][i] == color+1){
	cnt++;
	} else{
	cnt = 0;
	}
	if (max < cnt)
	max = cnt;
	}
	if (max == 5)
	win = 1;
	cnt = 0;
	max = 0;
	//Vertical Search
	for(int i = 0; i<9; i++){
	if (plane[i][u] == color+1){
	cnt++;
	} else{
	cnt = 0;
	}
	if (max < cnt)
	max = cnt;
	}
	if (max == 5)
	win = 1;
	cnt = 0;
	max = 0;
	
	int little;
	if (v>u){
	little = u;
	} else{
	little = v;
	}
	//Diagonal Search
	for(int i = 0; v-little+i<9 && u-little+i<9; i++){
	if (plane[v-little+i][u-little+i] == color+1){
	cnt++;
	} else{
	cnt = 0;
	}
	if (max < cnt)
	max = cnt;
	}
	if (max == 5)
	win = 1;
	cnt = 0;
	max = 0;
	
	if (8-v>u){
	little = u;
	} else{
	little = 8-v;
	}
	//Alter Diagonal Search
	for(int i = 0; v+little-i>=0 && u-little+i<9; i++){
	if (plane[v+little-i][u-little+i] == color+1){
	cnt++;
	} else{
	cnt = 0;
	}
	if (max < cnt)
	max = cnt;
	}
	if (max == 5)
	win = 1;
	cnt = 0;
	max = 0;
	
	
	}
int main(){

	
	for(int y = 0; y<9; y++){
	for(int x = 0; x < 9; x++)
	plane[y][x]=0;
	}
	
	while(1){
	printf("White Stone : 2\nBlack Stone : 1");
	for(int y = 0; y<9; y++){
	printf("\n");
	for(int x = 0; x < 9; x++)
	printf("%d ", plane[y][x]);
	}
	InputPosition();
	if(win == 1){
	if (color == 0){
	printf("Black's Win!!!");
	} else {
	printf("White's Win!!!");
	}
	exit(0);
	}
	color = 1 - color;
	}

}
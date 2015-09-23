#include<iostream>
#include<cstdlib>
#include<cstdio>


int sdk[9][9]={};
long long all=0;




struct Point{
	int row;
	int col;
	int num;
};


//vector<Point> vec;


///init
void init_sdk(){
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			sdk[i][j]=-1;
		}
	}
}


int fill_sdk(){

	struct Point point;

	printf("Format:\tROW COL NUM\nCTRL+D to stop inputing!\n");
	
	while(scanf("%d %d %d",&point.row,&point.col,&point.num)){
	
		sdk[point.row-1][point.col-1]=point.num;

	}

	return 0;
}


int select(int no,int count){
	
	int x=no/9;
	int y=no%9;

	if(x>=9||y>=9)return -1;

	bool check[10]={};///false default


	for(int i=0;i<9;i++){

		int row=sdk[i][y];
		int col=sdk[x][i];
		
		if(-1!=row){
			check[row]=true;
		}
		if(-1!=col){
			check[col]=true;
		}
		
		/*int diag;
		if(0<=(x+i)&&(x+i)<9&&0<=(y+i)&&(y+i)<9){
			diag=sdk[x+i][y+i];
			if(diag!=-1)check[diag]=true;
		}
		if(0<=(x-i)&&(x-i)<9&&0<=(y-i)&&(y-i)<9){
			diag=sdk[x-i][y-i];
			if(diag!=-1)check[diag]=true;
		}
		if(0<=(x-i)&&(x-i)<9&&0<=(y+i)&&(y+i)<9){
			diag=sdk[x-i][y+i];
			if(diag!=-1)check[diag]=true;
		}
		if(0<=(x+i)&&(x+i)<9&&0<=(y-i)&&(y-i)<9){
			diag=sdk[x+i][y-i];
			if(diag!=-1)check[diag]=true;
		}*/

		int sx=x/3;
		int sy=y/3;

		int xo=i/3;
		int yo=i%3;

		int num;
		if((num=sdk[sx*3+xo][sy*3+yo])!=-1){
			check[num]=true;	
		}
	}

	/* if((x+y==8)||(x==y))check[1]=true; */

	///select
	for(int i=1,j=0;i<=9;i++){
		if(j>count)break;
		if(check[i]==false){
			if(j==count){
				return i;
			}else j++;
		}
	}

	return -1;///all tested!

}


void bfs(int depth){

	int x=depth/9;
	int y=depth%9;

	if(depth>=81){

		all++;

		if(all%100000==0)putchar('.');
		
		printf("\n");
		for(int i=0;i<9;i++){
			for(int j=0;j<9;j++){
				printf("%d",sdk[i][j]);
			}
			printf("\n");
		}

		system("PAUSE");
		
	}else if(sdk[x][y]!=-1){
		
		bfs(depth+1);
		
		return;

	}else{
		int cnt=0;
		while(1){
			int num;
			if((num=select(depth,cnt++))!=-1){
				sdk[x][y]=num;
				bfs(depth+1);
				sdk[x][y]=-1;
			}else{
				return;
			}
		}
	}
}

int main(int argc,char**argv){
	
	init_sdk();

	fill_sdk();

	bfs(0);

	printf("Totally %lld Solution\n",all);

	system("PAUSE");

	return 0;
}


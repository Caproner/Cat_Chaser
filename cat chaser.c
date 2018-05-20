#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<windows.h>
#define F(X) for(i=0;i<X;i++)
#define G(X) for(j=0;j<X;j++)
int a[9][9],i,j,walk=1,x,y,xc,yc,b[9][9],dif;
//walk是指示用变量，当walk为0时表示被围住了
//x,y记录光标坐标；xc，yc记录猫位置 
//数组a用于记录地图，数组b用于深度优先搜索时记录已搜索的地区 
//以下函数中 road和road_walker就是猫的AI 
int road_walker(int xx,int yy)//用于递归逃脱路径 深度优先搜索 
{
	if(xx==0||yy==0||xx==8||yy==8)return 1;
	if(a[xx][yy]<99&&a[xx][yy]!=0)return a[xx][yy];
	b[xx][yy]=1;
	int k=99;//表示此路不通 
	int y_change;
	if(xx%2==0)y_change=yy-1;
	else y_change=yy+1;
	if(a[xx][yy+1]<100&&b[xx][yy+1]==0)
	{
		a[xx][yy+1]=road_walker(xx,yy+1);
		if(a[xx][yy+1]<k)k=a[xx][yy+1];
	} 
	if(a[xx][yy-1]<100&&b[xx][yy-1]==0)
	{
		b[xx][yy-1]=1;
		a[xx][yy-1]=road_walker(xx,yy-1);
		b[xx][yy-1]=0;
		if(a[xx][yy-1]<k)k=a[xx][yy-1];
	} 
	if(a[xx+1][yy]<100&&b[xx+1][yy]==0)
	{
		a[xx+1][yy]=road_walker(xx+1,yy);
		if(a[xx+1][yy]<k)k=a[xx+1][yy];
	} 
	if(a[xx+1][y_change]<100&&b[xx+1][y_change]==0)
	{
		a[xx+1][y_change]=road_walker(xx+1,y_change);
		if(a[xx+1][y_change]<k)k=a[xx+1][y_change];
	} 
	if(a[xx-1][yy]<100&&b[xx-1][yy]==0)
	{
		a[xx-1][yy]=road_walker(xx-1,yy);
		if(a[xx-1][yy]<k)k=a[xx-1][yy];
	} 
	if(a[xx-1][y_change]<100&&b[xx-1][y_change]==0)
	{
		a[xx-1][y_change]=road_walker(xx-1,y_change);
		if(a[xx-1][y_change]<k)k=a[xx-1][y_change];
	}
	b[xx][yy]=0;
	if(k==99)return k;
	return k+1;
}
int road()//计算最短逃脱路径的函数，返回0则表示跑不了了 
{
	int y_change,mk;
	if(xc%2==0)y_change=yc-1;
	else y_change=yc+1;
	int k=0;
	F(9)G(9)b[i][j]=0;
	F(9)G(9)if(a[i][j]<100)a[i][j]=0;
	b[xc][yc]=1;
	if(a[xc][yc+1]<100)
	{
		a[xc][yc+1]=road_walker(xc,yc+1);
		if(a[xc][yc+1]<90)k=1;
	} 
	if(a[xc][yc-1]<100)
	{
		a[xc][yc-1]=road_walker(xc,yc-1);
		if(a[xc][yc-1]<90)k=1;
	} 
	if(a[xc+1][yc]<100)
	{
		a[xc+1][yc]=road_walker(xc+1,yc);
		if(a[xc+1][yc]<90)k=1;
	} 
	if(a[xc+1][y_change]<100)
	{
		a[xc+1][y_change]=road_walker(xc+1,y_change);
		if(a[xc+1][y_change]<90)k=1;
	} 
	if(a[xc-1][yc]<100)
	{
		a[xc-1][yc]=road_walker(xc-1,yc);
		if(a[xc-1][yc]<90)k=1;
	} 
	if(a[xc-1][y_change]<100)
	{
		a[xc-1][y_change]=road_walker(xc-1,y_change);
		if(a[xc-1][y_change]<90)k=1;
	}
	//以下为弥补搜索时漏掉的一小部分路径进行的复查 
	for(i=1;i<8;i++)
	for(j=1;j<8;j++)
	if(a[i][j]<100)
	{
		if(i%2==0)y_change=j-1;
	    else y_change=j+1;
	    mk=100;
	    if(a[i][j+1]<mk)mk=a[i][j+1];
	    if(a[i][j-1]<mk)mk=a[i][j-1];
	    if(a[i+1][j]<mk)mk=a[i+1][j];
	    if(a[i+1][y_change]<mk)mk=a[i+1][y_change];
	    if(a[i-1][j]<mk)mk=a[i-1][j];
	    if(a[i-1][y_change]<mk)mk=a[i-1][y_change];
	    a[i][j]=mk==99?99:mk+1;
	}
	return k;
}
void cat_walk()
{
	int y_change;
	if(xc%2==0)y_change=yc-1;
	else y_change=yc+1;
	int move_x=xc,move_y=yc+1;
	if(1)
	{
		if(a[move_x][move_y]>a[xc][yc-1])move_y=yc-1;
		if(a[move_x][move_y]>a[xc+1][yc]){move_x=xc+1;move_y=yc;}
		if(a[move_x][move_y]>a[xc+1][y_change]){move_x=xc+1;move_y=y_change;}
		if(a[move_x][move_y]>a[xc-1][yc]){move_x=xc-1;move_y=yc;}
		if(a[move_x][move_y]>a[xc-1][y_change]){move_x=xc-1;move_y=y_change;}
	}
	a[xc][yc]=0;
	xc=move_x;
	yc=move_y;
	a[xc][yc]=999;
}
int cat_lose()
{
	F(9)G(9)
		if((i==0||j==0||i==8||j==8)&&a[i][j]==999)return 1;
	return 0;
}
int cat_win()
{
	if(xc%2==0)//位于无修正行 
	{
		if(a[xc][yc+1]==888&&a[xc][yc-1]==888&&a[xc-1][yc]==888&&a[xc-1][yc-1]==888&&a[xc+1][yc]==888&&a[xc+1][yc-1]==888)return 1;
		else return 0;
	}
	else//位于修正行 
	{
		if(a[xc][yc+1]==888&&a[xc][yc-1]==888&&a[xc-1][yc]==888&&a[xc-1][yc+1]==888&&a[xc+1][yc]==888&&a[xc+1][yc+1]==888)return 1;
		else return 0;
	}
}
void draw()//初始化地图 
{
	F(9)G(9)a[i][j]=0;
	/*for(i=0;i<9;i++)for(j=0;j<9;j++)a[i][j]=0;*/
	a[4][4]=999;//这是猫 
	x=4;
	y=3;
	xc=4;
	yc=4;
	int b[2];
	F(dif)
	{
		b[0]=rand()%81;
		b[1]=b[0]%9;
		b[0]=b[0]/9;
		if(a[b[0]][b[1]]==0)a[b[0]][b[1]]=888;//这是墙 
		else i--;
		Sleep(60);
	}
}
void clear(int ed)//刷新地图 
{
	system("cls");
	printf("\n\n");
	F(9)
	{
		if(i%2==1)printf(" ");
		printf("                              ");
		G(9)
		{
			if(i==x&&j==y&&ed==0)printf("▽");
			else
			{
				switch(a[i][j])
			    {
				    case 888:printf("◆");break;
				    case 999:printf("⊙");break;
				    default:printf("◇");break;
			    }
			}
		}
		printf("\n");
	}
	/*F(9)
	{
		G(9)printf("%4d",a[i][j]);
		printf("\n");
	}*/
	printf("\n                         WSAD移动坐标“▽”，回车键确认。\n");
}
int main()
{
	srand((unsigned int)(time(NULL)));
	int endc,win,found=0;
d:	printf("请输入墙的数量：（范围为0~80，超出范围会出现BUG）");
    scanf("%d",&dif);
	system("cls"); 
    printf("loading......");
	draw();
	clear(0);
	while(1)
	{
		endc=0;
		while(endc==0)
		{
			char choose;
b:			choose=getch();
			switch(choose)
			{
				case 13:if(a[x][y]<100){a[x][y]=888;endc=1;}break;
				case 'w':
				case 'W':if(x>0)x--;break;
				case 's':
				case 'S':if(x<8)x++;break;
				case 'a':
				case 'A':if(y>0)y--;break;
				case 'd':
				case 'D':if(y<8)y++;break;
				default:goto b;; 
			}
			clear(endc);
		} 
		if(cat_win())//判断猫是否被完全围住的函数 
		{
			win=1;
			break;
		}
		if(found==0)printf("\n                              猫猫思考中。。。");
		else printf("\n                              猫猫乱逛中。。。");
		Sleep(300); 
		if(walk==1)
		{
			walk=road();//最短逃脱路径计算
		}
		else
		{
			if(found==0)
			{
				printf("\n\n                              猫猫发现好像被围住了。。。\n\n                              猫猫乱逛中。。。");
		        Sleep(500);
		        found=1;
			}
			F(9)G(9)if(a[i][j]<100)a[i][j]=0;
		}
		cat_walk();//走猫函数
		clear(0); 
		if(cat_lose())//判断猫是否成功逃脱的函数 
		{
			win=0;
			break;
		}
	}
	if(win==1)printf("\n\n                              猫猫被困住了\n\n                              你成功地抓到了猫猫~");
	else printf("\n\n                              猫猫跑了。。。。。。\n\n                              下次继续加油吧！");
	getch();
	system("cls");
	walk=1;
	found=0;
	goto d;
	return 0;
}

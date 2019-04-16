#include<iostream>
#include<stdio.h>
#include<iomanip>
#include<cstdlib>
#include<ctime>
#include<conio.h>
void xuatgame(char a[])
{
	cout<<endl;
	cout<<"+---+---+---+---+---+---+---+---+---+---+"<<endl;
	cout<<"|   "<<"| "<<setw(1)<<0<<" "<<"| "<<setw(1)<<1<<" "<<"| "<<setw(1)<<2;
	cout<<" "<<"| "<<setw(1)<<3<<" "<<"| "<<setw(1)<<4<<" "<<"| "<<setw(1)<<5;
	cout<<" "<<"| "<<setw(1)<<6<<" "<<"| "<<setw(1)<<7<<" "<<"| ";
	cout<<setw(1)<<8<<" "<<"| "<<endl;
	for( int i=0; i<9; i++)
	{	
	cout<<"+---+---+---+---+---+---+---+---+---+---+"<<endl;
	cout<<"| "<<setw(1)<<i<<" | "<<setw(1)<<a[9*i+0]<<" "<<"| "<<setw(1)<<a[9*i+1];
	cout<<" "<<"| "<<setw(1)<<a[9*i+2]<<" "<<"| "<<setw(1)<<a[9*i+3]<<" "<<"| ";
	cout<<setw(1)<<a[9*i+4]<<" "<<"| "<<setw(1)<<a[9*i+5]<<" "<<"| ";
	cout<<setw(1)<<a[9*i+6]<<" "<<"| "<<setw(1)<<a[9*i+7]<<" "<<"| ";
	cout<<setw(1)<<a[9*i+8]<<" "<<"| "<<endl;
	}
	cout<<"+---+---+---+---+---+---+---+---+---+---+"<<endl;	
}
void taobom( int bom[])
{
	srand(time(0));
	for( int i=0; i<10; i++)
	{
		bom[i]=rand() %80+0;
	}	
}
void sobomthucte( int bom[],int &sobom)
{
	for( int i=0; i<5; i++)
	{
		for( int j=9; j>=5; j--)
		{
			if(bom[i]==bom[j])
			{
				for( int h=j; h<sobom; h++)
				{
					bom[h]=bom[h+1];
				}  
				sobom--;
			}
		}
	}
}
void gananso( char anso[], int bom[], int sobom)
{
	// Gan trang
	for( int i=0; i<81; i++)
	{
		anso[i]=' ';
	}
	// Gan bom
	for( int i=0; i<sobom; i++)
	{
		anso[bom[i]]='o';
	}
	// Gan so
	int flag[81];
	for( int i=0; i<81; i++)
	{
		flag[i]=0;
	}
	for( int i=0; i<sobom; i++)
	{
		for( int h=-1; h<2; h++)
		{
			for( int k=-1; k<2; k++)
			{
				if ((h==0)&&(k==0)) continue;
				if ((bom[i]%9)==0&&(k==-1)) continue;
				if ((bom[i]%9)==8&&(k==1)) continue;
				if (((bom[i]+9*h+k)<0)||((bom[i]+9*h+k)>80)) continue;
				flag[(bom[i]+9*h+k)]++;
			}
		}
	}
	for( int i=0; i<81; i++)
	{
		if (anso[i]=='o') continue;
		if (flag[i]==1) anso[i]='1';
		if (flag[i]==2) anso[i]='2';
		if (flag[i]==3) anso[i]='3';
		if (flag[i]==4) anso[i]='4';
		if (flag[i]==5) anso[i]='5';
		if (flag[i]==6) anso[i]='6';
		if (flag[i]==7) anso[i]='7';
		if (flag[i]==8) anso[i]='8';
		if (flag[i]==9) anso[i]='9';

	}
}
void mokhoangtrong( char hienthi[], char anso[], int m, int n)
{
	int i, j;
	for( i=-1; i<2; i++)
	{
		for( j=-1; j<2; j++)
		{
			if (hienthi[9*(m+i)+n+j]!='.') continue;
			if ((i==0)&&(j==0)) continue;
			if (n==0&&(j==-1)) continue;
			if ((n==8)&&(j==1)) continue;
			if (((9*(m+i)+n+j)<0)||((9*(m+i)+n+j)>80)) continue;
			if((anso[9*(m+i)+n+j])=='o') continue;	
			hienthi[9*(m+i)+n+j]=anso[9*(m+i)+n+j];
			if (anso[9*(m+i)+n+j]!=' ') { continue; }
			mokhoangtrong(hienthi, anso, m+i, n+j);		
		}
	}
}
void moso( char hienthi[], char anso[], int m, int n)
{
	hienthi[9*m+n]=anso[9*m+n];
}
void mobom( char hienthi[], int bom[], int sobom)
{
	cout<<endl<<" GAME OVER "<<endl;
	for( int i=0; i<sobom; i++)
	{
		hienthi[bom[i]]='o';
	}
}
void main()
{
	int m, n;
	int sobom=10;
	char hienthi[81];
	char anso[81];
	int bom[10];
	taobom( bom);
	sobomthucte( bom, sobom);
	gananso( anso, bom, sobom);
	for( int i=0; i<81; i++)
	{
		hienthi[i]='.';
	}
	// Game begin
	cout<<" Are you ready? "<<endl;
	cout<<" Let's begin"<<endl;
	xuatgame(hienthi);
	while(1)
	{
		int flag=0;
		cout<<" Let choose location to avoid bomb: ";
		cin>>m;
		cin>>n;
		// TH1: Mo khoang trong
		if( anso[9*m+n]==' ')
		{
			mokhoangtrong(hienthi, anso, m, n);
			xuatgame( hienthi);
			continue;
		}
		// TH2: Mo so 
		if(( anso[9*m+n]!=' ')&&( anso[9*m+n]!='o'))
		{
			moso( hienthi, anso, m, n);
			xuatgame( hienthi);
			continue;
		}
		//TH3: Mo bom
		if(( anso[9*m+n]='o'))
		{
			mobom(hienthi, bom, sobom);
			xuatgame( hienthi);
			break;
		}
		//TH: WIN
		for( int i=0; i<81; i++)
		{
			if( hienthi[i]=='.') flag++; 
		}
		if( flag==sobom )
		{
			cout<<" YOU WIN "<<endl;
			break;
		}
	}
	getch();
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SEP_LINE "--------------------------------"

void test( void );

int main()
{
    srand(time(0));
    int b;
    
    for ( int i = 0; ; ++i ){
    	int a = rand() % 10;
		int times = 1;
	    printf("猜一猜a是哪个数字？(注：a为一个0到9的整数)\n");
	    while(scanf("%d",&b) != EOF){
			if(b != a){
				printf("你猜错了，请再试一次！\n");
				times ++;
			}
			else{
				printf("你猜对了！这个数是%d!\n",a);
				printf("你一共猜了%d次\n",times);
				break;
			}
		}
		printf( SEP_LINE "\n" );
	}

//	test();
	
	return 0;
}

void test( void )
{
	srand( time(0) );
	int times = 0, range = 10;
	int a[10] = { 0 };
	
	for ( int i = 0; ; ++i, ++times ){
		int if_ok = 1;
		int num = rand() % range;
		a[num] = num;
		
		
		for ( int j = 0; j < range; ++j ){
			if ( a[j] != j ){
				if_ok = 0;
				break;
			}
		}

		if ( if_ok ) break;
	}
	
	printf("循环%d次,得到[0,%d]\n", times, range - 1 );
}

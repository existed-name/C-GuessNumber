/*	猜数游戏V1.0.0.20241221_Alpha	*/
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define BLANK4 "    "
#define SEP_LINE "--------------------------------"

struct record
{
	int target_num;
	int guess_times;
} rcd[100];

struct record2
{
	int round;
	int win_times;
	int make_trouble;	
} rcd2;

void intro( void );
int num_create( void );
void rcd_init( int i );
int guess_false( int guess_cnt );
void guess_judge( int i, int target );
int if_continue( void );
void grade_show( void );

int main( int argc, char *argv[] )
{
	intro();
	
	for ( int i = 0; ; ++i ){
		printf( SEP_LINE "\n");
		
		rcd_init( i );
		int target = rcd[i].target_num;	
		guess_judge( i, target );
		
		if ( if_continue() == 0 ) break;
	}
	
	grade_show();
	
	return 0;
}

void intro( void )
{
	printf("\t\t欢迎来到猜数游戏!\n");
	printf( BLANK4 "系统会给出一个10以内的自然数(0到10),"
		"你需要输入你猜的数\n"
		BLANK4 "tips:这个数不会变,可以试几个数从而排除这些数,缩小猜测范围\n"
		BLANK4 "cautions:猜错太多次会被系统判定为捣乱,记作违规!\n"
		BLANK4 "游戏开始,加油特种兵┗|｀O′|┛\n"
	);	
}

void rcd_init( int i )
{
	rcd[i].target_num = num_create();
	rcd[i].guess_times = 0;
	rcd2.round = i + 1;
	
	if ( i == 0 ){
		rcd2.win_times = 0;
		rcd2.make_trouble = 0;	
	}		
}

int num_create( void )
{
	srand( time( 0 ) );
	int a = rand();
	return a % 11;
}

void guess_judge( int i, int target )
{
	printf("\t\t第%d轮游戏\n", rcd2.round );
	printf("请输入你猜的数并按下enter键:\t");
	
	int input_num;
	scanf("%d", &input_num );
	
	int legal = 1;
	while ( input_num != target ){
		rcd[i].guess_times ++;
		
		if ( guess_false( rcd[i].guess_times ) ){
			legal = 0;
			rcd2.make_trouble ++;
			printf( BLANK4 "你被系统踢出了房间~\n");
			break;
		}
		
		printf("请重新输入你猜的数并按下enter:\t");
		scanf("%d", &input_num );
	}
	
	if ( legal ) {
		rcd[i].guess_times ++;
		rcd2.win_times ++;
		printf( BLANK4 "猜对了!这个数是%d,这一轮游戏你猜了%d次\n", target, rcd[i].guess_times );
	} else{
		printf("注意:乱按键盘会被系统劝退~\n");
	}
	
//	return legal;
}

int guess_false( int guess_cnt )
{
//	char *words = ( char * ) malloc( 20 * sizeof( char ) );
	char *words = NULL;
	int if_ban = 0;
	
	switch ( guess_cnt ) {
		case 17 :
			words = "系统察觉到你在捣乱,并扔出了一个\"gui!\"";
			if_ban = 1;
			break;
		case 14 :
			words = "(′д｀ )…彡…彡 猜错 x 14";
			break;
		case 13 :
			words = "┭┮﹏┭┮ 猜错 x 13";
			break;
		case 12 :
			words = "系统:逆天了";
			break;
		case 11 :
			words = "非酋王!";
			break;
		case 10 :
			words = "<真 * 排除法>";
			break;
		case 9 :
			words = "正常情况下还剩2个数了吧...";
			break;
		case 8 :
			words = "屏幕面前的是人机?";
			break;
		case 7 :
			words = "一种人们经常吃的绿色植物";
			break;
		case 6 :
			words = "辱彬逊说的是你嘛~";
			break;
		case 5 :
			words = "又双叒叕猜错了~";
			break;
		case 4 :
			words = "又双叒猜错了~";
			break;
		case 3 :
			words = "又双猜错了~";
			break;
		case 2 :
			words = "又猜错了~";
			break;
		case 1 :
			words = "猜错了~";
			break;
		default :
			words = "(╯▔皿▔)╯系统有点生气了";
			break;
	}
	
	printf( BLANK4 "%s\n", words );
//	free( words );

	return if_ban;
}

int if_continue( void )
{
	printf("本轮游戏结束,下一轮游戏请按1,退出请按0:\t");
	
	int if_ctnue;
	scanf("%d", &if_ctnue );
	
	if ( if_ctnue ){
		printf( BLANK4 "下一轮游戏即将开始,祝你好运!\n");
	} else{
		printf( BLANK4 "欢迎下次再来!\n");	
	}
	
	return if_ctnue;
}

void grade_show( void )
{
	printf( SEP_LINE "\n");
	printf( BLANK4 "你的战绩如下:\n");
	printf( "游戏总场次:\t%d\n"
			"违规次数:\t%d\n",
			rcd2.round, rcd2.make_trouble
	);
	
	for ( int i = 1; i <= rcd2.round; ++i ){
		printf("第%d场游戏:\t目标数为%d,猜数次数%d\n",
				i, rcd[ i - 1 ].target_num, rcd[ i - 1 ].guess_times
		);
	}
}

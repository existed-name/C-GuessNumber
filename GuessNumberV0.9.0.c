/*			序言
	工程能力很大程度上是从项目实践
而非刷题中锻炼的,既应该通过刷题来训
练自己的思维能力、算法能力以及获得一
些编程技巧,又应该多写项目(小游戏、小
程序),培养工作所需的工程能力(涵盖多方
面)
	上一次做的井字棋对我很有启发,昨
晚和蓝心小V的一次对话也提醒了我要把
诸多项目坚持下去,以培养自己的"工程能
力"
	2024.12.21.星期6 ~ 12.22星期7,
2~3个小时,借助曾经的思路、框架完成
了这个猜数游戏的基础功能--介绍说明、
读入并分析数据、输出结果,并也有了进
一步完善、更新的思考方向
	这第一款测试版本的猜数游戏的版
本号为猜数游戏V0.9.0.20241222_Alpha,
目前正致力于1.0.0版本的开发,同时也会
更新相应的开发日志
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void intro( void );

int num_create( void );
int guess_false( int guess_cnt );

int main( int argc, char *argv[] )
{
	intro();
	printf("请输入你猜的数并按下enter键:\t");
	
	int num = num_create();
	int guess_cnt = 0;
	int temp = -1;
	
	while ( 1 ){
		scanf("%d", &temp );
		if ( temp == num ){
			guess_cnt++;
			break;
		}
		guess_cnt++;
		if ( guess_false( guess_cnt ) ){
			printf("你被系统踢出了房间~\n");
			goto out1;
		};
		printf("请输入你猜的数并按下enter键:\t");
	}
	
	printf("    猜对了!你一共猜了%d次\n", guess_cnt );
	
	out1 : return 0;
}

void intro( void )
{
	printf("\t\t欢迎来到猜数游戏!\n");
	printf("    系统会给出一个10以内的自然数,"
		"你需要输入你猜的数\n"
		"    tips:这个数不会变,可以用排除法排除一些数\n"
		"    游戏开始,加油特种兵┗|｀O′|┛\n"
	);	
}

int num_create( void )
{
	srand( time( 0 ) );
	int a = rand();
	return a % 11;
}

int guess_false( int guess_cnt )
{
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
			words = "还剩2个数,极限二选一!";
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
	
	printf("    %s\n", words );

	return if_ban;
}

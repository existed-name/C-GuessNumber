/*	猜数游戏V2.0.0.20250207_Alpha	*/
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#define BLOCK_SIZE 25
#define BLANK4 "    "
#define SEP_LINE "--------------------------------"

//模式选择:经典(1),提示(2),挑战(3),轮回(4)(原变量模式),
enum MODE { Classic_Mode = 1, Hint_Mode, Challenge_Mode, Samsara_Mode, };
//使用枚举是为了在switch-case时避免用magic digit,而提高可读性
char *modename[] = {
	"经典模式",
	"提示模式",
	"挑战模式",
	"轮回模式",
};

char *modeintro[] = {
	"给出1个[0,10]内的整数(该数保持不变),由玩家猜数",
	"数据范围[0,20](整数),但可以提示玩家所猜数相对目标数较大/较小",
	"经典模式+限制猜数次数",
	"经典模式but每猜错1次,目标数会变成[0,10]内的任一数(可能和原来一样)",
};

const int numofmode = 4;//模式数量
const int block_range = 10;//1个block_range为1单位数据范围,用于num_create()

/*	各模式共用结构成员	*/
struct shared_record
{
	int game_round;
	int target_num;
	int guess_times;
	int mode;
} rcd[BLOCK_SIZE * 2];

/*	各模式结构体	*/
//经典模式
struct classicmode_rcd
{
	char *if_violate;
} rcd1[BLOCK_SIZE];

struct classicmode_rcd_
{
	int violation;
	int ban_round;
} rcd_1;
//提示模式
struct hintmode_rcd
{
	int hint_times;
} rcd2[BLOCK_SIZE];
//挑战模式
struct challengemode_rcd
{
	int limit_times;
	char *challenge_result;
} rcd3[BLOCK_SIZE];

struct challengemode_rcd_
{
	int win_times;
} rcd_3;
//轮回模式(原variable_mode)
struct samsaramode_rcd
{
	int target_array[BLOCK_SIZE * 2];
} rcd4[BLOCK_SIZE];

/*	游戏次数结构体	*/
struct game_cnt
{
	int classic;
	int hint;
	int challenge;
	int samsara;
	int total_round;
} gamecnt;

/*	充当程序框架的函数	*/
void mode_intro( void );
void rcd_initial( int mode, int i );
int mode_select( int i );
int num_create( int range );
int input_num( int i );
void guess_right( int i );
int if_continue( void );
void game_count( int mode );
void mode_continue( int mode, int i );
void grade_show( void );

/*	用作猜数功能的函数	*/
//经典模式
void classic_mode( int i );
void classic_judge( int i, int input, int target );
int classic_reply( int guess_cnt );
//提示模式
void hint_mode( int i );
void hint_judge( int i, int input, int target );
int hint_getdegree( int difference );
void hint_getreply( char *reply, int degree );
void hint_get_replyadd( char *reply_add, int degree );
//挑战模式
void challenge_mode( int i );
int challenge_setlimit( void );
void challenge_ifguide( int *input, int target );
void challenge_judge1( int input, int target );
int challenge_judge2( int j, int limit, int input, int target );
void chllenge_godfavor( int target );
//轮回模式(原变量模式)
void samsara_mode( int i );
void samsara_F_reply( int j );
void samsara_T_reply( int j );

int main( int argc, const char *argv[] )
{	
	mode_intro();
	int mode = 0, if_ctnue = -1;
	printf("\t\tPS:按下数字后记得按enter键\n");
	
	for ( int i = 0; ; ++i ){
		printf( SEP_LINE "\n第%d轮游戏\n", i + 1 );
		
		if ( if_ctnue == 2 ) mode_continue( mode, i );
		else mode = mode_select( i );
		
		game_count( mode );
		
		if_ctnue = if_continue();
		if ( if_ctnue == 0 ) break;
	}
	
	grade_show();
}

/*充当程序框架的函数*/
void mode_intro( void )
{
	printf("\t\t欢迎来到猜数游戏!\n" BLANK4 "以下是游戏模式介绍!\n" );
	for ( int i = 0; i < numofmode; ++i ){
		printf("模式%d : %s--%s\n", i + 1, modename[i], modeintro[i] );
	}
}

void rcd_initial( int mode, int i )
{
	//game_cnt初始化
	if ( i == 0 ){
		gamecnt.classic = 0;
		gamecnt.hint = 0;
		gamecnt.challenge = 0;
		gamecnt.samsara = 0;	
	}
	gamecnt.total_round = i + 1;
	//classicmode_rcd_以及challengemode_rcd_初始化
	if ( i == 0 ){
		rcd_1.violation = 0;
		rcd_1.ban_round = 0;
		rcd_3.win_times = 0;
	}
	//shared_rcd初始化
	rcd[i].game_round = i + 1;
	if( mode != 2 ) rcd[i].target_num = num_create( block_range );
	rcd[i].guess_times = 0;
	//记录游戏模式&目标数,rcd1234初始化
	rcd[i].mode = mode;
	switch ( mode ) {
		case Classic_Mode ://经典模式
			rcd1[ gamecnt.classic ].if_violate = NULL;
			break;
		case Hint_Mode ://提示模式
			rcd[i].target_num = num_create( block_range * 2 );
			rcd2[ gamecnt.hint ].hint_times = 0;
			break;
		case Challenge_Mode ://挑战模式,但其结构体成员只有win_times需要初始化为0
			break;
		case Samsara_Mode ://轮回模式
			rcd4[ gamecnt.samsara ].target_array[0] = rcd[i].target_num;
			break;
	}
}

int mode_select( int i )
{	
	int option = 1;
	printf("请输入你选择模式的序号,并按下enter键:\t");	
	do{
		scanf("%d", &option );
		if ( 1 <= option && option <= numofmode ){
			rcd_initial( option, i );
			printf("\t\t%s即将开始,特种兵请准备!\n", modename[i - 1] );
		}
		
		switch ( option ) {
			case Classic_Mode :
				classic_mode( i );
				break;
			case Hint_Mode :
				hint_mode( i );
				break;
			case Challenge_Mode :
				challenge_mode( i );
				break;
			case Samsara_Mode :
				samsara_mode( i );
				break;
			default :
				printf("你输入的序号有误,请重新输入并按下enter:\t");
				break;//continue;
		}
	} while ( option < 1 || option > numofmode );
	
	return option;
}

int num_create( int range )
{
	srand( (unsigned int) time( NULL ) );
	int a = rand();
	return a % ( range + 1 );//rand() % 11, % 21
}

int input_num( int i )
{
	printf("%s开始,加油特种兵!\n"
		   "请输入你猜的数并按下enter键:\t",
		   modename[i - 1] );
	int input;
	scanf("%d", &input );
	return input;
}

void guess_right( int i )
{
	printf( BLANK4 "猜对了!这个数是%d,这一轮游戏你猜了%d次\n",
			rcd[i].target_num, rcd[i].guess_times );
}

int if_continue( void )
{
	printf( BLANK4 "按任意键继续\n" );
	getchar();
	printf("\n本轮游戏结束,切换模式请按2,继续该模式请按1,退出游戏请按0:\t");
	
	int if_ctnue = 0;
	scanf("%d", &if_ctnue );
	
	if ( if_ctnue == 2 ){
		;
	} else if ( if_ctnue == 1 ){
		printf( BLANK4 "下一轮游戏即将开始,祝你好运!\n");
	} else{
		printf( BLANK4 "欢迎下次再来!\n");	
	}
	
	return if_ctnue;
}

void game_count( int mode )
{
	switch ( mode ) {
		case Classic_Mode :
			gamecnt.classic ++;
			break;
		case Hint_Mode :
			gamecnt.hint ++;
			break;
		case Challenge_Mode :
			gamecnt.challenge ++;
			break;
		case Samsara_Mode :
			gamecnt.samsara ++;
			break;
	}
}

void mode_continue( int mode, int i )
{
	switch ( mode ) {
		case Classic_Mode :
			classic_mode( i );
			break;
		case Hint_Mode :
			hint_mode( i );
			break;
		case Challenge_Mode :
			challenge_mode( i );
			break;
		case Samsara_Mode :
			samsara_mode( i );
			break;
	}	
}

void grade_show( void )
{
	printf( SEP_LINE "\n" BLANK4 "你的战绩如下:\n" );

	int classic_cnt = 0, hint_cnt = 0, challenge_cnt = 0, samsara_cnt = 0 ;
	for ( int i = 0; i < gamecnt.total_round; ++i ){
		int mode = rcd[i].mode;
		switch ( mode ) {
			case 1 :
				printf("第%d场游戏:\t%s\t目标数%d,猜数次数%d,%s\n",
						i + 1, modename[mode], rcd[i].target_num, rcd[i].guess_times,
						rcd1[ classic_cnt ].if_violate );
				classic_cnt ++;
				break;
			case 2 :
				printf("第%d场游戏:\t%s\t目标数%d,猜数次数%d,提示次数%d\n",
						i + 1, modename[mode], rcd[i].target_num, rcd[i].guess_times,
						rcd2[ hint_cnt ].hint_times );
				hint_cnt ++;
				break;
			case 3 :
				printf("第%d场游戏:\t%s\t目标数%d,猜数次数%d,限制次数%d,挑战结果:%s\n",
						i + 1, modename[mode], rcd[i].target_num, rcd[i].guess_times,
						rcd3[ challenge_cnt ].limit_times, rcd3[ challenge_cnt ].challenge_result );
				challenge_cnt ++;
				break;
			case 4 :
				printf("第%d场游戏:\t%s\t目标数%d,猜数次数%d,限制次数%d,挑战结果:%s\n",
						i + 1, modename[mode], rcd[i].target_num, rcd[i].guess_times,
						rcd3[ challenge_cnt ].limit_times, rcd3[ challenge_cnt ].challenge_result );
				samsara_cnt ++;
				break;
		}
	}
	
	printf("游戏总场次:\t%d\n", gamecnt.total_round );
	printf("经典模式:\t%d场,违规%d场\n", gamecnt.classic, rcd_1.violation );
	printf("提示模式:\t%d场\n", gamecnt.hint );
	printf("挑战模式:\t%d场,挑战成功%d场\n,", gamecnt.challenge, rcd_3.win_times );
	printf("轮回模式:\t%d场\n", gamecnt.samsara );
}

/*用作猜数功能的函数*/
//经典模式
void classic_mode( int i )
{
	printf( "提示:可以用排除法~\n"
			"注意:由于[0,10]只有11个数,最多猜11次必中,太多次猜错会被系统判定为故意送人头!\n");
			
	int input = input_num( rcd[i].mode );
	rcd[i].guess_times ++;
	classic_judge( i, input, rcd[i].target_num );
	gamecnt.classic ++;
}

void classic_judge( int i, int input, int target )
{
	int legal = 1;
	while ( input != target ){
		rcd[i].guess_times ++;
		
		if ( classic_reply( rcd[i].guess_times ) ){
			legal = 0;
			rcd_1.violation ++;
			rcd_1.ban_round = 3;
			printf( BLANK4 "你被系统踢出了房间,并且%d轮游戏内不可以玩该模式~\n"
					, rcd_1.ban_round );
			rcd1[i].if_violate = "有违规行为";
			break;
		}
		
		printf("请重新输入你猜的数并按下enter:\t");
		scanf("%d", &input );
	}
	
	if ( legal ) {
		rcd1[i].if_violate = "无违规行为";
		guess_right( i );
	} else {
		printf("注意:乱按键盘会被系统劝退~\n");
	}
}

int classic_reply( int guess_cnt )
{
	char *reply[] = {
		"猜错了~",
		"又猜错了~",
		"又双猜错了~",
		"又双叒叕猜错了~",
		"又双叒猜错了~",
		"辱彬逊说的是你嘛~",
		"一种人们经常吃的绿色植物",
		"屏幕面前的是人机?",
		"正常情况下还剩2个数了吧...",
		"<真 * 排除法>",
		"非酋王!",
		"系统:逆天了",
		"┭┮﹏┭┮ 猜错 x 13",
		"(′д｀ )…彡…彡 猜错 x 14",
		"(╯▔皿▔)╯系统有点生气了",
		"(╯▔皿▔)╯系统有点生气了",
		"系统察觉到你在捣乱,并扔出了一个\"gui!\"",
	};
	
	char *words = NULL;
	int if_ban = 0;
	
	words = reply[ guess_cnt - 1 ];
	if ( guess_cnt == 17 ) if_ban = 1;
	
	printf( BLANK4 "%s\n", words );

	return if_ban;
}

//提示模式
void hint_mode( int i )
{	
	printf("提示:可以采用二分思想,不断对半分,缩小目标范围~\n"
		   "注意:数据范围是[0,%d]喔\n", block_range * 2 );
	int input = input_num( rcd[i].mode );
	rcd[i].guess_times ++;
	int target_num = rcd[i].target_num;
	hint_judge( i, input, target_num );
	gamecnt.hint ++;
}

void hint_judge( int i, int input, int target )
{
	char *reply = NULL, *reply_add = NULL;
	
	while ( input != target ){
		int difference = input - target;
		int degree = hint_getdegree( difference );
		
		hint_getreply( reply, degree );
		hint_get_replyadd( reply_add, degree );
		
		printf( BLANK4 "%s\n" BLANK4 "%s(请输入):\t", reply, reply_add );
		scanf("%d", &input );
		
		rcd2[ gamecnt.hint ].hint_times ++;
		rcd[i].guess_times ++;
	}
	
	guess_right( i );
}

int hint_getdegree( int difference )
{
	int degree = 0;
	
	if ( difference > 10 ){
		degree = 1;
	} else if ( difference > 6 ){
		degree = 2;
	} else if ( difference > 3 ){
		degree = 3;
	} else if ( difference < -10 ){
		degree = -1;
	} else if ( difference < -6 ){
		degree = -2;
	} else if ( difference < -3 ){
		degree = -3;
	} else if ( abs( difference ) > 1 ){
		degree = 4;
	} else {
		degree = 5;
	}	
	
	return degree;
}

void hint_getreply( char *reply, int degree )
{
	const int sentence_num = 8;
	struct hint_reply
	{
		int Degree;
		char *Sentence;
	} Reply[ sentence_num ];
	
	Reply[0].Degree = -1, Reply[0].Sentence = "你猜的数太小了~";
	Reply[1].Degree = -2, Reply[1].Sentence = "这个数小了呜(。_。)~";
	Reply[2].Degree = -3, Reply[2].Sentence = "小了点O_O";
	Reply[3].Degree = 1, Reply[3].Sentence = "你猜的数太大了~";
	Reply[4].Degree = 2, Reply[4].Sentence = "这个数大了嗷(*゜ー゜*)~";
	Reply[5].Degree = 3, Reply[5].Sentence = "还是大了点(⊙o⊙)";
	Reply[6].Degree = 4, Reply[6].Sentence = "很接近了!q(≧▽≦q)";
	Reply[7].Degree = 5, Reply[7].Sentence = "极限位置!( $ _ $ )";
	
	for ( int j = 0; j < sentence_num; ++j ){
		if ( degree == Reply[j].Degree ){
			reply = Reply[j].Sentence;//printf( BLANK4 "%s\n", reply );
			break;
		}
	}
}


void hint_get_replyadd( char *reply_add, int degree )
{
	char *Reply_Add[] = {
		"还差亿点,曙光尚存",
		"既出一步,更有千里",
		"范围已定,指日可待",
		"近在咫尺,唾手可得",
		"一步之遥,可否一发入魂",
	};
	reply_add = Reply_Add[ abs( degree ) - 1 ];//printf( BLANK4 "%s(请输入:)\t", reply_add );
}

//挑战模式
void challenge_mode( int i )
{
	int limit = challenge_setlimit();
	int target = rcd[i].target_num;
	int input;
	
	if ( limit == 1 ){
		challenge_ifguide( &input, target );
		challenge_judge1( input, target );
		rcd[i].guess_times ++;
	} else {
		printf("那么挑战开始!系统将为你祈福!\n");
		for ( int j = limit; j > 0; --j, ++ rcd[i].guess_times ){
			printf("挑战者,给出你之所想(请猜数:)\t");
			scanf("%d", &input );
			
			int if_win = challenge_judge2( j, limit, input, target );
			if ( if_win ) break;
			
			if ( j == 1 ) chllenge_godfavor( target );
		}
	}
}

int challenge_setlimit( void )
{
	int *limit = &rcd3[ gamecnt.challenge ].limit_times;
	printf("挑战者,输入你的猜数限制次数吧(≤6):\t");
	while ( scanf("%d", limit ) != EOF ){
		if ( *limit > 6 ){
			printf("挑战者,莫要怯懦,系统会庇佑你!(重新输入更小的限制次数:)\t");
		} else if ( *limit <= 0 ){
			printf("挑战者,兵不血刃岂易求得?(重新输入正整数:)\t");
		} else {
			if ( *limit == 1 ){
				printf("勇士,你可知一着不慎之理?确定要走这条路?(是1,否0,请输入:)\t");
				int IF; scanf("%d", &IF );
				if ( IF ) printf("这位挑战者想必是欧皇挂王天选之子之流~~~\n");
				else {
					printf("那便另寻他路罢(重新输入:)\t");
					continue;
				}
			}
			else if ( *limit <= 3 ) printf("这位挑战者很勇的样子!\n");
			
			break;
		}
	}
	
	return *limit;
}

void challenge_ifguide( int *input, int target )
{
	printf("勇士,需要吾的指引么?(是1,否0,请输入:)\t");
	int IF; scanf("%d", &IF );
	if ( IF ){
		int left = target - num_create( 2 );
		int right = target + num_create( 2 );//运气好是可以left = target = right的
		printf("目标范围在[%d,%d],祝你好运!(请输入:)\t", left, right );
	} else {
		printf("那便一决胜负吧!(请输入:)\t");
	}
	scanf("%d", input );
}

void challenge_judge1( int input, int target )
{
	if ( input == target ){
		printf("一步登天!勇士,沐浴胜利的光辉吧!\n");
		rcd3[ gamecnt.challenge ].challenge_result = "victory";
	} else {
		printf("<甚是遗憾--下次再战>\n");
		rcd3[ gamecnt.challenge ].challenge_result = "defeat";
	}
}

int challenge_judge2( int j, int limit, int input, int target )
{
	int if_win = 0;
	char *wrong_reply[] = {
		"可惜可叹,挑战者下次再会罢!",
		"最后1次机会,能否一锤定音?",
		"仅剩还有2次机会,稳住能赢!",
		"尚有3次机会,切勿放弃!",
		"还有4次机会,勿焦勿躁!",
		"还有5次机会,机会仍然多多!",
	};
	
	if ( input == target ){
		if ( j == limit ){
			printf("一剑封喉!挑战者竟恐怖如斯!\n");
		} else {
			printf("挑战成功,荣登胜利之殿!\n");
		}
		rcd3[ gamecnt.challenge ].challenge_result = "victory";
		if_win = 1;
	} else {
		printf("%s\n", wrong_reply[j - 1] );
		if ( j == 1 ){
			rcd3[ gamecnt.challenge ].challenge_result = "defeat";
		}
	}
	
	return if_win;
}

void chllenge_godfavor( int target )
{
	int specific_num = 2;
	int if_favor = num_create( specific_num );//获得的数在[0,specific_num]
	if ( if_favor != specific_num ) return;//那么有1/3(0,1,2)的概率获得神之眷顾
	
	printf("挑战者,幸运之神眷顾了你!\n");
	int left = target - num_create( specific_num );
	int right = target + num_create( specific_num );
	if ( left == target && target == right ) right ++;
	printf("神曰:它落在[%d,%d]!\n", left, right );
}

//轮回模式
void samsara_mode( int i )
{
	printf( BLANK4 "<轮回之境>\n"
		   "传说无数人在此陷入轮回~~~\n"
		   "唯有领悟真谛者得到超脱~~~\n" );
		   
	int input = -1, target = -2;
	for ( int j = 0; input != target; ++ rcd[i].guess_times ){
		target = rcd4[ gamecnt.samsara ].target_array[j];
		
		printf("说出你的真谛(请输入:)\t");
		scanf("%d", &input );
		
		if ( input == target ){
			samsara_T_reply( j );
		} else {
			samsara_F_reply( j );
		}
		
		rcd4[ gamecnt.samsara ].target_array[++j] = num_create( block_range );
	}
	
	printf("你站在轮回之境外面,盯着里面深邃的虚空出神...\n");
}

void samsara_F_reply( int j )
{
	char *false_reply[] = {
		"轮回现身了",
		"轮回离你更近一步",
		"轮回的触手抓住了你",
		"轮回的触手爬满了你的身体",
		"轮回将你包裹、吞噬",
		"你一头扎进一团混沌中",
		"你开始下沉",
		"你不断下沉,似乎看到一条裂缝",
		"你愈沉愈深,看清楚了--如同深渊般的巨大裂谷",
		"你沉到谷口,发现周围众多黑影悬浮,或是同你一样地下沉",
		"你\"游\"近了观察,竟是活生生的人--体温、呼吸、心跳一切正常,唯独眼球死盯谷底,甚至没有一丝转动,最多眨眨眼睛",
		"你感到无比惊恐,但好奇心驱使你顺着轮回之力往谷底沉去",
		"突然!你感到意识似乎触电般\"抽搐\",你昏昏沉沉",
		"过去的记忆在你眼前如同影视般放映,你死盯着\"影视\",眼球维持着\"死盯\"的状态,但意识更加朦胧",
		"视频从你出生一直到现在,又不停地循环播放",
		"眼前突然一黑",
		"睁开双眼,你看到一个蛋糕,插着的'4'形蜡烛闪动着微光,旁边是陌生但又熟悉的一男一女,戴着三角形帽子,鼓掌唱歌",
		"一天,他们把你带进了一个地方,他们温和地跟你说了很久便走了。那里有很多哭闹的小朋友,你好像知道但又不知道他们为什么哭闹",
		"玩过了几年,你进了市重点初中,你终于感到一些压力,但你凭借着天赋、努力以及一种熟悉的感觉,过得风生水起",
		"高中,你对头脑的掌控愈加熟练,从前意识里的那个熟悉的感觉也越来越淡",
		"高考放榜,你感到空前舒畅,但习惯扮演尖子生的你容不得一丝懈怠,马上开始了新的\"卷途\",但互联网上的各种声音也让你感到无比焦虑",
		"你追求着绩点,追求着综测,追求着科研经历,忙碌,劳累",
		"收到保研的消息后,你躺在寝室床上,回忆高考结束的解脱以及中第的欣喜",
		"下了床,你打开了多年未玩的游戏,沉浸了一下午",
		"晚上,你兴致大发,出去散步,规划着未来,幻想着未来,只觉得无比兴奋",
		"你不想待在新的阶层的底层,于是开始了新的忙碌与劳累,比过去有过之而无不及",
		"你全身心投入到导师(你很幸运选到了一个不错的导师)不断推给你的项目,翻阅一沓沓文献,重复一遍遍实验,进行一次次讨论",
		"后来你发现自己并不喜欢科研,现实的许多跟你曾经的幻想大相径庭",
		"某天不由自主摸鱼,你终于开始思考你真正想要什么,是国奖?是SCI一作?是大厂起薪50+?",
		"\"生活的真谛是什么?\"你无从得知",
		"多年后,你白发苍苍,褶皱遍体,静卧榻上,眼皮欲闭,满堂子孙,满室伤悲"
		"\"生活的真谛是什么?\"你喃喃一句,便闭上双眼突然",
		"<一世轮回 ·终>",
		"你的意识竟未消散,同时多年前那种熟悉的感觉蔓延开来",
		"你感到天昏地旋,忽然听到一丝苍老有力的声音盘旋耳边",
		"\"轮回之境生轮回,轮回之渊历轮回,真谛之念破轮回,真谛之庐渡轮回\"",
		"你突然回神,发现漂浮在一个峡谷中央,周围许多人形黑影同你一样漂着",
		"你摇着头,努力搜索着脑海,\"这是梦?\"掐一下自己,你感觉到了痛",
		"\"是梦是梦,梦终即醒,非梦非梦,历练不尽\"",
		"你大惊,又发现脑海中似乎有两套记忆!一套记忆原属这个身体,另一套则是刚刚\"梦\"中近百年的记忆",
		"",
	};
	
	printf("%s...\n", false_reply[j] );
}

void samsara_T_reply( int j )
{
	char *true_reply[] = {
		"你很幸运,没有遇到轮回",
		"你绕开了轮回",
		"你挣脱了轮回的触手",
		"那些触手突然缩了回去,放开了你",
		"轮回浑身颤动,把你吐了出来",
		"混沌将你弹出了轮回之腹",
		"一股浮力将你送出轮回之腹",
		"你被一枚囊泡状的球包裹,飘出了轮回",
		"裂谷喷射出一连串气泡,你被带出了轮回",
		"",
		"你在陷入轮回之前逃离了它",
		"",
		"",
		"",
		"",
		"看来你破了这轮回",
		"你逃出了轮回之境",
	};
	
	printf("%s...\n", true_reply[j] );
}

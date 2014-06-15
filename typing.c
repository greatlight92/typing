#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include <sys/timeb.h>

// 화면의 너비값, Frame을 그릴때에 사용됨
#define	WIDTH	80

// 키코드
#define	KEY_UP		65
#define	KEY_DOWN	66
#define	KEY_RIGHT	67
#define	KEY_LEFT	68
#define	KEY_ENTER	10
#define	KEY_ESC		27

// 메뉴 ID 상수
#define	MID_JARI	1
#define	MID_NATMAL	2
#define	MID_SHORT	3
#define	MID_LONG	4
#define	MID_EXIT	5

// ANSI Color 상수
#define COLOR_BLACK		0
#define COLOR_RED		1
#define COLOR_CYAN		6
#define COLOR_WHITE		7
#define COLOR_RESET		9

/*
	작성자	: 김지수
	함수명	: beginFrame
	용도		: UI의 상단Frame을 그려줌
*/
void beginFrame();

/*
	작성자	: 김지수
	함수명	: endFrame
	용도		: UI의 하단Frame을 그려줌
*/
void endFrame();

/*
	작성자	: 김지수
	함수명	: printLine
	용도		: UI의 Frame 라인을 그려줌
*/
void printLine();

/*
	작성자		: 김지수
	함수명		: setPage
	용도			: 페이지를 메뉴ID값대로 이동시켜줌
	인자값
		mnuID	: 메뉴 ID값
*/
int setPage(int mnuID);

/*
	작성자		: 김지수
	함수명		: onMenu
	용도			: 페이지를 메뉴ID값대로 이동시켜줌
*/
void onMenu();

/*
	작성자		: 김지수
	함수명		: printMenu
	용도			: 메뉴들을 출력해줌
	인자값
		mnuID	: 메뉴 ID값
*/
void printMenu(int mnuID);

/*
	작성자		: 김지수
	함수명		: onChangeMenu
	용도			: 메뉴 커서를 바꿔 츨력해줌
	인자값
		mnuID	: 메뉴 ID값
*/
void onChangeMenu(int mnuID);

/*
	작성자		: 김지수
	함수명		: onJari
	용도			: 자리연습 페이지로 이동
*/
void onJari();

/*
	작성자		: 김지수
	함수명		: printJari
	용도			: 자리연습 화면 출력해줌
*/
void printJari();

/*
	작성자		: 김지수
	함수명		: onChangeJari
	용도			: 자리연습 화면 갱신해줌
	인자값
		right_count	: 맞게 입력한 수
		all_count	: 전체 입력한 수
		max			: 총 자리 개수
		ota_count	: 오타 개수
*/
void onChangeJari(int right_count, int all_count, int max, int ota_count);

/*
	작성자		: 김지수
	함수명		: printJariResult
	용도			: 자리연습 결과 출력해줌
	인자값
		right_count	: 맞게 입력한 수
		all_count	: 전체 입력한 수
		max			: 총 자리 개수
		ota_count	: 오타 개수
*/
void printJariResult(int right_count, int all_count, int max, int ota_count);

/*
	작성자		: 김지수
	함수명		: onNatmal
	용도			: 낱말연습 페이지로 이동
*/
void onNatmal();
/*
	작성자		: 김지수
	함수명		: printNatmal
	용도			: 낱말연습 화면 출력해줌
*/
void printNatmal();
/*
	작성자		: 김지수
	함수명		: onChangeNatmal
	용도			: 낱말연습 화면 갱신해줌
	인자값
		right_count	: 맞게 입력한 수
		all_count	: 전체 입력한 수
		max			: 총 자리 개수
		ota_count	: 오타 개수
*/
void onChangeNatmal(int right_count, int all_count, int max, int ota_count);
/*
	작성자		: 김지수
	함수명		: printNatmalResult
	용도		: 낱말연습 결과 출력해줌
	인자값
		right_count	: 맞게 입력한 수
		all_count	: 전체 입력한 수
		max			: 총 자리 개수
		ota_count	: 오타 개수
*/
void printNatmalResult(int right_count, int all_count, int max, int ota_count);

/*
	작성자		: 김지수
	함수명		: onShort
	용도			: 짧은글연습 페이지로 이동
*/
void onShort();
/*
	작성자		: 김지수
	함수명		: printShort
	용도			: 짧은글연습 화면 출력해줌
*/
void printShort();
/*
	작성자		: 김지수
	함수명		: onChangeShort
	용도			: 짧은글연습 화면 갱신해줌
	인자값
		right_typing	: 맞게 입력한 수
		typing_count	: 전체 입력한 수
		cursor			: 커서 위치
		max				: 총 자리 개수
		tnow			: 현재 타수
		thigh			: 최고 타수
*/
void onChangeShort(int right_typing, int typing_count, int cursor, int max, int tnow, int thigh);
/*
	작성자		: 김지수
	함수명		: printShortResult
	용도			: 짧은글연습 결과 출력해줌
	인자값
		thigh	: 현재 타수
*/
void printShortResult(int thigh);

/*
	작성자		: 김지수
	함수명		: onLong
	용도		: 긴글연습 페이지로 이동
*/
void onLong();
/*
	작성자		: 김지수
	함수명		: printLong
	용도		: 긴글연습 화면 출력해줌
*/
void printLong();
/*
	작성자		: 김지수
	함수명		: onChangeLong
	용도			: 긴글연습 화면 갱신해줌
	인자값
		right_typing	: 맞게 입력한 수
		cursor			: 커서 위치
		tnow			: 현재 타수
*/
void onChangeLong(int right_typing, int cursor, int tnow);
/*
	작성자		: 김지수
	함수명		: printShortResult
	용도			: 짧은글연습 결과 출력해줌
	인자값
		right_typing	: 맞게 입력한 수
		all_typing		: 전체 입력한 수
		tnow			: 현재 타수
*/
void printLongResult(int right_typing, int all_typing, int tnow);

int getch(); // getch 함수

/*
	ANSI_escape_code를 이용한 함수
	작성자 : 김지수
 */
inline void setForeColor(int colorCode); // 폰트색 바꾸는 함수
inline void setBackColor(int colorCode); // 배경색 바꾸는 함수
inline void setXY(int x,int y); // 커서 위치 바꾸는 함수

int main(void)
{
	onMenu();
	system("clear"); // 끝나기 전 화면 비워주는 센스!
	return 0;
}

void onMenu()
{
	int mnuID = 1, loop = 1;
	printMenu(mnuID);
	while(loop)
	{
		switch (getch())
		{
		case KEY_UP:
			if(mnuID <= 1)mnuID = MID_EXIT+1; // 맨 마지막 메뉴로
			onChangeMenu(--mnuID); // 선택 메뉴값을 위로
			break;
		case KEY_DOWN:
			if(mnuID>=MID_EXIT)mnuID = 0; // 맨 처음 메뉴로
			onChangeMenu(++mnuID); // 선택 메뉴값을 아래로
			break;
		case KEY_ENTER:
			if(setPage(mnuID) == -1)  // 페이지 이동 명령 수행
				loop = 0; // 종료명령시 루프 빠져나감
			else
				printMenu(mnuID);
			break;
		}
	}
}

void onChangeMenu(int mnuID)
{
	char cPoint, mnuList[][20] = {"자리 연습", "낱말 연습", "짧은 글 연습", "긴 글 연습", "프로그램 종료"};
	int i;
	
	for(i=0;i<sizeof(mnuList)/sizeof(mnuList[0]);++i) // 메뉴 개수만큼 반복
	{
		if((i+1)==mnuID) // 현재 메뉴이면 배경색 하얀색
		{
			cPoint = '>';
			setBackColor(COLOR_WHITE);
			setForeColor(COLOR_BLACK);
		}
		else // 현재 메뉴가 아니면 기본 색상
		{
			cPoint = ' ';
			setBackColor(COLOR_RESET);
			setForeColor(COLOR_RESET);
		}
		setXY(2, 4+i);
		printf("%c %s", cPoint, mnuList[i]);
	}
	setBackColor(COLOR_RESET);
	setForeColor(COLOR_RESET);
}

void printMenu(int mnuID)
{
	int i;
	printf("\n");
	system("clear");
	beginFrame();
	printf("│%-*s│\n", WIDTH-2, "                너구리 타자연습");
	printLine();
	for(i=0;i<MID_EXIT;++i) // 메뉴 개수만큼 여분공간 출력
		printf("│%*c│\n", WIDTH-2, ' ');
	endFrame();
	onChangeMenu(mnuID);
}

int setPage(int mnuID)
{
	switch (mnuID)
	{
	case MID_JARI: // 자리 연습
		onJari();
		break;
	case MID_NATMAL: // 낱말 연습
		onNatmal();
		break;
	case MID_SHORT: // 짧은 글 연습
		onShort();
		break;
	case MID_LONG: // 긴 글 연습
		onLong();
		break;
	case MID_EXIT: // 프로그램 종료
		return -1;
	 	break;
		
	}
	return 0;
}

void onJari()
{
	int right_count = 0, all_count = 0, ota_count = 0, jari_max = 20, jari_index, is_right = 1;
	char cJari_DB[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ", cInput;
	printJari();
	while(right_count < jari_max)
	{
		if(is_right) // 이전에 올바르게 입력했을 경우 다음 단어로
		{
			srand(time(NULL));
			jari_index = rand()%(sizeof(cJari_DB) - 1); // NULL문자 제외
		}
		onChangeJari(right_count, all_count, jari_max, ota_count);
		setXY(4, 6);
		putchar(cJari_DB[jari_index]);
		setXY(2, 7);
		printf("  _\b");
		if((cInput = getch()) == KEY_ESC) // ESC입력시 끝내기
			return;
		if(cInput == cJari_DB[jari_index]) // 올바르게 입력했는지
		{
			is_right = 1;
			right_count++;
		}
		else
		{
			is_right = 0;
			ota_count++;
		}
		all_count++;
	}
	printJariResult(right_count, all_count, jari_max, ota_count);
	while(getch() != KEY_ENTER); // 엔터 입력시에 끝 
}

void printJari()
{
	printf("\n");
	system("clear"); // 시작 전 화면 비워주는 센스!
	beginFrame();
	printf("│%-*s│\n", WIDTH - 2, "                  자리 연습");
	printLine();
	printf("│%-*c│\n", WIDTH - 2, ' ');
	printLine();
	printf("│%-*c│\n", WIDTH - 2, ' ');
	printf("│%-*c│\n", WIDTH - 2, ' ');
	printLine();
	printf("│%-*s│\n", WIDTH - 2, "               종료 : ESC");
	endFrame();
}

void onChangeJari(int right_count, int all_count, int max, int ota_count)
{
	setXY(2, 4);
	printf("진행도 : %-3d%%     오타수 : %-3d     정확도 : %-3d%%", 
					(int)(((double)right_count/max) * 100), // 진행도 계산
					ota_count,
					(int)(((double)right_count/(all_count?all_count:1)) * 100)); // 정확도 계산
}

void printJariResult(int right_count, int all_count, int max, int ota_count)
{
	printf("\n");
	system("clear"); // 시작 전 화면 비워주는 센스!
	beginFrame();
	printf("│%-*s│\n", WIDTH - 2, "                  자리 연습");
	printLine();
	printf("|진행도 : %-3d%%     오타수 : %-3d     정확도 : %-3d%%|\n", 
					(int)(((double)right_count/max) * 100), // 진행도 계산
					ota_count,
					(int)(((double)right_count/(all_count?all_count:1)) * 100)); // 정확도 계산
	printLine();
	printf("│%-*s│\n", WIDTH - 2, "               종료 : Enter");
	endFrame();
}

void onNatmal()
{
	const char *natmal_DB[] = {
		"approval", "approach", "access", "arrange", "agreement"
		, "barrier", "bless", "bare", "betray"
		, "challenge", "commitment", "coordinate", "contact", "conserve"
		, "denial", "destiny", "disclose", "descend"
		, "effort", "employees", "essay", "elegant", "echo"
		, "fare", "facility", "forbid", "fulfill", "fancy"
		, "genius", "golf", "grape", "gravity", "glide"
		, "halt", "hesitate", "humble", "hostage", "halo"
		, "introduction", "indication", "industry", "incidence"
		, "jag", "jar", "journey"
		, "knit", "kitchen", "kindness", "knowledge"
		, "literal", "lid", "lease", "logograph"
		, "military", "modest", "mutual", "mount", "moderate"
		, "naked", "notation"
		, "osteoporosis", "overwhelming"
		, "patriotism", "possess", "property", "potential", "passion"
		, "quite", "qualify", "quickly", "question"
		, "resemble", "regret", "request", "risk", "reward"
		, "substance", "symphony", "slave", "scale", "stimulate"
		, "thrive", "triumph", "thunder", "tender", "tournament"
		, "uncovered", "urgent"
		, "vital", "vote", "voyage", "veteran"
		, "weave", "wrench", "wring", "warrior"
		, "xenon", "xylophone", "yearn"
		, "zealous"
	};
	int all_count = 0, right_count = 0, ota_count = 0, natmal_max = 20, natmal_index = 0;
	printNatmal();
	while(all_count < natmal_max)
	{
		srand(time(NULL));
		natmal_index = rand()%(sizeof(natmal_DB)/sizeof(natmal_DB[0])); // 0~낱말개수 랜덤
		int cursor = 0, is_over = 0;
		char cInput;
		const int natmal_len = strlen(natmal_DB[natmal_index]);
		char buffer[(natmal_len<3?3:natmal_len)+1]; // ###(종료 명령)을 받기 위해 최소 버퍼길이를 4(널문자 포함)로..
		onChangeNatmal(right_count, all_count, natmal_max, ota_count);
		
		setXY(4, 6);
		printf(natmal_DB[natmal_index]);
		setXY(4+cursor, 7);
		printf("_\b"); // 커서 출력
		while((cInput = getch()) != KEY_ENTER) // 엔터 받을 때까지 키입력 받음
		{
			if(cInput != '\b' && cInput != 127 && ' ' <= cInput && '~' >= cInput) // 백스페이스 입력이 아니고 출력문자이면
			{
				setXY(4+cursor, 6);
				if(cursor >= natmal_len) // 커서가 글자수를 벗어나면
				{
					if(cursor < WIDTH-2-3) // 화면의 너비를 넘어가지 않도록...
					{
						is_over = 1; // 벗어났음
						setBackColor(COLOR_RED);
						printf(" ");
						setBackColor(COLOR_RESET);
					}
				}
				else 
				{
					int fore_color;
					if(natmal_DB[natmal_index][cursor] == cInput) // 맞게 입력 할 경우
						fore_color = COLOR_CYAN;
					else // 틀리게 입력 할 경우
						fore_color = COLOR_RED;
					buffer[cursor] = cInput;
					is_over = 0;
					setForeColor(fore_color); // 폰트색 설정
					putchar(natmal_DB[natmal_index][cursor]);
					setForeColor(COLOR_RESET);
				}
				setXY(4+cursor, 7);
				if(cursor < WIDTH-2-3) // 화면의 너비를 넘어가지 않도록...
				{
					printf("%c_\b", cInput);
					++cursor;
				}
			}
			else if(cInput == '\b' || cInput == 127) // 백스페이스
			{
				if(cursor > 0)
				{
					setXY(4+cursor, 7);
					printf("\b_ \b\b", cInput);
					--cursor;
					setXY(4+cursor, 6);
					if(cursor <= natmal_len) // 커서가 범위 이내 이면 다시 출력하여 입력할 글자색 원상태로
					{
						is_over = 0;
						putchar(natmal_DB[natmal_index][cursor]);
						if(cursor == natmal_len)printf(" ");
					}
					else
						printf(" ");
					setXY(4+cursor, 7);
				}
			}
		}
		buffer[cursor<natmal_len?cursor:natmal_len] = '\0'; // 맨 끝 문자는 null로 만듦
		if(strcmp("###", buffer) == 0) // ###입력 시 종료
			return;
		if(is_over || strcmp(natmal_DB[natmal_index], buffer) != 0) // 틀렸을 경우
			++ota_count;
		else // 맞을 경우
			++right_count;
		++all_count;
	}
	printNatmalResult(right_count, all_count, natmal_max, ota_count);
	while(getch() != KEY_ENTER); // 엔터 입력시에 끝 
}

void printNatmal()
{
	printf("\n");
	system("clear"); // 시작 전 화면 비워주는 센스!
	beginFrame();
	printf("│%-*s│\n", WIDTH - 2, "                  낱말 연습");
	printLine();
	printf("│%-*c│\n", WIDTH - 2, ' ');
	printLine();
	printf("│%-*c│\n", WIDTH - 2, ' ');
	printf("│%-*c│\n", WIDTH - 2, ' ');
	printLine();
	printf("│%-*s│\n", WIDTH - 2, "        종료 : '###'입력 후 Enter");
	endFrame();
}

void onChangeNatmal(int right_count, int all_count, int max, int ota_count)
{
	setXY(2, 4);
	printf("진행도 : %-3d%%     오타수 : %-3d     정확도 : %-3d%%", 
					(int)(((double)all_count/max) * 100), // 진행도 계산
					ota_count,
					(int)(((double)right_count/(all_count?all_count:1)) * 100)); // 정확도 계산
	setXY(0, 6);
	printf("│%-*c│\n", WIDTH - 2, ' ');
	setXY(0, 7);
	printf("│%-*c│\n", WIDTH - 2, ' ');
}

void printNatmalResult(int right_count, int all_count, int max, int ota_count)
{
	printf("\n");
	system("clear"); // 시작 전 화면 비워주는 센스!
	beginFrame();
	printf("│%-*s│\n", WIDTH - 2, "                  자리 연습");
	printLine();
	printf("|진행도 : %-3d%%     오타수 : %-3d     정확도 : %-3d%%|\n", 
					(int)(((double)all_count/max) * 100), // 진행도 계산
					ota_count,
					(int)(((double)right_count/(all_count?all_count:1)) * 100)); // 정확도 계산
	printLine();
	printf("│%-*s│\n", WIDTH - 2, "               종료 : Enter");
	endFrame();
}

void onShort()
{
	const char *short_DB[] = {
		"Love is merely madness",
		"Hate the sin, love the sinner",
		"We can only learn to love by loving",
		"To love is to receive a glimpse of heaven",
		"Only I can change my life",
		"Life is a zoo in a jungle",
		"Life's a voyage that's homeward bound",
		"Be gentle with the young",
		"Life is a long lesson in humility",
		"Well done is better than well said",
		"All Bibles are man made",
		"Much learning does not teach understanding",
		"Children are all foreigners",
		"Seek not every quality in one individual",
		"Success is never final",
		"Nothing fails like success",
		"Eighty percent of success is showing up",
		"Nothing succeeds like the appearance of success",
		"Friends have all things in common",
		"A friend is a second self",
		"My friends, there are no friends",
		"A friend to all is a friend to none",
		"United we stand, divided we fall",
		"Oh for a book and a shady nook",
		"Live always in the best company when you read",
		"A book that is shut is but a block",
		"This book fills a much needed gap",
		"Nothing is as far away as one minute ago",
		"Regret for wasted time is more wasted time",
		"Time is an illusion. Lunchtime doubly so"
	};
	int short_count = 0, right_typing = 0, short_max = 5, short_index = 0;
	struct timeb tstart = {0};
	int tnow = 0, thigh = 0;
	double difftime = 0;
	printShort();
	while(short_count < short_max)
	{
		srand(time(NULL));
		short_index = rand()%(sizeof(short_DB)/sizeof(short_DB[0])); // 0~짧은글 개수 랜덤
		char cInput;
		int cursor = 0;
		const int short_len = strlen(short_DB[short_index]); // 글자수 구함
		char buffer[short_len]; // 글자수 만큼 버퍼 생성
		onChangeShort(right_typing, cursor, short_count, short_max, tnow, thigh);
		setXY(0, 6);
		printf("│%-*c│\n", WIDTH - 2, ' ');
		setXY(0, 7);
		printf("│%-*c│\n", WIDTH - 2, ' ');
		setXY(4, 6);
		printf(short_DB[short_index]);
		setXY(4, 7);
		printf("_\b");
		ftime(&tstart); // 시작시각
		while((cInput = getch()) != KEY_ENTER)
		{
			if(cInput == KEY_ESC)return; // ESC누르면 종료
			if(cInput != '\b' && cInput != 127 && ' ' <= cInput && '~' >= cInput) // 백스페이스 입력이 아니고 출력문자이면
			{
				if(cursor < short_len) // 커서가 입력할 글자수보다 적을때만 출력
				{
					int fore_color;
					if(cInput == short_DB[short_index][cursor]) // 맞게 입력 할 경우
					{
						// 타수 = 작성글자수/경과시간(분)
						++right_typing;
							struct timeb tnowtime;
							ftime(&tnowtime);
							// 경과 시간 구하기
							difftime = (double)(tnowtime.time-tstart.time) + (double)(tnowtime.millitm-tstart.millitm)/1000.0;
							tnow = (int)(right_typing / (difftime/60)); // 타수 계산
						if(tnow > thigh) // 최고 타수 구함
							thigh = tnow;
						fore_color = COLOR_CYAN;
					}
					else // 틀리게 입력 할 경우
						fore_color = COLOR_RED;
					setXY(4+cursor, 6);
					setForeColor(fore_color);
					putchar(short_DB[short_index][cursor]);
					setForeColor(COLOR_RESET);
					setXY(4+cursor, 7);
					printf("%c_\b", cInput);
					buffer[cursor] = cInput; // 버퍼에 담음
					++cursor;
				}
			}
			else if(cInput == '\b' || cInput == 127)
			{
				if(cursor > 0)
				{
					--cursor;
					if(short_DB[short_index][cursor] == buffer[cursor]) // 이전에 입력했던 값이 맞는 값이였으면 타수에 반영하기 위해 맞은 개수를 줄여!
						--right_typing;
						
					struct timeb tnowtime;
					ftime(&tnowtime);
					// 경과 시간 구하기
					difftime = (double)(tnowtime.time-tstart.time) + (double)(tnowtime.millitm-tstart.millitm)/1000.0;
					tnow = (int)(right_typing / (difftime/60)); // 타수 계산
					
					setXY(4+cursor, 6);
					if(cursor <= short_len) // 커서가 범위 이내 이면 다시 출력하여 입력할 글자색 원상태로
					{
						putchar(short_DB[short_index][cursor]);
						if(cursor == short_len)printf(" ");
					} else printf(" ");
					setXY(4+cursor+1, 7);
					printf("\b_ \b\b");
				}
			}
			onChangeShort(right_typing, cursor, short_count, short_max, tnow, thigh);
			setXY(4+cursor, 7);
		}
		// 변수 초기화
		right_typing = 0;
		tnow = 0;
		onChangeShort(right_typing, cursor, short_count, short_max, tnow, thigh);
		++short_count;
	}
	printShortResult(thigh);
	while(getch() != KEY_ENTER); // 엔터 입력시에 끝 
}

void printShort()
{
	printf("\n");
	system("clear"); // 시작 전 화면 비워주는 센스!
	beginFrame();
	printf("│%-*s│\n", WIDTH - 2, "                짧은 글 연습");
	printLine();
	printf("│%-*c│\n", WIDTH - 2, ' ');
	printLine();
	printf("│%-*c│\n", WIDTH - 2, ' ');
	printf("│%-*c│\n", WIDTH - 2, ' ');
	printLine();
	printf("│%-*s│\n", WIDTH - 2, "        종료 : ESC");
	endFrame();
}

void onChangeShort(int right_typing, int cursor, int count, int max, int tnow, int thigh)
{
	setXY(2, 4);
	printf("진행도 : %3d%% 현재타수 : %-4d 최고타수 : %-4d 정확도 : %3d%%", 
				(int)(((double)count/max) * 100), // 진행도 계산
				tnow,
				thigh,
				cursor==0?0:(int)(((double)right_typing/cursor)*100)); // 정확도 계산
}

void printShortResult(int thigh)
{
	printf("\n");
	system("clear"); 
	beginFrame();
	printf("│%-*s│\n", WIDTH - 2, "                짧은 글 연습");
	printLine();
	printf("│%-*c│\n", WIDTH - 2, ' ');
	printLine();
	printf("│%-*s│\n", WIDTH - 2, "        종료 : Enter");
	endFrame();
	setXY(2, 4);
	printf("            최고타수 : %-4d", thigh);
}

void onLong()
{
	const char *long_DB[4][11] = 
	{
		{
			"The elves and the shoemaker",
			"Once upon a time, there was a poor shoemaker and his wife.",
			"\"This is all the leather I have left,\" said the poor shoemaker.",
			"\"I can make just one pair of shoes.\"",
			"That night, the shoemaker cut the leather.",
			"\"I'll make these shoes in the morning,\" he said. ",
			"He left the leather in the shop and went to bed.",
			"The next morning, the shoemaker came downstairs.",
			"To his surprise, the leather had been made into a pair of beautiful shoes.",
			"The shoemaker called his wife.",
			"\"Did you make these shoes?\""
		},
		{
			"the selfish giant",
			"One day the Giant came back. He had been to visit his friend the",
			"Cornish ogre, and had stayed with him for seven years. After the seven",
			"years were over he had said all that he had to say, for his conversa-",
			"tion was limited, and he determined to return to his own castle. When",
			"he arrived he saw the children playing in the garden.",
			"\"What are you doing here?\" he cried in a very gruff voice, and the",
			"children ran away.",
			"\"My own garden is my own garden,\" said the Giant; \"anyone can under-",
			"stand that, and I will allow nobody to play in it but myself.\" So he",
			"built a high wall all round it, and put up a notice-board."
		},
		{
			"The Wind and the Sun",
			"The North Wind was rushing along blowing the clouds as he passed.",
			"\"Who is so strong as I ?\" he cried. \"I am even stronger than the sun.\"",
			"\"Can you show that you are stronger ?\" asked the Sun.",
			"\"A traveler is coming over the hill,\" said the Wind. \"Let us see which of ",
			"us can first make him take off his long cloak. The one who succeeds will",
			"prove himself the stronger.\"",
			"The North Wind began first. He blew a gale, tore up trees, and raised",
			"clouds of dust. But the traveler only wrapped his cloak more closely",
			"about him, and kept on his way.",
			"Then the Sun began to shine. He drover away the clouds and warmed air."
		},
		{
			"Gulliver's travels",
			"After I had been free for two weeks an important man came to talk to me.",
			"He told me that though Lilliput seemed at peace, it was not.",
			"Within the court there were two groups of men.",
			"One group wore high-heeled shoes and the other wore low-heeled shoes.",
			"These two groups always disagreed with each other and bec-",
			"ause of their disagreeing, very little got done.",
			"The man told me that because  of this, Lilliput's enemy,",
			"Blefuscu, was planning to attack.",
			"Blefuscu, was Lilliput's enemy because Blefuscu's people fried their eggs.",
			"Lilliputians scrambled their eggs."
		}
	};
	int long_count = 0, right_typing = 0, all_typing = 0, long_index = 0, i;
	struct timeb tstart = {0}; // 시작 시간 변수
	int tnow = 0; // 현재 타수 변수
	double difftime = 0; // 시간간격 담을 변수
	printLong(); // UI출력
	srand(time(NULL));
	long_index = rand()%(sizeof(long_DB)/sizeof(long_DB[0])); // 0~긴글 개수 랜덤
	ftime(&tstart); // 시작시각
	while(long_count < sizeof(long_DB[0])/sizeof(long_DB[0][0])-1) // 긴글 줄 수 만큼 반복
	{
		char cInput;
		int cursor = 0, is_complete = 0;
		if(long_count%5 == 0) // 새 페이지 시작
		{
			setXY(4, 4);
			printf("제목 : %s [%d/%d]", 
						long_DB[long_index][0], // 제목 출력
						long_count/5+1, // 현재 페이지 수 계산
						(sizeof(long_DB[0])/sizeof(long_DB[0][0])-1)/5); // 전체 페이지수 계산
			for(i=1;i<=5;++i)
			{
				// 긴글 표시
				setXY(4, 8+(i-1)*2);
				printf("%-*s", WIDTH-2-2, long_DB[long_index][long_count + i]);
				setXY(4, 9+(i-1)*2);
				printf("%-*c", WIDTH-2-2, ' ');
			}
		}
		onChangeLong(right_typing, all_typing, tnow);
		setXY(4, 9+(long_count%5)*2); // 커서 변경
		printf("_\b");
		while(!is_complete)
		{
			const int long_len = strlen(long_DB[long_index][long_count + 1]); // 글자수 담음
			char buffer[WIDTH]; // 너비만큼 버퍼 잡음
			if(long_len <= cursor) // 현재 커서가 글자수 만큼이면 루프 빠져나가 다음 문장으로 이동
				is_complete = 1;
			cInput = getch();
			if(cInput == KEY_ESC)return; // ESC누르면 종료
			if(cInput != '\b' && cInput != 127 && ' ' <= cInput && '~' >= cInput) // 백스페이스 입력이 아니고 출력문자이면
			{
				if(cursor < long_len) // 커서가 입력할 글자수보다 적을때만 출력
				{
					int fore_color;
					if(cInput == long_DB[long_index][long_count + 1][cursor]) // 맞게 입력 할 경우
					{
						// 타수 = 작성글자수/경과시간(분)
						++right_typing;
							struct timeb tnowtime;
							ftime(&tnowtime);
							// 경과 시간 구하기
							difftime = (double)(tnowtime.time-tstart.time) + (double)(tnowtime.millitm-tstart.millitm)/1000.0;
							tnow = (int)(right_typing / (difftime/60)); // 타수 계산
						fore_color = COLOR_CYAN;
					}
					else // 틀리게 입력 할 경우
						fore_color = COLOR_RED;
					setXY(4+cursor, 8+(long_count%5)*2);
					setForeColor(fore_color);
					putchar(long_DB[long_index][long_count + 1][cursor]);
					setForeColor(COLOR_RESET);
					setXY(4+cursor, 9+(long_count%5)*2);
					printf("%c_\b", cInput);
					buffer[cursor] = cInput;
					++cursor;
					++all_typing;
				}
			}
			else if(cInput == '\b' || cInput == 127)
			{
				if(cursor > 0)
				{
					--cursor;
					--all_typing;
					if(long_DB[long_index][long_count + 1][cursor] == buffer[cursor]) // 이전에 입력했던 값이 맞는 값이였으면 타수에 반영하기 위해 맞은 개수를 줄여!
						--right_typing;
					struct timeb tnowtime;
					ftime(&tnowtime);
					// 경과 시간 구하기
					difftime = (double)(tnowtime.time-tstart.time) + (double)(tnowtime.millitm-tstart.millitm)/1000.0;
					tnow = (int)(right_typing / (difftime/60)); // 타수 계산
					
					setXY(4+cursor, 8+(long_count%5)*2);
					if(cursor <= long_len) // 커서가 범위 이내 이면 다시 출력하여 입력할 글자색 원상태로
					{
						putchar(long_DB[long_index][long_count + 1][cursor]);
						if(cursor == long_len)printf(" ");
					} else printf(" ");
					setXY(4+cursor+1, 9+(long_count%5)*2);
					printf("\b_ \b\b");
				}
			}
			onChangeLong(right_typing, all_typing, tnow);
			setXY(4+cursor, 9+(long_count%5)*2);
		}
		printf(" \b"); // 커서표시 지움
		++long_count;
	}
	printLongResult(right_typing, all_typing, tnow);
	while(getch() != KEY_ENTER); // 엔터 입력시에 끝 
}

void printLong()
{
	printf("\n");
	system("clear"); // 시작 전 화면 비워주는 센스!
	beginFrame();
	printf("│%-*s│\n", WIDTH - 2, "                긴 글 연습");
	printLine();
	printf("│%-*c│\n", WIDTH - 2, ' '); // 제목 표시 공간
	printLine();
	printf("│%-*c│\n", WIDTH - 2, ' '); // 상태 표시 공간
	printLine();
	printf("│%-*c│\n", WIDTH - 2, ' '); // 연습 공간 1
	printf("│>>%-*c│\n", WIDTH - 4, ' '); // 연습 공간
	
	printf("│%-*c│\n", WIDTH - 2, ' '); // 연습 공간 2
	printf("│>>%-*c│\n", WIDTH - 4, ' '); // 연습 공간
	
	printf("│%-*c│\n", WIDTH - 2, ' '); // 연습 공간 3
	printf("│>>%-*c│\n", WIDTH - 4, ' '); // 연습 공간
	
	printf("│%-*c│\n", WIDTH - 2, ' '); // 연습 공간 4
	printf("│>>%-*c│\n", WIDTH - 4, ' '); // 연습 공간
	
	printf("│%-*c│\n", WIDTH - 2, ' '); // 연습 공간 5
	printf("│>>%-*c│\n", WIDTH - 4, ' '); // 연습 공간
	printLine();
	printf("│%-*s│\n", WIDTH - 2, "        종료 : ESC");
	endFrame();
}

void onChangeLong(int right_typing, int all_typing, int tnow)
{
	setXY(2, 6);
	printf("정확도 : %3d%%     현재타수 : %-4d", 
				all_typing==0?0:(int)(((double)right_typing/all_typing)*100), // 정확도 계산
				tnow);
}

void printLongResult(int right_typing, int all_typing, int tnow)
{
	printf("\n");
	system("clear"); 
	beginFrame();
	printf("│%-*s│\n", WIDTH - 2, "                긴 글 연습");
	printLine();
	printf("│%-*c│\n", WIDTH - 2, ' ');
	printLine();
	printf("│%-*s│\n", WIDTH - 2, "        종료 : Enter");
	endFrame();
	setXY(2, 4);
	printf("정확도 : %3d%%     현재타수 : %-4d", 
				all_typing==0?0:(int)(((double)right_typing/all_typing)*100), // 정확도 계산
				tnow);
}

void beginFrame()
{
	int i;
	printf("┌");
	for(i=0;i<WIDTH-2;++i)
		printf("─");
	printf("┐\n");
}

void endFrame()
{
	int i;
	printf("└");
	for(i=0;i<WIDTH-2;++i)
		printf("─");
	printf("┘\n");
}

void printLine()
{
	int i;
	printf("├");
	for(i=0;i<WIDTH-2;++i)
		printf("─");
	printf("┤\n");
}

int getch()
{
	struct termios oldt, newt; // 터미널 Input Output Stream 구조체 선언
	int ch; // 받을 캐릭터
	tcgetattr(STDIN_FILENO, &oldt); // oldt에 터미널 IOS정보 받아옴
	newt = oldt; // newt에 oldt복사
	newt.c_lflag &= ~(ICANON | ECHO); // ICANON와 ECHO설정 뺌
	tcsetattr(STDIN_FILENO, TCSANOW, &newt); // 수정한 세팅 적용
	ch = getchar(); // 캐릭터 받아옴
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // 원상태로 세팅 복구
	return ch; // 받은 캐릭터 리턴
}

/*
	ANSI escape code 설명
	http://en.wikipedia.org/wiki/ANSI_escape_code#CSI_codes
*/
inline void setForeColor(int colorCode)
{
	// ANSI escape code m명령 30번대 : 글자색 변경
	printf("\e[3%dm", colorCode);
}

inline void setBackColor(int colorCode)
{
	// ANSI escape code m명령 40번대 : 배경색 변경
	printf("\e[4%dm", colorCode);
}

inline void setXY(int x, int y)
{
	// ANSI escape code f명령 : 커서 이동
	printf("\e[%d;%df", y, x);
}


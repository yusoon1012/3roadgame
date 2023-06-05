#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>

int roadClear = 0;
int damage = 0;
int playerHP = 45;

const int MAX_HP = 50;
const int MAX_STATPOINT = 20;


int roadSelector = 0;
int battleIncounter = 0;
int monsterHp = 0;
int monsterDamage = 0;
int randomMonster = 0;
int randomMHP = 0;
int randomMdamage = 0;

int healup = 0;
int healPer = 0;
char keyInput = '0';

void slime();
void goblin();
void golem();

int healSet();
int damageSet();
void statSet();
void healing();
void statusDP()
{ 
	printf("==================================================================\n\n");

	printf("        [현재 체력  %d / %d]  [공격력  %d]  [회복력 %d]\n", playerHP, MAX_HP, damage, healup);
	printf("\n\n==================================================================\n\n");

}

void slimebattle();
void goblinbattle();
void golembattle();


void drawLobby();
void drawMountine();
void drawRoad();
void drawHeal();
void drawRiver();
void drawSlime();
void drawGoblin();
void drawGolem();

void drawTitle();
void drawEnd();
void drawGameOver();
bool gameOver = false;

int main()//메인
{        
	srand(time(NULL));
	drawTitle();  //타이틀화면표시
	_getch();
	system("cls");
	statSet();   //스탯설정
	printf("==================================================================\n\n");
	printf("\n         최종 스탯 : [공격력] [%d] [회복력] [%d]\n", damage, healup);
	printf("\n\n==================================================================\n\n");

	Sleep(5000);
	system("cls");  //스탯설정완료
	

	while (roadClear < 6&&gameOver==false)
	{
		statusDP(); //스탯 표시해주는 함수
		drawLobby(); // 진행하는 길 그려주는함수
		printf("==================================================================\n\n");
		printf("\n       [세갈래 길이 나타났습니다. 진행하려면 [ENTER] 입력]\n");
		printf("\n\n==================================================================\n\n");
		_getch();

		roadSelector = rand() % 100; 
		battleIncounter = rand() % 100;


		if (roadSelector >= 0 && roadSelector < 30)
		{
			system("cls");
			drawRoad();
			printf("==================================================================\n\n");
			printf("\n            [도시로가는 표지판을 찾았다! 앞으로전진]\n");
			printf("\n\n==================================================================\n\n");

			roadClear += 1;
			Sleep(3000);
			system("cls");
		}
		else if (roadSelector > 30 && roadSelector <= 50)
		{
			system("cls");
			drawRiver();
			printf("==================================================================\n\n\n");
			printf("\n        강에 도착했지만 길이 끊겨있다. 다시 돌아가자.\n");
			printf("\n\n==================================================================\n\n");

			Sleep(3000);
			system("cls");
		}
		else
		{
			randomMonster = rand() % 100;
			randomMdamage = rand() % 5+1;//몬스터의 데미지를 랜덤으로 설정(1~5)
			
			system("cls");
			drawMountine();
			printf("==================================================================\n\n\n");
			printf("\n                    [  산에 도착했다. ]\n");
			printf("\n\n==================================================================\n\n");

			Sleep(2000);
			system("cls");
			if (battleIncounter >= 0 && battleIncounter < 40)   //산에 도착하면 40%확률로 전투발생
			{

				if (randomMonster >= 0 && randomMonster < 50)   //50%확률로 슬라임등장
				{
					slime();                                    //슬라임의 정보를 불러오는 함수
					monsterDamage = randomMdamage ;				//슬라임의 공격력을 지정
					slimebattle();                              //슬라임과 전투하는함수

				}
				else if (randomMonster >= 50 && randomMonster < 80)//30%확률로 고블린 등장
				{
					goblin();									//고블린의 정보를 불러오는 함수
					monsterDamage = randomMdamage+3 ;			//고블린의 공격력을 지정 랜덤값+3
					goblinbattle();								//고블린과 전투하는함수
				}
				else if (randomMonster >= 80 && randomMonster < 99)//20%확률로 골렘 등장
				{
					golem();										//골렘의 정보를 불러오는 함수
					monsterDamage = randomMdamage + 5;				//골렘의 공격력을 지정 랜덤값+5
					golembattle();									//골렘과 전투하는함수		
				}			
			}
			else  //전투발생 안될시 회복
			{
				drawHeal();
				healing();
			}

		}
		printf("도시로 가는길에 도착한 횟수 : %d \n", roadClear);
	    printf("------------------------------------------------------------------\n\n");

		if (gameOver == true)
		{
			drawGameOver();
		}
	}
	if (gameOver != true)
	{
		drawEnd();
	}
	//메인종료
}

void statSet()
{
	while (damage + healup != 20)
	{
		printf("[공격력과 회복력 스탯을 배분해주세요 스탯포인트 : 20)]\n");
		printf("\n[공격력] : ");
		damage = damageSet();
		if (damage > MAX_STATPOINT||damage<1)
		{
			printf("값이 잘못되었습니다. 다시입력해주세요.\n");
			damage = 0;
			Sleep(2000);
			system("cls");
			continue;
		}
		printf("\n[남은 스탯포인트 : %d]\n", MAX_STATPOINT - damage);
		printf("\n[회복력] : ");
		healup = healSet();
		if (healup + damage > MAX_STATPOINT||healup==0)
		{
			printf("값이 잘못되었습니다. 다시입력해주세요.\n");
			damage = 0;
			healup = 0;
			Sleep(2000);
			system("cls");
			continue;
		}
		else if (healup + damage < MAX_STATPOINT)
		{
			printf("\n[남은 스탯포인트 : %d]\n", MAX_STATPOINT - (damage + healup));
			printf("[스탯 포인트가 [%d]남았습니다. 계속하시겠습니까?\n[ Y / N ]\n",MAX_STATPOINT-(damage+healup));
			keyInput = _getch();
			if (keyInput == 'Y' || keyInput == 'y')
			{
				printf("[ Y ]\n");
				Sleep(1000);
				break;
			}
			if (keyInput == 'N' || keyInput == 'n')
			{
				printf("[ N ]\n");
				Sleep(1000);
				printf("[다시 스탯을 설정해주세요]\n");
				damage = 0;
				healup = 0;
				Sleep(2000);
				system("cls");

			}

		}


		printf("\n[남은 스탯포인트 : %d]\n", MAX_STATPOINT - (damage + healup));

	}

}
int damageSet()
{
	int dmg=0;
	scanf_s("%d", &dmg);
	return dmg;

}
int healSet()
{
	int heal = 0;
	scanf_s("%d", &heal);
	return heal;
}
void healing()
{
	printf("==================================================================\n\n");
	printf("\n  [산속에서 치유의 샘을 발견하였습니다. 회복력만큼 회복됩니다.]\n");
	if (playerHP + healup >= MAX_HP)
	{
		playerHP = MAX_HP;
		printf("\n            [회복되었습니다. 현재체력 [ %d ] ]\n", playerHP);
	}
	else
	{
		playerHP += healup;
		printf("\n   [회복력 [ %d ]만큼 회복되었습니다. 현재체력 [ %d ] ]\n",healup, playerHP);
	}
	printf("\n\n==================================================================\n\n");

	Sleep(3000);
	system("cls");
}
void slimebattle()
{
	Sleep(2000);
	int avoidPer = 0;
	int playerAvoid = 0;
	printf("\n                       [슬라임과 전투 시작]\n");
	drawSlime();
	Sleep(2000);
	system("cls");
	while (monsterHp >= 0)
	{
		statusDP();
		printf("\n               [[ 슬라임의 체력 [ %d ] 공격력 [ %d ] ]]\n", monsterHp,monsterDamage);
		drawSlime();
		Sleep(2000);
		avoidPer = rand() % 100;
		playerAvoid = rand() % 100;
		if (avoidPer >= 0 && avoidPer < 90)
		{
			playerHP -= monsterDamage;
			printf("==================================================================\n\n");
			printf("\n                      [ 슬라임의 공격 ]\n");
			printf("\n             [ 플레이어는 [ %d ] 데미지를 입었다.]\n",monsterDamage);
			if (playerHP  <= 0)
			{
				printf("\n                    [ 현재 체력 [ 0 ] ]\n");
				
				gameOver = true;
				break;
			}
			printf("==================================================================\n\n\n");

			printf("\n                     [현재 체력 %d / %d]\n", playerHP, MAX_HP);
		}
		else
		{
			printf("\n                 [ 슬라임의 공격을 회피했다.]\n");
		}
		
		Sleep(2000);
		printf("==================================================================\n\n");
		printf("                      [ 플레이어의 공격 ]\n");

		if (playerAvoid >= 0 && playerAvoid < 85)
		{
			monsterHp -= damage;
			printf("\n                [ 슬라임에게 %d 데미지를 입혔다.]\n", damage);
		}
		else
		{
			printf("\n                      [ 공격이 빗나갔다. ]\n");
		}
		if (monsterHp <= 0)
		{
			Sleep(2000);
			system("cls");
			statusDP();
			printf("\n               [[ 슬라임의 체력 [ %d ] 공격력 [ %d ] ]]\n", monsterHp, monsterDamage);
			drawSlime();

			printf("==================================================================\n\n");
			printf("\n                [전투승리] 슬라임을 토벌하였습니다 \n");
			printf("\n\n\n==================================================================\n\n");

			break;
		}
		Sleep(2000); 
		system("cls");
		
	}
	Sleep(5000);
	system("cls");
}
void goblinbattle()
{

	int avoidPer = 0;
	int playerAvoid = 0;

	Sleep(2000);
	printf("\n                      [ 고블린과 전투 시작 ]\n");
	drawGoblin();
	Sleep(2000);
	system("cls");
	while (monsterHp >= 0)
	{
		statusDP();
		printf("\n               [[ 고블린의 체력 [%d] 공격력[%d] ]]\n", monsterHp, monsterDamage);
		drawGoblin();
		Sleep(2000);
		avoidPer = rand() % 100;
		playerAvoid = rand() % 100;
		if (avoidPer >= 0 && avoidPer < 90)
		{
			playerHP -= monsterDamage;
			printf("==================================================================\n\n");
			printf("\n                    [ 고블린의 공격 ]\n");
			printf("\n          [ 플레이어는 [ %d ] 데미지를 입었다. ]\n", monsterDamage);
			if (playerHP  <= 0)
			{
				printf("\n                    [ 현재 체력 [ 0 ] ]\n");
				gameOver = true;
				break;
			}
			printf("==================================================================\n\n");

			printf("\n                 [ 현재 체력 %d / %d ]\n", playerHP, MAX_HP);

		}
		else
		{
			printf("\n                 [ 고블린의 공격을 회피했다. ]\n");
		}
		
		Sleep(2000);
		printf("==================================================================\n\n");

		printf("                      [ 플레이어의 공격]\n");
		if (playerAvoid >= 0 && playerAvoid < 85)
		{
			monsterHp -= damage;
			printf("\n              [ 고블린에게 %d 데미지를 입혔다. ]\n", damage);

		}
		else
		{
			printf("\n                   [ 공격이 빗나갔다. ]\n");
		}
		if (monsterHp <= 0)
		{
			Sleep(2000);
			system("cls");
			statusDP();

			printf("\n               [[ 고블린의 체력 [%d] 공격력[%d] ]]\n", monsterHp, monsterDamage);
			drawGoblin();

			printf("==================================================================\n\n");

			printf("\n              [전투승리] 고블린을 토벌하였습니다 \n");
			printf("\n\n\n==================================================================\n\n");
			break;
		}
		Sleep(2000);
		system("cls");
	}
	Sleep(5000);
	system("cls");
}
void golembattle()
{
	int avoidPer = 0;
	int playerAvoid = 0;
	Sleep(2000);
	printf("\n                      [ 골렘과 전투 시작]\n");
	drawGolem();
	Sleep(2000);
	system("cls");
	while (monsterHp >= 0)
	{
		
		statusDP();
		printf("\n	             [[ 골렘의 체력 [%d] 공격력[%d] ]]\n", monsterHp, monsterDamage);
		drawGolem();
		Sleep(2000);
		avoidPer = rand() % 100;
		playerAvoid = rand() % 100;
		if (avoidPer >= 0 && avoidPer < 90)
		{
			playerHP -= monsterDamage;
			Sleep(2000);
			printf("==================================================================\n\n");

			printf("\n	                     [ 골렘의 공격 ]\n");
			printf("\n	           [ 플레이어는 [ %d ] 데미지를 입었다. ]\n", monsterDamage);
			if (playerHP <= 0)
			{
				printf("\n                    [현재 체력 [ 0 ]]\n");
				gameOver = true;
				break;
			}
			printf("==================================================================\n\n");

			printf("\n                    [현재 체력 %d / %d]\n", playerHP, MAX_HP);
		}

		
		else
		{
			Sleep(2000);
			printf("\n                 [ 골렘의 공격을 회피했다. ]\n");
		}
		
		Sleep(2000);
		printf("==================================================================\n\n");

		printf("                       [ 플레이어의 공격 ]\n");
		if (playerAvoid >= 0 && playerAvoid < 85)
		{
			monsterHp -= damage;
			
			printf("\n                   [ 골렘에게 %d 데미지를 입혔다.]\n", damage);

		}
		else
		{
			printf("\n                      [ 공격이 빗나갔다. ]\n");
		}
		
		if (monsterHp <= 0)
		{
			Sleep(2000);
			system("cls");
			statusDP();

			printf("\n	             [[ 골렘의 체력 [%d] 공격력[%d] ]]\n", monsterHp, monsterDamage);
			drawGolem();
			printf("==================================================================\n\n");

			printf("\n                    [전투승리] 골렘을 토벌하였습니다 \n");
			printf("\n\n\n==================================================================\n\n");

			break;
		}
		Sleep(2000);
		system("cls");

	}
	Sleep(5000);
	system("cls");
}
void slime()
{
	printf("\n                      [ 슬라임이 나타났다 ] \n");
	monsterHp = 20;
}
void goblin()
{
	printf("\n                      [ 고블린이 나타났다 ]\n");
	monsterHp = 30;
	
}
void golem()
{
	printf("\n                      [ 골렘이 나타났다 ]\n");
	monsterHp = 60;

}
void drawLobby()
{ 
	//↑↗↖□
	printf("\n\n");
	printf("□           □        □              □        □             □\n");
	printf(" □           □       □              □       □             □\n");
	printf("  □    [?]    □      □     [?]      □      □     [?]     □\n");
	printf("   □           □     □              □     □             □\n");
	printf("    □           □    □              □    □             □\n");
	printf("     □           □   □              □   □             □\n");
	printf("\n\n");
}
void drawRoad()
{
	printf("\n\n");
	printf("                      =======================\n");
	printf("                      =                     =\n");
	printf("                      =                     =\n");
	printf("                      =        도시로       =\n");
	printf("                      =        가는길       =\n");
	printf("                      =                     =\n");
	printf("                      =                     =\n");
	printf("                      =======================\n");
	printf("                                ===\n");
	printf("                                ===\n");
	printf("                                ===\n");
	printf("                                ===\n");
	printf("                                ===\n");
	printf("\n\n");

}
void drawRiver()
{
	printf("\n\n");
	printf("                      §             §\n");
	printf("                     §             §\n");
	printf("                    §             §\n");
	printf("                    §             §\n");
	printf("                     §             §\n");
	printf("                      §             §\n");
	printf("                      §             §\n");
	printf("                     §             §\n");
	printf("                    §             §\n");
	printf("                    §             §\n");
	printf("                     §             §\n");
	printf("\n\n");
}
void drawMountine()
{
	//△▲
	printf("\n\n");
	printf("                        △   \n");
	printf("                       △△   \n");
	printf("                      △△△   \n");
	printf("                     △△△△   ▲\n");
	printf("                   △△△△△  ▲▲\n");
	printf("                  △△△△△△▲▲▲\n");
	printf("                 △△△△△△▲▲▲▲\n");
	printf("                △△△△△△▲▲▲▲▲\n");
	printf("\n\n");
}
void drawHeal()
{
	printf("\n\n");
	printf("                           ■    \n");
	printf("                         ■■■      \n");
	printf("                           ■        \n\n");
	printf("                    ▤▤▤▤▤▤▤▤ \n");
	printf("                  ▤                ▤  \n");
	printf("                 ▤                  ▤ \n");
	printf("                  ▤                ▤  \n");
	printf("                    ▤▤▤▤▤▤▤▤ \n");
	printf("\n\n");

}
void drawSlime()
{
	printf("\n\n");
	printf("                           ●●●●●●\n");
	printf("                        ●●          ●●\n");
	printf("                       ●     ◑   ◐    ●\n");
	printf("                       ●                ●\n");
	printf("                        ●●          ●●\n");
	printf("                           ●●●●●●\n");
	printf("\n\n");

}

void drawGoblin()
{
	printf("\n\n");
	printf("                        ◈          ◈\n");
	printf("                        ◈          ◈\n");
	printf("                        ◈◈◈◈◈◈◈\n");
	printf("                       ◈            ◈\n");
	printf("                      ◈   ※    ※   ◈\n");
	printf("                       ◈     WW     ◈\n");
	printf("                         ◈◈◈◈◈◈\n");
	printf("\n\n");

}
void drawGolem()
{
	printf("\n\n");
	printf("                           ▣▣▣▣▣▣\n");
	printf("                           ▣ ◈  ◈ ▣\n");
	printf("                           ▣        ▣\n");
	printf("                           ▣▣▣▣▣▣\n");
	printf("                   ▣▣▣▣▣▣▣▣▣▣▣▣▣▣\n");
	printf("                   ▣      ▣        ▣      ▣\n");
	printf("                   ▣      ▣        ▣      ▣\n");
	printf("                   ▣      ▣        ▣      ▣\n");
	printf("                   ▣      ▣▣▣▣▣▣      ▣\n");
	printf("                   ▣      ▣        ▣      ▣\n");
	printf("                   ▣      ▣        ▣      ▣\n");
	printf("                   ▣▣▣▣▣        ▣▣▣▣▣\n");
	printf("                           ▣        ▣\n");
	printf("                           ▣        ▣\n");
	printf("                         ▣▣        ▣▣\n");
	printf("                         ▣▣▣▣▣▣▣▣\n");
	printf("\n\n");



}
void drawTitle()
{
	printf("▣□▣□▣□▣□▣□▣□▣□▣□▣□▣□▣□▣□▣□▣□▣□▣□\n");
	printf("□                                                            ▣\n");
	printf("▣                                                            □\n");
	printf("□                                                            ▣\n");
	printf("▣                                                            □\n");
	printf("□                                                            ▣\n");
	printf("▣                                                            □\n");
	printf("□                       길 치 용 사                          ▣\n");
	printf("▣                                                            □\n");
	printf("□                                                            ▣\n");
	printf("▣                       press [ENTER]                        □\n");
	printf("□                                                            ▣\n");
	printf("▣                                                            □\n");
	printf("□                                                            ▣\n");
	printf("▣                                                            □\n");
	printf("□                                                            ▣\n");
	printf("▣□▣□▣□▣□▣□▣□▣□▣□▣□▣□▣□▣□▣□▣□▣□▣□\n");

}
void drawEnd()
{
	printf("▣□▣□▣□▣□▣□▣□▣□▣□▣□▣□▣□▣□▣□▣□▣□▣□\n");
	printf("□                                                            ▣\n");
	printf("▣                                                            □\n");
	printf("□                                                            ▣\n");
	printf("▣                                                            □\n");
	printf("□                                                            ▣\n");
	printf("▣                                                            □\n");
	printf("□                       길 치 용 사                          ▣\n");
	printf("▣                                                            □\n");
	printf("□                                                            ▣\n");
	printf("▣                       - THE END -                          □\n");
	printf("□                                                            ▣\n");
	printf("▣                                                            □\n");
	printf("□                                                            ▣\n");
	printf("▣                                                            □\n");
	printf("□                                                            ▣\n");
	printf("▣□▣□▣□▣□▣□▣□▣□▣□▣□▣□▣□▣□▣□▣□▣□▣□\n");
}
void drawGameOver()
{
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■                                                            ■\n");
	printf("■                                                            ■\n");
	printf("■                        GAME OVER                           ■\n");
	printf("■                                                            ■\n");
	printf("■                                                            ■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
}
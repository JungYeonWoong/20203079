#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define NAME 30
#define COLOR 20
#define LINE 100
#include "def.h"
//신발 정보 구조체 

//main함수 시작
int main(void)
{
	inform_shoes(); //txt 파일로부터 신발 정보를 가져와 연결리스트 생성
	int option;

	while(1)
	{
		//system("cls"); // 화면 정리 계속 해주기
		printf("<<  menu  >>\n");
		printf("1. 입고 \n");
		printf("2. 판매 \n");
		printf("3. 재고 검색 \n");
		printf("4. 할인율 상위 5위 검색 \n");
		printf("5. 원하는 color 중 판매율 상위 5위 검색 \n");
		printf("6. 할인 이벤트 시작\n");
		printf("0. 종료 \n");
		scanf("%d", &option);

		switch (option)
		{
			case 0:
				save(); //파일에 저장
				return 0;
			case 1:
				add(get_i, get_s);
				break;
			case 2:
				sell(get_i, get_s);
				break;
			case 3:
				inform_stock(get_i, get_s);
				break;
			case 4:
				top_discount();
				break;
			case 5:
				top_sale_by_color(get_s);
				break;
			case 6: 
				new_discount(get_i, get_s);
				break;
			default:
				printf("잘못된 옵션을 입력하셨습니다.\n");
		}
	}

	return 0;
}








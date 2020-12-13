#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define NAME 30
#define COLOR 20
#define LINE 100
#include "def.h"
//신발 정보 구조체 
typedef struct shoes{
	char name[NAME]; //상품명
	char color[COLOR]; //색상	
	int price; //가격
	int discount; //할인율
	int sales_vol; //판매량 
	int size_stock[5][2]; //사이즈별 재고

	struct shoes *next;

}shoes_t;
shoes_t *start = NULL; // 연결리스트의 시작






int inform_shoes()    //shoes 정보 가져와서 연결리스로 만들기 
{

	FILE *s_fp = NULL;   //파일 읽어오기 
	if( (s_fp = fopen("shoes_info.txt", "r")) == NULL)
	{
		fprintf(stderr, "출력을 위한 파일을 열 수 없습니다.\n");
		return 1;
	}

	shoes_t* cur = NULL;
	shoes_t* new_node = NULL;
	char line[LINE];
	char *info;
	int num;
	int index = 0;
	while (fscanf(s_fp, "%s", line) > 0)
	{	
		
		new_node = (shoes_t*)malloc(sizeof(shoes_t)); 
		new_node->next = NULL;
		num = 0;
		info = strtok(line, ",");
		while (info != NULL)
		{
			num ++;
			switch (num)
			{
				case 1: //상품명
					strcpy(new_node->name, info);  
					break;
				case 2: //색상
					strcpy(new_node->color, info);  
					break;
				case 3: //가격
					new_node->price = atoi(info);
					break;
				case 4: //할인율
					new_node->discount = atoi(info);
					break;
				case 5: //판매량
					new_node->sales_vol = atoi(info);
					break;
				case 6: 
				case 8:
				case 10:
				case 12:
				case 14:
					index = num/2 -3;
					new_node->size_stock[index][0] = atoi(info);					
					break;
				case 7:
				case 9:
				case 11:
				case 13:
				case 15:
					index = (num-1)/2 -3;
					new_node->size_stock[index][1] = atoi(info);
					break;
			}
			info = strtok(NULL, ",");
		}
		if (start == NULL)
			start = new_node;  //최초의 node 생성
		else
		{	
			for (cur = start; cur->next != NULL; cur = cur -> next); 
			cur->next = new_node;     //마지막 지점에 struct 삽입
		}
	}
	fclose(s_fp);
	return 0;
}

// 인자로 전달 될 입력 값 받아오는 함수 포인터 2개

int get_i(int sel) // 정수를 입력받아 오는 함수
{
	int i;
	if(sel == 1)
		printf("상품의 사이즈를 입력하시오: ");
	else if(sel == 2)
		printf("상품의 개수를 입력하시오: ");
	else if(sel == 3)
		printf("상품의 가격을 입력하시오: ");
	else if(sel == 4)
		printf("상품의 할인율을 입력하시오: ");
	else
		printf("올바른 sel값을 넣어주십시오.\n");
	scanf("%d", &i);
	return i;
}

void get_s(char *s, int sel) //문자열을 입력받아 오는 함수 
{
	if(sel == 1)
		printf("상품명을 입력하시오: ");
	else if(sel == 2)
		printf("상품의 색상을 입력하시오: ");
	else
		printf("올바른 sel값을 넣어주십시오.\n");
	
	scanf("%s", s);
}

//입고 함수
void add( int (*pf_i)(int), void (*pf_s)(char*, int) ) 
{
	char n_name[NAME];
	char n_color[COLOR];
	int n_size;
	int n_num;
	pf_s(n_name, 1);  //상품명 입력
	pf_s(n_color, 2); //상품의 색상 입력
	n_size = pf_i(1); // 상품의 사이즈 입력
	n_num = pf_i(2); //상품의 개수 입력
	int n_price;
	int n_discount;
	int k;
	int find = 0;
	shoes_t* new_node = NULL;
	shoes_t* cur = NULL;
	new_node = (shoes_t*)malloc(sizeof(shoes_t)); 
	new_node->next = NULL;
	for (cur = start; cur != NULL; cur = cur->next)
	{
		if((strcmp(cur->name, n_name)==0) && (strcmp(cur->color, n_color)==0))
		{
			for (k=0; k <5; k++)
				if(cur->size_stock[k][0] == n_size)
				{
					cur->size_stock[k][1] += n_num;
					find = 1;
					free(new_node);
				}	
		}
		if (find == 1)
			break;
	}
	if(find == 0)
	{
		strcpy(new_node->name, n_name);
		strcpy(new_node->color, n_color);
		for (int z =0; z<5; z++)
		{
			new_node->size_stock[z][1] =0;
			new_node->size_stock[z][0] = 240 + z*10;
		}
		new_node->size_stock[k][1] = n_num;
		new_node->sales_vol = 0;
		n_price = pf_i(3);
		new_node->price = n_price;
		n_discount = pf_i(4);
		new_node->discount = n_discount;	

		for (cur = start; cur->next != NULL; cur = cur -> next); 
			cur->next = new_node;     //마지막 지점에 struct 삽입
	}
}  //기존에 없던 상품명, 색상일 경우 새롭게 등록!

//판매 함수
void sell( int (*pf_i)(int), void (*pf_s)(char*, int) ) 
{
	char n_name[NAME];
	char n_color[COLOR];
	int n_size;
	int n_num;
	pf_s(n_name, 1);  //상품명 입력
	pf_s(n_color, 2); //상품의 색상 입력
	n_size = pf_i(1); // 상품의 사이즈 입력
	n_num = pf_i(2); //상품의 개수 입력

	shoes_t* cur = NULL;
	int find = 0;
	for (cur = start; cur != NULL; cur = cur->next)
	{
		if((strcmp(cur->name, n_name)==0) && (strcmp(cur->color, n_color)==0))
		{
			for (int k=0; k <5; k++)
				if(cur->size_stock[k][0] == n_size)
				{
					if (cur->size_stock[k][1] < n_num)
					{
						printf("재고가 %d개 부족합니다.\n", n_num - cur->size_stock[k][1]);
						for(int m=0; m<5; m++)
							printf("%d 사이즈 재고 : %d개 \n", cur->size_stock[m][0], cur->size_stock[m][1]);
					}

					else
					{
						cur->size_stock[k][1] -= n_num;
						printf("%d 사이즈 %d개 판매완료\n", cur->size_stock[k][0], n_num);
						printf("남은 재고 : %d개 \n", cur->size_stock[k][1]);
						
						cur->sales_vol += n_num;
						printf("총 판매량: %d개\n",cur->sales_vol);
					}				
		
					find = 1;
				}	
		}
		if (find == 1)
			break;
	}
}

//재고 검색 함수
void inform_stock( int (*pf_i)(int), void (*pf_s)(char*, int) ) 
{
	char n_name[NAME];
	char n_color[COLOR];
	int n_size;
	pf_s(n_name, 1);  //상품명 입력
	pf_s(n_color, 2); //상품의 색상 입력
	n_size = pf_i(1); // 상품의 사이즈 입력

	shoes_t* cur = NULL;
	int find = 0;
	for (cur = start; cur != NULL; cur = cur->next)
	{
	
		if((strcmp(cur->name, n_name)==0) && (strcmp(cur->color, n_color)==0))
		{
			for(int k=0; k<5; k++)
				printf("%d사이즈 재고 : %d개 \n", cur->size_stock[k][0], cur->size_stock[k][1]);

			find = 1;
		}
		if (find == 1)
			break;
	}
	if(find == 0)
		printf("상품을 찾지 못하였습니다.\n");
}
	

void top_discount() //할인율 상위 5등 상품 출력 
{
	char d_color[5][COLOR] = { {" "}, {" "}, { " "}, {" "}, {" "}};
	char d_name[5][NAME] = { {" "}, {" "}, { " "}, {" "}, {" "}};
	int d_discount[5] = {0};
		
	int index = 0;
	shoes_t* cur = NULL;
	int rank = 1;

	for(cur = start; cur != NULL; cur = cur->next) //연결리스트 끝까지 반복
	{
		if (cur->discount ==0)
			continue;          //할인율이 0인 상품은 건너뜀.
		
		for(index = 0; index<5; index++)
			if(d_discount[index] > cur->discount)
				break;   		// cur->discount보다 큰 값이 들어있는 index값 추출

		if(index == 0)
			continue;       //첫 번째 배열의 할인율보다 적은 할인율은 건너뜀

		else
		{
			for(int k =1; k<index; k++)
			{
				d_discount[k-1] = d_discount[k];
				strcpy(d_name[k-1], d_name[k]);
				strcpy(d_color[k-1], d_color[k]);
			}
			d_discount[index-1] = cur->discount;
			strcpy(d_name[index-1], cur->name);    //배열 정렬
			strcpy(d_color[index-1], cur->color);
		}

	}
	printf("할인율 순위\n");
	for(int q=4; q > -1; q--)
	{
		printf("%d.  %s상품 %s색상 할인율  :  %d %% \n", rank, d_name[q], d_color[q], d_discount[q]);
		rank += 1;
	}
}


//원하는 색상 중에 판매율 상위 5위 출력
void top_sale_by_color( void (*pf_s)(char*, int) )   
{
	char s_name[5][NAME] = { {" "}, {" "}, { " "}, {" "}, {" "}};
	int s_sales_vol[5] = {0};
	int index = 0;
	shoes_t* cur = NULL;
	char n_color[COLOR];
	pf_s(n_color, 2); //상품의 색상 입력
	int rank = 1;

	for(cur = start; cur != NULL; cur = cur->next) //연결리스트 끝까지 반복
	{
		if ( (cur->sales_vol == 0) || (strcmp(cur->color, n_color) !=0) )
			continue;          //판매량이 0인 상품은 건너뜀 , 색상이 다를 경우 건너뜀
		
		for(index = 0; index<5; index++)
			if(s_sales_vol[index] > cur->sales_vol)
				break;   		// cur의 판매량보다 큰 값이 들어있는 index값 추출

		if(index == 0)
			continue;       //첫 번째 배열의 판매량보다 적은 판매량은 건너뜀

		else
		{
			for(int k =1; k<index; k++)
			{
				s_sales_vol[k-1] = s_sales_vol[k];
				strcpy(s_name[k-1], s_name[k]);
			}
			s_sales_vol[index-1] = cur->sales_vol;
			strcpy(s_name[index-1], cur->name);    //배열 정렬
		}

	}
	printf("%s 색상 판매율 순위 \n", n_color);
	rank = 1;
	for(int q=4; q > -1; q--)
	{
		printf("%d.  %s상품  판매량  :  %d개 \n", rank, s_name[q], s_sales_vol[q]);
		rank += 1;
	}
}

//신발 정보 텍스트 파일에 저장하는 함수
int save()
{
	shoes_t* cur = NULL;

	FILE *s_fp = NULL;   //파일 읽어오기 
	if( (s_fp = fopen("shoes_info.txt", "w")) == NULL)
	{
		fprintf(stderr, "출력을 위한 파일을 열 수 없습니다.\n");
		return 1;
	}

	for (cur = start; cur != NULL; cur = cur->next)
	{
		fprintf(s_fp, "%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n", cur->name,cur->color,cur->price,cur->discount,cur->sales_vol,cur->size_stock[0][0],cur->size_stock[0][1],cur->size_stock[1][0],cur->size_stock[1][1],cur->size_stock[2][0],cur->size_stock[2][1],cur->size_stock[3][0],cur->size_stock[3][1],cur->size_stock[4][0],cur->size_stock[4][1]);

	}
	fclose(s_fp);
	return 0;
}



void new_discount(int (*pf_i)(int), void (*pf_s)(char*, int))
{
	char n_name[NAME];
	char n_color[COLOR];
	int n_discount;
	pf_s(n_name, 1);  //상품명 입력
	pf_s(n_color, 2); //상품의 색상 입력
	n_discount = pf_i(4); // 상품의 할인율 입력
	shoes_t* cur = NULL;
	int find = 0;
	for (cur = start; cur != NULL; cur = cur->next)
	{
		if((strcmp(cur->name, n_name)==0) && (strcmp(cur->color, n_color)==0))
		{
			cur->discount = n_discount;	
			find = 1;
		}
		
		
		if (find == 1)
			break;
	}
	if (find == 0)
		printf("상품을 찾지 못하였습니다.\n");
}










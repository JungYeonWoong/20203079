#pragma once

int inform_shoes(); // shoes 정보 가져와서 연결리스트 생성
void add(int (*pf_i)(int), void (*pf_s)(char*, int)); //입고
void sell(int (*pf_i)(int), void (*pf_s)(char*, int)); //판매
void inform_stock(int (*pf_i)(int), void (*pf_s)(char*, int)); //재고 검색
void top_discount(); // 할인율 상위 5등 제품 출력	
void top_sale_by_color(void (*pf_s)(char*, int)); //원하는 color 중에 판매율 상위 5위 출력  
void new_discount(int (*pf_i)(int), void (*pf_s)(char*, int));

int get_i(int); // 정수를 입력받아 오는 함수 포인터로 사용
void get_s(char*, int); //문자열을 입력받아 오는 함수, 함수 포인터 인자로 넘김 
int save();

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 11. Функция находит в строке симметричный фрагмент вида "abcdcba" длиной 7 и более символов
// (не содержащий пробелов) и возвращает указатель на его начало и длину. 
// С использованием функции "вычеркнуть" все симметричные фрагменты из строки.

const int STR_SIZE = 128;

struct WORD{
	char *pos;
	int len;
};

int wrds_cnt(char *STR, WORD *WORD_LIST = NULL){
	int cnt = 0;
	int space = 0;
	int pos = 0;
	int len = 0;
	for (; STR[pos] != '\0'; pos++){
		if ((!space && (STR[pos] == ' ')) || (STR[pos] == ' ') || (STR[pos + 1] == '\0')){
			if (pos - space >= 7){
				if (space) space++;
				if (STR[pos + 1] == '\0') pos++;
				if (WORD_LIST){
					WORD_LIST[cnt].pos = (STR + space);
					WORD_LIST[cnt].len = (pos - space);
				}
				space = pos;
				cnt++;
			}
		}
	}
	return cnt;
}

bool sym(WORD *WORD_LIST, int index){
	int len = WORD_LIST[index].len;
	if (len < 7) return 0;
	int i = 0;
	int j = len - 1;
	for (; i < j; i++, j--){
		if (WORD_LIST[index].pos[i] - WORD_LIST[index].pos[j]) return 0;
	}
	return 1;
}

WORD *repl(char *STR, WORD *WORD_LIST, int wrds){
	int s = 0;
	
	for (int i = 0; i != wrds; i++){
		if (!sym(WORD_LIST, i))	s++;
	}
	
	WORD *_WORD_LIST = (WORD*)malloc(sizeof(WORD) * wrds);
	
	for (int i = 0, n = 0; i != wrds; i++){
		if (!sym(WORD_LIST, i)){
			_WORD_LIST[n] = WORD_LIST[i];
			n++;
		}
	}
	return _WORD_LIST; 
}

int main(int argc, char *argv[]){
	char STR[STR_SIZE] = "abcxcba bbb11ccca111 cccv1vv11 1123211 abczcba1111abczcbaz";
	int wrds = wrds_cnt(STR);
	
	WORD *WORD_LIST = (WORD*)malloc(sizeof(WORD) * wrds);
	wrds_cnt(STR, WORD_LIST);

	WORD_LIST = repl(STR, WORD_LIST, wrds);
	
	printf("%d", WORD_LIST[5].len);
	
	while(1);
}

//printf("%p", WORD_LIST[0].pos);
//WORD *WORD_LIST = (WORD*)malloc(sizeof(WORD) * wrds_cnt(STR));

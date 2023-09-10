#include <stdio.h>
	int main(){
		int count = 0;
		char c;
		while((c = getchar()) != '\n'){
			count++;
		}
		printf("%d", count);
		return 0;
	}
	
	
	

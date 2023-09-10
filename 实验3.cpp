#include <stdio.h>
int main(){
	FILE *fp1,*fp2;
		fp1=fopen("C:\\Users\\XYM\\Desktop\\devc\\file1.txt","r+");
		char a[102];
		fscanf(fp1,"%s",a);
	fp2=fopen("C:\\Users\\XYM\\Desktop\\devc\\file2.txt","r+");
		for(int i=0;i<102;i++){
			fprintf(fp2,"%c",a[i]);
			
		}
		fclose(fp1);
		fclose(fp2);
		
	
}

#include <stdio.h>
#define MAXLEN 152

void cal(const char *inf, int *total_base,int *reads_num, double *q20, double *q30);

int main(int argc, const char *argv[]){
	const char *inf=NULL;
	double q20=0;
	double q30=0;
	int reads_num=0;
	int total_base=0;
	int i;
	for (i=1;i<argc;i++){
		inf=argv[i];
		printf("fasq file: %s\n",inf);
		cal(inf,&total_base,&reads_num,&q20,&q30);
		printf("reads num: %d\n",reads_num);
		printf(">=q20: %.2f%%\n",q20*100);
		printf(">=q30: %.2f%%\n",q30*100);
	}
	return 0;
}

void cal(const char * inf, int *total_base , int *reads_num, double *q20, double *q30) {
	FILE *f;
	char line[MAXLEN];
	int base_qual=0;
	int total_q20=0;
	int total_q30=0;
	f=fopen(inf,"r");
	if (f==NULL)
		perror("cannot open file");
	while (fgets(line,MAXLEN,f)) {
		(*reads_num)++;
		if ((*reads_num)%4!=0)
			continue;
		else {
	
			puts(line);
			int i=0;
			while (line[i]!='\n') {
				base_qual=line[i]-33;
				if (base_qual>=30){
					total_q30++;
					total_q20++;
				}
				else if (base_qual>=20)
					total_q20++;
				(*total_base)++;
				i++;
			}
		}
	}
	fclose(f);
	*q20=total_q20*1.0/(*total_base);
	*q30=total_q30*1.0/(*total_base);
}



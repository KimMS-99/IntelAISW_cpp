#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<string.h>
int main(int argc, char **argv)
{
	int n, in, out;
	char buf[500]; // 1024

	printf("argc : %d\n", argc);
	int i = 0;
	while(*argv != NULL)
	{
		printf("argv[%d] : %s\n", i, *argv);
	//	for(int j = 0; j < strlen(argv[i]); j++)
	//		printf("argv[%d][%d] : %c\n", i, j, *(*(argv+i)+j));
		for(int j = 0; j < strlen(*argv); j++)
			printf("%c\n", *(*argv+j));
		argv++;
	}
	if(argc < 3){
	//	write(2, "Usage : copy file1 file2\n", 25);
	//	fputs("Usage : coppy file1 file2", stderr);
		printf("Usage : %s file1 file2\n", argv[0]);
		return 1;
	}

	if((in = open(argv[1], O_RDONLY)) < 0) {
			perror(argv[1]);
			return 2;
	}
	
	if((out = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR|S_IWGRP|S_IRGRP|S_IROTH)) < 0){
		perror(argv[2]);
		return 3;
	}
	//while((n = read(in, buf, sizeof(buf))) > 0)
	//		write(out, buf, n);
	do{
		n = read(in, buf, sizeof(buf));
		printf("n : %d\n", n);
		if(n > 0)
			write(out, buf, n);
		else if(n == 0)
		{
			fputs("Done...\n", stderr);
			break;
		}
		else
		{
			perror("read()");
			break;
		}
	}while(1);

	close(out);
	close(in);

	return 0;

}

#include <sys/ioctl.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

//Declarations
void print_page(FILE *file, struct winsize *ws);
void flip_pages(FILE *file, struct winsize *ws, int page);
//int check_line_length(char* filename,int pos);
//bool check_if_newline(char* input,int count);
char* buffer[20];
int	main(int argc,char *argv[])
{
	FILE* fd = fopen("a.txt","r");
	struct winsize ws;
	if (ioctl(0,TIOCGWINSZ,&ws)!=0) {
		fprintf(stderr,"TIOCGWINSZ:%s\n",strerror(errno));
		exit(-1);
	}
	flip_pages(fd, &ws, 0);
	printf("row=%d, col=%d, xpixel=%d, ypixel=%d\n",
	ws.ws_row,ws.ws_col,ws.ws_xpixel,ws.ws_ypixel);


	//printf("%s\n",argv[1]); nur zum probieren ob es die richtige File nimmt.

	fclose(fd);
	return 0;
}
void print_page(FILE *file, struct winsize *ws) {
    char *buffer = malloc(sizeof(char) * (ws->ws_col + 1));
    for (int i = 0; i < ws->ws_row && !feof(file); i++) {
        fgets(buffer, ws->ws_col, file);
        printf("%s", buffer);
    }
    free(buffer);
}

void flip_pages(FILE *file, struct winsize *ws, int page) {
    rewind(file);
    if (file == 0)return;
    char input;
    int count = 0;
    while (count <= page) {
        system("clear");
        print_page(file, ws);
        count++;
    }
    input = getchar();
    if (input == '\n' && !feof(file)) {
        flip_pages(file, ws, page + 1);
    }
		else if (input == 'b' && page > 0) {
        while (input != '\n'){
            input = getchar();
					}
        flip_pages(file, ws, page - 1);
    }
		else if (input != '\n')
		{
        while (input != '\n')
            input = getchar();
        flip_pages(file, ws, page);
    }
}

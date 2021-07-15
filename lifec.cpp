
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h> 
#include <iostream>
#include <ostream>
#include <signal.h>
#include <string.h>


void drawTable(int **grid,int w,int h)
{
        for(int i=0;i<w;i=i+2){
            for(int j=0;j<h;j++){
                if(grid[i][j]==0){
                    if(grid[i+1][j]==0){
                        std::cout<<" ";
                    }else{
                        std::cout<<"▄";
                    }
                    }else{
                        if(grid[i+1][j]==0){
                            std::cout<<"▀";
                        }else{
                            std::cout<<"█";
                        }
                    }
                }
                std::cout<<std::endl;
        }

}


void signal_callback_handler(int signum) {
    system("clear");
    std::cout << "\033[0m\n";
    //enable cursor
    std::cout << "\e[?25h";

    exit(signum);
}

int main(int argc, char *argv[])

{
	int cols,rows;
	int** array;
	int** array2;
    int color=0;
    int nCycles=100;
	srand (time(NULL));

    signal(SIGINT, signal_callback_handler);

#ifdef TIOCGSIZE
    struct ttysize w;
    ioctl(STDIN_FILENO, TIOCGSIZE, &w);
    //cols = ts.ts_cols;
    //lines = ts.ts_lines;
#elif defined(TIOCGWINSZ)
    struct winsize w;
    ioctl(STDIN_FILENO, TIOCGWINSZ, &w);
    //cols = ts.ws_col;
    //lines = ts.ws_row;
#endif /* TIOCGSIZE */




    for(int i = 1; i < argc; i++){
		if(!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help") ){
			printf("Usage: App <options>\nOptions are:\n");
			printf("\t-c \tChange the colors of the cells\n");
            printf("\t-n \tChange the numbers of cycles to reset the table (by default 100)\n");
            printf("Colors:\n");
            printf("\t1 \tBlack\n");
            printf("\t2 \tRed\n");
            printf("\t3 \tGreen\n");
            printf("\t4 \tYellow\n");
            printf("\t5 \tBlue\n");
            printf("\t6 \tMagenta\n");
            printf("\t7 \tCyan\n");
            printf("\t8 \tLight gray\n");
            printf("\t9 \tDark gray\n");
            printf("\t10 \tLight red\n");
            printf("\t11 \tLight green\n");
            printf("\t12 \tLight yellow\n");
            printf("\t13 \tLight blue\n");
            printf("\t14 \tLight magenta\n");
            printf("\t15 \tLight cyan\n");


			exit(0);
		}else if(!strcmp(argv[i], "-c")){
			color = atoi(argv[i+1]);

            if(0<color<16){
                switch (color)
                {
                case 1:
                    std::cout<< "\033[1;30m";
                    break;
                case 2:
                    std::cout<< "\033[1;31m";
                    break;
                case 3:
                    std::cout<< "\033[1;32m";
                    break;
                case 4:
                    std::cout<< "\033[1;33m";
                    break;
                case 5:
                    std::cout<< "\033[1;34m";
                    break;
                case 6:
                    std::cout<< "\033[1;35m";
                    break;
                case 7:
                    std::cout<< "\033[1;36m";
                    break;
                case 8:
                    std::cout<< "\033[1;37m";
                    break;
                case 9:
                    std::cout<< "\033[1;90m";
                    break;
                case 10:
                    std::cout<< "\033[1;91m";
                    break;
                case 11:
                    std::cout<< "\033[1;92m";
                    break;
                case 12:
                    std::cout<< "\033[1;93m";
                    break;
                case 13:
                    std::cout<< "\033[1;94m";
                    break;
                case 14:
                    std::cout<< "\033[1;95m";
                    break;
                case 15:
                    std::cout<< "\033[1;96m";
                    break;
                }

            }else{
                printf("Invalid color!!");
                exit(0);
            }
		}else if(!strcmp(argv[i], "-n")){

            nCycles = atoi(argv[i+1]);
		}else{
			if(i == argc-1){
				break;
			}
			printf("ERROR: Invalid Command Line Option Found: \"%s\".\n", argv[i]);
            exit(0);
		}
	}


    rows = w.ws_row*2;
	cols = w.ws_col;
	
	
	
	
	array = new int*[rows];
	array2 = new int*[rows];

    //hide cursor
    std::cout<<"\e[?25l";

	int remainCycles=0;
     	while(1)
	{
		system("clear");
		if(remainCycles==0){
			for(int i=0;i<=rows;i++){
				array[i] = new int[cols];
				array2[i] = new int[cols];
				for(int j=0;j<cols;j++){
					array[i][j]=0;
					array2[i][j]=0;
				
				}
			
			}


			int max=cols+rows;
	
			for(int i=0;i<max*8;i++){
				array[rand() % rows][rand() % cols]=1;
		
	
			}
			remainCycles=nCycles;
		}

		for(int i = 0; i<=rows; i++){
			for(int j = 0; j<=cols ; j++){
			//!!!!!!
				int nNeighbours=0;
				if(i==0&&j==0){
					 nNeighbours = array[i+1][j]+array[i][j+1]+array[i+1][j+1];
				}
				else if(i==0&&j==cols){
					 nNeighbours =array[i][j-1]+array[i+1][j-1]+array[i+1][j];
				}
				else if(i==rows&&j==0){
                    nNeighbours =array[i-1][j]+array[i-1][j+1]+array[i][j+1];
				}
				else if(i==rows&&j==cols){
                    nNeighbours = array[i-1][j-1]+array[i][j-1]+array[i-1][j];
				}
				else if(i==0){
					nNeighbours =array[i][j-1]+array[i+1][j-1]+array[i+1][j]+array[i][j+1]+array[i+1][j+1];
				}
				else if(j==0){
					nNeighbours = array[i-1][j]+array[i+1][j]+array[i-1][j+1]+array[i][j+1]+array[i+1][j+1];
                }
                else if(j==cols){
                    nNeighbours =array[i-1][j-1]+array[i][j-1]+array[i+1][j-1]+array[i-1][j]+array[i+1][j];
				}else if(i==rows){
					nNeighbours =array[i-1][j-1]+array[i][j-1]+array[i-1][j]+array[i-1][j+1]+array[i][j+1];
				}
                else {
                    nNeighbours =array[i-1][j-1]+array[i][j-1]+array[i+1][j-1]+array[i-1][j]+array[i+1][j]+array[i-1][j+1]+array[i][j+1]+array[i+1][j+1];
				}

		       
				if(array[i][j] == 1 && (nNeighbours==2 || nNeighbours==3)){
					array2[i][j] = 1;
				}else if(array[i][j] == 0 && nNeighbours==3){
					array2[i][j] = 1;
				}

			
			}

		}
		drawTable(array2,rows,cols);
		for(int i = 0; i<=rows; i++){
                        for(int j = 0; j<=cols ; j++){
				array[i][j]=array2[i][j];
				array2[i][j]=0;
                        
                        }
                }



		remainCycles--;
		usleep(250000);
	}
    
	return EXIT_SUCCESS;
}






//importing header files needed for the program
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

//Defining constants
#define BRIGHTEN 	1

#define SET_BACK	0


//Defining function prototypes for the functions that are going to be used later
void print_coloured_text(int,int,int);
void fix_digit(char, int, int);
void print_letters(int array[5][6], int, int);


int main(int argc, char **argv){
	int req_colour,position; //req_colour is used for assigning required colours.
  if (argc==2){
    if (strcmp(argv[1],"-h")==0){//Displaying the help message
    	printf("usage : clock -h                quick help on cmd \nusage : clock -c <color>        print clock with a color \n<color-black|red|green|yellow|blue|magenta|cyan|white>  supported colors\n");
        }
    else{
        //Displaying an error message if other arguments are given.
      printf("Invalid use of arguments.\nusage : clock -h                quick help on cmd\nusage : clock -c <color>        print clock with a color\n");
      }
          return 0;
    }
	if(argc==1){
		// Set default colour as white
		req_colour = 7;
	}

    //For 3 or more arguments, we consider all the cases in one else if condtion.
	else if(argc>=3){
         char *argument;
        //.....................Selection of colours................
        for (int i= 0; i <argc; i++){
            argument=argv[i];
            if (strcmp(argument,"-h")==0)
                    {
                        printf("usage : clock -h                quick help on cmd\nusage : clock -c <color>        print clock with a color\n<color-black|red|green|yellow|blue|magenta|cyan|white>  supported colors\n");
                        return 0;
                    }
            else if (strcmp(argument,"-c")==0){
			if (argv[i+1]!=0){
				for(int j = 0; argv[i+1][j]!='\0'; j++){
  					argv[i+1][j]= tolower(argv[i+1][j]);
				}
			}
				if (argv[i+1]!=0){
					if (strcmp(argv[i+1],"black")==0){
						req_colour=0;
					}
					else if (strcmp(argv[i+1],"red")==0){
						req_colour=1;
					}
					else if (strcmp(argv[i+1],"green")==0){
						req_colour=2;
					}
					else if (strcmp(argv[i+1],"yellow")==0){
						req_colour=3;
					}
					else if (strcmp(argv[i+1],"blue")==0){
						req_colour=4;
					}
					else if (strcmp(argv[i+1],"magenta")==0){
						req_colour=5;
					}
					else if (strcmp(argv[i+1],"cyan")==0){
						req_colour=6;
					}
					else if (strcmp(argv[i+1],"white")==0){
						req_colour=7;
					}
					else{
						//error message showing correct colour inputs
						printf("%s:This is not a valid color, Please enter one of these colours: black, red, green, yellow, blue, magenta, cyan, white\n",argv[2]);
						return 0;
					}
				}
				else{
					  printf("Invalid use of arguments.\nusage : clock -h                quick help on cmd\nusage : clock -c <color>        print clock with a color\n");
					  return 0;	
				}
            }
			else if ((strcmp(argument,"-c")==1)|| (strcmp(argument,"-h")==1)){
				req_colour=7;
			}
        }
    }

    printf("\033[2J");		// Clear the printed area in console

	printf("\033[?25l");	// Hides the cursor from the terminal



	while(1){
		char date[20],time_string[20];
		time_t present_time;  		//.......This variable is used to store the presesnt time
		present_time = time(NULL);  // time gone in secodns since the program is started 
  		struct tm* sorted_time = localtime(&present_time); 
		strftime(date,20,"%Y-%m-%d ", sorted_time);	// Converts the date in to string 
  		strftime(time_string,20,"%H:%M:%S", sorted_time);	// Converts the time in to string
  		

    //..................This for loop prints the letters in time in the corresponding position........................
  	for(position=0;position<8;position++){	
  		fix_digit(time_string[position],position,req_colour);
    }

  	printf("\033[8;23H");
	print_coloured_text(BRIGHTEN, req_colour, 8);//Printing the colour

    
    //............This loop is used to print date......................
  	for(int i=0;i<12;i++){
  		printf("%c",date[i]);
  	}

  	printf("\n");
  	print_coloured_text(SET_BACK,7, 0);
  	sleep(1); //Sleep is used to display time after every second.
  	}
	return 0;
}

//Function to print the text in required colour
void print_coloured_text(int prop, int foreground_colour, int background_colour){
	printf("\033[0m");
	if (prop == BRIGHTEN){
        //foreground_colour is used to colour the text of digit of the time and date that are printed
        //background_colour is used to colour the empty spaces (backgrounds) when digit of the time and date that are printed
		if (foreground_colour == 8){
			printf("\033[%dm", background_colour +40);
		}else{
			printf("\033[%dm", foreground_colour +30);
		}
	}
}


// Defining an array for each digits that are needed to be printed as patterns

void fix_digit(char input,int position,int colour){
    switch (input){
    //We are defining a case also for the colon to print the colon.
	case ':':
    {
    int digit_array[5][6] = {
        {0,0,0,0,0,0},
        {0,0,1,1,0,0},
        {0,0,0,0,0,0},
        {0,0,1,1,0,0},
        {0,0,0,0,0,0}};
    print_letters(digit_array,position,colour);
	break;
	}
    case '0':{
    int digit_array[5][6]={			
		{1,1,1,1,1,1},
		{1,1,0,0,1,1},
		{1,1,0,0,1,1},
		{1,1,0,0,1,1},
		{1,1,1,1,1,1}
	};
	print_letters(digit_array,position,colour);
	break;
	}

	case '1':{
		int digit_array[5][6]={			
		{0,0,0,0,1,1},
		{0,0,0,0,1,1},
		{0,0,0,0,1,1},
		{0,0,0,0,1,1},
		{0,0,0,0,1,1}
	};
	print_letters(digit_array,position,colour);
	break;
	}

	case '3':{
		int digit_array[5][6]={			
		{1,1,1,1,1,1},
		{0,0,0,0,1,1},
		{1,1,1,1,1,1},
		{0,0,0,0,1,1},
		{1,1,1,1,1,1}
	};
	print_letters(digit_array,position,colour);
	break;
	}

	case '5':{
		int digit_array[5][6]={			
		{1,1,1,1,1,1},
		{1,1,0,0,0,0},
		{1,1,1,1,1,1},
		{0,0,0,0,1,1},
		{1,1,1,1,1,1}
	};
	print_letters(digit_array,position,colour);
	break;
	}
	
	case '2':{
		int digit_array[5][6]={			
		{1,1,1,1,1,1},
		{0,0,0,0,1,1},
		{1,1,1,1,1,1},
		{1,1,0,0,0,0},
		{1,1,1,1,1,1}
	};
	print_letters(digit_array,position,colour);
	break;
	}
	
	case '4':{
		int digit_array[5][6]={			
		{1,1,0,0,1,1},
		{1,1,0,0,1,1},
		{1,1,1,1,1,1},
		{0,0,0,0,1,1},
		{0,0,0,0,1,1}
	};
	print_letters(digit_array,position,colour);
	break;
	}

	case '6':{
		int digit_array[5][6]={			
		{1,1,1,1,1,1},
		{1,1,0,0,0,0},
		{1,1,1,1,1,1},
		{1,1,0,0,1,1},
		{1,1,1,1,1,1}
	};
	print_letters(digit_array,position,colour);
	break;
	}
	
	case '8':{
		int digit_array[5][6]={			
		{1,1,1,1,1,1},
		{1,1,0,0,1,1},
		{1,1,1,1,1,1},
		{1,1,0,0,1,1},
		{1,1,1,1,1,1}
	};
	print_letters(digit_array,position,colour);
	break;
	}

	case '7':{
		int digit_array[5][6]={			
		{1,1,1,1,1,1},
		{0,0,0,0,1,1},
		{0,0,0,0,1,1},
		{0,0,0,0,1,1},
		{0,0,0,0,1,1}
	};
	print_letters(digit_array,position,colour);
	break;
	}

	case '9':{
		int digit_array[5][6]={			
		{1,1,1,1,1,1},
		{1,1,0,0,1,1},
		{1,1,1,1,1,1},
		{0,0,0,0,1,1},
		{1,1,1,1,1,1}
	};
	print_letters(digit_array,position,colour);
	break;
	}
}
}

void print_letters(int array[5][6],int position, int colour){
	int spaces,column,row;
    //According to position, the spaces are determined.
	if (position==0)
		spaces=2;
	else if(position==1)
		spaces=9;
  else if(position==2)
		spaces=15;
	else if(position==3)
		spaces=21;
	else if(position==4)
		spaces=28;
  else if(position==5)
		spaces=34; 
	else if(position==6)
		spaces=40;
	else if(position==7)
		spaces=48;

    int number;
    //We are using spaces for printing big coloured outputs.
	for(row=0;row<5;row++){
		for(column=0;column<6;column++){
			printf("\033[%d;%dH",row+2,spaces+column);
			number = array[row][column];
            //If the number is zero,colour it by printing spaces.
			if(number==0){
				print_coloured_text(SET_BACK, 7, 0); //Set_Back is given so that next colour can be printed without continuing to print the same colour of the previous digit or space for the next blank spaces of next number,
				printf(" "); //print spaces in specified colour input given above.
			}
            //If the number is 1, colour it by printing coloured spaces
			else if(number==1){
				print_coloured_text(BRIGHTEN, 8, colour);
				printf(" ");//print spaces in specified colour input given above.
			}
		}
		print_coloured_text(SET_BACK, 7, 0);
	}
}




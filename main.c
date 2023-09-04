//seyed amirhosein mousavi nasab //1398.10.18-1398.10.07//program of the pocke tank game
//lotfan dar hengam ejraye barname full screen konid...thank you... 
#include<windows.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <dos.h>
#include <dir.h>
#include <pthread.h>
#include <mmsystem.h>
#define NUM_THREADS 2
void themass () {

PlaySound(TEXT("01-The-Mass-eRa-www.softgozar.com.WAV"), NULL, SND_LOOP | SND_ASYNC); // play music
}

void *playmusic(void *threadid)
{
   long tid;
   tid = (long)threadid;

   themass ();

   pthread_exit(NULL);
}

  int m1[20];	//x for first function
  int n1[20];
  int k1[20];
  int l1[20];
  int m2[20];	//x for second function
  int n2[20];
  int k2[20];
  int l2[20];
  int m3[20];	//x for third function
  int n3[20];
  int k3[20];
  int l3[20];
  int m4[15];	//x for forth function
  int n4[15];
  int k4[15];
  int l4[15];
int gameover = 0;	//end of game
int flag = 0;
int flag1 = 0;
int flag2 = 0;
int flag3;
int flag4;
int m;
int end = 1;
int next = 0;
int n = 0;
int z = 0;
int sum1 = 0;
int sum2 = 0;
double w;

struct score 	//score list
{
  int score1;
  int score2;
  struct score * link;
};

struct inf 	//speed and angle
{
  double angle;
  double v;
};
//gotoxy
int gotoxy(int x, int y) 
{
  HANDLE hConsoleOutput;
  COORD dwCursorPosition;
  dwCursorPosition;
  dwCursorPosition.X = x;
  dwCursorPosition.Y = y;
  hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);

}
void SetColor(int ForgC)
{
	WORD wColor;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	
	if(GetConsoleScreenBufferInfo(hStdOut,&csbi));
	{
		wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
		SetConsoleTextAttribute(hStdOut , wColor);
	}
	return 0;
}
//time func
time_t now, later;

void sleep(int delay) {
  now = time(NULL);
  later = now + delay;
  while (now <= later) now = time(NULL);
}
int menu();
int mount();	//mount function
int player1(double, struct inf pl);	//player one function
int player2(struct inf pl, double);	//player two function
int tank(double, double, double, double);
int fling(double, double,double, double, struct inf pl, double, struct score * temp, struct score * p);
int fling2(double, double,double, double, struct inf pl, double, struct score * temp, struct score * p);
int scorelist(struct score * temp);
int hint();
int check();
int logo();
int cloud();
//***********************************
int main()
{
    // play music while playing
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;
    for(t=0; t<NUM_THREADS; t++){
      rc = pthread_create(&threads[t], NULL, playmusic, (void *)t); // play music
      if (rc){
         printf("ERROR; return code from pthread_create() is %d\n", rc);
         exit(-1);
      }
    }

	  struct score * start;
  start = (struct score * ) malloc(sizeof(struct score));
  start -> link = '\0';
  struct score * temp;
  temp = (struct score * ) malloc(sizeof(struct score));
  temp=start;
  temp->score1=0;
  temp->score2=0;
  struct inf pl;
  double x1 = 20;
  double y1 = 170 + (7 * (-1));
  double x2 = 170;
  double y2 = 170 + (30 * (-1));
  char ch;
  double x0;	//first place
  double y0;	//first place
  double a;
  double c = 5;
  	//time
  double k;
  double v;	//speed
  char ch1;
  system("color 85");	//background and foreground color
  logo();
  menu:
  menu();  	
  system("cls"); 
  if (m == 1) 
   {
   		system("color f4");
	    gotoxy(85, 25);
	   printf("Is ");
	   sleep(.25);
	   printf("This ");
	   sleep(.25);
	   printf("Your ");
	   sleep(.25);
	   printf("First ");
	   sleep(.25);
	   printf("Time????");
	   sleep(.25);
	   printf("(y or n)");	   
	    ch = getch();
	    if (ch == 'y') 	//go for hint user
		{
	      system("cls");
	      hint();
	      sleep(8);
	      system("cls");
	    }
	    else
	    system("cls");	//cleare screen
	    system("color 0f");	//color
	    tank(x1, y1, x2, y2);	//tank
	    mount();	//mountain
	    cloud();
	    while (gameover == 0) 
	   {
		    struct score *p;
		    p = (struct score * ) malloc(sizeof(struct score));
		    if (end == 1) 
			{
		        pl.angle = 0;	//angle=0
		        end = 0;
		    }
		      if (next == 0)
		        player1(x1, pl);	//go to function of player 1
		    if (flag == 1 && next == 0) 
			{
				SetColor(9);
		        if (flag1 == 1) 
				{
				   if(x1<25)
				   {
			          x1++;
			        }
			        flag1 = 0;
			        gotoxy(20, 170 + (2 * -1));
			        printf("Angle:%5.2lf", pl.angle);	//print angle			        
		        }
		        if (flag2 == 1) 
				{
					if(x1>0)
					{
		          		x1--;
		          	}
			          flag2 = 0;
			          gotoxy(20, 170 + (2 * -1));
			          printf("             ");
			          gotoxy(20, 170 + (2 * -1));
			          printf("Angle:%5.2lf", pl.angle);		//print angle
		        }
		        if (flag3 == 1) 
				{
				  gotoxy(20, 170 + (2 * -1));	//move
				  printf("             ");
		          gotoxy(20, 170 + (2 * -1));
		          if(pl.angle<100)	//move
				  {
		            pl.angle += 5;
		      	  }
		      	  printf("Angle:%5.2lf", pl.angle);		//if you choose 'w' from the key board --> angle + 5
		          flag3 = 0;		      	  
		        }
		        if (flag4 == 1) 
				{
		          gotoxy(20, 170 + (2 * -1));
		          if(pl.angle>0)
				   {
			          pl.angle -= 5;
			          printf("Angle:%5.2lf", pl.angle);		//if you choose 's' from the key board --> angle - 5
		      	   }
		          flag4 = 0;
		        }
		        tank(x1, y1, x2, y2);
		    }
		    if (n == 1) 	//when player one finish his round
			{
		        v = w;
		        x0 = x1 + 4;
		        y0 = y1;
				temp->link=p;	//link list for scores
				temp=temp->link;				
		        fling(x0, y0,x2, v, pl, t, temp, p);	//fling fuction
		        system("cls");	//clear screen
		        mount();
		        cloud();
		        tank(x1, y1, x2, y2);	//tank function
		        n = 0;
		    }
		      gotoxy(10, 170 + (-1 * 50));
		      SetColor(4);
		      printf("*.*.*.*.*Player1:%d*.*.*.*.*", sum1);	//point of player1
		      gotoxy(170, 170 + (50 * -1));
		      SetColor(9);
		      printf(".#.#.#.#.#Player2:%d.#.#.#.#.#", sum2);	//point of player2
		    if (end == 1) 
			{
		        pl.angle = 0;
		        end = 0;
		    }
		    if (next == 1) 
			{
				SetColor(4);
		        player2(pl, x2);	//function player 2
		        if (flag == 1) 
				{
		          if (flag1 == 1) 
				   {
				   		if(x2 < 195)
				   		{
			            	x2++;		//angle		   			
						}
			            flag1 = 0;
			            gotoxy(170, 170 + (25 * -1));
			            printf("Angle:%5.2lf", pl.angle);	//angle
		            }
		          if (flag2 == 1) 
				   {
				   		if(x2>150)
				   		{
				   			x2--;
						}
			            flag2 = 0;
			            gotoxy(170, 170 + (25 * -1));	//moving tank
				   	    printf("             ");
			            gotoxy(170, 170 + (25 * -1));	//angle
			            printf("Angle:%5.2lf", pl.angle);
		            }
		          if (flag3 == 1) 
				   {
				   	    gotoxy(170, 170 + (25 * -1));
				   	    printf("             ");	
			            gotoxy(170, 170 + (25 * -1));
			            if(pl.angle<100)	//if you choose 'w' from the key board --> angle + 5
			            {
				            pl.angle += 5;
			        	}
			        	printf("Angle:%5.2lf", pl.angle);
			            flag3 = 0;
		            }
		          if (flag4 == 1) 
				   {
			            gotoxy(170, 170 + (25 * -1));
			            if(pl.angle>0)	//move
			            {
				            pl.angle -= 5;		//if you choose 's' from the key board --> angle - 5
				            printf("Angle:%5.2lf", pl.angle);
				        }
			            flag4 = 0;
		            }
		          tank(x1, y1, x2, y2);
		        }
		        if (z == 1) 
				{
		          x0 = x2 + 4;
		          y0 = y2;
		          v = w;
		          fling2(x0, y0,x1, v, pl, t, p, temp);	//fling for player2
		          system("cls");
		          gotoxy(10, 170 + (-1 * 50));
		          SetColor(4);
		          printf("*.*.*.*.*Player1:%d*.*.*.*.*", sum1);	//point of player 1
		          gotoxy(170, 170 + (50 * -1));
		          SetColor(9);
		          printf(".#.#.#.#.#Player2:%d.#.#.#.#.#", sum2);  //point of player 2
		          mount();
		          cloud();
		          tank(x1, y1, x2, y2);		          
		          z = 0;
	        	}
	       }
	    }
	    temp = start;
	    system("color 4e");	//color
	    int h=0;
	    scorelist(temp);
	    while(temp!='\0')
	    {
			gotoxy(85,24+h);
			printf("      %d                                       %d   ",temp->score1,temp->score2);	//players final scores
			temp=temp->link;
			h++;	    	
		}
	    int i;
		
	}
	if(m==2)	//about
	{
		system("color 4e");
		gotoxy(85, 25);
		sleep(.5);
		printf("this program produced at june 2020...");
		gotoxy(85, 26);
		sleep(.5);
		printf("Our team are realy glad that you choose our game...");
		gotoxy(85, 27);
		sleep(.5);
		printf("please help us with your opnions...");
		gotoxy(85, 28);
		sleep(.5);
		printf("company: musio group");
		gotoxy(85, 29);
		sleep(.5);
		printf("phone: 021-88126728");
		gotoxy(85, 30);
		sleep(.5);
		printf("thanks for your time...");
		sleep(2);
		system("cls");
		goto menu;
		
	}
	if(m==3)	//exit
	{
		gotoxy(100,26);
		printf("thank you...");
		gotoxy(100,27);
		printf("GOOD LUCK...");
		return 0;
	}
    pthread_exit(NULL);
}

//*****************************
int mount() 
{
  SetColor(6);
  double x;
  double y;
  int i;
  x = 40;
  y = 4;
  for (i = 0; i < 20; i++) 	//first mount
   {
	    x++;
	    y++;
	    m1[i] = x;
	    n1[i] = y;
	    gotoxy(m1[i], 170 + (-1 * n1[i]));
	    printf(".-");
    }
   x++;
  for (i = 0; i < 20; i++) //first mount
   {
	    x++;
	    y--;
	    k1[i] = x;
	    l1[i] = y;
	    gotoxy(k1[i], 170 + (-1 * l1[i]));
	    printf("-.");
    }
    x = k1[10];
    y = l1[10];
  for (i = 0; i < 16; i++) //second mount
   {
	    x++;
	    y++;
	    m2[i] = x;
	    n2[i] = y;
	    gotoxy(m2[i], 170 + (-1 * n2[i]));
	    printf(".-");
    }
//    y++;
    x += 1;
  for (i = 0; i < 20; i++)	//second mount 
   {
	    x++;
	    y--;
	    k2[i] = x;
	    l2[i] = y;
	    gotoxy(k2[i], 170 + (-1 * l2[i]));
 	    printf("-.");
    }
    x = k2[12];
    y = l2[12];
  for (i = 0; i < 16; i++) //third mount
   {
	    x++;
	    y++;
	    m3[i] = x;
	    n3[i] = y;
	    gotoxy(m3[i], 170 + (-1 * n3[i]));
	    printf(".-");
    }
//    y++;
    x += 1;
  for (i = 0; i < 20; i++) //third mount
   {
	    x++;
	    y--;
	    k3[i] = x;
	    l3[i] = y;
	    gotoxy(k3[i], 170 + (-1 * l3[i]));
	    printf("-.");
    }
    x = k3[10];
    y = l3[10];
  for (i = 0; i < 12; i++) 	//forth mount
   {
	    x++;
	    y++;
	    m4[i] = x;
	    n4[i] = y;
	    gotoxy(m4[i], 170 + (-1 * n4[i]));
	    printf(".-");
    }
    x += 1;
  for (i = 0; i < 11; i++) 	//fourth mount
   {
	    x++;
	    y--;
	    k4[i] = x;
	    l4[i] = y;
	    gotoxy(k4[i], 170 + (-1 * l4[i]));
	    printf("-.");
    }
}
//********************
int tank(double x1, double y1, double x2, double y2) 	//tank
{
  SetColor(4);	
  gotoxy(x1, y1);
  printf("     .- -. ");
  gotoxy(x1, y1 + 1);
  printf("  .-='= ='==-, ");
  gotoxy(x1, y1 + 2);
  printf(" (O_o_o _o_o_O) ");
  gotoxy(0, y1 + 3);
  SetColor(6);
  printf("_______________________________________");
  gotoxy(x2, y2);
  SetColor(9);
  printf("      .- -. ");
  gotoxy(x2, y2 + 1);
  printf("  ,-=='= ='=-. ");
  gotoxy(x2, y2 + 2);
  printf("  (O_o_o_o_o_O) ");
  gotoxy(150, y2 + 3);
  SetColor(6);
  printf("___________________________________________________________");
}
//*****************************

int player1(double x1, struct inf pl) 
{
	int r;	
  int q = 0;
  char move;
  flag = 0;
  gotoxy(x1, 170 + -1 * 4);
  if (kbhit)
  {
    move = getch();
  }
  switch (move) 
   {
	  case ('d'):	//right move
	    flag1 = 1;
	    flag = 1;
	    break;
	  case ('a'):	//left move
	    flag2 = 1;
	    flag = 1;
	    break;
	  case ('w'):	//angle
	    flag3 = 1;
	    flag = 1;
	    break;
	  case ('s'):	//angle
	    flag4 = 1;
	    flag = 1;
	    break;
	    

    }
  if (flag == 0) 
   {
   	    speed:
	    pl.v = '\0';
	    gotoxy(20, 170 + (3 * -1));
	    printf("Speed:");	//get speed
	    scanf("%lf", & pl.v);
	    if(pl.v > 100)
	    {
	    	gotoxy(20, 170 + (3 * -1));
			printf("              ");
			goto speed;		    	
		}
		else
		{
		    w = pl.v;
		    next = 1;
		    end = 1;
		    n = 1;
		}
    }
}
//**************************
int player2(struct inf pl, double x2) 
{
  int q = 0;
  char move;
  flag = 0;
  gotoxy(x2, 170 + -1 * 28);	
  if (kbhit) 
  {
    move = getch();
  }
  switch (move) 
   {
	  case ('d'):	//move
	    flag1 = 1;
	    flag = 1;
	    break;
	  case ('a'):	//move
	    flag2 = 1;
	    flag = 1;
	    break;
	  case ('w'):	//angle
	    flag3 = 1;
	    flag = 1;
	    break;
	  case ('s'):	//angle
	    flag4 = 1;
	    flag = 1;
	    break;

 	}
  if (flag == 0) 
   {
   		speed:
		gotoxy(170, 170 - 26);
		printf("Speed:");	//speed
		scanf("%lf", & pl.v);
		if(pl.v > 100)
		{
			gotoxy(170, 170 - 26);
			printf("              ");
			goto speed;	
		}
		else
		{
			w = pl.v;
			next = 0;
			end = 1;
			z = 1;
		}
    }
}
//************************

int fling(double x0, double y0,double x2, double v, struct inf pl, double t, struct score * temp, struct score * p) 	//fling for player 1
{
  double T;
  y0 = 7;
  x0 = x0 + 4;
  int bump = 0;
  int bump1 = 0;
  int stop = 0;
  double x;
  double y;
  double yk;
  int ycheck;
  int xcheck;
  double ykeep;
  int i;
  int j;
  int k;
  int e;
  int r;
  const double g = 9.8;		//gravity
  const double PI = 3.14159265 / 180;	//pi number
  t = (v * sin(pl.angle * PI) * 2) / g;
  T = 0;
  while (T < t && bump == 0 && bump1 == 0 && stop == 0) 
   {
	    x = v * cos(pl.angle * PI) * T + x0;	//x for fling
	    y = (-1 * 0.5 * g * T * T) + v * sin(pl.angle * PI) * T + y0;	//y for fling
	    ycheck=y;
	    y = (-1 * y + 170);
	    xcheck=x;
	    if (x > 170 + 40 || y< 170 + ( -1 * 65)) 
		{
	      stop = 1;
	    }
	    if (y > (170 + 31 * -1) && x > 170 && stop != 1) 	//when all shot arrived the tank
		{
		    T = (((2 * v * sin(pl.angle * PI)) / g) + sqrt(pow(((2 * v * sin(pl.angle * PI)) / g), 2) - ((4 * 24 * 2) / g))) / 2;	//calculation time
		    x = v * cos(pl.angle * PI) * T + x0;
		    if (x > x2 + 4 && x < x2 + 9) 
			{
		    	y = 30;
		        y = (-1 * y + 170);
		        gotoxy(x, y);
		        printf("o");
		        sleep(0.3);
		        bump = 1;
		    }
		   else 	//the top of tank
		   {
		        T = (((2 * v * sin(pl.angle * PI)) / g) + sqrt(pow(((2 * v * sin(pl.angle * PI)) / g), 2) - ((4 * 23 * 2) / g))) / 2;
		        x = v * cos(pl.angle * PI) * T + x0;
		        if (x > x2 + 1 && x < x2 + 15)
				{
		          y = 29;
		          y = (-1 * y + 170);
		          gotoxy(x, y);
		          printf("o");
		          sleep(0.3);
		          bump = 1;
		        } 
				else 	//the middle of tank
				{
		          T = (((2 * v * sin(pl.angle * PI)) / g) + sqrt(pow(((2 * v * sin(pl.angle * PI)) / g), 2) - ((4 * 21 * 2) / g))) / 2;
		          x = v * cos(pl.angle * PI) * T + x0;
		          y = 27;
		          y = (-1 * y + 170);
		          gotoxy(x, y);
		          printf("o");
		          sleep(0.3);
		          bump1 = 1;
	        	}
	        }
	    } 
		else if (stop != 1)
		{
		  j=20;
		  k=16;
		  e=16;
		  r=11;
		  for(i=0;i<20;i++)		//hit the mountain
		   {
		   	if(stop==0)
		   	{
		  	 j--;
		  	 k--;
		  	 e--;
		  	 r--;
			  	if(ycheck==n1[i])
			  	{
			  		if(x>=m1[i] && x<k1[j])
			  		{
				  		stop=1;
			  			if(xcheck==m1[i])
			  			{
			  				gotoxy(x, y);
		      				printf("o");
		      				sleep(0.3);
		     				printf("\b ");
		     				stop=1;
						}
						else
						{
							ykeep=y-yk;
							while(ykeep!=1 && stop!=1)
							{
								y--;
					            T = (((2 * v * sin(pl.angle * PI)) / g) + sqrt(pow(((2 * v * sin(pl.angle * PI)) / g), 2) - ((4 * (y-y0) * 2) / g))) / 2;
			                    x = v * cos(pl.angle * PI) * T + x0;
			                    xcheck=x;
			                    if(xcheck==m1[i])
			                    {
					  				gotoxy(x, y);
				      				printf("o");
				      				sleep(0.3);
				     				printf("\b ");
				     				stop=1;		                    	
								}
								ykeep--;
	                		}
											
						}
					}
				}
			  	if(ycheck==n2[i])
			  	{
			  		if(x>=m2[i] && x<k2[k])
			  		{
				  		stop=1;
			  			if(xcheck==m2[i])
			  			{
			  				gotoxy(x, y);
		      				printf("o");
		      				sleep(0.3);
		     				printf("\b ");
		     				stop=1;
						}
						else
						{
							ykeep=y-yk;
							while(ykeep!=1 && stop!=1)
							{
								y--;
					            T = (((2 * v * sin(pl.angle * PI)) / g) + sqrt(pow(((2 * v * sin(pl.angle * PI)) / g), 2) - ((4 * (y-y0) * 2) / g))) / 2;
			                    x = v * cos(pl.angle * PI) * T + x0;
			                    xcheck=x;
			                    if(xcheck==m2[i])
			                    {
					  				gotoxy(x, y);
				      				printf("o");
				      				sleep(0.3);
				     				printf("\b ");
				     				stop=1;		                    	
								}
								ykeep--;
	                		}
											
						}
					}
				}
			  	if(ycheck==n3[i])
			  	{
			  		if(x>=m3[i] && x<k3[e])
			  		{
				  		stop=1;
			  			if(xcheck==m3[i])
			  			{
			  				gotoxy(x, y);
		      				printf("o");
		      				sleep(0.3);
		     				printf("\b ");
		     				stop=1;
						}
						else
						{
							ykeep=y-yk;
							while(ykeep!=1 && stop!=1)
							{
								y--;
					            T = (((2 * v * sin(pl.angle * PI)) / g) + sqrt(pow(((2 * v * sin(pl.angle * PI)) / g), 2) - ((4 * (y-y0) * 2) / g))) / 2;
			                    x = v * cos(pl.angle * PI) * T + x0;
			                    xcheck=x;
			                    if(xcheck==m3[i])
			                    {
					  				gotoxy(x, y);
				      				printf("o");
				      				sleep(0.3);
				     				printf("\b ");
				     				stop=1;		                    	
								}
								ykeep--;
	                		}
											
						}
					}
				}		
			  	if(ycheck==n4[i])
			  	{
			  		if(x>=m4[i] && x<k4[r])
			  		{
				  		stop=1;
			  			if(xcheck==m4[i])
			  			{
			  				gotoxy(x, y);
		      				printf("o");
		      				sleep(0.3);
		     				printf("\b ");
		     				stop=1;
						}
						else
						{
							ykeep=y-yk;
							while(ykeep!=1 && stop!=1)
							{
								y--;
					            T = (((2 * v * sin(pl.angle * PI)) / g) + sqrt(pow(((2 * v * sin(pl.angle * PI)) / g), 2) - ((4 * (y-y0) * 2) / g))) / 2;
			                    x = v * cos(pl.angle * PI) * T + x0;
			                    xcheck=x;
			                    if(xcheck==m4[i])
			                    {
					  				gotoxy(x, y);
				      				printf("o");
				      				sleep(0.3);
				     				printf("\b ");
				     				stop=1;		                    	
								}
								ykeep--;
	                		}
											
						}
					}
				}							
				}							
			}
			if(stop!=1)	//when none of the tops not happening
			{	
		      gotoxy(x, y);
		      printf("o");
		      sleep(0.3);
		      printf("\b ");
		      T += .25;
		  	}
		  	yk=y;
	    }
	}
	  if (bump == 1)
	   {
			system("color 4f");
			sleep(.25);
			system("color 0f");	   	
		    temp -> score1 = 10;
		    sum1 += temp -> score1;
	    } 
	  else
	   {
		    temp -> score1 = 0;		//when ball not bump to the tank
		    sum1 += temp -> score1;
	 	}
	  if (sum1 == 50) 
	  {
	  	temp->link='\0';		//when ball bump to the tank
	    gameover = 1;
	  }
}
//********************************

int fling2(double x0, double y0, double x1, double v, struct inf pl, double t, struct score * p, struct score * temp) 	////fling for player 2
{
  double T;
  y0 = 31;
  x0 = x0;
  T = 0;
  double x;
  double y;
  int ykeep;
  double yk;
  int count = 0;
  int co = 0;
  int bump = 0;
  int bump1 = 0;
  int stop = 0;
  int ycheck;
  int xcheck;
  int flagg=0;
  int r,i,j,k,e;
  const double g = 9.8;
  const double PI = 3.14159265 / 180;	//pi
  pl.angle = 180 - pl.angle;	//angle
  t = (v * sin(pl.angle * PI) * 2) / g;
  while (bump == 0 && bump1 == 0 && stop == 0) 
   {
	    x = v * cos(pl.angle * PI) * T + x0;		//x for fling
	    y = (-1 * 0.5 * g * T * T) + v * sin(pl.angle * PI) * T + y0;	//y for fling
	    ycheck=y;
	    xcheck=x;
	    y = (-1 * y + 170);
	    if (x > 150 && y> 170 + ( -1 * 27)) //stop condition
		{
	      stop = 1;
	    }
	    if(x<0)
	    {
	    	stop=1;
		}
	    if(x>150 && y== 170 + (-1 * 28))	//stop condition
	    {
	    	stop=1;
		}
	    if (y > (170 + 7 * -1) && x < 40 && stop != 1) 	//when ball from player 2 arrive to the tank
		{
		      T = (((2 * v * sin(pl.angle * PI)) / g) + sqrt(pow(((2 * v * sin(pl.angle * PI)) / g), 2) - ((4 * (-25) * 2) / g))) / 2;
		      x = v * cos(pl.angle * PI) * T + x0;
		    if (x > x1+4 && x < x1 + 10) 
			{
		        y = 7;
		        y = (-1 * y + 170);
		        gotoxy(x, y);
		        printf("o");
		        sleep(0.1);
		        bump = 1;
		    } 
			else 
			{
		        T = (((2 * v * sin(pl.angle * PI)) / g) + sqrt(pow(((2 * v * sin(pl.angle * PI)) / g), 2) - ((4 * (-26) * 2) / g))) / 2;
		        x = v * cos(pl.angle * PI) * T + x0;
		        if (x > x1 + 1 && x < x1 + 15) 
				{
		          y = 6;
		          y = (-1 * y + 170);
		          gotoxy(x, y);
		          printf("o");
		          sleep(0.1);
		          bump = 1;
		        } 
				else 
				{
		          T = (((2 * v * sin(pl.angle * PI)) / g) + sqrt(pow(((2 * v * sin(pl.angle * PI)) / g), 2) - ((4 * (-28) * 2) / g))) / 2;
		          x = v * cos(pl.angle * PI) * T + x0;
		          y = 4;
		          y = (-1 * y + 170);
		          gotoxy(x, y);
		          printf("o");
		          sleep(0.1);
		          bump1 = 1;
		        }
	    	}
	    } 
		else if (stop == 0) 
		{
		  j=20;
		  k=16;
		  e=16;
		  r=12;
		  for(i=0;i<15;i++)	//hit to the mountain
		   {
		   	if(stop==0)
		   	{
		   		if(y>(170 + (- 24 )) && x> 50 && x < 70)
		   		{
		   			stop=1;   
				}
		   		if(y>(170 + (- 29 )) && x> 81 && x < 94)
		   		{
		   			stop=1;   
				}
		   		if(y>(170 + (- 32 )) && x> 110 && x < 120)
		   		{
		   			stop=1;   
				}
		   		if(y>(170 + (- 33 )) && x> 130 && x < 150)
		   		{
		   			stop=1;   
				}												
				}							
			}
			if(stop!=1)	//when none of up not happend
			{	
		      gotoxy(x, y);
		      printf("o");
		      sleep(0.1);
		      printf("\b ");
		      T += .25;
		  	}
		  	yk=y;
	    }
	}

	if (bump == 1) 
	{
		system("color 4f");
		sleep(.25);
		system("color 0f");
	    temp -> score2 = 10;
	    sum2 += temp -> score2;
	} 
	else 
	{
	    temp -> score2 = 0;	//when ball not bump to the tank
	    sum2 += temp -> score2;
	}
	if (sum2 == 50) 
	{
	    gameover = 1;	//when ball bump to the tank
	    temp->link='\0';
	}
}
//****************************

int scorelist(struct score * temp) 	//score list function
{
  static int x = 86;
  static int y = 23;
  int i;
  int j;
  int k = 0;
  static int h=0;
	if(temp->link!='\0')
	{
		gotoxy(85,24+h);
		printf("         %d                                       %d   ",temp->score1,temp->score2);
		temp=temp->link;
		h++;
		scorelist(temp);
	}
	else
  {
	  for (i = 1; i <= 40; i++) 
	   {
		    gotoxy(85, 22 + k);
		    for (j = 1; j <= 30; j++) {
		      if (i == 1 || i == 40 || j == 1 || j == 30) {
		
		        printf("* ");
		      }
		      if (i != 1 && j != 1 && i != 40 && j != 30) {
		        printf("  ");
		      }
		    }
		    k++;
	    }
	    gotoxy(86,23);
	    printf("      player1                                player2");
	    gotoxy(86,24+h);
	    printf("        %d                                    %d",sum1,sum2);
	}
}
//************************************
int hint() 	//hint function
{
  int i;
  int j;
  int k = 0;
  system("color 64");
  for (i = 1; i <= 30; i++) {
    gotoxy(80, 16 + k);
    for (j = 1; j <= 30; j++) {
      if (i == 1 || i == 30 || j == 1 || j == 30) {

        printf("* ");
      }
      if (i != 1 && j != 1 && i != 30 && j != 30) {
        printf("  ");
      }
    }
    // printf("\n");
    k++;
  }
  gotoxy(80 + 3, 16 + 1);
  printf("1.tank move:");
  gotoxy(80 + 3, 16 + 2);
  printf("right----------->>>:D");
  gotoxy(80 + 3, 16 + 3);
  printf("left<<<--------------:A");
  gotoxy(80 + 3, 16 + 4);
  printf("angle:");
  gotoxy(80 + 3, 16 + 5);
  printf("up^^^^^^^^^^:W");
  gotoxy(80 + 3, 16 + 6);
  printf("down;;;;;;;;;;:S");
  gotoxy(80 + 3, 16 + 7);
  printf("speed:\n");
  gotoxy(80 + 3, 16 + 8);
  printf("Press ENTER for enter the speed");
  gotoxy(80 + 3, 16 + 9);
  printf("Public informations:");
  gotoxy(80 + 3, 16 + 10);
  printf("******You are the winner if you get 60 points******");
  gotoxy(80 + 3, 16 + 12);
  printf("(:  GOOD LUCK  :)");
  gotoxy(81, 16 + 25);
  printf("    .- -.______");
  gotoxy(81, 41 + 1);
  printf(" .-='= ='==-,                      WHO WIIIINNNS???");
  gotoxy(81, 41 + 2);
  printf("(O_o_o _o_o_O) ");
  gotoxy(85, 32);
  printf("WHO WIIIINNNS???");
  gotoxy(120, 31);
  printf("_____.- -.");
  gotoxy(120, 31 + 1);
  printf(" ,-=='= ='=-. ");
  gotoxy(120, 31 + 2);
  printf(" (O_o_o_o_o_O) ");
  gotoxy(81, 36);
  printf("*********************************************************");
}
int menu()	//tarahi menu
{
char ch;
int x,y;
sleep(1);
int done=0;
system("cls");	
system("color 45");
SetColor(11);
gotoxy(90,25);	
printf("  _ __ __   ___ _ __  _  _") ;
gotoxy(90,26);
printf("|  _ ` _ \\ / _ \\ '_ \\| | | |");
gotoxy(90,27);
printf("| | | | | |  __/ | | | |_| |");
gotoxy(90,28);
printf("|_| |_| |_|\\___|_| |_|\\__,_|");
sleep(1);	
SetColor(15);
gotoxy(90,30);
printf("     _             _   ");
gotoxy(90,31);
printf(" ___| |_ __ _ _ __| |_ ");
gotoxy(90,32);
printf("/ __| __/ _` | '__| __|");
gotoxy(90,33);
printf("\\_  \\ || (_| | |  | |_"); 
gotoxy(90,34);
printf("|___/\\__\\__,_|__|  \\__|");
sleep(0.2);
gotoxy(90,36);
printf("       _                 _   ");
gotoxy(90,37); 
printf("  __ _| |__   ___  _   _| |_ ");
gotoxy(90,38);
printf(" / _` | '_ \ / _  \\| | | | __|");
gotoxy(90,39);
printf("| (_| | |_) | (_) | |_| | |_ ");
gotoxy(90,40);
printf(" \\__,_|_.__/\\____/\|__,__|\__|"); 
sleep(0.2);
gotoxy(90,42);
printf("           _ _");
gotoxy(90,43);  
printf("          (_) |"); 
gotoxy(90,44);
printf("  _____  ___| |_") ;
gotoxy(90,45);
printf(" / _ \\ \\/ / | __|");
gotoxy(90,46);
printf("|  __/>  <| | |_");
gotoxy(90,47);
printf(" \\___/_/\\_\\_|\\__|");
x=118;
y=32;
gotoxy(120,32);
while(done==0)
{
	if(kbhit())
	{
		ch=getch();
			if(ch==80)
			{
				if(y<42)
				{
					y+=5;
					gotoxy(x,y);
				}
			}
			else if(ch==72)
			{
				if(y>32)
				{
					y-=5;
					gotoxy(x,y);
				}				
			}
			if(ch==13)
			{
				done=1;
				if(y==32)
				{
					m=1;
				}
				if(y==37)
				{
					m=2;
				}
				if(y==42)
				{
					m=3;
				}
			}
		}
	}
}
//*********************************
int logo()	//tarahi logo
{
SetColor(4);
sleep(3);
gotoxy(20,4);	
printf("          _____                   _______                   _____                    _____                    _____                _____\n") ;
sleep(.025);
gotoxy(20,5);        
printf("         /\\    \\                 /::\\    \\                 /\\    \\                  /\\    \\                  /\\    \\              /\\    \\");
sleep(.025);
gotoxy(20,6);        
printf("        /::\\    \\               /::::\\    \\               /::\\    \\                /::\\____\\                /::\\    \\            /::\\    \\"); 
sleep(.025); 
gotoxy(20,7);     
printf("       /::::\\    \\             /::::::\\    \\             /::::\\    \\              /:::/    /               /::::\\    \\           \\:::\\    \\");
sleep(.025);
gotoxy(20,8);      
printf("      /::::::\\    \\           /::::::::\\    \\           /::::::\\    \\            /:::/    /               /::::::\\    \\           \\:::\\    \\"); 
sleep(.025); 
gotoxy(20,9);   
printf("     /:::/\\:::\\    \\         /:::/~~\\:::\\    \\         /:::/\\:::\\    \\          /:::/    /               /:::/\\:::\\    \\           \\:::\\    \\");  
sleep(.025);  
gotoxy(20,10); 
printf("    /:::/__\\:::\\    \\       /:::/    \\:::\\    \\       /:::/  \\:::\\    \\        /:::/____/               /:::/__\\:::\\    \\           \\:::\\    \\");  
sleep(.025);
gotoxy(20,11);  
printf("   /::::\\   \\:::\\    \\     /:::/    / \\:::\\    \\     /:::/    \\:::\\    \\      /::::\    \\               /::::\\   \\:::\\    \\          /::::\\    \\");  
sleep(.025); 
gotoxy(20,12);
printf("  /::::::\\   \\:::\\    \\   /:::/____/   \\:::\\____\\   /:::/    / \\:::\\    \\    /::::::\____\\________     /::::::\\   \\:::\\    \\        /::::::\\    \\"); 
sleep(.025);
gotoxy(20,13); 
printf(" /:::/\\:::\\   \\:::\\____\\ |:::|    |     |:::|    | /:::/    /   \\:::\\    \\  /:::/\\:::::::::::\\    \\  /:::/\\:::\\   \\:::\\    \\      /:::/\\:::\\    \\"); 
sleep(.025);
gotoxy(20,14);
printf("/:::/  \\:::\\   \\:::|    ||:::|____|     |:::|    |/:::/____/     \\:::\____\\ /:::/  |:::::::::::\\____\\/:::/__\\:::\\   \\:::\\\____\\    /:::/  \\:::\\____\\");
sleep(.025);
gotoxy(20,15);
printf("\\::/    \\:::\\  /:::|____| \\:::\\    \\   /:::/    / \\:::\\    \\      \\::/    /\\::/   |::|~~~|~~~~~     \\:::\\   \\:::\\   \\::/    /   /:::/    \\::/    /");
sleep(.025);
gotoxy(20,16);
printf(" \\/_____/\\:::\\/:::/    /   \\:::\\    \\ /:::/    /   \\:::\\    \\      \\/____/  \\/____|::|   |           \\:::\\   \\:::\\   \\/____/   /:::/    / \\/____/"); 
sleep(.025);
gotoxy(20,17);
printf("          \\::::::/    /     \\:::\\    /:::/    /     \\:::\\    \\                    |::|   |            \\:::\\   \\:::\\    \\      /:::/    /"); 
sleep(.025);
gotoxy(20,18);         
printf("           \\::::/    /       \\:::\\__/:::/    /       \\:::\\    \\                   |::|   |             \\:::\\   \\:::\\____\\    /:::/    /");
sleep(.025);  
gotoxy(20,19);        
printf("            \\::/____/         \\::::::::/    /         \\:::\\    \\                  |::|   |              \\:::\\   \\::/    /    \\::/    /");
sleep(.025);
gotoxy(20,20);           
printf("             ~~                \\::::::/    /           \\:::\\    \\                 |::|   |               \\:::\\   \\/____/      \\/____/");
sleep(.025); 
gotoxy(20,21);            
printf("                                \\::::/    /             \\:::\\    \\                |::|   |                \\:::\\    \\"); 
sleep(.025); 
gotoxy(20,22);                            
printf("                                 \\::/____/               \\:::\\____\\               \:: |   |                 \\:::\\____\\");
sleep(.025); 
gotoxy(20,23);                            
printf("                                  ~~                      \\::/    /                \\:|   |                  \\::/    /"); 
sleep(.025);
gotoxy(20,24);                            
printf("                                                           \\/____/                  \\|___|                   \\/____/");

SetColor(1);
gotoxy(35,26); 
sleep(.025);
printf("       _____                    _____                    _____                  _____\n");
sleep(.025);
gotoxy(35,27);         
printf("      /\\    \\                /::\\    \\                /:\\    \\                 /\\    \\\n"); 
sleep(.025); 
gotoxy(35,28);       
printf("     /::\\    \\              /::::\\    \\              /:::\\____\\               /::\\____\\\n");  
sleep(.025); 
gotoxy(35,29);     
printf("     \\:::\\    \\            /::::::\\    \\            /:::::|   |              /:::/    /\n"); 
sleep(.025);
gotoxy(35,30);       
printf("      \\:::\\    \\          /::::::::\\    \\          /::::::|   |             /:::/    /\n"); 
sleep(.025);
gotoxy(35,31);                  
printf("       \\:::\\    \\        /:::/__\\:::\\    \\        /:::/|::|   |            /:::/____/\n"); 
sleep(.025);
gotoxy(35,32);           
printf("       /::::\\    \\      /::::\\   \\:::\\    \\      /:::/ |::|   |           /::::\    \\\n"); 
sleep(.025);
gotoxy(35,33);           
printf("      /::::::\\    \\    /::::::\\   \\:::\\    \\    /:::/  |::|   | _____    /::::::\____\\________\n");  
sleep(.025);
gotoxy(35,34); 
printf("     /:::/\\:::\\    \\  /:::/\\:::\\   \\:::\\    \\  /:::/   |::|   |/\\    \\  /:::/\\:::::::::::\\    \\\n"); 
sleep(.025);
gotoxy(35,35); 
printf("    /:::/  \\:::\\____\\/:::/  \\:::\\   \\:::\\____\\/:: /    |::|   /::\\____\\/:::/  |:::::::::::\\____\\\n");
sleep(.025);
gotoxy(35,36); 
printf("   /:::/    \\::/    /\:::/    \\:::\\  /:::/    /\\::/    /|::|  /:::/    /\\::/   |::|~~~|~~~~~\n");
sleep(.025);
gotoxy(35,37);      
printf("  /:::/    / \\/____/  \\/____/ \\:::\\/:::/    /  \\/____/ |::| /:::/    /  \\/____|::|   |\n"); 
sleep(.025); 
gotoxy(35,38);         
printf(" /:::/    /                    \\::::::/    /           |::|/:::/    /         |::|   |\n"); 
sleep(.025);
gotoxy(35,39);          
printf("/:::/    /                      \\::::/    /            |::::::/    /          |::|   |\n"); 
sleep(.025);
gotoxy(35,40);          
printf(" \::/    /                       /:::/    /             |:::::/    /           |::|   |\n");  
sleep(.025);
gotoxy(35,41);         
printf("  \/____/                       /:::/    /              |::::/    /            |::|   |\n");
sleep(.025); 
gotoxy(35,42);          
printf("                              /:::/    /               /:::/    /             |::|   |\n");   
sleep(.025);
gotoxy(35,43);        
printf("                             /:::/    /               /:::/    /              \\::|   |\n"); 
sleep(.025); 
gotoxy(35,44);         
printf("                             \\::/    /                \\::/    /                \\:|   |\n");  
sleep(.025); 
gotoxy(35,45);        
printf("                              \\/____/                  \\/____/                  \\|___|\n"); 
sleep(.025); 
gotoxy(35,46); 	
}
//*************************
int cloud()	//tarahi clouds....
{
	SetColor(11);
	gotoxy(35,125);
	printf("                _");
	gotoxy(35,126);                                  
	printf("              (`  ).                  _    ");
	gotoxy(35,127);        
	printf("             (     ).              .:(`  )`. "); 
	gotoxy(35,128);     
	printf(")           (       '`.          :(   .    ) ");
	gotoxy(35,129);      
	printf("        .=(`(      .   )     .--  `.  (    ) )  "); 
	gotoxy(35,130);    
	printf("       ((    (..__.:'-'   .+(   )   ` _`  ) )");
	gotoxy(35,131);                  
	printf("`.     `(       ) )       (   .  )     (   )  ._ ");
	gotoxy(35,132);   
	printf("  )      ` __.:'   )     (   (   ))     `-'.-(`  ) ");
	gotoxy(35,133); 
	printf(")  )  ( )       --'       `- __.'         :(      )) ");
	gotoxy(35,134); 
	printf(".-'  (_.'          .')                    `(    )  ))");
	gotoxy(35,135); 
	printf("                  (_  )                     ` __.:'");
	gotoxy(35,136);           
	printf("                                        \n"); 
	gotoxy(35,137);
	printf("--..,___.--,--'`,---..-.--+--.,,-,,..._.--..-._.-a:f--.");	
}
//end of program
//good luck


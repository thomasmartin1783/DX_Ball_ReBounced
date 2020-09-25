# include "iGraphics.h"
# include <ctype.h>
# include <stdlib.h>
# include "stdbool.h"
# include<math.h>

#define pi 3.14159

FILE *userfile, *hs;
char name[40];
int indexNumber = 0;
int screenwidth = 1200;
int screenHight = 650;
int writing_mode;
int yAxis = 50;
int username_mode=0;
bool newgame = false;

bool highscore = false;
bool exits = false;

int a=0;
int level1 = 0;
int level2 = 0;
int countbricks1=50;

int timer = 0; 
int check_if_mega = 0;
int modenew=0, modenew2=0;
int modehighscore=0, modehighscore2=0;
int modeexit=0, modeexit2=0;
int life=3;
int hscore=0;
int mode_collaborations=0;

bool mega = false;
bool mini = false;

int red=255;
int blue=0;
int green=0;
int sc=0;
int powinterval=0;
char score[1000];
int xBall =(int)screenwidth/2;
int yBall=yAxis; 
int radiusBall=10;
int paused=0;

int v=10;
int theta=90;       
int dx=(int)v*cos(theta*pi/180);
int dy=(int)v*sin(theta*pi/180);
int mbeam=100;      
bool megabeam=false;
int mbx, mby;
int mibeam=200;   
bool minibeam=false;
int mibx, miby;
int skullpow=350;   
bool skull=false;
int skbx, skby;
int fire_pow_score=290;   
bool fireball=false;
bool firepower=false;
int fbx, fby;


struct brickstructure
{
    int x;
    int y;
    int dx;
    int dy;
    bool show;

	brickstructure():dx(100), dy(20) , show(true) {
	}


};

brickstructure bricks[50];

struct brickstructure2
{
    int x_2;
    int y_2;
    int dx2;
    int dy2;
    bool show2;

	brickstructure2():dx2(100), dy2(20) , show2(true) {
	}
};

struct brickstructure3
{
    int x_3;
    int y_3;
    int dx3;
    int dy3;
    bool show3;

	brickstructure3():dx3(100), dy3(20) , show3(true) {
	}
};

brickstructure2 bricks2[50];
brickstructure3 bricks3[50];

int xboard= xBall-50;
int yboard=yBall -20;
int dxboard =100;
int dyboard =10;

int idxboard =100;



bool isstarted = false;
int click=0;
void menu();
void ballChange();
void restartball();
void definebricks();
void definebricks2();
void changebeam();
void sound();
void timechange();
void Skull();
void FireBall();


FILE *fp = fopen("./data/Scores.txt", "a+");

char buff[1000];

void iDraw()
{
    iClear();

	
	fgets(buff, 255, (FILE*)fp);
	

    if(exits)    exit(0);
    if(level1)definebricks();
	else if(level2)definebricks2();
	if(username_mode){

        modenew=1;

	}
    if(life==0){
        iShowBMP(280, 185, "Game Over.bmp");
		iText(530,450,name,GLUT_BITMAP_TIMES_ROMAN_24);
		iText(470,400,"Your Score is ",GLUT_BITMAP_TIMES_ROMAN_24);
		iText(620,400,score,GLUT_BITMAP_TIMES_ROMAN_24);
		iText(500,200,"Press q to Quit" ,GLUT_BITMAP_TIMES_ROMAN_24);

		if(sc > 0) {
			fprintf(fp, "%s__%d___",name,sc);
			fclose(fp);
		}
		
		iPauseTimer(1);
    }
    else{
        if(!username_mode && !highscore && !exits)
        {
			
            iShowBMP(0, 0, "bluebackground.bmp");
            iShowBMP(420, 425, "DXBall2Logo.bmp");
        }

        iSetColor(255, 255, 255);

		iText(430,80 , "Press SPACE to start the game", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(430,50 , "Press q or END to quit anytime", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(430,20 , "Press p to pause & r to resume", GLUT_BITMAP_TIMES_ROMAN_24);

        iRectangle(520, 335, 170, 50);
        iText(540, 350, "NEW GAME",  GLUT_BITMAP_TIMES_ROMAN_24);
        iRectangle(470, 265, 270, 50);
        iText(490, 280, "COLLABORATIONS",  GLUT_BITMAP_TIMES_ROMAN_24);
        iRectangle(520, 195, 170, 50);
        iText(533, 210, "HIGH SCORE",  GLUT_BITMAP_TIMES_ROMAN_24);
        iRectangle(520, 125, 170, 50);
        iText(580, 140, "EXIT",  GLUT_BITMAP_TIMES_ROMAN_24);

        if(modenew)
        {
            iClear();
        iSetColor(255,255,255);
		iText(430,520 , "Press SPACE to start the game", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(250,480 , "Press LEFT ARROW or RIGHT ARROW to move the board", GLUT_BITMAP_TIMES_ROMAN_24);
        iText(450,400,"ENTER USERNAME:",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(30,30,"***click inside the box before writing your name***",GLUT_BITMAP_HELVETICA_18);
        iRectangle(450,350,250,40);

        if(writing_mode){
                iText(460,370,name,GLUT_BITMAP_TIMES_ROMAN_24);
                //printf("%s\n",name);
		     }
        }
        else if(modehighscore)
        {
			iClear();
            iSetColor(255,250,240);
            iText(10, 400, buff,  GLUT_BITMAP_TIMES_ROMAN_24);
			iText(10, 10, "Double Click to go back to the main menu" ,  GLUT_BITMAP_TIMES_ROMAN_24);
        }
        else if(modeexit)
        {
            iSetColor(178, 190, 181);
            iFilledRectangle(520, 125, 170, 50);
            iSetColor(255,250,240);
            iText(580, 140, "EXIT",  GLUT_BITMAP_TIMES_ROMAN_24);
			
		
			}else if(mode_collaborations) {
			iClear();
			iSetColor(255, 190, 181);
			iText(10, 580, "==>",  GLUT_BITMAP_TIMES_ROMAN_24);

			iSetColor(255, 255, 235);
			iText(10, 545, "",  GLUT_BITMAP_HELVETICA_18);
			iText(10, 518, "",  GLUT_BITMAP_HELVETICA_18);
			iText(10, 498, "",  GLUT_BITMAP_HELVETICA_18);
			iText(10, 469, "",  GLUT_BITMAP_HELVETICA_18);

			iSetColor(255, 190, 181);
			iText(10, 418, "==> Nibir 054",  GLUT_BITMAP_TIMES_ROMAN_24);

			iSetColor(255, 255, 255);
			iText(10, 387, "OverAll Game Logic Generator",  GLUT_BITMAP_HELVETICA_18);
			iText(10, 376, "Special Features Constructor",  GLUT_BITMAP_HELVETICA_18);
			iText(10, 350, "Level Integration Full Assistance",  GLUT_BITMAP_HELVETICA_18);
			iText(10, 330, "Bug Fixing",  GLUT_BITMAP_HELVETICA_18);
			
			iSetColor(255, 190, 181);
			iText(10, 260, "==>",  GLUT_BITMAP_TIMES_ROMAN_24);
			iSetColor(255, 255, 255);
			iText(10, 230, "",  GLUT_BITMAP_HELVETICA_18);
			iText(10, 208, "",  GLUT_BITMAP_HELVETICA_18);
			iText(10, 188, "",  GLUT_BITMAP_HELVETICA_18);
			
				
			iSetColor(255, 190, 181);
			iText(10, 130, "==>",  GLUT_BITMAP_TIMES_ROMAN_24);
			iSetColor(255, 255, 255);
			iText(10, 96, "",  GLUT_BITMAP_HELVETICA_18);
			iText(10, 88, "",  GLUT_BITMAP_HELVETICA_18);
			iText(10, 49, "",  GLUT_BITMAP_HELVETICA_18);
		}
        
        if(newgame){
            if(a==0) level1 = 1;
        }

        if(level1==1 || level2==1){
            iSetColor(255,0,0);
            iFilledRectangle(540, 610, 110, 3);
            if(level1)  iText(550, 620, "LEVEL 1", GLUT_BITMAP_TIMES_ROMAN_24);
            if(level1)  iShowBMP(0, 0, "Blues2.bmp"); 
            if(level2)  iText(550, 620, "LEVEL 2", GLUT_BITMAP_TIMES_ROMAN_24);
            
			if(level2)  iShowBMP(0, 0, "bluebackground.bmp");

            iSetColor(255,255,255);
            iText(5, 630, "SCORE",  GLUT_BITMAP_HELVETICA_12);
            iText(60, 630, score);
            iSetColor(124,252,0);
            if(life==3)  iText(1000, 600, "LIFE X 3", GLUT_BITMAP_TIMES_ROMAN_24);
            if(life==2)  iText(1000, 600, "LIFE X 2", GLUT_BITMAP_TIMES_ROMAN_24);
            if(life==1)  iText(1000, 600, "LIFE X 1", GLUT_BITMAP_TIMES_ROMAN_24);
            iSetColor(255,255,255);
            if(paused)
            {
                iShowBMP(470, 270, "Paused.bmp");
                

            }
            iSetColor(200,200,200);
            if(!fireball)iFilledCircle(xBall,yBall,radiusBall,1000);
            else
            {
                iSetColor(255,69,0);
                iFilledCircle(xBall,yBall,radiusBall,1000);
            }
            iSetColor(115,206,250);
            
            if(!mega && !mini)iShowBMP(xboard, yboard-4, "Paddle2.bmp");          ///100 x 15  and  200 x 15
            else if(mini && !mega)   iShowBMP(xboard, yboard-4, "Paddle3.bmp");
            else if(mega && !mini)   iShowBMP(xboard, yboard-4, "Paddle.bmp");


            if(minibeam)
            {
                  iShowBMP(mibx, miby, "minibeam_powerup.bmp");
                
            }
            if(megabeam)
            {
                  iShowBMP(mbx, mby, "megabeam_powerup.bmp");

            }
            if(skullpow)
            {
                iShowBMP(skbx, skby, "skull.bmp");
            }
            if(firepower)
            {
                iShowBMP(fbx, fby, "Fire Ball.bmp");
            }
            int i;
            if(level1)
            for(i=0;i<50;i++)
            {
                if(bricks[i].show)
                {
                    iSetColor(255, 255, 255);
       
                    iShowBMP(bricks[i].x, bricks[i].y, "Bricks2.bmp");
                }
            }
            int j;
           
            if(level2){
           
            for(j=1;j<50;j++)
            {
                if(bricks2[j].show2)
                {

                    iSetColor(255, 255, 255);
             
                    if(j%10==0 || j%10==8 || j<10 || j>40)iShowBMP(bricks2[j].x_2, bricks2[j].y_2, "blue-brick-wall-texture.bmp");
                    else                  iShowBMP(bricks2[j].x_2, bricks2[j].y_2, "fire-bricks.bmp");
                }
            }
        }

            changebeam();

        }
    }




}

void ballChange()
{
   if(isstarted){
     xBall += dx;
     yBall += dy;
     if(xBall>=screenwidth-10||xBall<=10)
        dx = -dx;
     if(yBall>=screenHight-10||yBall<=10)
        dy = -dy;

     int i;
     if(level1)
     for(i=0;i<50;i++)
     {
         if(bricks[i].show)
         {
             if(xBall>bricks[i].x && xBall<=bricks[i].x+bricks[i].dx)
             {
                if(yBall>=bricks[i].y-10 && yBall<=bricks[i].y+bricks[i].dy)
                {
                 PlaySound(TEXT("collide.wav"), NULL, SND_LOOP|SND_ASYNC);
                 countbricks1--;
                 if(countbricks1==0)    {level1=0; a=1; level2=1; restartball();}
                 if(!fireball)dy= -dy;
                 bricks[i].show=false;
                 sc+=10;
                 itoa(sc, score, 10);
                 if(sc==mbeam)
                 {
                     megabeam=true;
                     mbeam+=410;
                     mbx=bricks[i].x;
                     mby=bricks[i].y;
                 }
                 if(sc==mibeam)
                 {
                     minibeam=true;
                     mibeam+=200;
                     mibx=bricks[i].x;
                     miby=bricks[i].y;
                 }
                 if(sc==skullpow)
                 {
                     skull=true;
                     skullpow+=200;
                     skbx=bricks[i].x;
                     skby=bricks[i].y;
                 }
                 if(sc==fire_pow_score)
                 {
                     firepower=true;
                     fire_pow_score+=200;
                     fbx=bricks[i].x;
                     fby=bricks[i].y;
                 }
                }

             }
             else if(yBall>=bricks[i].y-10 && yBall<=bricks[i].y+bricks[i].dy+10)
             {
                 if(xBall>bricks[i].x-10 && xBall<=bricks[i].x+bricks[i].dx+10)
                {
                 PlaySound(TEXT("collide.wav"), NULL, SND_LOOP|SND_ASYNC);
                 countbricks1--;
                 if(countbricks1==0)    {level1=0; a=1; level2=1;  restartball();}
                 if(!fireball)dx = -dx;
                 bricks[i].show=false;
                 sc+=10;
                 itoa(sc, score, 10);
                 if(sc==mbeam)
                 {
                     megabeam=true;
                     mbeam+=410;
                     mbx=bricks[i].x;
                     mby=bricks[i].y;
                 }
                 if(sc==mibeam)
                 {
                     minibeam=true;
                     mibeam+=200;
                     mibx=bricks[i].x;
                     miby=bricks[i].y;
                 }
                 if(sc==skullpow)
                 {
                     skull=true;
                     skullpow+=200;
                     skbx=bricks[i].x;
                     skby=bricks[i].y;
                 }
                 if(sc==fire_pow_score)
                 {
                     firepower=true;
                     fire_pow_score+=200;
                     fbx=bricks[i].x;
                     fby=bricks[i].y;
                 }
                }
             }
         }
     }

     if(level2)
     for(i=0;i<50;i++)
     {
         if(bricks2[i].show2)
         {
             if(xBall>bricks2[i].x_2 && xBall<=bricks2[i].x_2+bricks2[i].dx2)
             {
                if(yBall>=bricks2[i].y_2-10 && yBall<=bricks2[i].y_2+bricks2[i].dy2)
                {
                 PlaySound(TEXT("collide"), NULL, SND_ASYNC);
                 if(!fireball)dy= -dy;

                 bricks2[i].show2=false;
                 sc+=10;
                 itoa(sc, score, 10);
                 if(sc==mbeam)
                 {
                     megabeam=true;
                     mbeam+=400;
                     mbx=bricks2[i].x_2;
                     mby=bricks2[i].y_2;
                 }
                 if(sc==mibeam)
                 {
                     minibeam=true;
                     mibeam+=200;
                     mibx=bricks2[i].x_2;
                     miby=bricks2[i].y_2;
                 }
                 if(sc==skullpow)
                 {
                     skull=true;
                     skbx=bricks[i].x;
                     skby=bricks[i].y;
                 }
                 if(sc==fire_pow_score)
                 {
                     firepower=true;
                     fire_pow_score+=200;
                     fbx=bricks[i].x;
                     fby=bricks[i].y;
                 }
                }

             }
             else if(yBall>=bricks2[i].y_2-10 && yBall<=bricks2[i].y_2+bricks2[i].dy2+10)
             {
                 if(xBall>bricks2[i].x_2-10 && xBall<=bricks2[i].x_2+bricks2[i].dx2+10)
                {
                 PlaySound(TEXT("collide"), NULL, SND_SYNC);
                 if(!fireball)dx = -dx;     
                 bricks2[i].show2=false;
                 sc+=10;
                 itoa(sc, score, 10);
                 if(sc==mbeam)
                 {
                     megabeam=true;
                     mbeam+=400;
                     mbx=bricks2[i].x_2;
                     mby=bricks2[i].y_2;
                 }
                 if(sc==mibeam)
                 {
                     minibeam=true;
                     mibeam+=200;
                     mibx=bricks2[i].x_2;
                     miby=bricks2[i].y_2;

                 }
                 if(sc==skullpow)
                 {
                     skull=true;
                     skbx=bricks[i].x;
                     skby=bricks[i].y;
                 }
                 if(sc==fire_pow_score)
                 {
                     firepower=true;
                     fire_pow_score+=200;
                     fbx=bricks[i].x;
                     fby=bricks[i].y;
                 }
                }
             }
         }
     }

    if(!mega && !mini){
         if(xBall>=xboard-10 && xBall<=xboard+dxboard+10 && yBall>=yboard+10 && yBall<=yboard+dyboard+10)
        {
            theta=(xboard+dxboard-xBall)+40;
            dx=(int)v*cos(theta*pi/180);
            dy=(int)v*sin(theta*pi/180);

        }
         else
         {
             if(yBall<yboard-15)
             {
                 restartball();
                 life--;
             }
         }
    }
    else if(mega){
        if(xBall>=xboard-10 && xBall<=xboard+200+10 && yBall>=yboard+10 && yBall<=yboard+dyboard+10)
         {
            if(!(xBall>=xboard-10+40 && xBall<=xboard+160+10))
                {
                    theta=-(xboard+200-xBall)+10;
                    //printf("xboarddd=%d\n", xboard+200); printf("xBall=%d\n",xBall);   printf("theta=%d\n", theta);
                }
            else    theta=(xboard+200-xBall-50)+40;
            dx=(int)v*cos(theta*pi/180);
            dy=(int)v*sin(theta*pi/180);

         }
         else
         {
             if(yBall<yboard-14)
             {
                 restartball();
                 life--;
             }
         }
    }
    else if(mini)
    {
        if(xBall>=xboard-10 && xBall<=xboard+50+10 && yBall>=yboard+10 && yBall<=yboard+dyboard+10)
         {
            theta=(xboard+50-xBall)+65;
            dx=(int)v*cos(theta*pi/180);
            dy=(int)v*sin(theta*pi/180);

         }
         else
         {
             if(yBall<yboard-14)
             {
                 restartball();
                 life--;
             }
         }
    }

   }

}


void iMouseMove(int mx, int my)
{

}


void iMouse(int button, int state, int mx, int my)
{

	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
        if(modenew==0 && mx >= 520 && mx <= 690 && my >= 350 && my <= 400) {
            username_mode=1;}  

        
        if(mx >= 520 && mx <= 690 && my >= 210 && my <= 260)  modehighscore = 1;
            else    modehighscore = 0;
        if(modehighscore)   highscore = true;
        if(mx >= 520 && mx <= 690 && my >= 140 && my <= 190)  modeexit = 1;
            else    modeexit = 0;
        if(modeexit)        exits = true;
        if(username_mode==1 && mx>=450 && mx<=700 && my>=350 && my<=390){
                writing_mode=1;
        }
		
		if(mx>=470 && mx<=740 && my>=265 && my<=315 ) {
			mode_collaborations = 1;
		}
		
	}
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{

	}
}


void iKeyboard(unsigned char key)
{
    if(key == 'f'){
        dx = 0;
        dy = 20;
    }
    if(key == 's'){
        dx = 0;
        dy = -10;
    }
	if(key == 'p')
	{
		iPauseTimer(1);
		paused = 1;
	}
	if(key == 'r')
	{
		iResumeTimer(1);
		paused = 0;
	}
    if(key == '\r')
    {
        if(modenew)         newgame = true;
        if(modehighscore)   highscore = true;
        if(modeexit)        exits = true;
    }
    if(key == ' ')
    {
        if(newgame && !isstarted){
            if(life>0) isstarted= true;
        }
    }

	if(key == 'q')
	{
		
		if(sc > 0) {
			fprintf(fp, "%s__%d___",name,sc);
			fclose(fp);
		}

		exit(0);
	}


	if(key != '\b' && writing_mode) 
	{
		name[indexNumber] = key;
		indexNumber++; 
		name[indexNumber] = '\0';
		
	}else {
		if(indexNumber <= 0 )
			indexNumber = 0;
		else
			indexNumber--;

		name[indexNumber] = '\0';
		
	}

}

/*
	function iSpecialKeyboard() is called whenever user hits special keys like-
	function keys, home, end, pg up, pg down, arrows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{

    if(key == GLUT_KEY_END)
	{
		exit(0);
	}

	if(life>0 ){                                     
        if(key == GLUT_KEY_LEFT){
            if(xboard>0){
                xboard -= 15;
                if(!isstarted)
                    xBall -=15;
            }
            if(xboard<=0)
                xboard = 0;
        }
        if(key == GLUT_KEY_RIGHT){

            if(xboard<screenwidth-dxboard){
                xboard += 15;
                if(!isstarted)
                    xBall +=15;
            }
            if(!mega && !mini){
                if(xboard >= screenwidth-100)
                    xboard = screenwidth-100;
            }
            else if(mega)
            {
                if(xboard >= screenwidth-200)
                    xboard = screenwidth-200;
            }
            else if(mini)
            {
                if(xboard >= screenwidth-50)
                    xboard = screenwidth-50;
            }
        }
	}


}

void restartball()
{
       xBall = (int)screenwidth/2;
       yBall = yAxis;

       dx=0;
       dy=10;

       xboard= xBall-50;
       yboard=yBall -20;

       isstarted = false;
       megabeam = false;
       minibeam = false;
       mega = false;
       mini = false;
       fireball = false;
       dxboard = idxboard;
}

void megaBeam()
{
    mby-=10;
}

void miniBeam()
{
    miby-=10;
}

void Skull()
{
    skby-=10;
}
void FireBall()
{
    fby-=10;
}

void definebricks()
{

    int i;
    int sumx=100;
    int sumy=450;

    for(i=0;i<50;i++)
    {

        bricks[i].x=sumx;
        bricks[i].y=sumy;

        sumx+=100;
        if(sumx>1000){
            sumx=100;
            sumy+=20;
        }
    }

}

void definebricks2()
{


    int i;
    int sumx2=200;
    int sumy2=350;


    for(i=1;i<8;i+=2)
    {
        
        bricks2[i].x_2=sumx2;
        bricks2[i].y_2=sumy2;
        sumx2+=200;
        bricks2[i].dx2=100;
        bricks2[i].dy2=20;

    }
    sumy2+=20;
    sumx2 = 100;
    for(i=10; i<40; i++)
    {
        if(i%10==0) sumy2 += 20;
        if((i%10)==0 || (i%10)==6)
        {
            
            bricks2[i].x_2=sumx2;
            bricks2[i].y_2=sumy2;
            bricks2[i].dx2=100;
            bricks2[i].dy2=20;
            sumx2+=200;
            i++;
            if(sumx2>1000)  sumx2 = 100;
        }
        else
        {
            if(i%10==9)
            {
                sumx2+=100;
                if(sumx2>1000)  sumx2 = 100;
                continue;
            }
            
            bricks2[i].x_2=sumx2;
            bricks2[i].y_2=sumy2;
            bricks2[i].dx2=100;
            bricks2[i].dy2=20;
            sumx2+=100;
            if(sumx2>1000)  sumx2 = 100;
        }

    }

    sumy2 += 40;
    sumx2 = 200;
    for(i=41; i<48; i+=2)
    {
        
        bricks2[i].x_2=sumx2;
        bricks2[i].y_2=sumy2;
        bricks2[i].dx2=100;
        bricks2[i].dy2=20;
        sumx2+=200;
        if(sumx2>1000){
            break;
        }


    }
}


void changebeam()
{
    if(mbx>xboard-40 && mbx<xboard+dxboard && mby==yboard+dyboard)
        {
                
                xboard-=20;
                mega = true;  
                mini = false;

        }

    else if(mby<yboard)
        {
            megabeam=false;
        }

    if(!mega){
        if(mibx>xboard-40 && mibx<xboard+dxboard && miby==yboard+dyboard)
        
        {

                
                xboard+=15;
                mini = true;  
                mega = false;
                skull = false;
        }
        else if(miby<yboard)
        {
            minibeam=false;
        }
        if(skbx>xboard-40 && skbx<xboard+dxboard && skby==yboard+dyboard)
        {
            mini = false;  
            mega = false;
            skull = true;
            if(skull){life--; restartball();}
        }
        else if(skby<yboard)
        {
            skull=false;
        }
        if(fbx>xboard-40 && fbx<xboard+dxboard && fby==yboard+dyboard)
        {
            skull = false;
            fireball = true;
        }
        else if(fby<yboard)
        {
            firepower=false;
        }
    }
    else{
        if(mibx>xboard-40 && mibx<xboard+200 && miby==yboard+dyboard)
        
        {

                
                xboard+=15;
                mini = true;  
                mega = false;
                skull = false;
        }
        else if(miby<yboard)
        {
            minibeam=false;
        }
        if(skbx>xboard-40 && skbx<xboard+200 && skby==yboard+dyboard)
        {
            mini = false;  
            mega = false;
            skull = true;
            if(skull){life--; restartball();}
        }
        else if(skby<yboard)
        {
            skull=false;
        }
        if(fbx>xboard-40 && fbx<xboard+200 && fby==yboard+dyboard)
        {
            skull = false;
            fireball = true;
        }
        else if(fby<yboard)
        {
            firepower=false;
        }
    }

}

void timechange()
{
    timer++;
}



int main()
{

	FILE *fp = fopen("Scores.txt", "w");


	definebricks();
	definebricks2();

	iSetTimer(1000, timechange);
	iSetTimer(20, ballChange);
	iSetTimer(20, megaBeam);
	iSetTimer(20, miniBeam);
	iSetTimer(20, Skull);
	iSetTimer(20, FireBall);
    PlaySound(TEXT("sound"), NULL, SND_ASYNC);
	itoa(sc, score, 10);
    iInitialize(screenwidth,screenHight, "DX Ball 2");

	
	

	

	return 0;
}


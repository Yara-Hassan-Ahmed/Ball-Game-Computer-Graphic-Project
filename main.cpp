#include<windows.h>
#include <GL/glut.h>
#include<bits/stdc++.h>
#include <stdlib.h>
#define rad (3.1416/180)
#define EN_SIZE 20
#include<mmsystem.h>

using namespace std;
static int slices = 16;
static int stacks = 16;
int score=0;
float tX=0,tY=0,tZ=-8;
bool Over = false;
bool START = false;
float tZ1=-20,tZ2=-40,tZ3=-60,tZ4=-80,tZ5=-100,tZ6=-120;
float torusPosX[7] = {1,-2,3,-4,-2,0,2};
float torusPosY[7] = {2,3,10,6,7,4,1};
int tola[5000][5000];
int TIME=0;
float rotX=0,rotY=0,rotZ=0;
float speed = 0.3;
float angleBackFrac = 0.2;
void *currentfont;
float zoom=4;
bool light0 = true;
bool no_ambient = false;
bool no_diffuse = false;
bool no_specular = false;
bool emmission_on = true;
int anglex= 0, angley = 0, anglez = 0;          ///rotation angles
bool normalLight=false;
bool rot = false;
int xo=0,yo=0,zo=0;
float ze=5;

static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 1000.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
///=================///
///*** All_Model ***///
///=================///

/// *** Field Model **///
void drawField(){

    ///Ground field
    glColor3d(0.4,0.2,0.2);
	glPushMatrix();
        glTranslated(0,1.55,0);
        glScaled(2,0.05,1.5);
        glutSolidCube(1);
    glPopMatrix();

    glColor3d(0.4,0.2,0.2);
	glPushMatrix();
        glTranslated(0,1.6,0);
        glScaled(1.9,0.05,1.4);
        glutSolidCube(1);
    glPopMatrix();

    glColor3d(0.4,0.2,0.2);
	glPushMatrix();
        glTranslated(0,1.65,0);
        glScaled(1.8,0.05,1.3);
        glutSolidCube(1);
    glPopMatrix();

    /// Circle
    glColor3d(1,0,0);
    glPushMatrix();
        glTranslated(0,2.1,-0.44);
        glScaled(0.35,0.35,0.01);
        glutSolidSphere(1,50,50);
    glPopMatrix();

    glColor3d(0,0,0);
    glPushMatrix();
        glTranslated(-0.18,1.9,-0.45);
        glScaled(0.01,0.5,0.01);
        glutSolidCube(1);
    glPopMatrix();

    glColor3d(0,0,0);
    glPushMatrix();
        glTranslated(0.18,1.9,-0.45);
        glScaled(0.01,0.5,0.01);
        glutSolidCube(1);
    glPopMatrix();

}
/// *** Filed display Model **///
void fieldDisplay(){
///Left field
    glPushMatrix();
        glTranslated(-8,-2.7,-5);
        glRotated(65,0,1,0);
        glScaled(2,2,2);
        drawField();
    glPopMatrix();
///Right field
    glPushMatrix();
        glTranslated(8,-2.7,-5);
        glRotated(-65,0,1,0);
        glScaled(2,2,2);
        drawField();
    glPopMatrix();
}

/// *** Ball Model **///
void Ball()
{
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    double a = t*90.0;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,5);
    glColor3d(1.5,0.5,0.5);

    glPushMatrix();
    GLUquadric *qob=gluNewQuadric();
    gluQuadricTexture(qob,GL_TRUE);
    glRotatef(a,0,0,1);
    glScaled(0.70,0.7,0.7);
    gluSphere(qob,1,30,30);
    gluDeleteQuadric(qob);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

/// *** Houses Model **///
void drawHouses(int R,int G,int B){
    ///Houses
    glColor3d(1, 1, 0.5);
    glPushMatrix();
        glTranslated(0,0,0);
        glutSolidCube(1);
    glPopMatrix();
    ///Window 1
    glColor3d(0.38, 0.21, 0.26);
    glPushMatrix();
        glTranslated(0.2,0,0);
        glScaled(0.3,0.3,1.001);
        glutSolidCube(1);
    glPopMatrix();
    ///Window 2
    glColor3d(0.38, 0.21, 0.26);
    glPushMatrix();
        glTranslated(-0.2,0,0);
        glScaled(0.3,0.3,1.001);
        glutSolidCube(1);
    glPopMatrix();
    ///Window 3
    glColor3d(0.38, 0.41, 0.36);
    glPushMatrix();
        glTranslated(0,0,0.2);
        glScaled(1.001,0.3,0.3);
        glutSolidCube(1);
    glPopMatrix();
    ///Window 4
    glColor3d(0.38, 0.41, 0.36);
    glPushMatrix();
        glTranslated(0,0,-0.2);
        glScaled(1.001,0.3,0.3);
        glutSolidCube(1);
    glPopMatrix();

}
/// *** Creation of many houses Model **///
void house(int n,int R,int G){
    for(int i=0;i<n;i++){
        glPushMatrix();
            glTranslated(0,1+i,0);
            drawHouses(G,R,i);
        glPopMatrix();
    }
}
/// *** Baby Doll Model **///
void BabyDoll()
{
    glPushMatrix();
    ///cloth
    glPushMatrix();
    glTranslated(0,-1.6,-6);
    glRotatef(-90,0.1,0,0);
    glColor3d(1, 0.37, 0);
    glScaled(1.5,1.7,2);
    glutSolidCone(1,1,slices,stacks);
    glPopMatrix();
    ///face
    glPushMatrix();
    glTranslated(0,.8,-5.8);
    glRotated(90,1,0,0);
    glScaled(1.5,1.5,1.5);
    glColor3ub(244, 224, 190);
    glutSolidSphere(1,slices,stacks);
    glPopMatrix();
    ///left leg
    glPushMatrix();
    glTranslated(-.74,-2.2,-6);
    glRotated(90,1,0,0);
    glScaled(.9,.9,.9);
    glColor3ub(128, 128, 128);
    glutSolidSphere(1,slices,stacks);
    glPopMatrix();
    ///left leg shoe
    glPushMatrix();
    glTranslated(-.74,-2.8,-6.1);
    glRotated(-90,0.1,0,0);
    glColor3ub(0,0,0);
    glScaled(.95,1,1);
    glutSolidCone(1,2,slices,stacks);
    glPopMatrix();
    ///right leg
    glPushMatrix();
    glTranslated(.74,-2.2,-6);
    glRotated(90,1,0,0);
    glScaled(.9,.9,.9);
    glColor3ub(128, 128, 128);
    glutSolidSphere(1,slices,stacks);
    glPopMatrix();
    ///right leg shoe
    glPushMatrix();
    glTranslated(.74,-2.8,-6.1);
    glRotated(-90,0.1,0,0);
    glColor3ub(0,0,0);
    glScaled(.95,1,1);
    glutSolidCone(1,2,slices,stacks);
    glPopMatrix();
    ///right hand
    glPushMatrix();
    glTranslated(1,-.55,-6);
    glRotated(60,0,1,0);
    glScaled(1.3,.2,.5);
    glutSolidSphere(1,slices,stacks);
    glPopMatrix();
    ///left hand
    glPushMatrix();
    glTranslated(-1,-.55,-6);
    glRotated(-60,0,1,0);
    glScaled(1.3,.2,.5);
    glutSolidSphere(1,slices,stacks);
    glPopMatrix();
    ///mouse
    glPushMatrix();
    glTranslated(0,.3,-4.5);
    glRotated(180,0,.5,-1);
    glScaled(.2,-.2,.2);
    glutSolidCone(1,2,slices,stacks);
    glPopMatrix();
    ///right black eye
    glPushMatrix();
    glTranslated(.32,.73,-4);
    glRotated(90,1,0,0);
    glScaled(.1,.1,.1);
    glColor3f(0,0,0);
    glutSolidSphere(1,slices,stacks);
    glPopMatrix();
    ///right white eye
    glPushMatrix();
    glTranslated(.35,.8,-4.3);
    glRotated(90,0,1,0);
    glScaled(.2,.3,.2);
    glColor3f(1,1,1);
    glutSolidSphere(1,slices,stacks);
    glPopMatrix();
    ///left black eye
    glPushMatrix();
    glTranslated(-.32,.73,-4);
    glRotated(90,1,0,0);
    glScaled(.1,.1,.1);
    glColor3f(0,0,0);
    glutSolidSphere(1,slices,stacks);
    glPopMatrix();
    ///left white eye
    glPushMatrix();
    glTranslated(-.35,.8,-4.3);
    glRotated(90,0,1,0);
    glScaled(.2,.3,.2);
    glColor3f(1,1,1);
    glutSolidSphere(1,slices,stacks);
    glPopMatrix();
    ///left eyebrow
    glPushMatrix();
    glTranslated(-.4,1.3,-4.3);
    glRotated(120,1,0,1);
    glScaled(.05,.2,.2);
    glColor3f(0,0,0);
    glutSolidCone(1,2,slices,stacks);
    glPopMatrix();
    ///right eyebrow
    glPushMatrix();
    glTranslated(.35,1.3,-4.3);
    glRotated(120,1,0,1);
    glScaled(.05,.2,.2);
    glColor3f(0,0,0);
    glutSolidCone(1,2,slices,stacks);
    glPopMatrix();
    glPopMatrix();

}
/// *** Stand Of Windmill Model **///
void quad(float a,float b,float c)
{
    glBegin(GL_QUADS);

    ///outer stand
    glColor3d(a+.3,b+.3,c+.3);
    glVertex3f(0,0,2);
    glVertex3f(2,0,2);
    glVertex3f(2,2,2);
    glVertex3f(0,2,2);
    ///inner stand
    glColor3d(a+.2,b+5,c+5);
    glVertex3f(2,0,2);
    glVertex3f(2,0,0);
    glVertex3f(2,2,0);
    glVertex3f(2,2,2);

    glEnd();
}
/// *** Windmill Model **///
void windMill()
{
    glPushMatrix();
    glTranslated(-4,-2,-5);
    glRotated(xo,0,1,0);
    glRotated(yo,1,0,0);
    glRotated(zo,0,0,1);
    glScaled(3,3,3);
    ///back stand
    glPushMatrix();
    glTranslated(-1,-2,-6+ze);
    glRotated(10,1,0,0);
    glScaled(.05,2.7,.05);
    quad(.5,.3,.1);
    glPopMatrix();
    ///front stand
    glPushMatrix();
    glTranslated(-1,-2,-4+ze);
    glRotated(-10,1,0,0);
    glScaled(.05,2.7,.05);
    quad(.5,.3,.1);
    glPopMatrix();
    ///right stand
    glPushMatrix();
    glTranslated(0,-2,-5+ze);
    glRotated(10,0,0,1);
    glScaled(.05,2.7,.05);
    quad(.5,.3,.1);
    glPopMatrix();
    ///left stand
    glPushMatrix();
    glTranslated(-2,-2,-5+ze);
    glRotated(-10,0,0,1);
    glScaled(.05,2.7,.05);
    quad(.5,.3,.1);
    glPopMatrix();
    ///upper corps
    glPushMatrix();
    glTranslated(-1.1,3.3,-5.1+ze);
    glScaled(.15,.25,.15);
    quad(.5,.3,.1);
    glPopMatrix();
    ///blade 1
    glPushMatrix();
    glTranslated(-1,3.6,-4.75+ze);
    glRotated(-40,0,0,1);
    glScaled(.1,.8,.03);
    quad(.6,.0,.0);
    glPopMatrix();
    ///blade 2
    glPushMatrix();
    glTranslated(-1.1,3.5,-4.75+ze);
    glRotated(80,0,0,1);
    glScaled(.1,.8,.03);
    quad(.1,.1,.1);
    glPopMatrix();
    ///blade 3
    glPushMatrix();
    glTranslated(-.8,3.5,-4.75+ze);
    glRotated(200,0,0,1);
    glScaled(.1,.8,.03);
    quad(.0,.6,.6);
    glPopMatrix();

    glPopMatrix();
}
/// *** Score Calculation **///
void Find_Score()
{
    float ballPosX = -tX;
    float ballPosY = -tY;

    if(tZ>-8.2 && tZ<-7.8)
    {
        if((ballPosX>1.5 && ballPosX<4.5) && (ballPosY>8.5 && ballPosY<11.5) )
        {
            score++;
        }
    }
    else if(tZ2>-8.2 && tZ2<-7.8)
    {
        if((ballPosX>-5.5 && ballPosX<-2.5) && (ballPosY>4.5 && ballPosY<7.5) )
        {
            score++;;
        }
    }
    else if(tZ3>-8.2 && tZ3<-7.8)
    {
        if((ballPosX>-3.5 && ballPosX<-0.5) && (ballPosY>1.5 && ballPosY<4.5) )
        {
            score++;
        }
    }
    else if(tZ4>-8.2 && tZ4<-7.8)
    {
        if((ballPosX>-1.5 && ballPosX<1.5) && (ballPosY>2.5 && ballPosY<5.5) )
        {
            score++;
        }
    }
    else if(tZ5>-8.2 && tZ5<-7.8)
    {
        if((ballPosX>0.5 && ballPosX<3.5) && (ballPosY>-0.5 && ballPosY<2.5) )
        {
            score++;
        }
    }
    else if(tZ6>-8.2 && tZ6<-7.8)
    {
        if((ballPosX>-5.5 && ballPosX<-2.5) && (ballPosY>2.5 && ballPosY<5.5) )
        {
            score++;
        }
    }
    if(tZ>10 && tZ<10.5)
    {
        if((ballPosX>1.5 && ballPosX<4.5) && (ballPosY>8.5 && ballPosY<11.5) )
        {
            Over=true;
            START=false;
        }
    }
    else if(tZ2>10 && tZ2<10.5)
    {
        if((ballPosX>-5.5 && ballPosX<-2.5) && (ballPosY>4.5 && ballPosY<7.5) )
        {
            Over=true;
            START=false;
        }
    }
    else if(tZ3>10 && tZ3<10.5)
    {
        if((ballPosX>-3.5 && ballPosX<-0.5) && (ballPosY>1.5 && ballPosY<4.5) )
        {
            Over=true;
            START=false;
        }
    }
    else if(tZ4>10 && tZ4<10.5)
    {
        if((ballPosX>-1.5 && ballPosX<1.5) && (ballPosY>2.5 && ballPosY<5.5) )
        {
            Over=true;
            START=false;
        }
    }
    else if(tZ5>10 && tZ5<10.5)
    {
        if((ballPosX>0.5 && ballPosX<3.5) && (ballPosY>-0.5 && ballPosY<2.5) )
        {
            Over=true;
            START=false;
        }
    }
    else if(tZ6>10 && tZ6<10.5)
    {
        if((ballPosX>-5.5 && ballPosX<-2.5) && (ballPosY>2.5 && ballPosY<5.5) )
        {
            Over=true;
            START=false;
        }
    }
}
/// *** Environment Model **///
void environment(int n){
    ///Ground
    glColor3d(0.5,0.5,0.5);
    glPushMatrix();
        glTranslated(0,0,0);
        glScaled(EN_SIZE*2,0.3,EN_SIZE*2);
        glutSolidCube(1);
    glPopMatrix();
    ///Windmill
    glPushMatrix();
    glTranslated(0,8.5,5);
    glScaled(1,1,1);
    windMill();
    glPopMatrix();
    ///Baby Doll
    glPushMatrix();
    glTranslated(-2.5,6,2);
    glRotated(-60,0,1,0);
    glScaled(1.5,2,1.5);
    glRotated(15,0,1,0);
    BabyDoll();
    glPopMatrix();
    ///Circle in the air
    glColor3d(0,1,0.5);
    glPushMatrix();
    glTranslated(torusPosX[n],torusPosY[n],0);
    glScaled(0.3,0.3,0.3);
    glutSolidTorus(0.1,2,30,30);
    glPopMatrix();
    Find_Score();
    ///displaying houses scene
        for(int i=-(EN_SIZE/2)+1;i<(EN_SIZE/2);i+=2)
            {
            for(int j=-(EN_SIZE/2)+1;j<(EN_SIZE/2);j+=2)
            {
                if(tola[i+(EN_SIZE/2)+1][j+(EN_SIZE/2)+1]!=0)
                {
                    glPushMatrix();
                        glTranslated(i,0,j);
                        house(tola[i+(EN_SIZE/2)+1][j+(EN_SIZE/2)+1],i,j);
                    glPopMatrix();
                }else if(i>=-5&&i<=5){}
                else{
                    tola[i+(EN_SIZE/2)+1][j+(EN_SIZE/2)+1]=(rand()%5)+1;
                    glPushMatrix();
                        glTranslated(i,0,j);
                        house(tola[i+(EN_SIZE/2)+1][j+(EN_SIZE/2)+1],i,j);
                    glPopMatrix();
                }
            }
        }
}
/// *** drawing the scene of the environment and the ball **///
void draw(){
    double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    double a = t*90.0;

    TIME = t;

    ///Ball
    if(rotX>11)rotX=11;
    if(rotX<-11)rotX=-11;
    if(rotZ>10)rotZ=10;
    if(rotZ<-15)rotZ=-15;

    glPushMatrix();
        glTranslated(0,1,0);
        glRotated(90,0,1,0);
        glRotated(5,0,0,1);
        glRotated(rotX,1,0,0);
        glRotated(rotY,0,1,0);
        glRotated(rotZ,0,0,1);

        glScaled(0.4,0.4,0.4);
        Ball();
    glPopMatrix();

    ///Environment
    if(tX>=4.1)tX=4.1;
    if(tX<=-4.1)tX=-4.1;
    if(tY>0.1)tY= 0.1;
    if(tY<-15)tY= -15;

    glPushMatrix();
        glTranslated(tX,tY,tZ);
        environment(2);
    glPopMatrix();

    glPushMatrix();
        glTranslated(tX,tY,tZ1);
        fieldDisplay();
    glPopMatrix();

    glPushMatrix();
        glTranslated(tX,tY,tZ2);
        environment(3);
    glPopMatrix();

    glPushMatrix();
        glTranslated(tX,tY,tZ3);
        environment(1);
    glPopMatrix();

    glPushMatrix();
        glTranslated(tX,tY,tZ4);
        environment(5);
    glPopMatrix();

    glPushMatrix();
        glTranslated(tX,tY,tZ5);
        environment(4);
    glPopMatrix();

    glPushMatrix();
        glTranslated(tX,tY,tZ6);
        environment(2);
    glPopMatrix();

    tZ+=speed;
    tZ1+=speed;
    tZ2+=speed;
    tZ3+=speed;
    tZ4+=speed;
    tZ5+=speed;
    tZ6+=speed;

    if(tZ>=20)tZ=-110;
    if(tZ1>=20)tZ1=-110;
    if(tZ2>=20)tZ2=-110;
    if(tZ3>=20)tZ3=-110;
    if(tZ4>=20)tZ4=-110;
    if(tZ5>=20)tZ5=-110;
    if(tZ6>=20)tZ6=-110;

    if(rotX>0)rotX-=angleBackFrac;
    if(rotX<0)rotX+=angleBackFrac;
    if(rotY>0)rotY-=angleBackFrac;
    if(rotY<0)rotY+=angleBackFrac;
    if(rotZ>0)rotZ-=angleBackFrac;
    if(rotZ<0)rotZ+=angleBackFrac;


    speed += 0.0002;
    if(speed>=0.1)speed=0.1;
}
/// *** Stroke of the texts **///
void drawStrokeText(char* str,int x,int y,int z)
{
	  char *c;
	  glPushMatrix();
	  glTranslatef(x, y+8,z);
	  glScalef(0.002f,0.002f,z);

	  for (c=str; *c != '\0'; c++)
	  {
    		glutStrokeCharacter(GLUT_STROKE_ROMAN , *c);
	  }
	  glPopMatrix();
}
/// *** Stroke and font of the texts **///
void drawStrokeText2(char* str,int x,int y,int z)
{
	  char *c;
	  glPushMatrix();
	  glTranslatef(x, y+8,z);
	  glScalef(0.005f,0.005f,z);

	  for (c=str; *c != '\0'; c++)
	  {
    		glutStrokeCharacter(GLUT_STROKE_ROMAN , *c);
	  }
	  glPopMatrix();
}
/// *** Stroke of the character **///
void drawStrokeChar(char c,float x,float y,float z)
{
	  glPushMatrix();
          glTranslatef(x, y+8,z);
          glScalef(0.002f,0.002f,z);
          glutStrokeCharacter(GLUT_STROKE_ROMAN , c);
	  glPopMatrix();
}
/// *** Font of the texts and the character **///
void setFont(void *font)
{
    currentfont=font;
}

void drawstring(float x,float y,float z,char *string)
{
    char *c;
    glRasterPos3f(x,y,z);

    for(c=string; *c!='\0'; c++)
    {
        glutBitmapCharacter(currentfont,*c);
    }
}
/// *** Lose State showing the score **///
void GameOver()
{
    int final_Result = score/24;
    char num_string[10];
    itoa(final_Result,num_string,10);

    glPushMatrix();
    setFont(GLUT_BITMAP_TIMES_ROMAN_24);
    glColor3f(1,0,0);
    drawstring(-1.8,8.0,0.0,"Game Over ");
    drawstring(-2.4,7.0,0.0,"Total Score is : ");
    drawstring(0,7.0,0.0,num_string);
    drawstring(-2.4,6.0,0.0,"Press Enter to Restart ");
    glPopMatrix();

    speed = 0.0;
    zoom=4;
    tX=0;
    tY=-2;
    tZ=-8;
    tZ1=-20;
    tZ2=-40;
    tZ3=-60;
    tZ4=-80;
    tZ5=-100;
    tZ6=-120;
    rotX=0;
    rotY=0;
    rotZ=0;
    angleBackFrac = 0.2;
    START = false;
    rot = false;
    light0 = true;
    no_ambient = false;
    no_diffuse = false;
    no_specular = false;
    emmission_on = true;
    anglex= 0.0;
    angley= 0.0;
    anglez= 0.0;
    normalLight =false;
}
/// *** The main screen (main menu) **///
void Main_Screen()
{
    int final_Result = score/24;
    char num_string[10];
    itoa(final_Result,num_string,10);
    glPushMatrix();
    glColor3f(1,0,1);
    setFont(GLUT_BITMAP_TIMES_ROMAN_24);

    drawstring(-6,7.0,0.0,"Score: ");
    drawstring(-5,7.0,0.0, num_string);
    glPopMatrix();
}
/// *** display function **///
static void display(void)
{
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    double a = t*90.0;
    double aa=a;

    if(!rot){
        a=0;
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    gluLookAt(	0.0, 4.5, 10.0,
                0, 4, 0,
                0, 1.0f, 0.0f);
glPushMatrix();

    glPopMatrix();
    if(START){

        glPushMatrix();
            glTranslated(0,0,0);
            glScaled(zoom,zoom,zoom);
            glRotated(a,0,1,0);
            draw();
        glPopMatrix();

        drawStrokeText("UP: W, DOWN: S, LEFT: A, RIGHT: D, ZOOM IN: z, ZOOM OUT: Z MAIN MENU: M",-8,0.9,0);
        drawStrokeText("TIME : ",3,0,0);
        int mod,number=0;
        while(TIME){
            mod=TIME%10;
            number=number*10+mod;
            TIME/=10;
        }
        float tmp=0;
        while(number){
            mod=number%10;
            drawStrokeChar(mod+48,4+tmp,0,0);
            number/=10;
            tmp+=0.2;
        }
        Main_Screen();

    }
     else if(Over)
    {
        GameOver();

    }
    else{
        glPushMatrix();
            glTranslated(0,3,0);
            glRotated(aa,0,1,0);
            glScaled(1.5,1.5,1.5);
            Ball();
        glPopMatrix();

        drawStrokeText2("Press ENTER to Start",-4,-1,0);
        drawStrokeText2("Ball Game",-2,0,0);
    }

    glutSwapBuffers();
}
static void key(unsigned char key, int x, int y)
{
    float frac = 0.3;
    float rotFrac = 1;
    switch (key)
    {
        ///exit key
        case 'q':
            exit(0);
            break;
        ///zoom in key
        case 'z':
            zoom+=0.05;
            break;
        ///zoom out key
        case 'Z':
            zoom-=0.05;
        ///go up key
        case 'w':
            tY-=frac;
            rotZ+=rotFrac;
            break;
        ///go down key
        case 's':
            tY+=frac;
            rotZ-=rotFrac;
            break;
        ///go left key
        case 'a':
            tX+=frac;
            rotX-=rotFrac*3;
            rotY+=rotFrac/2;
            break;
        ///go right key
        case 'd':
            tX-=frac;
            rotX+=rotFrac*3;
            rotY-=rotFrac/2;
            break;
        ///go to the main menu key
        case 'm':
            score=0;
            START=false;
            Over = false;
            break;
        ///Enter key
        case 13:
            score=0;
            START=true;
            break;
    }

    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

/// *** Program entry point **///
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowPosition(0,0);
	glutInitWindowSize(1366,720);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);

    glutCreateWindow("Ball Game 19109948/19100190");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    glClearColor(1,1,1,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    PlaySound(TEXT("sound1.wav"),NULL,SND_ASYNC|SND_FILENAME|SND_LOOP);

    glutMainLoop();

    return EXIT_SUCCESS;
}

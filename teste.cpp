#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include "tgaload.h"

#define PASSO_TEMPO 50  // Passo do tempo
#define GRAU_RAD 0.017453292519943   //  Define a constante de conversÃ£o de Graus para Radianos

#define SENS_ROT 10.0
#define SENS_OBS 10.0
#define SENS_TRANS 10.0   

// Qtd m?xima de texturas a serem usadas no programa
#define MAX_NO_TEXTURES 7
// vetor com os n?meros das texturas
GLuint texture_id[MAX_NO_TEXTURES];

void initTexture (void)
{
	// Habilita o uso de textura 
	glEnable ( GL_TEXTURE_2D );
	// Define a forma de armazenamento dos pixels na textura (1= alihamento por byte)
	glPixelStorei ( GL_UNPACK_ALIGNMENT, 1 );
	// Define quantas texturas ser?o usadas no programa 
	glGenTextures (MAX_NO_TEXTURES, texture_id);  // Quantidade de texturas, vetor de texturas
	
	// TEXTURA 0
	texture_id[0] = 1001;
	glBindTexture ( GL_TEXTURE_2D, texture_id[0] );
	image_t temp_image0;
	tgaLoad  ( "texturas/grama.tga", &temp_image0, TGA_FREE | TGA_LOW_QUALITY );
	
	texture_id[1] = 1002;
	glBindTexture ( GL_TEXTURE_2D, texture_id[1] );
	image_t temp_image1;
	tgaLoad  ( "texturas/parede.tga", &temp_image1, TGA_FREE | TGA_LOW_QUALITY );
	
	texture_id[2] = 1003;
	glBindTexture ( GL_TEXTURE_2D, texture_id[2] );
	image_t temp_image2;
	tgaLoad  ( "texturas/telhado.tga", &temp_image2, TGA_FREE | TGA_LOW_QUALITY );
	
	texture_id[3] = 1004;
	glBindTexture ( GL_TEXTURE_2D, texture_id[3] );
	image_t temp_image3;
	tgaLoad  ( "texturas/porta.tga", &temp_image3, TGA_FREE | TGA_LOW_QUALITY );
	
	texture_id[4] = 1005;
	glBindTexture ( GL_TEXTURE_2D, texture_id[4] );
	image_t temp_image4;
	tgaLoad  ( "texturas/piso.tga", &temp_image4, TGA_FREE | TGA_LOW_QUALITY );
	
	texture_id[5] = 1006;
	glBindTexture ( GL_TEXTURE_2D, texture_id[5] );
	image_t temp_image5;
	tgaLoad  ( "texturas/ceu.tga", &temp_image5, TGA_FREE | TGA_LOW_QUALITY );
}

//GLfloat angle, fAspect;
GLfloat ASPECTO, ANGULO;
int x_ini,y_ini, bot;
GLfloat obsX, obsY, obsZ, rotX, rotY;
GLfloat obsX_ini, obsY_ini, obsZ_ini, rotX_ini, rotY_ini;
GLfloat escalaX, escalaY, escalaZ;

static double alturaParedes = 40.0;
static double texturaTelhado[4] = {0.3, 0.2, 0.0, 1.0};
static double texturaParede[4] = {0.8, 0.8, 1.0, 1.0};
static double texturaChao[4] = {1.0, 1.0, 0.9, 1.0};
static double texturaJanela[4] = {1.0, 1.0, 1.0, 0.5};
static double texturaGrama[4] = {0.0, 0.6, 0.3, 1.0}; 

static bool abrePorta = false;
static double anguloPorta = 0;

static bool abreJanela = false;
static double anguloJanela = 0;

static double posicaoHumanoide = 60;
static bool rotacionaHumanoide = false;
static double anguloHumanoide = 0;

float OE = 0.0;
float PE = 0.0;
float OD = 0.0; 
float PD = 0.0;

void desenhaPorta(){
   	glPushMatrix();	 	
			glTranslatef(25.0, 0.0, 20.0); 
	   		glBindTexture ( GL_TEXTURE_2D, texture_id[3] );	 	
	    	glRotatef(anguloPorta, 0.0, 1.0, 0.0);
	    	glBegin(GL_QUADS);
	    	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 0.0, 0.0);
	    	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 0.0, 0.0);
	    	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 15.0, 0.0);
	    	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0, 15.0, 0.0);
	    	glEnd();
    glPopMatrix();
}
//---------------------CASA-----------------------------------
void desenhaJanela(GLfloat x, GLfloat y, GLfloat z, char tipo){
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	int constanteDePosicao = 1;
	int constanteDePosicaoJanela = 1;
	if(tipo == 'E'){
		constanteDePosicaoJanela = -1;
	} else if (tipo == 'D'){
		constanteDePosicao = -1;
	}
	glPushMatrix();	 
	   	   	glTranslatef(x, y, z);
	    	glRotatef(anguloJanela * constanteDePosicaoJanela, 0.0, 1.0, 0.0);
            glColor4f(texturaJanela[0], texturaJanela[1], texturaJanela[2], texturaJanela[3]);	 
	    	glBegin(GL_QUADS);
	    	glVertex3f(0.2 * constanteDePosicao, 0.2, 0.0);
	    	glVertex3f(9.8 * constanteDePosicao, 0.2, 0.0);
	    	glVertex3f(9.8 * constanteDePosicao, 9.8, 0.0);
	    	glVertex3f(0.2 * constanteDePosicao, 9.8, 0.0);
	    	glEnd();
	glPopMatrix();
	glPushMatrix();	 
			glTranslatef(x, y, z);
	    	glRotatef(anguloJanela * constanteDePosicaoJanela, 0.0, 1.0, 0.0);
            glColor4f(texturaTelhado[0], texturaTelhado[1], texturaTelhado[2], texturaTelhado[3]);	 
	    	glBegin(GL_QUADS);
	    	glVertex3f(0.0, 0.0, 0.0);
	    	glVertex3f(0.0, 10.0, 0.0);
	    	glVertex3f(0.2 * constanteDePosicao, 10.0, 0.0);
	    	glVertex3f(0.2 * constanteDePosicao, 0.0, 0.0);
	    	glEnd();
	glPopMatrix();
	glPushMatrix();	 
            glTranslatef(x, y, z);
	    	glRotatef(anguloJanela * constanteDePosicaoJanela, 0.0, 1.0, 0.0);
			glColor4f(texturaTelhado[0], texturaTelhado[1], texturaTelhado[2], texturaTelhado[3]);	 
	    	glBegin(GL_QUADS);
	    	glVertex3f(0.0, 10.0, 0.0);
	    	glVertex3f(10.0 * constanteDePosicao, 10.0, 0.0);
	    	glVertex3f(10.0 * constanteDePosicao, 9.8, 0.0);
	    	glVertex3f(0.0, 9.8, 0.0);
	    	glEnd();
	glPopMatrix();
	glPushMatrix();	 
            glTranslatef(x, y, z);
	    	glRotatef(anguloJanela * constanteDePosicaoJanela, 0.0, 1.0, 0.0);
			glColor4f(texturaTelhado[0], texturaTelhado[1], texturaTelhado[2], texturaTelhado[3]);	 
	    	glBegin(GL_QUADS);
	    	glVertex3f(9.8 * constanteDePosicao, 10.0, 0.0);
	    	glVertex3f(9.8 * constanteDePosicao, 0.0, 0.0);
	    	glVertex3f(10.0 * constanteDePosicao, 0.0, 0.0);
	    	glVertex3f(10.0 * constanteDePosicao, 10.0, 0.0);
	    	glEnd();
	glPopMatrix();
	glPushMatrix();	
  	   		glTranslatef(x, y, z);
    		glRotatef(anguloJanela * constanteDePosicaoJanela, 0.0, 1.0, 0.0);
            glColor4f(texturaTelhado[0], texturaTelhado[1], texturaTelhado[2], texturaTelhado[3]);	 
	    	glBegin(GL_QUADS);
	    	glVertex3f(0.0, 0.0, 0.0);
	    	glVertex3f(10.0 * constanteDePosicao, 0.0, 0.0);
	    	glVertex3f(10.0 * constanteDePosicao, 0.2, 0.0);
	    	glVertex3f(0.0, 0.2, 0.0);
	    	glEnd();
	glPopMatrix();
}

void desenhaJanelas(){
	desenhaJanela(5.0, 5.0, 40.0, 'E');
    desenhaJanela(5.0, 25.0, 40.0, 'E');
	desenhaJanela(75.0, 5.0, 40.0,  'D');
	desenhaJanela(75.0, 25.0, 40.0, 'D');
}

void desenhaPiso(GLfloat y){
	glPushMatrix();
	   		glBindTexture ( GL_TEXTURE_2D, texture_id[4] );	 
	    	glBegin(GL_QUADS);
	    	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, y, 0.0);
	    	glTexCoord2f(1.0f, 0.0f); glVertex3f(20.0, y, 0.0);
	    	glTexCoord2f(1.0f, 1.0f); glVertex3f(20.0, y, 40.0);
	    	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0, y, 40.0);
	    	glEnd();
        glPopMatrix();
        glPushMatrix();
	   		glBindTexture ( GL_TEXTURE_2D, texture_id[4] );	
	    	glBegin(GL_QUADS);
	    	glTexCoord2f(0.0f, 0.0f); glVertex3f(20.0, y, 0.0);
	    	glTexCoord2f(1.0f, 0.0f); glVertex3f(80.0, y, 0.0);
	    	glTexCoord2f(1.0f, 1.0f); glVertex3f(80.0, y, 20.0);
	    	glTexCoord2f(0.0f, 1.0f); glVertex3f(20.0, y, 20.0);
	    	glEnd();
        glPopMatrix();
        glPushMatrix();
	   		glBindTexture ( GL_TEXTURE_2D, texture_id[4] );	
	    	glBegin(GL_QUADS);
	    	glTexCoord2f(0.0f, 0.0f); glVertex3f(60.0, y, 20.0);
	    	glTexCoord2f(1.0f, 0.0f); glVertex3f(60.0, y, 40.0);
	    	glTexCoord2f(1.0f, 1.0f); glVertex3f(80.0, y, 40.0);
	    	glTexCoord2f(0.0f, 1.0f); glVertex3f(80.0, y, 20.0);
	    	glEnd();
        glPopMatrix();
}

void desenhaPisoAndares(){
	desenhaPiso(0.0);
	desenhaPiso(20.0);
}

void desenhaGrama(){
    glPushMatrix();
	   	glBindTexture ( GL_TEXTURE_2D, texture_id[0] );	 
    	glBegin(GL_QUADS);
    	glTexCoord2f(0.0f, 0.0f); glVertex3f(20.0, 0.0, 20.0);
    	glTexCoord2f(1.0f, 0.0f); glVertex3f(60.0, 0.0, 20.0);
    	glTexCoord2f(1.0f, 1.0f); glVertex3f(60.0, 0.0, 40.0);
    	glTexCoord2f(0.0f, 1.0f); glVertex3f(20.0, 0.0, 40.0);
    	glEnd();
    glPopMatrix();
    glPushMatrix();
	   	glBindTexture ( GL_TEXTURE_2D, texture_id[0] );
    	glBegin(GL_QUADS);
    	glTexCoord2f(0.0f, 0.0f); glVertex3f(-20.0, 0.0, 40.0);
    	glTexCoord2f(1.0f, 0.0f); glVertex3f(100.0, 0.0, 40.0);
    	glTexCoord2f(1.0f, 1.0f); glVertex3f(100.0, 0.0, 80.0);
    	glTexCoord2f(0.0f, 1.0f); glVertex3f(-20.0, 0.0, 80.0);
    	glEnd();
    glPopMatrix();
   glPushMatrix();
	   	glBindTexture ( GL_TEXTURE_2D, texture_id[0] );
    	glBegin(GL_QUADS);
    	glTexCoord2f(0.0f, 0.0f); glVertex3f(-20.0, 0.0, 0.0);
    	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0, 0.0, 0.0);
    	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0, 0.0, 40.0);
    	glTexCoord2f(0.0f, 1.0f); glVertex3f(-20.0, 0.0, 40.0);
    	glEnd();
    glPopMatrix();
    glPushMatrix();
	   	glBindTexture ( GL_TEXTURE_2D, texture_id[0] );
    	glBegin(GL_QUADS);
    	glTexCoord2f(0.0f, 0.0f); glVertex3f(-20.0, 0.0, 0.0);
    	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0, 0.0, 0.0);
    	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0, 0.0, 40.0);
    	glTexCoord2f(0.0f, 1.0f); glVertex3f(-20.0, 0.0, 40.0);
    	glEnd();
    glPopMatrix();
    glPushMatrix();
	   	glBindTexture ( GL_TEXTURE_2D, texture_id[0] );
    	glBegin(GL_QUADS);
    	glTexCoord2f(0.0f, 0.0f); glVertex3f(80.0, 0.0, 0.0);
    	glTexCoord2f(1.0f, 0.0f); glVertex3f(100.0, 0.0, 0.0);
    	glTexCoord2f(1.0f, 1.0f); glVertex3f(100.0, 0.0, 40.0);
    	glTexCoord2f(0.0f, 1.0f); glVertex3f(80.0, 0.0, 40.0);
    	glEnd();
    glPopMatrix();
}

void desenhaCasa(){
	//Mesa
    glPushMatrix();
        glBindTexture ( GL_TEXTURE_2D, texture_id[1] );	 	 
        glColor3f(0.5, 0.5, 0.5);
        glTranslatef(5.0,4.8,5.0);
        glRotatef(90.0,1.0,0.0,0.0);
        glutSolidCone(5.0,1.0,20.0,1.0);
    glPopMatrix();
    //Bule
    glPushMatrix();
        glColor3f(0.9, 0.9, 0.9);
        glTranslatef(5.0,5.0,5.0);
		glutSolidTeapot(1.0);
    glPopMatrix();
	//Pe da mesa
    glPushMatrix();
	   	glBindTexture ( GL_TEXTURE_2D, texture_id[1] );	 	 
        glTranslatef(5.0,4.0,5.0);
        glRotatef(90.0,1.0,0.0,0.0);
        GLUquadric *obj = gluNewQuadric();
        gluQuadricTexture(obj, GLU_FILL);
		gluCylinder(obj,1.0,1.0,4.0,20.0,4);
    glPopMatrix();
    //Chao
	desenhaPisoAndares();
	// desenhaGrama();
	//Paredes
    // Parede Esqueda
	glPushMatrix();
	   	glBindTexture ( GL_TEXTURE_2D, texture_id[1] );	 	 
    	glBegin(GL_QUADS);
    	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 0.0, 0.0);
    	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0, 0.0, 40.0);
    	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0, alturaParedes, 40.0);
    	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0, alturaParedes, 0.0);
    	glEnd();
    glPopMatrix();
    // Parede Fundo
    glPushMatrix();
	   	glBindTexture ( GL_TEXTURE_2D, texture_id[1] ); 
    	glBegin(GL_QUADS);
    	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 0.0, 0.0);
    	glTexCoord2f(1.0f, 0.0f); glVertex3f(80.0, 0.0, 0.0);
    	glTexCoord2f(1.0f, 1.0f); glVertex3f(80.0, alturaParedes, 0.0);
    	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0, alturaParedes, 0.0);
    	glEnd();
    glPopMatrix();
    // Parede Direita
    glPushMatrix();
	   	glBindTexture ( GL_TEXTURE_2D, texture_id[1] ); 
    	glBegin(GL_QUADS);
    	glTexCoord2f(0.0f, 0.0f); glVertex3f(80.0, 0.0, 0.0);
    	glTexCoord2f(1.0f, 0.0f); glVertex3f(80.0, 0.0, 40.0);
    	glTexCoord2f(1.0f, 1.0f); glVertex3f(80.0, alturaParedes, 40.0);
    	glTexCoord2f(0.0f, 1.0f); glVertex3f(80.0, alturaParedes, 0.0);
    	glEnd();
    glPopMatrix();
    //Parede Frontal Esquerda
    glPushMatrix();
	   	glBindTexture ( GL_TEXTURE_2D, texture_id[1] );
    	glBegin(GL_QUADS);
    	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 0.0, 40.0);
    	glTexCoord2f(1.0f, 0.0f); glVertex3f(20.0, 0.0, 40.0);
    	glTexCoord2f(1.0f, 1.0f); glVertex3f(20.0, 5.0, 40.0);
    	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0, 5.0, 40.0);
    	glEnd();
    glPopMatrix();
    glPushMatrix();
	   	glBindTexture ( GL_TEXTURE_2D, texture_id[1] );
    	glBegin(GL_QUADS);
    	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, 0.0, 40.0);
    	glTexCoord2f(1.0f, 0.0f); glVertex3f(5.0, 0.0, 40.0);
    	glTexCoord2f(1.0f, 1.0f); glVertex3f(5.0, alturaParedes, 40.0);
    	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0, alturaParedes, 40.0);
    	glEnd();
    glPopMatrix();
    glPushMatrix();
	   	glBindTexture ( GL_TEXTURE_2D, texture_id[1] ); 
    	glBegin(GL_QUADS);
    	glTexCoord2f(0.0f, 0.0f); glVertex3f(15.0, 0.0, 40.0);
    	glTexCoord2f(1.0f, 0.0f); glVertex3f(20.0, 0.0, 40.0);
    	glTexCoord2f(1.0f, 1.0f); glVertex3f(20.0, alturaParedes, 40.0);
    	glTexCoord2f(0.0f, 1.0f); glVertex3f(15.0, alturaParedes, 40.0);
    	glEnd();
    glPopMatrix();
    glPushMatrix();
	   	glBindTexture ( GL_TEXTURE_2D, texture_id[1] );	 
    	glBegin(GL_QUADS);
    	glTexCoord2f(0.0f, 0.0f); glVertex3f(5.0, 15.0, 40.0);
    	glTexCoord2f(1.0f, 0.0f); glVertex3f(15.0, 15.0, 40.0);
    	glTexCoord2f(1.0f, 1.0f); glVertex3f(15.0, 25.0, 40.0);
    	glTexCoord2f(0.0f, 1.0f); glVertex3f(5.0, 25.0, 40.0);
    	glEnd();
    glPopMatrix();
    glPushMatrix();
	   	glBindTexture ( GL_TEXTURE_2D, texture_id[1] );	 
    	glBegin(GL_QUADS);
    	glTexCoord2f(0.0f, 0.0f); glVertex3f(5.0, 35.0, 40.0);
    	glTexCoord2f(1.0f, 0.0f); glVertex3f(15.0, 35.0, 40.0);
    	glTexCoord2f(1.0f, 1.0f); glVertex3f(15.0, 40.0, 40.0);
    	glTexCoord2f(0.0f, 1.0f); glVertex3f(5.0, 40.0, 40.0);
    	glEnd();
    glPopMatrix();
    //Parede Frontal Interna Esquerda
    glPushMatrix();
	   	glBindTexture ( GL_TEXTURE_2D, texture_id[1] );
    	glBegin(GL_QUADS);
    	glTexCoord2f(0.0f, 0.0f); glVertex3f(20.0, 0.0, 40.0);
    	glTexCoord2f(1.0f, 0.0f); glVertex3f(20.0, 0.0, 20.0);
    	glTexCoord2f(1.0f, 1.0f); glVertex3f(20.0, alturaParedes, 20.0);
    	glTexCoord2f(0.0f, 1.0f); glVertex3f(20.0, alturaParedes, 40.0);
    	glEnd();
    glPopMatrix();
    //Parede Frontal
    glPushMatrix();
	   	glBindTexture ( GL_TEXTURE_2D, texture_id[1] );
    	glBegin(GL_QUADS);
    	glTexCoord2f(0.0f, 0.0f); glVertex3f(20.0, 0.0, 20.0);
    	glTexCoord2f(1.0f, 0.0f); glVertex3f(25.0, 0.0, 20.0);
    	glTexCoord2f(1.0f, 1.0f); glVertex3f(25.0, alturaParedes, 20.0);
    	glTexCoord2f(0.0f, 1.0f); glVertex3f(20.0, alturaParedes, 20.0);
    	glEnd();
    glPopMatrix();
    glPushMatrix();
	   	glBindTexture ( GL_TEXTURE_2D, texture_id[1] ); 
    	glBegin(GL_QUADS);
    	glTexCoord2f(0.0f, 0.0f); glVertex3f(20.0, 15.0, 20.0);
    	glTexCoord2f(1.0f, 0.0f); glVertex3f(35.0, 15.0, 20.0);
    	glTexCoord2f(1.0f, 1.0f); glVertex3f(35.0, alturaParedes, 20.0);
    	glTexCoord2f(0.0f, 1.0f); glVertex3f(20.0, alturaParedes, 20.0);
    	glEnd();
    glPopMatrix();
    glPushMatrix();
	   	glBindTexture ( GL_TEXTURE_2D, texture_id[1] );
    	glBegin(GL_QUADS);
    	glTexCoord2f(0.0f, 0.0f); glVertex3f(35.0, 0.0, 20.0);
    	glTexCoord2f(1.0f, 0.0f); glVertex3f(80.0, 0.0, 20.0);
    	glTexCoord2f(1.0f, 1.0f); glVertex3f(80.0, alturaParedes, 20.0);
    	glTexCoord2f(0.0f, 1.0f); glVertex3f(35.0, alturaParedes, 20.0);
    	glEnd();
    glPopMatrix();
    //Parede Frontal Interna Direita
    glPushMatrix();
	   	glBindTexture ( GL_TEXTURE_2D, texture_id[1] );	 
    	glBegin(GL_QUADS);
    	glTexCoord2f(0.0f, 0.0f); glVertex3f(60.0, 0.0, 20.0);
    	glTexCoord2f(1.0f, 0.0f); glVertex3f(60.0, 0.0, 40.0);
    	glTexCoord2f(1.0f, 1.0f); glVertex3f(60.0, alturaParedes, 40.0);
    	glTexCoord2f(0.0f, 1.0f); glVertex3f(60.0, alturaParedes, 20.0);
    	glEnd();
    glPopMatrix();
    //Parede Frontal Direita
	glPushMatrix();
	   	glBindTexture ( GL_TEXTURE_2D, texture_id[1] );
    	glBegin(GL_QUADS);
    	glTexCoord2f(0.0f, 0.0f); glVertex3f(60.0, 0.0, 40.0);
    	glTexCoord2f(1.0f, 0.0f); glVertex3f(80.0, 0.0, 40.0);
    	glTexCoord2f(1.0f, 1.0f); glVertex3f(80.0, 5.0, 40.0);
    	glTexCoord2f(0.0f, 1.0f); glVertex3f(60.0, 5.0, 40.0);
    	glEnd();
    glPopMatrix();
    glPushMatrix();
	   	glBindTexture ( GL_TEXTURE_2D, texture_id[1] );
    	glBegin(GL_QUADS);
    	glTexCoord2f(0.0f, 0.0f); glVertex3f(60.0, 0.0, 40.0);
    	glTexCoord2f(1.0f, 0.0f); glVertex3f(65.0, 0.0, 40.0);
    	glTexCoord2f(1.0f, 1.0f); glVertex3f(65.0, alturaParedes, 40.0);
    	glTexCoord2f(0.0f, 1.0f); glVertex3f(60.0, alturaParedes, 40.0);
    	glEnd();
    glPopMatrix();
    glPushMatrix();
	   	glBindTexture ( GL_TEXTURE_2D, texture_id[1] );
    	glBegin(GL_QUADS);
    	glTexCoord2f(0.0f, 0.0f); glVertex3f(75.0, 0.0, 40.0);
    	glTexCoord2f(1.0f, 0.0f); glVertex3f(80.0, 0.0, 40.0);
    	glTexCoord2f(1.0f, 1.0f); glVertex3f(80.0, alturaParedes, 40.0);
    	glTexCoord2f(0.0f, 1.0f); glVertex3f(75.0, alturaParedes, 40.0);
    	glEnd();
    glPopMatrix();
    glPushMatrix();
	   	glBindTexture ( GL_TEXTURE_2D, texture_id[1] ); 
    	glBegin(GL_QUADS);
    	glTexCoord2f(0.0f, 0.0f); glVertex3f(65.0, 15.0, 40.0);
    	glTexCoord2f(1.0f, 0.0f); glVertex3f(75.0, 15.0, 40.0);
    	glTexCoord2f(1.0f, 1.0f); glVertex3f(75.0, 25.0, 40.0);
    	glTexCoord2f(0.0f, 1.0f); glVertex3f(65.0, 25.0, 40.0);
    	glEnd();
    glPopMatrix();
    glPushMatrix();
	   	glBindTexture ( GL_TEXTURE_2D, texture_id[1] );
    	glBegin(GL_QUADS);
    	glTexCoord2f(0.0f, 0.0f); glVertex3f(65.0, 35.0, 40.0);
    	glTexCoord2f(1.0f, 0.0f); glVertex3f(75.0, 35.0, 40.0);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(75.0, 40.0, 40.0);
    	glTexCoord2f(0.0f, 1.0f); glVertex3f(65.0, 40.0, 40.0);
    	glEnd();
    glPopMatrix();     
    //Telhado
    //TelhadoEsquerdo
	glPushMatrix(); 
	   	glBindTexture ( GL_TEXTURE_2D, texture_id[2] );
    	glBegin(GL_QUADS);
    	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, alturaParedes, 40.0);
    	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 50.0, 40.0);
    	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 50.0, 40.0);
    	glTexCoord2f(0.0f, 1.0f); glVertex3f(20.0, alturaParedes, 40.0);
    	glEnd();
    glPopMatrix();
	glPushMatrix();	 
	   	glBindTexture ( GL_TEXTURE_2D, texture_id[2] );
    	glBegin(GL_QUADS);
    	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, alturaParedes, 40.0);
    	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 50.0, 40.0);
    	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 50.0, 0.0);
    	glTexCoord2f(0.0f, 1.0f);glVertex3f(0.0, alturaParedes, 0.0);
    	glEnd();
    glPopMatrix();
    glPushMatrix();	 
	   	glBindTexture ( GL_TEXTURE_2D, texture_id[2] );	 
    	glBegin(GL_QUADS);
    	glTexCoord2f(0.0f, 0.0f); glVertex3f(20.0, alturaParedes, 40.0);
    	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 50.0, 40.0);
    	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 50.0, 0.0);
    	glTexCoord2f(0.0f, 1.0f);glVertex3f(20.0, alturaParedes, 0.0);
    	glEnd();
    glPopMatrix();
    glPushMatrix(); 
	   	glBindTexture ( GL_TEXTURE_2D, texture_id[2] );	 
    	glBegin(GL_QUADS);
    	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0, alturaParedes, 0.0);
    	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 50.0, 0.0);
    	glTexCoord2f(1.0f, 1.0f); glVertex3f(10.0, 50.0, 0.0);
    	glTexCoord2f(0.0f, 1.0f); glVertex3f(20.0, alturaParedes, 0.0);
    	glEnd();
    glPopMatrix();
    //TelhadoDireito
    glPushMatrix(); 
	   	glBindTexture ( GL_TEXTURE_2D, texture_id[2] );	 
    	glBegin(GL_TRIANGLES);
    	glTexCoord2f(0.0f, 0.0f); glVertex3f(60, alturaParedes, 40.0);
    	glTexCoord2f(1.0f, 0.0f); glVertex3f(70.0, 50.0, 40.0);
    	glTexCoord2f(0.0f, 1.0f); glVertex3f(80.0, alturaParedes, 40.0);
    	glEnd();
    glPopMatrix();
    glPushMatrix();	 
	   	glBindTexture ( GL_TEXTURE_2D, texture_id[2] );
    	glBegin(GL_QUADS);
    	glTexCoord2f(0.0f, 0.0f); glVertex3f(60, alturaParedes, 40.0);
    	glTexCoord2f(1.0f, 0.0f); glVertex3f(70.0, 50.0, 40.0);
    	glTexCoord2f(1.0f, 1.0f); glVertex3f(70.0, 50.0, 0.0);
    	glTexCoord2f(0.0f, 1.0f); glVertex3f(60, alturaParedes, 0.0);
    	glEnd();
    glPopMatrix();
    glPushMatrix();	 
	   	glBindTexture ( GL_TEXTURE_2D, texture_id[2] );
    	glBegin(GL_QUADS);
    	glTexCoord2f(0.0f, 0.0f); glVertex3f(80.0, alturaParedes, 40.0);
    	glTexCoord2f(1.0f, 0.0f); glVertex3f(70.0, 50.0, 40.0);
    	glTexCoord2f(1.0f, 1.0f); glVertex3f(70.0, 50.0, 0.0);
    	glTexCoord2f(0.0f, 1.0f); glVertex3f(80.0, alturaParedes, 0.0);
    	glEnd();
    glPopMatrix();
	glPushMatrix(); 
	   	glBindTexture ( GL_TEXTURE_2D, texture_id[2] );
    	glBegin(GL_QUADS);
    	glTexCoord2f(0.0f, 0.0f); glVertex3f(60, alturaParedes, 0.0);
    	glTexCoord2f(1.0f, 0.0f); glVertex3f(70.0, 50.0, 0.0);
    	glTexCoord2f(1.0f, 1.0f); glVertex3f(70.0, 50.0, 0.0);
    	glTexCoord2f(0.0f, 1.0f); glVertex3f(80.0, alturaParedes, 0.0);
    	glEnd();
    glPopMatrix();
    //Telhado Meio
    glPushMatrix();	 
	   	glBindTexture ( GL_TEXTURE_2D, texture_id[2] );
    	glBegin(GL_QUADS);
    	glTexCoord2f(0.0f, 0.0f); glVertex3f(20.0, alturaParedes, 0.0);
    	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 50.0, 0.0);
    	glTexCoord2f(1.0f, 1.0f); glVertex3f(70.0, 50.0, 0.0);
    	glTexCoord2f(0.0f, 1.0f); glVertex3f(60.0, alturaParedes, 0.0);
    	glEnd();
    glPopMatrix();
	glPushMatrix();	 
	   	glBindTexture ( GL_TEXTURE_2D, texture_id[2] );	 
    	glBegin(GL_QUADS);
    	glTexCoord2f(0.0f, 0.0f); glVertex3f(20.0, alturaParedes, 20.0);
    	glTexCoord2f(1.0f, 0.0f); glVertex3f(10.0, 50.0, 0.0);
    	glTexCoord2f(1.0f, 1.0f); glVertex3f(70.0, 50.0, 0.0);
    	glTexCoord2f(0.0f, 1.0f); glVertex3f(60.0, alturaParedes, 20.0);
    	glEnd();
    glPopMatrix();
    //Garagem Pilastras
     glPushMatrix();
        glColor3f(0.5, 0.5, 0.5);
        glTranslatef(41.0,20.0,23.0);
        glRotatef(90.0,1.0,0.0,0.0);
        glRotatef(45.0,0.0,0.0,1.0);
        GLUquadric *obj2 = gluNewQuadric();
		gluCylinder(obj2,1.0,1.0,20.0,10,4);
    glPopMatrix();
	glPushMatrix();
        glColor3f(0.5, 0.5, 0.5);
        glTranslatef(41.0,20.0,39.0);
        glRotatef(90.0,1.0,0.0,0.0);
        glRotatef(45.0,0.0,0.0,1.0);
        GLUquadric *obj3 = gluNewQuadric();
		gluCylinder(obj3,1.0,1.0,20.0,10,4);
    glPopMatrix();	
    //Garagem Telhado	    
    glPushMatrix();	 
	   	glBindTexture ( GL_TEXTURE_2D, texture_id[2] );	 	 
    	glBegin(GL_QUADS);
    	glTexCoord2f(0.0f, 0.0f); glVertex3f(40.0, 20.0, 22.0);
    	glTexCoord2f(1.0f, 0.0f); glVertex3f(40.0, 20.0, 40.0);
    	glTexCoord2f(1.0f, 1.0f); glVertex3f(40.0, 20.0, 40.0);
    	glTexCoord2f(0.0f, 1.0f); glVertex3f(40.0, 30.0, 31.5);
    	glEnd();
    glPopMatrix();
	glPushMatrix();	 
	   	glBindTexture ( GL_TEXTURE_2D, texture_id[2] );	 
    	glBegin(GL_QUADS);
    	glTexCoord2f(0.0f, 0.0f); glVertex3f(40.0, 20.0, 40.0);
    	glTexCoord2f(1.0f, 0.0f); glVertex3f(40.0, 30.0, 31.5);
    	glTexCoord2f(1.0f, 1.0f); glVertex3f(60.0, 30.0, 31.5);
    	glTexCoord2f(0.0f, 1.0f); glVertex3f(60.0, 20.0, 40.0);
    	glEnd();
    glPopMatrix();	
	glPushMatrix();	 
	   	glBindTexture ( GL_TEXTURE_2D, texture_id[2] );	  
    	glBegin(GL_QUADS);
    	glTexCoord2f(0.0f, 0.0f); glVertex3f(40.0, 20.0, 22.0);
    	glTexCoord2f(1.0f, 0.0f); glVertex3f(40.0, 30.0, 31.5);
    	glTexCoord2f(1.0f, 1.0f); glVertex3f(60.0, 30.0, 31.5);
    	glTexCoord2f(0.0f, 1.0f); glVertex3f(60.0, 20.0, 22.5);
    	glEnd();
    glPopMatrix();
	desenhaPorta();
	desenhaJanelas();
}
//---------------------------------HUMANOIDE----------------------------------------

void desenhaHumanoide(double posicaoHumanoide){
    glPushMatrix();
       glTranslatef(30.0, 9.5, posicaoHumanoide); //Movimento de Andar
       glRotatef(anguloHumanoide, 0.0, 1.0, 0.0); // Movimento de Girar
       glColor3f(1.0, 0.0, 0.0);
       //TRONCO
       glRotatef(90, 1.0, 0.0, 0.0);
       GLUquadric *objTronco = gluNewQuadric();
       gluCylinder(objTronco, 0.3, 0.3,4.0,20.0,4);
       glPushMatrix();
       	   //COLO
		   glColor3f(0.0, 0.0, 1.0);  
       	   glRotatef(-90, 1.0, 0.0, 0.0);
		   glTranslatef(0.0, -4.0, 0.0);
       	   glutSolidSphere(0.5,  20.0,  20.0); //Colo
       	   glPushMatrix();
       	   	   //Perna Direita
	           glTranslatef(0.4, 0.0, 0.0);
    		   glRotatef(90, 0.0, 1.0, 0.0);
	           glColor3f(1.0, 0.0, 0.0);
       	   	   GLUquadric *objPernaDireita = gluNewQuadric();
	       	   gluCylinder(objPernaDireita, 0.3, 0.3,1.0,20.0,4); // Perna Direita
	       	   glPushMatrix();
	       	   	   //Articulação Perna Direita
				   glRotatef(PD, 0.0, 0.0, 1.0);
	       	   	   glColor3f(0.0, 0.0, 1.0);
				   glRotatef(-90, 0.0, 1.0, 0.0);
	       	   	   glTranslatef(1.0, 0.0, 0.0);
	       	   	   glutSolidSphere(0.5,  20.0,  20.0);//Articulação Perna Direita
	       	   	   //Coxa Direita
	       	   	   glPushMatrix();
	       	   	   	   glTranslatef(0.0, -0.5, 0.0);
    		   	   	   glRotatef(90, 1.0, 0.0, 0.0);
	           	   	   glColor3f(1.0, 0.0, 0.0);
	           	   	   GLUquadric *objCoxaDireita = gluNewQuadric();
	       	   	   	   gluCylinder(objCoxaDireita, 0.3, 0.3,2.0,20.0,4); // Coxa Direita
	       	   	   	   //Joelho
	       	   	   	   glPushMatrix();
		       	   	   	   glColor3f(0.0, 0.0, 1.0);
					   	   glRotatef(-90, 1.0, 0.0, 0.0);
		       	   	   	   glTranslatef(0.0, -2.0, 0.0);
		       	   	   	   glutSolidSphere(0.5,  20.0,  20.0);//Joelho Direito
		       	   	   	   //Canela Direita
		       	   	   	   glTranslatef(0.0, -0.5, 0.0);
	    		   	   	   glRotatef(90, 1.0, 0.0, 0.0);
		           	   	   glColor3f(1.0, 0.0, 0.0);
		           	   	   GLUquadric *objCanelaDireita = gluNewQuadric();
		       	   	   	   gluCylinder(objCanelaDireita, 0.3, 0.3,2.0,20.0,4); // Canela Direita
		       	   	   	   //Tornozelo Direita
		       	   	   	   glColor3f(0.0, 0.0, 1.0);
					   	   glRotatef(-90, 1.0, 0.0, 0.0);
		       	   	   	   glTranslatef(0.0, -2.0, 0.0);
		       	   	   	   glutSolidSphere(0.5,  20.0,  20.0);//Joelho Direito
		       	   	   	   //Pe Direita
		       	   	       glPushMatrix();
		       	   	       	   glTranslatef(0.0, 0.0, -1.0);
		           	   	   	   glColor3f(1.0, 0.0, 0.0);
		           	   	   	   GLUquadric *objPeDireita = gluNewQuadric();
		       	   	   	   	   gluCylinder(objPeDireita, 0.3, 0.3,1.0,20.0,4); // Pe Direita
		       	   	   	   	   //Ponta Pe Direita
							   glColor3f(0.0, 0.0, 1.0);
		       	   	   	   	   glTranslatef(0.0, 0.0, -0.5);
		       	   	   	   	   glutSolidSphere(0.5,  20.0,  20.0);//Ponta Pe Direita
	       	   	   	   	   glPopMatrix();
    				   glPopMatrix();		 	                
				   glPopMatrix();
	       	   glPopMatrix();
  	 	 	glPopMatrix();
  	  	    glPushMatrix();
       	   	   //Perna Esquerda
       	   	   glTranslatef(-1.0, 0.0, 0.0);
		   	   glRotatef(90, 0.0, 1.0, 0.0);
           	   glColor3f(1.0, 0.0, 0.0);
   	   	   	   GLUquadric *objPernaEsquerda = gluNewQuadric();
               gluCylinder(objPernaEsquerda, 0.3, 0.3,1.0,20.0,4); // Perna Direita
               glPushMatrix();
               	   //Articulação Perna Esquerda
               	   glRotatef(PE, 0.0, 0.0, 1.0);
	       	   	   glColor3f(0.0, 0.0, 1.0);
				   glRotatef(-90, 0.0, 1.0, 0.0);
	       	   	   glTranslatef(-0.5, 0.0, 0.0);
	       	   	   glutSolidSphere(0.5,  20.0,  20.0);//Articulação Perna Direita
	       	   	   //Coxa Esquerda
	       	   	   glPushMatrix();
   	    	           glTranslatef(0.0, -0.5, 0.0);
    		   	   	   glRotatef(90, 1.0, 0.0, 0.0);
	           	   	   glColor3f(1.0, 0.0, 0.0);
	           	   	   GLUquadric *objCoxaEsquerda = gluNewQuadric();
	       	   	   	   gluCylinder(objCoxaEsquerda, 0.3, 0.3,2.0,20.0,4); // Coxa Esquerda
	       	   	   	   //Joelho Esquerda
	       	   	   	   glColor3f(0.0, 0.0, 1.0);
				   	   glRotatef(-90, 1.0, 0.0, 0.0);
	       	   	   	   glTranslatef(0.0, -2.0, 0.0);
	       	   	   	   glutSolidSphere(0.5,  20.0,  20.0);//Joelho Esquerda
	       	   	   	   //Canela Esquerda
	       	   	   	   glTranslatef(0.0, -0.5, 0.0);
    		   	   	   glRotatef(90, 1.0, 0.0, 0.0);
	           	   	   glColor3f(1.0, 0.0, 0.0);
	           	   	   GLUquadric *objCanelaEsquerda = gluNewQuadric();
	       	   	   	   gluCylinder(objCanelaEsquerda, 0.3, 0.3,2.0,20.0,4); // Canela Esquerda
	       	   	   	   //Tornozelo Esquerda
	       	   	   	   glColor3f(0.0, 0.0, 1.0);
				   	   glRotatef(-90, 1.0, 0.0, 0.0);
	       	   	   	   glTranslatef(0.0, -2.0, 0.0);
	       	   	   	   glutSolidSphere(0.5,  20.0,  20.0);//Joelho Esquerda
	       	   	   	   //Pe Esquerda
	       	   	       glPushMatrix();
	       	   	       	   glTranslatef(0.0, 0.0, -1.0);
	           	   	   	   glColor3f(1.0, 0.0, 0.0);
	           	   	   	   GLUquadric *objPeEsquerda = gluNewQuadric();
	       	   	   	   	   gluCylinder(objPeEsquerda, 0.3, 0.3,1.0,20.0,4); // Pe Esquerda
	       	   	   	   	   //Ponta Pe Esquerda
						   glColor3f(0.0, 0.0, 1.0);
	       	   	   	   	   glTranslatef(0.0, 0.0, -0.5);
	       	   	   	   	   glutSolidSphere(0.5,  20.0,  20.0);//Ponta Pe Esquerda
    				   glPopMatrix();
			      glPopMatrix();
			   glPopMatrix();
           glPopMatrix();
		 glPopMatrix();
  		 glPushMatrix();
       	   //PEITO
		   glColor3f(0.0, 0.0, 1.0);  
       	   glRotatef(-90, 1.0, 0.0, 0.0);
		   glTranslatef(0.0, 0.0, 0.0);
       	   glutSolidSphere(0.5,  20.0,  20.0); //PEITO
       	   glPushMatrix();
			   //Braco Direita
			   glRotatef(OD, 1.0, 0.0, 0.0);
	           glTranslatef(0.4, 0.0, 0.0);
    		   glRotatef(90, 0.0, 1.0, 0.0);
    		   glRotatef(30, 1.0, 0.0, 0.0);
	           glColor3f(1.0, 0.0, 0.0);
       	   	   GLUquadric *objBracoDireita = gluNewQuadric();
	       	   gluCylinder(objBracoDireita, 0.3, 0.3,1.5,20.0,4); // Braco Direita
	       	   glPushMatrix();
	       	   	   //Cotovelo Direita
	       	   	   glColor3f(0.0, 0.0, 1.0);  
       	   	   	   glRotatef(-90, 0.0, 1.0, 0.0);
		   	   	   glTranslatef(1.5, 0.0, 0.0);
       	   	   	   glutSolidSphere(0.5,  20.0,  20.0); //Cotovelo Direita
       	   	   	   //AnteBraco Direita
       	   	   	   glPushMatrix();
       	   	   	   	   glTranslatef(0.4, 0.0, 0.0);
    		   	   	   glRotatef(90, 0.0, 1.0, 0.0);
	           	   	   glColor3f(1.0, 0.0, 0.0);
       	   	   	   	   GLUquadric *objAnteBracoDireita = gluNewQuadric();
	       	   	   	   gluCylinder(objAnteBracoDireita, 0.3, 0.3,1.5,20.0,4); // //AnteBraco Direita
	       	   	   	   //Mao Direita
					   glColor3f(0.0, 0.0, 1.0);  
       	   	   	   	   glRotatef(-90, 0.0, 1.0, 0.0);
		   	   	   	   glTranslatef(1.5, 0.0, 0.0);
       	   	   	   	   glutSolidSphere(0.5,  20.0,  20.0); //Mao Direita
       	   	   	   	   glPopMatrix();
	       	   glPopMatrix();
           glPopMatrix();
           glPushMatrix();
			   //Braco Esquerda
				glRotatef(OE, 1.0, 0.0, 0.0);
	           glTranslatef(-1.5, -0.7, 0.0);
    		   glRotatef(90, 0.0, 1.0, 0.0);
 			   glRotatef(-30, 1.0, 0.0, 0.0);
	           glColor3f(1.0, 0.0, 0.0);
       	   	   GLUquadric *objBracoEsquerda = gluNewQuadric();
	       	   gluCylinder(objBracoEsquerda, 0.3, 0.3,1.5,20.0,4); // Braco Esquerda
	       	   glPushMatrix();
	       	   	   //Cotovelo Esquerda
	       	   	   glColor3f(0.0, 0.0, 1.0);  
       	   	   	   glRotatef(-90, 0.0, 1.0, 0.0);
		   	   	   glTranslatef(0.0, 0.0, 0.0);
       	   	   	   glutSolidSphere(0.5,  20.0,  20.0); //Cotovelo Esquerda
       	   	   	   //AnteBraco Esquerda
       	   	   	   glPushMatrix();
       	   	   	   	   glTranslatef(-1.5, 0.0, 0.0);
    		   	   	   glRotatef(90, 0.0, 1.0, 0.0);
	           	   	   glColor3f(1.0, 0.0, 0.0);
       	   	   	   	   GLUquadric *objAnteBracoEsquerda = gluNewQuadric();
	       	   	   	   gluCylinder(objAnteBracoEsquerda, 0.3, 0.3,1.5,20.0,4); //AnteBraco Esquerda
	       	   	   	   //Mao Esquerda
					   glColor3f(0.0, 0.0, 1.0);  
       	   	   	   	   glRotatef(-90, 0.0, 1.0, 0.0);
		   	   	   	   glTranslatef(-0.5, 0.0, 0.0);
       	   	   	   	   glutSolidSphere(0.5,  20.0,  20.0); //Mao Esquerda
       	   	   	   glPopMatrix();
	       	   glPopMatrix();
           glPopMatrix();
	      glPushMatrix();
	      	//Pescoco
	        glColor3f(1.0, 0.0, 0.0);  
		 	glTranslatef(0.0, 1.5, 0.0);
			glRotatef(90, 1.0, 0.0, 0.0);
  	   	    GLUquadric *objPescoco = gluNewQuadric();
       	    gluCylinder(objPescoco, 0.3, 0.3,1.0,20.0,4);//Pescoco
       	    //Cabeca
			glColor3f(0.0, 0.0, 1.0);  
			glRotatef(-90, 1.0, 0.0, 0.0);
       	    glTranslatef(0.0, 0.5, 0.0);
       	    glutSolidSphere(1.0,  20.0,  20.0); //Mao Esquerda
		 glPopMatrix();  
		glPopMatrix();
    glPopMatrix();
}

void desenhaEsfera(){
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, texture_id[5]);
		glColor4f(1.0, 1.0, 1.0, 0.8);
		GLUquadric *objEsfera = gluNewQuadric();
		gluQuadricTexture(objEsfera, GLU_FILL);
		gluQuadricTexture(objEsfera, true);
		gluSphere(objEsfera, 500, 1000, 1000);
	 glPopMatrix();
	 	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, texture_id[0]);
		glRotatef(90, 1.0, 0.0,0.0);
		GLUquadric *objChaoEsfera = gluNewQuadric();
		gluQuadricTexture(objChaoEsfera, GLU_FILL);
		gluQuadricTexture(objChaoEsfera, true);
		gluDisk(objChaoEsfera, 0.0, 500, 1000, 1);
	 glPopMatrix();
}

// Fun??o callback chamada para fazer o desenho
void Desenha(void)
{
	// Limpa a janela e o depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT);
    
    desenhaCasa();
    desenhaEsfera();
    desenhaHumanoide(posicaoHumanoide);
    
    glutSwapBuffers();
}

// Inicializa par?metros de rendering
void Inicializa (void)
{ 
	GLfloat luzAmbiente[4]={0.6,0.6,0.6,1.0}; 
	GLfloat luzDifusa[4]={0.7,0.7,0.7,1.0};		 // "cor" 
	GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};// "brilho" 
	GLfloat posicaoLuz[4]={0.0, 20.0, 20.0, 1.0};

	// Capacidade de brilho do material
	GLfloat especularidade[4]={1.0,1.0,1.0,1.0}; 
	GLint especMaterial = 60;

 	// Especifica que a cor de fundo da janela ser? preta
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	
	// Habilita o modelo de coloriza??o de Gouraud
	glShadeModel(GL_SMOOTH);

	// Define a reflet?ncia do material 
	glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
	// Define a concentra??o do brilho
	glMateriali(GL_FRONT,GL_SHININESS,especMaterial);

	// Ativa o uso da luz ambiente 
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	// Define os par?metros da luz de n?mero 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente); 
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );

	// Habilita a defini??o da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de ilumina??o
	glEnable(GL_LIGHTING);  
	// Habilita a luz de n?mero 0
	glEnable(GL_LIGHT0);
	// Habilita o depth-buffering
	glEnable(GL_DEPTH_TEST);

    //angle=45;
    ANGULO = 45;
    rotX = rotY = 0;
    obsX = obsY = 0;
    obsZ = 60;//Voltar para 10
    escalaX = escalaY = escalaZ = 1;
}

// Fun??o usada para especificar o volume de visualiza??o
void EspecificaParametrosVisualizacao(void) //equivalente ao posiciona observador
{
	// Especifica sistema de coordenadas de proje??o
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de proje??o
	glLoadIdentity();

	// Especifica a proje??o perspectiva
    //gluPerspective(angle,fAspect,0.4,500);
    gluPerspective(ANGULO, ASPECTO, 0.4, 1000);

	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();

	// Especifica posi??o do observador e do alvo
    //gluLookAt(0,80,200, 0,0,0, 0,1,0);
    //gluLookAt(obsX, obsY, obsZ, 0,0,0, 0,1,0);
    glTranslatef(-obsX, -obsY, -obsZ);/*Translata a câmera para essas variáveis*/
    glRotatef(rotX,1,0,0);/*Rotacionar a câmera para essas coordenadas*/
    glRotatef(rotY,0,1,0); 
}

// Fun??o callback chamada quando o tamanho da janela ? alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Para previnir uma divis?o por zero
	if ( h == 0 ) h = 1;

	// Especifica o tamanho da viewport
    glViewport(0, 0, w, h);
 
	// Calcula a corre??o de aspecto
	//Aspect = (GLfloat)w/(GLfloat)h;
	ASPECTO = (GLfloat)w/(GLfloat)h;

	EspecificaParametrosVisualizacao();
}

// Fun??o callback chamada para gerenciar eventos do mouse
void GerenciaMouse(int button, int state, int x, int y)
{
	if(state == GLUT_DOWN){
		x_ini = x;
        y_ini = y;
        obsX_ini = obsX;
        obsY_ini = obsY;
        obsZ_ini = obsZ;
        rotX_ini = rotX;
        rotY_ini = rotY;
		bot = button;
	}
	else bot = -1;
	EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}

void motion(int x, int y){
    if(bot == GLUT_LEFT_BUTTON){//Rota??o
        int deltaX = x_ini - x;
        int deltaY = y_ini - y; 
        rotX = rotX_ini - deltaY/ SENS_ROT;
        rotY = rotY_ini - deltaX/ SENS_ROT;
     }
     else if (bot == GLUT_RIGHT_BUTTON){//Zoom
         int deltaZ = y_ini - y;
         obsZ = obsZ_ini + deltaZ/ SENS_OBS;
     }
     else if (bot == GLUT_MIDDLE_BUTTON){//Correr
         int deltaX = x_ini - x;
         int deltaY = y_ini - y;
         obsX = obsX_ini + deltaX/ SENS_TRANS;
         obsY = obsY_ini + deltaY/ SENS_TRANS;
     }
     EspecificaParametrosVisualizacao();
     glutPostRedisplay();
}

void Movimento()
{
    static double passo = 0.0;
    PD = 20.0 * sin(passo * GRAU_RAD); // Movimenta perna direita
    OD = -30.0 * sin(passo * GRAU_RAD); // Movimenta ombro direito
    PE = -20.0 * sin(passo * GRAU_RAD); // Movimenta perna esquerda
    OE = 30.0 * sin(passo * GRAU_RAD);  // Movimenta ombro direito

    passo = fmod(passo + 8.0, 360.0); // incrementa o passo na velocidade 8

}

static void key(unsigned char key, int x, int y){
	switch (key){
	    case 'q':
	        exit(0);
	        break;
	    case 'w':
	    	if(abrePorta){
				abrePorta = false;
			} else {
				abrePorta = true;
			}
			break;
		 case 's':
		 	if(abreJanela){
				abreJanela = false;
			} else {
				abreJanela = true;
			}
			break;
        case 'z':
           Movimento();
           if(anguloHumanoide <= 0) {
		   	   posicaoHumanoide -= 1.0;
		   } else {
			   	posicaoHumanoide += 1.0;
		   }
           break;
       case 'x':
       		if(rotacionaHumanoide){
				rotacionaHumanoide = false;
			} else {
				rotacionaHumanoide = true;
			}
		   break; 
    }
	glutPostRedisplay();
}

static void idle(void){
	   if(!abrePorta && anguloPorta > 0){
		   anguloPorta -= 0.3;
	   } else if (abrePorta && anguloPorta < 90){
		   anguloPorta += 0.3;
	   }
	   if(!abreJanela && anguloJanela > 0){
		   anguloJanela -= 0.3;
	   } else if (abreJanela && anguloJanela < 150){
		   anguloJanela += 0.3;
	   }
	   if(!rotacionaHumanoide && anguloHumanoide > 0){
		   anguloHumanoide -= 1.0;
	   } else if (rotacionaHumanoide && anguloHumanoide < 180){
		   anguloHumanoide += 1.0;
	   }
       glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1600,800);
	glutCreateWindow("Casa");
	initTexture ();
	glutDisplayFunc(Desenha);
    glutReshapeFunc(AlteraTamanhoJanela);
	glutMouseFunc(GerenciaMouse);
	glutMotionFunc(motion);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);
	Inicializa();
	glutMainLoop();
}


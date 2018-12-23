#define ALTURA_PAREDES = 40.0

class Casa{
		
    private:
		double corTelhado[4];
		double alturaParedes;
		double corDaParede[4];
		double corDoChao[4];
		double texturaJanela[4];
		
	public:
		bool abrePorta;
		double anguloPorta;
		bool abreJanela;
		double anguloJanela;
			
		Casa(){
			alturaParedes = 40.0;
			inicializaTexturas();
		}
	
		void desenhaPorta(){
		   	glPushMatrix();	 	
					glTranslatef(25.0, 0.0, 20.0); 
		            glColor4f(corTelhado[0], corTelhado[1], corTelhado[2], corTelhado[3]);	
			    	glRotatef(anguloPorta, 0.0, 1.0, 0.0);
			    	glBegin(GL_QUADS);
			    	glVertex3f(0.0, 0.0, 0.0);
			    	glVertex3f(10.0, 0.0, 0.0);
			    	glVertex3f(10.0, 15.0, 0.0);
			    	glVertex3f(0.0, 15.0, 0.0);
			    	glEnd();
		    glPopMatrix();
		}
		
		void desenhaJanela(float x, float y, float z, char tipo){
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
		            glColor4f(corTelhado[0], corTelhado[1], corTelhado[2], corTelhado[3]);	 
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
					glColor4f(corTelhado[0], corTelhado[1], corTelhado[2], corTelhado[3]);	 
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
					glColor4f(corTelhado[0], corTelhado[1], corTelhado[2], corTelhado[3]);	 
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
		            glColor4f(corTelhado[0], corTelhado[1], corTelhado[2], corTelhado[3]);	 
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
		
		void desenhaPiso(float y){
			glPushMatrix();
		            glColor4f(corDoChao[0], corDoChao[1], corDoChao[2], corDoChao[3]);	 
			    	glBegin(GL_QUADS);
			    	glVertex3f(0.0, y, 0.0);
			    	glVertex3f(20.0, y, 0.0);
			    	glVertex3f(20.0, y, 40.0);
			    	glVertex3f(0.0, y, 40.0);
			    	glEnd();
		        glPopMatrix();
		        glPushMatrix();
		            glColor4f(corDoChao[0], corDoChao[1], corDoChao[2], corDoChao[3]);	 
			    	glBegin(GL_QUADS);
			    	glVertex3f(20.0, y, 0.0);
			    	glVertex3f(80.0, y, 0.0);
			    	glVertex3f(80.0, y, 20.0);
			    	glVertex3f(20.0, y, 20.0);
			    	glEnd();
		        glPopMatrix();
		        glPushMatrix();
		            glColor4f(corDoChao[0], corDoChao[1], corDoChao[2], corDoChao[3]);	 
			    	glBegin(GL_QUADS);
			    	glVertex3f(60.0, y, 20.0);
			    	glVertex3f(60.0, y, 40.0);
			    	glVertex3f(80.0, y, 40.0);
			    	glVertex3f(80.0, y, 20.0);
			    	glEnd();
		        glPopMatrix();
		}
		
		void desenhaPisoAndares(){
			desenhaPiso(0.0);
			desenhaPiso(20.0);
		}
		
		void desenhaContorno(){
			glLineWidth(1.0);
			glColor3f(0.0, 0.0, 0.0);
			glPushMatrix();
				glBegin(GL_LINES);
		    	glVertex3f(0.0, 0.0, 0.0);
		    	glVertex3f(0.0, 40.0, 0.0);
		    	glEnd();
		    glPopMatrix();
			glPushMatrix();
				glBegin(GL_LINES);
		    	glVertex3f(0.0, 0.0, 40.0);
		    	glVertex3f(0.0, 40.0, 40.0);
		    	glEnd();
		    glPopMatrix();
			glPushMatrix();
			   	glBegin(GL_LINES);
		    	glVertex3f(20.0, 0.0, 40.0);
		    	glVertex3f(20.0, 40.0, 40.0);
		    	glEnd();
		    glPopMatrix();
			glPushMatrix();
			   	glBegin(GL_LINES);
		    	glVertex3f(20.1, 0.0, 20.1);
		    	glVertex3f(20.1, 40.0, 20.1);
		    	glEnd();
		    glPopMatrix();
		    glPushMatrix();
			   	glBegin(GL_LINES);
		    	glVertex3f(59.9, 0.0, 20.1);
		    	glVertex3f(59.9, 40.0, 20.1);
		    	glEnd();
		    glPopMatrix();
		    glPushMatrix();
			   	glBegin(GL_LINES);
		    	glVertex3f(60.1, 0.0, 40.1);
		    	glVertex3f(60.1, 40.0, 40.1);
		    	glEnd();
		    glPopMatrix();
			glPushMatrix();
			   	glBegin(GL_LINES);
		    	glVertex3f(80.0, 0.0, 40.0);
		    	glVertex3f(80.0, 40.0, 40.0);
		    	glEnd();
		    glPopMatrix();
		    glPushMatrix();
			   	glBegin(GL_LINES);
		    	glVertex3f(80.0, 0.0, 0.0);
		    	glVertex3f(80.0, 40.0, 0.0);
		    	glEnd();
		    glPopMatrix();
		    glPushMatrix();
			   	glBegin(GL_LINES);
		    	glVertex3f(20.1, 0.0, 20.1);
		    	glVertex3f(20.1, 0.0, 40.1);
		    	glEnd();
		    glPopMatrix();
		    glPushMatrix();
			   	glBegin(GL_LINES);
		    	glVertex3f(20.0, 0.0, 20.1);
		    	glVertex3f(60.0, 0.0, 20.1);
		    	glEnd();
		    glPopMatrix();
		    glPushMatrix();
			   	glBegin(GL_LINES);
		    	glVertex3f(59.9, 0.0, 20.0);
		    	glVertex3f(59.9, 0.0, 40.0);
		    	glEnd();
		    glPopMatrix();
		    glPushMatrix();
			   	glBegin(GL_LINES);
		    	glVertex3f(5.0, 5.0, 40.1);
		    	glVertex3f(15.0, 5.0, 40.1);
		   		glVertex3f(15.0, 15.0, 40.1);
		    	glVertex3f(5.0, 15.0, 40.1);
		    	glVertex3f(15.0, 5.0, 40.1);
		   		glVertex3f(15.0, 15.0, 40.1);
		    	glEnd();
		    glPopMatrix();
			    glPushMatrix();
			   	glBegin(GL_LINES);
		    	glVertex3f(5.0, 25.0, 40.1);
		    	glVertex3f(15.0, 25.0, 40.1);
		   		glVertex3f(15.0, 35.0, 40.1);
		    	glVertex3f(5.0, 35.0, 40.1);
		    	glVertex3f(15.0, 25.0, 40.1);
		   		glVertex3f(15.0, 35.0, 40.1);
		    	glEnd();
		    glPopMatrix();
		    glPopMatrix();
			    glPushMatrix();
			   	glBegin(GL_LINES);
		    	glVertex3f(65.0, 25.0, 40.1);
		    	glVertex3f(75.0, 25.0, 40.1);
		   		glVertex3f(75.0, 35.0, 40.1);
		    	glVertex3f(65.0, 35.0, 40.1);
		    	glVertex3f(65.0, 25.0, 40.1);
		   		glVertex3f(65.0, 35.0, 40.1);
		    	glEnd();
			glPopMatrix();
			    glPushMatrix();
			   	glBegin(GL_LINES);
		    	glVertex3f(65.0, 5.0, 40.1);
		    	glVertex3f(75.0, 5.0, 40.1);
		   		glVertex3f(75.0, 15.0, 40.1);
		    	glVertex3f(65.0, 15.0, 40.1);
		    	glVertex3f(65.0, 5.0, 40.1);
		   		glVertex3f(65.0, 15.0, 40.1);
		    	glEnd();
		    glPopMatrix();    
		}
	
	public: void desenhaCasa(){
			//Mesa
		    glPushMatrix();
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
			//Pé da mesa
		    glPushMatrix();
		        glColor3f(0.5, 0.5, 0.5);
		        glTranslatef(5.0,4.0,5.0);
		        glRotatef(90.0,1.0,0.0,0.0);
		        GLUquadric *obj = gluNewQuadric();
				gluCylinder(obj,1.0,1.0,4.0,20.0,4);
		    glPopMatrix();
		    //Chão
			desenhaPisoAndares();
		    glPushMatrix();
		        glColor4f(0.0, 0.6, 0.3, 0.8);	 
		    	glBegin(GL_QUADS);
		    	glVertex3f(20.0, 0.0, 20.0);
		    	glVertex3f(60.0, 0.0, 20.0);
		    	glVertex3f(60.0, 0.0, 40.0);
		    	glVertex3f(20.0, 0.0, 40.0);
		    	glEnd();
		    glPopMatrix();
			//Paredes
		    // Parede Esqueda
			glPushMatrix();
		        glColor4f(corDaParede[0], corDaParede[1], corDaParede[2], corDaParede[4]);	 
		    	glBegin(GL_QUADS);
		    	glVertex3f(0.0, 0.0, 0.0);
		    	glVertex3f(0.0, 0.0, 40.0);
		    	glVertex3f(0.0, alturaParedes, 40.0);
		    	glVertex3f(0.0, alturaParedes, 0.0);
		    	glEnd();
		    glPopMatrix();
		    // Parede Fundo
		    glPushMatrix();
		        glColor4f(corDaParede[0], corDaParede[1], corDaParede[2], corDaParede[4]);	 
		    	glBegin(GL_QUADS);
		    	glVertex3f(0.0, 0.0, 0.0);
		    	glVertex3f(80.0, 0.0, 0.0);
		    	glVertex3f(80.0, alturaParedes, 0.0);
		    	glVertex3f(0.0, alturaParedes, 0.0);
		    	glEnd();
		    glPopMatrix();
		    // Parede Direita
		    glPushMatrix();
		        glColor4f(corDaParede[0], corDaParede[1], corDaParede[2], corDaParede[4]);	 
		    	glBegin(GL_QUADS);
		    	glVertex3f(80.0, 0.0, 0.0);
		    	glVertex3f(80.0, 0.0, 40.0);
		    	glVertex3f(80.0, alturaParedes, 40.0);
		    	glVertex3f(80.0, alturaParedes, 0.0);
		    	glEnd();
		    glPopMatrix();
		    //Parede Frontal Esquerda
		    glPushMatrix();
		        glColor4f(corDaParede[0], corDaParede[1], corDaParede[2], corDaParede[4]);	 
		    	glBegin(GL_QUADS);
		    	glVertex3f(0.0, 0.0, 40.0);
		    	glVertex3f(20.0, 0.0, 40.0);
		    	glVertex3f(20.0, 5.0, 40.0);
		    	glVertex3f(0.0, 5.0, 40.0);
		    	glEnd();
		    glPopMatrix();
		    glPushMatrix();
		        glColor4f(corDaParede[0], corDaParede[1], corDaParede[2], corDaParede[4]);	 
		    	glBegin(GL_QUADS);
		    	glVertex3f(0.0, 0.0, 40.0);
		    	glVertex3f(5.0, 0.0, 40.0);
		    	glVertex3f(5.0, alturaParedes, 40.0);
		    	glVertex3f(0.0, alturaParedes, 40.0);
		    	glEnd();
		    glPopMatrix();
		    glPushMatrix();
		        glColor4f(corDaParede[0], corDaParede[1], corDaParede[2], corDaParede[4]);	 
		    	glBegin(GL_QUADS);
		    	glVertex3f(15.0, 0.0, 40.0);
		    	glVertex3f(20.0, 0.0, 40.0);
		    	glVertex3f(20.0, alturaParedes, 40.0);
		    	glVertex3f(15.0, alturaParedes, 40.0);
		    	glEnd();
		    glPopMatrix();
		    glPushMatrix();
		        glColor4f(corDaParede[0], corDaParede[1], corDaParede[2], corDaParede[4]);	 
		    	glBegin(GL_QUADS);
		    	glVertex3f(5.0, 15.0, 40.0);
		    	glVertex3f(15.0, 15.0, 40.0);
		    	glVertex3f(15.0, 25.0, 40.0);
		    	glVertex3f(5.0, 25.0, 40.0);
		    	glEnd();
		    glPopMatrix();
		    glPushMatrix();
		        glColor4f(corDaParede[0], corDaParede[1], corDaParede[2], corDaParede[4]);	 
		    	glBegin(GL_QUADS);
		    	glVertex3f(5.0, 35.0, 40.0);
		    	glVertex3f(15.0, 35.0, 40.0);
		    	glVertex3f(15.0, 40.0, 40.0);
		    	glVertex3f(5.0, 40.0, 40.0);
		    	glEnd();
		    glPopMatrix();
		    //Parede Frontal Interna Esquerda
		    glPushMatrix();
		        glColor4f(corDaParede[0], corDaParede[1], corDaParede[2], corDaParede[4]);	 
		    	glBegin(GL_QUADS);
		    	glVertex3f(20.0, 0.0, 40.0);
		    	glVertex3f(20.0, 0.0, 20.0);
		    	glVertex3f(20.0, alturaParedes, 20.0);
		    	glVertex3f(20.0, alturaParedes, 40.0);
		    	glEnd();
		    glPopMatrix();
		    //Parede Frontal
		    glPushMatrix();
		        glColor4f(corDaParede[0], corDaParede[1], corDaParede[2], corDaParede[4]);	 
		    	glBegin(GL_QUADS);
		    	glVertex3f(20.0, 0.0, 20.0);
		    	glVertex3f(25.0, 0.0, 20.0);
		    	glVertex3f(25.0, alturaParedes, 20.0);
		    	glVertex3f(20.0, alturaParedes, 20.0);
		    	glEnd();
		    glPopMatrix();
		    glPushMatrix();
		        glColor4f(corDaParede[0], corDaParede[1], corDaParede[2], corDaParede[4]);	 
		    	glBegin(GL_QUADS);
		    	glVertex3f(20.0, 15.0, 20.0);
		    	glVertex3f(35.0, 15.0, 20.0);
		    	glVertex3f(35.0, alturaParedes, 20.0);
		    	glVertex3f(20.0, alturaParedes, 20.0);
		    	glEnd();
		    glPopMatrix();
		    glPushMatrix();
		        glColor4f(corDaParede[0], corDaParede[1], corDaParede[2], corDaParede[4]);	 
		    	glBegin(GL_QUADS);
		    	glVertex3f(35.0, 0.0, 20.0);
		    	glVertex3f(80.0, 0.0, 20.0);
		    	glVertex3f(80.0, alturaParedes, 20.0);
		    	glVertex3f(35.0, alturaParedes, 20.0);
		    	glEnd();
		    glPopMatrix();
		    //Parede Frontal Interna Direita
		    glPushMatrix();
		        glColor4f(corDaParede[0], corDaParede[1], corDaParede[2], corDaParede[4]);	 
		    	glBegin(GL_QUADS);
		    	glVertex3f(60.0, 0.0, 20.0);
		    	glVertex3f(60.0, 0.0, 40.0);
		    	glVertex3f(60.0, alturaParedes, 40.0);
		    	glVertex3f(60.0, alturaParedes, 20.0);
		    	glEnd();
		    glPopMatrix();
		    //Parede Frontal Direita
			glPushMatrix();
		        glColor4f(corDaParede[0], corDaParede[1], corDaParede[2], corDaParede[4]);	 
		    	glBegin(GL_QUADS);
		    	glVertex3f(60.0, 0.0, 40.0);
		    	glVertex3f(80.0, 0.0, 40.0);
		    	glVertex3f(80.0, 5.0, 40.0);
		    	glVertex3f(60.0, 5.0, 40.0);
		    	glEnd();
		    glPopMatrix();
		    glPushMatrix();
		        glColor4f(corDaParede[0], corDaParede[1], corDaParede[2], corDaParede[4]);	 
		    	glBegin(GL_QUADS);
		    	glVertex3f(60.0, 0.0, 40.0);
		    	glVertex3f(65.0, 0.0, 40.0);
		    	glVertex3f(65.0, alturaParedes, 40.0);
		    	glVertex3f(60.0, alturaParedes, 40.0);
		    	glEnd();
		    glPopMatrix();
		    glPushMatrix();
		        glColor4f(corDaParede[0], corDaParede[1], corDaParede[2], corDaParede[4]);	 
		    	glBegin(GL_QUADS);
		    	glVertex3f(75.0, 0.0, 40.0);
		    	glVertex3f(80.0, 0.0, 40.0);
		    	glVertex3f(80.0, alturaParedes, 40.0);
		    	glVertex3f(75.0, alturaParedes, 40.0);
		    	glEnd();
		    glPopMatrix();
		    glPushMatrix();
		        glColor4f(corDaParede[0], corDaParede[1], corDaParede[2], corDaParede[4]);	 
		    	glBegin(GL_QUADS);
		    	glVertex3f(65.0, 15.0, 40.0);
		    	glVertex3f(75.0, 15.0, 40.0);
		    	glVertex3f(75.0, 25.0, 40.0);
		    	glVertex3f(65.0, 25.0, 40.0);
		    	glEnd();
		    glPopMatrix();
		    glPushMatrix();
		        glColor4f(corDaParede[0], corDaParede[1], corDaParede[2], corDaParede[4]);	 
		    	glBegin(GL_QUADS);
		    	glVertex3f(65.0, 35.0, 40.0);
		    	glVertex3f(75.0, 35.0, 40.0);
		    	glVertex3f(75.0, 40.0, 40.0);
		    	glVertex3f(65.0, 40.0, 40.0);
		    	glEnd();
		    glPopMatrix();     
		    //Telhado
		    //TelhadoEsquerdo
			glPushMatrix(); 
		        glColor4f(corTelhado[0], corTelhado[1], corTelhado[2], corTelhado[3]);	 
		    	glBegin(GL_TRIANGLES);
		    	glVertex3f(0.0, alturaParedes, 40.0);
		    	glVertex3f(10.0, 50.0, 40.0);
		    	glVertex3f(20.0, alturaParedes, 40.0);
		    	glEnd();
		    glPopMatrix();
			glPushMatrix();	 
		        glColor4f(corTelhado[0], corTelhado[1], corTelhado[2], corTelhado[3]);	 
		    	glBegin(GL_QUADS);
		    	glVertex3f(0.0, alturaParedes, 40.0);
		    	glVertex3f(10.0, 50.0, 40.0);
		    	glVertex3f(10.0, 50.0, 0.0);
		    	glVertex3f(0.0, alturaParedes, 0.0);
		    	glEnd();
		    glPopMatrix();
		    glPushMatrix();	 
		        glColor4f(corTelhado[0], corTelhado[1], corTelhado[2], corTelhado[3]);	 
		    	glBegin(GL_QUADS);
		    	glVertex3f(20.0, alturaParedes, 40.0);
		    	glVertex3f(10.0, 50.0, 40.0);
		    	glVertex3f(10.0, 50.0, 0.0);
		    	glVertex3f(20.0, alturaParedes, 0.0);
		    	glEnd();
		    glPopMatrix();
		    glPushMatrix(); 
		        glColor4f(corTelhado[0], corTelhado[1], corTelhado[2], corTelhado[3]);	 
		    	glBegin(GL_TRIANGLES);
		    	glVertex3f(0.0, alturaParedes, 0.0);
		    	glVertex3f(10.0, 50.0, 0.0);
		    	glVertex3f(20.0, alturaParedes, 0.0);
		    	glEnd();
		    glPopMatrix();
		    //TelhadoDireito
		    glPushMatrix(); 
		        glColor4f(corTelhado[0], corTelhado[1], corTelhado[2], corTelhado[3]);	 
		    	glBegin(GL_TRIANGLES);
		    	glVertex3f(60, alturaParedes, 40.0);
		    	glVertex3f(70.0, 50.0, 40.0);
		    	glVertex3f(80.0, alturaParedes, 40.0);
		    	glEnd();
		    glPopMatrix();
		    glPushMatrix();	 
		        glColor4f(corTelhado[0], corTelhado[1], corTelhado[2], corTelhado[3]);	 
		    	glBegin(GL_QUADS);
		    	glVertex3f(60, alturaParedes, 40.0);
		    	glVertex3f(70.0, 50.0, 40.0);
		    	glVertex3f(70.0, 50.0, 0.0);
		    	glVertex3f(60, alturaParedes, 0.0);
		    	glEnd();
		    glPopMatrix();
		    glPushMatrix();	 
		        glColor4f(corTelhado[0], corTelhado[1], corTelhado[2], corTelhado[3]);	 
		    	glBegin(GL_QUADS);
		    	glVertex3f(80.0, alturaParedes, 40.0);
		    	glVertex3f(70.0, 50.0, 40.0);
		    	glVertex3f(70.0, 50.0, 0.0);
		    	glVertex3f(80.0, alturaParedes, 0.0);
		    	glEnd();
		    glPopMatrix();
			glPushMatrix(); 
		        glColor4f(corTelhado[0], corTelhado[1], corTelhado[2], corTelhado[3]);	 
		    	glBegin(GL_TRIANGLES);
		    	glVertex3f(60, alturaParedes, 0.0);
		    	glVertex3f(70.0, 50.0, 0.0);
		    	glVertex3f(80.0, alturaParedes, 0.0);
		    	glEnd();
		    glPopMatrix();
		    //Telhado Meio
		    glPushMatrix();	 
		        glColor4f(corTelhado[0], corTelhado[1], corTelhado[2], corTelhado[3]);	 
		    	glBegin(GL_QUADS);
		    	glVertex3f(20.0, alturaParedes, 0.0);
		    	glVertex3f(10.0, 50.0, 0.0);
		    	glVertex3f(70.0, 50.0, 0.0);
		    	glVertex3f(60.0, alturaParedes, 0.0);
		    	glEnd();
		    glPopMatrix();
			glPushMatrix();	 
		        glColor4f(corTelhado[0], corTelhado[1], corTelhado[2], corTelhado[3]);	 
		    	glBegin(GL_QUADS);
		    	glVertex3f(20.0, alturaParedes, 20.0);
		    	glVertex3f(10.0, 50.0, 0.0);
		    	glVertex3f(70.0, 50.0, 0.0);
		    	glVertex3f(60.0, alturaParedes, 20.0);
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
		        glColor4f(corTelhado[0], corTelhado[1], corTelhado[2], corTelhado[3]);	 
		    	glBegin(GL_TRIANGLES);
		    	glVertex3f(40.0, 20.0, 22.0);
		    	glVertex3f(40.0, 20.0, 40.0);
		    	glVertex3f(40.0, 30.0, 31.5);
		    	glEnd();
		    glPopMatrix();
			glPushMatrix();	 
		        glColor4f(corTelhado[0], corTelhado[1], corTelhado[2], corTelhado[3]);	 
		    	glBegin(GL_QUADS);
		    	glVertex3f(40.0, 20.0, 40.0);
		    	glVertex3f(40.0, 30.0, 31.5);
		    	glVertex3f(60.0, 30.0, 31.5);
		    	glVertex3f(60.0, 20.0, 40.0);
		    	glEnd();
		    glPopMatrix();	
			glPushMatrix();	 
		        glColor4f(corTelhado[0], corTelhado[1], corTelhado[2], corTelhado[3]);	 
		    	glBegin(GL_QUADS);
		    	glVertex3f(40.0, 20.0, 22.0);
		    	glVertex3f(40.0, 30.0, 31.5);
		    	glVertex3f(60.0, 30.0, 31.5);
		    	glVertex3f(60.0, 20.0, 22.5);
		    	glEnd();
		    glPopMatrix();
			desenhaPorta();
			desenhaJanelas();
			desenhaContorno();
	}
	
	void inicializaTexturas(){
		
		corTelhado[0] = 0.3;
		corTelhado[1] = 0.2;
		corTelhado[2] = 0.0;
		corTelhado[3] = 1.0;
		
		corDaParede[0] = 0.8;
		corDaParede[1] = 0.8;
		corDaParede[2] = 1.0;
		corDaParede[3] = 1.0;
		
		corDoChao[0] = 1.0;
		corDoChao[1] = 1.0;
		corDoChao[2] = 0.9;
		corDoChao[3] = 1.0; 

		texturaJanela[0] = 1.0;
		texturaJanela[1] = 1.0;
		texturaJanela[2] = 1.0;
		texturaJanela[3] = 0.5;
		
	}
}
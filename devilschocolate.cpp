#include <iostream>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include<stdlib.h>
#include<GL/freeglut.h>

int i, k, l;

// ID to detect which scene the story is in.
int SCENE_ID;
#define PI 3.141592653589

GLfloat title_fade, intro_next_text_appear, summary_para1_fade, summary_para2_fade, summary_para3_fade, summary_para4_fade
, summary_next_text_appear, gy_chap_fade, gy_title_fade, hs_subtitle_1_appear, ps_chap_fade, ps_subtitle_1_appear, ps_subtitle_2_appear;

GLfloat trans_x_chap1, trans_x_title1, schoolboy_y = 5220, schoolboy_x = 1150, sun_move_left, trans_x_chap2, ps_title_fade, trans_y_title2,
trans_x_kid1, trans_x_kid2, trans_x_kid3, trans_x_ball, trans_subtitle_1_done, trans_x_chap3, trans_x_title2, trans_x_title3;

GLfloat window_top_r = 59, window_top_g = 91, window_top_b = 132,
window_bottom_r = 97, window_bottom_g = 131, window_bottom_b = 159,
sky_r = 12, sky_g = 172, sky_b = 232,
grass_r = 82, grass_g = 163, grass_b = 42,
sun_r = 251, sun_g = 255, sun_b = 163;

bool sun_moved_half, chapter_1_done, chapter_2_done, chapter_3_done, chapter_4_done, chapter_5_done, sun_has_set,
tuition_done, stars_are_made, wp_tb_big;

int star_alpha, no_of_stars, stars_array[40][2];

void circle_a(GLfloat x, GLfloat y, GLdouble radius)
{
	float x2, y2;
	float angle;
	glPointSize(2.0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y);
	for (angle = 1.0; angle < 361.0f; angle += 0.2)
	{
		x2 = x + sin(angle)*radius;
		y2 = y + cos(angle)*radius;
		glVertex2f(x2, y2);
	}
	glEnd();
}

void Head(float x1, float y1, double r)
{
	float x2, y2, angle;
	glPointSize(1);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x1, y1);
	for (angle = -1.58; angle <= 1.625; angle += 0.2)
	{
		x2 = x1 + sin(angle)*r;
		y2 = y1 + cos(angle)*r*1.7;
		glVertex2f(x2, y2);
	}
	glEnd();
}

void cloud_a(int x, int y, int r, int i)
{
	circle_a(x + i, y, r);
	circle_a(x + i, y, r);
	circle_a(x + 10 + i, y + 30, r - 10);
	circle_a(x + 55 + i, y + 20, r + 10);
	circle_a(x + 100 + i, y + 25, r - 5);


}
void tree2_a(int x, int y)
{
	circle_a(x - 5, y + 100, 35);
	/*circle_a(x - 5, y + 100, 35);*/
	circle_a(x - 30, y + 120, 35);
	circle_a(x - 8, y + 150, 35);
	circle_a(x + 40, y + 100, 35);
	circle_a(x + 35, y + 150, 35);
	glColor3ub(184, 134, 11);
	glBegin(GL_POLYGON);
	glVertex2i(x, y);
	glVertex2i(x + 30, y);
	glVertex2i(x + 28, y + 80);
	glVertex2i(x + 8, y + 80);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2i(x + 10, y + 80);
	glVertex2i(x + 28, y + 80);
	glVertex2i(x + 38, y + 110);
	glVertex2i(x + 28, y + 110);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2i(x + 28, y + 80);
	glVertex2i(x + 8, y + 80);
	glVertex2i(x - 15, y + 100);
	glVertex2i(x - 15, y + 110);
	glEnd();

}
void grass_a(int x, int y, int width, int height)
{
	i = x;
	for (l = 0; l < height; l++)
	{
		for (k = 0; k < width; k++)
		{
			glBegin(GL_TRIANGLES);
			glVertex2f(x, y);
			glVertex2f(x + 10, y);
			glVertex2f(x + 5, y + 15);
			glVertex2f(x, y);
			glVertex2f(x + 12, y);
			glVertex2f(x - 5, y + 10);
			glVertex2f(x - 3, y);
			glVertex2f(x + 10, y);
			glVertex2f(x + 15, y + 10);
			glEnd();
			x += 16;
		}
		y += 8;
		x = i;
	}
}

void sun12(GLfloat r1, GLfloat r2, GLdouble r3)
{

	float x1, y1, x2, y2;
	float angle;
	double radius = r3 + 30;
	x1 = r1, y1 = r2;
	glColor3f(1, 1, 0);
	glPointSize(2.0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x1, y1);
	for (angle = 1.0; angle < 361.0f; angle += 0.2)
	{
		x2 = x1 + sin(angle)*radius;
		y2 = y1 + cos(angle)*radius;
		glVertex2f(x2, y2);
	}
	glEnd();
}
void bird(int x, int y)
{
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_TRIANGLES);
	glVertex2f(x + 5, y + 30);
	glVertex2f(x + 3, y + 10);
	glVertex2f(x + 7, y + 10);
	glEnd();
	glColor3f(0.8, 0.5, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(x, y + 30);
	glVertex2f(x + 3, y + 30);
	glVertex2f(x + 5, y + 10);
	glVertex2f(x + 3, y + 10);
	glEnd();
	glColor3f(0.8, 0.5, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(x + 7, y + 30);
	glVertex2f(x + 10, y + 30);
	glVertex2f(x + 7, y + 10);
	glVertex2f(x + 5, y + 10);
	glEnd();
	glColor3f(0.8, 0.5, 0.0);
	glBegin(GL_TRIANGLES);
	glVertex2f(x - 20, y + 26);
	glVertex2f(x, y + 40);
	glVertex2f(x + 3, y + 30);
	glEnd();
	glColor3f(0.8, 0.5, 0.0);
	glBegin(GL_TRIANGLES);
	glVertex2f(x + 7, y + 30);
	glVertex2f(x + 10, y + 40);
	glVertex2f(x + 30, y + 26);
	glEnd();
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(x + 3, y + 10);
	glVertex2f(x + 7, y + 10);
	glVertex2f(x + 10, y);
	glVertex2f(x, y);
	glEnd();

}

// Function to Create Delay
void delay(float secs) {
	float end = clock() / CLOCKS_PER_SEC + secs;
	while ((clock() / CLOCKS_PER_SEC) < end);
}



// Function to drawText1 Text
void drawText1(const char *string,
	GLfloat r, GLfloat g, GLfloat b, GLfloat a,
	GLint x, GLint y,
	GLfloat w, GLfloat h,
	GLfloat strokeSize)
{
	glPushMatrix();

	glColor4f(r, g, b, a);
	glTranslatef(x, y, 0);
	glScalef(w, h, 0);

	glPointSize(strokeSize);
	glLineWidth(strokeSize);

	while (*string)
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, *string++);

	glPopMatrix();

	glLineWidth(1);
	glPointSize(1);
}
void Circle(float x1, float y1, double r)
{
	float x2, y2, angle;
	glPointSize(1);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x1, y1);
	for (angle = 0; angle <= 3 * 3.14; angle += 0.2)
	{
		x2 = x1 + sin(angle)*r;
		y2 = y1 + cos(angle)*r*1.5;
		glVertex2f(x2, y2);
	}
	glEnd();
}

void Arrow(int flag)
{
	if (flag == 1)
		glColor3f(0.8, 0.8, 0.9);				//Arrow 
	else glColor3f(0.54, 0.27, 0.072);
	glLineWidth(2);
	glBegin(GL_LINES);
	glVertex2f(478, 188);
	glVertex2f(435, 200);
	glEnd();
	glBegin(GL_POLYGON);					//Arrow Tail
	glVertex2f(478, 191);
	glVertex2f(481, 190);
	glVertex2f(480, 184);
	glVertex2f(477, 185);
	glVertex2f(471, 190);
	glEnd();

	if (flag == 1)
		glColor3f(1, 1, 0);						//Fire
	else
		glColor3f(0.54, 0.27, 0.072);
	glBegin(GL_POLYGON);
	glVertex2f(429, 198);
	glVertex2f(427, 202);
	glVertex2f(431, 208);
	glVertex2f(435, 210);
	glVertex2f(437, 200);
	glVertex2f(435, 195);
	glEnd();

	if (flag == 1)
		glColor3f(0.65, 0.65, 0);
	else glColor3f(0.54, 0.27, 0.072);
	glBegin(GL_POLYGON);					//Arrow Head
	glVertex2f(436, 203);
	glVertex2f(435, 197);
	glVertex2f(429, 202);
	glEnd();
}

void drawText(float x, float y, float r, float g, float b, const char *string)
{
	int j = strlen(string);
	//	glLineWidth(20.0);

	glColor3f(r, g, b);//1.0, 0.24902, 0.0

	glRasterPos2f(x, y);
	for (int i = 0; i < j; i++) {

		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}

void drawCircle(GLfloat x, GLfloat y,
	GLfloat r, GLfloat g, GLfloat b,
	GLfloat sx, GLfloat sy,
	GLfloat radius) {
	glPushMatrix();

	glTranslatef(x, y, 0);
	glScalef(sx, sy, 0);

	glBegin(GL_POLYGON);
	glColor3ub(r, g, b);
	for (GLfloat i = 0; i < 360; i += 5)
		glVertex2f(radius * sin(i * PI / 180), radius * cos(i * PI / 180));
	glEnd();

	glPopMatrix();
}
void circle1(GLfloat x, GLfloat y, GLdouble radius) {
	float x2, y2;
	float angle;
	glPointSize(2.0);
	glBegin(GL_TRIANGLE_FAN);
	for (angle = 0.0; angle < 6.3; angle += 0.01)
	{
		x2 = x + sin(angle)*radius;
		y2 = y + cos(angle)*radius;
		glVertex2f(x2, y2);
	}
	glEnd();
}

void arc(GLfloat x, GLfloat y, GLdouble radius, GLfloat i, GLfloat j) {
	//i is intial angle,j is final angle of arc
	float x2, y2;
	float angle;
	glLineWidth(3.0);
	glBegin(GL_LINE_STRIP);
	for (angle = i; angle <= j; angle += 0.01)
	{
		x2 = x + sin(angle)*radius;
		y2 = y + cos(angle)*radius;
		glVertex2f(x2, y2);
	}
	glEnd();
}

void head2() {
	glColor3f(0.6, 0.4, 0.2); //fur
	circle1(1000, 400, 100);
	circle1(800, 600, 100);
	circle1(600, 400, 100);
	circle1(800, 200, 100); 

	circle1(940, 540, 100);
	circle1(660, 540, 100);
	circle1(660, 260, 100);
	circle1(940, 260, 100);

	glColor3f(0.75, 0.5, 0.25);
	circle1(800, 400, 160);  //head

	circle1(670, 530, 50); //ears 
	circle1(930, 530, 50);

	glColor3f(0.2, 0.2, 0.2);
	glBegin(GL_POLYGON);
	glVertex2i(850.0, 400.0);  //nose
	glVertex2i(750.0, 400.0);
	glVertex2i(800.0, 350.0);
	glEnd();



	glColor3f(0.1, 0.1, 0.1);
	arc(750.0, 468.0, 30, 2.2, 4.08); //eyes open
	arc(850.0, 468.0, 30, 2.2, 4.08);
	arc(750.0, 430.0, 30, -0.94, 0.94);
	arc(850.0, 430.0, 30, -0.94, 0.94);
	circle1(742, 448, 10);
	circle1(842, 448, 10);

	glLineWidth(1);     // angry mouth
	glBegin(GL_LINES);
	glVertex2i(800.0, 350.0);
	glVertex2i(800.0, 325.0);
	glEnd();
	glBegin(GL_LINES);
	glVertex2i(800.0, 325.0);
	glVertex2i(720.0, 300.0);
	glEnd();
	glBegin(GL_LINES);
	glVertex2i(800.0, 325.0);
	glVertex2i(880.0, 300.0);
	glEnd();
}



void introduction() {
	// Background
	glClearColor(0.05, 0.05, 0.05, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	// Story Title
	drawText1("********************************************", 1, 1, 1, title_fade, 0, 750, .3, .3, 2);
	drawText1("GOVERNMENT OF INDIA", 8.1, 0.1, 0.1, title_fade, 500, 720, .2, .2, 2);
	drawText1("DAYANANDA SAGAR COLLEGE OF ENGINEERING", 1.0, 4.0, 0.0, title_fade, 100, 670, .3, .4, 4);
	drawText1("THIS CERTIFICATE IS VALID FOR CG PROGJECT ONLY", 1.0, 0.0, 4.0, title_fade, 170, 640, .2, .2, 2);
	drawText1("2710", 1, 1, 1, title_fade, 70, 600, .1, .2, 1);
	drawText1("DIL/188/2019-MUM   Feature", 1, 1, 1, title_fade, 70, 580, .1, .2, 1);
	drawText1("CERTIFICATE NO: D7         DATED:22/04/2019         Category:                                PARENTAL GUIDANCE CG", 0.0, 8.0, 0.0, title_fade, 70, 530, .1, .2, 1);
	drawText1("3T/UA", 1, 1, 1, title_fade, 700, 530, .4, .7, 4);
	drawText1("-", 1, 1, 1, title_fade, 735, 530, .3, .7, 4);
	drawText1("CG AD: DEVILS CHOCOLATE (BE) (COLOR) ", 0.0, 1.0, 4.0, title_fade, 70, 480, .1, .2, 1);
	drawText1("This AD is approved by the DSCE CSE DEPT say that it can used to show the project of cg and can obtain marks ", 1, 1, 1, title_fade, 100, 420, .1, .2, 1);
	drawText1("and mark it to AAT in fullfilment of the project this project contain copy rights and no charater has copyed   ", 1, 1, 1, title_fade, 100, 390, .1, .2, 1);
	drawText1("This was done in the period of 2 months and was apporoved by the DSCE CSE FACULTY and members are as below", 1, 1, 1, title_fade, 100, 360, .1, .2, 1);
	drawText1(" APPROVED BY: ", 1, 1, 1, title_fade, 70, 290, .1, .2, 1);
	drawText1(" Prof. ANITHA M ", 0.0, 1.0, 4.0, title_fade, 210, 250, .1, .2, 1);
	drawText1("Assistant Professor, Dept of CSE", 1, 1, 1, title_fade, 190, 210, .1, .2, 1);
	drawText1(" Prof. SHWETHA M D", 0.0, 1.0, 4.0, title_fade, 210, 170, .1, .2, 1);
	drawText1("Assistant Professor, Dept of CSE", 1, 1, 1, title_fade, 190, 140, .1, .2, 1);
	drawText1("Name of the Applicant: HARISH,NAVYA,VIDYASAGAR", 0.0, 1.0, 4.0, title_fade, 70, 100, .1, .2, 1);
	drawText1("1DS17CS407,1DS17CS419,1DS16CS756", 0.0, 1.0, 4.0, title_fade, 300, 70, .1, .2, 1);
	drawText1("HOD", 1.0, 0.0, 0.0, title_fade, 1050, 110, .2, .2, 5);
	drawText1("DSCE,BANGOLORE", 0.0, 1.0, 00.0, title_fade, 1010, 70, .1, .2, 1);
	drawText1("DR .RAMESH BABU", 1, 1, 1, title_fade, 900, 150, .2, .2, 3);
	drawText1("********************************************", 1, 1, 1, title_fade, 0, 20, .3, .3, 2);

	glFlush();
}

void Screen1() {
	glClearColor(0.05, 0.05, 0.05, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	drawText1("VIDYASAGAR N D", 0, 1, 0, gy_chap_fade, 400 + trans_x_chap1, 500, .3, .3, 4);
	drawText1("Programmer & TESTER ", 1, 1, 1, gy_title_fade, 350 + trans_x_title1, 430, .3, .3, 2);

}
void Screen2() {
	glClearColor(0.05, 0.05, 0.05, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	drawText1("NAVYA R", 1, 0, 1, gy_chap_fade, 450 + trans_x_chap2, 500, .3, .3, 4);
	drawText1("Programmer & AD ART DESIGNER", 1, 1, 1, gy_title_fade, 200 + trans_x_title2, 430, .3, .3, 2);

}

void Screen3() {

	glClearColor(0.05, 0.05, 0.05, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	drawText1("HARISH .P", 1, 1, 0, gy_chap_fade, 480 + trans_x_chap3, 500, .3, .3, 4);
	drawText1("TEAM LEAD,STORY PLAY,PROGRAMMER ", 1, 1, 1, gy_title_fade, 200 + trans_x_title3, 430, .3, .3, 2);
}
void Screenl() {

	glClearColor(0.05, 0.05, 0.05, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	drawText1("DEVILS", 1.0, 0.0, 0.0, title_fade, 450, 470, .7, .7, 7);
	drawText1("CHOCOLATE", 0.7, 0.3, 0.0, title_fade, 600, 370, .5, .5, 5);
	drawText1("BOOSTER guru!!", 2.0, 3.0, 1.0, title_fade, 850, 320, .3, .3, 3);

	glColor3f(1, 1, 1);
	Head(520, 330, 60);
	drawCircle(520, 340, 1, 1, 1, 5, 3, 4);
	glColor3f(0.0, 0, 0.0);
	circle_a(500, 380.0, 10.0);
	glColor3f(0.0, 0, 0.0);
	circle_a(540, 380.0, 10.0);

	glFlush();
}




void Screen0() {
	// Background

	glClearColor(0.0, 0.95, 0.49, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 1250, 0, 1250);

	drawText(450.0, 700.0, 1.1, 2.1, 0.0, "press 'e' for the Demonstration of project");
	glFlush();
}



void scene1(int l)
{
	for (float x = 0; x <= 300; x += 0.2)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glPointSize(5.0);
		//ground

		glColor3f(0.0, 1.0, 0.6);
		glBegin(GL_POLYGON);
		glVertex2f(0.0, 0.0);
		glVertex2f(0.0, 300.0);
		glVertex2f(1280.0, 300.0);
		glVertex2f(1280.0, 0.0);
		glColor3f(0.0, 1.0, 0.0);
		glEnd();

		//sky

		glColor3f(0.1, 1.0, 1.0);
		glBegin(GL_POLYGON);
		glVertex2f(0.0, 300.0);
		glVertex2f(1280.0, 300.0);
		glVertex2f(1280.0, 800.0);
		glVertex2f(0.0, 800.0);
		glEnd();

		//sun

		glColor3f(1.0, 0.7, 0.0);
		circle_a(x, 670.0, 50.0);

		//cloud_a
		glColor3f(1.0, 1.0, 1.0);
		cloud_a(x - 800, 600, 30, -l);
		glColor3f(1.0, 1.0, 1.0);
		cloud_a(x + 800, 680, 30, l);
		glColor3f(1.0, 1.0, 1.0);
		cloud_a(x - 700, 580, 30, -l);
		glColor3f(1.0, 1.0, 1.0);
		cloud_a(x + 50, 680, 30, l);
		glColor3f(1.0, 1.0, 1.0);
		cloud_a(x - 100, 540, 30, l);
		glColor3f(1.0, 1.0, 1.0);
		cloud_a(x + 600, 400, 30, -l);
		glColor3f(1.0, 1.0, 1.0);
		cloud_a(x - 400, 500, 30, -l);
		glColor3f(1.0, 1.0, 1.0);
		cloud_a(x + 300, 440, 30, l);

		// mountains
		glColor3f(0.7, 0.3, 0.0);
		circle_a(213.33, 491.5, 29.5);
		glColor3f(0.7, 0.3, 0.0);
		glBegin(GL_POLYGON);
		glVertex2f(0, 300);
		glVertex2f(183.33, 500);
		glVertex2f(243.33, 500);
		glVertex2f(426.67, 300);
		glEnd();

		glColor3f(0.7, 0.3, 0.0);
		circle_a(640.0, 491.5, 29.5);
		glBegin(GL_POLYGON);
		glVertex2f(426.67, 300);
		glVertex2f(610, 500);
		glVertex2f(670, 500);
		glVertex2f(853.33, 300);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(853.33, 300);
		glVertex2f(1036.6, 500);
		glVertex2f(1096.6, 500);
		glVertex2f(1280, 300);
		glEnd();


		glColor3f(0.7, 0.3, 0.0);
		circle_a(1066.66, 491.5, 29.5);
		glBegin(GL_POLYGON);
		glVertex2f(853.33, 300);
		glVertex2f(1036.6, 500);
		glVertex2f(1096.6, 500);
		glVertex2f(1280, 300);
		glEnd();
		//grass_a
		glColor3f(0, 1, 0);
		grass_a(20, 140, 1, 1);
		grass_a(120, 100, 1, 1);
		grass_a(140, 180, 1, 1);
		grass_a(200, 60, 1, 1);
		grass_a(220, 140, 1, 1);
		grass_a(40, 40, 1, 1);

		grass_a(320, 140, 1, 1);
		grass_a(420, 100, 1, 1);
		grass_a(440, 180, 1, 1);
		grass_a(500, 60, 1, 1);
		grass_a(520, 140, 1, 1);
		grass_a(340, 40, 1, 1);

		grass_a(620, 140, 1, 1);
		grass_a(720, 100, 1, 1);
		grass_a(740, 180, 1, 1);
		grass_a(820, 140, 1, 1);
		grass_a(600, 40, 1, 1);

		glColor3f(0, 1, 0);
		grass_a(820, 140, 1, 1);
		grass_a(920, 100, 1, 1);
		grass_a(940, 180, 1, 1);
		grass_a(1000, 60, 1, 1);
		grass_a(1020, 140, 1, 1);
		grass_a(840, 40, 1, 1);

		glColor3f(0, 1, 0);
		grass_a(1120, 140, 1, 1);
		grass_a(1080, 40, 1, 1);
		grass_a(1180, 80, 1, 1);


		//tree
		glColor3f(0, 1, 0);
		tree2_a(450, 300);
		glColor3f(1, 0.5, 0);
		tree2_a(830, 300);
		glColor3f(0, 0.5, 0);
		tree2_a(30, 300);
		glColor3f(0.5, 0.5, 0);
		tree2_a(1200, 300);
		//house
			//1st 

		glColor3ub(230, 115, 0);
		glBegin(GL_POLYGON);
		glVertex2i(20, 280);                        //left side wall
		glVertex2i(20, 110);
		glVertex2i(150, 85);
		glVertex2i(150, 285);
		glEnd();

		glColor3ub(90, 100, 100);
		glBegin(GL_POLYGON);
		glVertex2i(10, 280);                        //left side roof
		glVertex2i(195, 410);
		glVertex2i(150, 285);
		glEnd();

		glColor3ub(255, 255, 153);
		glBegin(GL_POLYGON);
		glVertex2i(45, 160);                        //left side window
		glVertex2i(45, 210);
		glVertex2i(118, 215);
		glVertex2i(118, 155);
		glEnd();

		glColor3f(0, 0, 0);
		glBegin(GL_LINES);                         //Window bars
		glVertex2i(75, 158);
		glVertex2i(75, 212);
		glVertex2i(45, 185);
		glVertex2i(118, 183);
		glEnd();

		glColor3ub(255, 128, 0);
		glBegin(GL_POLYGON);
		glVertex2i(150, 85);                       //right side wall
		glVertex2i(350, 90);
		glVertex2i(350, 280);
		glVertex2i(150, 285);
		glEnd();

		glColor3ub(255, 242, 230);
		glBegin(GL_POLYGON);                       //Entrance
		glVertex2i(230, 85);
		glVertex2i(230, 161);
		glVertex2i(290, 163);
		glVertex2i(290, 87);
		glEnd();

		glColor3ub(179, 119, 0);
		glBegin(GL_POLYGON);
		glVertex2i(230, 86);                        //Door
		glVertex2i(230, 160);
		glVertex2i(278, 156);
		glVertex2i(278, 83);
		glEnd();

		glColor3ub(255, 242, 230);

		//glColor3f(0.702,0,0);
		glColor3ub(105, 105, 105);
		glBegin(GL_POLYGON);
		glVertex2i(195, 410);                        //right side roof
		glVertex2i(368, 280);
		glVertex2i(150, 285);
		glEnd();


		

		//bird
		if (x <= 1200)
		{
			bird(40 + x * 0.5, 500 + x * 0.5);
			bird(150 + x * 0.7, 600 + x * 0.7);
			bird(280 + x * 0.8, 700 + x * 0.8);
			bird(350 + x * 0.9, 650 + x * 0.9);
			bird(540 + x * 0.5, 450 + x * 0.7);
			bird(770 + x * 0.6, 550 + x * 0.6);
			bird(900 + x * 0.7, 555 + x * 0.7);
			bird(1050 + x * 0.8, 655 + x * 0.8);
			bird(1150 + x * 0.9, 555 + x * 0.9);
		}

		if (x >= 15 && x <= 28)
		{
			drawText(400, 250, 0, 0, 0, "Shakalaka Boom Boom");
		}

		if (x >= 20 && x <= 265)
		{
			glColor3f(1, 1, 1);
			Head(400, 80, 60);
			glColor3f(0.0, 0, 0.0);
			drawCircle(400, 100, 1, 1, 1, 5, 3, 4);
			glColor3f(1.1, 0, 0.0);
			circle_a(380, 140.0, 10.0);
			glColor3f(0.0, 0, 0.0);
			circle_a(420, 140.0, 10.0);
			drawCircle(400, 190, 0, 50, 80, 5, 3, 6);

		}

		if (x >= 30 && x <= 50)
		{
			drawText(430, 250, 0, 0, 0, "MINISTER AND SOLDIERS ASSEMBLE");
		}

		if (x >= 55 && x <= 85)
		{
			drawText(730, 200, 0, 0, 0, "YES MY LORD");
		}

		if (x >= 87 && x <= 230)
		{
			glColor3f(1, 1, 1);
			Head(700, 100, 60);
			glColor3f(0.0, 0, 0.0);
			circle_a(670, 160.0, 10.0);
			glColor3f(0.0, 0, 0.0);
			circle_a(710, 160.0, 10.0);
			drawCircle(690, 120, 1, 1, 1, 5, 3, 4);
			

			glColor3f(1, 1, 1);
			Head(900, 120, 60);
			glColor3f(0.0, 0, 0.0);
			circle_a(870, 180.0, 10.0);
			glColor3f(0.0, 0, 0.0);
			circle_a(910, 180.0, 10.0);
			drawCircle(890, 140, 1, 1, 1, 5, 3, 4);

			glColor3f(1, 1, 1);
			Head(960, 80, 60);
			glColor3f(0.0, 0, 0.0);
			circle_a(930, 140.0, 10.0);
			glColor3f(0.0, 0, 0.0);
			circle_a(970, 140.0, 10.0);
			drawCircle(950, 100, 1, 1, 1, 5, 3, 4);

			glColor3f(1, 1, 1);
			Head(1030, 50, 60);
			glColor3f(0.0, 0, 0.0);
			circle_a(1000, 110.0, 10.0);
			glColor3f(0.0, 0, 0.0);
			circle_a(1040, 110.0, 10.0);
			drawCircle(1020, 70, 1, 1, 1, 5, 3, 4);

			glColor3f(1, 1, 1);
			Head(1070, 140, 60);
			glColor3f(0.0, 0, 0.0);
			circle_a(1050, 200.0, 10.0);
			glColor3f(0.0, 0, 0.0);
			circle_a(1090, 200.0, 10.0);
			drawCircle(1070, 170, 1, 1, 1, 5, 3, 4);

			glColor3f(1, 1, 1);
			Head(1140, 80, 60);
			glColor3f(0.0, 0, 0.0);
			circle_a(1110, 140.0, 10.0);
			glColor3f(0.0, 0, 0.0);
			circle_a(1150, 140.0, 10.0);
			drawCircle(1130, 110, 1, 1, 1, 5, 3, 4);

			

			glColor3f(1, 1, 1);
			Head(1170, 30, 60);
			glColor3f(0.0, 0, 0.0);
			circle_a(1140, 90.0, 10.0);
			glColor3f(0.0, 0, 0.0);
			circle_a(1180, 90.0, 10.0);
			drawCircle(1160, 50, 1, 1, 1, 5, 3, 4);
		}
		if (x >= 100 && x <= 130)
		{
			drawText(450, 250, 0, 0, 0, "GET READY FOR WAR ");
			drawText(450, 220, 0, 0, 0, "WE HAVE DECLARED");
			drawText(450, 190, 0, 0, 0, "WAR ON KING DASA");
		}

		if (x >= 130 && x <= 190)
		{
			drawText(430, 270, 0, 0, 0, "WE HAVE TO WIN THIS ");
			drawText(430, 240, 0, 0, 0, "WAR  I NEED EVERY ONE TO");
			drawText(430, 210, 0, 0, 0, "PREPARE WELL AND WE NEED");
			drawText(430, 180, 0, 0, 0, "TO EXECUTE IT WELL");
		}
		if (x >= 191 && x <= 205)
		{
			drawText(730, 200, 0, 0, 0, "YES MY LORD");
			drawText(730, 170, 0, 0, 0, "WE WILL....");
		}
		if (x >= 205 && x <= 220)
		{
			drawText(450, 250, 0, 0, 0, "GO AND PRACTICE");
			drawText(450, 220, 0, 0, 0, "JAI KILA KILA");

		}
		if (x >= 220 && x <= 230)
		{
			drawText(730, 250, 0, 0, 0, "JAI KILA KILA");
		}
		if (x >= 232 && x <= 265)
		{
			drawText(450, 250, 0, 0, 0, "MY SOLDIERS ARE WEAK");
			drawText(450, 220, 0, 0, 0, "I NEED TO DO SOMETHING");
			drawText(450, 190, 0, 0, 0, "I NEED TO VISIT MY HOME GOD");
			drawText(450, 160, 0, 0, 0, "JAI KILA KILA");

		}
		if (x >= 265 && x <= 300)
		{

			glColor3f(1, 1, 1);
			Head(x + 400, 80, 60);
			glColor3f(0.0, 0, 0.0);
			drawCircle(x + 400, 100, 1, 1, 1, 5, 3, 4);
			glColor3f(0.0, 0, 0.0);
			circle_a(x + 380, 140.0, 10.0);
			glColor3f(0.0, 0, 0.0);
			circle_a(x + 420, 140.0, 10.0);
			drawCircle(x + 400, 190, 0, 50, 80, 5, 3, 6);

		}

		glFlush();

	}


}


void win1()
{
	int j;
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 1280, 0, 800);
	scene1(i);
}
void scene2(int l)
{
	for (float x = 0; x <= 190; x += 0.2)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glPointSize(5.0);
		//ground

		glColor3f(0.0, 1.0, 0.6);
		glBegin(GL_POLYGON);
		glVertex2f(0.0, 0.0);
		glVertex2f(0.0, 300.0);
		glVertex2f(1280.0, 300.0);
		glVertex2f(1280.0, 0.0);
		glColor3f(0.0, 1.0, 0.0);
		glEnd();

		//sky

		glColor3f(0.1, 1.0, 1.0);
		glBegin(GL_POLYGON);
		glVertex2f(0.0, 300.0);
		glVertex2f(1280.0, 300.0);
		glVertex2f(1280.0, 800.0);
		glVertex2f(0.0, 800.0);
		glEnd();

		//sun

		glColor3f(1.0, 0.7, 0.0);
		circle_a(x, 670.0, 50.0);

		//cloud_a
		glColor3f(1.0, 1.0, 1.0);
		cloud_a(x - 800, 600, 30, -l);
		glColor3f(1.0, 1.0, 1.0);
		cloud_a(x + 800, 680, 30, l);
		glColor3f(1.0, 1.0, 1.0);
		cloud_a(x - 700, 580, 30, -l);
		glColor3f(1.0, 1.0, 1.0);
		cloud_a(x + 50, 680, 30, l);
		glColor3f(1.0, 1.0, 1.0);
		cloud_a(x - 100, 540, 30, l);
		glColor3f(1.0, 1.0, 1.0);
		cloud_a(x + 600, 400, 30, -l);
		glColor3f(1.0, 1.0, 1.0);
		cloud_a(x - 400, 500, 30, -l);
		glColor3f(1.0, 1.0, 1.0);
		cloud_a(x + 300, 440, 30, l);

		// mountains
		glColor3f(0.7, 0.3, 0.0);
		circle_a(213.33, 491.5, 29.5);
		glColor3f(0.7, 0.3, 0.0);
		glBegin(GL_POLYGON);
		glVertex2f(0, 300);
		glVertex2f(183.33, 500);
		glVertex2f(243.33, 500);
		glVertex2f(426.67, 300);
		glEnd();

		glColor3f(0.7, 0.3, 0.0);
		circle_a(640.0, 491.5, 29.5);
		glBegin(GL_POLYGON);
		glVertex2f(426.67, 300);
		glVertex2f(610, 500);
		glVertex2f(670, 500);
		glVertex2f(853.33, 300);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(853.33, 300);
		glVertex2f(1036.6, 500);
		glVertex2f(1096.6, 500);
		glVertex2f(1280, 300);
		glEnd();


		glColor3f(0.7, 0.3, 0.0);
		circle_a(1066.66, 491.5, 29.5);
		glBegin(GL_POLYGON);
		glVertex2f(853.33, 300);
		glVertex2f(1036.6, 500);
		glVertex2f(1096.6, 500);
		glVertex2f(1280, 300);
		glEnd();
		//grass_a
		glColor3f(0, 1, 0);
		grass_a(20, 140, 1, 1);
		grass_a(120, 100, 1, 1);
		grass_a(140, 180, 1, 1);
		grass_a(200, 60, 1, 1);
		grass_a(220, 140, 1, 1);
		grass_a(40, 40, 1, 1);

		grass_a(320, 140, 1, 1);
		grass_a(420, 100, 1, 1);
		grass_a(440, 180, 1, 1);
		grass_a(500, 60, 1, 1);
		grass_a(520, 140, 1, 1);
		grass_a(340, 40, 1, 1);

		grass_a(620, 140, 1, 1);
		grass_a(720, 100, 1, 1);
		grass_a(740, 180, 1, 1);
		grass_a(820, 140, 1, 1);
		grass_a(600, 40, 1, 1);

		glColor3f(0, 1, 0);
		grass_a(820, 140, 1, 1);
		grass_a(920, 100, 1, 1);
		grass_a(940, 180, 1, 1);
		grass_a(1000, 60, 1, 1);
		grass_a(1020, 140, 1, 1);
		grass_a(840, 40, 1, 1);

		glColor3f(0, 1, 0);
		grass_a(1120, 140, 1, 1);
		grass_a(1080, 40, 1, 1);
		grass_a(1180, 80, 1, 1);


		//tree
		glColor3f(0, 1, 0);
		tree2_a(450, 300);
		glColor3f(1, 0.5, 0);
		tree2_a(830, 300);
		glColor3f(0, 0.5, 0);
		tree2_a(30, 300);
		glColor3f(0.5, 0.5, 0);
		tree2_a(1200, 300);


		//bird
		if (x <= 1200)
		{
			bird(40 + x * 0.5, 500 + x * 0.5);
			bird(150 + x * 0.7, 600 + x * 0.7);
			bird(280 + x * 0.8, 700 + x * 0.8);
			bird(350 + x * 0.9, 650 + x * 0.9);
			bird(540 + x * 0.5, 450 + x * 0.7);
			bird(770 + x * 0.6, 550 + x * 0.6);
			bird(900 + x * 0.7, 555 + x * 0.7);
			bird(1050 + x * 0.8, 655 + x * 0.8);
			bird(1150 + x * 0.9, 555 + x * 0.9);
		}

		if (x >= 15 && x <= 25)
		{
			drawText(400, 250, 0, 0, 0, "Shakalaka Boom Boom");
		}

		if (x >= 20 && x <= 265)
		{
			glColor3f(1, 1, 1);
			Head(400, 80, 60);
			glColor3f(0.0, 0, 0.0);
			drawCircle(400, 100, 1, 1, 1, 5, 3, 4);
			glColor3f(0.0, 0, 0.0);
			circle_a(380, 140.0, 10.0);
			glColor3f(0.0, 0, 0.0);
			circle_a(420, 140.0, 10.0);
			drawCircle(400, 190, 0, 50, 80, 5, 3, 6);

		}

		if (x >= 25 && x <= 40)
		{
			drawText(400, 250, 0, 0, 0, "OM JAI KILA KILA....");
		}
		if (x >= 42 && x <= 60)
		{
			drawText(400, 250, 0, 0, 0, "O GOD PLEASE HELP ME");
		}
		if (x >= 60 && x <= 180)
		{
			head2();
		}
		if (x >= 65 && x <= 80)
		{
			drawText(500, 250, 0, 0, 0, "YES MY CHILD TELL YOUR PROBLEM !!!");
		}
		if (x >= 85 && x <= 120)
		{
			drawText(70, 250, 0, 0, 0, "MY SOLDIERS ARE WEAK");
			drawText(70, 220, 0, 0, 0, "AND I HAVE WAGED WAR");
			drawText(50, 190, 0, 0, 0, "I AND MY SOLDIERS NEED STRENGTH AND POWER");
			drawText(70, 160, 0, 0, 0, "TO WIN THE WAR MY GOD");

		}
		if (x >= 120 && x <= 145)
		{
			drawText(500, 250, 0, 0, 0, "TAKE THIS CHOCOLATE AND GIVE TO YOUR SOLDIERS");
			drawText(500, 220, 0, 0, 0, "YOU WILL ACHIEVE YOUR GOAL");
		}

		if (x >= 155 && x <= 200)
		{
			drawCircle(500, 50, 1, 1, 1, 10, 3, 5);
			glColor3d(0, 1, 1);
			glColor3f(0.7, 0.3, 0.0);
			Head(500, 60, 10);
			glColor3f(0.7, 0.3, 0.0);
			Head(480, 60, 10);
			glColor3f(0.7, 0.3, 0.0);
			Head(515, 60, 10);
			glColor3f(0.7, 0.3, 0.0);
			Head(530, 60, 10);

		}
		if (x >= 165 && x <= 175)
		{
			glColor3f(1, 0, 0);
			Head(400, 80, 60);
			glColor3f(0.0, 0, 0.0);
			drawCircle(400, 100, 1, 1, 1, 5, 3, 4);
			glColor3f(0.0, 0, 0.0);
			circle_a(380, 140.0, 10.0);
			glColor3f(0.0, 0, 0.0);
			circle_a(420, 140.0, 10.0);
			drawCircle(400, 190, 0, 50, 80, 5, 3, 6);

		}
		if (x >= 165 && x <= 180)
		{
			drawText(70, 250, 0, 0, 0, "THANK YOU GOD");
			drawText(70, 220, 0, 0, 0, "JAI KILA KILA...");
			drawText(50, 190, 0, 0, 0, "JAI KILA KILA...");
			drawText(70, 160, 0, 0, 0, "JAI KILA KILA...");

		}

		glFlush();

	}


}
void win2()
{
	int j;
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 1280, 0, 800);
	scene2(i);
}
void scene3(int l)
{
	for (float x = 0; x <= 276; x += 0.2)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glPointSize(5.0);
		//ground

		glColor3f(0.0, 1.0, 0.6);
		glBegin(GL_POLYGON);
		glVertex2f(0.0, 0.0);
		glVertex2f(0.0, 300.0);
		glVertex2f(1280.0, 300.0);
		glVertex2f(1280.0, 0.0);
		glColor3f(0.0, 1.0, 0.0);
		glEnd();

		//sky

		glColor3f(0.1, 1.0, 1.0);
		glBegin(GL_POLYGON);
		glVertex2f(0.0, 300.0);
		glVertex2f(1280.0, 300.0);
		glVertex2f(1280.0, 800.0);
		glVertex2f(0.0, 800.0);
		glEnd();

		//sun

		glColor3f(1.0, 0.7, 0.0);
		circle_a(x, 670.0, 50.0);

		//cloud_a
		glColor3f(1.0, 1.0, 1.0);
		cloud_a(x - 800, 600, 30, -l);
		glColor3f(1.0, 1.0, 1.0);
		cloud_a(x + 800, 680, 30, l);
		glColor3f(1.0, 1.0, 1.0);
		cloud_a(x - 700, 580, 30, -l);
		glColor3f(1.0, 1.0, 1.0);
		cloud_a(x + 50, 680, 30, l);
		glColor3f(1.0, 1.0, 1.0);
		cloud_a(x - 100, 540, 30, l);
		glColor3f(1.0, 1.0, 1.0);
		cloud_a(x + 600, 400, 30, -l);
		glColor3f(1.0, 1.0, 1.0);
		cloud_a(x - 400, 500, 30, -l);
		glColor3f(1.0, 1.0, 1.0);
		cloud_a(x + 300, 440, 30, l);

		// mountains
		glColor3f(0.7, 0.3, 0.0);
		circle_a(213.33, 491.5, 29.5);
		glColor3f(0.7, 0.3, 0.0);
		glBegin(GL_POLYGON);
		glVertex2f(0, 300);
		glVertex2f(183.33, 500);
		glVertex2f(243.33, 500);
		glVertex2f(426.67, 300);
		glEnd();

		glColor3f(0.7, 0.3, 0.0);
		circle_a(640.0, 491.5, 29.5);
		glBegin(GL_POLYGON);
		glVertex2f(426.67, 300);
		glVertex2f(610, 500);
		glVertex2f(670, 500);
		glVertex2f(853.33, 300);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(853.33, 300);
		glVertex2f(1036.6, 500);
		glVertex2f(1096.6, 500);
		glVertex2f(1280, 300);
		glEnd();


		glColor3f(0.7, 0.3, 0.0);
		circle_a(1066.66, 491.5, 29.5);
		glBegin(GL_POLYGON);
		glVertex2f(853.33, 300);
		glVertex2f(1036.6, 500);
		glVertex2f(1096.6, 500);
		glVertex2f(1280, 300);
		glEnd();
		//grass_a
		glColor3f(0, 1, 0);
		grass_a(20, 140, 1, 1);
		grass_a(120, 100, 1, 1);
		grass_a(140, 180, 1, 1);
		grass_a(200, 60, 1, 1);
		grass_a(220, 140, 1, 1);
		grass_a(40, 40, 1, 1);

		grass_a(320, 140, 1, 1);
		grass_a(420, 100, 1, 1);
		grass_a(440, 180, 1, 1);
		grass_a(500, 60, 1, 1);
		grass_a(520, 140, 1, 1);
		grass_a(340, 40, 1, 1);

		grass_a(620, 140, 1, 1);
		grass_a(720, 100, 1, 1);
		grass_a(740, 180, 1, 1);
		grass_a(820, 140, 1, 1);
		grass_a(600, 40, 1, 1);

		glColor3f(0, 1, 0);
		grass_a(820, 140, 1, 1);
		grass_a(920, 100, 1, 1);
		grass_a(940, 180, 1, 1);
		grass_a(1000, 60, 1, 1);
		grass_a(1020, 140, 1, 1);
		grass_a(840, 40, 1, 1);

		glColor3f(0, 1, 0);
		grass_a(1120, 140, 1, 1);
		grass_a(1080, 40, 1, 1);
		grass_a(1180, 80, 1, 1);


		//tree
		glColor3f(0, 1, 0);
		tree2_a(450, 300);
		glColor3f(1, 0.5, 0);
		tree2_a(830, 300);
		glColor3f(0, 0.5, 0);
		tree2_a(30, 300);
		glColor3f(0.5, 0.5, 0);
		tree2_a(1200, 300);
		//house
			//1st 


		glColor3ub(230, 115, 0);
		glBegin(GL_POLYGON);
		glVertex2i(20, 280);                        //left side wall
		glVertex2i(20, 110);
		glVertex2i(150, 85);
		glVertex2i(150, 285);
		glEnd();

		glColor3ub(90, 100, 100);
		glBegin(GL_POLYGON);
		glVertex2i(10, 280);                        //left side roof
		glVertex2i(195, 410);
		glVertex2i(150, 285);
		glEnd();

		glColor3ub(255, 255, 153);
		glBegin(GL_POLYGON);
		glVertex2i(45, 160);                        //left side window
		glVertex2i(45, 210);
		glVertex2i(118, 215);
		glVertex2i(118, 155);
		glEnd();

		glColor3f(0, 0, 0);
		glBegin(GL_LINES);                         //Window bars
		glVertex2i(75, 158);
		glVertex2i(75, 212);
		glVertex2i(45, 185);
		glVertex2i(118, 183);
		glEnd();

		glColor3ub(255, 128, 0);
		glBegin(GL_POLYGON);
		glVertex2i(150, 85);                       //right side wall
		glVertex2i(350, 90);
		glVertex2i(350, 280);
		glVertex2i(150, 285);
		glEnd();

		glColor3ub(255, 242, 230);
		glBegin(GL_POLYGON);                       //Entrance
		glVertex2i(230, 85);
		glVertex2i(230, 161);
		glVertex2i(290, 163);
		glVertex2i(290, 87);
		glEnd();

		glColor3ub(179, 119, 0);
		glBegin(GL_POLYGON);
		glVertex2i(230, 86);                        //Door
		glVertex2i(230, 160);
		glVertex2i(278, 156);
		glVertex2i(278, 83);
		glEnd();

		glColor3ub(255, 242, 230);

		//glColor3f(0.702,0,0);
		glColor3ub(105, 105, 105);
		glBegin(GL_POLYGON);
		glVertex2i(195, 410);                        //right side roof
		glVertex2i(368, 280);
		glVertex2i(150, 285);
		glEnd();


		//bird
		if (x <= 1200)
		{
			bird(40 + x * 0.5, 500 + x * 0.5);
			bird(150 + x * 0.7, 600 + x * 0.7);
			bird(280 + x * 0.8, 700 + x * 0.8);
			bird(350 + x * 0.9, 650 + x * 0.9);
			bird(540 + x * 0.5, 450 + x * 0.7);
			bird(770 + x * 0.6, 550 + x * 0.6);
			bird(900 + x * 0.7, 555 + x * 0.7);
			bird(1050 + x * 0.8, 655 + x * 0.8);
			bird(1150 + x * 0.9, 555 + x * 0.9);
		}

		if (x >= 15 && x <= 28)
		{
			drawText(400, 250, 0, 0, 0, "Shakalaka Boom Boom");
		}

		if (x >= 20 && x <= 275)
		{
			glColor3f(1, 1, 1);
			Head(400, 80, 60);
			glColor3f(0.0, 0, 0.0);
			drawCircle(400, 100, 1, 1, 1, 5, 3, 4);
			glColor3f(0.0, 0, 0.0);
			circle_a(380, 140.0, 10.0);
			glColor3f(0.0, 0, 0.0);
			circle_a(420, 140.0, 10.0);
			drawCircle(400, 190, 0, 50, 80, 5, 3, 6);

		}

		if (x >= 30 && x <= 50)
		{
			drawText(430, 250, 0, 0, 0, "MINISTER AND SOLDIERS ASSEMBLE");
		}

		if (x >= 55 && x <= 85)
		{
			drawText(730, 200, 0, 0, 0, "YES MY LORD");
		}

		if (x >= 87 && x <= 275)
		{
			glColor3f(1, 1, 1);
			Head(700, 100, 60);
			glColor3f(0.0, 0, 0.0);
			circle_a(670, 160.0, 10.0);
			glColor3f(0.0, 0, 0.0);
			circle_a(710, 160.0, 10.0);
			drawCircle(690, 120, 1, 1, 1, 5, 3, 4);
			drawCircle(700, 200, 25, 100, 80, 5, 3, 6);

			glColor3f(1, 1, 1);
			Head(900, 120, 60);
			glColor3f(0.0, 0, 0.0);
			circle_a(870, 180.0, 10.0);
			glColor3f(0.0, 0, 0.0);
			circle_a(910, 180.0, 10.0);
			drawCircle(890, 140, 1, 1, 1, 5, 3, 4);

			glColor3f(1, 1, 1);
			Head(960, 80, 60);
			glColor3f(0.0, 0, 0.0);
			circle_a(930, 140.0, 10.0);
			glColor3f(0.0, 0, 0.0);
			circle_a(970, 140.0, 10.0);
			drawCircle(950, 100, 1, 1, 1, 5, 3, 4);

			glColor3f(1, 1, 1);
			Head(1030, 50, 60);
			glColor3f(0.0, 0, 0.0);
			circle_a(1000, 110.0, 10.0);
			glColor3f(0.0, 0, 0.0);
			circle_a(1040, 110.0, 10.0);
			drawCircle(1020, 70, 1, 1, 1, 5, 3, 4);

			glColor3f(1, 1, 1);
			Head(1070, 140, 60);
			glColor3f(0.0, 0, 0.0);
			circle_a(1050, 200.0, 10.0);
			glColor3f(0.0, 0, 0.0);
			circle_a(1090, 200.0, 10.0);
			drawCircle(1070, 170, 1, 1, 1, 5, 3, 4);

			glColor3f(1, 1, 1);
			Head(1140, 80, 60);
			glColor3f(0.0, 0, 0.0);
			circle_a(1110, 140.0, 10.0);
			glColor3f(0.0, 0, 0.0);
			circle_a(1150, 140.0, 10.0);
			drawCircle(1130, 110, 1, 1, 1, 5, 3, 4);

			glColor3f(1, 1, 1);
			Head(1170, 30, 60);
			glColor3f(0.0, 0, 0.0);
			circle_a(1140, 90.0, 10.0);
			glColor3f(0.0, 0, 0.0);
			circle_a(1180, 90.0, 10.0);
			drawCircle(1160, 50, 1, 1, 1, 5, 3, 4);
		}
		if (x >= 100 && x <= 130)
		{
			drawText(450, 270, 0, 0, 0, "I HAVE BROUGHT ");
			drawText(450, 240, 0, 0, 0, "YOU PRASADA OF KILA KILA");
			drawText(450, 210, 0, 0, 0, "CHOCOLATE GIVEN BY GOD");
		}

		if (x >= 130 && x <= 190)
		{
			drawText(430, 270, 0, 0, 0, "HAVE IT WE WILL ");
			drawText(430, 240, 0, 0, 0, "GET ENERGY AND");
			drawText(430, 210, 0, 0, 0, "PEACE OF MIND");
			drawText(430, 180, 0, 0, 0, "SO THAT WE CAN WIN");
		}
		if (x >= 191 && x <= 200)
		{
			drawText(730, 200, 0, 0, 0, "YES MY LORD");
		}
		if (x >= 205 && x <= 220)
		{
			drawText(450, 250, 0, 0, 0, "HOW WAS IT");
		}
		if (x >= 220 && x <= 235)
		{
			drawText(730, 250, 0, 0, 0, "ITS TASTY AND VERY ENERGETIC ");
		}
		if (x >= 236 && x <= 265)
		{
			drawText(450, 250, 0, 0, 0, "MY SOLDIERS ARE ");
			drawText(450, 220, 0, 0, 0, "STRONG AND  ENERGETIC");
			drawText(450, 190, 0, 0, 0, "COME ON NOW FACE THE WAR");
			drawText(450, 160, 0, 0, 0, "JAI KILA KILA");

		}
		if (x >= 265 && x <= 275)
		{
			drawText(730, 250, 0, 0, 0, "JAI KILA KILA");
		}

		if (x >= 20 && x <= 275)
		{
			drawCircle(500, 50, 1, 1, 1, 10, 3, 5);
		}

		if (x >= 20 && x <= 200)
		{

			glColor3d(0, 1, 1);
			glColor3f(0.7, 0.3, 0.0);
			Head(500, 60, 10);
			glColor3f(0.7, 0.3, 0.0);
			Head(480, 60, 10);
			glColor3f(0.7, 0.3, 0.0);
			Head(515, 60, 10);
			glColor3f(0.7, 0.3, 0.0);
			Head(530, 60, 10);
		}

		if (x >= 200 && x <= 210)
		{

			glColor3d(0, 1, 1);
			glColor3f(0.7, 0.3, 0.0);
			Head(890, 140, 10);
			glColor3f(0.7, 0.3, 0.0);
			Head(950, 100, 10);
			glColor3f(0.7, 0.3, 0.0);
			Head(1020, 70, 10);
			glColor3f(0.7, 0.3, 0.0);
			Head(1070, 170, 10);
			glColor3f(0.7, 0.3, 0.0);
			Head(1130, 110, 10);
			glColor3f(0.7, 0.3, 0.0);
			Head(1160, 50, 10);
			glColor3f(0.7, 0.3, 0.0);
			Head(690, 120, 10);

		}
		if (x >= 210 && x <= 215)
		{
			glColor3f(1, 0, 0);
			Head(700, 100, 60);
			glColor3f(0.0, 0, 0.0);
			circle_a(670, 160.0, 10.0);
			glColor3f(0.0, 0, 0.0);
			circle_a(710, 160.0, 10.0);
			drawCircle(690, 120, 1, 1, 1, 5, 3, 4);
			drawCircle(700, 200, 25, 100, 80, 5, 3, 6);

			glColor3f(1, 0, 0);
			Head(900, 120, 60);
			glColor3f(0.0, 0, 0.0);
			circle_a(870, 180.0, 10.0);
			glColor3f(0.0, 0, 0.0);
			circle_a(910, 180.0, 10.0);
			drawCircle(890, 140, 1, 1, 1, 5, 3, 4);

			glColor3f(1, 0, 0);
			Head(960, 80, 60);
			glColor3f(0.0, 0, 0.0);
			circle_a(930, 140.0, 10.0);
			glColor3f(0.0, 0, 0.0);
			circle_a(970, 140.0, 10.0);
			drawCircle(950, 100, 1, 1, 1, 5, 3, 4);

			glColor3f(1, 0, 0);
			Head(1030, 50, 60);
			glColor3f(0.0, 0, 0.0);
			circle_a(1000, 110.0, 10.0);
			glColor3f(0.0, 0, 0.0);
			circle_a(1040, 110.0, 10.0);
			drawCircle(1020, 70, 1, 1, 1, 5, 3, 4);

			glColor3f(1, 0, 0);
			Head(1070, 140, 60);
			glColor3f(0.0, 0, 0.0);
			circle_a(1050, 200.0, 10.0);
			glColor3f(0.0, 0, 0.0);
			circle_a(1090, 200.0, 10.0);
			drawCircle(1070, 170, 1, 1, 1, 5, 3, 4);

			glColor3f(1, 0, 0);
			Head(1140, 80, 60);
			glColor3f(0.0, 0, 0.0);
			circle_a(1110, 140.0, 10.0);
			glColor3f(0.0, 0, 0.0);
			circle_a(1150, 140.0, 10.0);
			drawCircle(1130, 110, 1, 1, 1, 5, 3, 4);

			glColor3f(1, 0, 0);
			Head(1170, 30, 60);
			glColor3f(0.0, 0, 0.0);
			circle_a(1140, 90.0, 10.0);
			glColor3f(0.0, 0, 0.0);
			circle_a(1180, 90.0, 10.0);
			drawCircle(1160, 50, 1, 1, 1, 5, 3, 4);
		}

		glFlush();

	}


}

void win3()
{
	int j;
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 1280, 0, 800);
	scene3(i);
}
void scene4(int l)
{
	for (float x = 0; x <= 140; x += 0.2)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glPointSize(5.0);
		//ground

		glColor3f(0.0, 1.0, 0.6);
		glBegin(GL_POLYGON);
		glVertex2f(0.0, 0.0);
		glVertex2f(0.0, 300.0);
		glVertex2f(1280.0, 300.0);
		glVertex2f(1280.0, 0.0);
		glColor3f(0.0, 1.0, 0.0);
		glEnd();

		//sky

		glColor3f(0.1, 1.0, 1.0);
		glBegin(GL_POLYGON);
		glVertex2f(0.0, 300.0);
		glVertex2f(1280.0, 300.0);
		glVertex2f(1280.0, 800.0);
		glVertex2f(0.0, 800.0);
		glEnd();

		//sun

		glColor3f(1.0, 0.7, 0.0);
		circle_a(750, 670.0, 50.0);

		//cloud_a
		glColor3f(1.0, 1.0, 1.0);
		cloud_a(x - 800, 600, 30, -l);
		glColor3f(1.0, 1.0, 1.0);
		cloud_a(x + 800, 680, 30, l);
		glColor3f(1.0, 1.0, 1.0);
		cloud_a(x - 700, 580, 30, -l);
		glColor3f(1.0, 1.0, 1.0);
		cloud_a(x + 50, 680, 30, l);
		glColor3f(1.0, 1.0, 1.0);
		cloud_a(x - 100, 540, 30, l);
		glColor3f(1.0, 1.0, 1.0);
		cloud_a(x + 600, 400, 30, -l);
		glColor3f(1.0, 1.0, 1.0);
		cloud_a(x - 400, 500, 30, -l);
		glColor3f(1.0, 1.0, 1.0);
		cloud_a(x + 300, 440, 30, l);

		glColor3f(1.0, 1.0, 1.0);
		cloud_a(x - 1000, 600, 30, -l);
		glColor3f(1.0, 1.0, 1.0);
		cloud_a(x - 800, 680, 30, l);
		glColor3f(1.0, 1.0, 1.0);
		cloud_a(x - 600, 580, 30, -l);
		glColor3f(1.0, 1.0, 1.0);
		cloud_a(x - 200, 680, 30, l);
		glColor3f(1.0, 1.0, 1.0);
		cloud_a(x - 100, 540, 30, l);
		glColor3f(1.0, 1.0, 1.0);
		cloud_a(x - 500, 400, 30, -l);
		glColor3f(1.0, 1.0, 1.0);
		cloud_a(x - 400, 500, 30, -l);
		glColor3f(1.0, 1.0, 1.0);
		cloud_a(x - 300, 440, 30, l);


		//bird
		if (x <= 1200)
		{
			bird(40 + x * 0.5, 500 + x * 0.5);
			bird(150 + x * 0.7, 600 + x * 0.7);
			bird(280 + x * 0.8, 700 + x * 0.8);
			bird(350 + x * 0.9, 650 + x * 0.9);
			bird(540 + x * 0.5, 450 + x * 0.7);
			bird(770 + x * 0.6, 550 + x * 0.6);
			bird(900 + x * 0.7, 555 + x * 0.7);
			bird(1050 + x * 0.8, 655 + x * 0.8);
			bird(1150 + x * 0.9, 555 + x * 0.9);
		}
		//black
		if (x >= 5 && x <= 116)
		{
			glColor3f(0, 0, 0);
			Head(450, 130, 60);
			glColor3f(1, 1, 1);
			circle_a(430, 190.0, 10.0);
			glColor3f(1, 1, 1);
			circle_a(470, 190.0, 10.0);
			drawCircle(450, 150, 248, 248, 255, 5, 3, 4);
			drawCircle(450, 230, 800, 50, 80, 5, 3, 6);

			glColor3f(0, 0, 0);
			Head(350, 40, 60);
			glColor3f(1, 1, 1);
			circle_a(330, 100.0, 10.0);
			glColor3f(1, 1, 1);
			circle_a(370, 100.0, 10.0);
			drawCircle(350, 60, 248, 248, 255, 5, 3, 4);


			glColor3f(0, 0, 0);
			Head(350, 230, 60);
			glColor3f(1, 1, 1);
			circle_a(330, 290.0, 10.0);
			glColor3f(1, 1, 1);
			circle_a(370, 290.0, 10.0);
			drawCircle(350, 250, 248, 248, 255, 5, 3, 4);



			glColor3f(0, 0, 0);
			Head(250, 140, 60);
			glColor3f(1, 1, 1);
			circle_a(230, 200.0, 10.0);
			glColor3f(1, 1, 1);
			circle_a(270, 200.0, 10.0);
			drawCircle(250, 160, 248, 248, 255, 5, 3, 4);

			glColor3f(0, 0, 0);
			Head(100, 40, 60);
			glColor3f(1, 1, 1);
			circle_a(80, 100.0, 10.0);
			glColor3f(1, 1, 1);
			circle_a(120, 100.0, 10.0);
			drawCircle(100, 60, 248, 248, 255, 5, 3, 4);

			glColor3f(0, 0, 0);
			Head(100, 220, 60);
			glColor3f(1, 1, 1);
			circle_a(80, 280.0, 10.0);
			glColor3f(1, 1, 1);
			circle_a(120, 280.0, 10.0);
			drawCircle(100, 240, 248, 248, 255, 5, 3, 4);
		}
		//white
		if (x >= 7 && x <= 330)
		{
			glColor3f(1, 1, 1);
			Head(700, 130, 60);
			glColor3f(0.0, 0, 0.0);
			circle_a(670, 190.0, 10.0);
			glColor3f(0.0, 0, 0.0);
			circle_a(710, 190.0, 10.0);
			drawCircle(690, 150, 1, 1, 1, 5, 3, 4);
			drawCircle(700, 230, 25, 100, 80, 5, 3, 6);

			glColor3f(1, 1, 1);
			Head(850, 40, 60);
			glColor3f(0.0, 0, 0.0);
			circle_a(830, 100.0, 10.0);
			glColor3f(0.0, 0, 0.0);
			circle_a(870, 100.0, 10.0);
			drawCircle(850, 60, 1, 1, 1, 5, 3, 4);

			glColor3f(1, 1, 1);
			Head(850, 230, 60);
			glColor3f(0.0, 0, 0.0);
			circle_a(830, 290.0, 10.0);
			glColor3f(0.0, 0, 0.0);
			circle_a(870, 290.0, 10.0);
			drawCircle(850, 250, 1, 1, 1, 5, 3, 4);

			glColor3f(1, 1, 1);
			Head(950, 140, 60);
			glColor3f(0.0, 0, 0.0);
			circle_a(930, 200, 10.0);
			glColor3f(0.0, 0, 0.0);
			circle_a(970, 200, 10.0);
			drawCircle(950, 160, 1, 1, 1, 5, 3, 4);

			glColor3f(1, 1, 1);
			Head(1100, 40, 60);
			glColor3f(0.0, 0, 0.0);
			circle_a(1080, 100, 10.0);
			glColor3f(0.0, 0, 0.0);
			circle_a(1120, 100, 10.0);
			drawCircle(1100, 60, 1, 1, 1, 5, 3, 4);

			glColor3f(1, 1, 1);
			Head(1100, 220, 60);
			glColor3f(0.0, 0, 0.0);
			circle_a(1080, 280.0, 10.0);
			glColor3f(0.0, 0, 0.0);
			circle_a(1120, 280.0, 10.0);
			drawCircle(1100, 240, 1, 1, 1, 5, 3, 4);
		}
		if (x >= 10 && x <= 40)
		{
			drawText(430, 310, 0, 0, 0, "Nimmddaa�Gojrass thelmii.. ");
			drawText(430, 280, 0, 0, 0, "Aardha bhos.. Kkraakvikana Bhhumle. ");
			drawText(430, 250, 0, 0, 0, "Mohinoojukooo�Lioohakvee� ");
		}

		if (x >= 40 && x <= 60)
		{
			drawText(430, 310, 0, 0, 0, "Unu Kaasthaa..peezzraaa.. ");
			drawText(430, 280, 0, 0, 0, "Chooho..Chuunnamatasweekkdhee.. ");
			drawText(430, 250, 0, 0, 0, "Thraaa�Ghraakshh�Hooorrr�Aarr..");
		}

		if (x >= 65 && x <= 90)
		{
			drawText(550, 330, 0, 0, 0, "Keep telling dialogues");
			drawText(550, 300, 0, 0, 0, "No one will fear");
			drawText(550, 280, 0, 0, 0, "we have god kila kila blessing");
		}

		if (x >= 90 && x <= 95)
		{
			drawText(550, 330, 0, 0, 0, "SOLDIERS FIRE");
			drawText(550, 300, 0, 0, 0, "KILL THEM");

		}
		if (x >= 95 && x <= 100)
		{

			drawCircle(200, 250, 205, 92, 92, 10, 0.5, 6);
			drawCircle(210, 60, 205, 92, 92, 10, 0.5, 6);
			drawCircle(350, 180, 205, 92, 92, 10, 0.5, 6);
			drawCircle(450, 260, 205, 92, 92, 10, 0.5, 6);
			drawCircle(450, 60, 205, 92, 92, 10, 0.5, 6);
		}
		if (x >= 111 && x <= 105)
		{

			drawCircle(200, 250, 205, 92, 92, 10, 0.5, 6);
			drawCircle(210, 60, 205, 92, 92, 10, 0.5, 6);
			drawCircle(350, 180, 205, 92, 92, 10, 0.5, 6);
			drawCircle(450, 260, 205, 92, 92, 10, 0.5, 6);
			drawCircle(450, 60, 205, 92, 92, 10, 0.5, 6);
		}
		if (x >= 106 && x <= 115)
		{

			drawCircle(200, 250, 205, 92, 92, 10, 0.5, 6);
			drawCircle(210, 60, 205, 92, 92, 10, 0.5, 6);
			drawCircle(350, 180, 205, 92, 92, 10, 0.5, 6);
			drawCircle(450, 260, 205, 92, 92, 10, 0.5, 6);
			drawCircle(450, 60, 205, 92, 92, 10, 0.5, 6);
		}
		if (x >= 116 && x <= 137)
		{
			glColor3f(0, 0, 0);
			Head(450, 130, 60);
			glColor3f(1, 1, 1);
			circle_a(430, 190.0, 10.0);
			glColor3f(1, 1, 1);
			circle_a(470, 190.0, 10.0);
			drawCircle(450, 150, 248, 248, 255, 5, 3, 4);
			drawCircle(450, 230, 800, 50, 80, 5, 3, 6);
		}
		if (x >= 106 && x <= 115)
		{

			glColor3f(238, 223, 0);
			Head(350, 40, 60);
			glColor3f(1, 1, 1);
			circle_a(330, 100.0, 10.0);
			glColor3f(1, 1, 1);
			circle_a(370, 100.0, 10.0);
			drawCircle(350, 60, 248, 248, 255, 5, 3, 4);


			glColor3f(238, 223, 0);
			Head(350, 230, 60);
			glColor3f(1, 1, 1);
			circle_a(330, 290.0, 10.0);
			glColor3f(1, 1, 1);
			circle_a(370, 290.0, 10.0);
			drawCircle(350, 250, 248, 248, 255, 5, 3, 4);



			glColor3f(238, 223, 0);
			Head(250, 140, 60);
			glColor3f(1, 1, 1);
			circle_a(230, 200.0, 10.0);
			glColor3f(1, 1, 1);
			circle_a(270, 200.0, 10.0);
			drawCircle(250, 160, 248, 248, 255, 5, 3, 4);

			glColor3f(238, 223, 0);
			Head(100, 40, 60);
			glColor3f(1, 1, 1);
			circle_a(80, 100.0, 10.0);
			glColor3f(1, 1, 1);
			circle_a(120, 100.0, 10.0);
			drawCircle(100, 60, 248, 248, 255, 5, 3, 4);

			glColor3f(238, 223, 0);
			Head(100, 220, 60);
			glColor3f(1, 1, 1);
			circle_a(80, 280.0, 10.0);
			glColor3f(1, 1, 1);
			circle_a(120, 280.0, 10.0);
			drawCircle(100, 240, 248, 248, 255, 5, 3, 4);
		}
		if (x >= 136 && x <= 160)
		{
			drawText(550, 330, 0, 0, 0, "WE WON........");
			drawText(550, 300, 0, 0, 0, "WE WON........");

		}
		if (x >= 116 && x <= 135)
		{
			drawText(430, 310, 0, 0, 0, "Khali stop yo have only won !!");
			drawText(430, 280, 0, 0, 0, "Leave me now I will run away");
			drawText(430, 250, 0, 0, 0, "My all kingdom is yours now !!!");
		}
		glFlush();

	}


}
void win4()
{
	int j;
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 1280, 0, 800);
	scene4(i);
}
void renderScene() {
	// Switch to know which scene is playing
	switch (SCENE_ID) {
	case 0:
		introduction();
		break;
	case 1:
		Screen1();
		break;
	case 2:
		Screen2();
		break;
	case 3:
		Screen3();
		break;
	case 4:
		win1();
		break;
	case 5:
		win2();
		break;
	case 6:win3();
		break;
	case 7:win4();
		break;
	case 8:Screenl();

		break;
	case 9:exit(0);

		break;
	}
	glFlush();
}



void mouseClick(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		std::cout << x << "\t" << 800 - y << "\n";
}

void update(int) {

	if (SCENE_ID == 0) {
		if (title_fade < 1)
			title_fade += .003;
		else
			intro_next_text_appear = 1;
	}

	if (SCENE_ID == 1) {
		if (trans_x_chap1 < 100)
			trans_x_chap1 += 1;

		if (trans_x_title1 < 100)
			trans_x_title1 += 1;

		if (gy_chap_fade < 1)
			gy_chap_fade += .025;

		if (gy_title_fade < 1)
			gy_title_fade += .025;
	}

	if (SCENE_ID == 2) {
		if (trans_x_chap2 < 100)
			trans_x_chap2 += 1;

		if (trans_x_title2 < 100)
			trans_x_title2 += 1;

		if (gy_chap_fade < 1)
			gy_chap_fade += .025;

		if (gy_title_fade < 1)
			gy_title_fade += .025;
	}

	if (SCENE_ID == 3) {
		if (trans_x_chap3 < 100)
			trans_x_chap3 += 1;

		if (trans_x_title3 < 100)
			trans_x_title3 += 1;

		if (gy_chap_fade < 1)
			gy_chap_fade += .025;

		if (gy_title_fade < 1)
			gy_title_fade += .025;
	}
	if (SCENE_ID == 8) {
		if (title_fade < 1)
			title_fade += .003;
		else
			intro_next_text_appear = 1;
	}

	// Recalls the Display Function
	glutPostRedisplay();

	// Creates a Timer of 25ms
	glutTimerFunc(25, update, 0);
}

void keyPress(unsigned char key, int x, int y) {
	switch (key) {
		// Go to Previous Scene
	case 'b':
	case 'B':
		if (SCENE_ID == 0)
			break;
		SCENE_ID--;
		break;
		// Go to Next Scene
	case ' ':
	case '1':
		if (SCENE_ID == 15)
			break;
		SCENE_ID++;
		break;
		// Quit Story
	case 'q':
	case 'Q':
		exit(0);
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

void initializeScreen() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 1400, 0, 800);
}


int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1400, 800);
	glutCreateWindow("DEVILS CHOCOLATE");
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glutDisplayFunc(renderScene);
	glutKeyboardFunc(keyPress);
	glutMouseFunc(mouseClick);

	initializeScreen();
	glutTimerFunc(25, update, 0);

	glutMainLoop();

	return 0;
}
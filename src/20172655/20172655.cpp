#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h" //텍스처로 사용된 bmp 이미지 로딩에 사용되는 오픈 소스 라이브러리
#include <glut.h>

// 회전을 위한 변수
int prevX = 0;
int prevY = 0;
float rotationX = 0.0;
float rotationY = 0.0;

// 확대,축소를 위한 변수
float zoom = 1.0;

//곡괭이 좌표 설정 위한 변수
float px = -6;
float py = 11.7;
float pz = 11.9;

// 텍스처 변수 선언
GLuint frontTexture, backTexture, leftTexture, rightTexture, topTexture, bottomTexture;
GLuint bgfloor, bgsky, bg1, bg2, bg3, bg4;

// 함수 원형 선언
void loadTextures();

void drawGuide();
void drawLeftleg();
void drawRightleg();
void drawBody();
void drawLeftarm();
void drawRightarm();
void drawHead();
void drawPick();

void display();
void reshape(int width, int height);
void mouse(int button, int state, int x, int y);
void motion(int x, int y);
void keyboard(unsigned char key, int x, int y);

// main 함수
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1920, 1080);
    glutCreateWindow("Steve in Minecraft");

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);

    loadTextures();

    //콜백 함수들
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}

void loadTextures() {
    int width, height, channels;
    unsigned char* image;

    // 얼굴 앞면 텍스처 로드
    image = stbi_load("front.bmp", &width, &height, &channels, 0);
    glGenTextures(1, &frontTexture);
    glBindTexture(GL_TEXTURE_2D, frontTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    stbi_image_free(image);

    // 얼굴 뒷면 텍스처 로드
    image = stbi_load("back.bmp", &width, &height, &channels, 0);
    glGenTextures(1, &backTexture);
    glBindTexture(GL_TEXTURE_2D, backTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    stbi_image_free(image);

    // 얼굴 왼쪽면 텍스처 로드
    image = stbi_load("left.bmp", &width, &height, &channels, 0);
    glGenTextures(1, &leftTexture);
    glBindTexture(GL_TEXTURE_2D, leftTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    stbi_image_free(image);

    // 얼굴 오른쪽면 텍스처 로드
    image = stbi_load("right.bmp", &width, &height, &channels, 0);
    glGenTextures(1, &rightTexture);
    glBindTexture(GL_TEXTURE_2D, rightTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    stbi_image_free(image);

    // 얼굴 상단면 텍스처 로드
    image = stbi_load("top.bmp", &width, &height, &channels, 0);
    glGenTextures(1, &topTexture);
    glBindTexture(GL_TEXTURE_2D, topTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    stbi_image_free(image);

    // 얼굴 하단면 텍스처 로드
    image = stbi_load("bottom.bmp", &width, &height, &channels, 0);
    glGenTextures(1, &bottomTexture);
    glBindTexture(GL_TEXTURE_2D, bottomTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    stbi_image_free(image);
}

// 좌표축 표시 
void drawGuide()
{
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0); //x축
    glVertex3f(-50, 0, 0);
    glVertex3f(50, 0, 0);
    glColor3f(0.0, 1.0, 0.0); //y축
    glVertex3f(0, -50, 0);
    glVertex3f(0, 50, 0);
    glColor3f(0.0, 0.0, 1.0); //z축
    glVertex3f(0, 0, -50);
    glVertex3f(0, 0, 50);
    glEnd();
    glPopMatrix();
}

//Steve는 (0, 0, 0)에 서 있는 상태
void drawLeftleg()
{
    // 왼다리
    glPushMatrix();
    glColor3f(0.21961f, 0.34118f, 0.66667f);
    //glTranslatef(-0.21, 0.7, -0.4);
    glTranslatef(-2.1, 7, -4);
    glRotatef(45.0, 1.0, 0.0, 0.0);
    //glScalef(0.4, 1.2, 0.4);
    glScalef(4, 12, 4);
    glutSolidCube(1.0);
    glPopMatrix();
}
void drawRightleg()
{
    // 오른다리
    glPushMatrix();
    glColor3f(0.21961f, 0.34118f, 0.66667f);
    glTranslatef(2.1, 6, 3);
    glRotatef(-30.0, 1.0, 0.0, 0.0);
    glScalef(4, 12, 4);
    glutSolidCube(1.0);
    glPopMatrix();
}
void drawBody()
{
    // 몸통
    glPushMatrix();
    glColor3f(0.06275f, 0.72941f, 0.72941f);
    glTranslatef(0.0, 17, 0.0);
    glScalef(8, 12, 4);
    glutSolidCube(1.0);
    glPopMatrix();
}
void drawLeftarm()
{
    // 왼팔
    glPushMatrix();
    glColor3f(0.91765f, 0.72941f, 0.53725f);
    glTranslatef(-6, 19, 4);
    glRotatef(-70.0, 1.0, 0.0, 0.0);
    glScalef(4, 12, 4);
    glutSolidCube(1.0);
    glPopMatrix();

    //소매
    glPushMatrix();
    glColor3f(0.06275f, 0.72941f, 0.72941f);
    glTranslatef(-6, 20.5, 0);
    glRotatef(-70.0, 1.0, 0.0, 0.0);
    glScalef(4.1, 4.1, 4.1);
    glutSolidCube(1.0);
    glPopMatrix();
}
void drawRightarm()
{
    // 오른팔
    glPushMatrix();
    glColor3f(0.91765f, 0.72941f, 0.53725f);
    glTranslatef(6, 17.5, -3.5);
    glRotatef(45.0, 1.0, 0.0, 0.0);
    glScalef(4, 12, 4);
    glutSolidCube(1.0);
    glPopMatrix();

    //소매
    glPushMatrix();
    glColor3f(0.06275f, 0.72941f, 0.72941f);
    glTranslatef(6, 20.3, -0.7);
    glRotatef(45.0, 1.0, 0.0, 0.0);
    glScalef(4.1, 4.1, 4.1);
    glutSolidCube(1.0);
    glPopMatrix();
}
void drawHead()
{
    // 머리
    glPushMatrix();
    glTranslatef(0.0, 27, 0.0);
    glScalef(8, 8, 8);

    // Front
    glBindTexture(GL_TEXTURE_2D, frontTexture);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(1.0f, 0.0f);  glVertex3f(-0.5f, 0.5f, 0.5f);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);

    // Back
    glBindTexture(GL_TEXTURE_2D, backTexture);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, 0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, -0.5f, -0.5f);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);

    // Top
    glBindTexture(GL_TEXTURE_2D, topTexture);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, 0.5f, -0.5f);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);

    // Bottom
    glBindTexture(GL_TEXTURE_2D, bottomTexture);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);

    // Right
    glBindTexture(GL_TEXTURE_2D, rightTexture);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5f, -0.5f, 0.5f);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);

    // Left
    glBindTexture(GL_TEXTURE_2D, leftTexture);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    
    glPopMatrix();
}
void drawPick()
{
    //곡괭이
    //y=0
    glPushMatrix();
    glColor3f(0.15686, 0.11765, 0.04314);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 0.0 + py, 0.0 + pz);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.15686, 0.11765, 0.04314);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 0.0 + py, 1 + pz);
    glutSolidCube(1);
    glPopMatrix();

    //y=1
    glPushMatrix();
    glColor3f(0.28627f, 0.21176f, 0.08235f);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 1 + py, 0.0 + pz);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.53725f, 0.40392f, 0.15294f);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 1 + py, 1 + pz);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.15686, 0.11765, 0.04314);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 1 + py, 2 + pz);
    glutSolidCube(1);
    glPopMatrix();

    //y=2
    glPushMatrix();
    glColor3f(0.28627f, 0.21176f, 0.08235f);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 2 + py, 1 + pz);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.40784f, 0.30588f, 0.11765f);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 2 + py, 2 + pz);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.15686, 0.11765, 0.04314);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 2 + py, 3 + pz);
    glutSolidCube(1);
    glPopMatrix();

    //y=3
    glPushMatrix();
    glColor3f(0.28627f, 0.21176f, 0.08235f);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 3 + py, 2 + pz);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.53725f, 0.40392f, 0.15294f);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 3 + py, 3 + pz);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.15686, 0.11765, 0.04314);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 3 + py, 4 + pz);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.09412f, 0.09412f, 0.09412f);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 3 + py, 11 + pz);
    glutSolidCube(1);
    glPopMatrix();

    //y=4
    glPushMatrix();
    glColor3f(0.28627f, 0.21176f, 0.08235f);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px,  4 + py,  3 + pz);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.40784f, 0.30588f, 0.11765f);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 4 + py, 4 + pz);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.15686, 0.11765, 0.04314);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 4 + py, 5 + pz);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.09412f, 0.09412f, 0.09412f);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 4 + py, 10 + pz);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 4 + py, 11 + pz);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.09412f, 0.09412f, 0.09412f);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 4 + py, 12 + pz);
    glutSolidCube(1);
    glPopMatrix();

    //y=5
    glPushMatrix();
    glColor3f(0.28627f, 0.21176f, 0.08235f);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 5 + py, 4 + pz);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.53725f, 0.40392f, 0.15294f);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 5 + py, 5 + pz);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.15686, 0.11765, 0.04314);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 5 + py, 6 + pz);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.09412f, 0.09412f, 0.09412f);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 5 + py, 10 + pz);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.84706f, 0.84706f, 0.84706f);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 5 + py, 11 + pz);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.09412f, 0.09412f, 0.09412f);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 5 + py, 12 + pz);
    glutSolidCube(1);
    glPopMatrix();

    //y=6
    glPushMatrix();
    glColor3f(0.28627f, 0.21176f, 0.08235f);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 6 + py, 5 + pz);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.40784f, 0.30588f, 0.11765f);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 6 + py, 6 + pz);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.15686, 0.11765, 0.04314);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 6 + py, 7 + pz);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.09412f, 0.09412f, 0.09412f);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 6 + py, 10 + pz);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.75686f, 0.75686f, 0.75686f);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 6 + py, 11 + pz);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.09412f, 0.09412f, 0.09412f);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 6 + py, 12 + pz);
    glutSolidCube(1);
    glPopMatrix();

    //y=7
    glPushMatrix();
    glColor3f(0.28627f, 0.21176f, 0.08235f);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 7 + py, 6 + pz);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.53725f, 0.40392f, 0.15294f);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 7 + py, 7 + pz);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.15686, 0.11765, 0.04314);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 7 + py, 8 + pz);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.09412f, 0.09412f, 0.09412f);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 7 + py, 10 + pz);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.75686f, 0.75686f, 0.75686f);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 7 + py, 11 + pz);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.09412f, 0.09412f, 0.09412f);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 7 + py, 12 + pz);
    glutSolidCube(1);
    glPopMatrix();

    //y=8
    glPushMatrix();
    glColor3f(0.28627f, 0.21176f, 0.08235f);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 8 + py, 7 + pz);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.40784f, 0.30588f, 0.11765f);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 8 + py, 8 + pz);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.15686, 0.11765, 0.04314);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 8 + py, 9 + pz);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.75686f, 0.75686f, 0.75686f);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 8 + py, 10 + pz);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.84706f, 0.84706f, 0.84706f);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 8 + py, 11 + pz);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.09412f, 0.09412f, 0.09412f);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 8 + py, 12 + pz);
    glutSolidCube(1);
    glPopMatrix();

    //y=9
    glPushMatrix();
    glColor3f(0.28627f, 0.21176f, 0.08235f);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 9 + py, 8 + pz);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.84706f, 0.84706f, 0.84706f);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 9 + py, 9 + pz);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.75686f, 0.75686f, 0.75686f);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 9 + py, 10 + pz);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.09412f, 0.09412f, 0.09412f);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 9 + py, 11 + pz);
    glutSolidCube(1);
    glPopMatrix();

    //y=10
    glPushMatrix();
    glColor3f(0.26667f, 0.26667f, 0.26667f);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 10 + py, 4 + pz);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.09412f, 0.09412f, 0.09412f);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 10 + py, 5 + pz);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.09412f, 0.09412f, 0.09412f);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 10 + py, 6 + pz);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.09412f, 0.09412f, 0.09412f);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 10 + py, 7 + pz);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.75686f, 0.75686f, 0.75686f);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 10 + py, 8 + pz);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.75686f, 0.75686f, 0.75686f);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 10 + py, 9 + pz);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.53725f, 0.40392f, 0.15294f);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 10 + py, 10 + pz);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.15686, 0.11765, 0.04314);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 10 + py, 11 + pz);
    glutSolidCube(1);
    glPopMatrix();

    //y=11
    glPushMatrix();
    glColor3f(0.26667f, 0.26667f, 0.26667f);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 11 + py, 3 + pz);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 11 + py, 4 + pz);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.84706f, 0.84706f, 0.84706f);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 11 + py, 5 + pz);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.75686f, 0.75686f, 0.75686f);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 11 + py, 6 + pz);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.75686f, 0.75686f, 0.75686f);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 11 + py, 7 + pz);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.84706f, 0.84706f, 0.84706f);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 11 + py, 8 + pz);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.26667f, 0.26667f, 0.26667f);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 11 + py, 9 + pz);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.28627f, 0.21176f, 0.08235f);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 11 + py, 10 + pz);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.40784f, 0.30588f, 0.11765f);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 11 + py, 11 + pz);
    glutSolidCube(1);
    glPopMatrix();

    //y=12
    glPushMatrix();
    glColor3f(0.26667f, 0.26667f, 0.26667f);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 12 + py, 4 + pz);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.26667f, 0.26667f, 0.26667f);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 12 + py, 5 + pz);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.26667f, 0.26667f, 0.26667f);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 12 + py, 6 + pz);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.26667f, 0.26667f, 0.26667f);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 12 + py, 7 + pz);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.26667f, 0.26667f, 0.26667f);
    glRotatef(-25.0, 1.0, 0.0, 0.0);
    glTranslatef(0.0 + px, 12 + py, 8 + pz);
    glutSolidCube(1);
    glPopMatrix();

}

// display 함수
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // 확대, 축소, 회전
    glTranslatef(0.0, -3.0, -40.0);
    glScalef(zoom, zoom, zoom);
    glRotatef(rotationX, 1.0, 0.0, 0.0);
    glRotatef(rotationY, 0.0, 1.0, 0.0);

    //좌표축
    drawGuide();

    //모델
    drawHead();
    drawLeftleg();
    drawRightleg();
    drawBody();
    drawLeftarm();
    drawRightarm();

    //곡괭이
    drawPick();
   
    glFlush();
    glutSwapBuffers();
}

// reshape 함수
void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float)width / height, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

//마우스클릭
void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        prevX = x;
        prevY = y;
    }
}

//로테이션
void motion(int x, int y)
{
    rotationX += (y - prevY) * 0.5;
    rotationY += (x - prevX) * 0.5;
    prevX = x;
    prevY = y;
    glutPostRedisplay();
}

//키입력 -> 확대, 축소
void keyboard(unsigned char key, int x, int y)
{
    if (key == 'a')
    {
        zoom += 0.1;
        if (zoom > 3)
            zoom = 3;
    }
    else if (key == 'z')
    {
        zoom -= 0.1;
        if (zoom < 0.2)
            zoom = 0.2;
    }
    glutPostRedisplay();
}

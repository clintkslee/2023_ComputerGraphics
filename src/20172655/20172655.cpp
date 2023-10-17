#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h" //�ؽ�ó�� ���� bmp �̹��� �ε��� ���Ǵ� ���� �ҽ� ���̺귯��
#include <glut.h>

// ȸ���� ���� ����
int prevX = 0;
int prevY = 0;
float rotationX = 0.0;
float rotationY = 0.0;

// Ȯ��,��Ҹ� ���� ����
float zoom = 1.0;

//��� ��ǥ ���� ���� ����
float px = -6;
float py = 11.7;
float pz = 11.9;

// �ؽ�ó ���� ����
GLuint frontTexture, backTexture, leftTexture, rightTexture, topTexture, bottomTexture;
GLuint bgfloor, bgsky, bg1, bg2, bg3, bg4;

// �Լ� ���� ����
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

// main �Լ�
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1920, 1080);
    glutCreateWindow("Steve in Minecraft");

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);

    loadTextures();

    //�ݹ� �Լ���
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

    // �� �ո� �ؽ�ó �ε�
    image = stbi_load("front.bmp", &width, &height, &channels, 0);
    glGenTextures(1, &frontTexture);
    glBindTexture(GL_TEXTURE_2D, frontTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    stbi_image_free(image);

    // �� �޸� �ؽ�ó �ε�
    image = stbi_load("back.bmp", &width, &height, &channels, 0);
    glGenTextures(1, &backTexture);
    glBindTexture(GL_TEXTURE_2D, backTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    stbi_image_free(image);

    // �� ���ʸ� �ؽ�ó �ε�
    image = stbi_load("left.bmp", &width, &height, &channels, 0);
    glGenTextures(1, &leftTexture);
    glBindTexture(GL_TEXTURE_2D, leftTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    stbi_image_free(image);

    // �� �����ʸ� �ؽ�ó �ε�
    image = stbi_load("right.bmp", &width, &height, &channels, 0);
    glGenTextures(1, &rightTexture);
    glBindTexture(GL_TEXTURE_2D, rightTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    stbi_image_free(image);

    // �� ��ܸ� �ؽ�ó �ε�
    image = stbi_load("top.bmp", &width, &height, &channels, 0);
    glGenTextures(1, &topTexture);
    glBindTexture(GL_TEXTURE_2D, topTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    stbi_image_free(image);

    // �� �ϴܸ� �ؽ�ó �ε�
    image = stbi_load("bottom.bmp", &width, &height, &channels, 0);
    glGenTextures(1, &bottomTexture);
    glBindTexture(GL_TEXTURE_2D, bottomTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    stbi_image_free(image);
}

// ��ǥ�� ǥ�� 
void drawGuide()
{
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0); //x��
    glVertex3f(-50, 0, 0);
    glVertex3f(50, 0, 0);
    glColor3f(0.0, 1.0, 0.0); //y��
    glVertex3f(0, -50, 0);
    glVertex3f(0, 50, 0);
    glColor3f(0.0, 0.0, 1.0); //z��
    glVertex3f(0, 0, -50);
    glVertex3f(0, 0, 50);
    glEnd();
    glPopMatrix();
}

//Steve�� (0, 0, 0)�� �� �ִ� ����
void drawLeftleg()
{
    // �޴ٸ�
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
    // �����ٸ�
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
    // ����
    glPushMatrix();
    glColor3f(0.06275f, 0.72941f, 0.72941f);
    glTranslatef(0.0, 17, 0.0);
    glScalef(8, 12, 4);
    glutSolidCube(1.0);
    glPopMatrix();
}
void drawLeftarm()
{
    // ����
    glPushMatrix();
    glColor3f(0.91765f, 0.72941f, 0.53725f);
    glTranslatef(-6, 19, 4);
    glRotatef(-70.0, 1.0, 0.0, 0.0);
    glScalef(4, 12, 4);
    glutSolidCube(1.0);
    glPopMatrix();

    //�Ҹ�
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
    // ������
    glPushMatrix();
    glColor3f(0.91765f, 0.72941f, 0.53725f);
    glTranslatef(6, 17.5, -3.5);
    glRotatef(45.0, 1.0, 0.0, 0.0);
    glScalef(4, 12, 4);
    glutSolidCube(1.0);
    glPopMatrix();

    //�Ҹ�
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
    // �Ӹ�
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
    //���
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

// display �Լ�
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Ȯ��, ���, ȸ��
    glTranslatef(0.0, -3.0, -40.0);
    glScalef(zoom, zoom, zoom);
    glRotatef(rotationX, 1.0, 0.0, 0.0);
    glRotatef(rotationY, 0.0, 1.0, 0.0);

    //��ǥ��
    drawGuide();

    //��
    drawHead();
    drawLeftleg();
    drawRightleg();
    drawBody();
    drawLeftarm();
    drawRightarm();

    //���
    drawPick();
   
    glFlush();
    glutSwapBuffers();
}

// reshape �Լ�
void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float)width / height, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

//���콺Ŭ��
void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        prevX = x;
        prevY = y;
    }
}

//�����̼�
void motion(int x, int y)
{
    rotationX += (y - prevY) * 0.5;
    rotationY += (x - prevX) * 0.5;
    prevX = x;
    prevY = y;
    glutPostRedisplay();
}

//Ű�Է� -> Ȯ��, ���
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

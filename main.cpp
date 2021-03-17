#include<windows.h>
#include <GL/glut.h>
#include<bits/stdc++.h>
#include <fstream>
using namespace std;

GLint height=600;
GLint width=800;
struct Point {
	GLint x;
	GLint y;
	GLfloat r;
	GLfloat g;
	GLfloat b;
};
int typ,psize,linewidth;
GLfloat red,green,blue;
Point p;
vector<Point> Points;
vector<Point> tmpP;
vector<int> shapeType;

void color(int n){
    float b=(float)(n%10)/10.0;
    n/=10;
    float g=(n%10)/10.0;
    n/=10;
    float r=(n%10)/10.0;
    glColor3f(r, g, b);
}
void text(int thick,int w,int h, char* m, int col){
    glLineWidth(thick);
    color(col);
    glTranslatef(w,h,0);
    for (int i = 0; i < strlen(m); i++) {
        glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, m[i]);
    }
}
void CurrentShape(){
    if(typ==1){
        glBegin(GL_POINTS);
        glColor3f(0,0,0); glVertex2d(200,height-35);
        glEnd();
    }
    else if(typ==2){
        glLineWidth((float)linewidth);
        glColor3f(0,0,0);
        glBegin(GL_LINES);
        glVertex2d(200,height-35);
        glVertex2d(250,height-35);
        glEnd();
    }
    else if(typ==3){
        glColor3f(0,0,0);
        glBegin(GL_TRIANGLES);
        glVertex2d(225,height-10);
        glVertex2d(200,height-60);
        glVertex2d(250,height-60);
        glEnd();
    }
    else if(typ==4){
        glColor3f(0,0,0);
        glBegin(GL_QUADS);
        glVertex2i(200,height-10);
        glVertex2i(250,height-10);
        glVertex2i(250,height-60);
        glVertex2i(200,height-60);
        glEnd();
    }
}
void CurrentColor(){
    cout<<"Color : "<<red<<" "<<green<<" "<<blue<<endl;
    glPointSize(12);
    glBegin(GL_POINTS);
    glColor3f(red,0,0); glVertex2d(10,height-20);
    glColor3f(0,green,0); glVertex2d(10,height-35);
    glColor3f(0,0,blue); glVertex2d(10,height-50);
    glEnd();
    glColor3f(red,green,blue);
    glBegin(GL_QUADS);
    glVertex2i(20,height-10);
    glVertex2i(70,height-10);
    glVertex2i(70,height-60);
    glVertex2i(20,height-60);
    glEnd();
}
void printPoints(){
    glPointSize(psize);
    glColor3f(0,0,0);
	glBegin(GL_POINTS);
	for(int i=0; i<tmpP.size(); i++){
        glVertex2i(tmpP[i].x, tmpP[i].y);
	}
	glEnd();
}
void draw() {

	glClear(GL_COLOR_BUFFER_BIT);
	int i=0;
    for(int j=0; j<shapeType.size(); j++){
        int t=shapeType[j];
        if(t==4){
            glBegin(GL_QUADS);
                while(t && i<Points.size()){
                    glColor3f(Points[i].r,Points[i].g, Points[i].b);
                    glVertex2i(Points[i].x, Points[i].y);
                    i++; t--;
                }
            glEnd();
        }
        else if(t==3){
            glBegin(GL_TRIANGLES);
                while(t && i<Points.size()){
                    glColor3f(Points[i].r,Points[i].g, Points[i].b);
                    glVertex2i(Points[i].x, Points[i].y);
                    i++; t--;
                }
            glEnd();
        }
        else if(t==2){
            glLineWidth((float)linewidth);
            glBegin(GL_LINES);
                while(t && i<Points.size()){
                    glColor3f(Points[i].r,Points[i].g, Points[i].b);
                    glVertex2i(Points[i].x, Points[i].y);
                    i++; t--;
                }
            glEnd();
        }
        else if(t==1){
            glBegin(GL_POINTS);
                while(t && i<Points.size()){
                    glColor3f(Points[i].r,Points[i].g, Points[i].b);
                    glVertex2i(Points[i].x, Points[i].y);
                    i++; t--;
                }
            glEnd();
        }
    }


	printPoints();
    CurrentColor();
    CurrentShape();
	glFlush();
}

void myMouseFunc(int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        p.r=red; p.g=green; p.b=blue;
		p.x = x;
		p.y = height - y;
		tmpP.push_back(p);

		if(tmpP.size()>=typ){
                shapeType.push_back(typ);
            for(int i=0; i<typ; i++){
                p.r = tmpP[i].r ;
                p.g = tmpP[i].g ;
                p.b = tmpP[i].b ;
                p.x = tmpP[i].x ;
                p.y = tmpP[i].y;
                Points.push_back(p);
            }
            tmpP.clear();
		}
		draw();
	}
}
void AllClear(){
    shapeType.clear();
    Points.clear();
    tmpP.clear();
    draw();
}
void tmpClear(){
    tmpP.clear();
    draw();
}
void removeLast(){
    if(shapeType.size()>0){
        int t=shapeType[shapeType.size()-1];
        shapeType.pop_back();
        while(t--){
            Points.pop_back();
        }
        draw();
    }

}
void SetColor(unsigned char key){
    if(key=='r'){red = red+0.1; if(red>1.01)red=0; }
    else if(key=='g'){green = green+0.1; if(green>1.01)green=0; }
    else {blue = blue+0.1; if(blue>1.01)blue=0; }
    draw();
}
void Save(){
    string filename;
    cout<<"File name To save : ";
    //cin>>filename;
    cout<<"(Wait!!!)Saving into File .......\n";
    ofstream file;
    file.open("1.txt");
    if(file){
        for(int i=0; i<Points.size(); i++){
            //file<<Points[i].r<<" ";
            //file<<Points[i].g<<" ";
            //file<<Points[i].b<<" ";
            //file<<Points[i].x<<" ";
            cout<<".";
            file<<"a ";
            file<<Points[i].x;
            file<<" ";
            file<<Points[i].y;
            file<<"\n";
        }
        file.close();
    }
    else if(!file)cout<<"FILE not found\n";

    cout<<"\nFile Saved.\n";

}
static void key(unsigned char key, int x, int y)
{
    if(key=='r' || key=='g' || key=='b')SetColor(key);
    else if(key=='p')AllClear();
    else if(key=='c')tmpClear();
    else if(key=='z')removeLast();
    else if(key=='s')Save();
    else if(key=='q')exit(EXIT_SUCCESS);
    else if(key=='1'){typ=1; draw(); }
    else if(key=='2'){typ=2; draw(); }
    else if(key=='3'){typ=3; draw(); }
    else if(key=='4'){typ=4; draw(); }
}

void init() {
    typ=4; red=0; green=0; blue=0; psize=4; linewidth =5;
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	gluOrtho2D(0.0f, width, 0.0f, height);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(width,height);
    glutInitWindowPosition(10,10);

    glutCreateWindow("NO pen GL Illustrator- best drawing software");
    glutDisplayFunc(draw);
    glutKeyboardFunc(key);
    glutMouseFunc(myMouseFunc);

    init();

    glutMainLoop();

    return EXIT_SUCCESS;
}

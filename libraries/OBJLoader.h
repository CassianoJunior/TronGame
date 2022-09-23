#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <iostream>
#include <stdio.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>  

GLuint object;
char ch='1';

GLuint loadObj(char* fname){
    FILE *fp;
    int read;
    GLfloat x, y, z;
    char ch;
    object=glGenLists(1);
    fp=fopen(fname,"r");
    if (!fp){
        printf("can't open file %s\n", fname);
        exit(1);
    }
    glPointSize(2.0);
    glNewList(object, GL_COMPILE);
    
    {
        glPushMatrix();
        glBegin(GL_POINTS);
        while(!(feof(fp))){
            read=fscanf(fp,"%c %f %f %f",&ch,&x,&y,&z);
            if(read==4&&ch=='v'){
                glVertex3f(x,y,z);
            }
        }
        glEnd();
    }

    glPopMatrix();
    glEndList();
    fclose(fp);

    return object;
}

#endif
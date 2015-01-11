#include <iostream>
#include <GL/glut.h>
#include <stdlib.h>
#include <bits/stdc++.h>
#include "vector3D.h"
#include "vectorOperation.h"
#include "glm1.h"
#include "text3d.h"
#include "imageloader.h"

using namespace std;

struct object {
	vector3D center;
	vector3D headDir;
	vector3D upDir;
	vector3D velocity;
	float left;
	float right;
	float front;
	float back;
	float top;
	float bottom;
};

struct track {
	vector3D start1;
	vector3D end1;
	vector3D start2;
	vector3D end2;
	vector3D center;
	float radius1;
	float radius2;
	float angle;
	string id;
};

GLMmodel* myModel;
GLMmodel* fence;
GLMmodel* tree;
GLMmodel* tree_1;
GLMmodel* missile_obj;

GLuint _textureId;
GLuint _textureId_bike;
GLuint _textureId_tree;
GLuint _textureId_bike_1;
GLuint _textureId_road;
GLuint _textureId_tyre1;
GLuint _textureId_tyre2;
GLuint _textureId_fire1;
GLuint _textureId_fire2;
GLuint _textureId_meter;
GLuint _textureId_flag;

GLuint DLid;
GLuint DLid_fence;
GLuint DLid_tree;
GLuint DLid_tree_1;
GLuint DLid_missile;
GLuint DLid_tunnel;

//GLuint DLid_tree_1;
GLMmodel* tunnel;
GLuint _textureId_bridge;

object mainPlane;
object plane2;
object plane3;
object plane4;
object plane5;
object plane6;
object plane7;
object plane8;

object missile;
vector3D camera;
vector3D camera2;
vector3D camera3;
vector3D up(0.0, 1.0, 0.0);
int tyre = 0;
int track_id = 0;
int plane2_track = 0;
int plane3_track = 0;
int plane4_track = 0;
int plane5_track = 0;
int plane6_track = 0;
int plane7_track = 0;
int plane8_track = 0;
int missile1_track = 0;
int fire = 0;
int blast = 0;
int collided = 1;
int Lap = 1;
int Lap_2 = 1;
int Lap_3 = 1;
int Lap_4 = 1;
int Lap_5 = 1;
int Lap_6 = 1;
int Lap_7 = 1;
int Lap_8 = 1;
int print_pos = 8;
int Total_laps=2;

int plane_position = 8;
bool GameOver = false;
bool store_position=false;

float rotation = 2.0;
float auto_rotation = 2.0;
float auto_rotation2 = 2.0;
float auto_rotation3 = 2.0;
float auto_rotation4 = 2.0;
float auto_rotation5 = 2.0;
float auto_rotation6 = 2.0;
float auto_rotation7 = 2.0;
float auto_rotation8 = 2.0;

float rightRotation = 0.0;
float leftRotation = 0.0;
float rightRotationY = 0.0;
float leftRotationY = 0.0;

float rightRotation2 = 0.0;
float leftRotation2 = 0.0;
float rightRotationY2 = 0.0;
float leftRotationY2 = 0.0;

float rightRotation3 = 0.0;
float leftRotation3 = 0.0;
float rightRotationY3 = 0.0;
float leftRotationY3 = 0.0;

float rightRotation4 = 0.0;
float leftRotation4 = 0.0;
float rightRotationY4 = 0.0;
float leftRotationY4 = 0.0;

float rightRotation5 = 0.0;
float leftRotation5 = 0.0;
float rightRotationY5 = 0.0;
float leftRotationY5 = 0.0;

float rightRotation6 = 0.0;
float leftRotation6 = 0.0;
float rightRotationY6 = 0.0;
float leftRotationY6 = 0.0;

float rightRotation7 = 0.0;
float leftRotation7 = 0.0;
float rightRotationY7 = 0.0;
float leftRotationY7 = 0.0;

float rightRotation8 = 0.0;
float leftRotation8 = 0.0;
float rightRotationY8 = 0.0;
float leftRotationY8 = 0.0;

float rightRotationYM1 = 0.0;
float leftRotationYM1 = 0.0;

bool rightKey = false;
bool leftKey = false;

vector<track> track_states;

void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-100.0,100.0,0.0,100.0,1,2000);

	gluPerspective(45.0, (double) w / (double) h, 0.20, 2000.0);
}

GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0,
			GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
	return textureId;
}

void display_list_texture(GLMmodel* myModel, GLuint _textureId) {
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glmFacetNormals(myModel);
	glmVertexNormals(myModel, 90);
	glmDraw(myModel, GLM_SMOOTH | GLM_TEXTURE);
	glDisable(GL_TEXTURE_2D);

}

void display_list_notexture(GLMmodel* myModel) {
	glmFacetNormals(myModel);
	glmVertexNormals(myModel, 90);
	glmDraw(myModel, GLM_SMOOTH | GLM_TEXTURE);
}

GLuint createDL_texture(GLMmodel* myModel, GLuint _textureId) {
	GLuint snowManDL;
	snowManDL = glGenLists(1);
	glNewList(snowManDL, GL_COMPILE);
	display_list_texture(myModel, _textureId);
	glEndList();
	return (snowManDL);
}

GLuint createDL_notexture(GLMmodel* myModel) {
	GLuint snowManDL;
	snowManDL = glGenLists(1);
	glNewList(snowManDL, GL_COMPILE);
	display_list_notexture(myModel);
	glEndList();
	return (snowManDL);
}

void initRendering() {
	glClearColor(119.0 / 255.0, 136.0 / 255.0, 153.0 / 255.0, 0.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_MODELVIEW);
	t3dInit();
	Image* image = loadBMP("aircraft tex.bmp");
	_textureId_bike = loadTexture(image);
	delete image;

	image = loadBMP("road.bmp");
	_textureId_road = loadTexture(image);
	delete image;

	image = loadBMP("shu1.bmp");
	_textureId_tree = loadTexture(image);
	delete image;

	image = loadBMP("water.bmp");
	_textureId = loadTexture(image);
	delete image;

	image = loadBMP("blast.bmp");
	_textureId_fire1 = loadTexture(image);
	delete image;

	image = loadBMP("blast_1.bmp");
	_textureId_fire2 = loadTexture(image);
	delete image;

	image = loadBMP("meter2.bmp");
	_textureId_meter = loadTexture(image);
	delete image;

	image = loadBMP("tex.bmp");
	_textureId_bridge = loadTexture(image);
	delete image;

	image = loadBMP("flag.bmp");
	_textureId_flag = loadTexture(image);
	delete image;
	DLid_tunnel = createDL_texture(tunnel, _textureId_bridge);

	DLid = createDL_texture(myModel, _textureId_bike);
	DLid_fence = createDL_notexture(fence);
	DLid_tree = createDL_texture(tree, _textureId_tree);
	DLid_tree_1 = createDL_notexture(tree_1);
	DLid_missile = createDL_notexture(missile_obj);

}

void track_1() {

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTranslatef(0, -0.1, 0);

	for (float image_x = -100; image_x < 500; image_x += 20) {
		for (float image_y = -250; image_y < 400; image_y += 20) {
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(image_x, 0.0, image_y);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(image_x, 0.0, image_y + 20);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(image_x + 20, 0.0, image_y + 20);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(image_x + 20, 0.0, image_y);
			glEnd();
		}

	}
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -150);
	glEnable(GL_TEXTURE_2D);
	for (float image_x = 0; image_x < 300; image_x += 10) {
		if (image_x == 50) {

			glBindTexture(GL_TEXTURE_2D, _textureId_flag);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(image_x, 0.0, -20.0);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(image_x, 0.0, 20);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(image_x + 10, 0.0, 20);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(image_x + 10, 0.0, -20);
			glEnd();

		} else {

			glBindTexture(GL_TEXTURE_2D, _textureId_road);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(image_x, 0.0, -20.0);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(image_x, 0.0, 20);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(image_x + 10, 0.0, 20);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(image_x + 10, 0.0, -20);
			glEnd();
		}
	}
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(300, 0, -90);
	glRotatef(90, 0, 1, 0);
	float terrain_angle = 0;
	float radius_inner = 40.0f;
	float radius_outer = 80.0f;
	vector3D normal_to_plane(0.0, 1.0, 0.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId_road);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	while (terrain_angle <= 180) {

		vector3D normal_inner(
				radius_inner * cos(terrain_angle * (3.14) / 180.0), 0,
				radius_inner * sin(terrain_angle * (3.14) / 180.0));
		vector3D normal_outer(
				radius_outer * cos(terrain_angle * (3.14) / 180.0), 0,
				radius_outer * sin(terrain_angle * (3.14) / 180.0));
		vector3D normal_normaize = normalise(normal_inner);

		vector3D tangent = crossProduct(normal_to_plane, normal_normaize);

		vector3D first = add(normal_inner, constProduct(tangent, 1.0));
		vector3D second = subtract(normal_inner, constProduct(tangent, 1.0));
		vector3D fourth = add(normal_outer, constProduct(tangent, 1.0));
		vector3D third = subtract(normal_outer, constProduct(tangent, 1.0));

		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(first.x, 0.0, first.z);
		glVertex3f(second.x, 0.0, second.z);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(fourth.x, 0.0, fourth.z);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(third.x, 0.0, third.z);
		glTexCoord2f(0.0f, 1.0f);

		glEnd();
		terrain_angle = terrain_angle + 0.7;

	}
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(300, 0, 30);
	glRotatef(180, 0, 1, 0);
	terrain_angle = 0;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId_road);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	while (terrain_angle <= 90) {
		vector3D normal_inner(
				radius_inner * cos(terrain_angle * (3.14) / 180.0), 0,
				radius_inner * sin(terrain_angle * (3.14) / 180.0));
		vector3D normal_outer(
				radius_outer * cos(terrain_angle * (3.14) / 180.0), 0,
				radius_outer * sin(terrain_angle * (3.14) / 180.0));
		vector3D normal_normaize = normalise(normal_inner);
		vector3D tangent = crossProduct(normal_to_plane, normal_normaize);
		vector3D first = add(normal_inner, constProduct(tangent, 1.0));
		vector3D second = subtract(normal_inner, constProduct(tangent, 1.0));
		vector3D fourth = add(normal_outer, constProduct(tangent, 1.0));
		vector3D third = subtract(normal_outer, constProduct(tangent, 1.0));

		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(first.x, 0.0, first.z);
		glVertex3f(second.x, 0.0, second.z);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(fourth.x, 0.0, fourth.z);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(third.x, 0.0, third.z);
		glTexCoord2f(0.0f, 1.0f);

		glEnd();
		terrain_angle = terrain_angle + 0.7;

	}
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(240, 0, 30);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId_road);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	for (float image_x = 0; image_x < 150; image_x += 10) {
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-20.0, 0.0, image_x);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(20.0, 0.0, image_x);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(20.0, 0.0, image_x + 10);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-20.0, 0.0, image_x + 10);
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(300, 0, 180);
	glRotatef(270, 0, 1, 0);
	terrain_angle = 0;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId_road);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	while (terrain_angle <= 90) {
		vector3D normal_inner(
				radius_inner * cos(terrain_angle * (3.14) / 180.0), 0,
				radius_inner * sin(terrain_angle * (3.14) / 180.0));
		vector3D normal_outer(
				radius_outer * cos(terrain_angle * (3.14) / 180.0), 0,
				radius_outer * sin(terrain_angle * (3.14) / 180.0));
		vector3D normal_normaize = normalise(normal_inner);
		vector3D tangent = crossProduct(normal_to_plane, normal_normaize);
		vector3D first = add(normal_inner, constProduct(tangent, 1.0));
		vector3D second = subtract(normal_inner, constProduct(tangent, 1.0));
		vector3D fourth = add(normal_outer, constProduct(tangent, 1.0));
		vector3D third = subtract(normal_outer, constProduct(tangent, 1.0));

		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(first.x, 0.0, first.z);
		glVertex3f(second.x, 0.0, second.z);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(fourth.x, 0.0, fourth.z);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(third.x, 0.0, third.z);
		glTexCoord2f(0.0f, 1.0f);

		glEnd();
		terrain_angle = terrain_angle + 0.7;

	}
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(300, 0, 240);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId_road);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	for (float image_x = 0; image_x < 100; image_x += 10) {
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(image_x, 0.0, -20.0);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(image_x, 0.0, 20);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(image_x + 10, 0.0, 20);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(image_x + 10, 0.0, -20);
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(400, 0, 300);
	glRotatef(90, 0, 1, 0);
	terrain_angle = 0;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId_road);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	while (terrain_angle <= 180) {
		vector3D normal_inner(
				radius_inner * cos(terrain_angle * (3.14) / 180.0), 0,
				radius_inner * sin(terrain_angle * (3.14) / 180.0));
		vector3D normal_outer(
				radius_outer * cos(terrain_angle * (3.14) / 180.0), 0,
				radius_outer * sin(terrain_angle * (3.14) / 180.0));
		vector3D normal_normaize = normalise(normal_inner);
		vector3D tangent = crossProduct(normal_to_plane, normal_normaize);
		vector3D first = add(normal_inner, constProduct(tangent, 1.0));
		vector3D second = subtract(normal_inner, constProduct(tangent, 1.0));
		vector3D fourth = add(normal_outer, constProduct(tangent, 1.0));
		vector3D third = subtract(normal_outer, constProduct(tangent, 1.0));

		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(first.x, 0.0, first.z);
		glVertex3f(second.x, 0.0, second.z);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(fourth.x, 0.0, fourth.z);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(third.x, 0.0, third.z);
		glTexCoord2f(0.0f, 1.0f);

		glEnd();
		terrain_angle = terrain_angle + 0.7;

	}
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(400, 0, 360);
	glRotatef(180, 0, 1, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId_road);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	for (float image_x = 250; image_x >= 0; image_x -= 10) {
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(image_x, 0.0, -20.0);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(image_x, 0.0, 20);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(image_x + 10, 0.0, 20);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(image_x + 10, 0.0, -20);
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(150, 0, 300);
	glRotatef(270, 0, 1, 0);
	terrain_angle = 0;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId_road);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	while (terrain_angle <= 90) {
		vector3D normal_inner(
				radius_inner * cos(terrain_angle * (3.14) / 180.0), 0,
				radius_inner * sin(terrain_angle * (3.14) / 180.0));
		vector3D normal_outer(
				radius_outer * cos(terrain_angle * (3.14) / 180.0), 0,
				radius_outer * sin(terrain_angle * (3.14) / 180.0));
		vector3D normal_normaize = normalise(normal_inner);
		vector3D tangent = crossProduct(normal_to_plane, normal_normaize);
		vector3D first = add(normal_inner, constProduct(tangent, 1.0));
		vector3D second = subtract(normal_inner, constProduct(tangent, 1.0));
		vector3D fourth = add(normal_outer, constProduct(tangent, 1.0));
		vector3D third = subtract(normal_outer, constProduct(tangent, 1.0));

		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(first.x, 0.0, first.z);
		glVertex3f(second.x, 0.0, second.z);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(fourth.x, 0.0, fourth.z);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(third.x, 0.0, third.z);
		glTexCoord2f(0.0f, 1.0f);

		glEnd();
		terrain_angle = terrain_angle + 0.7;

	}
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(90, 0, 300);
	glRotatef(180, 0, 1, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId_road);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	for (float image_x = 0; image_x < 250; image_x += 10) {
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-20.0, 0.0, image_x);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(20.0, 0.0, image_x);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(20.0, 0.0, image_x + 10);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-20.0, 0.0, image_x + 10);
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(30, 0, 50);
	glRotatef(90, 0, 1, 0);
	terrain_angle = 0;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId_road);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	while (terrain_angle <= 90) {
		vector3D normal_inner(
				radius_inner * cos(terrain_angle * (3.14) / 180.0), 0,
				radius_inner * sin(terrain_angle * (3.14) / 180.0));
		vector3D normal_outer(
				radius_outer * cos(terrain_angle * (3.14) / 180.0), 0,
				radius_outer * sin(terrain_angle * (3.14) / 180.0));
		vector3D normal_normaize = normalise(normal_inner);
		vector3D tangent = crossProduct(normal_to_plane, normal_normaize);
		vector3D first = add(normal_inner, constProduct(tangent, 1.0));
		vector3D second = subtract(normal_inner, constProduct(tangent, 1.0));
		vector3D fourth = add(normal_outer, constProduct(tangent, 1.0));
		vector3D third = subtract(normal_outer, constProduct(tangent, 1.0));

		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(first.x, 0.0, first.z);
		glVertex3f(second.x, 0.0, second.z);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(fourth.x, 0.0, fourth.z);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(third.x, 0.0, third.z);
		glTexCoord2f(0.0f, 1.0f);

		glEnd();
		terrain_angle = terrain_angle + 0.7;

	}
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -90);
	glRotatef(180, 0, 1, 0);
	terrain_angle = 0;

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId_road);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	while (terrain_angle <= 90) {
		vector3D normal_inner(
				radius_inner * cos(terrain_angle * (3.14) / 180.0), 0,
				radius_inner * sin(terrain_angle * (3.14) / 180.0));
		vector3D normal_outer(
				radius_outer * cos(terrain_angle * (3.14) / 180.0), 0,
				radius_outer * sin(terrain_angle * (3.14) / 180.0));
		vector3D normal_normaize = normalise(normal_inner);
		vector3D tangent = crossProduct(normal_to_plane, normal_normaize);
		vector3D first = add(normal_inner, constProduct(tangent, 1.0));
		vector3D second = subtract(normal_inner, constProduct(tangent, 1.0));
		vector3D fourth = add(normal_outer, constProduct(tangent, 1.0));
		vector3D third = subtract(normal_outer, constProduct(tangent, 1.0));

		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(first.x, 0.0, first.z);
		glVertex3f(second.x, 0.0, second.z);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(fourth.x, 0.0, fourth.z);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(third.x, 0.0, third.z);
		glTexCoord2f(0.0f, 1.0f);

		glEnd();
		terrain_angle = terrain_angle + 0.7;

	}
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(30, 0, -10);
	glRotatef(180, 0, 1, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId_road);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	for (float image_x = 0; image_x < 30; image_x += 10) {
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(image_x, 0.0, -20.0);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(image_x, 0.0, 20);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(image_x + 10, 0.0, 20);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(image_x + 10, 0.0, -20);
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -70);
	glRotatef(270, 0, 1, 0);
	terrain_angle = 0;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId_road);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	while (terrain_angle <= 90) {
		vector3D normal_inner(
				radius_inner * cos(terrain_angle * (3.14) / 180.0), 0,
				radius_inner * sin(terrain_angle * (3.14) / 180.0));
		vector3D normal_outer(
				radius_outer * cos(terrain_angle * (3.14) / 180.0), 0,
				radius_outer * sin(terrain_angle * (3.14) / 180.0));
		vector3D normal_normaize = normalise(normal_inner);
		vector3D tangent = crossProduct(normal_to_plane, normal_normaize);
		vector3D first = add(normal_inner, constProduct(tangent, 1.0));
		vector3D second = subtract(normal_inner, constProduct(tangent, 1.0));
		vector3D fourth = add(normal_outer, constProduct(tangent, 1.0));
		vector3D third = subtract(normal_outer, constProduct(tangent, 1.0));

		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(first.x, 0.0, first.z);
		glVertex3f(second.x, 0.0, second.z);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(fourth.x, 0.0, fourth.z);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(third.x, 0.0, third.z);
		glTexCoord2f(0.0f, 1.0f);

		glEnd();
		terrain_angle = terrain_angle + 0.7;

	}
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(-60, 0, -70);
	glRotatef(180, 0, 1, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId_road);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	for (float image_x = 0; image_x < 20; image_x += 10) {
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-20.0, 0.0, image_x);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(20.0, 0.0, image_x);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(20.0, 0.0, image_x + 10);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-20.0, 0.0, image_x + 10);
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

}

void track_1_texture() {
	// straight parts first
	if (track_id % 21 == 20 || track_id % 21 == 0) {
		glPushMatrix();
		glTranslatef(0, 0, -150);
		for (int image_x = 0; image_x <= 100; image_x += 5) {
			glPushMatrix();
			glTranslatef(image_x, 0, -20);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, 20);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, 21);
			glCallList(DLid_tree);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, -21);
			glCallList(DLid_tree);
			glPopMatrix();
		}
		glPopMatrix();
	}

	if (track_id % 21 == 0 || track_id % 21 == 1) {
		glPushMatrix();
		glTranslatef(100, 0, -150);
		for (int image_x = 0; image_x <= 100; image_x += 5) {
			glPushMatrix();
			glTranslatef(image_x, 0, -20);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, 20);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, 21);
			glCallList(DLid_tree);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, -21);
			glCallList(DLid_tree);
			glPopMatrix();
		}
		glPopMatrix();
	}

	if (track_id % 21 == 1 || track_id % 21 == 2) {
		glPushMatrix();
		glTranslatef(200, 0, -150);
		for (int image_x = 0; image_x <= 100; image_x += 5) {
			glPushMatrix();
			glTranslatef(image_x, 0, -20);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, 20);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, 21);
			glCallList(DLid_tree);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, -21);
			glCallList(DLid_tree);
			glPopMatrix();
		}
		glPopMatrix();
	}

	if (track_id % 21 == 5 || track_id % 21 == 6) {
		glPushMatrix();
		glTranslatef(240, 0, 30);
		for (int image_x = 0; image_x <= 150; image_x += 5) {
			glPushMatrix();
			glTranslatef(20, 0, image_x);
			glRotatef(90, 0, 1, 0);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(-20, 0, image_x);
			glRotatef(90, 0, 1, 0);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(-21, 0, image_x);
			glCallList(DLid_tree);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(21, 0, image_x);
			glCallList(DLid_tree);
			glPopMatrix();
		}
		glPopMatrix();

	}

	if (track_id % 21 == 7 || track_id % 21 == 8) {
		glPushMatrix();
		glTranslatef(300, 0, 240);
		for (int image_x = 0; image_x <= 100; image_x += 5) {
			glPushMatrix();
			glTranslatef(image_x, 0, -20);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, 20);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, 21);
			glCallList(DLid_tree);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, -21);
			glCallList(DLid_tree);
			glPopMatrix();
		}
		glPopMatrix();

	}
	if (track_id % 21 == 10 || track_id % 21 == 11) {

		glPushMatrix();
		glTranslatef(400, 0, 360);
		glRotatef(180, 0, 1, 0);
		for (int image_x = 0; image_x <= 125; image_x += 5) {
			glPushMatrix();
			glTranslatef(image_x, 0, -20);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, 20);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, 21);
			glCallList(DLid_tree);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, -21);
			glCallList(DLid_tree);
			glPopMatrix();
		}
		glPopMatrix();

	}

	if (track_id % 21 == 11 || track_id % 21 == 12) {

		glPushMatrix();
		glTranslatef(275, 0, 360);
		glRotatef(180, 0, 1, 0);
		for (int image_x = 0; image_x <= 125; image_x += 5) {
			glPushMatrix();
			glTranslatef(image_x, 0, -20);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, 20);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, 21);
			glCallList(DLid_tree);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, -21);
			glCallList(DLid_tree);
			glPopMatrix();
		}
		glPopMatrix();

	}

	if (track_id % 21 == 13 || track_id % 21 == 14) {

		glPushMatrix();
		glTranslatef(90, 0, 300);
		glRotatef(180, 0, 1, 0);
		for (int image_x = 0; image_x <= 125; image_x += 5) {
			glPushMatrix();
			glTranslatef(20, 0, image_x);
			glRotatef(90, 0, 1, 0);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(-20, 0, image_x);
			glRotatef(90, 0, 1, 0);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(-21, 0, image_x);
			glCallList(DLid_tree);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(21, 0, image_x);
			glCallList(DLid_tree);
			glPopMatrix();
		}
		glPopMatrix();

	}

	if (track_id % 21 == 14 || track_id % 21 == 15 || track_id % 21 == 16) {

		glPushMatrix();
		glTranslatef(90, 0, 175);
		glRotatef(180, 0, 1, 0);
		for (int image_x = 0; image_x <= 125; image_x += 5) {
			glPushMatrix();
			glTranslatef(20, 0, image_x);
			glRotatef(90, 0, 1, 0);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(-20, 0, image_x);
			glRotatef(90, 0, 1, 0);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(-21, 0, image_x);
			glCallList(DLid_tree);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(21, 0, image_x);
			glCallList(DLid_tree);
			glPopMatrix();
		}
		glPopMatrix();

	}

	if (track_id % 21 == 16 || track_id % 21 == 17 || track_id % 21 == 20) {

		glPushMatrix();
		glTranslatef(30, 0, -10);
		glRotatef(180, 0, 1, 0);
		for (int image_x = 0; image_x <= 30; image_x += 5) {
			glPushMatrix();
			glTranslatef(image_x, 0, -20);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, 20);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, 21);
			glCallList(DLid_tree);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, -21);
			glCallList(DLid_tree);
			glPopMatrix();
		}
		glPopMatrix();

	}

	if (track_id % 21 == 18 || track_id % 21 == 19 || track_id % 21 == 0
			|| track_id % 21 == 20) {
		glPushMatrix();
		glTranslatef(-60, 0, -70);
		glRotatef(180, 0, 1, 0);
		for (int image_x = 0; image_x <= 20; image_x += 5) {
			glPushMatrix();
			glTranslatef(20, 0, image_x);
			glRotatef(90, 0, 1, 0);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(-20, 0, image_x);
			glRotatef(90, 0, 1, 0);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(-21, 0, image_x);
			glCallList(DLid_tree);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(21, 0, image_x);
			glCallList(DLid_tree);
			glPopMatrix();
		}
		glPopMatrix();

	}

	//Circular Parts
	float terrain_angle = 0;
	float radius_inner = 40.0f;
	float radius_outer = 80.0f;
	vector3D normal_to_plane(0.0, 1.0, 0.0);

	if (track_id % 21 == 2 || track_id % 21 == 3) {
		glPushMatrix();
		glTranslatef(300, 0, -90);
		glRotatef(90, 0, 1, 0);
		terrain_angle = 0;
		while (terrain_angle <= 90) {
			glPushMatrix();
			glTranslatef(radius_inner * cos(terrain_angle * (3.14) / 180.0), 0,
					radius_inner * sin(terrain_angle * (3.14) / 180.0));
			glRotatef(90 - terrain_angle, 0, 1, 0);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(
					(radius_inner - 1) * cos(terrain_angle * (3.14) / 180.0), 0,
					(radius_inner - 1) * sin(terrain_angle * (3.14) / 180.0));
			glCallList(DLid_tree);
			glPopMatrix();

			terrain_angle = terrain_angle + 7;
		}

		terrain_angle = 0;
		while (terrain_angle <= 90) {
			glPushMatrix();
			glTranslatef(radius_outer * cos(terrain_angle * (3.14) / 180.0), 0,
					radius_outer * sin(terrain_angle * (3.14) / 180.0));
			glRotatef(90 - terrain_angle, 0, 1, 0);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(
					(radius_outer + 1) * cos(terrain_angle * (3.14) / 180.0), 0,
					(radius_outer + 1) * sin(terrain_angle * (3.14) / 180.0));
			glCallList(DLid_tree);
			glPopMatrix();

			terrain_angle = terrain_angle + 4;
		}

		glPopMatrix();
	}

	if (track_id % 21 == 3 || track_id % 21 == 4) {
		glPushMatrix();
		glTranslatef(300, 0, -90);
//		glRotatef(90, 0, 1, 0);
		terrain_angle = 0;
		while (terrain_angle <= 90) {
			glPushMatrix();
			glTranslatef(radius_inner * cos(terrain_angle * (3.14) / 180.0), 0,
					radius_inner * sin(terrain_angle * (3.14) / 180.0));
			glRotatef(90 - terrain_angle, 0, 1, 0);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(
					(radius_inner - 1) * cos(terrain_angle * (3.14) / 180.0), 0,
					(radius_inner - 1) * sin(terrain_angle * (3.14) / 180.0));
			glCallList(DLid_tree);
			glPopMatrix();

			terrain_angle = terrain_angle + 7;
		}

		terrain_angle = 0;
		while (terrain_angle <= 90) {
			glPushMatrix();
			glTranslatef(radius_outer * cos(terrain_angle * (3.14) / 180.0), 0,
					radius_outer * sin(terrain_angle * (3.14) / 180.0));
			glRotatef(90 - terrain_angle, 0, 1, 0);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(
					(radius_outer + 1) * cos(terrain_angle * (3.14) / 180.0), 0,
					(radius_outer + 1) * sin(terrain_angle * (3.14) / 180.0));
			glCallList(DLid_tree);
			glPopMatrix();

			terrain_angle = terrain_angle + 4;
		}

		glPopMatrix();
	}

	if (track_id % 21 == 4 || track_id % 21 == 5) {
		glPushMatrix();
		glTranslatef(300, 0, 30);
		glRotatef(180, 0, 1, 0);
		terrain_angle = 0;
		while (terrain_angle <= 90) {
			glPushMatrix();
			glTranslatef(radius_inner * cos(terrain_angle * (3.14) / 180.0), 0,
					radius_inner * sin(terrain_angle * (3.14) / 180.0));
			glRotatef(90 - terrain_angle, 0, 1, 0);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(
					(radius_inner - 1) * cos(terrain_angle * (3.14) / 180.0), 0,
					(radius_inner - 1) * sin(terrain_angle * (3.14) / 180.0));
			glCallList(DLid_tree);
			glPopMatrix();

			terrain_angle = terrain_angle + 7;
		}

		terrain_angle = 0;
		while (terrain_angle <= 90) {
			glPushMatrix();
			glTranslatef(radius_outer * cos(terrain_angle * (3.14) / 180.0), 0,
					radius_outer * sin(terrain_angle * (3.14) / 180.0));
			glRotatef(90 - terrain_angle, 0, 1, 0);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(
					(radius_outer + 1) * cos(terrain_angle * (3.14) / 180.0), 0,
					(radius_outer + 1) * sin(terrain_angle * (3.14) / 180.0));
			glCallList(DLid_tree);
			glPopMatrix();

			terrain_angle = terrain_angle + 4;
		}

		glPopMatrix();

	}

	if (track_id % 21 == 6 || track_id % 21 == 7) {
		glPushMatrix();
		glTranslatef(300, 0, 180);
		glRotatef(270, 0, 1, 0);
		terrain_angle = 0;
		while (terrain_angle <= 90) {
			glPushMatrix();
			glTranslatef(radius_inner * cos(terrain_angle * (3.14) / 180.0), 0,
					radius_inner * sin(terrain_angle * (3.14) / 180.0));
			glRotatef(90 - terrain_angle, 0, 1, 0);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(
					(radius_inner - 1) * cos(terrain_angle * (3.14) / 180.0), 0,
					(radius_inner - 1) * sin(terrain_angle * (3.14) / 180.0));
			glCallList(DLid_tree);
			glPopMatrix();

			terrain_angle = terrain_angle + 7;
		}

		terrain_angle = 0;
		while (terrain_angle <= 90) {
			glPushMatrix();
			glTranslatef(radius_outer * cos(terrain_angle * (3.14) / 180.0), 0,
					radius_outer * sin(terrain_angle * (3.14) / 180.0));
			glRotatef(90 - terrain_angle, 0, 1, 0);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(
					(radius_outer + 1) * cos(terrain_angle * (3.14) / 180.0), 0,
					(radius_outer + 1) * sin(terrain_angle * (3.14) / 180.0));
			glCallList(DLid_tree);
			glPopMatrix();

			terrain_angle = terrain_angle + 4;
		}

		glPopMatrix();

	}

	if (track_id % 21 == 8 || track_id % 21 == 9) {

		glPushMatrix();
		glTranslatef(400, 0, 300);
		glRotatef(90, 0, 1, 0);
		terrain_angle = 0;
		while (terrain_angle <= 90) {
			glPushMatrix();
			glTranslatef(radius_inner * cos(terrain_angle * (3.14) / 180.0), 0,
					radius_inner * sin(terrain_angle * (3.14) / 180.0));
			glRotatef(90 - terrain_angle, 0, 1, 0);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(
					(radius_inner - 1) * cos(terrain_angle * (3.14) / 180.0), 0,
					(radius_inner - 1) * sin(terrain_angle * (3.14) / 180.0));
			glCallList(DLid_tree);
			glPopMatrix();

			terrain_angle = terrain_angle + 7;
		}

		terrain_angle = 0;
		while (terrain_angle <= 90) {
			glPushMatrix();
			glTranslatef(radius_outer * cos(terrain_angle * (3.14) / 180.0), 0,
					radius_outer * sin(terrain_angle * (3.14) / 180.0));
			glRotatef(90 - terrain_angle, 0, 1, 0);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(
					(radius_outer + 1) * cos(terrain_angle * (3.14) / 180.0), 0,
					(radius_outer + 1) * sin(terrain_angle * (3.14) / 180.0));
			glCallList(DLid_tree);
			glPopMatrix();

			terrain_angle = terrain_angle + 4;
		}

		glPopMatrix();

	}

	if (track_id % 21 == 9 || track_id % 21 == 10) {

		glPushMatrix();
		glTranslatef(400, 0, 300);
//	glRotatef(90, 0, 1, 0);
		terrain_angle = 0;
		while (terrain_angle <= 90) {
			glPushMatrix();
			glTranslatef(radius_inner * cos(terrain_angle * (3.14) / 180.0), 0,
					radius_inner * sin(terrain_angle * (3.14) / 180.0));
			glRotatef(90 - terrain_angle, 0, 1, 0);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(
					(radius_inner - 1) * cos(terrain_angle * (3.14) / 180.0), 0,
					(radius_inner - 1) * sin(terrain_angle * (3.14) / 180.0));
			glCallList(DLid_tree);
			glPopMatrix();

			terrain_angle = terrain_angle + 7;
		}

		terrain_angle = 0;
		while (terrain_angle <= 90) {
			glPushMatrix();
			glTranslatef(radius_outer * cos(terrain_angle * (3.14) / 180.0), 0,
					radius_outer * sin(terrain_angle * (3.14) / 180.0));
			glRotatef(90 - terrain_angle, 0, 1, 0);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(
					(radius_outer + 1) * cos(terrain_angle * (3.14) / 180.0), 0,
					(radius_outer + 1) * sin(terrain_angle * (3.14) / 180.0));
			glCallList(DLid_tree);
			glPopMatrix();

			terrain_angle = terrain_angle + 4;
		}

		glPopMatrix();

	}

	if (track_id % 21 == 12 || track_id % 21 == 13) {

		glPushMatrix();
		glTranslatef(150, 0, 300);
		glRotatef(270, 0, 1, 0);
		terrain_angle = 0;
		while (terrain_angle <= 90) {
			glPushMatrix();
			glTranslatef(radius_inner * cos(terrain_angle * (3.14) / 180.0), 0,
					radius_inner * sin(terrain_angle * (3.14) / 180.0));
			glRotatef(90 - terrain_angle, 0, 1, 0);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(
					(radius_inner - 1) * cos(terrain_angle * (3.14) / 180.0), 0,
					(radius_inner - 1) * sin(terrain_angle * (3.14) / 180.0));
			glCallList(DLid_tree);
			glPopMatrix();

			terrain_angle = terrain_angle + 7;
		}

		terrain_angle = 0;
		while (terrain_angle <= 90) {
			glPushMatrix();
			glTranslatef(radius_outer * cos(terrain_angle * (3.14) / 180.0), 0,
					radius_outer * sin(terrain_angle * (3.14) / 180.0));
			glRotatef(90 - terrain_angle, 0, 1, 0);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(
					(radius_outer + 1) * cos(terrain_angle * (3.14) / 180.0), 0,
					(radius_outer + 1) * sin(terrain_angle * (3.14) / 180.0));
			glCallList(DLid_tree);
			glPopMatrix();

			terrain_angle = terrain_angle + 4;
		}

		glPopMatrix();

	}

	if (track_id % 21 == 15 || track_id % 21 == 16 || track_id % 21 == 18
			|| track_id % 21 == 17) {

		glPushMatrix();
		glTranslatef(30, 0, 50);
		glRotatef(90, 0, 1, 0);
		terrain_angle = 0;
		while (terrain_angle <= 90) {
			glPushMatrix();
			glTranslatef(radius_inner * cos(terrain_angle * (3.14) / 180.0), 0,
					radius_inner * sin(terrain_angle * (3.14) / 180.0));
			glRotatef(90 - terrain_angle, 0, 1, 0);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(
					(radius_inner - 1) * cos(terrain_angle * (3.14) / 180.0), 0,
					(radius_inner - 1) * sin(terrain_angle * (3.14) / 180.0));
			glCallList(DLid_tree);
			glPopMatrix();

			terrain_angle = terrain_angle + 7;
		}

		terrain_angle = 0;
		while (terrain_angle <= 90) {
			glPushMatrix();
			glTranslatef(radius_outer * cos(terrain_angle * (3.14) / 180.0), 0,
					radius_outer * sin(terrain_angle * (3.14) / 180.0));
			glRotatef(90 - terrain_angle, 0, 1, 0);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(
					(radius_outer + 1) * cos(terrain_angle * (3.14) / 180.0), 0,
					(radius_outer + 1) * sin(terrain_angle * (3.14) / 180.0));
			glCallList(DLid_tree);
			glPopMatrix();

			terrain_angle = terrain_angle + 4;
		}

		glPopMatrix();

	}

	if (track_id % 21 == 17 || track_id % 21 == 18 || track_id % 21 == 20
			|| track_id % 21 == 19) {
		glPushMatrix();
		glTranslatef(0, 0, -70);
		glRotatef(270, 0, 1, 0);
		terrain_angle = 0;
		while (terrain_angle <= 90) {
			glPushMatrix();
			glTranslatef(radius_inner * cos(terrain_angle * (3.14) / 180.0), 0,
					radius_inner * sin(terrain_angle * (3.14) / 180.0));
			glRotatef(90 - terrain_angle, 0, 1, 0);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(
					(radius_inner - 1) * cos(terrain_angle * (3.14) / 180.0), 0,
					(radius_inner - 1) * sin(terrain_angle * (3.14) / 180.0));
			glCallList(DLid_tree);
			glPopMatrix();

			terrain_angle = terrain_angle + 7;
		}

		terrain_angle = 0;
		while (terrain_angle <= 90) {
			glPushMatrix();
			glTranslatef(radius_outer * cos(terrain_angle * (3.14) / 180.0), 0,
					radius_outer * sin(terrain_angle * (3.14) / 180.0));
			glRotatef(90 - terrain_angle, 0, 1, 0);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(
					(radius_outer + 1) * cos(terrain_angle * (3.14) / 180.0), 0,
					(radius_outer + 1) * sin(terrain_angle * (3.14) / 180.0));
			glCallList(DLid_tree);
			glPopMatrix();

			terrain_angle = terrain_angle + 4;
		}

		glPopMatrix();

	}

	if (track_id % 21 == 19 || track_id % 21 == 20 || track_id % 21 == 0) {
		glPushMatrix();
		glTranslatef(0, 0, -90);
		glRotatef(180, 0, 1, 0);
		terrain_angle = 0;
		while (terrain_angle <= 90) {
			glPushMatrix();
			glTranslatef(radius_inner * cos(terrain_angle * (3.14) / 180.0), 0,
					radius_inner * sin(terrain_angle * (3.14) / 180.0));
			glRotatef(90 - terrain_angle, 0, 1, 0);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(
					(radius_inner - 1) * cos(terrain_angle * (3.14) / 180.0), 0,
					(radius_inner - 1) * sin(terrain_angle * (3.14) / 180.0));
			glCallList(DLid_tree);
			glPopMatrix();

			terrain_angle = terrain_angle + 7;
		}

		terrain_angle = 0;
		while (terrain_angle <= 90) {
			glPushMatrix();
			glTranslatef(radius_outer * cos(terrain_angle * (3.14) / 180.0), 0,
					radius_outer * sin(terrain_angle * (3.14) / 180.0));
			glRotatef(90 - terrain_angle, 0, 1, 0);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(
					(radius_outer + 1) * cos(terrain_angle * (3.14) / 180.0), 0,
					(radius_outer + 1) * sin(terrain_angle * (3.14) / 180.0));
			glCallList(DLid_tree);
			glPopMatrix();

			terrain_angle = terrain_angle + 4;
		}

		glPopMatrix();

	}
	// Bridges and Other Objects
	glPushMatrix();
	glTranslatef(90, 0, 175);
	glRotatef(90, 0, 1, 0);
	glPushMatrix();
	glColor3f(150.0 / 255.0, 150.0 / 255.0, 150.0 / 255.0);
	glScalef(6, 15, 20);
	glTranslatef(0, -3.9, 0);
	glCallList(DLid_tree_1);
	glColor3f(1.0, 1.0, 1.0);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(250, 0, 360);
	glRotatef(180, 0, 1, 0);
	glPushMatrix();
	glColor3f(150.0 / 255.0, 150.0 / 255.0, 150.0 / 255.0);
	glScalef(6, 15, 20);
	glTranslatef(0, -3.9, 0);
	glCallList(DLid_tree_1);
	glColor3f(1.0, 1.0, 1.0);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(200, 0, -150);
	glRotatef(180, 0, 1, 0);
	glPushMatrix();
	glColor3f(150.0 / 255.0, 150.0 / 255.0, 150.0 / 255.0);
	glScalef(6, 15, 20);
	glTranslatef(0, -3.9, 0);
	glCallList(DLid_tree_1);
	glColor3f(1.0, 1.0, 1.0);
	glPopMatrix();
	glPopMatrix();
}

void track_1_fill_vec() {

	vector3D start1_track(0, 0, -170);
	vector3D end1_track(100, 0, -170);
	vector3D start2_track(0, 0, -130);
	vector3D end2_track(100, 0, -130);
	vector3D center_track(0, 0, 0);
	float radius1_track = 0.0;
	float radius2_track = 0.0;
	float angle_track = 0.0;
	string id_track = "S";
	track part_1;
	part_1.start1 = start1_track;
	part_1.end1 = end1_track;
	part_1.start2 = start2_track;
	part_1.end2 = end2_track;
	part_1.id = id_track;
	track_states.push_back(part_1);

	start1_track.x = 100;
	start1_track.y = 0;
	start1_track.z = -170;
	end1_track.x = 200;
	end1_track.y = 0;
	end1_track.z = -170;
	start2_track.x = 100;
	start2_track.y = 0;
	start2_track.z = -130;
	end2_track.x = 200;
	end2_track.y = 0;
	end2_track.z = -130;
	id_track = "S";
	track part_1_1;
	part_1_1.start1 = start1_track;
	part_1_1.end1 = end1_track;
	part_1_1.start2 = start2_track;
	part_1_1.end2 = end2_track;
	part_1_1.id = id_track;
	track_states.push_back(part_1_1);

	start1_track.x = 200;
	start1_track.y = 0;
	start1_track.z = -170;
	end1_track.x = 300;
	end1_track.y = 0;
	end1_track.z = -170;
	start2_track.x = 200;
	start2_track.y = 0;
	start2_track.z = -130;
	end2_track.x = 300;
	end2_track.y = 0;
	end2_track.z = -130;
	id_track = "S";
	track part_1_2;
	part_1_2.start1 = start1_track;
	part_1_2.end1 = end1_track;
	part_1_2.start2 = start2_track;
	part_1_2.end2 = end2_track;
	part_1_2.id = id_track;
	track_states.push_back(part_1_2);

	start1_track.x = 300;
	start1_track.y = 0;
	start1_track.z = -170;
	end1_track.x = 380;
	end1_track.y = 0;
	end1_track.z = -90;
	start2_track.x = 300;
	start2_track.y = 0;
	start2_track.z = -130;
	end2_track.x = 340;
	end2_track.y = 0;
	end2_track.z = -90;
	center_track.x = 300;
	center_track.y = 0;
	center_track.z = -90;
	radius1_track = 80.0;
	radius2_track = 40.0;
	angle_track = 1.57;
	id_track = "C";
	track part_2;
	part_2.start1 = start1_track;
	part_2.end1 = end1_track;
	part_2.start2 = start2_track;
	part_2.end2 = end2_track;
	part_2.radius1 = radius1_track;
	part_2.radius2 = radius2_track;
	part_2.angle = angle_track;
	part_2.id = id_track;
	part_2.center = center_track;
	track_states.push_back(part_2);

	start1_track.x = 380;
	start1_track.y = 0;
	start1_track.z = -90;
	end1_track.x = 300;
	end1_track.y = 0;
	end1_track.z = -10;
	start2_track.x = 340;
	start2_track.y = 0;
	start2_track.z = -90;
	end2_track.x = 300;
	end2_track.y = 0;
	end2_track.z = -50;
	center_track.x = 300;
	center_track.y = 0;
	center_track.z = -90;
	radius1_track = 80.0;
	radius2_track = 40.0;
	angle_track = 1.57;
	id_track = "C";
	track part_2_2;
	part_2_2.start1 = start1_track;
	part_2_2.end1 = end1_track;
	part_2_2.start2 = start2_track;
	part_2_2.end2 = end2_track;
	part_2_2.radius1 = radius1_track;
	part_2_2.radius2 = radius2_track;
	part_2_2.angle = angle_track;
	part_2_2.id = id_track;
	part_2_2.center = center_track;
	track_states.push_back(part_2_2);

	start1_track.x = 300;
	start1_track.y = 0;
	start1_track.z = -10;
	end1_track.x = 260;
	end1_track.y = 0;
	end1_track.z = 30;
	start2_track.x = 300;
	start2_track.y = 0;
	start2_track.z = -50;
	end2_track.x = 220;
	end2_track.y = 0;
	end2_track.z = 30;
	center_track.x = 300;
	center_track.y = 0;
	center_track.z = 30;
	radius1_track = 80.0;
	radius2_track = 40.0;
	angle_track = -1.57;
	id_track = "C";
	track part_3;
	part_3.start1 = start1_track;
	part_3.end1 = end1_track;
	part_3.start2 = start2_track;
	part_3.end2 = end2_track;
	part_3.radius1 = radius1_track;
	part_3.radius2 = radius2_track;
	part_3.angle = angle_track;
	part_3.id = id_track;
	part_3.center = center_track;
	track_states.push_back(part_3);

	start1_track.x = 260;
	start1_track.y = 0;
	start1_track.z = 30;
	end1_track.x = 260;
	end1_track.y = 0;
	end1_track.z = 180;
	start2_track.x = 220;
	start2_track.y = 0;
	start2_track.z = 30;
	end2_track.x = 220;
	end2_track.y = 0;
	end2_track.z = 180;
	id_track = "S";
	track part_4;
	part_4.start1 = start1_track;
	part_4.end1 = end1_track;
	part_4.start2 = start2_track;
	part_4.end2 = end2_track;
	part_4.id = id_track;
	track_states.push_back(part_4);

	start1_track.x = 260;
	start1_track.y = 0;
	start1_track.z = 180;
	end1_track.x = 300;
	end1_track.y = 0;
	end1_track.z = 220;
	start2_track.x = 220;
	start2_track.y = 0;
	start2_track.z = 180;
	end2_track.x = 300;
	end2_track.y = 0;
	end2_track.z = 260;
	center_track.x = 300;
	center_track.y = 0;
	center_track.z = 180;
	radius1_track = 80.0;
	radius2_track = 40.0;
	angle_track = -1.57;
	id_track = "C";
	track part_5;
	part_5.start1 = start1_track;
	part_5.end1 = end1_track;
	part_5.start2 = start2_track;
	part_5.end2 = end2_track;
	part_5.radius1 = radius1_track;
	part_5.radius2 = radius2_track;
	part_5.angle = angle_track;
	part_5.id = id_track;
	part_5.center = center_track;
	track_states.push_back(part_5);

	start1_track.x = 300;
	start1_track.y = 0;
	start1_track.z = 220;
	end1_track.x = 400;
	end1_track.y = 0;
	end1_track.z = 220;
	start2_track.x = 300;
	start2_track.y = 0;
	start2_track.z = 260;
	end2_track.x = 400;
	end2_track.y = 0;
	end2_track.z = 260;
	id_track = "S";
	track part_6;
	part_6.start1 = start1_track;
	part_6.end1 = end1_track;
	part_6.start2 = start2_track;
	part_6.end2 = end2_track;
	part_6.id = id_track;
	track_states.push_back(part_6);

	start1_track.x = 400;
	start1_track.y = 0;
	start1_track.z = 220;
	end1_track.x = 480;
	end1_track.y = 0;
	end1_track.z = 300;
	start2_track.x = 400;
	start2_track.y = 0;
	start2_track.z = 260;
	end2_track.x = 440;
	end2_track.y = 0;
	end2_track.z = 300;
	center_track.x = 400;
	center_track.y = 0;
	center_track.z = 300;
	radius1_track = 80.0;
	radius2_track = 40.0;
	angle_track = 1.57;
	id_track = "C";
	track part_7;
	part_7.start1 = start1_track;
	part_7.end1 = end1_track;
	part_7.start2 = start2_track;
	part_7.end2 = end2_track;
	part_7.radius1 = radius1_track;
	part_7.radius2 = radius2_track;
	part_7.angle = angle_track;
	part_7.id = id_track;
	part_7.center = center_track;
	track_states.push_back(part_7);

	start1_track.x = 480;
	start1_track.y = 0;
	start1_track.z = 300;
	end1_track.x = 400;
	end1_track.y = 0;
	end1_track.z = 380;
	start2_track.x = 440;
	start2_track.y = 0;
	start2_track.z = 300;
	end2_track.x = 400;
	end2_track.y = 0;
	end2_track.z = 340;
	center_track.x = 400;
	center_track.y = 0;
	center_track.z = 300;
	radius1_track = 80.0;
	radius2_track = 40.0;
	angle_track = 1.57;
	id_track = "C";
	track part_7_1;
	part_7_1.start1 = start1_track;
	part_7_1.end1 = end1_track;
	part_7_1.start2 = start2_track;
	part_7_1.end2 = end2_track;
	part_7_1.radius1 = radius1_track;
	part_7_1.radius2 = radius2_track;
	part_7_1.angle = angle_track;
	part_7_1.id = id_track;
	part_7_1.center = center_track;
	track_states.push_back(part_7_1);

	start1_track.x = 400;
	start1_track.y = 0;
	start1_track.z = 380;
	end1_track.x = 275;
	end1_track.y = 0;
	end1_track.z = 380;
	start2_track.x = 400;
	start2_track.y = 0;
	start2_track.z = 340;
	end2_track.x = 275;
	end2_track.y = 0;
	end2_track.z = 340;
	id_track = "S";
	track part_8;
	part_8.start1 = start1_track;
	part_8.end1 = end1_track;
	part_8.start2 = start2_track;
	part_8.end2 = end2_track;
	part_8.id = id_track;
	track_states.push_back(part_8);

	start1_track.x = 275;
	start1_track.y = 0;
	start1_track.z = 380;
	end1_track.x = 150;
	end1_track.y = 0;
	end1_track.z = 380;
	start2_track.x = 275;
	start2_track.y = 0;
	start2_track.z = 340;
	end2_track.x = 150;
	end2_track.y = 0;
	end2_track.z = 340;
	id_track = "S";
	track part_8_1;
	part_8_1.start1 = start1_track;
	part_8_1.end1 = end1_track;
	part_8_1.start2 = start2_track;
	part_8_1.end2 = end2_track;
	part_8_1.id = id_track;
	track_states.push_back(part_8_1);

	start1_track.x = 150;
	start1_track.y = 0;
	start1_track.z = 380;
	end1_track.x = 70;
	end1_track.y = 0;
	end1_track.z = 300;
	start2_track.x = 150;
	start2_track.y = 0;
	start2_track.z = 340;
	end2_track.x = 110;
	end2_track.y = 0;
	end2_track.z = 300;
	center_track.x = 150;
	center_track.y = 0;
	center_track.z = 300;
	radius1_track = 80.0;
	radius2_track = 40.0;
	angle_track = 1.57;
	id_track = "C";
	track part_9;
	part_9.start1 = start1_track;
	part_9.end1 = end1_track;
	part_9.start2 = start2_track;
	part_9.end2 = end2_track;
	part_9.radius1 = radius1_track;
	part_9.radius2 = radius2_track;
	part_9.angle = angle_track;
	part_9.id = id_track;
	part_9.center = center_track;
	track_states.push_back(part_9);

	start1_track.x = 70;
	start1_track.y = 0;
	start1_track.z = 300;
	end1_track.x = 70;
	end1_track.y = 0;
	end1_track.z = 175;
	start2_track.x = 110;
	start2_track.y = 0;
	start2_track.z = 300;
	end2_track.x = 110;
	end2_track.y = 0;
	end2_track.z = 175;
	id_track = "S";
	track part_13;
	part_13.start1 = start1_track;
	part_13.end1 = end1_track;
	part_13.start2 = start2_track;
	part_13.end2 = end2_track;
	part_13.id = id_track;
	track_states.push_back(part_13);

	start1_track.x = 70;
	start1_track.y = 0;
	start1_track.z = 175;
	end1_track.x = 70;
	end1_track.y = 0;
	end1_track.z = 50;
	start2_track.x = 110;
	start2_track.y = 0;
	start2_track.z = 175;
	end2_track.x = 110;
	end2_track.y = 0;
	end2_track.z = 50;
	id_track = "S";
	track part_13_1;
	part_13_1.start1 = start1_track;
	part_13_1.end1 = end1_track;
	part_13_1.start2 = start2_track;
	part_13_1.end2 = end2_track;
	part_13_1.id = id_track;
	track_states.push_back(part_13_1);

	start1_track.x = 70;
	start1_track.y = 0;
	start1_track.z = 50;
	end1_track.x = 30;
	end1_track.y = 0;
	end1_track.z = 10;
	start2_track.x = 110;
	start2_track.y = 0;
	start2_track.z = 50;
	end2_track.x = 30;
	end2_track.y = 0;
	end2_track.z = -30;
	center_track.x = 30;
	center_track.y = 0;
	center_track.z = 50;
	radius1_track = 80.0;
	radius2_track = 40.0;
	angle_track = -1.57;
	id_track = "C";
	track part_10;
	part_10.start1 = start1_track;
	part_10.end1 = end1_track;
	part_10.start2 = start2_track;
	part_10.end2 = end2_track;
	part_10.radius1 = radius1_track;
	part_10.radius2 = radius2_track;
	part_10.angle = angle_track;
	part_10.id = id_track;
	part_10.center = center_track;
	track_states.push_back(part_10);

	start1_track.x = 30;
	start1_track.y = 0;
	start1_track.z = 10;
	end1_track.x = 0;
	end1_track.y = 0;
	end1_track.z = 10;
	start2_track.x = 30;
	start2_track.y = 0;
	start2_track.z = -30;
	end2_track.x = 0;
	end2_track.y = 0;
	end2_track.z = -30;
	id_track = "S";
	track part_11;
	part_11.start1 = start1_track;
	part_11.end1 = end1_track;
	part_11.start2 = start2_track;
	part_11.end2 = end2_track;
	part_11.id = id_track;
	track_states.push_back(part_11);

	start1_track.x = 0;
	start1_track.y = 0;
	start1_track.z = 10;
	end1_track.x = -80;
	end1_track.y = 0;
	end1_track.z = -70;
	start2_track.x = 0;
	start2_track.y = 0;
	start2_track.z = -30;
	end2_track.x = -40;
	end2_track.y = 0;
	end2_track.z = -70;
	center_track.x = 0;
	center_track.y = 0;
	center_track.z = -70;
	radius1_track = 80.0;
	radius2_track = 40.0;
	angle_track = 1.57;
	id_track = "C";
	track part_14;
	part_14.start1 = start1_track;
	part_14.end1 = end1_track;
	part_14.start2 = start2_track;
	part_14.end2 = end2_track;
	part_14.radius1 = radius1_track;
	part_14.radius2 = radius2_track;
	part_14.angle = angle_track;
	part_14.id = id_track;
	part_14.center = center_track;
	track_states.push_back(part_14);

	start1_track.x = -80;
	start1_track.y = 0;
	start1_track.z = -70;
	end1_track.x = -80;
	end1_track.y = 0;
	end1_track.z = -90;
	start2_track.x = -40;
	start2_track.y = 0;
	start2_track.z = -70;
	end2_track.x = -40;
	end2_track.y = 0;
	end2_track.z = -90;
	id_track = "S";
	track part_15;
	part_15.start1 = start1_track;
	part_15.end1 = end1_track;
	part_15.start2 = start2_track;
	part_15.end2 = end2_track;
	part_15.id = id_track;
	track_states.push_back(part_15);

	start1_track.x = -80;
	start1_track.y = 0;
	start1_track.z = -90;
	end1_track.x = 0;
	end1_track.y = 0;
	end1_track.z = -170;
	start2_track.x = -40;
	start2_track.y = 0;
	start2_track.z = -90;
	end2_track.x = 0;
	end2_track.y = 0;
	end2_track.z = -130;
	center_track.x = 0;
	center_track.y = 0;
	center_track.z = -90;
	radius1_track = 80.0;
	radius2_track = 40.0;
	angle_track = 1.57;
	id_track = "C";
	track part_12;
	part_12.start1 = start1_track;
	part_12.end1 = end1_track;
	part_12.start2 = start2_track;
	part_12.end2 = end2_track;
	part_12.radius1 = radius1_track;
	part_12.radius2 = radius2_track;
	part_12.angle = angle_track;
	part_12.id = id_track;
	part_12.center = center_track;
	track_states.push_back(part_12);

}

void track_2() {

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTranslatef(0, -0.1, 0);

	for (float image_x = -150; image_x < 500; image_x += 20) {
		for (float image_y = -250; image_y < 800; image_y += 20) {
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(image_x, 0.0, image_y);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(image_x, 0.0, image_y + 20);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(image_x + 20, 0.0, image_y + 20);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(image_x + 20, 0.0, image_y);
			glEnd();
		}

	}
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -150);
	glEnable(GL_TEXTURE_2D);
	for (float image_x = 0; image_x < 300; image_x += 10) {
		if (image_x == 50) {

			glBindTexture(GL_TEXTURE_2D, _textureId_flag);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(image_x, 0.0, -20.0);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(image_x, 0.0, 20);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(image_x + 10, 0.0, 20);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(image_x + 10, 0.0, -20);
			glEnd();

		} else {

			glBindTexture(GL_TEXTURE_2D, _textureId_road);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(image_x, 0.0, -20.0);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(image_x, 0.0, 20);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(image_x + 10, 0.0, 20);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(image_x + 10, 0.0, -20);
			glEnd();
		}
	}
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(300, 0, -90);
	glRotatef(90, 0, 1, 0);
	float terrain_angle = 0;
	float radius_inner = 40.0f;
	float radius_outer = 80.0f;
	vector3D normal_to_plane(0.0, 1.0, 0.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId_road);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	while (terrain_angle <= 90) {

		vector3D normal_inner(
				radius_inner * cos(terrain_angle * (3.14) / 180.0), 0,
				radius_inner * sin(terrain_angle * (3.14) / 180.0));
		vector3D normal_outer(
				radius_outer * cos(terrain_angle * (3.14) / 180.0), 0,
				radius_outer * sin(terrain_angle * (3.14) / 180.0));
		vector3D normal_normaize = normalise(normal_inner);

		vector3D tangent = crossProduct(normal_to_plane, normal_normaize);

		vector3D first = add(normal_inner, constProduct(tangent, 1.0));
		vector3D second = subtract(normal_inner, constProduct(tangent, 1.0));
		vector3D fourth = add(normal_outer, constProduct(tangent, 1.0));
		vector3D third = subtract(normal_outer, constProduct(tangent, 1.0));

		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(first.x, 0.0, first.z);
		glVertex3f(second.x, 0.0, second.z);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(fourth.x, 0.0, fourth.z);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(third.x, 0.0, third.z);
		glTexCoord2f(0.0f, 1.0f);

		glEnd();
		terrain_angle = terrain_angle + 1;

	}
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(360, 0, -90);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId_road);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	for (float image_x = 0; image_x < 700; image_x += 10) {
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-20.0, 0.0, image_x);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(20.0, 0.0, image_x);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(20.0, 0.0, image_x + 10);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-20.0, 0.0, image_x + 10);
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(300, 0, 610);
	terrain_angle = 0;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId_road);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	while (terrain_angle <= 180) {

		vector3D normal_inner(
				radius_inner * cos(terrain_angle * (3.14) / 180.0), 0,
				radius_inner * sin(terrain_angle * (3.14) / 180.0));
		vector3D normal_outer(
				radius_outer * cos(terrain_angle * (3.14) / 180.0), 0,
				radius_outer * sin(terrain_angle * (3.14) / 180.0));
		vector3D normal_normaize = normalise(normal_inner);

		vector3D tangent = crossProduct(normal_to_plane, normal_normaize);

		vector3D first = add(normal_inner, constProduct(tangent, 1.0));
		vector3D second = subtract(normal_inner, constProduct(tangent, 1.0));
		vector3D fourth = add(normal_outer, constProduct(tangent, 1.0));
		vector3D third = subtract(normal_outer, constProduct(tangent, 1.0));

		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(first.x, 0.0, first.z);
		glVertex3f(second.x, 0.0, second.z);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(fourth.x, 0.0, fourth.z);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(third.x, 0.0, third.z);
		glTexCoord2f(0.0f, 1.0f);

		glEnd();
		terrain_angle = terrain_angle + 1;

	}
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(240, 0, 610);
	glRotatef(180, 0, 1, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId_road);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	for (float image_x = 0; image_x < 230; image_x += 10) {
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-20.0, 0.0, image_x);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(20.0, 0.0, image_x);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(20.0, 0.0, image_x + 10);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-20.0, 0.0, image_x + 10);
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(180, 0, 380);
	glRotatef(90, 0, 1, 0);
	terrain_angle = 0;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId_road);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	while (terrain_angle <= 90) {
		vector3D normal_inner(
				radius_inner * cos(terrain_angle * (3.14) / 180.0), 0,
				radius_inner * sin(terrain_angle * (3.14) / 180.0));
		vector3D normal_outer(
				radius_outer * cos(terrain_angle * (3.14) / 180.0), 0,
				radius_outer * sin(terrain_angle * (3.14) / 180.0));
		vector3D normal_normaize = normalise(normal_inner);
		vector3D tangent = crossProduct(normal_to_plane, normal_normaize);
		vector3D first = add(normal_inner, constProduct(tangent, 1.0));
		vector3D second = subtract(normal_inner, constProduct(tangent, 1.0));
		vector3D fourth = add(normal_outer, constProduct(tangent, 1.0));
		vector3D third = subtract(normal_outer, constProduct(tangent, 1.0));

		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(first.x, 0.0, first.z);
		glVertex3f(second.x, 0.0, second.z);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(fourth.x, 0.0, fourth.z);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(third.x, 0.0, third.z);
		glTexCoord2f(0.0f, 1.0f);

		glEnd();
		terrain_angle = terrain_angle + 1;

	}
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(180, 0, 320);
	glRotatef(180, 0, 1, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId_road);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	for (float image_x = 0; image_x < 180; image_x += 10) {
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(image_x, 0.0, -20.0);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(image_x, 0.0, 20);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(image_x + 10, 0.0, 20);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(image_x + 10, 0.0, -20);
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 260);
	glRotatef(270, 0, 1, 0);
	terrain_angle = 0;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId_road);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	while (terrain_angle <= 90) {
		vector3D normal_inner(
				radius_inner * cos(terrain_angle * (3.14) / 180.0), 0,
				radius_inner * sin(terrain_angle * (3.14) / 180.0));
		vector3D normal_outer(
				radius_outer * cos(terrain_angle * (3.14) / 180.0), 0,
				radius_outer * sin(terrain_angle * (3.14) / 180.0));
		vector3D normal_normaize = normalise(normal_inner);
		vector3D tangent = crossProduct(normal_to_plane, normal_normaize);
		vector3D first = add(normal_inner, constProduct(tangent, 1.0));
		vector3D second = subtract(normal_inner, constProduct(tangent, 1.0));
		vector3D fourth = add(normal_outer, constProduct(tangent, 1.0));
		vector3D third = subtract(normal_outer, constProduct(tangent, 1.0));

		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(first.x, 0.0, first.z);
		glVertex3f(second.x, 0.0, second.z);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(fourth.x, 0.0, fourth.z);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(third.x, 0.0, third.z);
		glTexCoord2f(0.0f, 1.0f);

		glEnd();
		terrain_angle = terrain_angle + 1;

	}
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-60, 0, 260);
	glRotatef(180, 0, 1, 0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId_road);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	for (float image_x = 0; image_x < 350; image_x += 10) {
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-20.0, 0.0, image_x);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(20.0, 0.0, image_x);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(20.0, 0.0, image_x + 10);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-20.0, 0.0, image_x + 10);
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, -90);
	glRotatef(180, 0, 1, 0);
	terrain_angle = 0;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId_road);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	while (terrain_angle <= 90) {
		vector3D normal_inner(
				radius_inner * cos(terrain_angle * (3.14) / 180.0), 0,
				radius_inner * sin(terrain_angle * (3.14) / 180.0));
		vector3D normal_outer(
				radius_outer * cos(terrain_angle * (3.14) / 180.0), 0,
				radius_outer * sin(terrain_angle * (3.14) / 180.0));
		vector3D normal_normaize = normalise(normal_inner);
		vector3D tangent = crossProduct(normal_to_plane, normal_normaize);
		vector3D first = add(normal_inner, constProduct(tangent, 1.0));
		vector3D second = subtract(normal_inner, constProduct(tangent, 1.0));
		vector3D fourth = add(normal_outer, constProduct(tangent, 1.0));
		vector3D third = subtract(normal_outer, constProduct(tangent, 1.0));

		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(first.x, 0.0, first.z);
		glVertex3f(second.x, 0.0, second.z);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(fourth.x, 0.0, fourth.z);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(third.x, 0.0, third.z);
		glTexCoord2f(0.0f, 1.0f);

		glEnd();
		terrain_angle = terrain_angle + 1;

	}
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

}

void track_2_texture() {
	if (track_id % 21 == 20 || track_id % 21 == 0) {
		glPushMatrix();
		glTranslatef(0, 0, -150);
		for (int image_x = 0; image_x <= 100; image_x += 5) {
			glPushMatrix();
			glTranslatef(image_x, 0, -20);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, 20);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, 21);
			glCallList(DLid_tree);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, -21);
			glCallList(DLid_tree);
			glPopMatrix();
		}
		glPopMatrix();
	}

	if (track_id % 21 == 0 || track_id % 21 == 1) {
		glPushMatrix();
		glTranslatef(100, 0, -150);
		for (int image_x = 0; image_x <= 100; image_x += 5) {
			glPushMatrix();
			glTranslatef(image_x, 0, -20);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, 20);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, 21);
			glCallList(DLid_tree);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, -21);
			glCallList(DLid_tree);
			glPopMatrix();
		}
		glPopMatrix();
	}

	if (track_id % 21 == 1 || track_id % 21 == 2) {
		glPushMatrix();
		glTranslatef(200, 0, -150);
		for (int image_x = 0; image_x <= 100; image_x += 5) {
			glPushMatrix();
			glTranslatef(image_x, 0, -20);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, 20);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, 21);
			glCallList(DLid_tree);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, -21);
			glCallList(DLid_tree);
			glPopMatrix();
		}
		glPopMatrix();
	}

	float terrain_angle = 0;
	float radius_inner = 40.0f;
	float radius_outer = 80.0f;
	vector3D normal_to_plane(0.0, 1.0, 0.0);

	if (track_id % 21 == 2 || track_id % 21 == 3) {
		glPushMatrix();
		glTranslatef(300, 0, -90);
		glRotatef(90, 0, 1, 0);
		terrain_angle = 0;
		while (terrain_angle <= 90) {
			glPushMatrix();
			glTranslatef(radius_inner * cos(terrain_angle * (3.14) / 180.0), 0,
					radius_inner * sin(terrain_angle * (3.14) / 180.0));
			glRotatef(90 - terrain_angle, 0, 1, 0);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(
					(radius_inner - 1) * cos(terrain_angle * (3.14) / 180.0), 0,
					(radius_inner - 1) * sin(terrain_angle * (3.14) / 180.0));
			glCallList(DLid_tree);
			glPopMatrix();

			terrain_angle = terrain_angle + 7;
		}

		terrain_angle = 0;
		while (terrain_angle <= 90) {
			glPushMatrix();
			glTranslatef(radius_outer * cos(terrain_angle * (3.14) / 180.0), 0,
					radius_outer * sin(terrain_angle * (3.14) / 180.0));
			glRotatef(90 - terrain_angle, 0, 1, 0);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(
					(radius_outer + 1) * cos(terrain_angle * (3.14) / 180.0), 0,
					(radius_outer + 1) * sin(terrain_angle * (3.14) / 180.0));
			glCallList(DLid_tree);
			glPopMatrix();

			terrain_angle = terrain_angle + 4;
		}

		glPopMatrix();
	}

	if (track_id % 21 == 3 || track_id % 21 == 4) {
		glPushMatrix();
		glTranslatef(360, 0, -90);
		glRotatef(270, 0, 1, 0);
		for (int image_x = 0; image_x <= 100; image_x += 5) {
			glPushMatrix();
			glTranslatef(image_x, 0, -20);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, 20);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, 21);
			glCallList(DLid_tree);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, -21);
			glCallList(DLid_tree);
			glPopMatrix();
		}
		glPopMatrix();
	}
	if (track_id % 21 == 4 || track_id % 21 == 5) {
		glPushMatrix();
		glTranslatef(360, 0, 10);
		glRotatef(270, 0, 1, 0);
		for (int image_x = 0; image_x <= 100; image_x += 5) {
			glPushMatrix();
			glTranslatef(image_x, 0, -20);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, 20);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, 21);
			glCallList(DLid_tree);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, -21);
			glCallList(DLid_tree);
			glPopMatrix();
		}
		glPopMatrix();
	}
	if (track_id % 21 == 5 || track_id % 21 == 6) {
		glPushMatrix();
		glTranslatef(360, 0, 110);
		glRotatef(270, 0, 1, 0);
		for (int image_x = 0; image_x <= 100; image_x += 5) {
			glPushMatrix();
			glTranslatef(image_x, 0, -20);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, 20);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, 21);
			glCallList(DLid_tree);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, -21);
			glCallList(DLid_tree);
			glPopMatrix();
		}
		glPopMatrix();
	}
	if (track_id % 21 == 6 || track_id % 21 == 7) {
		glPushMatrix();
		glTranslatef(360, 0, 210);
		glRotatef(270, 0, 1, 0);
		for (int image_x = 0; image_x <= 100; image_x += 5) {
			glPushMatrix();
			glTranslatef(image_x, 0, -20);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, 20);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, 21);
			glCallList(DLid_tree);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, -21);
			glCallList(DLid_tree);
			glPopMatrix();
		}
		glPopMatrix();
	}
	if (track_id % 21 == 7 || track_id % 21 == 8) {
		glPushMatrix();
		glTranslatef(360, 0, 310);
		glRotatef(270, 0, 1, 0);
		for (int image_x = 0; image_x <= 100; image_x += 5) {
			glPushMatrix();
			glTranslatef(image_x, 0, -20);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, 20);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, 21);
			glCallList(DLid_tree);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, -21);
			glCallList(DLid_tree);
			glPopMatrix();
		}
		glPopMatrix();
	}
	if (track_id % 21 == 8 || track_id % 21 == 9) {
		glPushMatrix();
		glTranslatef(360, 0, 410);
		glRotatef(270, 0, 1, 0);
		for (int image_x = 0; image_x <= 100; image_x += 5) {
			glPushMatrix();
			glTranslatef(image_x, 0, -20);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, 20);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, 21);
			glCallList(DLid_tree);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, -21);
			glCallList(DLid_tree);
			glPopMatrix();
		}
		glPopMatrix();
	}

	if (track_id % 21 == 9 || track_id % 21 == 10) {
		glPushMatrix();
		glTranslatef(360, 0, 510);
		glRotatef(270, 0, 1, 0);
		for (int image_x = 0; image_x <= 100; image_x += 5) {
			glPushMatrix();
			glTranslatef(image_x, 0, -20);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, 20);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, 21);
			glCallList(DLid_tree);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, -21);
			glCallList(DLid_tree);
			glPopMatrix();
		}
		glPopMatrix();
	}

	if (track_id % 21 == 10 || track_id % 21 == 11) {
		glPushMatrix();
		glTranslatef(300, 0, 610);
//			glRotatef(90, 0, 1, 0);
		terrain_angle = 0;
		while (terrain_angle <= 90) {
			glPushMatrix();
			glTranslatef(radius_inner * cos(terrain_angle * (3.14) / 180.0), 0,
					radius_inner * sin(terrain_angle * (3.14) / 180.0));
			glRotatef(90 - terrain_angle, 0, 1, 0);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(
					(radius_inner - 1) * cos(terrain_angle * (3.14) / 180.0), 0,
					(radius_inner - 1) * sin(terrain_angle * (3.14) / 180.0));
			glCallList(DLid_tree);
			glPopMatrix();

			terrain_angle = terrain_angle + 7;
		}

		terrain_angle = 0;
		while (terrain_angle <= 90) {
			glPushMatrix();
			glTranslatef(radius_outer * cos(terrain_angle * (3.14) / 180.0), 0,
					radius_outer * sin(terrain_angle * (3.14) / 180.0));
			glRotatef(90 - terrain_angle, 0, 1, 0);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(
					(radius_outer + 1) * cos(terrain_angle * (3.14) / 180.0), 0,
					(radius_outer + 1) * sin(terrain_angle * (3.14) / 180.0));
			glCallList(DLid_tree);
			glPopMatrix();

			terrain_angle = terrain_angle + 4;
		}

		glPopMatrix();
	}

	if (track_id % 21 == 11 || track_id % 21 == 12) {
		glPushMatrix();
		glTranslatef(300, 0, 610);
		glRotatef(270, 0, 1, 0);
		terrain_angle = 0;
		while (terrain_angle <= 90) {
			glPushMatrix();
			glTranslatef(radius_inner * cos(terrain_angle * (3.14) / 180.0), 0,
					radius_inner * sin(terrain_angle * (3.14) / 180.0));
			glRotatef(90 - terrain_angle, 0, 1, 0);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(
					(radius_inner - 1) * cos(terrain_angle * (3.14) / 180.0), 0,
					(radius_inner - 1) * sin(terrain_angle * (3.14) / 180.0));
			glCallList(DLid_tree);
			glPopMatrix();

			terrain_angle = terrain_angle + 7;
		}

		terrain_angle = 0;
		while (terrain_angle <= 90) {
			glPushMatrix();
			glTranslatef(radius_outer * cos(terrain_angle * (3.14) / 180.0), 0,
					radius_outer * sin(terrain_angle * (3.14) / 180.0));
			glRotatef(90 - terrain_angle, 0, 1, 0);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(
					(radius_outer + 1) * cos(terrain_angle * (3.14) / 180.0), 0,
					(radius_outer + 1) * sin(terrain_angle * (3.14) / 180.0));
			glCallList(DLid_tree);
			glPopMatrix();

			terrain_angle = terrain_angle + 4;
		}

		glPopMatrix();
	}

	if (track_id % 21 == 12 || track_id % 21 == 13) {
		glPushMatrix();
		glTranslatef(240, 0, 610);
		glRotatef(90, 0, 1, 0);
		for (int image_x = 0; image_x <= 125; image_x += 5) {
			glPushMatrix();
			glTranslatef(image_x, 0, -20);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, 20);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, 21);
			glCallList(DLid_tree);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, -21);
			glCallList(DLid_tree);
			glPopMatrix();
		}
		glPopMatrix();
	}

	if (track_id % 21 == 13 || track_id % 21 == 14) {
		glPushMatrix();
		glTranslatef(240, 0, 485);
		glRotatef(90, 0, 1, 0);
		for (int image_x = 0; image_x <= 105; image_x += 5) {
			glPushMatrix();
			glTranslatef(image_x, 0, -20);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, 20);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, 21);
			glCallList(DLid_tree);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, -21);
			glCallList(DLid_tree);
			glPopMatrix();
		}
		glPopMatrix();
	}

	if (track_id % 21 == 14 || track_id % 21 == 15) {
		glPushMatrix();
		glTranslatef(180, 0, 380);
		glRotatef(90, 0, 1, 0);
		terrain_angle = 0;
		while (terrain_angle <= 90) {
			glPushMatrix();
			glTranslatef(radius_inner * cos(terrain_angle * (3.14) / 180.0), 0,
					radius_inner * sin(terrain_angle * (3.14) / 180.0));
			glRotatef(90 - terrain_angle, 0, 1, 0);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(
					(radius_inner - 1) * cos(terrain_angle * (3.14) / 180.0), 0,
					(radius_inner - 1) * sin(terrain_angle * (3.14) / 180.0));
			glCallList(DLid_tree);
			glPopMatrix();

			terrain_angle = terrain_angle + 7;
		}

		terrain_angle = 0;
		while (terrain_angle <= 90) {
			glPushMatrix();
			glTranslatef(radius_outer * cos(terrain_angle * (3.14) / 180.0), 0,
					radius_outer * sin(terrain_angle * (3.14) / 180.0));
			glRotatef(90 - terrain_angle, 0, 1, 0);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(
					(radius_outer + 1) * cos(terrain_angle * (3.14) / 180.0), 0,
					(radius_outer + 1) * sin(terrain_angle * (3.14) / 180.0));
			glCallList(DLid_tree);
			glPopMatrix();

			terrain_angle = terrain_angle + 4;
		}

		glPopMatrix();
	}

	if (track_id % 21 == 15 || track_id % 21 == 16) {
		glPushMatrix();
		glTranslatef(180, 0, 320);
		glRotatef(180, 0, 1, 0);
		for (int image_x = 0; image_x <= 180; image_x += 5) {
			glPushMatrix();
			glTranslatef(image_x, 0, -20);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, 20);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, 21);
			glCallList(DLid_tree);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, -21);
			glCallList(DLid_tree);
			glPopMatrix();
		}
		glPopMatrix();
	}

	if (track_id % 21 == 16 || track_id % 21 == 17) {
		glPushMatrix();
		glTranslatef(0, 0, 260);
		glRotatef(270, 0, 1, 0);
		terrain_angle = 0;
		while (terrain_angle <= 90) {
			glPushMatrix();
			glTranslatef(radius_inner * cos(terrain_angle * (3.14) / 180.0), 0,
					radius_inner * sin(terrain_angle * (3.14) / 180.0));
			glRotatef(90 - terrain_angle, 0, 1, 0);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(
					(radius_inner - 1) * cos(terrain_angle * (3.14) / 180.0), 0,
					(radius_inner - 1) * sin(terrain_angle * (3.14) / 180.0));
			glCallList(DLid_tree);
			glPopMatrix();

			terrain_angle = terrain_angle + 7;
		}

		terrain_angle = 0;
		while (terrain_angle <= 90) {
			glPushMatrix();
			glTranslatef(radius_outer * cos(terrain_angle * (3.14) / 180.0), 0,
					radius_outer * sin(terrain_angle * (3.14) / 180.0));
			glRotatef(90 - terrain_angle, 0, 1, 0);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(
					(radius_outer + 1) * cos(terrain_angle * (3.14) / 180.0), 0,
					(radius_outer + 1) * sin(terrain_angle * (3.14) / 180.0));
			glCallList(DLid_tree);
			glPopMatrix();

			terrain_angle = terrain_angle + 4;
		}

		glPopMatrix();
	}

	if (track_id % 21 == 17 || track_id % 21 == 18) {
		glPushMatrix();
		glTranslatef(-60, 0, 260);
		glRotatef(90, 0, 1, 0);
		for (int image_x = 0; image_x <= 175; image_x += 5) {
			glPushMatrix();
			glTranslatef(image_x, 0, -20);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, 20);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, 21);
			glCallList(DLid_tree);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, -21);
			glCallList(DLid_tree);
			glPopMatrix();
		}
		glPopMatrix();
	}
	if (track_id % 21 == 18 || track_id % 21 == 19) {
		glPushMatrix();
		glTranslatef(-60, 0, 85);
		glRotatef(90, 0, 1, 0);
		for (int image_x = 0; image_x <= 175; image_x += 5) {
			glPushMatrix();
			glTranslatef(image_x, 0, -20);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, 20);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, 21);
			glCallList(DLid_tree);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(image_x, 0, -21);
			glCallList(DLid_tree);
			glPopMatrix();
		}
		glPopMatrix();
	}

	if (track_id % 21 == 19 || track_id % 21 == 20) {
		glPushMatrix();
		glTranslatef(0, 0, -90);
		glRotatef(180, 0, 1, 0);
		terrain_angle = 0;
		while (terrain_angle <= 90) {
			glPushMatrix();
			glTranslatef(radius_inner * cos(terrain_angle * (3.14) / 180.0), 0,
					radius_inner * sin(terrain_angle * (3.14) / 180.0));
			glRotatef(90 - terrain_angle, 0, 1, 0);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(
					(radius_inner - 1) * cos(terrain_angle * (3.14) / 180.0), 0,
					(radius_inner - 1) * sin(terrain_angle * (3.14) / 180.0));
			glCallList(DLid_tree);
			glPopMatrix();

			terrain_angle = terrain_angle + 7;
		}

		terrain_angle = 0;
		while (terrain_angle <= 90) {
			glPushMatrix();
			glTranslatef(radius_outer * cos(terrain_angle * (3.14) / 180.0), 0,
					radius_outer * sin(terrain_angle * (3.14) / 180.0));
			glRotatef(90 - terrain_angle, 0, 1, 0);
			glScalef(0.01, 0.01, 0.01);
			glCallList(DLid_fence);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(
					(radius_outer + 1) * cos(terrain_angle * (3.14) / 180.0), 0,
					(radius_outer + 1) * sin(terrain_angle * (3.14) / 180.0));
			glCallList(DLid_tree);
			glPopMatrix();

			terrain_angle = terrain_angle + 4;
		}

		glPopMatrix();
	}

	//Bridges and tunnels
	glPushMatrix();
	glTranslatef(861, 0, 600);
	glPushMatrix();
	glTranslatef(0, -22.0, 0);
//			glRotatef(90,0,1,0);
	glScalef(0.04, 0.015, 0.02);
	glCallList(DLid_tunnel);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(441, 0, 340);
	glPushMatrix();
	glTranslatef(0, -22.0, 0);
//							glRotatef(90,0,1,0);
	glScalef(0.04, 0.015, 0.015);
	glCallList(DLid_tunnel);
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(240, 0, 500);
	glRotatef(90, 0, 1, 0);
	glPushMatrix();
	glScalef(6, 15, 19);
	glTranslatef(0, -3.9, 0);
	glColor3f(150.0 / 255.0, 150.0 / 255.0, 150.0 / 255.0);
	glCallList(DLid_tree_1);
	glColor3f(1.0, 1.0, 1.0);
	glPopMatrix();
	glPopMatrix();

}
void track_2_fill_vec() {
	vector3D start1_track(0, 0, -170);
	vector3D end1_track(100, 0, -170);
	vector3D start2_track(0, 0, -130);
	vector3D end2_track(100, 0, -130);
	vector3D center_track(0, 0, 0);
	float radius1_track = 0.0;
	float radius2_track = 0.0;
	float angle_track = 0.0;
	string id_track = "S";
	track part_1;
	part_1.start1 = start1_track;
	part_1.end1 = end1_track;
	part_1.start2 = start2_track;
	part_1.end2 = end2_track;
	part_1.id = id_track;
	track_states.push_back(part_1);

	start1_track.x = 100;
	start1_track.y = 0;
	start1_track.z = -170;
	end1_track.x = 200;
	end1_track.y = 0;
	end1_track.z = -170;
	start2_track.x = 100;
	start2_track.y = 0;
	start2_track.z = -130;
	end2_track.x = 200;
	end2_track.y = 0;
	end2_track.z = -130;
	id_track = "S";
	track part_2;
	part_2.start1 = start1_track;
	part_2.end1 = end1_track;
	part_2.start2 = start2_track;
	part_2.end2 = end2_track;
	part_2.id = id_track;
	track_states.push_back(part_2);

	start1_track.x = 200;
	start1_track.y = 0;
	start1_track.z = -170;
	end1_track.x = 300;
	end1_track.y = 0;
	end1_track.z = -170;
	start2_track.x = 200;
	start2_track.y = 0;
	start2_track.z = -130;
	end2_track.x = 300;
	end2_track.y = 0;
	end2_track.z = -130;
	id_track = "S";
	track part_3;
	part_3.start1 = start1_track;
	part_3.end1 = end1_track;
	part_3.start2 = start2_track;
	part_3.end2 = end2_track;
	part_3.id = id_track;
	track_states.push_back(part_3);

	start1_track.x = 300;
	start1_track.y = 0;
	start1_track.z = -170;
	end1_track.x = 380;
	end1_track.y = 0;
	end1_track.z = -90;
	start2_track.x = 300;
	start2_track.y = 0;
	start2_track.z = -130;
	end2_track.x = 340;
	end2_track.y = 0;
	end2_track.z = -90;
	center_track.x = 300;
	center_track.y = 0;
	center_track.z = -90;
	radius1_track = 80.0;
	radius2_track = 40.0;
	angle_track = 1.57;
	id_track = "C";
	track part_4;
	part_4.start1 = start1_track;
	part_4.end1 = end1_track;
	part_4.start2 = start2_track;
	part_4.end2 = end2_track;
	part_4.radius1 = radius1_track;
	part_4.radius2 = radius2_track;
	part_4.angle = angle_track;
	part_4.id = id_track;
	part_4.center = center_track;
	track_states.push_back(part_4);

	start1_track.x = 380;
	start1_track.y = 0;
	start1_track.z = -90;
	end1_track.x = 380;
	end1_track.y = 0;
	end1_track.z = 10;
	start2_track.x = 340;
	start2_track.y = 0;
	start2_track.z = -90;
	end2_track.x = 340;
	end2_track.y = 0;
	end2_track.z = 10;
	id_track = "S";
	track part_5;
	part_5.start1 = start1_track;
	part_5.end1 = end1_track;
	part_5.start2 = start2_track;
	part_5.end2 = end2_track;
	part_5.id = id_track;
	track_states.push_back(part_5);

	start1_track.x = 380;
	start1_track.y = 0;
	start1_track.z = 10;
	end1_track.x = 380;
	end1_track.y = 0;
	end1_track.z = 110;
	start2_track.x = 340;
	start2_track.y = 0;
	start2_track.z = 10;
	end2_track.x = 340;
	end2_track.y = 0;
	end2_track.z = 110;
	id_track = "S";
	track part_6;
	part_6.start1 = start1_track;
	part_6.end1 = end1_track;
	part_6.start2 = start2_track;
	part_6.end2 = end2_track;
	part_6.id = id_track;
	track_states.push_back(part_6);

	start1_track.x = 380;
	start1_track.y = 0;
	start1_track.z = 110;
	end1_track.x = 380;
	end1_track.y = 0;
	end1_track.z = 210;
	start2_track.x = 340;
	start2_track.y = 0;
	start2_track.z = 110;
	end2_track.x = 340;
	end2_track.y = 0;
	end2_track.z = 210;
	id_track = "S";
	track part_7;
	part_7.start1 = start1_track;
	part_7.end1 = end1_track;
	part_7.start2 = start2_track;
	part_7.end2 = end2_track;
	part_7.id = id_track;
	track_states.push_back(part_7);

	start1_track.x = 380;
	start1_track.y = 0;
	start1_track.z = 210;
	end1_track.x = 380;
	end1_track.y = 0;
	end1_track.z = 310;
	start2_track.x = 340;
	start2_track.y = 0;
	start2_track.z = 210;
	end2_track.x = 340;
	end2_track.y = 0;
	end2_track.z = 310;
	id_track = "S";
	track part_8;
	part_8.start1 = start1_track;
	part_8.end1 = end1_track;
	part_8.start2 = start2_track;
	part_8.end2 = end2_track;
	part_8.id = id_track;
	track_states.push_back(part_8);

	start1_track.x = 380;
	start1_track.y = 0;
	start1_track.z = 310;
	end1_track.x = 380;
	end1_track.y = 0;
	end1_track.z = 410;
	start2_track.x = 340;
	start2_track.y = 0;
	start2_track.z = 310;
	end2_track.x = 340;
	end2_track.y = 0;
	end2_track.z = 410;
	id_track = "S";
	track part_9;
	part_9.start1 = start1_track;
	part_9.end1 = end1_track;
	part_9.start2 = start2_track;
	part_9.end2 = end2_track;
	part_9.id = id_track;
	track_states.push_back(part_9);

	start1_track.x = 380;
	start1_track.y = 0;
	start1_track.z = 410;
	end1_track.x = 380;
	end1_track.y = 0;
	end1_track.z = 510;
	start2_track.x = 340;
	start2_track.y = 0;
	start2_track.z = 410;
	end2_track.x = 340;
	end2_track.y = 0;
	end2_track.z = 510;
	id_track = "S";
	track part_10;
	part_10.start1 = start1_track;
	part_10.end1 = end1_track;
	part_10.start2 = start2_track;
	part_10.end2 = end2_track;
	part_10.id = id_track;
	track_states.push_back(part_10);

	start1_track.x = 380;
	start1_track.y = 0;
	start1_track.z = 510;
	end1_track.x = 380;
	end1_track.y = 0;
	end1_track.z = 610;
	start2_track.x = 340;
	start2_track.y = 0;
	start2_track.z = 510;
	end2_track.x = 340;
	end2_track.y = 0;
	end2_track.z = 610;
	id_track = "S";
	track part_11;
	part_11.start1 = start1_track;
	part_11.end1 = end1_track;
	part_11.start2 = start2_track;
	part_11.end2 = end2_track;
	part_11.id = id_track;
	track_states.push_back(part_11);

	start1_track.x = 380;
	start1_track.y = 0;
	start1_track.z = 610;
	end1_track.x = 300;
	end1_track.y = 0;
	end1_track.z = 690;
	start2_track.x = 340;
	start2_track.y = 0;
	start2_track.z = 610;
	end2_track.x = 300;
	end2_track.y = 0;
	end2_track.z = 650;
	center_track.x = 300;
	center_track.y = 0;
	center_track.z = 610;
	radius1_track = 80.0;
	radius2_track = 40.0;
	angle_track = 1.57;
	id_track = "C";
	track part_12;
	part_12.start1 = start1_track;
	part_12.end1 = end1_track;
	part_12.start2 = start2_track;
	part_12.end2 = end2_track;
	part_12.radius1 = radius1_track;
	part_12.radius2 = radius2_track;
	part_12.angle = angle_track;
	part_12.id = id_track;
	part_12.center = center_track;
	track_states.push_back(part_12);

	start1_track.x = 300;
	start1_track.y = 0;
	start1_track.z = 690;
	end1_track.x = 220;
	end1_track.y = 0;
	end1_track.z = 610;
	start2_track.x = 300;
	start2_track.y = 0;
	start2_track.z = 650;
	end2_track.x = 260;
	end2_track.y = 0;
	end2_track.z = 610;
	center_track.x = 300;
	center_track.y = 0;
	center_track.z = 610;
	radius1_track = 80.0;
	radius2_track = 40.0;
	angle_track = 1.57;
	id_track = "C";
	track part_13;
	part_13.start1 = start1_track;
	part_13.end1 = end1_track;
	part_13.start2 = start2_track;
	part_13.end2 = end2_track;
	part_13.radius1 = radius1_track;
	part_13.radius2 = radius2_track;
	part_13.angle = angle_track;
	part_13.id = id_track;
	part_13.center = center_track;
	track_states.push_back(part_13);

	start1_track.x = 220;
	start1_track.y = 0;
	start1_track.z = 610;
	end1_track.x = 220;
	end1_track.y = 0;
	end1_track.z = 485;
	start2_track.x = 260;
	start2_track.y = 0;
	start2_track.z = 610;
	end2_track.x = 260;
	end2_track.y = 0;
	end2_track.z = 485;
	id_track = "S";
	track part_14;
	part_14.start1 = start1_track;
	part_14.end1 = end1_track;
	part_14.start2 = start2_track;
	part_14.end2 = end2_track;
	part_14.id = id_track;
	track_states.push_back(part_14);

	start1_track.x = 220;
	start1_track.y = 0;
	start1_track.z = 485;
	end1_track.x = 220;
	end1_track.y = 0;
	end1_track.z = 380;
	start2_track.x = 260;
	start2_track.y = 0;
	start2_track.z = 485;
	end2_track.x = 260;
	end2_track.y = 0;
	end2_track.z = 380;
	id_track = "S";
	track part_15;
	part_15.start1 = start1_track;
	part_15.end1 = end1_track;
	part_15.start2 = start2_track;
	part_15.end2 = end2_track;
	part_15.id = id_track;
	track_states.push_back(part_15);

	start1_track.x = 220;
	start1_track.y = 0;
	start1_track.z = 380;
	end1_track.x = 180;
	end1_track.y = 0;
	end1_track.z = 340;
	start2_track.x = 260;
	start2_track.y = 0;
	start2_track.z = 380;
	end2_track.x = 180;
	end2_track.y = 0;
	end2_track.z = 300;
	center_track.x = 180;
	center_track.y = 0;
	center_track.z = 380;
	radius1_track = 80.0;
	radius2_track = 40.0;
	angle_track = -1.57;
	id_track = "C";
	track part_16;
	part_16.start1 = start1_track;
	part_16.end1 = end1_track;
	part_16.start2 = start2_track;
	part_16.end2 = end2_track;
	part_16.radius1 = radius1_track;
	part_16.radius2 = radius2_track;
	part_16.angle = angle_track;
	part_16.id = id_track;
	part_16.center = center_track;
	track_states.push_back(part_16);

	start1_track.x = 180;
	start1_track.y = 0;
	start1_track.z = 340;
	end1_track.x = 0;
	end1_track.y = 0;
	end1_track.z = 340;
	start2_track.x = 180;
	start2_track.y = 0;
	start2_track.z = 300;
	end2_track.x = 0;
	end2_track.y = 0;
	end2_track.z = 300;
	id_track = "S";
	track part_17;
	part_17.start1 = start1_track;
	part_17.end1 = end1_track;
	part_17.start2 = start2_track;
	part_17.end2 = end2_track;
	part_17.id = id_track;
	track_states.push_back(part_17);

	start1_track.x = 0;
	start1_track.y = 0;
	start1_track.z = 340;
	end1_track.x = -80;
	end1_track.y = 0;
	end1_track.z = 260;
	start2_track.x = 0;
	start2_track.y = 0;
	start2_track.z = 300;
	end2_track.x = -40;
	end2_track.y = 0;
	end2_track.z = 260;
	center_track.x = 0;
	center_track.y = 0;
	center_track.z = 260;
	radius1_track = 80.0;
	radius2_track = 40.0;
	angle_track = 1.57;
	id_track = "C";
	track part_18;
	part_18.start1 = start1_track;
	part_18.end1 = end1_track;
	part_18.start2 = start2_track;
	part_18.end2 = end2_track;
	part_18.radius1 = radius1_track;
	part_18.radius2 = radius2_track;
	part_18.angle = angle_track;
	part_18.id = id_track;
	part_18.center = center_track;
	track_states.push_back(part_18);

	start1_track.x = -80;
	start1_track.y = 0;
	start1_track.z = 260;
	end1_track.x = -80;
	end1_track.y = 0;
	end1_track.z = 85;
	start2_track.x = -40;
	start2_track.y = 0;
	start2_track.z = 260;
	end2_track.x = -40;
	end2_track.y = 0;
	end2_track.z = 85;
	id_track = "S";
	track part_19;
	part_19.start1 = start1_track;
	part_19.end1 = end1_track;
	part_19.start2 = start2_track;
	part_19.end2 = end2_track;
	part_19.id = id_track;
	track_states.push_back(part_19);

	start1_track.x = -80;
	start1_track.y = 0;
	start1_track.z = 85;
	end1_track.x = -80;
	end1_track.y = 0;
	end1_track.z = -90;
	start2_track.x = -40;
	start2_track.y = 0;
	start2_track.z = 85;
	end2_track.x = -40;
	end2_track.y = 0;
	end2_track.z = -90;
	id_track = "S";
	track part_20;
	part_20.start1 = start1_track;
	part_20.end1 = end1_track;
	part_20.start2 = start2_track;
	part_20.end2 = end2_track;
	part_20.id = id_track;
	track_states.push_back(part_20);

	start1_track.x = -80;
	start1_track.y = 0;
	start1_track.z = -90;
	end1_track.x = 0;
	end1_track.y = 0;
	end1_track.z = -170;
	start2_track.x = -40;
	start2_track.y = 0;
	start2_track.z = -90;
	end2_track.x = 0;
	end2_track.y = 0;
	end2_track.z = -130;
	center_track.x = 0;
	center_track.y = 0;
	center_track.z = -90;
	radius1_track = 80.0;
	radius2_track = 40.0;
	angle_track = 1.57;
	id_track = "C";
	track part_21;
	part_21.start1 = start1_track;
	part_21.end1 = end1_track;
	part_21.start2 = start2_track;
	part_21.end2 = end2_track;
	part_21.radius1 = radius1_track;
	part_21.radius2 = radius2_track;
	part_21.angle = angle_track;
	part_21.id = id_track;
	part_21.center = center_track;
	track_states.push_back(part_21);

}

float _scale;
const char* STRS[1] = { "Speed" };
float computeScale(const char* strs[1]) {
	float maxWidth = 0;
	for (int i = 0; i < 1; i++) {
		float width = t3dDrawWidth(strs[i]);
		if (width > maxWidth) {
			maxWidth = width;
		}
	}

	return 2.6f / maxWidth;
}

void cleanup1() {
	t3dCleanup();
}

void drawNumCollisions(int lap, int y, bool g) {
	ostringstream oss;
	ostringstream oss1;
	ostringstream oss2;
	ostringstream oss3;
	ostringstream oss4;

	oss << "LAP - " << lap <<"/"<<Total_laps;

	string str = oss.str();
	oss1 << "POSITION - " << plane_position<<"/8";

	string str1 = oss1.str();
//    oss2 << " Star: " << s;
	string str2 = oss2.str();
	oss3 << "GAME OVER";
	string str3 = oss3.str();
	oss4 << "YOU FINISHED " << print_pos;
	string str4 = oss4.str();
//
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);

	glPushMatrix();
	glColor3f(1.0f, 1.0, 0.0f);
	glTranslatef(-2.50f, 0.90f, -5.0f);
	glScalef(0.2f, 0.2f, 0.2f);
//    cout<<"running"<<endl;
	t3dDraw2D(str, 0, 0);
	glTranslatef(13.0f, 2.0f, -5.0f);
//
//
	t3dDraw2D(str1, 0, 0);
//    glTranslatef(15.0f, 2.0f, -5.0f);
//
//    t3dDraw2D(str2, 0, 0);
	if (g) {
		glTranslatef(-5.0f, -7.0f, -5.0f);
		glScalef(4.0, 4.0, 4.0);
		//
		t3dDraw2D(str3, 0, 0);
		glTranslatef(0.0f, -2.0f, -10.0f);
		glScalef(1.0, 1.0, 1.0);
		//
		t3dDraw2D(str4, 0, 0);
	}
	glColor3f(1.0f, 1.0, 1.0f);
	glPopMatrix();

	glEnable(GL_LIGHTING);
}

void position() {
	int count = 0;
	if (Lap > Lap_2) {
		count++;
	} else if (Lap < Lap_2) {

	} else {
		if (plane2_track > track_id) {
		} else if (plane2_track < track_id) {
			count++;
		} else {
			if (dotProduct(subtract(mainPlane.center, plane2.center),
					mainPlane.headDir) >= 0) {
				count++;
			}
		}
	}
	if (Lap > Lap_3) {
		count++;
	} else if (Lap < Lap_3) {

	} else {
		if (plane3_track > track_id) {
		} else if (plane3_track < track_id) {
			count++;
		} else {
			if (dotProduct(subtract(mainPlane.center, plane3.center),
					mainPlane.headDir) >= 0) {
				count++;
			}
		}
	}
	if (Lap > Lap_4) {
		count++;
	} else if (Lap < Lap_4) {

	} else {
		if (plane4_track > track_id) {
		} else if (plane4_track < track_id) {
			count++;
		} else {
			if (dotProduct(subtract(mainPlane.center, plane4.center),
					mainPlane.headDir) >= 0) {
				count++;
			}
		}
	}
	if (Lap > Lap_5) {
		count++;
	} else if (Lap < Lap_5) {

	} else {
		if (plane5_track > track_id) {
		} else if (plane5_track < track_id) {
			count++;
		} else {
			if (dotProduct(subtract(mainPlane.center, plane5.center),
					mainPlane.headDir) >= 0) {
				count++;
			}
		}
	}
	if (Lap > Lap_6) {
		count++;
	} else if (Lap < Lap_6) {

	} else {
		if (plane6_track > track_id) {
		} else if (plane6_track < track_id) {
			count++;
		} else {
			if (dotProduct(subtract(mainPlane.center, plane6.center),
					mainPlane.headDir) >= 0) {
				count++;
			}
		}
	}
	if (Lap > Lap_7) {
		count++;
	} else if (Lap < Lap_7) {

	} else {
		if (plane7_track > track_id) {
		} else if (plane7_track < track_id) {
			count++;
		} else {
			if (dotProduct(subtract(mainPlane.center, plane7.center),
					mainPlane.headDir) >= 0) {
				count++;
			}
		}
	}
	if (Lap > Lap_8) {
		count++;
	} else if (Lap < Lap_8) {

	} else {
		if (plane8_track > track_id) {
		} else if (plane8_track < track_id) {
			count++;
		} else {
			if (dotProduct(subtract(mainPlane.center, plane8.center),
					mainPlane.headDir) >= 0) {
				count++;
			}
		}
	}

	plane_position = 8 - count;
}

void draw() {
	glClearColor(119.0 / 255.0, 136.0 / 255.0, 153.0 / 255.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glTranslatef(1.0, 1.0, 0);
	drawNumCollisions(Lap, plane_position, GameOver);
	glPopMatrix();
	float s = 7.0;
	camera = subtract(mainPlane.center, constProduct(mainPlane.headDir, s));
//	    camera2=subtract(plane2.center,constProduct(plane2.headDir,s));
	gluLookAt(camera.x, camera.y + 1.0, camera.z, mainPlane.center.x,
			mainPlane.center.y + 1.0, mainPlane.center.z, 0.0, 1.0, 0.0);
//	    gluLookAt(camera2.x,camera2.y+1.0,camera2.z,plane2.center.x,plane2.center.y+1.0,plane2.center.z,0.0,1.0,0.0);

	GLfloat ambientColor[] = { 0.4f, 0.4f, 0.4f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

	GLfloat lightColor0[] = { 0.6f, 0.6f, 0.6f, 1.0f };
	GLfloat lightPos0[] = { -0.5f, 0.8f, 0.1f, 0.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

	glPushMatrix();
	glTranslatef(mainPlane.center.x, mainPlane.center.y, mainPlane.center.z);
	glScalef(0.1, 0.1, 0.1);
	glRotatef(180, 0, 1, 0);
	glRotatef(leftRotationY, 0.0, 1.0, 0.0);
	glRotatef(rightRotationY, 0.0, 1.0, 0.0);
	glRotatef(rightRotation, 1.0, 0.0, 0.0);
	glRotatef(leftRotation, 1.0, 0.0, 0.0);

	glCallList(DLid);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(plane2.center.x, plane2.center.y, plane2.center.z);
	glScalef(0.1, 0.10, 0.1);
	glRotatef(180, 0, 1, 0);
	glRotatef(leftRotationY2, 0.0, 1.0, 0.0);
	glRotatef(rightRotationY2, 0.0, 1.0, 0.0);
	glRotatef(rightRotation2, 1.0, 0.0, 0.0);
	glRotatef(leftRotation2, 1.0, 0.0, 0.0);

	glCallList(DLid);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(plane3.center.x, plane3.center.y, plane3.center.z);
	glScalef(0.1, 0.1, 0.1);
	glRotatef(180, 0, 1, 0);
	glRotatef(leftRotationY3, 0.0, 1.0, 0.0);
	glRotatef(rightRotationY3, 0.0, 1.0, 0.0);
	glRotatef(rightRotation3, 1.0, 0.0, 0.0);
	glRotatef(leftRotation3, 1.0, 0.0, 0.0);

	glCallList(DLid);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(plane4.center.x, plane4.center.y, plane4.center.z);
	glScalef(0.1, 0.1, 0.1);
	glRotatef(180, 0, 1, 0);
	glRotatef(leftRotationY4, 0.0, 1.0, 0.0);
	glRotatef(rightRotationY4, 0.0, 1.0, 0.0);
	glRotatef(rightRotation4, 1.0, 0.0, 0.0);
	glRotatef(leftRotation4, 1.0, 0.0, 0.0);

	glCallList(DLid);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(plane5.center.x, plane5.center.y, plane5.center.z);
	glScalef(0.1, 0.1, 0.1);
	glRotatef(180, 0, 1, 0);
	glRotatef(leftRotationY5, 0.0, 1.0, 0.0);
	glRotatef(rightRotationY5, 0.0, 1.0, 0.0);
	glRotatef(rightRotation5, 1.0, 0.0, 0.0);
	glRotatef(leftRotation5, 1.0, 0.0, 0.0);

	glCallList(DLid);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(plane6.center.x, plane6.center.y, plane6.center.z);
	glScalef(0.1, 0.1, 0.1);
	glRotatef(180, 0, 1, 0);
	glRotatef(leftRotationY6, 0.0, 1.0, 0.0);
	glRotatef(rightRotationY6, 0.0, 1.0, 0.0);
	glRotatef(rightRotation6, 1.0, 0.0, 0.0);
	glRotatef(leftRotation6, 1.0, 0.0, 0.0);

	glCallList(DLid);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(plane7.center.x, plane7.center.y, plane7.center.z);
	glScalef(0.1, 0.1, 0.1);
	glRotatef(180, 0, 1, 0);
	glRotatef(leftRotationY7, 0.0, 1.0, 0.0);
	glRotatef(rightRotationY7, 0.0, 1.0, 0.0);
	glRotatef(rightRotation7, 1.0, 0.0, 0.0);
	glRotatef(leftRotation7, 1.0, 0.0, 0.0);

	glCallList(DLid);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(plane8.center.x, plane8.center.y, plane8.center.z);
	glScalef(0.1, 0.1, 0.1);
	glRotatef(180, 0, 1, 0);
	glRotatef(leftRotationY8, 0.0, 1.0, 0.0);
	glRotatef(rightRotationY8, 0.0, 1.0, 0.0);
	glRotatef(rightRotation8, 1.0, 0.0, 0.0);
	glRotatef(leftRotation8, 1.0, 0.0, 0.0);

	glCallList(DLid);
	glPopMatrix();

	if (fire == 1) {
		glPushMatrix();
		glTranslatef(missile.center.x, missile.center.y, missile.center.z);
		glColor3f(1.0, 1.0, 0.0);
		glScalef(0.8, 0.8, 0.8);
		glRotatef(180, 0, 1, 0);
		glRotatef(leftRotationYM1, 0.0, 1.0, 0.0);
		glRotatef(rightRotationYM1, 0.0, 1.0, 0.0);

		glCallList(DLid_missile);
		glColor3f(1.0, 1.0, 1.0);

		glPopMatrix();

	}
	if (blast > 0 && blast < 15) {
		blast++;
		glPushMatrix();

		glEnable(GL_TEXTURE_2D);
		if (tyre == 0) {
			glBindTexture(GL_TEXTURE_2D, _textureId_fire1);
		} else {
			glBindTexture(GL_TEXTURE_2D, _textureId_fire2);
		}

//								       	glTranslatef(0,-0.1,0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		vector3D leftSide = normalise(crossProduct(up, missile.headDir));
		vector3D rightSide = normalise(crossProduct(missile.headDir, up));
		vector3D leftWing = add(missile.center, constProduct(leftSide, 0.5));
		vector3D rightWing = add(missile.center, constProduct(rightSide, 0.5));
		cout << "check" << endl;
		cout << rightWing.x << " " << rightWing.z << endl;
		cout << leftWing.x << " " << leftWing.z << endl;
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(leftWing.x - missile.headDir.x * 1.0, 0.9, leftWing.z);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(rightWing.x - missile.headDir.x * 1.0, 0.9, rightWing.z);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(rightWing.x - missile.headDir.x * 1.0, 1.4, rightWing.z);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(leftWing.x - missile.headDir.x * 1.0, 1.4, leftWing.z);
		glEnd();

		glDisable(GL_TEXTURE_2D);

		glPopMatrix();

	}
//		track_1();
//		track_1_texture();
	track_2();
	track_2_texture();

	glutSwapBuffers();

}

void keyup(int k, int x, int y) {
	if (k == GLUT_KEY_UP) {

	}
	if (k == GLUT_KEY_LEFT) {
		leftKey = false;
	}
	if (k == GLUT_KEY_RIGHT) {
		rightKey = false;
	}

	if (k == GLUT_KEY_F1) {
//        	fire=0;
//        	cout<<"holdddd"<<endl;
	}

}
//
void keyboard(unsigned char key, int x, int y) {
	if (key == 27) {
		exit(0);
	} else if (key == 32) {
		if (collided == 1) {
			collided = 0;

			fire = 1;
			blast = 0;
			vector3D leftSide = normalise(crossProduct(up, mainPlane.headDir));
			vector3D rightSide = normalise(crossProduct(mainPlane.headDir, up));
			vector3D leftWing = add(mainPlane.center,
					constProduct(leftSide, 1.0));

			missile.center = leftWing;
			missile.headDir = mainPlane.headDir;
			missile.velocity = constProduct(mainPlane.headDir, 8);
			leftRotationYM1 = leftRotationY;
			rightRotationYM1 = rightRotationY;
			missile1_track = track_id;
			cout << "Fireeddd" << endl;
		}
		glutPostRedisplay();

	}

}

void specialKeys(int key, int x, int y) {

	if (key == GLUT_KEY_F1) {
		if (collided == 1) {
			collided = 0;

			fire = 1;
			blast = 0;
			vector3D leftSide = normalise(crossProduct(up, mainPlane.headDir));
			vector3D rightSide = normalise(crossProduct(mainPlane.headDir, up));
			vector3D leftWing = add(mainPlane.center,
					constProduct(leftSide, 1.0));

			missile.center = leftWing;
			missile.headDir = mainPlane.headDir;
			missile.velocity = constProduct(mainPlane.headDir, 3);
			leftRotationYM1 = leftRotationY;
			rightRotationYM1 = rightRotationY;
			missile1_track = track_id;
			cout << "Fireeddd" << endl;
		}
		glutPostRedisplay();
	}

	else if (key == GLUT_KEY_RIGHT) {
		rightKey = true;
//    	cout<<"right pressed"<<endl;
	}

	else if (key == GLUT_KEY_LEFT) {
		leftKey = true;
	}

	else if (key == GLUT_KEY_UP) {
		if (!GameOver) {
			if (magnitude(mainPlane.velocity) < 2.5) {
				mainPlane.velocity = add(mainPlane.velocity,
						constProduct(mainPlane.headDir, 0.5));
			}
		}
	}
//
//
	else if (key == GLUT_KEY_DOWN) {
		if (dotProduct(mainPlane.velocity, mainPlane.headDir) >= 0) {
			mainPlane.velocity = subtract(mainPlane.velocity,
					constProduct(mainPlane.headDir, 0.2));
		}

		glutPostRedisplay();
	}

	glutPostRedisplay();

}

float sideValue(float ang) {
	return (-1.6 / 95.0) * ang + 1.6;
}

void collision(vector<track> racing_track) {
	track t = racing_track[track_id];
	if (racing_track[track_id].id == "S") {
		vector3D road_dir = normalise(
				subtract(racing_track[track_id].end1,
						racing_track[track_id].start1));
		vector3D plane_dir1 = normalise(
				subtract(racing_track[track_id].end1, mainPlane.center));
//		vector3D plane_dir2=normalise(subtract(racing_track[track_id].end2,mainPlane.center));
		if (dotProduct(road_dir, plane_dir1) >= 0) {
//			cout<<"inside straight"<<endl;
			vector3D leftSide = normalise(crossProduct(up, mainPlane.headDir));
			vector3D rightSide = normalise(crossProduct(mainPlane.headDir, up));
			vector3D leftWing = add(mainPlane.center,
					constProduct(leftSide, mainPlane.left));
			vector3D rightWing = add(mainPlane.center,
					constProduct(rightSide, mainPlane.right));
			vector3D wing_dir1 = normalise(
					subtract(racing_track[track_id].end1, leftWing));
			vector3D wing_dir2 = normalise(
					subtract(racing_track[track_id].end2, rightWing));

			if (crossProduct(road_dir, wing_dir1).y <= 0) {
//				cout<<"negitive outsideee"<<endl;
				mainPlane.center = add(mainPlane.center,
						constProduct(
								normalise(crossProduct(mainPlane.headDir, up)),
								0.2));
				mainPlane.velocity = constProduct(mainPlane.velocity, 0.10);
			}
			if (crossProduct(road_dir, wing_dir2).y >= 0) {
				mainPlane.center = add(mainPlane.center,
						constProduct(
								normalise(crossProduct(mainPlane.headDir, up)),
								-0.2));
				mainPlane.velocity = constProduct(mainPlane.velocity, 0.10);
			}
		} else {
			cout << "incrementeddddddddddddddddddddddd" << endl;
			track_id = (track_id + 1) % racing_track.size();
			if (track_id % track_states.size() == 0) {
				Lap++;
			}
		}
	} else {
		vector3D start_circle = normalise(
				subtract(racing_track[track_id].start1,
						racing_track[track_id].center));
		vector3D plane_vector = subtract(mainPlane.center, t.center);
		plane_vector.y = 0.0;
		if (angle(start_circle, plane_vector)
				> cos(racing_track[track_id].angle + 0.001)) {
			cout << "circle" << endl;
			vector3D head_dir = mainPlane.headDir;
			head_dir.y = 0.0;
			vector3D leftSide = normalise(crossProduct(up, mainPlane.headDir));
			vector3D rightSide = normalise(crossProduct(mainPlane.headDir, up));
			vector3D leftWing = add(mainPlane.center,
					constProduct(leftSide, mainPlane.left));
			vector3D rightWing = add(mainPlane.center,
					constProduct(rightSide, mainPlane.right));

			if (racing_track[track_id].angle > 0) {
				if (magnitude(subtract(leftWing, t.center)) >= t.radius1) {
					cout << "outer" << endl;
					if (dotProduct(crossProduct(up, normalise(plane_vector)),
							mainPlane.headDir) > 0.707) {
						mainPlane.center.x = mainPlane.center.x
								- plane_vector.x * 0.01;
						mainPlane.center.z = mainPlane.center.z
								- plane_vector.z * 0.01;
						mainPlane.velocity = constProduct(mainPlane.velocity,
								0.20);
					} else {
						mainPlane.center.x = mainPlane.center.x
								- plane_vector.x * 0.01;
						mainPlane.center.z = mainPlane.center.z
								- plane_vector.z * 0.01;
						mainPlane.velocity = constProduct(mainPlane.velocity,
								0.1);
					}

				} else if (magnitude(subtract(rightWing, t.center))
						<= t.radius2) {
					cout << "inner" << endl;
					if (dotProduct(crossProduct(up, normalise(plane_vector)),
							mainPlane.headDir) > 0.707) {
						mainPlane.center.x = mainPlane.center.x
								+ plane_vector.x * 0.01;
						mainPlane.center.z = mainPlane.center.z
								+ plane_vector.z * 0.01;
						mainPlane.velocity = constProduct(mainPlane.velocity,
								0.20);
					} else {
						mainPlane.center.x = mainPlane.center.x
								+ plane_vector.x * 0.01;
						mainPlane.center.z = mainPlane.center.z
								+ plane_vector.z * 0.01;
						mainPlane.velocity = constProduct(mainPlane.velocity,
								0.1);
					}
				}
			} else {
				if (magnitude(subtract(rightWing, t.center)) >= t.radius1) {
					cout << "outer" << endl;
					if (dotProduct(crossProduct(up, normalise(plane_vector)),
							mainPlane.headDir) > 0.707) {
						mainPlane.center.x = mainPlane.center.x
								- plane_vector.x * 0.01;
						mainPlane.center.z = mainPlane.center.z
								- plane_vector.z * 0.01;
						mainPlane.velocity = constProduct(mainPlane.velocity,
								0.20);
					} else {
						mainPlane.center.x = mainPlane.center.x
								- plane_vector.x * 0.01;
						mainPlane.center.z = mainPlane.center.z
								- plane_vector.z * 0.01;
						mainPlane.velocity = constProduct(mainPlane.velocity,
								0.1);
					}

				} else if (magnitude(subtract(leftWing, t.center))
						<= t.radius2) {
					cout << "inner" << endl;
					if (dotProduct(crossProduct(up, normalise(plane_vector)),
							mainPlane.headDir) > 0.707) {
						mainPlane.center.x = mainPlane.center.x
								+ plane_vector.x * 0.01;
						mainPlane.center.z = mainPlane.center.z
								+ plane_vector.z * 0.01;
						mainPlane.velocity = constProduct(mainPlane.velocity,
								0.20);
					} else {
						mainPlane.center.x = mainPlane.center.x
								+ plane_vector.x * 0.01;
						mainPlane.center.z = mainPlane.center.z
								+ plane_vector.z * 0.01;
						mainPlane.velocity = constProduct(mainPlane.velocity,
								0.1);
					}
				}

			}

		} else {
			cout << "incrementeddddddddddddddddddddddd" << endl;
			track_id = (track_id + 1) % racing_track.size();
			if (track_id % track_states.size() == 0) {
				Lap++;
			}
		}

	}
	////////////////////////////////////////////////////////////////////
	if (fire == 1) {
		track m_track = racing_track[missile1_track];
		if (racing_track[missile1_track].id == "S") {
			vector3D road_dir = normalise(
					subtract(racing_track[missile1_track].end1,
							racing_track[missile1_track].start1));
			vector3D plane_dir1 = normalise(
					subtract(racing_track[missile1_track].end1,
							missile.center));
			//		vector3D plane_dir2=normalise(subtract(racing_track[missile1_track].end2,missile.center));
			if (dotProduct(road_dir, plane_dir1) >= 0) {
				//			cout<<"inside straight"<<endl;
				vector3D leftSide = normalise(
						crossProduct(up, missile.headDir));
				vector3D rightSide = normalise(
						crossProduct(missile.headDir, up));
				vector3D leftWing = add(missile.center,
						constProduct(leftSide, missile.left));
				vector3D rightWing = add(missile.center,
						constProduct(rightSide, missile.right));
				vector3D wing_dir1 = normalise(
						subtract(racing_track[missile1_track].end1, leftWing));
				vector3D wing_dir2 = normalise(
						subtract(racing_track[missile1_track].end2, rightWing));

				if (crossProduct(road_dir, wing_dir1).y <= 0) {
					//				cout<<"negitive outsideee"<<endl;
					fire = 0;
					blast = 1;
					collided = 1;
				}
				if (crossProduct(road_dir, wing_dir2).y >= 0) {
					fire = 0;
					blast = 1;
					collided = 1;
				}
			} else {
				cout << "incrementeddddddddddddddddddddddd" << endl;
				missile1_track = (missile1_track + 1) % racing_track.size();
			}
		} else {

			vector3D start_circle = normalise(
					subtract(racing_track[missile1_track].start1,
							racing_track[missile1_track].center));
			vector3D plane_vector = subtract(missile.center, m_track.center);
			plane_vector.y = 0.0;
			if (angle(start_circle, plane_vector)
					> cos(racing_track[missile1_track].angle + 0.1)) {
				vector3D head_dir = missile.headDir;
				head_dir.y = 0.0;
				vector3D leftSide = normalise(
						crossProduct(up, missile.headDir));
				vector3D rightSide = normalise(
						crossProduct(missile.headDir, up));
				vector3D leftWing = add(missile.center,
						constProduct(leftSide, missile.left));
				vector3D rightWing = add(missile.center,
						constProduct(rightSide, missile.right));

				if (magnitude(subtract(leftWing, m_track.center))
						>= m_track.radius1) {
					fire = 0;
					blast = 1;
					collided = 1;
				} else if (magnitude(subtract(rightWing, m_track.center))
						<= m_track.radius2) {
					fire = 0;
					blast = 1;
					collided = 1;
				}

			} else {
				//			cout<<"incrementeddddddddddddddddddddddd"<<endl;
				missile1_track = (missile1_track + 1) % racing_track.size();
			}

		}

		if ((missile.center.x - plane2.center.x)
				* (missile.center.x - plane2.center.x)
				+ (missile.center.z - plane2.center.z)
						* (missile.center.z - plane2.center.z)
				<= (plane2.left) * (plane2.left)) {
			cout << "collision detected" << endl;

			plane2.velocity = constProduct(plane2.velocity, 0.01);
			fire = 0;
			blast = 1;
			collided = 1;

		}
		if ((missile.center.x - plane3.center.x)
				* (missile.center.x - plane3.center.x)
				+ (missile.center.z - plane3.center.z)
						* (missile.center.z - plane3.center.z)
				<= (plane3.left) * (plane3.left)) {
			cout << "collision detected" << endl;
			plane3.velocity = constProduct(plane3.velocity, 0.01);
			fire = 0;
			blast = 1;
			collided = 1;

		}
		if ((missile.center.x - plane4.center.x)
				* (missile.center.x - plane4.center.x)
				+ (missile.center.z - plane4.center.z)
						* (missile.center.z - plane4.center.z)
				<= (plane4.left) * (plane4.left)) {
			cout << "collision detected" << endl;

			plane4.velocity = constProduct(plane4.velocity, 0.01);
			fire = 0;
			blast = 1;
			collided = 1;

		}
		if ((missile.center.x - plane5.center.x)
				* (missile.center.x - plane5.center.x)
				+ (missile.center.z - plane5.center.z)
						* (missile.center.z - plane5.center.z)
				<= (plane5.left) * (plane5.left)) {
			cout << "collision detected" << endl;

			plane5.velocity = constProduct(plane5.velocity, 0.01);
			fire = 0;
			blast = 1;
			collided = 1;

		}
		if ((missile.center.x - plane6.center.x)
				* (missile.center.x - plane6.center.x)
				+ (missile.center.z - plane6.center.z)
						* (missile.center.z - plane6.center.z)
				<= (plane6.left) * (plane6.left)) {
			cout << "collision detected" << endl;

			plane6.velocity = constProduct(plane6.velocity, 0.01);
			fire = 0;
			blast = 1;
			collided = 1;

		}
		if ((missile.center.x - plane7.center.x)
				* (missile.center.x - plane7.center.x)
				+ (missile.center.z - plane7.center.z)
						* (missile.center.z - plane7.center.z)
				<= (plane7.left) * (plane7.left)) {
			cout << "collision detected" << endl;

			plane7.velocity = constProduct(plane7.velocity, 0.01);
			fire = 0;
			blast = 1;
			collided = 1;

		}
		if ((missile.center.x - plane8.center.x)
				* (missile.center.x - plane8.center.x)
				+ (missile.center.z - plane8.center.z)
						* (missile.center.z - plane8.center.z)
				<= (plane8.left) * (plane8.left)) {
			cout << "collision detected" << endl;

			plane8.velocity = constProduct(plane8.velocity, 0.01);
			fire = 0;
			blast = 1;
			collided = 1;

		}
	}
	/////////////////////////////////////////////////////////////////////////////
	if ((mainPlane.center.x - plane2.center.x)
			* (mainPlane.center.x - plane2.center.x)
			+ (mainPlane.center.z - plane2.center.z)
					* (mainPlane.center.z - plane2.center.z)
			<= (mainPlane.left + plane2.left - 0.2)
					* (mainPlane.left + plane2.left - 0.2)) {
		cout << "collision detected" << endl;
		vector3D leftSide = normalise(crossProduct(up, mainPlane.headDir));
		vector3D rightSide = normalise(crossProduct(mainPlane.headDir, up));
		if (dotProduct(subtract(mainPlane.center, plane2.center),
				mainPlane.headDir) >= 0) {
			mainPlane.velocity = constProduct(mainPlane.velocity, 1.1);
			plane2.velocity = constProduct(plane2.velocity, 0.1);
			cout << "reduceeeeeeeeeee" << endl;
			auto_rotation2=0.01;
		} else {
			cout << "uppppppppppppppppppppppppp" << endl;
			mainPlane.velocity = constProduct(mainPlane.velocity, 0.1);
			plane2.velocity = constProduct(plane2.velocity, 1.05);
		}

	}
	if ((mainPlane.center.x - plane3.center.x)
			* (mainPlane.center.x - plane3.center.x)
			+ (mainPlane.center.z - plane3.center.z)
					* (mainPlane.center.z - plane3.center.z)
			<= (mainPlane.left + plane3.left - 0.2)
					* (mainPlane.left + plane3.left - 0.2)) {
		cout << "collision detected" << endl;
		vector3D leftSide = normalise(crossProduct(up, mainPlane.headDir));
		vector3D rightSide = normalise(crossProduct(mainPlane.headDir, up));
		if (dotProduct(subtract(mainPlane.center, plane3.center),
				mainPlane.headDir) >= 0) {
			mainPlane.velocity = constProduct(mainPlane.velocity, 1.1);
			plane3.velocity = constProduct(plane3.velocity, 0.1);
			auto_rotation3=0.01;
		} else {
			mainPlane.velocity = constProduct(mainPlane.velocity, 0.1);
			plane3.velocity = constProduct(plane3.velocity, 1.05);
		}
	}
	if ((mainPlane.center.x - plane4.center.x)
			* (mainPlane.center.x - plane4.center.x)
			+ (mainPlane.center.z - plane4.center.z)
					* (mainPlane.center.z - plane4.center.z)
			<= (mainPlane.left + plane4.left - 0.2)
					* (mainPlane.left + plane4.left - 0.2)) {
		cout << "collision detected" << endl;
		vector3D leftSide = normalise(crossProduct(up, mainPlane.headDir));
		vector3D rightSide = normalise(crossProduct(mainPlane.headDir, up));
		if (dotProduct(subtract(mainPlane.center, plane4.center),
				mainPlane.headDir) >= 0) {
			mainPlane.velocity = constProduct(mainPlane.velocity, 1.1);
			plane4.velocity = constProduct(plane4.velocity, 0.1);
			auto_rotation4=0.01;
		} else {
			mainPlane.velocity = constProduct(mainPlane.velocity, 0.1);
			plane4.velocity = constProduct(plane4.velocity, 1.05);
		}
	}

	if ((mainPlane.center.x - plane5.center.x)
			* (mainPlane.center.x - plane5.center.x)
			+ (mainPlane.center.z - plane5.center.z)
					* (mainPlane.center.z - plane5.center.z)
			<= (mainPlane.left + plane5.left - 0.2)
					* (mainPlane.left + plane5.left - 0.2)) {
		cout << "collision detected" << endl;
		vector3D leftSide = normalise(crossProduct(up, mainPlane.headDir));
		vector3D rightSide = normalise(crossProduct(mainPlane.headDir, up));
		if (dotProduct(subtract(mainPlane.center, plane5.center),
				mainPlane.headDir) >= 0) {
			mainPlane.velocity = constProduct(mainPlane.velocity, 1.1);
			plane5.velocity = constProduct(plane5.velocity, 0.1);
			auto_rotation5=0.01;
		} else {
			mainPlane.velocity = constProduct(mainPlane.velocity, 0.1);
			plane5.velocity = constProduct(plane5.velocity, 1.05);
		}
	}
	if ((mainPlane.center.x - plane6.center.x)
			* (mainPlane.center.x - plane6.center.x)
			+ (mainPlane.center.z - plane6.center.z)
					* (mainPlane.center.z - plane6.center.z)
			<= (mainPlane.left + plane6.left - 0.2)
					* (mainPlane.left + plane6.left - 0.2)) {
		cout << "collision detected" << endl;
		vector3D leftSide = normalise(crossProduct(up, mainPlane.headDir));
		vector3D rightSide = normalise(crossProduct(mainPlane.headDir, up));
		if (dotProduct(subtract(mainPlane.center, plane6.center),
				mainPlane.headDir) >= 0) {
			mainPlane.velocity = constProduct(mainPlane.velocity, 1.1);
			plane6.velocity = constProduct(plane6.velocity, 0.1);
			auto_rotation6=0.01;
		} else {
			mainPlane.velocity = constProduct(mainPlane.velocity, 0.1);
			plane6.velocity = constProduct(plane6.velocity, 1.05);
		}
	}
	if ((mainPlane.center.x - plane7.center.x)
			* (mainPlane.center.x - plane7.center.x)
			+ (mainPlane.center.z - plane7.center.z)
					* (mainPlane.center.z - plane7.center.z)
			<= (mainPlane.left + plane7.left - 0.2)
					* (mainPlane.left + plane7.left - 0.2)) {
		cout << "collision detected" << endl;
		vector3D leftSide = normalise(crossProduct(up, mainPlane.headDir));
		vector3D rightSide = normalise(crossProduct(mainPlane.headDir, up));
		if (dotProduct(subtract(mainPlane.center, plane7.center),
				mainPlane.headDir) >= 0) {
			mainPlane.velocity = constProduct(mainPlane.velocity, 1.1);
			plane7.velocity = constProduct(plane7.velocity, 0.1);
			auto_rotation7=0.01;
		} else {
			mainPlane.velocity = constProduct(mainPlane.velocity, 0.1);
			plane7.velocity = constProduct(plane7.velocity, 1.05);
		}
	}
	if ((mainPlane.center.x - plane8.center.x)
			* (mainPlane.center.x - plane8.center.x)
			+ (mainPlane.center.z - plane8.center.z)
					* (mainPlane.center.z - plane8.center.z)
			<= (mainPlane.left + plane8.left )
					* (mainPlane.left + plane8.left )) {
		cout << "collision detected 8" << endl;
		vector3D leftSide = normalise(crossProduct(up, mainPlane.headDir));
		vector3D rightSide = normalise(crossProduct(mainPlane.headDir, up));
		if (dotProduct(subtract(mainPlane.center, plane8.center),
				mainPlane.headDir) >= 0) {
			mainPlane.velocity = constProduct(mainPlane.velocity, 1.1);
			plane8.velocity = constProduct(plane8.velocity, 0.1);
			auto_rotation8=0.01;
		} else {
			mainPlane.velocity = constProduct(mainPlane.velocity, 0.1);
			plane8.velocity = constProduct(plane8.velocity, 1.05);
		}
	}
}

void autoPlane2() {
	track t = track_states[plane2_track];
	if (track_states[plane2_track].id == "S") {
//		cout << "straight" << endl;
		vector3D road_dir = normalise(
				subtract(track_states[plane2_track].end1,
						track_states[plane2_track].start1));
		vector3D plane_dir1 = normalise(
				subtract(track_states[plane2_track].end1, plane2.center));
		if (dotProduct(road_dir, plane_dir1) >= 0) {
			if (rightRotation2 < -4 || rightRotation2 > 4) {
//						cout<<"yeahhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh"<<endl;
				rightRotation2 += 6;
				plane2.right = sideValue(abs(rightRotation2));
				plane2.left = sideValue(abs(rightRotation2));
			}
			if (leftRotation2 < -4 || leftRotation2 > 4) {
//								cout<<"wooooooooooooooooooooooooooooooooo"<<endl;
				leftRotation2 -= 4;
				plane2.right = sideValue(abs(leftRotation2));
				plane2.left = sideValue(abs(leftRotation2));
			}
//				rightRotation2=0.0;
			plane2.headDir = road_dir;
			float vel = magnitude(plane2.velocity);
			plane2.velocity = constProduct(plane2.headDir, vel);
			plane2.center = add(plane2.center, plane2.velocity);
		} else {
			cout << "incrementeddddddddddddddddddddddd" << endl;
			plane2_track = (plane2_track + 1) % track_states.size();
			if (plane2_track % track_states.size() == 0) {
				Lap_2++;
			}
		}
	} else {
//		cout << "circle" << endl;
		vector3D start_circle = normalise(
				subtract(track_states[plane2_track].start1,
						track_states[plane2_track].center));
		vector3D plane_vector = subtract(plane2.center, t.center);
		plane_vector.y = 0.0;
		if (angle(start_circle, plane_vector)
				> cos(track_states[plane2_track].angle + 0.001)) {
			if (track_states[plane2_track].angle > 0) {
				cout << "positive" << endl;
				if (leftRotation2 < -4 || leftRotation2 > 4) {
					cout << "wooooooooooooooooooooooooooooooooo" << endl;
					leftRotation2 -= 4;
					plane2.right = sideValue(abs(leftRotation2));
					plane2.left = sideValue(abs(leftRotation2));
				}
				vector3D newCenter = constProduct(
						rotateVectorRight(plane_vector, up, auto_rotation2),
						magnitude(plane_vector));
				plane2.center = add(t.center, newCenter);
				plane2.center.y = 1.2;

				if (rightRotation2 > -95) {
					rightRotation2 -= auto_rotation2;
					plane2.right = sideValue(abs(rightRotation2));
					plane2.left = sideValue(abs(rightRotation2));
				}

				rightRotationY2 -= auto_rotation2;
				plane2.headDir = rotateVectorRight(plane2.headDir, up,
						auto_rotation2);
				plane2.velocity = constProduct(
						rotateVectorRight(plane2.velocity, up, auto_rotation2),
						magnitude(plane2.velocity));

			} else {
				cout << "negitivee" << endl;
				if (rightRotation2 < -4 || rightRotation2 > 4) {
//						cout<<"yeahhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh"<<endl;
					rightRotation2 += 4;
					plane2.right = sideValue(abs(rightRotation2));
					plane2.left = sideValue(abs(rightRotation2));
				}
				vector3D newCenter = constProduct(
						rotateVectorLeft(plane_vector, up, auto_rotation2),
						magnitude(plane_vector));
				plane2.center = add(t.center, newCenter);
				plane2.center.y = 1.2;
				if (leftRotation2 < 95) {
					leftRotation2 += auto_rotation2;
					plane2.right = sideValue(abs(leftRotation2));
					plane2.left = sideValue(abs(leftRotation2));
				}

				leftRotationY2 += auto_rotation2;
				plane2.headDir = rotateVectorLeft(plane2.headDir, up,
						auto_rotation2);
				plane2.velocity = constProduct(
						rotateVectorLeft(plane2.velocity, up, auto_rotation2),
						magnitude(plane2.velocity));

			}

		} else {
			cout << "incrementeddddddddddddddddddddddd" << endl;

			plane2_track = (plane2_track + 1) % track_states.size();
			if (plane2_track % track_states.size() == 0) {
				Lap_2++;
			}
		}

	}
}

void autoPlane3() {
	track t = track_states[plane3_track];
	if (track_states[plane3_track].id == "S") {

		vector3D road_dir = normalise(
				subtract(track_states[plane3_track].end1,
						track_states[plane3_track].start1));
		vector3D plane_dir1 = normalise(
				subtract(track_states[plane3_track].end1, plane3.center));
		if (dotProduct(road_dir, plane_dir1) >= 0) {
			if (rightRotation3 < -4 || rightRotation3 > 4) {
//					cout<<"yeahhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh"<<endl;
				rightRotation3 += 4;
			}
			if (leftRotation3 < -4 || leftRotation3 > 4) {
//							cout<<"wooooooooooooooooooooooooooooooooo"<<endl;
				leftRotation3 -= 4;
			}
//				rightRotation3=0.0;
			plane3.headDir = road_dir;
			float vel = magnitude(plane3.velocity);
			plane3.velocity = constProduct(plane3.headDir, vel);
			plane3.center = add(plane3.center, plane3.velocity);
		} else {
//				cout<<"incrementeddddddddddddddddddddddd"<<endl;
			plane3_track = (plane3_track + 1) % track_states.size();
			if (plane3_track % track_states.size() == 0) {
				Lap_3++;
			}
		}
	} else {

		vector3D start_circle = normalise(
				subtract(track_states[plane3_track].start1,
						track_states[plane3_track].center));
		vector3D plane_vector = subtract(plane3.center, t.center);
		plane_vector.y = 0.0;
		if (angle(start_circle, plane_vector)
				> cos(track_states[plane3_track].angle + 0.001)) {
			if (track_states[plane3_track].angle > 0) {
				if (leftRotation3 < -4 || leftRotation3 > 4) {
//					cout<<"wooooooooooooooooooooooooooooooooo"<<endl;
					leftRotation3 -= 4;
				}
				vector3D newCenter = constProduct(
						rotateVectorRight(plane_vector, up, auto_rotation3),
						magnitude(plane_vector));
				plane3.center = add(t.center, newCenter);
				plane3.center.y = 1.2;

				if (rightRotation3 > -95) {
					rightRotation3 -= auto_rotation3;
					plane3.right = sideValue(abs(rightRotation3));
					plane3.left = sideValue(abs(rightRotation3));
				}

				rightRotationY3 -= auto_rotation3;
				plane3.headDir = rotateVectorRight(plane3.headDir, up,
						auto_rotation3);
				plane3.velocity = constProduct(
						rotateVectorRight(plane3.velocity, up, auto_rotation3),
						magnitude(plane3.velocity));

			} else {
				if (rightRotation3 < -4 || rightRotation3 > 4) {
//						cout<<"yeahhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh"<<endl;
					rightRotation3 += 4;
				}
				vector3D newCenter = constProduct(
						rotateVectorLeft(plane_vector, up, auto_rotation3),
						magnitude(plane_vector));
				plane3.center = add(t.center, newCenter);
				plane3.center.y = 1.2;
				if (leftRotation3 < 95) {
					leftRotation3 += auto_rotation3;
					plane2.right = sideValue(abs(leftRotation));
					plane2.left = sideValue(abs(leftRotation));
				}

				leftRotationY3 += auto_rotation3;
				plane3.headDir = rotateVectorLeft(plane3.headDir, up,
						auto_rotation3);
				plane3.velocity = constProduct(
						rotateVectorLeft(plane3.velocity, up, auto_rotation3),
						magnitude(plane3.velocity));

			}

		} else {
//			cout<<"incrementeddddddddddddddddddddddd"<<endl;
			plane3_track = (plane3_track + 1) % track_states.size();
			if (plane3_track % track_states.size() == 0) {
				Lap_3++;
			}
		}

	}
}

void autoPlane4() {
	track t = track_states[plane4_track];
	if (track_states[plane4_track].id == "S") {

		vector3D road_dir = normalise(
				subtract(track_states[plane4_track].end1,
						track_states[plane4_track].start1));
		vector3D plane_dir1 = normalise(
				subtract(track_states[plane4_track].end1, plane4.center));
		if (dotProduct(road_dir, plane_dir1) >= 0) {
			if (rightRotation4 < -4 || rightRotation4 > 4) {
//					cout<<"yeahhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh"<<endl;
				rightRotation4 += 4;
			}
			if (leftRotation4 < -4 || leftRotation4 > 4) {
//							cout<<"wooooooooooooooooooooooooooooooooo"<<endl;
				leftRotation4 -= 4;
			}
//				rightRotation4=0.0;
			plane4.headDir = road_dir;
			float vel = magnitude(plane4.velocity);
			plane4.velocity = constProduct(plane4.headDir, vel);
			plane4.center = add(plane4.center, plane4.velocity);
		} else {
//				cout<<"incrementeddddddddddddddddddddddd"<<endl;
			plane4_track = (plane4_track + 1) % track_states.size();
			if (plane4_track % track_states.size() == 0) {
				Lap_4++;
			}
		}
	} else {

		vector3D start_circle = normalise(
				subtract(track_states[plane4_track].start1,
						track_states[plane4_track].center));
		vector3D plane_vector = subtract(plane4.center, t.center);
		plane_vector.y = 0.0;
		if (angle(start_circle, plane_vector)
				> cos(track_states[plane4_track].angle + 0.001)) {
			if (track_states[plane4_track].angle > 0) {
				if (leftRotation4 < -4 || leftRotation4 > 4) {
//					cout<<"wooooooooooooooooooooooooooooooooo"<<endl;
					leftRotation4 -= 4;
				}
				vector3D newCenter = constProduct(
						rotateVectorRight(plane_vector, up, auto_rotation4),
						magnitude(plane_vector));
				plane4.center = add(t.center, newCenter);
				plane4.center.y = 1.2;

				if (rightRotation4 > -95) {
					rightRotation4 -= auto_rotation4;
					plane4.right = sideValue(abs(rightRotation4));
					plane4.left = sideValue(abs(rightRotation4));
				}

				rightRotationY4 -= auto_rotation4;
				plane4.headDir = rotateVectorRight(plane4.headDir, up,
						auto_rotation4);
				plane4.velocity = constProduct(
						rotateVectorRight(plane4.velocity, up, auto_rotation4),
						magnitude(plane4.velocity));

			} else {
				if (rightRotation4 < -4 || rightRotation4 > 4) {
//						cout<<"yeahhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh"<<endl;
					rightRotation4 += 4;
				}
				vector3D newCenter = constProduct(
						rotateVectorLeft(plane_vector, up, auto_rotation4),
						magnitude(plane_vector));
				plane4.center = add(t.center, newCenter);
				plane4.center.y = 1.2;
				if (leftRotation4 < 95) {
					leftRotation4 += auto_rotation4;
					plane2.right = sideValue(abs(leftRotation));
					plane2.left = sideValue(abs(leftRotation));
				}

				leftRotationY4 += auto_rotation4;
				plane4.headDir = rotateVectorLeft(plane4.headDir, up,
						auto_rotation4);
				plane4.velocity = constProduct(
						rotateVectorLeft(plane4.velocity, up, auto_rotation4),
						magnitude(plane4.velocity));

			}

		} else {
//			cout<<"incrementeddddddddddddddddddddddd"<<endl;
			plane4_track = (plane4_track + 1) % track_states.size();
			if (plane4_track % track_states.size() == 0) {
				Lap_4++;
			}
		}

	}
}

void autoPlane5() {
	track t = track_states[plane5_track];
	if (track_states[plane5_track].id == "S") {

		vector3D road_dir = normalise(
				subtract(track_states[plane5_track].end1,
						track_states[plane5_track].start1));
		vector3D plane_dir1 = normalise(
				subtract(track_states[plane5_track].end1, plane5.center));
		if (dotProduct(road_dir, plane_dir1) >= 0) {
			if (rightRotation5 < -4 || rightRotation5 > 4) {
//					cout<<"yeahhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh"<<endl;
				rightRotation5 += 4;
			}
			if (leftRotation5 < -4 || leftRotation5 > 4) {
//							cout<<"wooooooooooooooooooooooooooooooooo"<<endl;
				leftRotation5 -= 4;
			}
//				rightRotation5=0.0;
			plane5.headDir = road_dir;
			float vel = magnitude(plane5.velocity);
			plane5.velocity = constProduct(plane5.headDir, vel);
			plane5.center = add(plane5.center, plane5.velocity);
		} else {
//				cout<<"incrementeddddddddddddddddddddddd"<<endl;
			plane5_track = (plane5_track + 1) % track_states.size();
			if (plane5_track % track_states.size() == 0) {
				Lap_5++;
			}
		}
	} else {

		vector3D start_circle = normalise(
				subtract(track_states[plane5_track].start1,
						track_states[plane5_track].center));
		vector3D plane_vector = subtract(plane5.center, t.center);
		plane_vector.y = 0.0;
		if (angle(start_circle, plane_vector)
				> cos(track_states[plane5_track].angle + 0.001)) {
			if (track_states[plane5_track].angle > 0) {
				if (leftRotation5 < -4 || leftRotation5 > 4) {
//					cout<<"wooooooooooooooooooooooooooooooooo"<<endl;
					leftRotation5 -= 4;
				}
				vector3D newCenter = constProduct(
						rotateVectorRight(plane_vector, up, auto_rotation5),
						magnitude(plane_vector));
				plane5.center = add(t.center, newCenter);
				plane5.center.y = 1.2;

				if (rightRotation5 > -95) {
					rightRotation5 -= auto_rotation5;
					plane5.right = sideValue(abs(rightRotation5));
					plane5.left = sideValue(abs(rightRotation5));
				}

				rightRotationY5 -= auto_rotation5;
				plane5.headDir = rotateVectorRight(plane5.headDir, up,
						auto_rotation5);
				plane5.velocity = constProduct(
						rotateVectorRight(plane5.velocity, up, auto_rotation5),
						magnitude(plane5.velocity));

			} else {
				if (rightRotation5 < -4 || rightRotation5 > 4) {
//						cout<<"yeahhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh"<<endl;
					rightRotation5 += 4;
				}
				vector3D newCenter = constProduct(
						rotateVectorLeft(plane_vector, up, auto_rotation5),
						magnitude(plane_vector));
				plane5.center = add(t.center, newCenter);
				plane5.center.y = 1.2;
				if (leftRotation5 < 95) {
					leftRotation5 += auto_rotation5;
					plane2.right = sideValue(abs(leftRotation));
					plane2.left = sideValue(abs(leftRotation));
				}

				leftRotationY5 += auto_rotation5;
				plane5.headDir = rotateVectorLeft(plane5.headDir, up,
						auto_rotation5);
				plane5.velocity = constProduct(
						rotateVectorLeft(plane5.velocity, up, auto_rotation5),
						magnitude(plane5.velocity));

			}

		} else {
//			cout<<"incrementeddddddddddddddddddddddd"<<endl;
			plane5_track = (plane5_track + 1) % track_states.size();
			if (plane5_track % track_states.size() == 0) {
				Lap_5++;
			}
		}

	}
}

void autoPlane6() {
	track t = track_states[plane6_track];
	if (track_states[plane6_track].id == "S") {

		vector3D road_dir = normalise(
				subtract(track_states[plane6_track].end1,
						track_states[plane6_track].start1));
		vector3D plane_dir1 = normalise(
				subtract(track_states[plane6_track].end1, plane6.center));
		if (dotProduct(road_dir, plane_dir1) >= 0) {
			if (rightRotation6 < -4 || rightRotation6 > 4) {
//					cout<<"yeahhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh"<<endl;
				rightRotation6 += 4;
			}
			if (leftRotation6 < -4 || leftRotation6 > 4) {
//							cout<<"wooooooooooooooooooooooooooooooooo"<<endl;
				leftRotation6 -= 4;
			}
//				rightRotation6=0.0;
			plane6.headDir = road_dir;
			float vel = magnitude(plane6.velocity);
			plane6.velocity = constProduct(plane6.headDir, vel);
			plane6.center = add(plane6.center, plane6.velocity);
		} else {
//				cout<<"incrementeddddddddddddddddddddddd"<<endl;
			plane6_track = (plane6_track + 1) % track_states.size();
			if (plane6_track % track_states.size() == 0) {
				Lap_6++;
			}
		}
	} else {

		vector3D start_circle = normalise(
				subtract(track_states[plane6_track].start1,
						track_states[plane6_track].center));
		vector3D plane_vector = subtract(plane6.center, t.center);
		plane_vector.y = 0.0;
		if (angle(start_circle, plane_vector)
				> cos(track_states[plane6_track].angle + 0.001)) {
			if (track_states[plane6_track].angle > 0) {
				if (leftRotation6 < -4 || leftRotation6 > 4) {
//					cout<<"wooooooooooooooooooooooooooooooooo"<<endl;
					leftRotation6 -= 4;
				}
				vector3D newCenter = constProduct(
						rotateVectorRight(plane_vector, up, auto_rotation6),
						magnitude(plane_vector));
				plane6.center = add(t.center, newCenter);
				plane6.center.y = 1.2;

				if (rightRotation6 > -95) {
					rightRotation6 -= auto_rotation6;
					plane6.right = sideValue(abs(rightRotation6));
					plane6.left = sideValue(abs(rightRotation6));
				}

				rightRotationY6 -= auto_rotation6;
				plane6.headDir = rotateVectorRight(plane6.headDir, up,
						auto_rotation6);
				plane6.velocity = constProduct(
						rotateVectorRight(plane6.velocity, up, auto_rotation6),
						magnitude(plane6.velocity));

			} else {
				if (rightRotation6 < -4 || rightRotation6 > 4) {
//						cout<<"yeahhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh"<<endl;
					rightRotation6 += 4;
				}
				vector3D newCenter = constProduct(
						rotateVectorLeft(plane_vector, up, auto_rotation6),
						magnitude(plane_vector));
				plane6.center = add(t.center, newCenter);
				plane6.center.y = 1.2;
				if (leftRotation6 < 95) {
					leftRotation6 += auto_rotation6;
					plane2.right = sideValue(abs(leftRotation));
					plane2.left = sideValue(abs(leftRotation));
				}

				leftRotationY6 += auto_rotation6;
				plane6.headDir = rotateVectorLeft(plane6.headDir, up,
						auto_rotation6);
				plane6.velocity = constProduct(
						rotateVectorLeft(plane6.velocity, up, auto_rotation6),
						magnitude(plane6.velocity));

			}

		} else {
//			cout<<"incrementeddddddddddddddddddddddd"<<endl;
			plane6_track = (plane6_track + 1) % track_states.size();
			if (plane6_track % track_states.size() == 0) {
				Lap_6++;
			}
		}

	}
}

void autoPlane7() {
	track t = track_states[plane7_track];
	if (track_states[plane7_track].id == "S") {

		vector3D road_dir = normalise(
				subtract(track_states[plane7_track].end1,
						track_states[plane7_track].start1));
		vector3D plane_dir1 = normalise(
				subtract(track_states[plane7_track].end1, plane7.center));
		if (dotProduct(road_dir, plane_dir1) >= 0) {
			if (rightRotation7 < -4 || rightRotation7 > 4) {
//					cout<<"yeahhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh"<<endl;
				rightRotation7 += 4;
			}
			if (leftRotation7 < -4 || leftRotation7 > 4) {
//							cout<<"wooooooooooooooooooooooooooooooooo"<<endl;
				leftRotation7 -= 4;
			}
//				rightRotation7=0.0;
			plane7.headDir = road_dir;
			float vel = magnitude(plane7.velocity);
			plane7.velocity = constProduct(plane7.headDir, vel);
			plane7.center = add(plane7.center, plane7.velocity);
		} else {
//				cout<<"incrementeddddddddddddddddddddddd"<<endl;
			plane7_track = (plane7_track + 1) % track_states.size();
			if (plane7_track % track_states.size() == 0) {
				Lap_7++;
			}
		}
	} else {

		vector3D start_circle = normalise(
				subtract(track_states[plane7_track].start1,
						track_states[plane7_track].center));
		vector3D plane_vector = subtract(plane7.center, t.center);
		plane_vector.y = 0.0;
		if (angle(start_circle, plane_vector)
				> cos(track_states[plane7_track].angle + 0.001)) {
			if (track_states[plane7_track].angle > 0) {
				if (leftRotation7 < -4 || leftRotation7 > 4) {
//					cout<<"wooooooooooooooooooooooooooooooooo"<<endl;
					leftRotation7 -= 4;
				}
				vector3D newCenter = constProduct(
						rotateVectorRight(plane_vector, up, auto_rotation7),
						magnitude(plane_vector));
				plane7.center = add(t.center, newCenter);
				plane7.center.y = 1.2;

				if (rightRotation7 > -95) {
					rightRotation7 -= auto_rotation7;
					plane7.right = sideValue(abs(rightRotation7));
					plane7.left = sideValue(abs(rightRotation7));
				}

				rightRotationY7 -= auto_rotation7;
				plane7.headDir = rotateVectorRight(plane7.headDir, up,
						auto_rotation7);
				plane7.velocity = constProduct(
						rotateVectorRight(plane7.velocity, up, auto_rotation7),
						magnitude(plane7.velocity));

			} else {
				if (rightRotation7 < -4 || rightRotation7 > 4) {
//						cout<<"yeahhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh"<<endl;
					rightRotation7 += 4;
				}
				vector3D newCenter = constProduct(
						rotateVectorLeft(plane_vector, up, auto_rotation7),
						magnitude(plane_vector));
				plane7.center = add(t.center, newCenter);
				plane7.center.y = 1.2;
				if (leftRotation7 < 95) {
					leftRotation7 += auto_rotation7;
					plane2.right = sideValue(abs(leftRotation));
					plane2.left = sideValue(abs(leftRotation));
				}

				leftRotationY7 += auto_rotation7;
				plane7.headDir = rotateVectorLeft(plane7.headDir, up,
						auto_rotation7);
				plane7.velocity = constProduct(
						rotateVectorLeft(plane7.velocity, up, auto_rotation7),
						magnitude(plane7.velocity));

			}

		} else {
//			cout<<"incrementeddddddddddddddddddddddd"<<endl;
			plane7_track = (plane7_track + 1) % track_states.size();
			if (plane7_track % track_states.size() == 0) {
				Lap_7++;
			}
		}

	}
}

void autoPlane8() {
	track t = track_states[plane8_track];
	if (track_states[plane8_track].id == "S") {

		vector3D road_dir = normalise(
				subtract(track_states[plane8_track].end1,
						track_states[plane8_track].start1));
		vector3D plane_dir1 = normalise(
				subtract(track_states[plane8_track].end1, plane8.center));
		if (dotProduct(road_dir, plane_dir1) >= 0) {
			if (rightRotation8 < -4 || rightRotation8 > 4) {
//					cout<<"yeahhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh"<<endl;
				rightRotation8 += 4;
			}
			if (leftRotation8 < -4 || leftRotation8 > 4) {
//							cout<<"wooooooooooooooooooooooooooooooooo"<<endl;
				leftRotation8 -= 4;
			}
//				rightRotation8=0.0;
			plane8.headDir = road_dir;
			float vel = magnitude(plane8.velocity);
			plane8.velocity = constProduct(plane8.headDir, vel);
			plane8.center = add(plane8.center, plane8.velocity);
		} else {
//				cout<<"incrementeddddddddddddddddddddddd"<<endl;
			plane8_track = (plane8_track + 1) % track_states.size();
			if (plane8_track % track_states.size() == 0) {
				Lap_8++;
			}
		}
	} else {

		vector3D start_circle = normalise(
				subtract(track_states[plane8_track].start1,
						track_states[plane8_track].center));
		vector3D plane_vector = subtract(plane8.center, t.center);
		plane_vector.y = 0.0;
		if (angle(start_circle, plane_vector)
				> cos(track_states[plane8_track].angle + 0.001)) {
			if (track_states[plane8_track].angle > 0) {
				if (leftRotation8 < -4 || leftRotation8 > 4) {
//					cout<<"wooooooooooooooooooooooooooooooooo"<<endl;
					leftRotation8 -= 4;
				}
				vector3D newCenter = constProduct(
						rotateVectorRight(plane_vector, up, auto_rotation8),
						magnitude(plane_vector));
				plane8.center = add(t.center, newCenter);
				plane8.center.y = 1.2;

				if (rightRotation8 > -95) {
					rightRotation8 -= auto_rotation8;
					plane8.right = sideValue(abs(rightRotation8));
					plane8.left = sideValue(abs(rightRotation8));
				}

				rightRotationY8 -= auto_rotation8;
				plane8.headDir = rotateVectorRight(plane8.headDir, up,
						auto_rotation8);
				plane8.velocity = constProduct(
						rotateVectorRight(plane8.velocity, up, auto_rotation8),
						magnitude(plane8.velocity));

			} else {
				if (rightRotation8 < -4 || rightRotation8 > 4) {
//						cout<<"yeahhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh"<<endl;
					rightRotation8 += 4;
				}
				vector3D newCenter = constProduct(
						rotateVectorLeft(plane_vector, up, auto_rotation8),
						magnitude(plane_vector));
				plane8.center = add(t.center, newCenter);
				plane8.center.y = 1.2;
				if (leftRotation8 < 95) {
					leftRotation8 += auto_rotation8;
					plane2.right = sideValue(abs(leftRotation));
					plane2.left = sideValue(abs(leftRotation));
				}

				leftRotationY8 += auto_rotation8;
				plane8.headDir = rotateVectorLeft(plane8.headDir, up,
						auto_rotation8);
				plane8.velocity = constProduct(
						rotateVectorLeft(plane8.velocity, up, auto_rotation8),
						magnitude(plane8.velocity));

			}

		} else {
//			cout<<"incrementeddddddddddddddddddddddd"<<endl;
			plane8_track = (plane8_track + 1) % track_states.size();
			if (plane8_track % track_states.size() == 0) {
				Lap_8++;
			}
		}

	}
}

void update(int value) {
	if (Lap == 3) {
		GameOver = true;

	}
	if (GameOver) {
		if(!store_position){
			print_pos = plane_position;
			store_position=true;
		}

		if (magnitude(mainPlane.velocity) > 0.010) {
			mainPlane.velocity = constProduct(mainPlane.velocity, 0.95);

		}

	}
	position();
//cout<<"center"<<endl;
//	printVector(mainPlane.center);
//	cout << "velocity: " << magnitude(plane2.velocity) << endl;
//	cout << "velocity Main: " << magnitude(mainPlane.velocity) << endl;
//		printVector(plane2.velocity);
//		cout<<"head"<<endl;
//		printVector(mainPlane.headDir);
//		cout<<"up"<<endl;
//		printVector(mainPlane.upDir);
//	cout << "track: " << plane2_track <<" "<<auto_rotation2<< endl;
	tyre = (tyre + 1) % 2;

//	if(magnitude(mainPlane.velocity)<1.0){
//		mainPlane.velocity=constProduct(mainPlane.velocity,1.20);
//	}
	if (auto_rotation2 < auto_rotation) {
			auto_rotation2+=0.1;
		}
	if (auto_rotation3 < auto_rotation) {
				auto_rotation3+=0.1;
			}
	if (auto_rotation4 < auto_rotation) {
					auto_rotation4+=0.1;
				}
	if (auto_rotation5 < auto_rotation) {
					auto_rotation5+=0.1;
				}
	if (auto_rotation6 < auto_rotation) {
					auto_rotation6+=0.1;
				}
	if (auto_rotation7 < auto_rotation) {
					auto_rotation7+=0.1;
				}
	if (auto_rotation8 < auto_rotation) {
					auto_rotation8+=0.1;
				}

	if (magnitude(plane2.velocity) < 1.50) {
		plane2.velocity = constProduct(plane2.velocity, 1.20);
	}
	if (magnitude(plane3.velocity) < 2.55) {
		plane3.velocity = constProduct(plane3.velocity, 1.20);
	}
	if (magnitude(plane4.velocity) < 2.4) {
		plane4.velocity = constProduct(plane4.velocity, 1.20);
	}
	if (magnitude(plane5.velocity) < 2.5) {
		plane5.velocity = constProduct(plane5.velocity, 1.20);
	}
	if (magnitude(plane6.velocity) < 1.9) {
		plane6.velocity = constProduct(plane6.velocity, 1.20);
	}
	if (magnitude(plane7.velocity) < 2.1) {
		plane7.velocity = constProduct(plane7.velocity, 1.20);
	}
	if (magnitude(plane8.velocity) < 2.2) {
		plane8.velocity = constProduct(plane8.velocity, 1.20);
	}

//	if(rightKey){
//		if(rightRotation>-95){
//			rightRotation-=rotation;
////			mainPlane.upDir=rotateVectorLeft(mainPlane.upDir,mainPlane.headDir,rotation);
//		}
//
//
//		rightRotationY-=rotation;
//		mainPlane.headDir=rotateVectorRight(mainPlane.headDir,up,rotation);
//		mainPlane.velocity=constProduct(rotateVectorRight(mainPlane.velocity,up,rotation),magnitude(mainPlane.velocity));
//
//	}
//
//	else{
//		if(rightRotation<-rotation*4 || rightRotation>rotation*4){
//			rightRotation+=rotation*4;
////			mainPlane.upDir=rotateVectorRight(mainPlane.upDir,mainPlane.headDir,rotation*4);
//		}
//	}
//	if(leftKey){
//			if(leftRotation<95){
//				leftRotation+=rotation;
////				mainPlane.upDir=rotateVectorRight(mainPlane.upDir,mainPlane.headDir,rotation);
//			}
//
//			leftRotationY+=rotation;
//			mainPlane.headDir=rotateVectorLeft(mainPlane.headDir,up,rotation);
//			mainPlane.velocity=constProduct(rotateVectorLeft(mainPlane.velocity,up,rotation),magnitude(mainPlane.velocity));
//
//		}
//		else{
//			if(leftRotation<-rotation*4 || leftRotation>rotation*4){
//				leftRotation-=rotation*4;
////				mainPlane.upDir=rotateVectorLeft(mainPlane.upDir,mainPlane.headDir,rotation*4);
//			}
//		}
	if (rightKey) {
		if (rightRotation > -95) {
			rightRotation -= rotation;
			mainPlane.right = sideValue(abs(rightRotation));
			mainPlane.left = sideValue(abs(rightRotation));
//				mainPlane.upDir=rotateVectorLeft(mainPlane.upDir,mainPlane.headDir,rotation);
		}

		rightRotationY -= rotation;
		mainPlane.headDir = rotateVectorRight(mainPlane.headDir, up, rotation);
		mainPlane.velocity = constProduct(
				rotateVectorRight(mainPlane.velocity, up, rotation),
				magnitude(mainPlane.velocity));

	}

	else {
		if (rightRotation < -rotation * 4 || rightRotation > rotation * 4) {
			rightRotation += rotation * 4;
			mainPlane.right = sideValue(abs(rightRotation));
			mainPlane.left = sideValue(abs(rightRotation));
			//			mainPlane.upDir=rotateVectorRight(mainPlane.upDir,mainPlane.headDir,rotation*4);
		}
	}
	if (leftKey) {
		if (leftRotation < 95) {
			leftRotation += rotation;
			mainPlane.right = sideValue(abs(leftRotation));
			mainPlane.left = sideValue(abs(leftRotation));
//					mainPlane.upDir=rotateVectorRight(mainPlane.upDir,mainPlane.headDir,rotation);
		}

		leftRotationY += rotation;
		mainPlane.headDir = rotateVectorLeft(mainPlane.headDir, up, rotation);
		mainPlane.velocity = constProduct(
				rotateVectorLeft(mainPlane.velocity, up, rotation),
				magnitude(mainPlane.velocity));

	} else {
		if (leftRotation < -rotation * 4 || leftRotation > rotation * 4) {
			leftRotation -= rotation * 4;
			mainPlane.right = sideValue(abs(leftRotation));
			mainPlane.left = sideValue(abs(leftRotation));
			//				mainPlane.upDir=rotateVectorLeft(mainPlane.upDir,mainPlane.headDir,rotation*4);
		}
	}

//	printVector(mainPlane.velocity);
	mainPlane.center = add(mainPlane.center, mainPlane.velocity);
	if (fire == 1) {
		missile.center = add(missile.center, missile.velocity);
	}
	collision(track_states);
	autoPlane2();
	autoPlane3();
	autoPlane4();
	autoPlane5();
	autoPlane6();
	autoPlane7();
	autoPlane8();
	glutPostRedisplay();
	glutTimerFunc(1, update, 0);
}

//
//

int main(int argc, char** argv) {
	glutInit(&argc, argv);
//glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1366, 768);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(argv[0]);
//myModel = glmReadOBJ("F:/SemV/CSL781/CSL781_Project/Project/Gta-spano-2010 obj/Gta-spano-2010 obj.obj");
//myModel = glmReadOBJ("F:/SemV/CSL781/CSL781_Project/Project/skyfighter_obj/skyfighterobj.obj");
	myModel = glmReadOBJ("skyfighter obj.obj");
//myModel = glmReadOBJ("RetroRacer_obj/RetroRacerOrange.obj");
//myModel = glmReadOBJ("space.obj");
	fence = glmReadOBJ("fence_01_obj.obj");
	tree = glmReadOBJ("lowpolytree5.obj");
	tree_1 = glmReadOBJ("Large steel arch bridge.obj");
	missile_obj = glmReadOBJ("missile.obj");
	tunnel = glmReadOBJ("tower bridge.obj");
	vector3D centerMain(0.0, 1.2, -150.00);
	vector3D head(1.0, 0.0, 0.0);
	vector3D up(0.0, 1.0, 0.0);
	vector3D vel(00.1000, 0.0, 0.0);
	mainPlane.center = centerMain;
	mainPlane.velocity = vel;
	mainPlane.headDir = head;
	mainPlane.upDir = up;
	mainPlane.left = 1.6;
	mainPlane.right = 1.6;
/////Plane-2//////////////////////
	vector3D center2(5.0, 1.2, -165.0);
	vector3D head2(1.0, 0.0, 0.0);
	vector3D up2(0.0, 1.0, 0.0);
	vector3D vel2(00.10, 0.0, 0.0);
	plane2.center = center2;
	plane2.velocity = vel2;
	plane2.headDir = head2;
	plane2.upDir = up2;
	plane2.left = 1.6;
	plane2.right = 1.6;

	vector3D center3(25.0, 1.2, -160.0);
	vector3D head3(1.0, 0.0, 0.0);
	vector3D up3(0.0, 1.0, 0.0);
	vector3D vel3(0.10, 0.0, 0.0);
	plane3.center = center3;
	plane3.velocity = vel3;
	plane3.headDir = head3;
	plane3.upDir = up3;
	plane3.left = 1.6;
	plane3.right = 1.6;

	vector3D center4(45.0, 1.2, -155.0);
	vector3D head4(1.0, 0.0, 0.0);
	vector3D up4(0.0, 1.0, 0.0);
	vector3D vel4(0.10, 0.0, 0.0);
	plane4.center = center4;
	plane4.velocity = vel4;
	plane4.headDir = head4;
	plane4.upDir = up4;
	plane4.left = 1.6;
	plane4.right = 1.6;

	vector3D center5(45.0, 1.2, -150.0);
	vector3D head5(1.0, 0.0, 0.0);
	vector3D up5(0.0, 1.0, 0.0);
	vector3D vel5(0.10, 0.0, 0.0);
	plane5.center = center5;
	plane5.velocity = vel5;
	plane5.headDir = head5;
	plane5.upDir = up5;
	plane5.left = 1.6;
	plane5.right = 1.6;

	vector3D center6(45.0, 1.2, -145.0);
	vector3D head6(1.0, 0.0, 0.0);
	vector3D up6(0.0, 1.0, 0.0);
	vector3D vel6(0.10, 0.0, 0.0);
	plane6.center = center6;
	plane6.velocity = vel6;
	plane6.headDir = head6;
	plane6.upDir = up6;
	plane6.left = 1.6;
	plane6.right = 1.6;

	vector3D center7(25.0, 1.2, -140.0);
	vector3D head7(1.0, 0.0, 0.0);
	vector3D up7(0.0, 1.0, 0.0);
	vector3D vel7(0.10, 0.0, 0.0);
	plane7.center = center7;
	plane7.velocity = vel7;
	plane7.headDir = head7;
	plane7.upDir = up7;
	plane7.left = 1.6;
	plane7.right = 1.6;

	vector3D center8(5.0, 1.2, -135.0);
	vector3D head8(1.0, 0.0, 0.0);
	vector3D up8(0.0, 1.0, 0.0);
	vector3D vel8(0.10, 0.0, 0.0);
	plane8.center = center8;
	plane8.velocity = vel8;
	plane8.headDir = head8;
	plane8.upDir = up8;
	plane8.left = 1.6;
	plane8.right = 1.6;

	track_2_fill_vec();
	initRendering();
	glutDisplayFunc(draw);
//_scale = computeScale(STRS);
	glutReshapeFunc(handleResize);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeys);
	glutSpecialUpFunc(keyup);
	glutTimerFunc(2, update, 0);
	glutMainLoop();
	return 0;
}

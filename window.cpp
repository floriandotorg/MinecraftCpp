#include "window.hpp"

#include <ctime>

#include <list>
#include <memory>
#include <functional>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "OpenGL.h"
#include "world.hpp"
#include "utility.hpp"

class window::impl
{
public:
    static impl& instance();

	impl();
	int run(int argc, char * argv[]);

	void idle();
	void display();
	void mouse_move(int x, int y);
	void key_pressed(unsigned char key, int x, int y);
	void key_up(unsigned char key, int x, int y);

private:
	static const int DESIRED_STATE_UPDATES_PER_SECOND = 50;
	static const int DESIRED_STATE_UPDATE_DURATION_MS = 1000 / DESIRED_STATE_UPDATES_PER_SECOND;

    void create_glut_window();
    glm::vec3 motion_vector();
    void update(double dt);
    void create_glut_callbacks();
    void init_opengl();

	double last_loop_time;
	double time_accumulated_ms;
	int win;
	glm::vec3 position;
	glm::vec2 rotation;
	int strafe[2];
	world world;
};

window::impl& window::impl::instance()
{
    static std::unique_ptr<impl> instance(new impl());
    return *instance;
}

int window::run(int argc, char * argv[])
{ return window::impl::instance().run(argc, argv); }

//////

#if _MSC_VER
#pragma warning(disable: 4351)
#endif

window::impl::impl()
	: position(0, 1, 0)
	, rotation(0, 120)
	, strafe()
	, win(0)
	, last_loop_time(0)
	, time_accumulated_ms(0)
{ }

#if _MSC_VER
#pragma warning(default: 4351)
#endif

int window::impl::run(int argc, char * argv[])
{
	glutInit(&argc, argv);

	create_glut_window();
	create_glut_callbacks();
	init_opengl();

    world.init();

	glutMainLoop();

	return 0;
}

void window::impl::create_glut_window()
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(10, 10);
	glutInitWindowSize(1400, 800);
	win = glutCreateWindow("");
}

glm::vec3 window::impl::motion_vector()
{
	GLfloat dx = 0, dy = 0, dz = 0;

	if (strafe[0] || strafe[1])
	{
		const GLfloat s = degrees(std::atan2(strafe[0], strafe[1]));
		const GLfloat y_angle = radians(rotation.y);
		const GLfloat x_angle = radians(rotation.x + s);

		//flying
		if (true)
		{
			GLfloat m = std::cos(y_angle);
			dy = std::sin(y_angle);

			if (strafe[1])
			{
				dy = 0.0;
				m = 1;
			}

			if (strafe[0] > 0)
			{
				dy *= -1;
			}

			dx = std::cos(x_angle) * m;
			dz = std::sin(x_angle) * m;
		}
		else
		{
			dy = 0.0;
			dx = std::cos(x_angle);
			dz = std::sin(x_angle);
		}
	}

	return glm::vec3(dx, dy, dz);
}

void window::impl::update(double dt)
{
	const GLfloat speed = 15;
	const GLfloat d = dt * speed;
	const glm::vec3 motion = motion_vector();
	position.x += motion.x * d;
	position.y += motion.y * d;
	position.z += motion.z * d;

    world.update(dt);
}

void window::impl::idle()
{
	const double now = glutGet(GLUT_ELAPSED_TIME);
	const double timeElapsedMs = ((now - last_loop_time) * 1000) / (CLOCKS_PER_SEC);
	time_accumulated_ms += timeElapsedMs;

	while (time_accumulated_ms >= DESIRED_STATE_UPDATE_DURATION_MS) {
		update(DESIRED_STATE_UPDATE_DURATION_MS / 1000.0);

		time_accumulated_ms -= DESIRED_STATE_UPDATE_DURATION_MS;

		glutPostRedisplay();
	}

	last_loop_time = now;

	glutPostRedisplay();
}

void window::impl::display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLfloat width = glutGet(GLUT_WINDOW_WIDTH), height = glutGet(GLUT_WINDOW_HEIGHT);

	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, width / float(height), 0.1, 60.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glRotatef(rotation.x, 0, 1, 0);
	glRotatef(-rotation.y, std::cos(radians(rotation.x)), 0, std::sin(radians(rotation.x)));

	glTranslatef(-position.x, -position.y, -position.z);

    world.draw();

	glFlush();
	glutSwapBuffers();
}

void window::impl::mouse_move(int x, int y)
{
	//x = x - (glutGet(GLUT_WINDOW_WIDTH) / 2);
	//y = y - (glutGet(GLUT_WINDOW_HEIGHT) / 2);

	//rotation.x = fmod(x + 3600, 360.0f);
	//rotation.y = fmod(y + 3600, 360.0f);

	//glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);

	//std::cout << c_xrot << " " << c_yrot << std::endl;

	static int lx = 0;
	static int ly = 0;

	GLfloat m = 0.25;
	rotation.x = rotation.x + (x - lx) * m;
	rotation.y = rotation.y + -(y - ly) * m;
	rotation.y = max(-90, min(90, rotation.y));

	lx = x;
	ly = y;
}

void window::impl::key_pressed(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		strafe[0] = -1;
		break;
	case 's':
		strafe[0] = 1;
		break;
	case 'a':
		strafe[1] = -1;
		break;
	case 'd':
		strafe[1] = 1;
		break;
	}
}

void window::impl::key_up(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		strafe[0] = 0;
		break;
	case 's':
		strafe[0] = 0;
		break;
	case 'a':
		strafe[1] = 0;
		break;
	case 'd':
		strafe[1] = 0;
		break;
	}
}

void idle()
{ window::impl::instance().idle(); }

void display()
{ window::impl::instance().display(); }

void mouse_move(int x, int y)
{ window::impl::instance().mouse_move(x, y); }

void key_pressed(unsigned char key, int x, int y)
{ window::impl::instance().key_pressed(key, x, y); }

void key_up(unsigned char key, int x, int y)
{ window::impl::instance().key_up(key, x, y); }

void window::impl::create_glut_callbacks()
{
	glutDisplayFunc(::display);
	glutIdleFunc(::idle);
	glutPassiveMotionFunc(::mouse_move);
	glutKeyboardFunc(::key_pressed);
	glutKeyboardUpFunc(::key_up);
}

//void setupFog()
//{
//	glEnable(GL_FOG);
//	// Set the fog color.
//	const GLfloat a[] = { 0.5, 0.69, 1.0, 1 };
//	glFogfv(GL_FOG_COLOR, a);
//	// Say we have no preference between rendering speed and quality.
//	glHint(GL_FOG_HINT, GL_DONT_CARE);
//	// Specify the equation used to compute the blending factor.
//	glFogi(GL_FOG_MODE, GL_LINEAR);
//	// How close and far away fog starts and ends. The closer the start and end,
//	// the denser the fog in the fog range.
//	glFogf(GL_FOG_START, 20.0);
//	glFogf(GL_FOG_END, 60.0);
//}

void window::impl::init_opengl()
{
	//    glMatrixMode(GL_PROJECTION);
	//    glLoadIdentity();
	//    gluPerspective(90.0, 1.0, 0.1, 100);
	//    glMatrixMode(GL_MODELVIEW);
	//    
	//    glEnable(GL_DEPTH_TEST);
	//    glEnable(GL_TEXTURE_2D);
	////    loadTextures();
	//    
	//    glEnable(GL_NORMALIZE);
	//    glShadeModel(GL_SMOOTH);
	//    glEnable(GL_LIGHTING);
	//    glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteLight);
	//    glLightfv(GL_LIGHT0, GL_SPECULAR, whiteLight);
	//    glEnable(GL_LIGHT0);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);

	//    glEnable(GL_CULL_FACE);
	//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glClearColor(0.5, 0.69, 1.0, 1);

	//    setupFog();
}

#include "GLRenderer.h"
#include "CommandCenter.h"

GLRenderer::GLRenderer(unsigned int width, unsigned int height, const char* title, int style)
	: window(sf::VideoMode(width, height), title, style)
{
	
}

GLRenderer::GLRenderer(unsigned int width, unsigned int height, const char* title, int style, sf::ContextSettings &settings)
	: window(sf::VideoMode(width, height), title, style, settings)
{

}

GLRenderer::~GLRenderer()
{

}

bool GLRenderer::Init()
{
	//Output OpenGL stats
    std::cout << "OPENGL: " << std::endl;
    std::cout << " VERSION: " << glGetString(GL_VERSION) << std::endl;
    std::cout << " VENDOR: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << " RENDERER: " << glGetString(GL_RENDERER) << std::endl << std::endl;
 
    //Check OpenGL Context Settings 
    sf::ContextSettings context = window.getSettings();
    std::cout << "OpenGL Context: " << std::endl;
    std::cout << " GL_Version: " << context.majorVersion << "." << context.minorVersion << std::endl;
    std::cout << " Depth Bits: " << context.depthBits << std::endl;
    std::cout << " Stencil Bits " << context.stencilBits << std::endl;
    std::cout << " Anti-aliasing: " << context.antialiasingLevel << std::endl << std::endl;

	glClearDepth(1.0f);
	glClearColor(0.0f, 0.5f, 0.5f, 1.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, 1.0f, 1.0f, 500.0f);

	return true;
}

void GLRenderer::Run()
{
	if(!Init())
	{
		std::cerr << "Unable to Initialize" << std::endl;
	}

	window.setActive();

	while(window.isOpen())
	{
		sf::Event sfEvent;
		while(window.pollEvent(sfEvent))
		{
			switch(sfEvent.type)
			{
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::Resized:
					glViewport(0, 0, sfEvent.size.width, sfEvent.size.height);
					break;

			}
		}
		
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Tilde))
		{
			/*std::cout << ">> ";
			std::string cmd;
			std::cin >> cmd;*/
			if(!Command("load asdasd"))
			{
				std::cout << "Invalid command" << std::endl;
			}
			if(!Command("setpos Suzanne 0 0 -20"))
			{
				std::cout << "Invalid command" << std::endl;
			}
		}
		
		sf::Time time = clock.restart();

		Update(time);
		Render(time);

		window.display();
	}
}

void GLRenderer::Render(sf::Time &time)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	for(int i = 0; i < objects.size(); i++)
	{
		glTranslatef(objects[i].position.x, objects[i].position.y, objects[i].position.z);
		glBegin(GL_TRIANGLES);
		{
			for(int j = 0; j < objects[i].verticies.size(); j++)
			{
				glVertex3f(objects[i].verticies[j].x, objects[i].verticies[j].y,
					objects[i].verticies[j].z);
			}
		}
		glEnd();
	}
}


void GLRenderer::Update(sf::Time &time)
{

}


bool GLRenderer::Command(std::string cmd)
{
	std::cout << cmd << std::endl;
	return CommandCenter::ProcessCommand(cmd, objects);
}

void GLRenderer::drawCube()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -200.0f);
	glRotatef(35, 1.0f, 0.0f, 0.0f);
	glRotatef(65, 0.0f, 1.0f, 0.0f);
	glRotatef(95, 0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-50.f, -50.f, -50.f);
		glVertex3f(-50.f,  50.f, -50.f);
		glVertex3f( 50.f,  50.f, -50.f);
		glVertex3f( 50.f, -50.f, -50.f);

		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-50.f, -50.f, 50.f);
		glVertex3f(-50.f,  50.f, 50.f);
		glVertex3f( 50.f,  50.f, 50.f);
		glVertex3f( 50.f, -50.f, 50.f);

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-50.f, -50.f, -50.f);
		glVertex3f(-50.f,  50.f, -50.f);
		glVertex3f(-50.f,  50.f,  50.f);
		glVertex3f(-50.f, -50.f,  50.f);

		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(50.f, -50.f, -50.f);
		glVertex3f(50.f,  50.f, -50.f);
		glVertex3f(50.f,  50.f,  50.f);
		glVertex3f(50.f, -50.f,  50.f);

		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-50.f, -50.f,  50.f);
		glVertex3f(-50.f, -50.f, -50.f);
		glVertex3f( 50.f, -50.f, -50.f);
		glVertex3f( 50.f, -50.f,  50.f);

		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-50.f, 50.f,  50.f);
		glVertex3f(-50.f, 50.f, -50.f);
		glVertex3f( 50.f, 50.f, -50.f);
		glVertex3f( 50.f, 50.f,  50.f);
	glEnd();
}
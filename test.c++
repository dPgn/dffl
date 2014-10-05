/*
	Distance Field Font Library test program
	
	Compiles on my box with
	g++ -std=c++11 -O3 `freetype-config --cflags` -otest test.c++ -lGLEW -lglfw -lGL `freetype-config --libs`
*/

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "dffl.h++"
DFFL_LUTS

int main()
{
	if (!glfwInit())
	{
		std::cerr << "glfwInit failed." << std::endl;
		return 1;
	} 

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	GLFWwindow* win = glfwCreateWindow(800, 600, "Distance Field Font Test", 0, 0);
	if (!win)
	{
		std::cerr << "glfwCreateWindow failed." << std::endl;
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(win);

	glewExperimental = GL_TRUE;
	glewInit();

	dffl::Context ctx;
	ctx.Viewport(800, 600);
	
	dffl::Font font(ctx);

//	font.Load("/usr/share/fonts/truetype/freefont/FreeSans.ttf");
//	font.Load("/usr/share/fonts/truetype/freefont/FreeSansBoldOblique.ttf");
	font.Load("/usr/share/fonts/truetype/droid/DroidSerif-Bold.ttf");
	font.Load("/usr/share/fonts/truetype/arphic-bkai00mp/bkai00mp.ttf"); // Chinese

	// Generate 100 glyphs to calculate average time of glyph generation.
	double t0 = glfwGetTime();
	font.Add("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZäöüÄÖÜ1234567890€@\"$%&/()=?[]{}^'*µ<>;:,._-°ß`~");
	double t1 = glfwGetTime();
	std::cout << "100 glyphs generated at " << (t1 - t0) * 10 << " ms / glyph." << std::endl;
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	while (!glfwWindowShouldClose(win))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		ctx.MoveTo(-390, 100);
		ctx.Size(10);
		ctx.Smooth(0.3f);
		ctx.FillColor(0.8, 1.0, 1.0, 1.0);
		font.Write("10px text");
		ctx.MoveTo(-390, 80);
		ctx.Size(20);
		ctx.Smooth(1.0f);
		ctx.FillColor(0.8, 0.5, 1.0, 1.0);
		font.Write("20px text");
		ctx.MoveTo(-390, 20);
		ctx.Size(60);
		ctx.FillColor(0.8, 1.0, 1.0, 0.7);
		font.Write("60px text");
		ctx.MoveTo(-390, -110);
		ctx.Size(130);
		ctx.FillColor(0.8, 0.2, 0.1, 0.7);
		ctx.OutlineColor(1.0, 1.0, 1.0, 1.0);
		ctx.OutlineWidth(2.0f);
		font.Write("130px text");
		ctx.MoveTo(-390, -290);
		ctx.Size(160);
		ctx.OutlineWidth(0);
		ctx.FillColor(1.0, 1.0, 0.7, 1.0);
		font.Write("麻辣味型");

		ctx.MoveTo(-390, 200);
		ctx.Size(25);
		ctx.FillColor(1.0f, 1.0f, 1.0f, 0.5f);
		font.Write("Hello, ");
		ctx.Size(35);
		ctx.FillColor(0.0f, 0.0f, 1.0f, 1.0f);
		font.Write("World!");
		ctx.Size(9);
		ctx.Smooth(0.7f);
		ctx.FillColor(1.0f, 1.0f, 1.0f, 1.0f); 
		ctx.Move(30, 0); 
		font.Write("Here comes the small print.");

		glfwPollEvents();
		glfwSwapBuffers(win);
	}
	
	glfwTerminate();
	return 0;
}

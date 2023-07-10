#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"
#include <iostream>
#include <vector>

using namespace std;

class Star
{
public:
	Star(const kiko::Vector2& pos, const kiko::Vector2& vel) : m_pos{ pos }, m_vel{ vel } {}
	void Update() { m_pos += m_vel; }
	void Draw(kiko::Renderer& renderer) { renderer.DrawPoint(m_pos.x, m_pos.y); }

public:
	kiko::Vector2 m_pos;
	kiko::Vector2 m_vel;
};

int main(int argc, char* argv[])

{
	kiko::seedRandom((unsigned int)time(nullptr));
	
	kiko::Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("CSC195", 800, 600);

	kiko::InputSystem inputSystem;
	inputSystem.Initialize();

	/*bool quit = false;
	while (!quit)
	{
		inputSystem.Update();
		if (inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}

	}*/

	

	vector<Star> stars;
	for (int i = 0; i < 1000; i++)
	{
		kiko::Vector2 pos(kiko::Vector2(kiko::random(renderer.GetWidth()), kiko::random(renderer.GetHeight())));
		kiko::Vector2 vel(kiko::randomf(1, 4), 0.0f);

		stars.push_back(Star(pos, vel));
	}

	while (true)
	{
		renderer.SetColor(0, 0, 0, 0);
		renderer.BeginFrame();
		// draw
		kiko::Vector2 vel(1.0f, 0.3f);

		for (auto& star : stars)
		{
			star.Update();

			if (star.m_pos.x > renderer.GetWidth()) 
			{
				star.m_pos.x = 0;
			}
			if (star.m_pos.y > renderer.GetHeight())
			{
				star.m_pos.y = 0;
			}

			
			renderer.SetColor(kiko::random(256), kiko::random(256), kiko::random(256), 255);
			renderer.DrawPoint(star.m_pos.x, star.m_pos.y);
		}

		/*for (int i = 0; i < 10000; i++)
		{
			//kiko::Vector2 pos(kiko::random(renderer.GetWidth()), kiko::random(renderer.GetHeight()));
			//renderer.SetColor(kiko::random(256), kiko::random(256), kiko::random(256), 255);
			//renderer.DrawPoint(kiko::random(pos.x, pos.y ));
			//renderer.DrawLine(kiko::random(renderer.GetWidth()), kiko::random(renderer.GetHeight()), kiko::random(renderer.GetWidth()), kiko::random(renderer.GetHeight()));
		}*/
		renderer.EndFrame();
	}

	/*kiko::g_memoryTracker.DisplayInfo();
	int* p = new int;
	kiko::g_memoryTracker.DisplayInfo();
	delete p;
	kiko::g_memoryTracker.DisplayInfo();

	kiko::Time timer;
	for (int i = 0; i < 1000000; i++) {}
	cout << timer.GetElapsedSeconds() << endl;*/



	/*auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < 1000000000; i++) {}
	auto end = std::chrono::high_resolution_clock::now();

	cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << endl;*/




	/*cout << kiko::getFilePath() << endl;
	kiko::setFilePath("../../../Build/Assets");
	cout << kiko::getFilePath() << endl;

	size_t size;
	kiko::getFileSize("game.txt", size);
	cout << size << endl;
	
	std::string s;
	kiko::readFile("game.txt", s);
	cout << s << endl;

	kiko::seedRandom((unsigned int)time(nullptr));
	for (int i = 0; i < 0; i++)
	{
		cout << kiko::random(5, 20) << endl;
	}*/

}

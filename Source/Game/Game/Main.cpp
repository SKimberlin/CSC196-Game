#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"
#include "Renderer/Model.h"
#include <iostream>
#include <vector>
#include <thread>

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


//m_pos += m_vel * kiko::g_time.GetDeltaTime();

int main(int argc, char* argv[])
{
	constexpr float a = kiko::DegreesToRadians(180);

	kiko::seedRandom((unsigned int)time(nullptr));
	kiko::setFilePath("assets");
	
	kiko::Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("CSC195", 800, 600);

	kiko::InputSystem inputSystem;
	inputSystem.Initialize();

	//std::vector<kiko::vec2> points{ {0,-100}, {100,0}, {0, 100}, {-100,0}, {0,-100} };
	kiko::Model model;
	model.Load("ship.txt");

	vector<Star> stars;
	for (int i = 0; i < 1000; i++)
	{
		kiko::Vector2 pos(kiko::Vector2(kiko::random(renderer.GetWidth()), kiko::random(renderer.GetHeight())));
		kiko::Vector2 vel(kiko::randomf(0.0f, 100.0f), kiko::randomf(0.0f, 100.0f));

		stars.push_back(Star(pos, vel));

	}

	kiko::Transform transform{ {400, 300 }, 0, 3 };

	kiko::vec2 position{ 400, 300 };
	float speed = 200;
	float turnSpeed = kiko::DegreesToRadians(180);

	//main game loop
	bool quit = false;
	while (!quit)
	{
		kiko::g_time.Tick();

		inputSystem.Update();
		if (inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}
		if (inputSystem.GetMouseButtonDown(0)) 
		{
			cout << "\nLeft Mouse Button Pressed!" << endl;
			
			cout << "\nMouse X position: " << inputSystem.GetMousePosition().x << "\nMouse Y position: " << inputSystem.GetMousePosition().y << endl;
		}
		float rotate = 0;
		if (inputSystem.GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
		if (inputSystem.GetKeyDown(SDL_SCANCODE_D)) rotate = 1;
		transform.rotation += rotate * turnSpeed * kiko::g_time.GetDeltaTime();

		float thrust = 0;
		if (inputSystem.GetKeyDown(SDL_SCANCODE_W)) thrust = 1;

		kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(transform.rotation);
		transform.position += forward * speed * thrust * kiko::g_time.GetDeltaTime();
		transform.position.x = kiko::Wrap(transform.position.x, renderer.GetWidth());
		transform.position.y = kiko::Wrap(transform.position.y, renderer.GetHeight());

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
			if (star.m_pos.x < 0)
			{
				star.m_pos.x = renderer.GetWidth();
			}
			if (star.m_pos.y < 0)
			{
				star.m_pos.y = renderer.GetHeight();
			}

			
			renderer.SetColor(kiko::random(256), kiko::random(256), kiko::random(256), 255);
			renderer.DrawPoint(star.m_pos.x, star.m_pos.y);
		}

		model.Draw(renderer, transform.position, transform.rotation, transform.scale );

		renderer.EndFrame();

	}

	return 0;
}

#include "SpaceGame.h"
#include "Player.h"
#include "Enemy.h"

#include "Framework/Scene.h"

#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/Text.h"
#include "Renderer/ModelManager.h"

bool SpaceGame::Initialize()
{
    // load font
    m_font = std::make_shared<kiko::Font>("Starlight.ttf", 50);
    m_scoreText = std::make_unique<kiko::Text>(m_font);
    m_scoreText->Create(kiko::g_renderer, "SCORE 0000", kiko::Color{ 1, 0, 1, 1 });

    m_titleText = std::make_unique<kiko::Text>(m_font);
    m_titleText->Create(kiko::g_renderer, "EMU", kiko::Color{ 1, 1, 1, 1 });

    // load audio
    kiko::g_audioSystem.AddAudio("Laser_Shoot", "Laser_Shoot.wav");

    m_scene = std::make_unique<kiko::Scene>();

    

    //for (size_t i = 0; i < 1; i++)
    //{
    //    std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(speed - kiko::randomf(30.0f, 100.0f), turnSpeed, kiko::Transform{ { kiko::random(kiko::g_renderer.GetWidth()), kiko::random(kiko::g_renderer.GetHeight()) }, kiko::randomf(kiko::TwoPi), 2 }, kiko::g_manager.Get("ship.txt"));
    //    enemy->m_tag = "Enemy";
    //    m_scene->Add(std::move(enemy));
    //}

	return true;
}

void SpaceGame::Shutdown()
{
}

void SpaceGame::Update(float dt)
{
	switch (m_state)
    {
	    case SpaceGame::Title:
            if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE))
            {
                m_state = eState::StartGame;
            }
            break;
        case SpaceGame::StartGame:
            m_score = 0;
            m_lives = 3;
            m_state = eState::StartLevel;
            break;
        case SpaceGame::StartLevel:
            m_scene->RemoveAll();
        {
            std::unique_ptr<Player> player = std::make_unique<Player>(200.0f, kiko::DegreesToRadians(180), kiko::Transform{ {400, 300 }, 0, 3 }, kiko::g_manager.Get("ship.txt"));
            player->m_tag = "Player";
            player->m_game = this;
            m_scene->Add(std::move(player));
        }
            m_state = eState::Game;
            break;
        case SpaceGame::Game:
        {
            m_spawnTimer += dt;
            if (m_spawnTimer >= m_spawnTime)
            {
                std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(kiko::randomf(150.0f, 100.0f), kiko::DegreesToRadians(180), kiko::Transform{ { kiko::random(kiko::g_renderer.GetWidth()), kiko::random(kiko::g_renderer.GetHeight()) }, kiko::randomf(kiko::TwoPi), 2 }, kiko::g_manager.Get("ship.txt"));
                enemy->m_tag = "Enemy";
                enemy->m_game = this;
                m_scene->Add(std::move(enemy));
                m_spawnTimer = 0;
            }
            break;
        }
        case SpaceGame::PlayerDead:
            if (m_lives == 0) m_state = eState::GameOver;
            else m_state = eState::StartLevel;
            break;
        case SpaceGame::GameOver:
            break;
        default:
            break;
    }

    m_scoreText->Create(kiko::g_renderer, "Score " + std::to_string(m_score), {1, 0, 1, 1});
    m_scene->Update(dt);
}

void SpaceGame::Draw(kiko::Renderer& renderer)
{
    if (m_state == eState::Title)
    {
        m_titleText->Draw(renderer, 400, 300);
    }
    m_scoreText->Draw(renderer, 40, 20);
    m_scene->Draw(renderer);
}

#include "Enemy.h"
#include "Player.h"
#include "Weapon.h"
#include "SpaceGame.h"
#include "Framework/Scene.h"
#include "Renderer/Renderer.h"

void Enemy::Update(float dt)
{
	Actor::Update(dt);

	Player* player = m_scene->GetActor<Player>();
	if (player) 
	{
		kiko::vec2 direction = player->m_transform.position - m_transform.position;
		m_transform.rotation = direction.Angle() + kiko::HalfPi;
	}


	kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(m_transform.rotation);
	m_transform.position += forward * m_speed * kiko::g_time.GetDeltaTime();
	m_transform.position.x = kiko::Wrap(m_transform.position.x, (float)kiko::g_renderer.GetWidth());
	m_transform.position.y = kiko::Wrap(m_transform.position.y, (float)kiko::g_renderer.GetHeight());

	m_fireTimer -= dt;
	if (m_fireTimer <= 0)
	{
		kiko::Transform transform{ m_transform.position, m_transform.rotation, 0.5f };
		std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(400.0f, transform, m_model);
		weapon->m_tag = "EnemyBullet";
		m_scene->Add(std::move(weapon));
		m_fireTimer = m_fireTime;
	}
}

void Enemy::OnCollision(Actor* other)
{
	if (other->m_tag == "PlayerBullet")
	{
		m_game->AddPoints(100);
		m_destroyed = true;
	}
}

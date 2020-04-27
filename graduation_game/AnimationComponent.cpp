#include "stdafx.h"
#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet)
	:sprite(sprite), textureSheet(texture_sheet), lastAnimation(NULL), priorityAnimation(NULL)
{

}

AnimationComponent::~AnimationComponent()
{
	for (auto &i : this->animations)
	{
		delete i.second;
	}
}

// Accessor
const bool & AnimationComponent::isDone(const std::string key)
{
	return this->animations[key]->isDone();
}

// Function
void AnimationComponent::addAnimation(const std::string key,
	float animation_timer, int start_frame_x, int start_frame_y,
	int frames_x, int frames_y, int width, int height)
{
	this->animations[key] = new Animation(
		this->sprite, this->textureSheet,
		animation_timer, start_frame_x, start_frame_y,
		frames_x, frames_y, width, height);
}

const bool& AnimationComponent::play(const std::string key, const float & dt, const bool priority)
{
	if (this->priorityAnimation) // 우선순위 애니메이션이 있으면
	{
		if (this->priorityAnimation == this->animations[key])
		{
			if (this->lastAnimation != this->animations[key])
			{
				if (this->lastAnimation == NULL)
					this->lastAnimation = this->animations[key];
				else
				{
					this->lastAnimation->reset();
					this->lastAnimation = this->animations[key];
				}
			}

			// 우선순위 애니메이션이 끝나면 제거
			if (this->animations[key]->play(dt))
			{
				this->priorityAnimation = NULL;
			}
		}
	}
	else // 우선순위가 없는 애니메이션 실행
	{
		// 우선 순위 애니메이션인 경우 설정
		if (priority)
		{
			this->priorityAnimation = this->animations[key];
		}

		if (this->lastAnimation != this->animations[key])
		{
			if (this->lastAnimation == NULL)
				this->lastAnimation = this->animations[key];
			else
			{
				this->lastAnimation->reset();
				this->lastAnimation = this->animations[key];
			}
		}

		this->animations[key]->play(dt);
	}

	return this->animations[key]->isDone();
}

const bool& AnimationComponent::play(const std::string key, const float & dt, const float & modifier, const float & modifier_max, const bool priority)
{
	if (this->priorityAnimation) // 우선순위 애니메이션이이 있으면
	{
		if (this->priorityAnimation == this->animations[key])
		{
			if (this->lastAnimation != this->animations[key])
			{
				if (this->lastAnimation == NULL)
					this->lastAnimation = this->animations[key];
				else
				{
					this->lastAnimation->reset();
					this->lastAnimation = this->animations[key];
				}
			}

			// 우선순위 애니메이션이 끝나면 제거
			if (this->animations[key]->play(dt, abs(modifier / modifier_max)))
			{
				this->priorityAnimation = NULL;
			}
			this->animations[key]->play(dt, abs(modifier / modifier_max));
		}
	}
	else // 우선순위가 없는 애니메이션 실행
	{
		// 우선순위 애니메이션인 경우 설정
		if (priority)
		{
			this->priorityAnimation = this->animations[key];
		}

		if (this->lastAnimation != this->animations[key])
		{
			if (this->lastAnimation == NULL)
				this->lastAnimation = this->animations[key];
			else
			{
				this->lastAnimation->reset();
				this->lastAnimation = this->animations[key];
			}
		}

		this->animations[key]->play(dt, abs(modifier / modifier_max));
	}

	return this->animations[key]->isDone();
}

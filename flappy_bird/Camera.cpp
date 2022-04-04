#include "Camera.h"
#include <iostream>

Camera::Camera(sf::Vector2i _w_size, float _scale)
{
	center = sf::Vector2f(_w_size.x / 2, _w_size.y / 2);
	view.setSize(_w_size.x, _w_size.y);
	view.setCenter(center);

	shakeDistance *= _scale;
	shakeSpeed *= _scale;
	fallSpeed *= _scale;

	//view.zoom(2);
	//view.zoom(0.5);
}

void Camera::shake()
{
	if (isReset)
	{
		isReset = false;
		doShake = true;
	}
}

void Camera::fall()
{
	if(doFall == false)
		doFall = true;
}

void Camera::update(sf::RenderWindow& _window, float _deltaTime)
{
	if (doShake)
	{
		switch (turns)
		{
		case 0:
			view.move(shakeSpeed * _deltaTime, 0.f);
			if (view.getCenter().x > center.x + shakeDistance) turns++;
			break;
		case 1:
			view.move(-shakeSpeed * _deltaTime, 0.f);
			if (view.getCenter().x < center.x - shakeDistance / 2) turns++;
			break;
		case 2:
			view.move(shakeSpeed * _deltaTime, 0.f);
			if (view.getCenter().x > center.x + shakeDistance / 4) turns++;
			break;
		case 3:
			view.move(-shakeSpeed * _deltaTime, 0.f);
			if (view.getCenter().x < center.x)
			{
				view.setCenter(center);
				turns = 0;
				doShake = false;
			}
		}
	}

	if (doFall)
	{
		view.move(0.f, fallSpeed * _deltaTime);
		if (view.getCenter().y >= center.y + 10.f)
		{
			doFall = false;
			view.setCenter(view.getCenter().x, center.y + 10.f);
		}
	}

	if (doReset)
	{
		view.move(0.f, -fallSpeed * _deltaTime);
		if (view.getCenter().y <= center.y)
		{
			doReset = false;
			isReset = true;
			view.setCenter(center);
		}
	}

	_window.setView(view);
}

void Camera::reset(sf::RenderWindow& _window)
{
	doReset = true;
	doShake = false;
	doFall = false;
	_window.setView(view);
}
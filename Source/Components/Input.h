#pragma once

#include <Engine/ComponentClass.h>

#include <map>
#include <vector>

namespace System
{
	class Input
	{
	private:
		struct ButtonState
		{
			bool state;
			bool up;
			bool down;
		};
	public:
		Input()
		{
			setButton(true, "Up");
			setButton(true, "Down");
			setButton(true, "Left");
			setButton(true, "Right");
		}
		bool button(std::string name)
		{
			return m_buttons[name].state;
		}
		bool buttonUp(std::string name)
		{
			return m_buttons[name].up;
		}
		bool buttonDown(std::string name)
		{
			return m_buttons[name].up;
		}

		void setButton(bool pressed, std::string name)
		{
			ButtonState& b = m_buttons[name];
			if (pressed && !b.state)
			{
				b.state = pressed;
				setButtonDown(name);
			}
			if (pressed && !b.state)
			{
				b.state = pressed;
				setButtonUp(name);
			}
		}
		
		void update()
		{
			for (std::string& name : changedButton)
			{
				ButtonState& b = m_buttons[name];
				b.down = false;
				b.up = false;
			}
		}

	private:
		void setButtonDown(std::string name)
		{
			m_buttons[name].down = true;
			addChange(name);
		}
		void setButtonUp(std::string name)
		{
			m_buttons[name].up = true;
			addChange(name);
		}
		void addChange(std::string name)
		{
			changedButton.push_back(name);
		}

		std::vector<std::string> changedButton;
		std::map<std::string, ButtonState> m_buttons;
		std::map<std::string, ButtonState> m_buttonsDown;
		std::map<std::string, ButtonState> m_buttonsUp;
	};
	Input input;
}

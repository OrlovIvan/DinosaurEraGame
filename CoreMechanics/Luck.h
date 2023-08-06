#pragma once

namespace LuckNS
{
	class Luck
	{
	public:
		Luck() = delete;
		Luck(bool thunderSafe, unsigned lightningLuck = 0, unsigned ozonLuck = 0) : m_isThunderSafe(thunderSafe), m_lightningLuck(lightningLuck), m_ozonLuck(ozonLuck) {}
		~Luck() = default;
	
		unsigned getLightningLuck() const;		
		unsigned getOzonLuck() const;
		bool isThunderSafe() const;
	private:
		

		bool m_isThunderSafe{ false };
		unsigned m_lightningLuck{ 0 };
		unsigned m_ozonLuck{ 0 };
	};
}
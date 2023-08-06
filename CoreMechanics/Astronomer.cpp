#include "pch.h"
#include "Astronomer.h"

Astronomer::Astronomer() 
{
	if (m_luck)
	{
		delete m_luck;
		m_luck = nullptr;
		m_luck = new LuckNS::Luck(true, 1);
	}
}

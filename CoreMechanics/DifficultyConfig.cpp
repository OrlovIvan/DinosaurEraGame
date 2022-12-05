#include "pch.h"
#include "DifficultyConfig.h"

DifficultyConfig* DifficultyConfig::instance = nullptr;

/* // original set of a weather deck
#define CLEAN_COUNT (20)
#define CLOWDY_COUNT (9)
#define OZON_COUNT (4)
#define LIGHTNING_COUNT (4)
#define THUNDER_COUNT (10)
#define METEORITE_COUNT (3)*/

//hard
#define HARD_CLEAN_COUNT (15)
#define HARD_CLOWDY_COUNT (14)
#define HARD_OZON_COUNT (4)
#define HARD_LIGHTNING_COUNT (4)
#define HARD_THUNDER_COUNT (10)
#define HARD_METEORITE_COUNT (3)

//medium
#define MEDIUM_CLEAN_COUNT (20)
#define MEDIUM_CLOWDY_COUNT (19)
#define MEDIUM_OZON_COUNT (4)
#define MEDIUM_LIGHTNING_COUNT (4)
#define MEDIUM_THUNDER_COUNT (5)
#define MEDIUM_METEORITE_COUNT (3)

//easy
#define EASY_CLEAN_COUNT (20)
#define EASY_CLOWDY_COUNT (19)
#define EASY_OZON_COUNT (5)
#define EASY_LIGHTNING_COUNT (3)
#define EASY_THUNDER_COUNT (5)
#define EASY_METEORITE_COUNT (3)

unsigned DifficultyConfig::getWeatherCardCountClean() const
{
    switch (m_level)
    {
    case DifficultyLevel::Easy:
        return EASY_CLEAN_COUNT;
    case DifficultyLevel::Medium:
        return MEDIUM_CLEAN_COUNT;
    case DifficultyLevel::Hard:
        return HARD_CLEAN_COUNT;
    }
    return 0;
}

unsigned DifficultyConfig::getWeatherCardCountClowdy() const
{
    switch (m_level)
    {
    case DifficultyLevel::Easy:
        return EASY_CLOWDY_COUNT;
    case DifficultyLevel::Medium:
        return MEDIUM_CLOWDY_COUNT;
    case DifficultyLevel::Hard:
        return HARD_CLOWDY_COUNT;
    }
    return 0;
}

unsigned DifficultyConfig::getWeatherCardCountThunder() const
{
    switch (m_level)
    {
    case DifficultyLevel::Easy:
        return EASY_THUNDER_COUNT;
    case DifficultyLevel::Medium:
        return MEDIUM_THUNDER_COUNT;
    case DifficultyLevel::Hard:
        return HARD_THUNDER_COUNT;
    }
    return 0;
}

unsigned DifficultyConfig::getWeatherCardCountOzon() const
{
    switch (m_level)
    {
    case DifficultyLevel::Easy:
        return EASY_OZON_COUNT;
    case DifficultyLevel::Medium:
        return MEDIUM_OZON_COUNT;
    case DifficultyLevel::Hard:
        return HARD_OZON_COUNT;
    }
    return 0;
}

unsigned DifficultyConfig::getWeatherCardCountLightning() const
{
    switch (m_level)
    {
    case DifficultyLevel::Easy:
        return EASY_LIGHTNING_COUNT;
    case DifficultyLevel::Medium:
        return MEDIUM_LIGHTNING_COUNT;
    case DifficultyLevel::Hard:
        return HARD_LIGHTNING_COUNT;
    }
    return 0;
}

unsigned DifficultyConfig::getWeatherCardCountMeteorite() const
{
    switch (m_level)
    {
    case DifficultyLevel::Easy:
        return EASY_METEORITE_COUNT;
    case DifficultyLevel::Medium:
        return MEDIUM_METEORITE_COUNT;
    case DifficultyLevel::Hard:
        return HARD_METEORITE_COUNT;
    }
    return 0;
}

unsigned DifficultyConfig::getMonsterHealthAddition() const
{
    switch (m_level)
    {
    case DifficultyLevel::Easy:
        return -1;
        break;
    case DifficultyLevel::Hard:
        return 1;
        break;
    case DifficultyLevel::Medium:
    default:
        break;
    }
    return 0;
}

#include "src/MineralCfg.h"

const std::map<Mineral::MineralType, MineralConfig> MINERAL_CONFIGS = {
    {Mineral::GOLD_MINI,        {50,  2.0, 6, "./images/gold_mini.png", "./images/mask_gold_mini.bmp"}},
    {Mineral::GOLD_NORMAL,      {100, 3.5, 8, "./images/gold_normal.png", "./images/mask_gold_normal.bmp"}},
    {Mineral::GOLD_NORMAL_PLUS, {250, 5.0, 11, "./images/gold_normal_plus.png", "./images/mask_gold_normal_plus.bmp"}},
    {Mineral::GOLD_BIG,         {500, 7.0, 17, "./images/gold_big.png", "./images/mask_gold_big.bmp"}},
    {Mineral::ROCK_MINI,        {11,  5.5, 8, "./images/rock_mini.png", "./images/mask_rock_mini.bmp"}},
    {Mineral::ROCK_NORMAL,      {20,  7.0, 12, "./images/rock_normal.png", "./images/mask_rock_normal.bmp"}},
    {Mineral::ROCK_BIG,         {100, 10.0, 17, "./images/rock_big.png", "./images/mask_rock_big.bmp"}},
    {Mineral::DIAMOND,          {600, 1.5, 6, "./images/diamond.png", "./images/mask_diamond.bmp"}},
    {Mineral::QUESTION_BAG,     {0,   1.0, 12, "./images/question_bag.png", "./images/mask_question_bag.bmp"}},
    {Mineral::SKULL,            {20,  2.0, 10, "./images/skull.png", "./images/mask_skull.bmp"}},
    {Mineral::BONE,             {7,   3.0, 11, "./images/bone.png", "./images/mask_bone.bmp"}},
    {Mineral::TNT,              {2,   1.0, 17, "./images/tnt.png", "./images/mask_tnt.bmp"}}
};
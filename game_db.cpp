
#include "game_db.h"

std::vector<CharacterClass> CharClasses = {
    {CC_Knight, "Рыцарь", {CS_Sword,CS_LeatherArmor}},
    {CC_Paladin, "Паладин", {CS_Sword,CS_MagicSpirit}},
    {CC_Archer, "Лучник",{CS_Archery,CS_MagicSky}},
    {CC_Druid, "Друид",{CS_Staff,CS_MagicEarth}},
    {CC_Cleric, "Клерик",{CS_Mace,CS_MagicBody}},
    {CC_Sorcerer, "Маг",{CS_Dagger,CS_MagicFile}}
};

///////////////////////////////////

std::vector<CharacterSkill> CharSkills ={
//   id,        name,                       {CC_Knight,  CC_Paladin, CC_Archer,  CC_Druid,   CC_Cleric,  CC_Sorcerer}, select_in_create
    {CS_Sword,"Мечи",                       {true,      true,       true,       false,      false,      false},     true},
    {CS_Axe,"Топоры",                       {true,      true,       true,       false,      false,      false},     true},
    {CS_Spear,"Копья",                      {true,      true,       true,       false,      false,      false},     true},
    {CS_Mace,"Булавы",                      {true,      true,       true,       true,       true,       false},     true},
    {CS_Dagger,"Ножи",                      {true,      true,       true,       true,       false,      true},      true},
    {CS_Staff,"Посохи",                     {true,      true,       true,       true,       true,       true},      true},
    {CS_Archery,"Луки",                     {true,      true,       true,       true,       true,       true},      true},
    {CS_Ancient,"Древнее оружие",           {true,      true,       true,       true,       true,       true},      false},
// Armor scills
    {CS_LeatherArmor,"Кожаный доспех",      {true,      true,       true,       true,       true,       true},      true},
    {CS_ChainMail,"Кольчужный доспех",      {true,      true,       true,       false,      true,       false},     true},
    {CS_PlateArmor,"Пластинчатый доспех",   {true,      true,       false,      false,      false,      false},     false},
    {CS_Shields,"Щиты",                     {true,      true,       false,      true,       true,       false},     true},
// Magic scills
    {CS_MagicFile,"Магия Огня",             {false,     false,      true,       true,       false,      true},      true},
    {CS_MagicSky,"Магия Воздуха",           {false,     false,      true,       true,       false,      true},      true},
    {CS_MagicWater,"Магия Воды",            {false,     false,      true,       true,       false,      true},      true},
    {CS_MagicEarth,"Магия Земли",           {false,     false,      true,       true,       false,      true},      true},

    {CS_MagicSpirit,"Магия Духа",           {false,     true,       false,      true,       true,       false},     true},
    {CS_MagicMind,"Магия Разума",           {false,     true,       false,      true,       true,       false},     true},
    {CS_MagicBody,"Магия Тела",             {false,     true,       false,      true,       true,       false},     true},

    {CS_MagicLight,"Магия Света",           {false,     false,      false,      false,      true,       true},      false},
    {CS_MagicDark,"Магия Тьмы",             {false,     false,      false,      false,      true,       true},      false}
};

std::vector<CharacterEffect> CharEffects = {
    {CE_Poison,"Отравлен"},     //
    {CE_Diseased,"Больной"},    //
    {CE_Afraid,"Испуган"},      //
    {CE_Insane,"Безумный"},     //
    {CE_Drunk,"Пьян"},          //
// another effects
    {CE_Weak,"Слабый"},            // -50% damage by weapon
    {CE_Asleep,"Усыпленный"},      // skip turns to first damage
    {CE_Cursed,"Проклятый"},       // success cast spells 1/3%
//
    {CE_Unconscious,"Без сознания"},
    {CE_Paralyzed,"Парализован"},
    {CE_Stoned,"Окаменевший"},
    {CE_Dead,"Мертв"},
    {CE_Eradicated,"Искоренен"}
};

std::vector<TileDisplay> GameTiles = {
    {'X',COLOR_RED,true,true},    // GT_None
    {'~',COLOR_BLUE,true,false},   // GT_Biome_DeepWater
    {'~',COLOR_SKY,true,false},    // GT_Biome_ShallowWater
    {'.',COLOR_YELLOW,true,false}, // GT_Biome_Beach
    {'.',COLOR_GREEN,true,false},  // GT_Biome_Plains
    {'*',COLOR_GREEN,true,false},  // GT_Biome_Forest
    {'~',COLOR_ORANGE,true,false}, // GT_Biome_Hills
    {'^',COLOR_WHITE,true,false},  // GT_Biome_Mountain
    // map tiles
    {'.',COLOR_YELLOW,true,true},   //GT_Sand,
    {'.',COLOR_GREY,true,true},   //GT_Ground,
    {'.',COLOR_GREEN,true,true},  //GT_Grass,
    {'.',COLOR_ORANGE,true,true}, //GT_Road,
    {'.',COLOR_SILVER,true,true}, //GT_RoadStone,
    {'.',COLOR_YELLOW,true,true}, //GT_Floor,
    {'.',COLOR_SILVER,true,true}, //GT_FloorStone,
    {'.',COLOR_SKY,true,true},    //GT_FloorMramor,

    {'T',COLOR_GREEN,true,false},  //GT_Tree,
    {'T',COLOR_GREEN,true,false},  //GT_TreeApple,
    {'v',COLOR_GREEN,true,true},  //GT_Bush,
    {'v',COLOR_BLUE,true,true},   //GT_BrushСurrant,    // смородина
    {'v',COLOR_SKY,true,true},    //GT_BrushGooseberry, // крыжовник

    {'#',COLOR_YELLOW,false,false}, //GT_WallWoden,
    {'#',COLOR_WHITE,false,false},  //GT_WallStone,
    {'#',COLOR_SILVER,false,false}, //GT_WallOldStone,
    {'#',COLOR_SKY,false,false},    //GT_WallMramor

    {'|',COLOR_SKY,true,false},    //GT_Window,
    {'\'',COLOR_SKY,true,false},   //GT_WindowOpen,

    {'|',COLOR_YELLOW,true,false}, //GT_DoorWooden,
    {'\'',COLOR_YELLOW,true,true}, //GT_DoorWoodenOpen,
    {'|',COLOR_WHITE,true,false},  //GT_DoorStone,
    {'\'',COLOR_WHITE,true,true},  //GT_DoorStoneOpen,

    {'<',COLOR_AZURE,true,true},  //GT_StairsWest,
    {'>',COLOR_AZURE,true,true},  //GT_StairsEast,
    {'^',COLOR_AZURE,true,true},  //GT_StairsNorth,
    {'v',COLOR_AZURE,true,true},  //GT_StairsSouth

    // Creatures
    {'@',COLOR_WHITE,true,true},    //GT_Hero,
    {'h',COLOR_WHITE,true,true},    //GT_Human,

    {'g',COLOR_GREEN,true,true},    //GT_MobGoblin,
    {'g',COLOR_BLUE,true,true},     //GT_MobShaman,
    {'g',COLOR_RED,true,true},      //GT_MobKing,

    {'x',COLOR_GREY,true,true},     //GT_MobSpider,
    {'X',COLOR_GREY,true,true},     //GT_MobSpiderGiant,
    {'X',COLOR_YELLOW,true,true},   //GT_MobSpiderGreat,
    {'X',COLOR_RED,true,true},      //GT_MobSpiderQueen,

    {'b',COLOR_YELLOW,true,true},    //GT_MobBat,
    {'b',COLOR_RED,true,true},    //GT_MobBatVampire,

    {'s',COLOR_SKY,true,true},    //GT_MobSnake,
    {'S',COLOR_SKY,true,true},    //GT_MobSnakeQueen


};

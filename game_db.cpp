
#include "game_db.h"

std::vector<CharacterClass> CharClasses =
	{
		{CC_Knight, "Рыцарь"},
		{CC_Paladin, "Паладин"},
		{CC_Archer, "Лучник"},
		{CC_Druid, "Друид"},
		{CC_Cleric, "Клерик"},
		{CC_Sorcerer, "Маг"}
	};

std::vector<CharacterSkill> CharSkills =
    {
        {CS_Sword,"Мечи"},
        {CS_Axe,"Топоры"},
        {CS_Spear,"Копья"},
        {CS_Mace,"Булавы"},
        {CS_Dagger,"Ножи"},
        {CS_Staff,"Посохи"},
        {CS_Archery,"Луки"},
        {CS_Ancient,"Древнее оружие"},
// Armor scills
        {CS_LeatherArmor,"Кожаный доспех"},
        {CS_ChainMail,"Кольчужный доспех"},
        {CS_PlateArmor,"Пластинчатый доспех"},
        {CS_Shields,"Щиты"},
// Magic scills
        {CS_MagicFile,"Магия Огня"},
        {CS_MagicSky,"Магия Воздуха"},
        {CS_MagicWater,"Магия Воды"},
        {CS_MagicEarth,"Магия Земли"},

        {CS_MagicSpirit,"Магия Духа"},
        {CS_MagicMind,"Магия Разума"},
        {CS_MagicBody,"Магия Тела"},

        {CS_MagicLight,"Магия Света"},
        {CS_MagicDark,"Магия Тьмы"}
    };

std::vector<CharacterEffect> CharEffects =
    {
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




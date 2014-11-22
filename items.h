#ifndef ITEMS_H_INCLUDED
#define ITEMS_H_INCLUDED

/*
0 = Black
8 = Gray

1 = Blue
9 = Light Blue

2 = Green
A = Light Green

3 = Aqua
B = Light Aqua

4 = Red
C = Light Red

5 = Purple
D = Light Purple

6 = Yellow
E = Light Yellow

7 = White
F = Bright White
*/

enum EItemType{
    ITEMTYPE_NONE,
    //usable
    ITEMTYPE_POTION,
//    ITEMTYPE_SCROLL,
//    ITEMTYPE_BOOK,
    // weapon
    ITEMTYPE_WEAPON,
    // armor
    ITEMTYPE_ARMOR
    //
};

enum EItemWeaponType{
    WEAPONTYPE_NONE,
    WEAPONTYPE_MELEE,
    WEAPONTYPE_PROJECTIVE,
    WEAPONTYPE_TROW
};

enum EItemArmorType{
    ARMORTYPE_NONE,
    ARMORTYPE_HELMET,
    ARMORTYPE_BODY,
    ARMORTYPE_SHIELD,
    ARMORTYPE_BOOTS
};

enum EItemPotionEffect{
    P_EFFECT_NONE,
    P_EFFECT_HEALING,
    P_EFFECT_ADD_MANA,
    P_EFFECT_REMOVE_POISON,
    P_EFFECT_REMOVE_CURSE,
    P_EFFECT_ADD_POISON,
    P_EFFECT_ADD_CURSE,
    P_EFFECT_OIL_AMMO,
    P_EFFECT_WAPON_AMMO
};

enum ECharachtersSlots{
    C_SLOT_NONE,
    C_SLOT_HEAD,
    C_SLOT_HAND,
    C_SLOT_NECK,
    C_SLOT_LEG,
    C_SLOT_BODY,
    C_SLOT_BODY_UP,
    C_SLOT_TENTACLE
};

class CItem{
        EItemType type;
        char display_char;
        unsigned char display_color;
        unsigned char items_stack_count;
        unsigned int weighht;
    public:
    CItem(){
        type=ITEMTYPE_NONE;
        display_char='X';
        display_color=0x04;
        items_stack_count=0;
        weighht=0;
    }
    const bool isPotion(){
        return type==ITEMTYPE_POTION;
    }
    const bool isWeapon(){
        return type==ITEMTYPE_WEAPON;
    }
    const bool isArmor(){
        return type==ITEMTYPE_ARMOR;
    }
};

class CItemEquipped : public CItem{
        unsigned char slot;
        unsigned char slot_count;
        bool is_equipped;
    public:
    CItemEquipped(){
        is_equipped=false;
        slot=C_SLOT_NONE;
        slot_count=0;
    }
};

class CItemPotion : public CItem{
        EItemPotionEffect effect;
    public:
        CItemPotion(){
            effect=P_EFFECT_NONE;
        }
};

class CItemWeapon : public CItemEquipped{
        EItemWeaponType weapon_type;
        int ammo_type;
        int clip_size;
        bool autoreloaded;
    public:
        CItemWeapon(){
            weapon_type=WEAPONTYPE_NONE;
            ammo_type=0;
            clip_size=0;
            autoreloaded=false;
        }
};

class CItemArmor : public CItemEquipped{
        EItemArmorType armor_type;
        int def;
        int mdef;
    public:
        CItemArmor(){
            armor_type=ARMORTYPE_NONE;
            def=0;
            mdef=0;
        }
};

#endif // ITEMS_H_INCLUDED

#ifndef VALUE_HPP
#define VALUE_HPP
#include <iostream>
#include "include/json/json.h"
#include <math.h>
struct DishBuff {
    int dishNum;
    int dishBuff = 0;
};
class MaterialCategoryBuff {
  public:
    int vegetable;
    int meat;
    int fish;
    int creation;
    MaterialCategoryBuff() : vegetable(0), meat(0), fish(0), creation(0) {}
    void add(const MaterialCategoryBuff &m) {
        this->vegetable += m.vegetable;
        this->meat += m.meat;
        this->fish += m.fish;
        this->creation += m.creation;
    }
    void print() {
        std::cout << "MaterialCategoryBuff: Vegetable: " << this->vegetable
                  << "; Meat: " << this->meat << "; Fish: " << this->fish
                  << "; Creation: " << this->creation << std::endl;
    }
};
class FlavorBuff {
  public:
    int sweet;
    int salty;
    int sour;
    int bitter;
    int spicy;
    int tasty;
    FlavorBuff() : sweet(0), salty(0), sour(0), bitter(0), spicy(0), tasty(0) {}
    void add(const FlavorBuff &f) {
        this->sweet += f.sweet;
        this->salty += f.salty;
        this->sour += f.sour;
        this->bitter += f.bitter;
        this->spicy += f.spicy;
        this->tasty += f.tasty;
    }
    void print() {
        std::cout << "FlavorBuff: Sweet: " << this->sweet
                  << "; Salty: " << this->salty << "; Sour: " << this->sour
                  << "; Bitter: " << this->bitter << "; Spicy: " << this->spicy
                  << "; Tasty: " << this->tasty << std::endl;
    }
};
class RarityBuff {
  public:
    int rarityBuff[5] = {0, 0, 0, 0, 0};
    void add(const RarityBuff &r) { for (int i = 0; i < 5; i++) this->rarityBuff[i] += r.rarityBuff[i]; }
    void print() {
        std::cout << "RarityBuff: ";
        for (int i = 0; i < 5; i++)  std::cout << i + 1 << "火(" << this->rarityBuff[i] << ") ";
        std::cout << std::endl;
    }
    /*几火就是几，不用减一*/
    int &operator[](int i) { return rarityBuff[i - 1]; }
};
class Ability {
  public:
    int stirfry;
    int bake;
    int boil;
    int steam;
    int fry;
    int knife;
    Ability() : stirfry(0), bake(0), boil(0), steam(0), fry(0), knife(0) {}
    Ability(int stirfry, int bake, int boil, int steam, int fry, int knife)
        : stirfry(stirfry), bake(bake), boil(boil), steam(steam), fry(fry),
          knife(knife) {}
    void multiply(double a) {
        this->stirfry = int(this->stirfry * a);
        this->bake = int(this->bake * a);
        this->boil = int(this->boil * a);
        this->steam = int(this->steam * a);
        this->fry = int(this->fry * a);
        this->knife = int(this->knife * a);
    }
    void add(const Ability &a) {
        this->stirfry += a.stirfry;
        this->bake += a.bake;
        this->boil += a.boil;
        this->steam += a.steam;
        this->fry += a.fry;
        this->knife += a.knife;
    }
    void add(int a) {
        this->stirfry += a;
        this->bake += a;
        this->boil += a;
        this->steam += a;
        this->fry += a;
        this->knife += a;
    }
    void print(std::string title) {
        std::cout << title << "Stirfry: " << this->stirfry
                  << "; Boil: " << this->boil << "; Knife: " << this->knife
                  << "; Fry: " << this->fry << "; Bake: " << this->bake
                  << "; Steam: " << this->steam << std::endl;
    }
};

class AbilityBuff : public Ability {
  public:
    AbilityBuff() {}
    AbilityBuff(int stirfry, int bake, int boil, int steam, int fry, int knife)
        : Ability(stirfry, bake, boil, steam, fry, knife) {}
    void print() { this->Ability::print("AbilityBuff: "); }
};
class CookAbility : public Ability {
    

  public:
    Ability percent;
    CookAbility(int stirfry, int bake, int boil, int steam, int fry, int knife)
        : Ability(stirfry, bake, boil, steam, fry, knife) {}
    CookAbility() : Ability() {}
    CookAbility(Json::Value &v);
    int operator/(const Ability &a);
    void print() {
        this->Ability::print("CookAbility: ");
        this->percent.print("CookAbilityPercent: ");
    }
    void add(const CookAbility &a) {
        this->Ability::add(a);
        this->percent.add(a.percent);
    }
    void add(const Ability &a) {
        this->Ability::add(a);
    }
    void add(int a){
        this->Ability::add(a);
    }
    int operator*(const AbilityBuff &a);
    void handle_percent() {
        this->stirfry = int(ceil(this->stirfry * (this->percent.stirfry + 100) / 100.0));
        this->bake = int(ceil(this->bake * (this->percent.bake + 100) / 100.0));
        this->boil = int(ceil(this->boil * (this->percent.boil + 100) / 100.0));
        this->steam = int(ceil(this->steam * (this->percent.steam + 100) / 100.0));
        this->fry = int(ceil(this->fry * (this->percent.fry + 100) / 100.0));
        this->knife = int(ceil(this->knife * (this->percent.knife + 100) / 100.0));
    }
};
class StrangeBuff {
  public:
    DishBuff ExcessCookbookNum;
    DishBuff Rank;

    StrangeBuff() {
        this->ExcessCookbookNum.dishNum = -1;
        this->Rank.dishNum = -1;
    }
    void add(const StrangeBuff &s) {
        if (~s.ExcessCookbookNum.dishNum) {
            if (~this->ExcessCookbookNum.dishNum) {
                //不许不else,很难想象不else会发生什么
                this->ExcessCookbookNum.dishBuff += s.ExcessCookbookNum.dishBuff;
            } else {
                this->ExcessCookbookNum.dishNum = s.ExcessCookbookNum.dishNum;
                this->ExcessCookbookNum.dishBuff = s.ExcessCookbookNum.dishBuff;
            }
        }
        if (~s.Rank.dishNum) {
            if (~this->Rank.dishNum) {
                //不许不else,很难想象不else会发生什么
                this->Rank.dishBuff += s.Rank.dishBuff;
            } else {
                this->Rank.dishNum = s.Rank.dishNum;
                this->Rank.dishBuff = s.Rank.dishBuff;
            }
        }
    }
    void print() {
        if (~this->ExcessCookbookNum.dishNum)
            std::cout << "ExcessCookbookNum: " << this->ExcessCookbookNum.dishNum 
                    << "(" << this->ExcessCookbookNum.dishBuff << ")" << std::endl;
        if (~this->Rank.dishNum)
            std::cout << "Rank: " << this->Rank.dishNum 
                    << "(" << this->Rank.dishBuff << ")" << std::endl;
    }
};
// 技法光环
class SkillHalo : public Ability {
  public:
    SkillHalo(int stirfry, int bake, int boil, int steam, int fry, int knife)
        : Ability(stirfry, bake, boil, steam, fry, knife) {}
    SkillHalo() : Ability() {}
    void print() { this->Ability::print("SkillHalo: "); }
};
// 技法光环:Next
class SkillHaloNext : public Ability {
  public:
    SkillHaloNext(int stirfry, int bake, int boil, int steam, int fry, int knife)
        : Ability(stirfry, bake, boil, steam, fry, knife) {}
    SkillHaloNext() : Ability() {}
    void print() { this->Ability::print("SkillHaloNext: "); }
};
class Skill {
  private:
  public:
    static std::map<int, Skill> skillList;
    CookAbility ability;
    AbilityBuff abilityBuff;
    FlavorBuff flavorBuff;
    RarityBuff rarityBuff;
    MaterialCategoryBuff materialBuff;
    StrangeBuff strangeBuff;
    int coinBuff;
    bool halo;
    SkillHalo skillHalo;
    bool halo_next;
    SkillHaloNext skillHaloNext;
    Skill(CookAbility ability, AbilityBuff abilityBuff, FlavorBuff flavorBuff, RarityBuff rarityBuff, 
          MaterialCategoryBuff materialBuff, StrangeBuff strangeBuff,int coinBuff,
          bool halo, SkillHalo skillHalo,
          bool halo_next, SkillHaloNext skillHaloNext)
        : ability(ability), abilityBuff(abilityBuff), flavorBuff(flavorBuff), rarityBuff(rarityBuff),
          materialBuff(materialBuff), strangeBuff(strangeBuff), coinBuff(coinBuff),
          halo(halo), skillHalo(skillHalo), 
          halo_next(halo_next), skillHaloNext(skillHaloNext){}
    Skill() {
        this->ability = CookAbility();
        this->abilityBuff = AbilityBuff();
        this->flavorBuff = FlavorBuff();
        this->rarityBuff = RarityBuff();
        this->materialBuff = MaterialCategoryBuff();
        this->strangeBuff = StrangeBuff();
        this->coinBuff = 0;
        this->halo = false;
        this->skillHalo = SkillHalo();
        this->halo_next = false;
        this->skillHaloNext = SkillHaloNext();
    }
    Skill getSkill(int id) { return skillList[id]; }
    static void loadJson(Json::Value &v);
    void add(const Skill &s) {
        this->ability.add(s.ability);
        this->abilityBuff.add(s.abilityBuff);
        this->flavorBuff.add(s.flavorBuff);
        this->rarityBuff.add(s.rarityBuff);
        this->materialBuff.add(s.materialBuff);
        this->strangeBuff.add(s.strangeBuff);
        this->coinBuff += s.coinBuff;
        this->halo |= s.halo;
        this->skillHalo.add(s.skillHalo);
        this->halo_next |= s.halo_next;
        this->skillHaloNext.add(s.skillHaloNext);
    }
    void print() {
        this->ability.print();
        this->abilityBuff.print();
        this->flavorBuff.print();
        this->rarityBuff.print();
        this->materialBuff.print();
        this->strangeBuff.print();
        std::cout << "CoinBuff: " << this->coinBuff << std::endl;
        if (this->halo){
            std::cout << "Halo: " << std::endl;
            this->skillHalo.print();
        }
        if (this->halo_next){
            std::cout << "Halo_next: " << std::endl;
            this->skillHaloNext.print();
        }
    }
};
enum ToolEnum {
    NO_TOOL = -2,
    NOT_EQUIPPED = -1,
    STIRFRY,
    BAKE,
    BOIL,
    STEAM,
    FRY,
    KNIFE
};
enum FlavorEnum { UNIDENTIFIED = -1, SWEET, SALTY, SOUR, BITTER, SPICY, TASTY };
enum ToolFileType {
    NO_FILE__NO_TOOL,
    EMPTY_FILE__NOT_EQUIPPED,
    CUSTOMIZE_TOOL
};
#endif
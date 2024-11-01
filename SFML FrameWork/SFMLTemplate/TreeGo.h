#pragma once
#include "GameObject.h"

class EffectLog;
class BranchGo;
class TreeGo :
    public GameObject
{
protected:
    sf::Sprite tree;
    std::list<BranchGo*> branches;
    int branchCount = 6;
    std::string treeTextureId = "graphics/tree.png";
    std::string branchTextureId = "graphics/branch.png";

    float branchOffsetY = 150.f;

    ObjectPool<EffectLog> effectLogPool;
    std::list<EffectLog*> logEffects;
public:
    TreeGo(const std::string& name = "");
    ~TreeGo();
    
    Sides RandomSide() const;

    Sides Chop(Sides side);
    void UpdateBranchPos();
    
    void Init() override;
    void Release() override;

    void Reset() override;
    void Update(float dt) override;
    void Draw(sf::RenderWindow& window) override;
    
    void SetPosition(const sf::Vector2f& pos) override;

    void ClearEffectLog();
};


#include "stdafx.h"
#include "TreeGo.h"
#include "BranchGo.h"
#include "EffectLog.h"
#include "Scene.h"
TreeGo::TreeGo(const std::string& name)
    : GameObject(name)
{
}

TreeGo::~TreeGo()
{
    Release();
}

Sides TreeGo::RandomSide() const
{
    int rand = Utils::RandomRange(0, 2);
    if (rand > 1)
        return Sides::None;

    return Sides(rand);
}

Sides TreeGo::Chop(Sides side)
{

    BranchGo* temp = branches.front();
    branches.pop_front();

    temp->SetSide(RandomSide());

    branches.push_back(temp);
    UpdateBranchPos();
    return branches.front()->GetSide();
}

void TreeGo::UpdateBranchPos()
{
    sf::Vector2f pos = Getposition();

    for (auto branch : branches)
    {
        pos.y -= branchOffsetY;

        branch->SetPosition(pos);
    }
}

void TreeGo::Init()
{
    Release();
    tree.setTexture(TEXTURE_MGR.Get(treeTextureId), true);
    Utils::SetOrigin(tree, Origins::BC);

    sf::Vector2f originBranch;
    originBranch.x = tree.getLocalBounds().width * -0.5f;
    sf::Texture& branchTex = TEXTURE_MGR.Get(branchTextureId);
    originBranch.y = branchTex.getSize().y * 0.5f;
    for (int i = 0; i < branchCount; i++)
    {
        BranchGo* branch = new BranchGo(branchTextureId);
        branch->SetOrigin(originBranch);
        branch->Init();
        branch->SetSide(RandomSide());
        branches.push_back(branch);
    }
}

void TreeGo::Release()
{
    for (auto logEffect : effectLogPool.GetUsedList())
    {
        effectLogPool.Return(logEffect);
        SCENE_MGR.GetCurrentScene()->RemoveGo(logEffect);
    }
    logEffects.clear();
    for (auto branch : branches)
    {
        branch->Release();
        delete branch;
    }
    branches.clear();
}

void TreeGo::Reset()
{
    tree.setTexture(TEXTURE_MGR.Get(treeTextureId), true);
    for (auto branch : branches)
    {
        branch->Reset();
    }
    UpdateBranchPos();
    auto lastBranch = branches.front();
    lastBranch->SetSide(Sides::None);
}

void TreeGo::Update(float dt)
{
    if (InputMgr::GetKeyDown(sf::Keyboard::Left))
    {
        EffectLog* effect = effectLogPool.Take();
        if (effect != nullptr)
        {
            SCENE_MGR.GetCurrentScene()->AddGo(effect);
            effect->SetOrigin(Origins::BC);
            effect->SetPosition(position);
            effect->Fire({ 1000.f, -1000.f });
            logEffects.push_back(effect);
        }
    }
    if (InputMgr::GetKeyDown(sf::Keyboard::Right))
    {
        EffectLog* effect = effectLogPool.Take();
        if (effect != nullptr)
        {
            SCENE_MGR.GetCurrentScene()->AddGo(effect);
            effect->SetOrigin(Origins::BC);
            effect->SetPosition(position);
            effect->Fire({ -1000.f, -1000.f });
            logEffects.push_back(effect);  // logEffects�� �߰�
        }
    }
    for (auto branch : branches)
    {
        branch->Update(dt);
    }

    auto it = logEffects.begin();
    while (it != logEffects.end())
    {
        auto logEffect = *it;
        if (!logEffect->IsActive())
        {
            effectLogPool.Return(logEffect); // ��Ȱ��ȭ�� ��ü ��ȯ
            SCENE_MGR.GetCurrentScene()->RemoveGo(logEffect); // ������ ����
            it = logEffects.erase(it); // used ����Ʈ���� ����
        }
        else
        {
            ++it;
        }
    }

}

void TreeGo::Draw(sf::RenderWindow& window)
{
    window.draw(tree);
    for (auto branch : branches)
    {
        if (branch->IsActive())
        {
            branch->Draw(window);
        }
    }
}

void TreeGo::SetPosition(const sf::Vector2f& pos)
{
    position = pos;
    tree.setPosition(pos);
    UpdateBranchPos();
}

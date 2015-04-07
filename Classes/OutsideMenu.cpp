//
//  OutsideMenu.cpp
//  CustomDropDownList
//
//  Created by ESoragoto on 3/2/15.
//
//

#include "OutsideMenu.h"

USING_NS_CC;

OutsideMenu::OutsideMenu(Node* scene, Node* layer, int side)
{
}

OutsideMenu::~OutsideMenu()
{}

OutsideMenu* OutsideMenu::Create(Node *scene, Node *layer, int side)
{
    auto ret = new OutsideMenu(scene, layer, side);
    if (ret && ret->init())
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}

bool OutsideMenu::init()
{
    if (!Node::init())
    {
        return false;
    }
    
    log("init OutsideMenu");
    return true;
}

int OutsideMenu::SetMenuBySide()
{
    switch (side_)
    {
        case 0:
            position_.x = scene_->getPosition().x;
            position_.y = scene_->getPosition().y - layer_->getContentSize().height;
            break;
        case 1:
            position_.x = scene_->getPosition().x - layer_->getContentSize().width;
            position_.y = scene_->getPosition().y;
            break;
        case 2:
            position_.x = scene_->getPosition().x;
            position_.y = scene_->getPosition().y + layer_->getContentSize().height;
            break;
        case 3:
            position_.x = scene_->getPosition().x + layer_->getContentSize().width;
            position_.y = scene_->getPosition().y;
            break;
        default:
            return -1;
    }
    return 0;
}
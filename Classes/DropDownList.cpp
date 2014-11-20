//
//  DropDownList.cpp
//  CustomDropDownList
//
//  Created by ESoragoto on 11/20/14.
//
//


#include "cocos2d.h"
#include "DropDownList.h"

USING_NS_CC;

NS_CC_BEGIN

namespace CustomDropDownListBox {
    DropDownList::DropDownList(LabelTTF *pLable,
                               Size size) :
    pShowLable(pLable),
    isShowingMenu(false),
    lastSelectedIndex(0)
    {
        pMainMenu = Menu::create();
        pMainMenu->setPosition(Point(size.width / 2,
                                     size.height / 2));
        pMainMenu->setColor(DROPDOWNLIST_NORMAL_COLOR3);
        pMainMenu->retain();
        
        pShowLable->setPosition(Point(size.width / 2,
                                      size.height / 2));
        pShowLable->setColor(DROPDOWNLIST_NORMAL_COLOR3);
        
        this->addChild(pShowLable);
        this->setContentSize(size);
    }//DropDownList::DropDownList
    
    DropDownList::~DropDownList() {};
    
    DropDownList *DropDownList::create(LabelTTF *pLabel,
                                       Size size)
    {
        auto *pList = new DropDownList(pLabel,
                                       size);
        pList->autorelease();
                
        return pList;
    }//DropDownList *DropDownList::create
    
    std::string DropDownList::getString()
    {
        return pShowLable->getString();
    }//DropDownList::getString
    
    int DropDownList::getSelectedIndex()
    {
        return lastSelectedIndex;
    }//DropDownList::getSelectedIndex
    
    void DropDownList::setSelectedIndex(int index)
    {
        lastSelectedIndex = index;
        
        for (int i = 0, j = (int)selectLables.size(); i < j; i++)
        {
            if ( lastSelectedIndex == i)
            {
                bgLayers[i]->setColor(DROPDOWNLIST_SELECTED_COLOR3);
                pShowLable->setString(selectLables[i]->getString());
            }
            else
            {
                bgLayers[i]->setColor(DROPDOWNLIST_NORMAL_COLOR3);
            }
        }
    }//DropDownList::setSelectedIndex
    
    void DropDownList::onEnter()
    {
        setTouchEnabled(true);
        Layer::onEnter();
    }//DropDownList::onEnter
    
    
    
    bool DropDownList::touchBegan(Touch *pTouch,
                                  Event *pEvent)
    {
        auto locInView = pTouch->getLocationInView();
        auto location = Director::sharedDirector()->convertToGL(locInView);
        
        CCLOG("BEGAN----------");
        CCLOG("location: %f, %f",
              location.x,
              location.y);
        
        if (false == isShowingMenu)
        {
            Rect showRect;
            showRect.origin = this->getPosition();
            showRect.size = this->getContentSize();
            
            if (showRect.containsPoint(location))
            {
                isShowingMenu = true;
                addChild(pMainMenu);
                
                for (int i = 0, j = (int)selectLables.size(); i < j; i++)
                {
                    if ( lastSelectedIndex == i)
                    {
                        bgLayers[i]->setColor(DROPDOWNLIST_HIGHLIGHT_COLOR3);
                    }
                    else
                    {
                        bgLayers[i]->setColor(DROPDOWNLIST_NORMAL_COLOR3);
                    }
                }
                return true;
            }
        }
        
        if (true == isShowingMenu)
        {
            Rect listRect;
            listRect.origin = this->getPosition();
            listRect.size = this->getContentSize();
            
            if (!listRect.containsPoint(location))
            {
                onClose();
            }
        }
        
        return false;
    }//DropDownList::touchBegan
    
    void DropDownList::addLabel(LabelTTF *pLabel)
    {
        auto size = getContentSize();
        auto *pNormalColor = LayerColor::create(DROPDOWNLIST_NORMAL_COLOR,
                                                size.width,
                                                size.height);
        auto *pSelectedColor = LayerColor::create(DROPDOWNLIST_SELECTED_COLOR,
                                                  size.width,
                                                  size.height);
        
        bgLayers.push_back(pNormalColor);
        selectLables.push_back(pLabel);
        
        auto item = MenuItemSprite::create(pNormalColor,
                                           pSelectedColor,
                                           NULL,
                                           this,
                                           SEL_MenuHandler(&DropDownList::onSelected));
        
        pLabel->setPosition(Point(size.width / 2,
                                  size.height / 2));
        item->addChild(pLabel);
        item->setTag((int)selectLables.size() - 1);
        item->setPosition(0,
                          -(int)selectLables.size() * size.height);
        
        pMainMenu->addChild(item);
        
    }//DropDownList::addLabel
    
    void DropDownList::onSelected(Object *pSender)
    {
        auto item = dynamic_cast<MenuItem *>(pSender);
        
        if (item)
        {
            lastSelectedIndex = item->getTag();
            pShowLable->setString(selectLables[item->getTag()]->getString());
        }
        
        onClose();
    }//DropDownList::onSelected
    
    void DropDownList::onClose()
    {
        removeChild(pMainMenu,
                    true);
        isShowingMenu = false;
    }//DropDownList::onClose
}//namespace CustomDropDownListBox

NS_CC_END
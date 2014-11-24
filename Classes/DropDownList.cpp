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
    DropDownList::DropDownList(LabelTTF *lable,
                               Size size) :
    show_lable_(lable),
    is_showing_menu_(false),
    
    last_selected_index_(0)
    {
        main_menu_ = Menu::create();
        main_menu_->setPosition(Point(size.width / 2,
                                     size.height / 2));
        main_menu_->setColor(kDropDownListNormalColor3B);
        main_menu_->retain();
        
        show_lable_->setPosition(Point(size.width / 2,
                                      size.height / 2));
        show_lable_->setColor(kDropDownListNormalColor3B);
        
        this->addChild(show_lable_);
        this->setContentSize(size);
    }//DropDownList::DropDownList
    
    DropDownList::~DropDownList() {};
    
    bool DropDownList::init()
    {
        if ( !Layer::init() )
        {
            return false;
        }
        
        listener_touch_ = EventListenerTouchOneByOne::create();
        listener_touch_->onTouchBegan = CC_CALLBACK_2(DropDownList::onTouchBegan,
                                                      this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener_touch_,
                                                                 this);
        log("init");
        return true;
    }
    
    DropDownList *DropDownList::Create(LabelTTF *label,
                                       Size size)
    {
        auto *list = new DropDownList(label,
                                       size);
        list->autorelease();
                
        return list;
    }//DropDownList *DropDownList::create
    
    std::string DropDownList::GetString()
    {
        return show_lable_->getString();
    }//DropDownList::GetString
    
    int DropDownList::GetSelectedIndex()
    {
        return last_selected_index_;
    }//DropDownList::getSelectedIndex
    
    void DropDownList::SetSelectedIndex(int index)
    {
        last_selected_index_ = index;
        
        for (int i = 0, j = (int)select_lables_.size(); i < j; i++)
        {
            if ( last_selected_index_ == i)
            {
                bg_layers_[i]->setColor(kDropDownListSelectedColor3B);
                show_lable_->setString(select_lables_[i]->getString());
            }
            else
            {
                bg_layers_[i]->setColor(kDropDownListNormalColor3B);
            }
        }
    }//DropDownList::setSelectedIndex
        
    bool DropDownList::onTouchBegan(Touch *touch,
                                  Event *event)
    {
        auto locInView = touch->getLocationInView();
        auto location = Director::sharedDirector()->convertToGL(locInView);
        
        CCLOG("BEGAN----------");
        CCLOG("location: %f, %f",
              location.x,
              location.y);
        
        if (false == is_showing_menu_)
        {
            Rect show_rect;
            show_rect.origin = this->getPosition();
            show_rect.size = this->getContentSize();
            
            if (show_rect.containsPoint(location))
            {
                is_showing_menu_ = true;
                addChild(main_menu_);
                
                for (int i = 0, j = (int)select_lables_.size(); i < j; i++)
                {
                    if ( last_selected_index_ == i)
                    {
                        bg_layers_[i]->setColor(kDropDownListHighlightColor3B);
                    }
                    else
                    {
                        bg_layers_[i]->setColor(kDropDownListNormalColor3B);
                    }
                }
                return true;
            }
        }
        
        if (true == is_showing_menu_)
        {
            Rect list_rect;
            list_rect.origin = this->getPosition();
            list_rect.size = this->getContentSize();
            
            if (!list_rect.containsPoint(location))
            {
                OnClose();
            }
        }
        
        return false;
    }//DropDownList::touchBegan
    
    void DropDownList::AddLabel(LabelTTF *label)
    {
        auto size = getContentSize();
        auto *normal_color = LayerColor::create(kDropDownListNormalColor4B,
                                                size.width,
                                                size.height);
        auto *pSelectedColor = LayerColor::create(kDropDownListSelectedColor4B,
                                                  size.width,
                                                  size.height);
        
        bg_layers_.push_back(normal_color);
        select_lables_.push_back(label);
        
        auto item = MenuItemSprite::create(normal_color,
                                           pSelectedColor,
                                           NULL,
                                           this,
                                           SEL_MenuHandler(&DropDownList::OnSelected));
        
        label->setPosition(Point(size.width / 2,
                                  size.height / 2));
        item->addChild(label);
        item->setTag((int)select_lables_.size() - 1);
        item->setPosition(0,
                          -(int)select_lables_.size() * size.height);
        
        main_menu_->addChild(item);
        
    }//DropDownList::addLabel
    
    void DropDownList::OnSelected(Object *sender)
    {
        auto item = dynamic_cast<MenuItem *>(sender);
        
        if (item)
        {
            last_selected_index_ = item->getTag();
            show_lable_->setString(select_lables_[item->getTag()]->getString());
        }
        
        OnClose();
    }//DropDownList::onSelected
    
    void DropDownList::OnClose()
    {
        removeChild(main_menu_,
                    true);
        is_showing_menu_ = false;
    }//DropDownList::onClose
}//namespace CustomDropDownListBox

NS_CC_END
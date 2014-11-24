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
    DropDownList::DropDownList(LabelTTF *label,
                               Size size) :
    show_label_(label),
    is_showing_menu_(false),
    last_selected_index_(0)
    {
        main_menu_ = Menu::create();
        main_menu_->setPosition(Point(size.width / 2,
                                      size.height / 2));
        main_menu_->setColor(kDropDownListNormalColor3B);
        main_menu_->retain();
        
        show_label_->setPosition(Point(size.width / 2,
                                       size.height / 2));
        show_label_->setColor(kDropDownListNormalColor3B);
        
        this->addChild(show_label_);
//        AddLabel(show_label_);
        this->setContentSize(size);
    }//DropDownList::DropDownList
    
    DropDownList::~DropDownList() {};
    
    void DropDownList::OpenListener()
    {
        //添加触摸监听
        listener_touch_ = EventListenerTouchOneByOne::create();
        listener_touch_->onTouchBegan = CC_CALLBACK_2(DropDownList::onTouchBegan,
                                                      this);
        listener_touch_->onTouchEnded = CC_CALLBACK_2(DropDownList::onTouchEnded,
                                                      this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener_touch_,
                                                                 this);
        //输出启动监听的信息
        log("listener ready");
    }//DropDownList::OpenListener
    
    DropDownList *DropDownList::Create(LabelTTF *label,
                                       Size size)
    {
        auto *list = new DropDownList(label,
                                      size);
//        list->AddLabel(label);
        
        return list;
    }//*DropDownList::create
    
    std::string DropDownList::GetString()
    {
        return show_label_->getString();
    }//DropDownList::GetString
    
    int DropDownList::GetSelectedIndex()
    {
        return last_selected_index_;
    }//DropDownList::GetSelectedIndex
    
    void DropDownList::SetSelectedIndex(int index)
    {
        last_selected_index_ = index;
        
        for (int i = 0, j = (int)select_labels_.size(); i < j; i++)
        {
            if ( last_selected_index_ == i)
            {
                bg_layers_[i]->setColor(kDropDownListSelectedColor3B);
                show_label_->setString(select_labels_[i]->getString());
            }
            else
            {
                bg_layers_[i]->setColor(kDropDownListNormalColor3B);
            }
        }
    }//DropDownList::SetSelectedIndex
        
    bool DropDownList::onTouchBegan(Touch *touch,
                                  Event *event)
    {
        auto locInView = touch->getLocationInView();
        auto location = Director::sharedDirector()->convertToGL(locInView);
        
        log("BEGAN----------");
        log("location: %f, %f",
            location.x,
            location.y);
        
        if (false == is_showing_menu_)
        {
            Rect show_rect;
            show_rect.origin = this->getPosition();
            show_rect.size = getContentSize();
            
            log("rect----------");
            log("location: %f, %f",
                show_rect.origin.x,
                show_rect.origin.y);
            log("size: %f, %f",
                show_rect.size.width,
                show_rect.size.height);
            
            if (show_rect.containsPoint(location))
            {
                is_showing_menu_ = true;
                for (int i = 0, j = (int)select_labels_.size(); i < j; i++)
                {
                    if (last_selected_index_ == i)
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
    }//DropDownList::onTouchBegan
    
    void DropDownList::onTouchEnded(cocos2d::Touch *touch,
                                    cocos2d::Event *event)
    {
        if (true == is_showing_menu_)
        {
//            main_menu_->setPosition(Vec2(0,
//                                         0));
            addChild(main_menu_);
        }
    }//DropDownList::onTouchEnded
    
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
        select_labels_.push_back(label);
        
        auto item = MenuItemSprite::create(normal_color,
                                           pSelectedColor,
                                           NULL,
                                           this,
                                           SEL_MenuHandler(&DropDownList::OnSelected));
        
        label->setPosition(Point(size.width / 2,
                                  size.height / 2));
        item->addChild(label);
        //select_labels_是向量，因此select_labels_.size()表示其包含元素的个数
        item->setTag((int)select_labels_.size() - 1);
        item->setPosition(0,
                          - (int)select_labels_.size() * size.height);
        
        main_menu_->addChild(item);
    }//DropDownList::AddLabel
    
    void DropDownList::OnSelected(Object *sender)
    {
        auto item = dynamic_cast<MenuItem *>(sender);
        
        if (item)
        {
            last_selected_index_ = item->getTag();
            show_label_->setString(select_labels_[item->getTag()]->getString());
        }
        
        OnClose();
    }//DropDownList::OnSelected
    
    void DropDownList::OnClose()
    {
        removeChild(main_menu_,
                    true);
        is_showing_menu_ = false;
    }//DropDownList::OnClose
}//namespace CustomDropDownListBox

NS_CC_END
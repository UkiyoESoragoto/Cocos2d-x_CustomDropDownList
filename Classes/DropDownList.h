//
//  DropDownList.h
//  CustomDropDownList
//
//  Created by ESoragoto on 11/20/14.
//
//

#ifndef __CustomDropDownList__DropDownList__
#define __CustomDropDownList__DropDownList__

#pragma once

#include <cocos2d.h>

USING_NS_CC;
NS_CC_BEGIN

namespace CustomDropDownListBox
{
    //设置颜色
    //普通颜色(Color4B)
    const auto kDropDownListNormalColor4B = Color4B(128,
                                                    128,
                                                    128,
                                                    255);
    //选中颜色(Color4B)
    const auto kDropDownListSelectedColor4B = Color4B(200,
                                                      200,
                                                      200,
                                                      255);
    //高亮颜色(Color4B)
    const auto kDropDownListHighlightColor4B = Color4B(0,
                                                       0,
                                                       255,
                                                       255);
    //普通颜色(Color3B)
    const auto kDropDownListNormalColor3B = Color3B(128,
                                                    128,
                                                    128);
    //选中颜色(Color3B)
    const auto kDropDownListSelectedColor3B = Color3B(200,
                                                      200,
                                                      200);
    //高亮颜色(Color3B)
    const auto kDropDownListHighlightColor3B = Color3B(0,
                                                       0,
                                                       225);
    
    //声明对象
    class DropDownList : public Layer
    {
    public:
        DropDownList(LabelTTF *label,
                     Size size);
        ~DropDownList();
        
        ///<summary>
        ///
        ///</summary>
        ///<parm name = ""></parm>
        virtual bool init();
        
        ///<summary>
        ///创建实例对象
        ///</summary>
        ///<parm name = "*label"></parm>
        ///<parm name = "size"></parm>
        static DropDownList * Create(LabelTTF *label,
                                     Size size);
        
        ///<summary>
        ///获取选中对象的string
        ///</summary>
        std::string GetString();
        
        ///<summary>
        ///获取选中的index
        ///</summary>
        ///<parm name = ""></parm>
        int GetSelectedIndex();
        
        ///<summary>
        ///设置选中的index
        ///</summary>
        ///<parm name = "index"></parm>
        void SetSelectedIndex(int index);
        
//        ///<summary>
//        ///
//        ///</summary>
//        ///<parm name = ""></parm>
//        void OnEnter();
        
        ///<summary>
        ///
        ///</summary>
        ///<parm name = ""></parm>
        virtual bool onTouchBegan(Touch *touch,
                                Event *event);
        
        ///<summary>
        ///添加新的Label以冒充下拉菜单
        ///</summary>
        ///<parm name = ""></parm>
        void AddLabel(LabelTTF *lable);
        
        ///<summary>
        ///下拉列表中的项被选中
        ///</summary>
        ///<parm name = ""></parm>
        void OnSelected(Object *sender);
        
        ///<summary>
        ///关闭下拉列表
        ///</summary>
        ///<parm name = ""></parm>
        void OnClose();
        
    private:
        Menu *main_menu_;    //下拉选项列表的集合
        LabelTTF *show_lable_;   //显示选中的结果
        std::vector<LabelTTF *> select_lables_;   //用来冒充下拉列表的label们
        std::vector<LayerColor *> bg_layers_; //用于设置背景颜色
        bool is_showing_menu_; //是否已显示了下拉列表
        int last_selected_index_;  //选中下拉列表的index
    
        EventListenerTouchOneByOne *listener_touch_;
    };//class DropDownList : public Layer
}//namespace CustomDropDownListBox
NS_CC_END

#endif //#define __CustomDropDownList__DropDownList__
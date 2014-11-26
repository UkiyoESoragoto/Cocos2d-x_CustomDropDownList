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
    const auto kColorWhite = Color3B(255,
                                     255,
                                     255);
    
    //声明对象
    class DropDownList : public Layer
    {
    public:
        DropDownList(LabelTTF *label,
                     Size show_label_size,
                     Size main_menu_cell_size);
        ~DropDownList();
        
        ///<summary>
        ///初始化
        ///</summary>
        void OpenListener();
        
        ///<summary>
        ///创建实例对象
        ///</summary>
        ///<parm name = "*label">添加一个label作为默认显示</parm>
        ///<parm name = "size">默认尺寸</parm>
        static DropDownList * Create(LabelTTF *label,
                                     Size show_label_size,
                                     Size main_menu_cell_size);
        
        ///<summary>
        ///获取选中对象的string
        ///</summary>
        std::string GetString();
        
        ///<summary>
        ///获取选中的index
        ///</summary>
        int GetSelectedIndex();
        
        ///<summary>
        ///设置选中的对象
        ///</summary>
        ///<parm name = "index">对象的index值</parm>
        void SetSelectedIndex(int index);
        
        ///<summary>
        ///开始触摸
        ///</summary>
        ///<parm name = "*touch">触摸对象</parm>
        ///<parm name = "*event">触摸事件</parm>
        virtual bool onTouchBegan(Touch *touch,
                                  Event *event);
        
        ///<summary>
        ///结束触摸
        ///</summary>
        ///<parm name = "*touch">触摸对象</parm>
        ///<parm name = "*event">触摸事件</parm>
        void onTouchEnded(Touch *touch,
                          Event *event);
        
        ///<summary>
        ///添加新的Label以冒充下拉菜单
        ///</summary>
        ///<parm name = "*label">冒充菜单用的label素材</parm>
        void AddLabel(LabelTTF *label);
        
        ///<summary>
        ///下拉列表中的项被选中
        ///</summary>
        ///<parm name = "*sender">被点击的的对象</parm>
        void OnSelected(Object *sender);
        
        ///<summary>
        ///关闭下拉列表
        ///</summary>
        void OnClose();
        
        ///<summary>
        ///自定义的位置设置
        ///</summary>
        ///<parm name = "*sender">被点击的的对象</parm>
        void CustomSetPosition(Node *node,
                               Point point);
        
    private:
        Menu *main_menu_;    //下拉选项列表的集合
        LabelTTF *show_label_;   //对显示区用label
        std::vector<LabelTTF *> select_labels_;   //用来冒充下拉列表的label们
        std::vector<LayerColor *> bg_layers_; //用于设置背景颜色
        bool is_need_show_menu_; //是否已显示了下拉列表
        int last_selected_index_;  //选中下拉列表的index
        Size main_menu_cell_size_;   //菜单包含项的Size
        Size show_label_size_;  //对显示区用label的占地面积
    
        EventListenerTouchOneByOne *listener_touch_;
    };//class DropDownList : public Layer
}//namespace CustomDropDownListBox
NS_CC_END

#endif //#define __CustomDropDownList__DropDownList__
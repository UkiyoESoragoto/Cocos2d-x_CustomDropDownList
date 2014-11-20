//
//  DropDownList.h
//  CProject
//
//  Created by ESoragoto on 11/18/14.
//
//

#ifndef __CProject__DropDownList__
#define __CProject__DropDownList__

#pragma once

#include <cocos2d.h>

USING_NS_CC;
NS_CC_BEGIN

namespace CustomDropDownListBox
{
    //设置颜色
    //普通颜色(Color4B)
    const auto DROPDOWNLIST_NORMAL_COLOR = cocos2d::Color4B(128,
                                                            128,
                                                            128,
                                                            255);
    //选中颜色(Color4B)
    const auto DROPDOWNLIST_SELECTED_COLOR = Color4B(200,
                                                     200,
                                                     200,
                                                     255);
    //高亮颜色(Color4B)
    const auto DROPDOWNLIST_HIGHLIGHT_COLOR = Color4B(0,
                                                      0,
                                                      255,
                                                      255);
    //普通颜色(Color3B)
    const auto DROPDOWNLIST_NORMAL_COLOR3 = Color3B(128,
                                                    128,
                                                    128);
    //选中颜色(Color3B)
    const auto DROPDOWNLIST_SELECTED_COLOR3 = Color3B(200,
                                                      200,
                                                      200);
    //高亮颜色(Color3B)
    const auto DROPDOWNLIST_HIGHLIGHT_COLOR3 = Color3B(0,
                                                       0,
                                                       225);
    
    //声明对象
    class DropDownList : public Layer
    {
    public:
        DropDownList(LabelTTF *pLabel,
                     Size size);
        ~DropDownList();
        
        ///<summary>
        ///
        ///</summary>
        ///<parm name = ""></parm>
        
        ///<summary>
        ///创建实例对象
        ///</summary>
        ///<parm name = "*pLabel"></parm>
        ///<parm name = "size"></parm>
        static DropDownList * create(LabelTTF *pLabel,
                                     Size size);
        
        ///<summary>
        ///获取选中对象的string
        ///</summary>
        std::string getString();
        
        
        ///<summary>
        ///设置选中的index
        ///</summary>
        ///<parm name = "index"></parm>
        void setSelectedIndex(int index);
        
        ///<summary>
        ///
        ///</summary>
        ///<parm name = ""></parm>
        void onEnter();
        
        ///<summary>
        ///
        ///</summary>
        ///<parm name = ""></parm>
//        void registerWithTouchDispatcher();
        
        ///<summary>
        ///
        ///</summary>
        ///<parm name = ""></parm>
        virtual bool touchBegan(Touch *pTouch,
                                Event *pEvent);
        
        ///<summary>
        ///添加新的Label以冒充下拉菜单
        ///</summary>
        ///<parm name = ""></parm>
        void addLabel(LabelTTF *pLable);
        
        ///<summary>
        ///下拉列表中的项被选中
        ///</summary>
        ///<parm name = ""></parm>
        void onSelected(Object *pSender);
        
        ///<summary>
        ///关闭下拉列表
        ///</summary>
        ///<parm name = ""></parm>
        void onClose();
        
    private:
        Menu *pMainMenu;    //下拉选项列表的集合
        LabelTTF *pShowLable;   //显示选中的结果
        std::vector<LabelTTF *> selectLables;   //用来冒充下拉列表的label们
        std::vector<LayerColor *> bgLayers; //用于设置背景颜色
        bool isShowingMenu; //是否已显示了下拉列表
        int lastSelectedIndex;  //选中下拉列表的index
    };//class DropDownList : public Layer
}//namespace CustomDropDownListBox
NS_CC_END

#endif /* defined(__CProject__DropDownList__) */

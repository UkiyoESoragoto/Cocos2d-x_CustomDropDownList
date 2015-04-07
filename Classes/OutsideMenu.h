//
//  OutsideMenu.h
//  CustomDropDownList
//
//  Created by ESoragoto on 3/2/15.
//
//

#ifndef __CustomDropDownList__OutsideMenu__
#define __CustomDropDownList__OutsideMenu__

#include <cocos2d.h>

USING_NS_CC;

class OutsideMenu : public Node
{
private:
    Node* scene_;
    Node* layer_;
    int side_;
    struct Position
    {
        int x;
        int y;
    };
    
    Position position_;
    
public:
    OutsideMenu(Node* scene, Node* layer, int side);
    ~OutsideMenu();
    
    virtual bool init();
    
    static OutsideMenu* Create(Node* scene, Node* layer, int side);
    
    int SetMenuBySide();
};

#endif /* defined(__CustomDropDownList__OutsideMenu__) */

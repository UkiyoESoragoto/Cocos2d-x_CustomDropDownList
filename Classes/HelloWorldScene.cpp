#include "HelloWorldScene.h"
#include "DropDownList.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visible_size = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto close_item = MenuItemImage::create("CloseNormal.png",
                                            "CloseSelected.png",
                                            CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	close_item->setPosition(Vec2(origin.x + visible_size.width - close_item->getContentSize().width/2 ,
                                 origin.y + close_item->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(close_item, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("请问魏钲是什么？", "Arial", 24);
    
    // position the label on the center of the screen
//    label->setPosition(Vec2(origin.x + visible_size.width/2,
//                            origin.y + visible_size.height - label->getContentSize().height));
    auto box_size = Size(80.0,
                         30.0);
    
    auto list_box = CustomDropDownListBox::DropDownList::Create(label,
                                                                box_size);
    
    auto label1 = LabelTTF::create("是基佬",
                                   "Arial",
                                   22);
    list_box->AddLabel(label1);
    
    auto label2 = LabelTTF::create("是基佬！",
                                   "Arial",
                                   22);
    list_box->AddLabel(label2);
    
    auto label3 = LabelTTF::create("都说了是基佬你不无聊么！",
                                   "Arial",
                                   22);
    list_box->AddLabel(label3);
    
    list_box->setPosition(200,
                          300);
    
    this->addChild(list_box,
                   2);
    
    list_box->init();

    // add the label as a child to this layer
//    this->addChild(label, 1);
//
//    // add "HelloWorld" splash screen"
//    auto sprite = Sprite::create("HelloWorld.png");
//
//    // position the sprite on the center of the screen
//    sprite->setPosition(Vec2(visible_size.width/2 + origin.x, visible_size.height/2 + origin.y));
//
//    // add the sprite as a child to this layer
//    this->addChild(sprite, 0);
    
    
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

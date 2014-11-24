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
    
    auto label = LabelTTF::create("Make a Choice", "Arial", 24);
    
    auto box_size = Size(100.0,
                         30.0);
    
    auto list_box = CustomDropDownListBox::DropDownList::Create(label,
                                                                box_size);
    
    //添加一堆label进去
    auto label1 = LabelTTF::create("IOS",
                                   "Arial",
                                   22);
    list_box->AddLabel(label1);
    auto label2 = LabelTTF::create("Android",
                                   "Arial",
                                   22);
    list_box->AddLabel(label2);
    auto label3 = LabelTTF::create("Windows Phone",
                                   "Arial",
                                   22);
    list_box->AddLabel(label3);
    list_box->setPosition(200,
                          300);
    
    // 设置位置
    list_box->setPosition(Vec2(origin.x + visible_size.width / 2 - list_box->getContentSize().width / 2,
                               origin.y + visible_size.height / 2 - list_box->getContentSize().height / 2));
    
    this->addChild(list_box,
                   2);
    
    //很奇特的调用，目前看来是必须的，还不太了解init()函数的机制。难道不该是自动的么魂淡
    list_box->init();

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

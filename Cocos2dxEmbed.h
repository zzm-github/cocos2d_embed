#ifndef  _COCOS2DX_EMBED_H_
#define  _COCOS2DX_EMBED_H_

#include "platform/CCApplication.h"

using namespace std;

/**
 @brief    The cocos2d Application.

 The reason for implement as private inheritance is to hide some interface call by Director.
 */
class Cocos2dxEmbed : public cocos2d::Application
{
public:
    Cocos2dxEmbed();
    virtual ~Cocos2dxEmbed();
    
    void initConfig(string mainJs);

    void initGLContextAttrs() override;

    /**
     @brief    Implement Director and Scene init code here.
     @return true    Initialize success, app continue.
     @return false   Initialize failed, app terminate.
     */
    virtual bool applicationDidFinishLaunching();

    /**
     @brief  The function be called when the application enter background
     @param  the pointer of the application
     */
    virtual void applicationDidEnterBackground();

    /**
     @brief  The function be called when the application enter foreground
     @param  the pointer of the application
     */
    virtual void applicationWillEnterForeground();
    
    virtual void pauseDirector();
    
    virtual void resumeDirector();
    
    virtual void end();
    
protected:
    string mainJs;
};

#endif // _COCOS2DX_EMBED_H_

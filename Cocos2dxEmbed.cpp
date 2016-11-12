#include "Cocos2dxEmbed.h"

#include "platform/CCGLView.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "platform/ios/CCGLViewImpl-ios.h"
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/CCGLViewImpl-android.h"
#endif // CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#include "base/CCDirector.h"
#include "base/CCEventDispatcher.h"
#include "SimpleAudioEngine.h"

#include "js_module_register.h"

USING_NS_CC;
using namespace std;
using namespace CocosDenshion;

Cocos2dxEmbed::Cocos2dxEmbed()
{
}

Cocos2dxEmbed::~Cocos2dxEmbed()
{
    ScriptEngineManager::destroyInstance();
}

void Cocos2dxEmbed::initConfig(string mainJs)
{
    this->mainJs = mainJs;
}

void Cocos2dxEmbed::initGLContextAttrs()
{
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
    GLView::setGLContextAttrs(glContextAttrs);
}

bool Cocos2dxEmbed::applicationDidFinishLaunching()
{
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::createWithRect("Cocos2dxEmbed", Rect(0,0,900,640));
        director->setOpenGLView(glview);
    }

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    js_module_register();

    ScriptingCore* sc = ScriptingCore::getInstance();
    sc->start();
    sc->runScript("script/jsb_boot.js");
#if defined(COCOS2D_DEBUG) && (COCOS2D_DEBUG > 0)
    sc->enableDebugger();
#endif
    ScriptEngineManager::getInstance()->setScriptEngine(sc);
    ScriptingCore::getInstance()->runScript(this->mainJs);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void Cocos2dxEmbed::applicationDidEnterBackground()
{
    auto director = Director::getInstance();
    director->stopAnimation();
    director->getEventDispatcher()->dispatchCustomEvent("game_on_hide");
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
}

// this function will be called when the app is active again
void Cocos2dxEmbed::applicationWillEnterForeground()
{
    auto director = Director::getInstance();
    director->startAnimation();
    director->getEventDispatcher()->dispatchCustomEvent("game_on_show");
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeAllEffects();
}

void Cocos2dxEmbed::pauseDirector()
{
    Director::getInstance()->pause();
}

void Cocos2dxEmbed::resumeDirector()
{
    Director::getInstance()->resume();
}

void Cocos2dxEmbed::end()
{
    Director::getInstance()->end();
}

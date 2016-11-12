
#import "Cocos2dxUIViewController.h"
#import "Cocos2dxEmbed.h"
#import "cocos2d.h"
#import "platform/ios/CCEAGLView-ios.h"
#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

int runCount = 0;

@implementation Cocos2dxUIViewController

- (void)viewDidLoad {
    
    runCount ++;
    
    if(runCount >= 2) {
        delete cocos2d::Director::getInstance();
    }
    
    CCEAGLView *eaglView = [CCEAGLView viewWithFrame: [[UIScreen mainScreen] bounds]
                                         pixelFormat: kEAGLColorFormatRGBA8
                                         depthFormat: GL_DEPTH24_STENCIL8_OES
                                  preserveBackbuffer: NO
                                          sharegroup: nil
                                       multiSampling: NO
                                     numberOfSamples: 0 ];

    [eaglView setMultipleTouchEnabled:YES];

    // Use RootViewController manage CCEAGLView
    self.wantsFullScreenLayout = YES;
    self.view = eaglView;

    [[UIApplication sharedApplication] setStatusBarHidden: YES];

    cocos2d::GLView *glview = cocos2d::GLViewImpl::createWithEAGLView((__bridge void *) eaglView);
    cocos2d::Director::getInstance()->setOpenGLView(glview);

    cocos2d::Application::getInstance()->run();
    
    UIButton *button = [UIButton buttonWithType:UIButtonTypeCustom];
    [button addTarget:self action:@selector(onCloseBtnClick:)
     forControlEvents:UIControlEventTouchUpInside];
    [button setTitle:@"Close" forState:UIControlStateNormal];
    button.frame = CGRectMake(80.0, 210.0, 160.0, 40.0);
    [eaglView addSubview:button];
}

// Override to allow orientations other than the default portrait orientation.
// This method is deprecated on ios6
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    return UIInterfaceOrientationIsLandscape( interfaceOrientation );
}

// For ios6, use supportedInterfaceOrientations & shouldAutorotate instead
- (NSUInteger) supportedInterfaceOrientations{
#ifdef __IPHONE_6_0
    return UIInterfaceOrientationMaskAllButUpsideDown;
#endif
}

- (BOOL) shouldAutorotate {
    return YES;
}

- (void)didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation {
    [super didRotateFromInterfaceOrientation:fromInterfaceOrientation];

    cocos2d::GLView *glview = cocos2d::Director::getInstance()->getOpenGLView();
    if (glview)
    {
        CCEAGLView *eaglview = (__bridge CCEAGLView*)glview->getEAGLView();

        if (eaglview)
        {
            CGSize s = CGSizeMake([eaglview getWidth], [eaglview getHeight]);
            cocos2d::Application::getInstance()->applicationScreenSizeChanged((int) s.width, (int) s.height);
        }
    }
}

//fix not hide status on ios7
- (BOOL)prefersStatusBarHidden {
    return YES;
}

- (void)didReceiveMemoryWarning {
    cocos2d::Director::getInstance()->purgeCachedData();
}

- (void)viewDidDisappear:(BOOL)animated {
    cocos2d::Director::getInstance()->end();
    Cocos2dxEmbed::destroyInstance();
}

- (void)viewDidUnload {
    [super viewDidUnload];
}

- (void)onCloseBtnClick:(UIButton*)sender {
    [self dismissViewControllerAnimated:YES completion:nil];
}

@end

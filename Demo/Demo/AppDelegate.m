//
//  AppDelegate.m
//  abtest_demo
//
//  Created by kerrydong on 2019/7/12.
//  Copyright © 2019 kerrydong. All rights reserved.
//

#import "AppDelegate.h"
#import <romaabtest/RomaABSDK.h>

@implementation AppDelegate


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.
    
    NSString *reportUrl = [[NSUserDefaults standardUserDefaults] objectForKey:@"reportUrl"];
    NSString *strategyUrl = [[NSUserDefaults standardUserDefaults] objectForKey:@"strategyUrl"];
    NSString *appid = [[NSUserDefaults standardUserDefaults] objectForKey:@"appid"];
    NSString *userid = [[NSUserDefaults standardUserDefaults] objectForKey:@"userid"];
    
    dispatch_queue_t serialQueue = dispatch_queue_create("initQueue", DISPATCH_QUEUE_SERIAL);
    
    dispatch_async(serialQueue, ^{
        
        [RomaABSDK setLogLevel:10];
        
        // 初始化实验相关
        if (reportUrl.length == 0 && strategyUrl.length == 0)
        {
            // 公有云接入，走默认saas地址，无需自己设置
            [[RomaABSDK defaultSDK] initWithAppKey:appid
                                            userId:userid
                                  completeHandler:^(BOOL result) {
                NSLog(@"Saas roma AB Iint %d", result);
            }];
        }
        else {
            // 私有化部署，必须设置上报服务地址和拉取实验服务地址
            [[RomaABSDK defaultSDK] initWithReportUrl:reportUrl
                                          strategyUrl:strategyUrl
                                               AppKey:appid
                                               userId:userid
                                      completeHandler:^(BOOL result) {
                NSLog(@"Private roma AB Iint %d", result);
            }];
        }
        
    });
    
  
    
    return YES;
}

@end

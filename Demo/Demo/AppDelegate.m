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
    
    NSString *appid = [[NSUserDefaults standardUserDefaults] objectForKey:@"appid"];
    NSString *userid = [[NSUserDefaults standardUserDefaults] objectForKey:@"userid"];
    
    dispatch_queue_t serialQueue = dispatch_queue_create("initQueue", DISPATCH_QUEUE_SERIAL);
    
    dispatch_async(serialQueue, ^{
        
        [[RomaABSDK defaultSDK] setUseTest:FALSE];
        [RomaABSDK setLogLevel:10];
        
        // 初始化实验相关
        [[RomaABSDK defaultSDK] initWithAppKey:appid
                                        userId:userid
                              completeHandler:^(BOOL result) {
            NSLog(@"Roma AB Iint %d", result);
            
        }];
        
    });
    
  
    
    return YES;
}

@end

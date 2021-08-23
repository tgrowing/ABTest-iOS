//
//  ViewController.m
//  abtest_demo
//
//  Created by kerrydong on 2019/7/12.
//  Copyright © 2019 kerrydong. All rights reserved.
//

#import "ViewController.h"
#import <romaabtest/RomaABSDK.h>
#import <romaabtest/RomaDefaultConfig.h>


@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    NSString *appid = [[NSUserDefaults standardUserDefaults] objectForKey:@"appid"];
    NSString *userid = [[NSUserDefaults standardUserDefaults] objectForKey:@"userid"];
    self.appidTextField.text = appid;
    self.useridTextField.text = userid;
    
    [RomaDefaultConfig defaultConfig];
}

- (IBAction) testBtnClick:(id)sender {
    NSString *expName = self.testTextField.text;
    RomaExp* exp = [[RomaABSDK defaultSDK] getCachedExpAndReport:expName];
    self.resultLabel.text = [exp description];
}


- (IBAction) testBtn2Click:(id)sender {
    NSString *expName = self.testTextField2.text;
    [[RomaABSDK defaultSDK] getExpByNameWithReport:expName completeHandler:^(RomaExp* exp) {
        dispatch_async(dispatch_get_main_queue(), ^{
            self.resultLabel.text = [exp description];
        });
    }];
}

- (IBAction) testBtn3Click:(id)sender {
    NSString *userid = self.testTextField3.text;
    [[RomaABSDK defaultSDK] switchUser:userid completeHandler:^(BOOL rst) {
        dispatch_async(dispatch_get_main_queue(), ^{
            self.resultLabel.text = [NSString stringWithFormat:@"切换用户%@", rst ? @"成功" : @"失败"];
        });
    }];
}


- (IBAction)onSaveButtonClick:(UIButton *)sender {
    NSString *appid = self.appidTextField.text;
    NSString *userid = self.useridTextField.text;
    
    [[NSUserDefaults standardUserDefaults] setObject:appid forKey:@"appid"];
    [[NSUserDefaults standardUserDefaults] setObject:userid forKey:@"userid"];
    [[NSUserDefaults standardUserDefaults] synchronize];
}


@end

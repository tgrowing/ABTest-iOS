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
    
    NSString *reportUrl = [[NSUserDefaults standardUserDefaults] objectForKey:@"reportUrl"];
    NSString *strategyUrl = [[NSUserDefaults standardUserDefaults] objectForKey:@"strategyUrl"];
    NSString *appid = [[NSUserDefaults standardUserDefaults] objectForKey:@"appid"];
    NSString *userid = [[NSUserDefaults standardUserDefaults] objectForKey:@"userid"];
    
    self.reportUrlTextField.text = reportUrl;
    self.strategyUrlTextField.text = strategyUrl;
    self.appidTextField.text = appid;
    self.useridTextField.text = userid;
    
    [RomaDefaultConfig defaultConfig];
}

- (IBAction) testBtnClick:(id)sender {
    NSString *expName = self.testTextField.text;
    RomaExp* exp = [[RomaABSDK defaultSDK] getCachedExpAndReport:expName];
    self.resultLabel.text = [exp description];
    [self.testTextField resignFirstResponder];
}


- (IBAction) testBtn2Click:(id)sender {
    NSString *expName = self.testTextField2.text;
    [[RomaABSDK defaultSDK] getExpByNameWithReport:expName completeHandler:^(RomaExp* exp,NSString *errMsg) {
        dispatch_async(dispatch_get_main_queue(), ^{
            self.resultLabel.text = [exp description];
        });
    }];
    [self.testTextField2 resignFirstResponder];
}

- (IBAction) testBtn3Click:(id)sender {
    NSString *userid = self.testTextField3.text;
    [[RomaABSDK defaultSDK] switchUser:userid completeHandler:^(BOOL rst, NSString *errMsg) {
        dispatch_async(dispatch_get_main_queue(), ^{
            self.resultLabel.text = [NSString stringWithFormat:@"切换用户%@", rst ? @"成功" : @"失败"];
        });
    }];
    [self.testTextField3 resignFirstResponder];
}


- (IBAction)onSaveButtonClick:(UIButton *)sender {
    NSString *reportUrl = self.reportUrlTextField.text;
    NSString *strategyUrl = self.strategyUrlTextField.text;
    NSString *appid = self.appidTextField.text;
    NSString *userid = self.useridTextField.text;
    
    [[NSUserDefaults standardUserDefaults] setObject:reportUrl forKey:@"reportUrl"];
    [[NSUserDefaults standardUserDefaults] setObject:strategyUrl forKey:@"strategyUrl"];
    [[NSUserDefaults standardUserDefaults] setObject:appid forKey:@"appid"];
    [[NSUserDefaults standardUserDefaults] setObject:userid forKey:@"userid"];
    [[NSUserDefaults standardUserDefaults] synchronize];
    
    [self.reportUrlTextField resignFirstResponder];
    [self.strategyUrlTextField resignFirstResponder];
    [self.appidTextField resignFirstResponder];
    [self.useridTextField resignFirstResponder];
    
    // 保存后主动退出，避免测试未手动重启。
    exit(1);
}

- (IBAction)onEventButtonClick:(id)sender {
    NSString *expName = self.testTextField2.text;
    NSString *event = self.eventCodeTextField.text;
    NSLog(@"eventBtnClicked, expName:%@, event:%@", expName, event);
    [[RomaABSDK defaultSDK] getExpByName:expName completeHandler:^(RomaExp* exp,NSString *errMsg) {
        dispatch_async(dispatch_get_main_queue(), ^{
            NSLog(@"eventBtnClicked, exp:%@", exp);
            [[RomaABSDK defaultSDK] reportExpAction:event withExp:exp];
            self.resultLabel.text = [NSString stringWithFormat:@"exp: %@, event: %@", [exp description], event];
        });
    }];
    [self.eventCodeTextField resignFirstResponder];
}

@end

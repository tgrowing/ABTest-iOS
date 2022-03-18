//
//  ViewController.h
//  abtest_demo
//
//  Created by kerrydong on 2019/7/12.
//  Copyright © 2019 kerrydong. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ViewController : UIViewController

@property (weak, nonatomic) IBOutlet UITextField *reportUrlTextField;

@property (weak, nonatomic) IBOutlet UITextField *strategyUrlTextField;

@property (weak, nonatomic) IBOutlet UITextField *testTextField;

@property (weak, nonatomic) IBOutlet UITextField *testTextField2;

@property (weak, nonatomic) IBOutlet UITextField *testTextField3;

@property (weak, nonatomic) IBOutlet UITextField *appidTextField;

@property (weak, nonatomic) IBOutlet UITextField *useridTextField;

@property (weak, nonatomic) IBOutlet UITextField *eventCodeTextField;

@property (weak, nonatomic) IBOutlet UIButton *saveBtn;

@property (weak, nonatomic) IBOutlet UILabel *resultLabel;

@end


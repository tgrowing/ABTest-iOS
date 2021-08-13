//
//  ViewController.h
//  abtest_demo
//
//  Created by kerrydong on 2019/7/12.
//  Copyright © 2019 kerrydong. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ViewController : UIViewController
// btn
@property (weak, nonatomic) IBOutlet UIButton *testBtn;
// btn
@property (weak, nonatomic) IBOutlet UIButton *testBtn2;
// btn
@property (weak, nonatomic) IBOutlet UIButton *testBtn3;

@property (weak, nonatomic) IBOutlet UITextField *testTextField;

@property (weak, nonatomic) IBOutlet UITextField *testTextField2;

@property (weak, nonatomic) IBOutlet UITextField *testTextField3;

@property (weak, nonatomic) IBOutlet UITextField *appidTextField;

@property (weak, nonatomic) IBOutlet UITextField *useridTextField;

@property (weak, nonatomic) IBOutlet UIButton *saveBtn;

@property (weak, nonatomic) IBOutlet UILabel *resultLabel;

@end


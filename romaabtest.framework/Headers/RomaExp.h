//
//  RomaExp.h
//  romaabtest
//
//  Created by kerrydong on 2020/1/27.
//  Copyright © 2020 kerrydong. All rights reserved.
//

/**
 TAB实验数据
 */
@interface RomaExp : NSObject<NSSecureCoding> {
    long grayId;
    NSString* layerCode;
    NSMutableDictionary* params;
    BOOL isFirstHit;
    
    NSString* expName;
    NSString* assignment;
    
    int percentage;
    int bucket;
}
// 所在分层的Code  2、这个就是字典的key
@property (nonatomic, retain) NSString* layerCode;
// 实验的参数
@property (nonatomic, retain) NSMutableDictionary* params;
//1、这个就是sGrayPolicyId
@property (nonatomic, assign) long grayId;
 // 是否首次命中（之前未产生过曝光） 3、这个也没找到
@property (nonatomic, assign) BOOL isFirstHit;
// 实验的流量设置
@property (nonatomic, assign) int percentage;
// 用户所在的实验桶
@property (nonatomic, assign) int bucket;
// 实验组名称
@property (nonatomic, retain) NSString* expName;
 // 实验版本 control, treatment1, treatment2 ...
@property (nonatomic, retain) NSString* assignment;


@end

//
//  RomaABDef.h
//  romaabtest
//
//  Created by kerrydong on 2020/3/16.
//  Copyright © 2020 kerrydong. All rights reserved.
//
#import "RomaExp.h"

#ifndef RomaABDef_h
#define RomaABDef_h

typedef enum {
    User_Unit_Type_UserId = 0, // 用户id
    User_Unit_Type_DeviceId = 1, // 设备id
} User_Unit_Type;

// 默认实验标志，如果未命中任何实验， 则返回对象RomaExp中的assignment是这个值
#define DEFAULT_EXP_ASSIGNMENT @"default"

// 请求完成的回调，结果中会通知请求是否成功
typedef void (^RomaRequestFinish)(BOOL result, NSString *errMsg);
// 异步加载实验请求回调，会返回一个实验对象（失败返回缓存的对象，缓存无则返回默认对象）
typedef void (^RomaLoadExpFinish)(RomaExp *exp, NSString *errMsg);

#endif /* RomaABDef_h */

//
//  RomaDefatutConfig.h
//  romaabtest
//
//  Created by bluetan on 2020/11/3.
//  Copyright © 2020 kerrydong. All rights reserved.
//


#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface RomaDefaultConfig : NSObject

/// 默认配置
+ (instancetype)defaultConfig;

- (instancetype)init NS_UNAVAILABLE;

/// 获取BOOL类型配置值
- (BOOL)romaConfigBoolValue:(NSString *)key;

/// 获取int32_t类型配置值
- (int32_t)romaConfigInt32Value:(NSString *)key;

/// 获取uint32_t类型配置值
- (uint32_t)romaConfigUInt32Value:(NSString *)key;

/// 获取int64_t类型配置值
- (int64_t)romaConfigInt64Value:(NSString *)key;

/// 获取uint64_t类型配置值
- (uint64_t)romaConfigUInt64Value:(NSString *)key;

/// 获取float类型配置值
- (float)romaConfigFloatValue:(NSString *)key;

/// 获取double类型配置值
- (double)romaConfigDoubleValue:(NSString *)key;

/// 获取NSString类型配置值
- (NSString *)romaConfigStringValue:(NSString *)key;


@end

NS_ASSUME_NONNULL_END

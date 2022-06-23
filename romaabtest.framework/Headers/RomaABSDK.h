//
//  RomaABSDK.h
//  romaabtest
//
//  Created by kerrydong on 2019/11/25.
//  Copyright © 2019 kerrydong. All rights reserved.
//

#import "RomaABDef.h"

NS_ASSUME_NONNULL_BEGIN

@interface RomaABSDK : NSObject

/**
 初始化TAB实验SDK
 */

// 日志级别，比如10
+(void) setLogLevel:(int) level;

// 获取默认sdk实例
+(RomaABSDK*) defaultSDK;

// 设置一个单独的key，获取一个对应的实例。主要是支持多个业务使用SDK
+(RomaABSDK*) getInstance:(NSString*) instanceKey;

/**
 * 初始化sdk
 * 上报地址和策略实验服务默认为公有云SAAS地址
 * appkey, 从abtest.qq.com平台获取，userid代表用户身份标识
 * guid默认为User_Unit_Type_UserId，可以通过接口设置为User_Unit_Type_Qimei
 */
-(bool) initWithAppKey:(NSString*) appKey
                userId:(NSString*) userId;

/**
 * 初始化sdk
 * 上报地址和策略实验服务为私有化部署
 * appkey, 从abtest.qq.com平台获取，userid代表用户身份标识
 * guid默认为User_Unit_Type_UserId，可以通过接口设置为User_Unit_Type_Qimei
 */
-(bool) initWithReportUrl:(NSString *)reportUrl
              strategyUrl:(NSString *)strategyUrl
                   AppKey:(NSString *)appKey
                   userId:(NSString *)userId;

// with callback
- (bool)initWithAppKey:(NSString *)appKey
                userId:(NSString *)userId
       completeHandler:(RomaRequestFinish)handler;

-(bool) initWithReportUrl:(NSString *)reportUrl
              strategyUrl:(NSString *)strategyUrl
                   AppKey:(NSString *)appKey
                   userId:(NSString *) userId
          completeHandler:(RomaRequestFinish)handler;

// 是否初始化完成
- (bool) isInited;

// 设置用户类型，默认是用户id类型，可以换成Qimei这种设备id类型
// TAB平台上配置实验支持按照用户类型配置，不同的类型获取到的实验不一样
/**
 在一些应用的首屏，用户可能还没有登录，为了完成实验的覆盖，一般可以采用设备id类型的o用户体系
 如果有这两类的体系实验，建议使用两个sdk实例完成，做不同类型的实验的实验使用不同的sdk实例完成
 例如：
 RomaABSDK* userSDK = [RomaABSDK getInstance:@"userType"];
 [userSDK initWithAppKey:@"***" userId:@"1234456"];
 
 RomaABSDK* deviceSDK = [RomaABSDK getInstance:@"deviceType"];
 [deviceSDK setUserUnitType:User_Unit_Type_DeviceId];
 [deviceSDK initWithAppKey:@"***" userId:@"abc-deg-ddd"];
 */
- (void) setUserUnitType:(User_Unit_Type) type;

// 设置用户profile, 用户的标签属性，可以用来设置标签实验
// 必须在init之前调用，或者调用一次forceUpdateExps来更新策略
-(void) setProfiles: (NSDictionary*) profiles;

// 设置用户profile， key/value， 例如sexy:male, age:10
-(void) setProfileWithKey:(NSString*) key value:(NSString*) val;

// 强制发起一次网络策略拉取
-(void) forceUpdateExps:(RomaRequestFinish _Nullable) handler;

// 切换用户id, 比如用户切换账号登录，则清空实验缓存，重新拉取实验配置
// 注意，设备类似的实例，不允许切换，TAB平台认为设备id是不可变的
-(void) switchUser:(NSString*) userId
   completeHandler:(RomaRequestFinish _Nullable) handler;

/**
获取实验API
*/

// TABC实验平台使用expName标识实验Id，通过assignment标识实验版本
/**
 建议使用如下方式完成实验逻辑：
 // 如果需要自己实验的时机，可以使用getExpByName，然后调用reportExpExpose接口上报实验曝光
 // 比如提前预取到实验对象，但在后续的某个时机再去做实验，那么在做实验的时机上报曝光是合理的
 [sdk getExpByNameWithReport:@"myExpTest" completeHandler^(RomaExp* exp] {
     if ([exp.assignment isEqualTo:@"MyExpTestVersionA"]) {
        // 实现实验版本A的逻辑
        // update View on UIThread or other logic
     } else if ([exp.assignment isEqualTo:@"MyExpTestContorlVersion"]) {
        // 实验实验对照版本的逻辑
        // update View on UIThread or other logic
     } else {
        // 默认版本的逻辑
     }
 }];
 */
// 从缓存中获取实验，如果没有则异步从后台请求实验数据，并上报一次实验曝光
-(void) getExpByNameWithReport:(NSString*) expName
               completeHandler:(RomaLoadExpFinish _Nullable) handler;
// 从缓存中获取实验，如果没有则异步从后台请求实验数据
-(void) getExpByName:(NSString*) expName
     completeHandler:(RomaLoadExpFinish) handler;

/**
 曝光上报API
 */
//上报一次实验曝光
-(void) reportExpExpose:(RomaExp*) exp;
// 上报一次实验反馈事件
/**
 一般 用户反馈行为事件已经在灯塔上报事件里面，可以有TAB拉取灯塔的事件做分析，不建议单独上报一份
 */
-(void) reportExpAction:(NSString*) eventCode withExp:(RomaExp*) exp;

/**
其他API支持
*/

// 设置launchOptions，可以用一些用户启动状态（用户启动，通知启动）等作为实验标签
-(void) setLaunchOptions: (NSDictionary*) launchOptions;
// 设置加载策略的layerCode， 请求策略的时候会只请求这几个layerCode的策略.
// 必须在init之前调用，或者调用一次forceUpdateExps来更新策略
-(void) setLayerCodes:(NSArray*) layerCodes;
// 设置渠道
-(void) setChannelCode:(NSString*) channelCode;
// 设置请求超时时间
-(void) setReqTimeout:(int) timeout;

// 获取缓存中的所有的实验信息。key为layerCode， 只为RomaExp
-(NSDictionary*) getAllExps;
// 从缓存中获取expName的实验，并上报一次实验曝光
-(RomaExp*) getCachedExpAndReport: (NSString*) expName;
// 从缓存中获取expName的实验, 但不会上报实验曝光.
-(RomaExp*) getCachedExp: (NSString*) expName;
// 从缓存中获取实验id的实验，并上报一次曝光
-(RomaExp*) getExpByGrayIdAndReport: (long) grayId;
// 从缓存中获取实验id的实验，但不会上报实验曝光
-(RomaExp*) getExpByGrayId: (long) grayId;
// 从缓存中获取分层Code的实验，并上报一次曝光
-(RomaExp*) getExpByLayerCodeAndReport: (NSString*) layerCode;
// 从缓存中获取分层Code的实验，但不会上报实验曝光
-(RomaExp*) getExpByLayerCode: (NSString*) layerCode;

// 用户上报通道，默认采用atta自建通道
+ (void)setEnableBeacon:(bool)enable __attribute__((deprecated("Use atta channel instead")));
+ (bool)getEnableBeacon __attribute__((deprecated("Use atta channel instead")));

@end

NS_ASSUME_NONNULL_END

# ABTest-iOS

## 环境
* iOS 9.0+
* Xcode 10.0+

## SDK集成
SDK提供两种集成方式供iOS开发者选择：
- 通过CocoaPods集成
- 手动集成 ABTest iOS SDK 

### 通过 CocoaPods 安装，在 podfile 里添加：

```objc
pod 'tgpABTest', '~> x.x.x'
// 如：
pod 'tgpABTest', '~> 2.1.0'
```
### 手动集成
1. 拖拽 romaabtest.framework文件到Xcode工程内(请勾选Copy items if neeeded)
2. 添加依赖库 SystemConfiguration.framework Security.framework

## SDK使用

### 导入头文件

在工程的AppDelegate.m文件导入头文件

```objc
#import <romaabtest/RomaABSDK.h>
```
如果是Swift工程，请在对应bridging-header.h中导入

### 初始化RomaABTest

在工程AppDelegate.m的application:didFinishLaunchingWithOptions:方法中初始化：

```objc
// 初始化sdk, appkey, 从abtest.qq.com平台获取，userid代表用户身份标识
// guid默认为User_Unit_Type_UserId，可以通过接口设置为User_Unit_Type_Qimei
[RomaABSDK defaultSDK] initWithAppKey:@"具体的appkey" 
                               userId:@"用户的唯一id"]; 

// 初始化sdk, 带有加载数据完成的回调
[[RomaABSDK defaultSDK] initWithAppKey:@"具体的appkey" 
                                userId:@"用户的唯一id"
                      completeHandler:
^(BOOL result,NSString *errMsg)) {
    NSLog(@"SDK加载实验数据完成 %d,errMsg: %@", result,errMsg);
}];


// 如果用户发生登陆切换，可以调用该APi
[[RomaABSDK defaultSDK] switchUser:@"newUserId" completeHandler:^(BOOL result,NSString *errMsg) {
    NSLog(@"SDK切换实验数据完成 %d,errMsg:%@", result,errMsg);
}];
```

### 获取实验数据

1. 通过实验标识获取实验数据，并上报一次实验曝光。

```objc
// 该调用会首先从缓存中获取实验，没有缓存的话则发起一次异步的调用，并在拿到结果后回调
[sdk getExpByNameWithReport:@"具体的实验id" completeHandler^(RomaExp* exp, NSString *errMsg] {
    // 以下是命中对应实验的TODO
    if ([exp.assignment isEqualTo:@"具体的实验版本"]) {
        // 实现实验版本A的逻辑
        // update View on UIThread or other logic
    } else if ([exp.assignment isEqualTo:@"具体的实验版本2"]) {
        // 实验实验对照版本的逻辑
        // update View on UIThread or other logic
    } else {
        // 默认版本的逻辑
    }
}];

```

2. 通过实验标识获取实验数据，不会上报实验曝光。

```objc
// 该调用会首先从缓存中获取实验，没有缓存的话则发起一次异步的调用，并在拿到结果后回调
[sdk getExpByName:@"具体的实验id" completeHandler^(RomaExp* exp, NSString *errMsg) {
     // 以下是命中对应实验的TODO
    if ([exp.assignment isEqualTo:@"具体的实验版本"]) {
        // 实现实验版本A的逻辑
        // update View on UIThread or other logic
    } else if ([exp.assignment isEqualTo:@"具体的实验版本2"]) {
        // 实验实验对照版本的逻辑
        // update View on UIThread or other logic
    } else {
        // 默认版本的逻辑
    }
}];
```

3. 只从缓存中获取实验数据，不会发起异步请求。

```objc
RomaExp* exp = [[RomaABSDK defaultSDK] getCachedExpAndReport:@"具体的实验id"]; // 上报一次曝光
RomaExp* exp = [[RomaABSDK defaultSDK] getCachedExp:@"具体的实验id"]; // 不上报曝光
```

### 上报事件

1. 上报实验曝光

```objc
[[RomaABSDK defaultSDK] reportExpExpose:exp];
```

2. 上报实验反馈事件

```objc
[[RomaABSDK defaultSDK] reportExpAction:@"具体的实验code" withExp:exp];
```
### 以上数据对应的位置
① 具体的appkey
![image.png](https://tencent-growth-platform-1251316161.cos.ap-beijing.myqcloud.com/sdk/images/abtest_sdk/abtest_ios_step_1.png)
② 具体的实验id
![image.png](https://tencent-growth-platform-1251316161.cos.ap-beijing.myqcloud.com/sdk/images/abtest_sdk/abtest_ios_step_2.png)
③ 具体的实验版本
![image.png](https://tencent-growth-platform-1251316161.cos.ap-beijing.myqcloud.com/sdk/images/abtest_sdk/abtest_ios_step_3.png)
④  具体的事件code：
![image.png](https://tencent-growth-platform-1251316161.cos.ap-beijing.myqcloud.com/sdk/images/abtest_sdk/abtest_ios_step_4.png)
##  License

ISC

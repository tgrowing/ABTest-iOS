# tgpABTest

## 环境
* iOS 9.0+
* Xcode 10.0+

## SDK集成

* 通过 CocoaPods 安装，在 podfile 里添加：

```
pod 'tgpABTest', '~> x.x.x'
```

## SDK使用

### 导入头文件

在工程的AppDelegate.m文件导入头文件

```
#import <romaabtest/RomaABSDK.h>
```
如果是Swift工程，请在对应bridging-header.h中导入

### 初始化RomaABTest

在工程AppDelegate.m的application:didFinishLaunchingWithOptions:方法中初始化：

```
// 初始化，并从本地缓存中加载实验数据完成
[RomaABSDK defaultSDK] initWithAppId:@"TAB appid" 
                                guid:@"用户userid"]; 

// 带有加载数据完成的回调
[[RomaABSDK defaultSDK] initWithAppId:@"TAB appid" 
                                 guid:@"用户userid"
                      completeHandler:
^(BOOL result) {
    NSLog(@"SDK加载实验数据完成 %d", result);
}];


// 如果用户发生登陆切换，可以调用该APi
[sdk switchUser:@"newUserId" completeHandler:^(BOOL result) {
    NSLog(@"SDK切换实验数据完成 %d", result);
}];
```

### 获取实验数据

1. 通过实验标识获取实验数据，并上报一次实验曝光。

```
// 该调用会首先从缓存中获取实验，没有缓存的话则发起一次异步的调用，并在拿到结果后回调
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

```

2. 通过实验标识获取实验数据，不会上报实验曝光。

```
[sdk getExpByName:@"myExpTest" completeHandler^(RomaExp* exp] {
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
```

3. 只从缓存中获取实验数据，不会发起异步请求。

```
RomaExp* exp = [[RomaABSDK defaultSDK] getCachedExpAndReport:@"myExpTest"]; // 上报一次曝光
RomaExp* exp = [[RomaABSDK defaultSDK] getCachedExp:@"myExpTest"]; // 不上报曝光
```

### 上报事件

SDK会默认上报实验曝光事件，其他事件建议使用灯塔SDK进行上报，TAB会在后台打通实验数据。
如果业务并未使用灯塔SDK，或者有其他需求，仍旧可以手动调用接口上报实验曝光和实验事件。

1. 上报实验曝光

```
[[RomaABSDK defaultSDK] reportExpExpose:exp];
```

2. 上报实验事件

```
[[RomaABSDK defaultSDK] reportExpAction:@"eventCode" withExp:exp];
```

### 只拉取部分layer的实验策略

```
// 请在 sdk init前调用设置， 或者设置后再更新一次策略forceUpdateExps
// 如果实验平台的实验包括前后端的，可以通过这个功能只拉取部分实验策略，减少流量
[[RomaABSDK defaultSDK] setLayerCodes:
    [NSArray arrayWithObjects:@"mLayer1", @"mLayer2", @"mLayer3", @"mLayer4", @"mLayer5", nil]];
```

### 设置用户属性（标签实验）

```
// 请在 sdk init前调用设置， 或者设置后再更新一次策略forceUpdateExps
[[RomaABSDK defaultSDK] setProfileWithKey:@"sexy" value:@"male"];
[[RomaABSDK defaultSDK] setProfileWithKey:@"isLogin" value:@"true"];
[[RomaABSDK defaultSDK] setProfileWithKey:@"qq" value:@"37776292"];
```

SDK默认会设置一些属性，可以直接用来配置标签实验

```
    "ROMA_BUNDLE_NAME" : "abtest_demo",
    "ROMA_BUNDLE_SHORT_VER" : "1.0",
    "ROMA_DEV_RESOLUTION" : "414*896",
    "ROMA_PLATFORM" : "iOS",
    "ROMA_OS_VER" : "13.3 (18E227)",
    "ROMA_OS_MODEL" : "x86_64",
    "ROMA_BUNDLE_VER" : "1",
    "ROMA_OS_VER_FLOAT" : "13.3",
    "ROMA_BUNDLE_ID" : "com.tencent.roma.abtest-demo"
```

### 多实例

```
 // 在一些应用的首屏，用户可能还没有登录，为了完成实验的覆盖，一般可以采用设备id类型的o用户体系
 // 如果有这两类的体系实验，建议使用两个sdk实例完成，做不同类型的实验的实验使用不同的sdk实例完成
 // 例如：
 RomaABSDK* userSDK = [RomaABSDK getInstance:@"userType"];
 [userSDK initWIthAppId:@"***" appKey:@"***" guid:@"1234456"];
 
 RomaABSDK* deviceSDK = [RomaABSDK getInstance:@"deviceType"];
 [deviceSDK initWIthAppId:@"***" appKey:@"***" guid:@"abc-deg-ddd"];
```

## SDK 数据

### 包大小

静态库，大小为1Mb，包含arm64 armv7 i386 x86_64
测试应用(armv7 arm64)使用sdk增加189kb

### 内存消耗

iphone5, 测试应用，大约增加0.81Mb的内存消耗。
测试无Leak

### License

ISC

//
//  NetMonitor.h
//  NetworkStatus
//
//  Created by NooN on 2/11/22.
//

#import <Foundation/Foundation.h>
#import <SystemConfiguration/SystemConfiguration.h>

//! Project version number for MacOSReachability.
FOUNDATION_EXPORT double ReachabilityVersionNumber;

//! Project version string for MacOSReachability.
FOUNDATION_EXPORT const unsigned char ReachabilityVersionString[];

/**
 * Create NS_ENUM macro if it does not exist on the targeted version of iOS or OS X.
 *
 * @see http://nshipster.com/ns_enum-ns_options/
 **/
#ifndef NS_ENUM
#define NS_ENUM(_type, _name) enum _name : _type _name; enum _name : _type
#endif

extern NSString *const kReachabilityChangedNotification;

typedef NS_ENUM(NSInteger, NetworkStatus) {
    // Apple NetworkStatus Compatible Names.
    NotReachable = 0,
    ReachableViaWiFi = 2,
    ReachableViaWWAN = 1
};

@class NetMonitor;

typedef void (^NetworkReachable)(NetMonitor * reachability);
typedef void (^NetworkUnreachable)(NetMonitor * reachability);
typedef void (^NetworkReachability)(NetMonitor * reachability, SCNetworkConnectionFlags flags);


@interface NetMonitor : NSObject

@property (nonatomic, copy) NetworkReachable    reachableBlock;
@property (nonatomic, copy) NetworkUnreachable  unreachableBlock;
@property (nonatomic, copy) NetworkReachability reachabilityBlock;

@property (nonatomic, assign) BOOL reachableOnWWAN;


+(instancetype)reachabilityWithHostname:(NSString*)hostname;
+(instancetype)reachabilityWithHostName:(NSString*)hostname;
+(instancetype)reachabilityForInternetConnection;
+(instancetype)reachabilityWithAddress:(void *)hostAddress;
+(instancetype)reachabilityForLocalWiFi;
+(instancetype)reachabilityWithURL:(NSURL*)url;

-(instancetype)initWithReachabilityRef:(SCNetworkReachabilityRef)ref;

-(BOOL)startNotifier;
-(void)stopNotifier;

-(BOOL)isReachable;
-(BOOL)isReachableViaWWAN;
-(BOOL)isReachableViaWiFi;

-(BOOL)isConnectionRequired;
-(BOOL)connectionRequired;
-(BOOL)isConnectionOnDemand;
-(BOOL)isInterventionRequired;

-(NetworkStatus)currentReachabilityStatus;
-(SCNetworkReachabilityFlags)reachabilityFlags;
-(NSString*)currentReachabilityString;
-(NSString*)currentReachabilityFlags;

@end

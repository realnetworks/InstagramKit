//
//  StoryPlayer.h
//  RealTimesSDK
//
//  Created by Ante Trbojevic 1 on 10/06/15.
//  Copyright (c) 2015 RealNetworks. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@class RTStory;
@protocol RTPlaybackCompletionHandling;

/** This option specifies whether the RealTimes application should be automatically installed if it is not installed when playWithStory:options:handler:error:. The value in dictionary is BOOL.*/
extern NSString * const RTOptionAllowAutoInstall; //NSNumber of BOOL

/** This option allows you to pass an authentication token to the player. The value in dictionary is NSString.*/
extern NSString * const RTOptionAuthenticationToken; //NSString

/** This option allows you to specify the album where video should be stored in the camera roll when user saves a video file from a story (aka publishes a video) or when user shares a story. The value in dictionary is NSString.*/
extern NSString * const RTOptionSavedVideosAlbum; //NSString

/** This option allows you to pass the subscriber ID (MSISDN) to the player. The value in dictionary is NSString.*/
extern NSString * const RTOptionSubscriberId; //NSString

/** This option allows the host application to define own URL scheme so that RealTimes Player knows to send the response to the host app via the URL scheme. The value in dictionary is NSString.*/
extern NSString * const RTOptionHostAppURLScheme; //NSString

/** Use a RTStoryPlayer object to play back an existing and appropriately configured story.
 
 The story is played back with the help of the RealTimes activity. Consequently the RealTimes activity must be installed on the user's device in order to play back the story. You can check whether the RealTimes activity is installed by calling the isPlayerInstalled property and checking its return value.
 
 Call playWithStory:options:requestCode:handler: with a story to play back the story. You also pass a completion handler to this method which will be invoked once playback has finished and the user has indicated that he wants to return to your application. The completion handler is invoked with the story object that you passed to the playWithStory:options:handler:error: method.
 
 ***Using a story player***
 
 You typically create a RTStoryPlayer object right at the time that you want to play a story. You then check whether the RealTimes ViewController is installed on the device. Depending on the result of this call you can display an appropriate dialog to the user if the RealTimes ViewController is not installed. This dialog may offer the user an option to download and install the RealTimes ViewController. Once the installation process has completed or if the app was already installed on the device, you the proceed to call playWithStory:options:handler:error: with the desired story.
 
 The playWithStory:options:handler:error: call next packages up your story and it invokes the RealTimes activity with the packaged up story. The RealTimes ViewController then handles playback and all associated user interaction. Once the user indicates that he wants to return to your ViewController, your ViewController will receive a call. You must forward this call to story player application:didOpenUrl:annotation: call to ensure that the story player can correctly update its internal state, clean up and in turn invoke the playback completion handler.
 
 ***API Key***
 
 You must pass an API key to the constructor of the player story class when you create an instance of the player. This key is used by the story player to identify the caller of the API and based on that, which functionality in the RealTimes activity should be enabled or disabled.
 
 ***Framework Version***
 RealTimes Framework version is defined in constant **RTRealTimesFrameworkVersion**
 */
@interface RTStoryPlayer : NSObject


/** @name Constructors */

/** Constructs a RealTimes object.
 
 @param APIKey The API key.
 */
- (id)initWithAPIKey:(NSString *)APIKey;


/** Returns *YES* if the RealTimes player activity is installed on the device. */
@property (readonly, nonatomic) BOOL isPlayerInstalled;


/** @name Methods */

/** Must be called from the UIApplicationDelegate: implementation of the current application.
 This method processes the result of a playWithStory:options:handler:error call.
 
 @param application The application.
 @param openURL The URL to open.
 @param annotation The annotation.
 
 @return *YES* if the delegate successfully handled the request or *NO* if the attempt to open the URL resource failed.
 */
- (BOOL)application:(UIApplication *)application didOpenURL:(NSURL *)openURL annotation:(id)annotation;

/** Invokes the RealTimes application if it is installed and triggers the playback of the given story.
 
 Possible __options__ constants:
 
 - The option **RTOptionAllowAutoInstall** specifies whether the RealTimes application should be automatically installed if it is not installed when playWithStory:options:handler:error: has been invoked. The value in dictionary is __NSNumber of BOOL__ (__YES__ or __NO__).
        
        extern NSString *const RTOptionAllowAutoInstall;
 
 - The option **RTOptionAuthenticationToken** allows you to pass an authentication token to the player. The value in dictionary is NSString.
        
        extern NSString *const RTOptionAuthenticationToken;
        
 - The option **RTOptionSavedVideosAlbum** allows you to specify the album where video should be stored in the camera roll, when the user saves a video file from a story (aka publishes a video) or the user shares a story. The value in dictionary is NSString.
        
        extern NSString *const RTOptionSavedVideosAlbum;
 
 - This option **RTOptionSubscriberId** allows you to pass the subscriber ID (MSISDN) to the player. The value in dictionary is NSString.
 
        extern NSString *const RTOptionSubscriberId;
 
 - This option **RTOptionHostAppURLScheme** allows the host application to define own URL scheme so that RealTimes Player knows to send the response to the host app via the URL scheme. The value in dictionary is NSString.

        extern NSString *const RTOptionHostAppURLScheme;
 
 @param story The story to play back.
 @param options The player options.
 @param handler Playback completion handler.
 @param error If not *nil* something went wrong, e.g. RealTimes not installed.
 @return _YES_ if the error has occured, otherwise _NO_.
 */
- (BOOL)playWithStory:(RTStory *)story options:(NSDictionary *)options handler:(id <RTPlaybackCompletionHandling>)handler error:(NSError **)error;

@end

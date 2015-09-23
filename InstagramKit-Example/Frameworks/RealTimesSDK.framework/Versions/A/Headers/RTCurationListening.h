//
//  CurationListener.h
//  RealTimesSDK
//
//  Created by Ante Trbojevic 1 on 10/06/15.
//  Copyright (c) 2015 RealNetworks. All rights reserved.
//

#import <Foundation/Foundation.h>

@class RTCurator;

/** The story curation listener interface defines the methods which an object should implement in order to be able to observe the curation progress for items that are part of a story. 
 
 See the [RTCurator curateWithStory:options:listener:] method for more information.
 */
@protocol RTCurationListening <NSObject>


/** @name Methods */

/** Called at the beginning of the curation.
 
 @param curator The curator.
 */
- (void)curatorDidStartCuration:(RTCurator *)curator;

/** Called once curation has been completed.

 @param curator The curator.
 @param mediaItems Array od curated media items.
 */
- (void)curatorDidCompleteCuration:(RTCurator *)curator withMediaItems:(NSArray*)mediaItems;

/** Called at reasonable intervals while curation is happening.
 
 @param curator The curator.
 @param progress The progress (0 - 1).
 */
- (void)curator:(RTCurator *)curator curationDidProgress:(float)progress;

@end

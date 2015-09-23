//
//  RTStoryCurator.h
//  RealTimesSDK
//
//  Created by Ante Trbojevic 1 on 15/06/15.
//  Copyright (c) 2015 RealNetworks. All rights reserved.
//

#import <Foundation/Foundation.h>

/** Callback which will be called when curation starts */
typedef void(^RTCuratorCurationStartCallbackType)();

/** Callback which will be called for each progress update */
typedef void(^RTCuratorCurationProgressCallbackType)(float progress);

/** Callback which will be called when curation finishes */
typedef void(^RTCuratorCurationCallbackType)(NSArray* mediaItems);

/** Use a RTStoryCurator object to compute curation information for all the media items in a story.
 
 See the RTStory class for an explanation of how curation helps in selecting a good set of hero items for a story.
 */
@interface RTCurator : NSObject

/** @name Methods */

/** Curates all the media items in the given array.
 
 @param mediaItems The array ode media items to curate, each item has to be RTMediaItem.
 @param options Options, pass _nil_ to use the default settings.
 @param startCallback Optional, will be called when curation starts.
 @param progressCallback Optional, will be called for each progress update
 @param completionCallback Will be called when curation finishes.
 */
- (void)curateWithMediaItems:(NSArray *)mediaItems
                     options:(NSDictionary *)options
               startCallback:(RTCuratorCurationStartCallbackType) startCallback
            progressCallback:(RTCuratorCurationProgressCallbackType) progressCallback
          completionCallback:(RTCuratorCurationCallbackType) completionCallback;

@end

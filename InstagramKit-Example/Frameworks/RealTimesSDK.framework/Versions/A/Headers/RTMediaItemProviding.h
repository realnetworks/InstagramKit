//
//  RTMediaItemProviding.h
//  RealTimesSDK
//
//  Created by Ante Trbojevic 1 on 09/06/15.
//  Copyright (c) 2015 RealNetworks. All rights reserved.
//

#import <Foundation/Foundation.h>

@class RTMediaItem;

/** A media item provider is used by a story builder to enumerate all the media items in a media item collection. 
 
 The enumeration is expected to be ordered by the creation date of the media items. The first item that is returned by the item provider should have the oldest creation date and the last item returned by the provider should have the newest creation date.
 
 See RTStoryBuilder for more information.
 */
@protocol RTMediaItemProviding <NSObject>


/** @name Methods */

/** Returns the media item at current position of the item provider.

 If will be *nil* if either the media item collection is empty or all items in collection have been exhausted ( moveToNext returned *NO*).
 
 @return The media item at current position of the item provider.
 */
- (RTMediaItem *)newMediaItem;

/** Moves the item provider to the first media item in the media item collection.
 
 Returns *NO* if the media item collection is empty.
 
 @return *YES* if the move succeeded; *NO* if it failed.
 */
- (BOOL)moveToFirst;

/** Moves the item provider to the next media item in the media item collection. 
 
 Returns *NO* if there are no more media items in collection.
 
 @return *YES* if the move succeeded; *NO* if it failed.
 */
- (BOOL)moveToNext;

@end
